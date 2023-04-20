#ifndef INCLUDES_MARKER_H_
#define INCLUDES_MARKER_H_

#include <memory>
#include <mutex>
#include <thread>

using std::mutex;
using std::shared_ptr;

namespace sync_threads {
namespace marker {

class Props {
   public:
    Props(shared_ptr<int[]> array, shared_ptr<mutex> array_write_mutex) : array_(array), array_write_mutex_(array_write_mutex){};

   private:
    shared_ptr<int[]> array_;
    shared_ptr<mutex> array_write_mutex_;
};

int Worker();

}  // namespace marker
}  // namespace sync_threads

#endif /* INCLUDES_MARKER_H_ */
