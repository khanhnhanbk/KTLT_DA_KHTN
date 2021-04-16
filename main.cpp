#include "game.h"
#include "consoleM.h"
#include "saveLoadGame.h"

bool proceedMainScreen()
{
    system("cls");
    cout << "Xin chao ban den vao chung toi\n"
         << "Nhan T de tai lai \n";
    int temp;
    temp = toupper(getch());
    if (temp == 'T')
        loadFile();
    return temp == 'T';
}
int main()
{
    int temp;
    system("color 0A");
    FixConsoleWindow();
    ShowConsoleCursor(false);
    srand(time(NULL));
    if (!proceedMainScreen()) // xu ly man hinh chinh
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
            else if (temp == 'T')
            {
                loadFile();
            }
            else if (temp == 'L')
            {
                PauseGame((HANDLE)t1.native_handle());
                saveFile();
            }
            else if (flag)
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