#include "../includes/marker.h"

#include "../includes/utils.h"

using std::lock_guard;
using std::unique_lock;

namespace marker {

Manager::Manager(SharedVectorPtr data, int threads_num) : alive(threads_num), working(0), data_(data), data_write_mutex_(), working_signal_mutex_() {
    workers_.reserve(threads_num);
}

int Manager::Worker(int index) {
    srand(index);
    const int kDataSize = data_.get()->size();
    int index_to_mark = utils::GetRandomNumber(0, kDataSize);
}

void Manager::Mark(int data_index, int marker_index) {
    unique_lock data_lock{data_write_mutex_};
    utils::ThreadImitateWork(5);
    (*data_.get())[data_index] = marker_index;
    data_lock.unlock();
    utils::ThreadImitateWork(5);
}

}  // namespace marker