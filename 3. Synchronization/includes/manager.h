#ifndef INCLUDES_MANAGER_H_
#define INCLUDES_MANAGER_H_

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace marker {

class Manager {
   public:
    static Manager& InitializeMarkersManager(int data_size, int threads_num);
    void DeactivateWorker(int index);
    void WaitWorkers();
    void StartWorkers();
    void PrintData(std::ostream& stream);

   private:
    Manager(int data_size, int threads_num);
    int Worker(int index);
    bool WorkerCanMark(Marker& marker, int& element_index);
    void WorkerMark(Marker& marker, int element_index);
    void WorkerFinish(Marker& marker, int unmarked_index);
    void MarkerPrintAll(Marker& marker, int unmarked_index);
    std::vector<std::unique_ptr<std::thread>> workers_;
    int workers_busy_;
    bool workers_should_start_;
    std::vector<bool> active_workers_;
    std::vector<int> data_;
    std::mutex data_write_mutex_;
    std::mutex work_cycle_mutex_;
    std::condition_variable signal_no_workers_busy_;
    std::condition_variable signal_workers_should_start_;
};

}  // namespace marker

#endif /* INCLUDES_MANAGER_H_ */
