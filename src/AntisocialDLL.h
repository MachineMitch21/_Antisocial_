
#ifndef ANTISOCIAL_H
#define ANTISOCIAL_H

#ifdef __WIN32__
#include <Windows.h>
#include <iostream>
#include <fstream>
BOOL APIENTRY DLLMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  switch(ul_reason_for_call)
  {
    case DLL_PROCESS_ATTACH:
      std::ofstream logFile("antisocialLog.txt");
      if(logFile.is_open()){
        logFile << "a process has attatched to antisocialDLL!\n";
      }
      logFile.close();
    break;
    case DLL_THREAD_ATTACH:

    break;
    case DLL_THREAD_DETACH:

    break;
    case DLL_PROCESS_DETACH:
    break;
  }
  return true;
}

#ifdef ANTISOCIAL_EXPORT
#define ANTISOCIAL_API __declspec(dllexport)
#else
#define ANTISOCIAL_API __declspec(dllimport)
#endif // ANTISOCIAL_EXPORT
#endif // __WIN32__

#ifdef __LINUX__
#define ANTISOCIAL_API
#endif // __LINUX__

#endif // ANTISOCIAL_H
