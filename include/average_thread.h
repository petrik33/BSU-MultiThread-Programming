#ifndef INCLUDE_AVERAGE_THREAD_H_
#define INCLUDE_AVERAGE_THREAD_H_

#include <boost/thread.hpp>
#include <iostream>

#include "./array_thread.h"

namespace average_thread {

typedef array_thread::IArrayThreadProps IAverageProps;

class IAveragePromise {
   public:
    IAveragePromise();
    boost::unique_future<double> get_future();
    void set_value(double average);

   protected:
    boost::promise<double> average_;
};

int AverageWorker(const IAverageProps& props, IAveragePromise& promise);
double FindArrayAverage(const int* array, const int size);

}  // namespace average_thread

#endif /* INCLUDE_AVERAGE_THREAD_H_ */
