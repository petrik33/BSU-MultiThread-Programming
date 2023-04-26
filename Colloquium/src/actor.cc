#include "../includes/actor.h"

namespace colloq {
Actor::Actor() : state(new StateIdle(this)), x_(0), y_(0) {
}

Actor::~Actor() {
    delete state;
}

void Actor::Update() {
    State* next_state = state->Update();
    if (next_state != state) {
        delete state;
        state = next_state;
    }
}

const int Actor::x() const {
    return x_;
}

const int Actor::y() const {
    return y_;
}

void Actor::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}
}  // namespace colloq