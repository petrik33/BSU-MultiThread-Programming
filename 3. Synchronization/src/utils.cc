#include "../includes/utils.h"

#include <iostream>
#include <random>
#include <thread>

namespace utils {
int GetRandomNumber(int min, int max) {
    int range = max - min;
    return rand() % range + min;
}

void ThreadImitateWork(int miliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds{miliseconds});
}

void InputDataFromConsole(int& array_size, int& workers_num) {
    std::cout << "Input vector size: ";
    std::cin >> array_size;
    std::cout << std::endl;
    std::cout << "Input workers num: ";
    std::cin >> workers_num;
    std::cout << std::endl;
}

int InputWorkerToStop() {
    int worker;
    std::cout << "Input worker to shut down: ";
    std::cin >> worker;
    --worker;
    std::cout << std::endl;
    return worker;
}
}  // namespace utils