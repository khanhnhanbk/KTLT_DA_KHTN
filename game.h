#include "consoleM.h"
//Hàm khởi tạo dữ liệu mặc định ban đầu
#define MAX_CAR 17
#define MAX_CAR_LENGTH 40
#define MAX_SPEED 3
//Biến toàn cục
POINT **X;                        //Mảng chứa MAX_CAR xe
POINT Y;                          // Đại diện người qua đường
int cnt = 0;                      //Biến hỗ trợ trong quá trình tăng tốc độ xe di chuyển
int MOVING;                       //Biến xác định hướng di chuyển của người
int SPEED;                        // Tốc độ xe chạy (xem như level)
int HEIGH_CONSOLE = 20, WIDTH_CONSOLE = 100; // Độ rộng và độ cao của màn hình console
bool STATE;

void ResetData()
{
    MOVING = 'D'; // Ban đầu cho người di chuyển sang phải
    SPEED = 1;    // Tốc độ lúc đầu
    Y = {18, 19}; // Vị trí lúc đầu của người
    // Tạo mảng xe chạy
    if (X == NULL)
    {
        X = new POINT *[MAX_CAR];
        for (int i = 0; i < MAX_CAR; i++)
            X[i] = new POINT[MAX_CAR_LENGTH];
        for (int i = 0; i < MAX_CAR; i++)
        {
            int temp = (rand() % (WIDTH_CONSOLE - MAX_CAR_LENGTH)) + 1;
            for (int j = 0; j < MAX_CAR_LENGTH; j++)
            {
                X[i][j].x = temp + j;
                X[i][j].y = 2 + i;
            }
        }
    }
}

void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0)
{
    GotoXY(x, y);
    cout << 'X';
    for (int i = 1; i < width; i++)
        cout << 'X';
    cout << 'X';
    GotoXY(x, height + y);
    cout << 'X';
    for (int i = 1; i < width; i++)
        cout << 'X';
    cout << 'X';
    for (int i = y + 1; i < height + y; i++)
    {
        GotoXY(x, i);
        cout << 'X';
        GotoXY(x + width, i);
        cout << 'X';
    }
    GotoXY(curPosX, curPosY);
}

void StartGame()
{
    system("cls");
    ResetData();                                   // Khởi tạo dữ liệu gốc
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Vẽ màn hình game
    STATE = true;                                  //Bắt đầu cho Thread chạy
}
//Hàm dọn dẹp tài nguyên
void GabageCollect()
{
    for (int i = 0; i < MAX_CAR; i++)
    {
        delete[] X[i];
    }
    delete[] X;
}
//Hàm thoát game
void ExitGame(HANDLE t)
{
    system("cls");
    // TerminateThread(t, 0);
    GabageCollect();
}
//Hàm dừng game
void PauseGame(HANDLE t)
{
    SuspendThread(t);
}
//Hàm xử lý khi người đụng xe
void ProcessDead()
{
    STATE = 0;
// Ve ra chu SOS
    
    GotoXY(0, HEIGH_CONSOLE + 2);
    printf("Dead, type y to continue or anykey to exit");
}
//Hàm xử lý khi người băng qua đường thành công
void ProcessFinish(POINT &p)
{
    SPEED == MAX_SPEED ? SPEED = 1 : SPEED++;
    p = {18, 19}; // Vị trí lúc đầu của người
    MOVING = 'D'; // Ban đầu cho người di chuyển sang phải
}
//Hàm vẽ các toa xe
void DrawCars(char *s)
{
    for (int i = 0; i < MAX_CAR; i++)
    {
        for (int j = 0; j < MAX_CAR_LENGTH; j++)
        {
            GotoXY(X[i][j].x, X[i][j].y);
            printf(".");
        }
    }
}
//Hàm vẽ người qua đường
void DrawSticker(const POINT &p, char *s)
{
    GotoXY(p.x, p.y);
    printf(s);
}

bool IsImpact(const POINT &p)
{
    if (p.y == 1 || p.y == 19)
        return false;
    for (int i = 0; i < MAX_CAR_LENGTH; i++)
    {
        if (p.x == X[p.y - 2][i].x && p.y == X[p.y - 2][i].y)
            return true;
    }
    return false;
}

void MoveCars()
{
    for (int i = 1; i < MAX_CAR; i += 2)
    {
        cnt = 0;
        do
        {
            cnt++;
            for (int j = 0; j < MAX_CAR_LENGTH - 1; j++)
            {
                X[i][j] = X[i][j + 1];
            }
            X[i][MAX_CAR_LENGTH - 1].x + 1 == WIDTH_CONSOLE ? X[i][MAX_CAR_LENGTH -
                                                                   1]
                                                                  .x = 1
                                                            : X[i][MAX_CAR_LENGTH - 1].x++; // Kiểm tra xem xe có đụng màn hình
        } while (cnt < SPEED);
    }
    for (int i = 0; i < MAX_CAR; i += 2)
    {
        cnt = 0;
        do
        {
            cnt++;
            for (int j = MAX_CAR_LENGTH - 1; j > 0; j--)
            {
                X[i][j] = X[i][j - 1];
            }
            X[i][0].x - 1 == 0 ? X[i][0].x = WIDTH_CONSOLE - 1 : X[i][0].x--; // Kiểm
        } while (cnt < SPEED);
    }
}
void EraseCars()
{
    for (int i = 0; i < MAX_CAR; i += 2)
    {
        cnt = 0;
        do
        {
            GotoXY(X[i][MAX_CAR_LENGTH - 1 - cnt].x, X[i][MAX_CAR_LENGTH - 1 - cnt].y);
            printf(" ");
            cnt++;
        } while (cnt < SPEED);
    }
    for (int i = 1; i < MAX_CAR; i += 2)
    {
        cnt = 0;
        do
        {
            GotoXY(X[i][0 + cnt].x, X[i][0 + cnt].y);
            printf(" ");
            cnt++;
        } while (cnt < SPEED);
    }
}

void MoveRight()
{
    if (Y.x < WIDTH_CONSOLE - 1)
    {
        DrawSticker(Y, " ");
        Y.x++;
        DrawSticker(Y, "Y");
    }
}
void MoveLeft()
{
    if (Y.x > 1)
    {
        DrawSticker(Y, " ");
        Y.x--;
        DrawSticker(Y, "Y");
    }
}
void MoveDown()
{
    if (Y.y < HEIGH_CONSOLE - 1)
    {
        DrawSticker(Y, " ");
        Y.y++;
        DrawSticker(Y, "Y");
    }
}
void MoveUp()
{
    if (Y.y > 1)
    {
        DrawSticker(Y, " ");
        Y.y--;
        DrawSticker(Y, "Y");
    }
}
void SubThread()
{
    while (1)
    {
        if (STATE) //Nếu người vẫn còn sống
        {
            switch (MOVING) //Kiểm tra biến moving
            {
            case 'A':
                MoveLeft();
                break;
            case 'D':
                MoveRight();
                break;
            case 'W':
                MoveUp();
                break;
            case 'S':
                MoveDown();
                break;
            }
            MOVING = ' '; // Tạm khóa không cho di chuyển, chờ nhận phím từ hàm main
            EraseCars();
            MoveCars();
            DrawCars(".");
            if (IsImpact(Y))
            {
                ProcessDead(); // Kiểm tra xe có đụng không
            }
            if (Y.y == 1)
                ProcessFinish(Y); // Kiểm tra xem về đích chưa
            Sleep(50);            //Hàm ngủ theo tốc độ SPEED
        }
    }
}