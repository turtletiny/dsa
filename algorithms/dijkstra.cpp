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

#include <a.out.h>
#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <print>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* input format:
 *
 * src  target   time
 * [1,     2,      1]
 *
 * n = number of nodes
 * k = src node
 * */

int network_delay(std::vector<std::vector<int>> &times, int n, int k) {
    constexpr int MAX_TIME = INT_MAX / 2;
    // init
    std::unordered_set<int> known{k};
    std::vector<int> estimates(n, MAX_TIME);
    estimates[k - 1] = 0;

    for (auto &edge : times) {
        int src = edge[0];
        int target = edge[1];
        int time = edge[2];

        if (src == k) {
            estimates[target - 1] = std::min(estimates[target - 1], time);
        }
    }

    // loop

    while (known.size() < n) {
        int min_time = MAX_TIME;
        int min_node = -1;

        for (int i = 0; i < estimates.size(); ++i) {
            auto node_i = i + 1;
            auto time = estimates[i];
            if (time < min_time && !known.contains(node_i)) {
                min_time = time;
                min_node = node_i;
            }
        }
        if (min_node == -1) return -1;

        known.insert(min_node);

        for (auto &edge : times) {
            int src = edge[0];
            int target = edge[1];
            int time = edge[2];
            if (src == min_node && !known.contains(target)) {
                estimates[target - 1] =
                    std::min(estimates[target - 1], estimates[src - 1] + time);
            }
        }
    }

    return *std::max_element(estimates.begin(), estimates.end());
}

int main() {

    std::vector<std::vector<int>> times = {
        {1, 2, 1}, {2, 3, 1}, {1, 4, 4}, {3, 4, 1}};

    auto a = network_delay(times, 4, 1);
    std::cout << a;

    return 0;
}
