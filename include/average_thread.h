#ifndef INCLUDE_AVERAGE_THREAD_H_
#define INCLUDE_AVERAGE_THREAD_H_

#include <boost/thread.hpp>
#include <iostream>

namespace average_thread {

class IAverageProps {
   public:
    IAverageProps(int* array, int size);
    int* array() const;
    int size() const;

   private:
    int* array_;
    int size_;
};

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
