#include "../includes/state.h"

namespace colloq {
State::State() {
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
        case '2': {
            return new StateSad();
        }
        case '1': {
            return new StateHappy();
        }
        case ' ': {
            return new StateIdle();
        }
        default: {
            return nullptr;
        }
    }
}

StateHappy::StateHappy() : State() {
}

void StateHappy::Render() {
    const int y = actor.get()->y();
    const int x = actor.get()->x();
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
    actor.get()->move(3, 0);
}

StateIdle::StateIdle() : State() {
}

void StateIdle::Render() {
    const int y = actor.get()->y();
    const int x = actor.get()->x();
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

StateSad::StateSad() : State() {
}

void StateSad::Render() {
    const int y = actor.get()->y();
    const int x = actor.get()->x();
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

void StateSad::Move() {
    actor.get()->move(0, 2);
}

}  // namespace colloq