#include "../includes/worker.h"

namespace data_marker {
Worker::Worker(int index, shared_ptr<mark_data> data) : index_(index), busy_(false), active_(true), start_(false), marker_(index, data) {}

void Worker::WaitSignalToStartWork(condition_variable& start_signal, mutex& start_mutex) {
    unique_lock start_lock{start_mutex};
    start_signal.wait(start_lock, [this] { return start_; });
    start_ = false;
}

bool Worker::TryMarking(mutex& data_mutex) {
    unique_lock data_lock{data_mutex};
    marker_.FindMarkTarget();
    if (!marker_.TargetIsMarkable()) {
        return false;
    }
    ThreadImitateWork(5);
    marker_.MarkTargetElement();
    ThreadImitateWork(5);
    return true;
}

void Worker::CleanMarking(mutex& data_mutex) {
    unique_lock data_lock{data_mutex};
    marker_.UnmarkElements();
}

void Worker::FinishWork(condition_variable& finish_signal, int& finished_worker, mutex& finish_mutex, mutex& data_mutex) {
    cout << "Thread " << index_ << " Locked for finish" << endl;
    unique_lock finish_lock{finish_mutex};
    cout << "Thread " << index_ << " Unlocked for finish" << endl;
    marker_.PrintFinishedMarking(cout);
    CleanMarking(data_mutex);
    finished_worker = index_;
    finish_signal.notify_one();
    cout << "Finish lock Free from Thread " << index_ << endl;
}

void Worker::SetStart(bool start) {
    start_ = start;
}

void Worker::SetBusy(bool busy) {
    busy_ = busy;
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