#ifndef INCLUDES_ACTOR_H_
#define INCLUDES_ACTOR_H_

#include "state.h"
#include "types.h"

namespace colloq {

class State;

class Actor {
   public:
    Actor();
    ~Actor();
    void Update();
    const int x() const;
    const int y() const;
    void move(int dx, int dy);

   private:
    State* state;
    int x_;
    int y_;
};

}  // namespace colloq

#endif /* INCLUDES_ACTOR_H_ */
