#ifndef INCLUDE_ARRAY_UTILS_H_
#define INCLUDE_ARRAY_UTILS_H_

#include <iostream>

namespace array_utils {
void InputArray(int* array, int size, std::istream& sin);
void OutputArray(int* array, int size, std::ostream& sout);
}  // namespace array_utils

#endif /* INCLUDE_ARRAY_UTILS_H_ */
