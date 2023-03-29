#include "../include/min_max.h"

namespace min_max_thread {
boost::winapi::DWORD_ MinMax(boost::winapi::LPVOID_ iMinMaxProps) {
    IMinMaxProps* props = static_cast<IMinMaxProps*>(iMinMaxProps);
    WIN_PINT array = props->array();
    WIN_INT size = props->size();
    std::cout << "MIN_MAX thread started\n";
    WIN_INT_PAIR min_max_pos = LocateMinMax(array, size);
    props->set_min_max_pos(min_max_pos);
    WIN_INT min = array[min_max_pos.first];
    WIN_INT max = array[min_max_pos.second];
    std::cout << "Min: " << min << ", Max: " << max << "\n";
    std::cout << "MIN_MAX thread ended\n";
}
WIN_INT_PAIR LocateMinMax(WIN_PINT array, WIN_INT size) {
    WIN_INT_PAIR min_max_pos = std::make_pair(0, 0);
    WIN_INT first = array[0];
    WIN_INT_PAIR min_max = std::make_pair(first, first);

    for (int i = 1; i < size; ++i) {
        WIN_INT element = array[i];
        if (element < min_max.first) {
            min_max.first = element;
            min_max_pos.first = i;
        }
        if (element > min_max.second) {
            min_max.second = element;
            min_max_pos.second = i;
        }
    }
    return min_max_pos;
}
IMinMaxProps::IMinMaxProps(WIN_PINT array, WIN_INT size) {
    array_ = array;
    size_ = size;
    min_max_pos_ = std::make_pair(0, 0);
}
WIN_PINT IMinMaxProps::array() { return array_; }
WIN_INT IMinMaxProps::size() { return size_; }
}  // namespace min_max_thread
