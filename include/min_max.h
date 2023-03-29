#ifndef INCLUDE_MIN_MAX_H_
#define INCLUDE_MIN_MAX_H_

#include <algorithm>
#include <boost/winapi/thread.hpp>
#include <iostream>
#include <limits>
#include <utility>

namespace min_max_thread {

typedef boost::winapi::INT_ WIN_INT;
typedef boost::winapi::PINT_ WIN_PINT;
typedef boost::winapi::DWORD_ WIN_DWORD;
typedef boost::winapi::LPVOID_ WIN_LPVOID;
typedef std::pair<WIN_INT, WIN_INT> WIN_INT_PAIR;

class IMinMaxProps {
   public:
    IMinMaxProps(WIN_PINT array, WIN_INT size);
    WIN_PINT array();
    WIN_INT size();
    WIN_INT_PAIR min_max_pos();
    void set_min_max_pos(WIN_INT_PAIR min_max_pos);

   protected:
    WIN_PINT array_;
    WIN_INT size_;
    WIN_INT_PAIR min_max_pos_;
};

WIN_DWORD MinMax(WIN_LPVOID iMinMaxProps);
WIN_INT_PAIR LocateMinMax(WIN_PINT array, WIN_INT size);

}  // namespace min_max_thread

#endif /* INCLUDE_MIN_MAX_H_ */
