#include "AntisocialDLL.h"

#ifdef __WIN32__
// Specifying an entry point for DLL
    BOOL APIENTRY DLLMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
    {
        //Setting up a log file to write errors or updates to
        std::ofstream logFile("antisocialLog.txt");

        switch(ul_reason_for_call)
        {
            //Run when process attaches to the DLL
            case DLL_PROCESS_ATTACH:
                  if (logFile.is_open())
                  {
                      logFile << "a process has attatched to antisocialDLL!\n";
                  }

            break;
            //Run when a thread attaches to the DLL
            case DLL_THREAD_ATTACH:

            break;
            //Run when a thread detaches from the DLL
            case DLL_THREAD_DETACH:

            break;
            //Run when a process detaches from a DLL
            case DLL_PROCESS_DETACH:
            break;
            default:
                if(logFile.is_open())
                {
                    logFile << "DLLMain for antisocail was reached, but process was not attatched\n";
                }
         }
         
         logFile.close();
         return true;
    }
#endif // __WIN32__
