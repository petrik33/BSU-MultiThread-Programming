#ifndef INCLUDES_MANAGER_H_
#define INCLUDES_MANAGER_H_

#include "./types.h"

namespace data_marker {

class Manager {
   public:
    Manager(int data_size, int threads_num);
    static Manager& StartManagerFromConsole(int data_size, int threads_num);
    void DeactivateWorker(int index);
    void WaitWorkers();
    void StartWorkers();
    void PrintData(ostream& stream);

   private:
    int workers_busy_;
    bool workers_should_start_;
    mark_data data_;
    mutex data_write_mutex_;
    mutex work_cycle_mutex_;
    condition_variable signal_no_workers_busy_;
    condition_variable signal_workers_should_start_;
};

}  // namespace data_marker

#endif /* INCLUDES_MANAGER_H_ */
