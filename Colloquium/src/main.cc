#include <thread>

#include "../includes/actor.h"

using namespace colloq;

int main() {
    Actor actor;

    while (true) {
        // Clear the console screen
        cout.flush();

        actor.Update();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}