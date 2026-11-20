#include <array>
#include <cstddef>
#include <vector>

class RingBuffer {
  public:
    RingBuffer(size_t capacity) {
        this->capacity = capacity;
        data.reserve(capacity);
    }

    void push(int element) {
        if 

    }

  private:
    size_t capacity;
    std::vector<int> data;
}
