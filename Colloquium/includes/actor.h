#ifndef INCLUDES_ACTOR_H_
#define INCLUDES_ACTOR_H_

#include "state.h"
#include "types.h"

namespace colloq {

class Actor {
   public:
    Actor();
    void Update() {
        State* next_state = state.get()->Update();
        if (next_state) {
            state = make_unique<State>(next_state);
        }
    };
    int x() const { return x_; };
    int y() const { return y_; };
    void move(int dx, int dy) {
        x_ += dx;
        y_ += dy;
    }

   private:
    unique_ptr<State> state;
    int x_;
    int y_;
};

}  // namespace colloq

#endif /* INCLUDES_ACTOR_H_ */
