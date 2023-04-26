#include "../includes/state.h"

namespace colloq {
State::State(Actor* actor) : actor_(actor) {
}

State::~State() {
}

State* State::Update() {
    Move();
    Render();
    return HandleInput();
}

State* State::HandleInput() {
    char input;
    cin >> input;
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
    // Draw the smile at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << string(x, ' ');   // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << string(x, ' ');
    cout << "  .-'     `-.  " << endl;
    cout << string(x, ' ');
    cout << " /           \\ " << endl;
    cout << string(x, ' ');
    cout << "| o       o | " << endl;
    cout << string(x, ' ');
    cout << "|           | " << endl;
    cout << string(x, ' ');
    cout << "|  \\     /  | " << endl;
    cout << string(x, ' ');
    cout << " \\  `---'  /  " << endl;
    cout << string(x, ' ');
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
    // Draw the face at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << string(x, ' ');   // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << string(x, ' ');
    cout << "  .'       '.  " << endl;
    cout << string(x, ' ');
    cout << " /           \\ " << endl;
    cout << string(x, ' ');
    cout << "|   0     0   | " << endl;
    cout << string(x, ' ');
    cout << "|      ^      | " << endl;
    cout << string(x, ' ');
    cout << "| \\     /    | " << endl;
    cout << string(x, ' ');
    cout << " \\  ___  /  " << endl;
    cout << string(x, ' ');
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
    // Draw the face at the current position
    cout << string(y, '\n');  // Move the cursor to the correct row
    cout << string(x, ' ');   // Move the cursor to the correct column
    cout << "     _____     " << endl;
    cout << string(x, ' ');
    cout << "  .'       '.  " << endl;
    cout << string(x, ' ');
    cout << " /           \\ " << endl;
    cout << string(x, ' ');
    cout << "|   0     0   | " << endl;
    cout << string(x, ' ');
    cout << "|      ^      | " << endl;
    cout << string(x, ' ');
    cout << "|  .     .    | " << endl;
    cout << string(x, ' ');
    cout << "|  \\_____\\_/ | " << endl;
    cout << string(x, ' ');
    cout << " \\          /  " << endl;
    cout << string(x, ' ');
    cout << "  `-.___,-'   " << endl;
}

void StateSad::Move() {
    actor_->move(0, 2);
}

}  // namespace colloq