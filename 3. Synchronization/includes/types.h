#ifndef INCLUDES_TYPES_H_
#define INCLUDES_TYPES_H_

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "./utils.h"

namespace data_marker {

using mark_data = std::vector<int>;
using std::condition_variable;
using std::cout;
using std::mutex;
using std::ostream;
using std::shared_ptr;
using std::thread;
using std::unique_lock;
using std::unique_ptr;
using std::vector;

using std::make_shared;
using std::make_unique;

using utils::GetRandomNumber;
using utils::ThreadImitateWork;

}  // namespace data_marker

#endif /* INCLUDES_TYPES_H_ */
