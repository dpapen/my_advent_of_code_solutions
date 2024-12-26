//
// Created by dpapen on 23.12.24.
//
#include "../../util/util.h"
#include <iostream>


using namespace std;

set<string> augment_clique(const multimap<string, string>& adj, const set<string>& clique, const set<string>& candidates){
    set<string> res{clique};
    size_t i=0;
    for(const string& c : candidates){
        if(res.size()+i >= clique.size()+candidates.size()) return res;//there isn't any bigger clique left to find
        ++i;
        set<string> next_candidates{};
        for(auto edge = adj.lower_bound(c); edge != adj.upper_bound(c); ++edge){
            if(candidates.contains(edge->second) && edge->second != c) {
                next_candidates.insert(edge->second);
            }
        }
        if(clique.size()+1+next_candidates.size()>res.size()) {
            set<string> next_clique{clique};
            next_clique.insert(c);
            set<string> tmp = augment_clique(adj, next_clique, next_candidates);
            if (tmp.size() > res.size()) {
                res.clear();
                res = set<string>{tmp};//TODO move semantic or something similar
            }

        }
    }

    return res;
}


int main(){
string filepath = "../2024/23/input";
vector<string> input = file_to_strings(filepath);

multimap<string, string> adj{};

for(const string& s : input) {
    vector<string> tmp = split_string(s, '-');
    adj.insert({tmp[0], tmp[1]});
    adj.insert({tmp[1], tmp[0]});
}

set<set<string>> k3;//full k3 subgraphs with nodes listed ordered alphabetically as set is ordered
//Part 1
for(auto it= adj.lower_bound("ta"); it!=adj.upper_bound("tz"); ++it){
    for(auto neighbor = adj.lower_bound(it->first); neighbor != adj.upper_bound(it->first); ++neighbor){
        if(0 < std::count(adj.lower_bound(it->second), adj.upper_bound(it->second), pair<const string,string>{it->second, neighbor->second})){
            k3.insert({it->first, it->second, neighbor->second});
        }
    }
}

    cout << k3.size() << "\n";

//Part 2
set<string> keys{};
for(const auto &it : adj) keys.insert(it.first);

set<string> max_clique = augment_clique(adj, set<string>{}, keys);

    for(const string& s : max_clique) cout << s << ",";

    return 0;
}