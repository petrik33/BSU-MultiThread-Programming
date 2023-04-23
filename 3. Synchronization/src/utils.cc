#include "../includes/utils.h"

#include <random>
#include <thread>

namespace utils {
int GetRandomNumber(int min, int max) {
    int range = max - min;
    return rand() % range + min;
}

void ThreadImitateWork(int miliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds{5});
}
}  // namespace utils