#include <vector>

template <typename T> class GraphNode {
public:
  T data;
  std::vector<GraphNode> adjacent_nodes;
};
