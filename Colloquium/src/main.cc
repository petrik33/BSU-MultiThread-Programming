#include <thread>

#include "../includes/actor.h"

namespace colloq {

int main() {
    Actor actor;

    while (true) {
        // Clear the console screen
        system("cls");

        actor.Update();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}

}  // namespace colloq