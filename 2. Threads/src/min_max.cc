#include "../include/min_max.h"

namespace min_max_thread {

int MinMaxWorker(const IMinMaxProps& props, IMinMaxPromise& promise) {
    std::cout << "MIN_MAX thread started\n";

    int* array = props.array();
    int size = props.size();

    if (size < 1) {
        promise.set_exception(boost::invalid_thread_argument());
        return 1;
    }

    min_max_location_pair min_max_pos = LocateMinMax(array, size);

    int min = array[min_max_pos.first];
    int max = array[min_max_pos.second];

    std::cout << "Min: " << min << ", Max: " << max << "\n";
    std::cout << "MIN_MAX thread ended\n";

    promise.set_value(min_max_pos);
    return 0;
}

min_max_location_pair LocateMinMax(const int* array, const int size) {
    min_max_location_pair min_max_pos = std::make_pair(0, 0);
    int first = array[0];
    std::pair<int, int> min_max = std::make_pair(first, first);

    for (int i = 1; i < size; ++i) {
        int element = array[i];
        if (element < min_max.first) {
            min_max.first = element;
            min_max_pos.first = i;
        }
        if (element > min_max.second) {
            min_max.second = element;
            min_max_pos.second = i;
        }
        boost::this_thread::sleep_for(boost::chrono::milliseconds(7));
    }
    return min_max_pos;
}

IMinMaxPromise::IMinMaxPromise() : boost::promise<min_max_location_pair>(){};

}  // namespace min_max_thread
