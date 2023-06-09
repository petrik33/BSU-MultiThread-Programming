#include <thread>

#include "../includes/actor.h"

using namespace colloq;

int main() {
    Actor actor;

    char c = ' ';
    while (true) {
        // Clear the console screen
        std::cout << "\033[2J\033[1;1H";

        actor.Update(c);
        cin >> c;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}