#include "../includes/actor.h"

namespace colloq {
Actor::Actor() : x_(0), y_(0), state(make_unique<StateIdle>()) {}

void Actor::Update() {
    State* next_state = state.get()->Update();
    if (next_state) {
        state = make_unique<State>(next_state);
    }
}

int Actor::x() const {
    return x_;
}

int Actor::y() const {
    return y_;
}

void Actor::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}
}  // namespace colloq