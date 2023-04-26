#ifndef INCLUDES_ACTOR_H_
#define INCLUDES_ACTOR_H_

#include "state.h"
#include "types.h"

namespace colloq {

class State;

class Actor {
   public:
    Actor();
    void Update();
    int x() const;
    int y() const;
    void move(int dx, int dy);

   private:
    unique_ptr<State> state;
    int x_;
    int y_;
};

}  // namespace colloq

#endif /* INCLUDES_ACTOR_H_ */
