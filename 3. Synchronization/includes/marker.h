#ifndef INCLUDES_MARKER_H_
#define INCLUDES_MARKER_H_

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace marker {

typedef std::shared_ptr<std::vector<int>> SharedVectorPtr;

class Manager {
   public:
    Manager(SharedVectorPtr data, int threads_num);

   private:
    int Worker(int index);
    void Mark(int data_index, int marker_index);
    
    int alive;
    int working;
    std::vector<std::thread> workers_;
    SharedVectorPtr data_;
    std::mutex data_write_mutex_;
    std::mutex working_signal_mutex_;
};

}  // namespace marker

#endif /* INCLUDES_MARKER_H_ */
