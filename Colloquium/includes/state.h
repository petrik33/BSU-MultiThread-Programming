#ifndef INCLUDES_STATE_H_
#define INCLUDES_STATE_H_

#include "actor.h"
#include "types.h"

namespace colloq {

class State {
   public:
    State();
    virtual ~State();
    State* Update() {
        Move();
        Render();
        return HandleInput();
    };

   protected:
    shared_ptr<Actor> actor;
    virtual void Render() = 0;
    virtual void Move() = 0;
    virtual State* HandleInput() {
        char input;
        cin >> input;
        switch (input) {
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
    };
};

class StateHappy : public State {
   public:
    StateHappy();

   protected:
    void Render() override {
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
    void Move() override {
        actor.get()->move(3, 0);
    }
};

class StateIdle : public State {
   public:
    StateIdle();

   private:
    void Render() override {
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
    };
    void Move() override {
        //
    }
};

class StateSad : public State {
   public:
    StateSad();

   private:
    void Render() override {
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
    };
    void Move() override {
        actor.get()->move(0, 2);
    }
};

}  // namespace colloq

#endif /* INCLUDES_STATE_H_ */
