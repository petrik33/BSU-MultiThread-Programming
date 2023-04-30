#ifndef INCLUDES_UTILS_H_
#define INCLUDES_UTILS_H_

namespace utils {

// Generates random number from min inclusively to max exclusively
int GetRandomNumber(int min, int max);
void ThreadImitateWork(int miliseconds);
void InputDataFromConsole(int& array_size, int& workers_num);
int InputWorkerToStop();

}  // namespace utils

#endif /* INCLUDES_UTILS_H_ */
