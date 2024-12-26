//
// Created by dpapen on 09.12.24.
//
#include "../../util/util.h"
#include <iostream>

using namespace std;

//part 1
void fill_gaps_with_fragmentation(vector<int>& disc) {
    int l = 0;
    int r = disc.size()-1;
    while(true) {
        while(l < r && disc[l] >= 0) ++l;
        while(l < r && disc[r] < 0) --r;
        if(l < r) {
            disc[l] = disc[r];
            disc[r] = -1;
        }
        else break;
    }
}

//part 2
struct file {
    int id; //-1 if free
    int offset;
    int size;
};

class Disc {
private:
    vector<file> disc;

public:
    Disc(const vector<int>& disc_map) {
        int offset = 0;
        for(int i=0; i<disc_map.size(); ++i) {
            int id = (i%2==0)? i/2 : -1;
            disc.push_back({id,offset,disc_map[i]});
            offset += disc_map[i];
        }
    }

    map<int,int> get_id_to_index() {
        map<int,int> res{};
        for(int i=0; i<disc.size(); ++i) {
            if(disc[i].id >= 0) res.insert({disc[i].id,i});
        }
        return res;
    }


    bool move(int file_index, int dest_index){
        auto f = disc.begin() + file_index;
        auto d = disc.begin()+dest_index;

        //check if possible
        if(f->id < 0) return false;//not a file
        if(d->id >= 0) return false;//dest not a free section
        if(f->size > d->size) return false; //not enough space

        file to_insert = {f->id, d->offset, f->size};

        //adjust dest
        d->offset += f->size;
        d->size -= f->size;

        //insert before dest
        //do later to not invalidate iterators
        f->id = -1; //mark the old file as free

        //merge next block (if existing and free) with f
        if((f+1) != disc.end() && (f+1)->id < 0) {
            f->size += (f+1)->size;
            (f+1)->size = 0;
        }
        //merge f into previous block (if existing and free)
        if(f != disc.begin() && (f-1)->id < 0) {
            (f-1)->size += f->size;
            f->size = 0;
        }

        //insert
        disc.insert(d, to_insert);

        return true;
    }

    void cleanup() {
        for (std::vector<file>::iterator it = disc.begin(); it != disc.end();)
        {
            if (it->size == 0) it = disc.erase(it);
            else ++it;
        }
    }

    void fill_gaps_without_fragmentation() {
        map<int,int> id_to_index = get_id_to_index();
        //assumes id are given without gaps starting at 0
        for(int id=id_to_index.size()-1; id>=0; --id) {
            cleanup();
            id_to_index = get_id_to_index();
            int i = id_to_index[id];

            for(int j=0; j<i; ++j) {
                if(move(i,j)) break;
            }
        }
    }


    long long checksum() {
        long long res = 0;
        for(file f : disc) {
            if(f.id >= 0) {
                cout << f.id << ": " << f.size*f.offset+(f.size*f.size-1)/2 << "\n";
                res += f.id * (f.size*f.offset+(f.size*f.size-1)/2);
            }
        }
        return res;
    }

    void print() {
        for(file f : disc) {
            cout << f.id << "\t" << f.offset << "\t" << f.size << "\n";
        }
        cout << "\n";
    }

    long long checksum2() {
        long long res = 0;
        int pos = 0;
        for(file f : disc) {
            for(int i=0; i<f.size; ++i) {
                if(f.id>=0) res += pos*f.id;
                ++pos;
            }
        }
        return res;
    }

};






int main() {
    vector<int> input = string_to_digits(file_to_strings("../2024/09/input")[0]);

    //decode input to disc layout
    vector<int> disc;
    for(int i=0; i<input.size(); ++i) {
        int id = (i%2==0)? i/2 : -1;
        for(int j=0; j<input[i]; ++j) {
            disc.push_back(id);
        }
    }

    //fill gaps
    fill_gaps_with_fragmentation(disc);

    //calculate checksum
    long long res = 0;
    for(int i=0; i<disc.size(); ++i) {
        if(disc[i] == -1) break;
        res += i*disc[i];
    }
    cout << res << "\n";

    //PART2
    input = string_to_digits(file_to_strings("../2024/09/input")[0]);
    Disc d = Disc(input);
    d.fill_gaps_without_fragmentation();
    cout << d.checksum() << "\n";
    cout << d.checksum2() << "\n";


    return 0;
}