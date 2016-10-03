#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using std::vector;
using std::pair;

// class lessthan {
//   public:
//     bool operator()(const pair<int,int> & p1, const pair<int,int> & p2) const {
//         if (p1.first != p2.first)
//             return p1.first < p2.first;
//         else if (p1.second != p2.second)
//             return p1.second < p2.second;
//         else
//             return false;
//     }
// };

bool operator<(const pair<int,int> & p1, const pair<int,int> & p2) {
    if (p1.first != p2.first)
        return p1.first < p2.first;
    else if (p1.second != p2.second)
        return p1.second < p2.second;
    else
        return false;
}

class solution {
  public:
    vector<pair<int,int>> maxEnvelopes(const vector<pair<int,int>> & envelopes) {
        std::set<pair<int,int>> cands;
        for (auto p : envelopes)
            cands.insert(p);

        vector<vector<pair<int,int>>> paths;
        for (auto it = cands.begin(); it != cands.end(); ++it) {
            auto updated = cands;
            updated.erase(*it);
            auto temp = fromTo(updated, *it);
            std::cout << "From [" << it->first << "," << it->second << "]:" << std::endl;
            for (auto tmp : temp) {
                std::for_each(tmp.begin(), tmp.end(),
                              [](const pair<int,int> & pr){
                                  std::cout << "[" << pr.first << "," << pr.second << "]";
                              });
                std::cout << std::endl;
                paths.push_back(tmp);
            }
        }

        size_t idx = 0;
        for (size_t i = idx+1; i < paths.size(); ++i) {
            if (paths[i].size() > paths[idx].size())
                idx = i;
        }

        return paths[idx];
    }

  private:
    vector<vector<pair<int,int>>> fromTo(const std::set<pair<int,int>> & sets, const pair<int,int> & curr)
    {
        vector<vector<pair<int,int>>> result;
        auto next = getNext(sets, curr);
        if (next.empty()) {
            vector<pair<int,int>> temp{curr};
            result.push_back(temp);
        }
        else {
            vector<vector<pair<int,int>>> cands;
            for (auto nx : next) {
                auto updated = sets;
                updated.erase(nx);
                auto temp = fromTo(updated, nx);
                for (auto tmp : temp) {
                    tmp.insert(tmp.begin(), curr);
                    cands.push_back(tmp);
                }
            }

            if (!cands.empty()) {
                size_t idx = 0;
                for (size_t i = idx+1; i < cands.size(); ++i) {
                    if (cands[i].size() > cands[idx].size())
                        idx = i;
                }

                for (size_t i = 0; i < cands.size(); ++i) {
                    if (cands[i].size() == cands[idx].size())
                        result.push_back(cands[i]);
                }
            }
        }
        return result;
    }

    vector<pair<int,int>> getNext(const std::set<pair<int,int>> & sets, const pair<int,int> & curr)
    {
        vector<pair<int,int>> next;
        for (auto it = sets.begin(); it != sets.end(); ++it) {
            if (it->first > curr.first && it->second > curr.second)
                next.push_back(*it);
        }
        return next;
    }
};

int main() {
    vector<pair<int,int>> envelopes;
    envelopes.push_back(std::make_pair(5,4));
    envelopes.push_back(std::make_pair(6,4));
    envelopes.push_back(std::make_pair(6,7));
    envelopes.push_back(std::make_pair(2,3));

    solution soln;
    auto paths = soln.maxEnvelopes(envelopes);
    std::cout << "The longest envelope is:\n";
    std::for_each(paths.begin(), paths.end(),
                  [](const pair<int,int> & pr){
                      std::cout << "[" << pr.first << "," << pr.second << "]";
                  });
    std::cout << std::endl;
}
