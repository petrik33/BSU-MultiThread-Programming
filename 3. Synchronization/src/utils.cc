#include "../includes/utils.h"

#include "random"

namespace utils {
int GetRandomNumber(int min, int max) {
    int range = max - min;
    return rand() % range + min;
}
}  // namespace utils