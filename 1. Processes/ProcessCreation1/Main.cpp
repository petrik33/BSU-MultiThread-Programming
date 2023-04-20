#include <Windows.h>

#include <fstream>
#include <iostream>
#include <string>

void outputStreamToStream(std::istream& in, std::ostream& out);
bool ExecuteProcess(std::string& appName, std::string& cmdArgs);
LPWSTR GetWideStringFromString(std::string str);
bool ExecuteCreator(std::string& fileName, int recordsNum);
bool ExecuteReporter(std::string& binaryName, std::string& reportName,
                     double wage);

int main() {
  std::cout << "PROCESS CREATION APP\n\n";

  std::cout << "Enter data file name: ";
  std::string binaryName;
  std::cin >> binaryName;

  std::cout << "Enter number of employees: ";
  int recordsNum;
  std::cin >> recordsNum;

  if (!ExecuteCreator(binaryName, recordsNum)) {
    return 1;
  }

  std::cout << "Enter report file name: ";
  std::string reportName;
  std::cin >> reportName;

  std::cout << "Enter wage: ";
  double wage;
  std::cin >> wage;

  if (!ExecuteReporter(binaryName, reportName, wage)) {
    return 1;
  }

  std::cout << "PROCESS CREATION FINISHED\n";

  return 0;
}

bool ExecuteCreator(std::string& fileName, int recordsNum) {
  std::string creatorPath{"..\\x64\\Debug\\Creator.exe"};
  std::string cmdArgs =
      creatorPath + " \"" + fileName + "\" " + std::to_string(recordsNum);

  std::cout << std::endl;
  if (!ExecuteProcess(creatorPath, cmdArgs)) {
    return false;
  }

  std::cout << "Your data is saved in " << fileName << " as:\n";

  std::ifstream dataFile(fileName, std::ios::binary);
  outputStreamToStream(dataFile, std::cout);
  dataFile.close();

  std::cout << "\n";
  return true;
}

bool ExecuteReporter(std::string& binaryName, std::string& reportName,
                     double wage) {
  std::string reportherPath{"..\\x64\\Debug\\Reporter.exe"};
  std::string cmdArgs = reportherPath + " \"" + binaryName + "\" \"" +
                        reportName + "\" " + std::to_string(wage);

  std::cout << std::endl;
  if (!ExecuteProcess(reportherPath, cmdArgs)) {
    return false;
  }

  std::cout << "Your report is saved in " << reportName << " as:\n";

  std::ifstream reportFile(reportName, std::ios::binary);
  outputStreamToStream(reportFile, std::cout);
  reportFile.close();

  std::cout << "\n";
  return true;
}

bool ExecuteProcess(std::string& appName, std::string& cmdArgs) {
  // Create the process
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  if (!CreateProcess(
          GetWideStringFromString(appName),  // Application name
          GetWideStringFromString(cmdArgs),  // Command line arguments
          NULL,                              // Process attributes
          NULL,                              // Thread attributes
          FALSE,                             // Inherit handles
          0,                                 // Creation flags
          NULL,                              // Environment block
          NULL,                              // Current directory
          &si,                               // Startup info
          &pi                                // Process info
          )) {
    printf("CreateProcess failed (%d).\n", GetLastError());
    return false;
  }

  // Wait for the process to finish
  WaitForSingleObject(pi.hProcess, INFINITE);

  // Get the exit code
  DWORD exitCode;
  if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
    std::cerr << "Failed to get the exit code\n";
    return false;
  }

  // Close the process and thread handles
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  if (exitCode != 0) {
    std::cout << "The process exited with code " << exitCode << '\n';
  }

  return true;
}

void outputStreamToStream(std::istream& in, std::ostream& out) {
  const int bufferSize = 255;
  char buffer[bufferSize];
  while (in.getline(buffer, bufferSize)) {
    out << buffer << "\n";
  }
}

LPWSTR GetWideStringFromString(std::string str) {
  int length = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
  LPWSTR wideStr = new WCHAR[length];
  MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wideStr, length);
  return wideStr;
}