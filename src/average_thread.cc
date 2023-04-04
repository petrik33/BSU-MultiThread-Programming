#include "../include/average_thread.h"

namespace average_thread {
IAveragePromise::IAveragePromise() : average_(boost::promise<double>()) {}

boost::unique_future<double> IAveragePromise::get_future() {
    return average_.get_future();
}

void IAveragePromise::set_value(double average) {
    average_.set_value(average);
}

int AverageWorker(const IAverageProps& props, IAveragePromise& promise) {
    std::cout << "AVERAGE thread started\n";

    int* array = props.array();
    int size = props.size();

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