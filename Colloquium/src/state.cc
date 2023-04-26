#include "../includes/state.h"

namespace colloq {
State::State(Actor* actor) : actor_(actor) {
}

State::~State() {
}

State* State::Update(char input) {
    Move();
    Render();
    return HandleInput(input);
}

State* State::HandleInput(char input) {
    switch (input) {
        case '3': {
            return new StateSad(actor_);
        }
        case '2': {
            return new StateHappy(actor_);
        }
        case '1': {
            return new StateIdle(actor_);
        }
        default: {
            return this;
        }
    }
}

StateHappy::StateHappy(Actor* actor) : State(actor) {
}

void StateHappy::Render() {
    const int y = actor_->y();
    const int x = actor_->x();
    string xoffset(x, ' ');
    // Draw the smile at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << xoffset;          // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << xoffset;
    cout << "  .-'     `-.  " << endl;
    cout << xoffset;
    cout << " /           \\ " << endl;
    cout << xoffset;
    cout << "| o       o | " << endl;
    cout << xoffset;
    cout << "|           | " << endl;
    cout << xoffset;
    cout << "|  \\     /  | " << endl;
    cout << xoffset;
    cout << " \\  `---'  /  " << endl;
    cout << xoffset;
    cout << "  `-.___.-'   " << endl;
}

void StateHappy::Move() {
    actor_->move(3, 0);
}

StateIdle::StateIdle(Actor* actor) : State(actor) {
}

void StateIdle::Render() {
    const int y = actor_->y();
    const int x = actor_->x();
    string xoffset(x, ' ');
    // Draw the face at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << xoffset;          // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << xoffset;
    cout << "  .'       '.  " << endl;
    cout << xoffset;
    cout << " /           \\ " << endl;
    cout << xoffset;
    cout << "|   0     0   | " << endl;
    cout << xoffset;
    cout << "|      ^      | " << endl;
    cout << xoffset;
    cout << "| \\     /    | " << endl;
    cout << xoffset;
    cout << " \\  ___  /  " << endl;
    cout << xoffset;
    cout << "  `-.___,-'   " << endl;
}

void StateIdle::Move() {
    //
}

StateSad::StateSad(Actor* actor) : State(actor) {
}

void StateSad::Render() {
    const int y = actor_->y();
    const int x = actor_->x();
    string xoffset(x, ' ');
    // Draw the face at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << xoffset;          // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << xoffset;
    cout << "  .'       '.  " << endl;
    cout << xoffset;
    cout << " /           \\ " << endl;
    cout << xoffset;
    cout << "|   0     0   | " << endl;
    cout << xoffset;
    cout << "|      ^      | " << endl;
    cout << xoffset;
    cout << "|  .     .    | " << endl;
    cout << xoffset;
    cout << "|  \\_____\\_/ | " << endl;
    cout << xoffset;
    cout << " \\          /  " << endl;
    cout << xoffset;
    cout << "  `-.___,-'   " << endl;
}

void StateSad::Move() {
    actor_->move(0, 2);
}

}  // namespace colloq