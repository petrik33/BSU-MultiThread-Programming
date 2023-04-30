#include "../includes/worker.h"

namespace data_marker {
Worker::Worker(int index, shared_ptr<mark_data> data) : busy_(false), active_(true), marker_(index, data) {}

void Worker::WaitSignalToStartWork(condition_variable& start_signal, mutex& start_mutex) {
    unique_lock start_lock{start_mutex};
    start_signal.wait(start_lock);
}

bool Worker::TryMarking(mutex& data_mutex) {
    unique_lock data_lock{data_mutex};
    marker_.FindMarkTarget();
    if (!marker_.TargetIsMarkable()) {
        return false;
    }
    ThreadImitateWork(5);
    marker_.MarkTargetElement();
    data_lock.unlock();
    ThreadImitateWork(5);
    return true;
}

void Worker::CleanMarking(mutex& data_mutex) {
    unique_lock data_lock{data_mutex};
    marker_.UnmarkElements();
}

void Worker::FinishWork(condition_variable& finish_signal, mutex& finish_mutex, mutex& data_mutex) {
    unique_lock finish_lock{finish_mutex};
    marker_.PrintFinishedMarking(cout);
    CleanMarking(data_mutex);
    busy_ = false;
    finish_signal.notify_all();
}

bool Worker::IsBusy() const {
    return busy_;
}

bool Worker::IsActive() const {
    return active_;
}

void Worker::Deactivate() {
    active_ = false;
}

}  // namespace data_marker