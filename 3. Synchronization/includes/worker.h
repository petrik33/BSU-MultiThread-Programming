#ifndef INCLUDES_WORKER_H_
#define INCLUDES_WORKER_H_

#include "./types.h"

namespace data_marker {
class Worker {
   public:
    explicit Worker();

   private:
    bool active_;
    mutex write_mutex_;
    mutex start_mutex_;
    condition_variable start_signal_;
    condition_variable finished_signal_;
};
}  // namespace data_marker

#endif /* INCLUDES_WORKER_H_ */
