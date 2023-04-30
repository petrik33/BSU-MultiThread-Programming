#ifndef INCLUDES_MANAGER_H_
#define INCLUDES_MANAGER_H_

#include "./types.h"
#include "./worker.h"

namespace data_marker {

class Manager {
   public:
    Manager(shared_ptr<mark_data> data);
    void SingleSyncWorker(int index);
    void RunSyncThread(int number = 1);
    bool StopSyncThread(int index);
    void WaitRunningThreads();
    void StartWaitingThreads();
    bool AllWorkersFree() const;
    bool NoWorkersActive() const;
    void PrintData(ostream& stream) const;

   private:
    shared_ptr<mark_data> data_;
    vector<thread> threads_;
    vector<Worker> workers_;
    mutable int workers_busy_;
    mutable int workers_active_;
    mutex data_mutex_;
    mutex workers_start_mutex_;
    mutex worker_finished_mutex_;
    condition_variable workers_start_signal_;
    condition_variable worker_finished_signal_;
};

}  // namespace data_marker

#endif /* INCLUDES_MANAGER_H_ */
