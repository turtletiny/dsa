/*
 * ===Pseudocode===
 *
 * Initialisation
 *
 * 1. vec<Node> known_nodes = {u} //init source node in vec
 * 2. check every node a; if a adjacent to u
 *
 *
 *
 *
 */

#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>

class Solution {
  public:
    int networkDelayTime(std::vector<std::vector<int>> &times, int n, int k) {
        constexpr int INFINITY = 1001;
        constexpr int NO_PREV = -1;

        // init
        std::unordered_set<int> known = {k};
        std::vector<int> estimates(n);
        std::vector<int> prev_node(n);

        for (auto node : times) {
            int src = node[0];
            int dst = node[1];
            int t = node[2];

            if (src == k) {
                estimates[dst - 1] = t;
                prev_node[dst - 1] = src;
            } else {
                estimates[dst - 1] = INFINITY;
                prev_node[dst - 1] = NO_PREV;
            }
        }

        // loop

        while (known.size() < n) {
            // find min estimates
            int min_node = -1;
            int cur_min = INFINITY;
            for (int i = 0; i < estimates.size(); i++) {
                if (!known.contains(i + 1) && estimates[i] < cur_min) {
                    cur_min = estimates[i];
                    min_node = i + 1;
                }
            }

            known.insert(min_node);
            for (auto node : times) {
                int src = node[0];
                int dst = node[1];
                int t = node[2];

                if (src == min_node && !known.contains(dst)) {
                    estimates[dst - 1] =
                        std::min(estimates[dst - 1], estimates[src - 1] + t);
                }
                if (src == prev_node[estimates[min_node - 1]] &&
                    dst == min_node) {
                    estimates[min_node - 1] =
                        std::min(estimates[min_node - 1],
                                 estimates[prev_node[min_node - 1]] + t);
                }
            }
        }

        return std::accumulate(estimates.begin(), estimates.end(), 0);
    }
};
