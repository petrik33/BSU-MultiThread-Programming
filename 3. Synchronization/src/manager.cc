#include "../includes/manager.h"

#include "../includes/marker.h"
#include "../includes/utils.h"

using std::unique_lock;

namespace data_marker {
Manager::Manager(shared_ptr<mark_data> data) : data_(data), workers_busy_(0), workers_active_(0) {
}

void Manager::RunSyncThread(int number) {
    int index = workers_.size();
    for (int i = 0; i < number; i++) {
        int thread_idx = index + i;
        workers_.push_back(Worker{thread_idx, data_});
        threads_.push_back(thread{[this, thread_idx] {
            SingleSyncWorker(thread_idx);
            return 0;
        }});
    }
    workers_active_ += number;
}

bool Manager::StopSyncThread(int index) {
    if (!workers_[index].IsActive()) {
        return false;
    }
    workers_[index].Deactivate();
    threads_[index].join();
    workers_active_--;
    return true;
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
    worker_finished_signal_.wait(workers_finished_lock, [this] {
        workers_busy_--;
        return AllWorkersFree();
    });
}

void Manager::StartWaitingThreads() {
    unique_lock workers_start_lock{workers_start_mutex_};
    workers_start_signal_.notify_all();
    workers_busy_ += workers_active_;
}

bool Manager::AllWorkersFree() const {
    return workers_busy_ == 0;
}

bool Manager::NoWorkersActive() const {
    return workers_active_ == 0;
}

}  // namespace data_marker