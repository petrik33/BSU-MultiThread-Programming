#include "../includes/manager.h"

#include "../includes/marker.h"
#include "../includes/utils.h"

using std::unique_lock;

namespace data_marker {
Manager::Manager(shared_ptr<mark_data> data) : data_(data), workers_busy_(0) {
}

void Manager::StartSyncThread(int index) {
    threads_.push_back(thread{Manager::SingleSyncWorker, index});
}

void Manager::StopSyncThread(int index) {
    DeactivateWorker(index);
    threads_[index].join();
}

void Manager::PrintData(std::ostream& stream) const {
    const mark_data& data_reference = *data_.get();
    for (auto& element : data_reference) {
        stream << element << " ";
    }
    stream << std::endl;
}

void Manager::SingleSyncWorker(int index) {
    Worker& worker = workers_[index];
    worker.WaitSignalToStartWork(workers_start_signal_, workers_start_mutex_);
    while (worker.IsActive()) {
        while (worker.TryMarking(data_mutex_)) {
        }
        worker.FinishWork(worker_finished_signal_, worker_finished_mutex_, data_mutex_);
        worker.WaitSignalToStartWork(workers_start_signal_, workers_start_mutex_);
    }
    worker.CleanMarking(data_mutex_);
}

void Manager::WaitRunningThreads() {
    unique_lock workers_finished_lock{worker_finished_mutex_};
    worker_finished_signal_.wait(workers_finished_lock, ReceiveFinishedWork);
}

void Manager::StartWaitingThreads() {
    unique_lock workers_start_lock{workers_start_mutex_};
    workers_start_signal_.notify_all();
}

void Manager::AddWorker() {
    Worker worker{workers_.size(), data_};
    workers_.push_back(worker);
}

void Manager::DeactivateWorker(int index) {
    workers_[index].Deactivate();
}

bool Manager::ReceiveFinishedWork() {
    workers_busy_--;
    return AllWorkersFree();
}

bool Manager::AllWorkersFree() const {
    return workers_busy_ == 0;
}

}  // namespace data_marker