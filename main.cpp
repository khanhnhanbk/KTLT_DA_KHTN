#include "consoleM.h"
#include "game.h"
//Hằng số

int main()
{
    int temp;
    FixConsoleWindow();
    ShowConsoleCursor(false);
    srand(time(NULL));
    StartGame();
    thread t1(SubThread);
    while (1)
    {
        // if (_kbhit())
            temp = toupper(getch());
        if (STATE == 1)
        {
            if (temp == 27)
            {
                ExitGame((HANDLE)t1.native_handle());
                return 0;
            }
            else if (temp == 'P')
            {
                PauseGame((HANDLE)t1.native_handle());
            }
            else
            {
                ResumeThread((HANDLE)t1.native_handle());
                if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S')
                {
                    MOVING = temp;
                }
            }
        }
        else
        {
            if (temp == 'Y')
                StartGame();
            else
            {
                ExitGame((HANDLE)t1.native_handle());
                return 0;
            }
        }
    }
    return 0;
}