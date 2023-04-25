#ifndef INCLUDES_TYPES_H_
#define INCLUDES_TYPES_H_

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace data_marker {

using mark_data = std::vector<int>;
using std::condition_variable;
using std::mutex;
using std::ostream;
using std::shared_ptr;
using std::thread;
using std::unique_lock;
using std::vector;

}  // namespace data_marker

#endif /* INCLUDES_TYPES_H_ */
