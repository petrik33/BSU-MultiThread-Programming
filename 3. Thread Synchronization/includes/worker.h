#ifndef INCLUDES_WORKER_H_
#define INCLUDES_WORKER_H_

#include "./marker.h"
#include "./types.h"

namespace data_marker {
class Worker {
   public:
    Worker(int index, shared_ptr<mark_data> data);
    void WaitSignalToStartWork(condition_variable& start_signal, mutex& start_mutex);
    bool TryMarking(mutex& data_mutex);
    void CleanMarking(mutex& data_mutex);
    void FinishWork(condition_variable& finish_signal, int& finished_worker, mutex& finish_mutex, mutex& data_mutex);
    void SetStart(bool start);
    void SetBusy(bool busy);
    bool IsBusy() const;
    bool IsActive() const;
    void Deactivate();

   private:
    int index_;
    bool start_;
    bool busy_;
    bool active_;
    Marker marker_;
};
}  // namespace data_marker

#endif /* INCLUDES_WORKER_H_ */
