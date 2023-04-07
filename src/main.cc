#include <boost/thread.hpp>
#include <exception>
#include <iostream>

#include "../include/array_utils.h"
#include "../include/average_thread.h"
#include "../include/min_max.h"

int min_max_thread::MinMaxWorker(const IMinMaxProps& props, IMinMaxPromise& promise);

int average_thread::AverageWorker(const IAverageProps& props, IAveragePromise& promise);

int InputArraySizeFromConsole();

int main() {
    std::cout << "PROGRAM started\n";

    int size = InputArraySizeFromConsole();

    auto array = std::shared_ptr<int[]>(new int[size]);
    std::cout << "Enter array elements:" << std::endl;
    array_utils::InputArray(array.get(), size, std::cin);

    min_max_thread::IMinMaxProps min_max_props(array.get(), size);
    average_thread::IAverageProps average_props(array.get(), size);

    min_max_thread::IMinMaxPromise min_max_promise;
    average_thread::IAveragePromise average_promise;

    boost::thread min_max_thread(min_max_thread::MinMaxWorker, std::cref(min_max_props), std::ref(min_max_promise));

    boost::thread average_thread(average_thread::AverageWorker, std::cref(average_props), std::ref(average_promise));

    auto min_max_future = min_max_promise.get_future();
    min_max_thread::min_max_location_pair min_max_pos;

    try {
        min_max_pos = min_max_future.get();
    } catch (const std::exception error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }

    auto average_future = average_promise.get_future();
    double average_value;

    try {
        average_value = average_future.get();
    } catch (const std::exception error) {
        std::cerr << error.what() << std::endl;
    }

    std::cout << "Changing min and max elements with floored average..." << std::endl;

    int min_pos = min_max_pos.first;
    int max_pos = min_max_pos.second;

    array[min_pos] = floor(average_value);
    array[max_pos] = floor(average_value);

    std::cout << "Changed array:" << std::endl;
    array_utils::OutputArray(array.get(), size, std::cout);

    average_thread.join();
    min_max_thread.join();

    std::cout << "PROGRAM ended\n";
    return 0;
}

int InputArraySizeFromConsole() {
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;
    while (size < 1) {
        std::cout << "Invalid array size. Please, enter again: ";
        std::cin >> size;
    }
    return size;
}
