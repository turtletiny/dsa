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
#include <print>
#include <unordered_set>
#include <vector>

int network_delay(std::vector<std::vector<int>> &times, int n, int k, int destination) {
    /* assuming max time =  1000*/
    constexpr int INF = 1001;
    constexpr int NO_PREV = -1;

    // init
    std::unordered_set<int> known = {k};
    std::vector<int> estimates(n, INF); // nodes 1 - n
    std::vector<int> prev_node(n, NO_PREV); // nodes 1 - n 
    estimates[k - 1] = 0;

    for (auto node : times) {
        int src = node[0];
        int dst = node[1];
        int t = node[2];

        if (src == k) {
            estimates[dst - 1] = t;
            prev_node[dst - 1] = src;
        }
    }

    // loop
    while (known.size() < n) {
        // find min estimates
        int min_node = -1;
        int cur_min = INF;
        for (int i = 0; i < estimates.size(); i++) {
            if (!known.contains(i + 1) && estimates[i] < cur_min) {
                cur_min = estimates[i];
                min_node = i + 1;
            }
        }

        known.insert(min_node);
        for (const auto &edge : times) {
            int src = edge[0];
            int dst = edge[1];
            int t = edge[2];

            if (src == min_node && !known.contains(dst)) {
                estimates[dst - 1] =
                    std::min(estimates[dst - 1], estimates[src - 1] + t);
            }
        }
    }

    return estimates[destination - 1];
}

int main() {

    std::vector<std::vector<int>> times = {
        {1, 2, 1}, {2, 3, 1}, {1, 4, 4}, {3, 4, 1}};

    auto a = network_delay(times, 4, 1, 4);
    std::println("{}", a);

    return 0;
}
