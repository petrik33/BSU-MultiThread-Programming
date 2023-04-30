#include "../includes/manager.h"
#include "../includes/utils.h"

using data_marker::Manager;
using data_marker::mark_data;
using std::cin;
using std::cout;
using std::make_shared;
using std::shared_ptr;
using std::vector;
using utils::InputDataFromConsole;
using utils::InputWorkerToStop;

void StopOneWorker(Manager& manager);

int main() {
    cout << "MAIN THREAD STARTED WORK\n";
    int data_size, workers_num;
    InputDataFromConsole(data_size, workers_num);
    shared_ptr<mark_data> data{make_shared<mark_data>(data_size, 0)};
    Manager manager{data};
    manager.RunSyncThread(workers_num);
    while (!manager.NoWorkersActive()) {
        manager.StartWaitingThreads();
        manager.WaitRunningThreads();
        manager.PrintData(cout);
        StopOneWorker(manager);
        manager.PrintData(cout);
        manager.StartWaitingThreads();
    }

    cout << "MAIN THREAD FINISHED WORK\n";

    return 0;
}

void StopOneWorker(Manager& manager) {
    int worker_to_stop = InputWorkerToStop();
    while (!manager.StopSyncThread(worker_to_stop)) {
        cout << "Worker already inactive. Try again, please.\n";
        worker_to_stop = InputWorkerToStop();
    }
}
