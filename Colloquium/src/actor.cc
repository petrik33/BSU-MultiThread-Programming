#include "../includes/actor.h"

namespace colloq {
Actor::Actor() : state(new StateIdle()), x_(0), y_(0) {}

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