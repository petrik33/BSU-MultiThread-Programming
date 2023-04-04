#include "../include/array_thread.h"

namespace array_thread {
IArrayThreadProps::IArrayThreadProps(int* array, int size) {
    array_ = array;
    size_ = size;
}

int* IArrayThreadProps::array() const { return array_; }
int IArrayThreadProps::size() const { return size_; }

}  // namespace array_thread