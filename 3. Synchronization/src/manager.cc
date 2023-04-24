#include "../includes/manager.h"

#include "../includes/marker.h"
#include "../includes/utils.h"

using std::unique_lock;

namespace marker {
Manager& Manager::InitializeMarkersManager(int data_size, int threads_num) {
    Manager manager{data_size, threads_num};
    manager.StartWorkers();
}

void Manager::DeactivateWorker(int index) {
    active_workers_[index] = false;
}

void Manager::WaitWorkers() {
    unique_lock workers_lock{work_cycle_mutex_};
    signal_no_workers_busy_.wait(workers_lock, [this] { return !workers_busy_; });
}

void Manager::StartWorkers() {
    unique_lock workers_lock{work_cycle_mutex_};
    int threads_num = workers_.size();
    int active_num = 0;
    for (int i = 0; i < threads_num; i++) {
        if (!active_workers_[i]) {
            continue;
        }
        ++active_num;
    }
    workers_should_start_ = true;
    workers_lock.unlock();
    signal_workers_should_start_.notify_all();
    workers_busy_ = active_num;
}

void Manager::PrintData(std::ostream& stream) {
    for (auto& element : data_) {
        stream << element << " ";
    }
    stream << std::endl;
}

Manager::Manager(int data_size, int threads_num) : data_(data_size, 0), active_workers_(threads_num, true), workers_busy_(0), workers_(threads_num, nullptr) {
    for (int i = 0; i < threads_num; i++) {
        workers_[i] = std::make_unique<std::thread>(Worker, &(*this));
    }
}

int Manager::Worker(int index) {
    Marker marker{index};
    int element_index;

    unique_lock work_lock{work_cycle_mutex_};
    signal_workers_should_start_.wait(work_lock, [this] { return workers_should_start_; });
    work_lock.unlock();

    while (active_workers_[index]) {
        while (WorkerCanMark(marker, element_index)) {
            WorkerMark(marker, element_index);
        }
        WorkerFinish(marker, element_index);
        work_lock.lock();
        signal_workers_should_start_.wait(work_lock, [this] { return workers_should_start_; });
        work_lock.unlock();
    }
}

bool Manager::WorkerCanMark(Marker& marker, int& element_index) {
    int element_index = Marker::FindMarkTarget(data_);
    return Marker::ElementIsMarkable(data_, element_index);
}

void Manager::WorkerMark(Marker& marker, int element_index) {
    unique_lock write_lock{data_write_mutex_};
    utils::ThreadImitateWork(5);
    marker.MarkElement(data_, element_index);
    write_lock.unlock();
    utils::ThreadImitateWork(5);
}

void Manager::WorkerFinish(Marker& marker, int unmarked_index) {
    MarkerPrintAll(marker, unmarked_index);
    unique_lock work_lock{work_cycle_mutex_};
    workers_busy_--;
    work_lock.unlock();
    signal_no_workers_busy_.notify_one();
}

void Manager::MarkerPrintAll(Marker& marker, int unmarked_index) {
    marker.PrintIndex(std::cout);
    marker.PrintMarkedElementsNumber(std::cout);
    marker.PrintUnmarkableElement(std::cout, unmarked_index);
}

}  // namespace marker