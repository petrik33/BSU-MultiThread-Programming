#include "../includes/manager.h"

#include "../includes/marker.h"
#include "../includes/utils.h"

using std::unique_lock;

namespace data_marker {
Manager::Manager(shared_ptr<mark_data> data) : data_(data), finished_worker_(-1) {
}

bool Manager::StopSyncThread(int index) {
    if (!workers_[index].IsActive()) {
        return false;
    }
    workers_[index].Deactivate();
    workers_[index].SetStart(true);
    workers_start_signal_.notify_all();
    threads_[index].join();
    return true;
}

void Manager::PrintData(std::ostream& stream) const {
    const mark_data& data_reference = *data_.get();
    for (auto& element : data_reference) {
        stream << element << " ";
    }
    stream << std::endl;
}

void Manager::CheckFinishedWorker() {
    cout << "Check Finished Worker " << finished_worker_ << endl;
    if (finished_worker_ == -1) {
        return;
    }
    Worker& worker = workers_[finished_worker_];
    if (!worker.IsBusy()) {
        cout << "Worker " << finished_worker_ << " wasn't busy" << endl;
        return;
    }
    worker.SetBusy(false);
    cout << "Worker " << finished_worker_ << " set free" << endl;
    finished_worker_ = -1;
}

void Manager::SingleSyncWorker(int index) {
    Worker& worker = workers_[index];
    worker.WaitSignalToStartWork(workers_start_signal_, workers_start_mutex_);
    while (worker.IsActive()) {
        while (worker.TryMarking(data_mutex_)) {
        }
        worker.FinishWork(worker_finished_signal_, finished_worker_, worker_finished_mutex_, data_mutex_);
        worker.WaitSignalToStartWork(workers_start_signal_, workers_start_mutex_);
    }
    worker.CleanMarking(data_mutex_);
}

void Manager::AddWorker() {
    workers_.emplace_back(workers_.size(), data_);
}

void Manager::StartSyncThread(int index) {
    threads_.emplace_back([this, index] {
        SingleSyncWorker(index);
    });
}

void Manager::WaitRunningThreads() {
    cout << "Main Thread Locked for finish wait" << endl;
    unique_lock workers_finished_lock{worker_finished_mutex_};
    worker_finished_signal_.wait(workers_finished_lock, [this] {
        CheckFinishedWorker();
        return AllWorkersFree();
    });
    cout << "Main Thread Unlocked after finish wait" << endl;
}

void Manager::StartWaitingThreads() {
    unique_lock workers_start_lock{workers_start_mutex_};
    for (auto& worker : workers_) {
        if (worker.IsActive()) {
            worker.SetStart(true);
        }
    }
    workers_start_signal_.notify_all();
}

bool Manager::AllWorkersFree() const {
    int workers_busy = 0;
    for (auto& worker : workers_) {
        if (worker.IsBusy()) {
            workers_busy++;
        }
    }
    cout << "Workers busy: " << workers_busy << endl;
    return workers_busy == 0;
}

bool Manager::NoWorkersActive() const {
    int workers_active = 0;
    for (auto& worker : workers_) {
        if (worker.IsActive()) {
            workers_active++;
        }
    }
    return workers_active == 0;
}

}  // namespace data_marker