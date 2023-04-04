#ifndef INCLUDE_MIN_MAX_H_
#define INCLUDE_MIN_MAX_H_

#include <algorithm>
#include <boost/thread.hpp>
#include "./array_thread.h"
#include <iostream>
#include <utility>

namespace min_max_thread {

typedef std::pair<int, int> min_max_location_pair;
typedef array_thread::IArrayThreadProps IMinMaxProps;

class IMinMaxPromise {
   public:
    IMinMaxPromise();
    boost::unique_future<min_max_location_pair> get_future();
    void set_value(min_max_location_pair min_max_pos_);

   protected:
    boost::promise<min_max_location_pair> promise_;
};

int MinMaxWorker(const IMinMaxProps& props, IMinMaxPromise& promise);
min_max_location_pair LocateMinMax(const int* array, const int size);

}  // namespace min_max_thread

#endif /* INCLUDE_MIN_MAX_H_ */
