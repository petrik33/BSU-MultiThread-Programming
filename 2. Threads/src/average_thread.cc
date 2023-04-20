#include "../include/average_thread.h"

namespace average_thread {
IAveragePromise::IAveragePromise() : boost::promise<double>(){};

int AverageWorker(const IAverageProps& props, IAveragePromise& promise) {
    std::cout << "AVERAGE thread started\n";

    int* array = props.array();
    int size = props.size();

    if (size < 1) {
        promise.set_exception(boost::invalid_thread_argument());
        return 1;
    }

    double average = FindArrayAverage(array, size);

    std::cout << "Average: " << average << "\n";
    std::cout << "AVERAGE thread ended\n";

    promise.set_value(average);
    return 0;
}

double FindArrayAverage(const int* array, const int size) {
    int sum = 0;

    for (int i = 0; i < size; ++i) {
        sum += array[i];
        boost::this_thread::sleep_for(boost::chrono::milliseconds(12));
    }

    return static_cast<double>(sum) / size;
}

}  // namespace average_thread