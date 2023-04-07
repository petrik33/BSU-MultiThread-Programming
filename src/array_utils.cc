#include "../include/array_utils.h"

namespace array_utils {
void InputArray(int* array, int size, std::istream& sin) {
    for (int i = 0; i < size; ++i) {
        sin >> array[i];
    }
}

void OutputArray(int* array, int size, std::ostream& sout) {
    for (int i = 0; i < size; ++i) {
        sout << array[i] << " ";
    }
}
}  // namespace array_utils
