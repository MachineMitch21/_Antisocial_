#include "AntisocialDLL.h"

#ifdef __WIN32__
    BOOL APIENTRY DLLMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
    {
        std::ofstream logFile("antisocialLog.txt");

        switch(ul_reason_for_call)
        {
            case DLL_PROCESS_ATTACH:
                  if (logFile.is_open())
                  {
                      logFile << "a process has attatched to antisocialDLL!\n";
                  }

            break;
            case DLL_THREAD_ATTACH:

            break;
            case DLL_THREAD_DETACH:

            break;
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
