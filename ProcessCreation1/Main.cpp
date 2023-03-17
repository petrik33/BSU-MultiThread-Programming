#include <fstream>
#include <iostream>

#include "Creator.h"
#include "Reporter.h"

DWORD WINAPI creator::Creator(LPVOID iCreatorProps);
DWORD WINAPI reporter::Reporter(LPVOID iReporterProps);

namespace {
void outputStreamToStream(std::istream& in, std::ostream& out);
}

int main() {
  std::cout << "PROCESS CREATION APP\n\n";

  HANDLE creatorThread;
  DWORD creatorThreadID;
  creator::ICreatorProps* creatorProps = new creator::ICreatorProps();

  std::cout << "Enter data file name: ";
  // char fileName[50];
  std::cin >> creatorProps->fileName;

  std::cout << "Enter number of employees: ";
  // int employeesNum;
  std::cin >> creatorProps->recordsNum;

  std::cout << "\n";
  creatorThread = CreateThread(NULL, 0, creator::Creator, (void*)creatorProps,
                               0, &creatorThreadID);
  if (!creatorThread) {
    return GetLastError();
  }

  WaitForSingleObject(creatorThread, INFINITE);
  CloseHandle(creatorThread);

  std::cout << "Your data is saved in " << creatorProps->fileName << " as:\n";

  std::ifstream dataFile(creatorProps->fileName, std::ios::binary);
  outputStreamToStream(dataFile, std::cout);
  dataFile.close();

  std::cout << "\n";

  HANDLE reporterThread;
  DWORD reporterThreadID;
  reporter::IReporterProps* reporterProps = new reporter::IReporterProps();

  strcpy_s(reporterProps->binaryName, creatorProps->fileName);

  std::cout << "Enter report file name: ";
  std::cin >> reporterProps->fileName;

  std::cout << "Enter wage: ";
  std::cin >> reporterProps->wage;

  std::cout << "\n";
  reporterThread = CreateThread(NULL, 0, reporter::Reporter,
                                (void*)reporterProps, 0, &reporterThreadID);
  if (!reporterThread) {
    return GetLastError();
  }

  WaitForSingleObject(reporterThread, INFINITE);
  CloseHandle(reporterThread);

  std::cout << "Your report is saved in " << reporterProps->fileName
            << " as:\n";

  std::ifstream reportFile(reporterProps->fileName, std::ios::binary);
  outputStreamToStream(reportFile, std::cout);
  reportFile.close();

  std::cout << "\n";

  std::cout << "PROCESS CREATION FINISHED\n";

  return 0;
}

namespace {
void outputStreamToStream(std::istream& in, std::ostream& out) {
  const int bufferSize = 255;
  char buffer[bufferSize];
  while (in.getline(buffer, bufferSize)) {
    out << buffer << "\n";
  }
}
}  // namespace