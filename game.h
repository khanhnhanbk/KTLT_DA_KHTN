#pragma once
#include <string>
#include "consoleM.h"
//Hàm khởi tạo dữ liệu mặc định ban đầu
#define MAX_CAR 17        //
#define MAX_CAR_LENGTH 10 //
#define MAX_SPEED 3       //
#define thoiGianDung 50   // moi xe dung 10 nhip
//Biến toàn cục
POINT **X;                                   //Mảng chứa MAX_CAR xe
POINT Y;                                     // Đại diện người qua đường
POINT posBoard = {5, 3};                     //
int cnt = 0;                                 //Biến hỗ trợ trong quá trình tăng tốc độ xe di chuyển
int MOVING;                                  //Biến xác định hướng di chuyển của người
int SPEED;                                   // Tốc độ xe chạy (xem như level)
int HEIGH_CONSOLE = 20, WIDTH_CONSOLE = 100; // Độ rộng và độ cao của màn hình console
bool STATE;                                  //
long *preY;                                  //
int countY;                                  //
bool flag{true};                             //
int dungXe{0};                               // thuc hien dung xe neu so xe dong du voi so dung Xe theo mod7
int tinhThoiGianDung{0};                     // so lan cap nhap thoi gian dung
long unit = 1;                                // de lam ham chay nguoc

void ResetData()
{
    MOVING = 'D'; // Ban đầu cho người di chuyển sang phải
    SPEED = 1;    // Tốc độ lúc đầu
    int pos = rand() % (WIDTH_CONSOLE - 1) + 1 + posBoard.x;
    Y = {pos, posBoard.y + HEIGH_CONSOLE - 1}; // Vị trí lúc đầu của người
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
                X[i][j].x = posBoard.x + temp;
                X[i][j].y = posBoard.y + 2 + i;
            }
        }
    }
    if (preY == NULL)
    {
        preY = new long[WIDTH_CONSOLE];
    }
    for (int i = 0; i < WIDTH_CONSOLE; i++)
    {
        preY[i] = -1;
    }
    countY = 0;
}

void DrawBoard(long x, long y, int width, int height, int curPosX = 0, int curPosY = 0)
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
    ResetData();                                                     // Khởi tạo dữ liệu gốc
    DrawBoard(posBoard.x, posBoard.y, WIDTH_CONSOLE, HEIGH_CONSOLE); // Vẽ màn hình game
    STATE = true;                                                    //Bắt đầu cho Thread chạy
}
//Hàm dọn dẹp tài nguyên
void GabageCollect()
{
    for (int i = 0; i < MAX_CAR; i++)
    {
        delete[] X[i];
    }
    delete[] X;
    delete[] preY;
}
//Hàm thoát game
//Hàm dừng game
void PauseGame(HANDLE t)
{
    flag = !flag;
    SuspendThread(t);
    Sleep(100);
    GotoXY(0, posBoard.y + HEIGH_CONSOLE + 2);
    if (!flag)
        cout << "\tDa dung game! \n"
             << "\tNhan \"P\" lan nua de tiep tuc.\n"
             << "\tNhan \"T\" de tai lai game da luu. \n"
             << "\tNhan \"L\" de luu game.";
    else
        cout << "                                              \n"
             << "                                              \n"
             << "                                              \n"
             << "                                              \n";
}
void ExitGame(HANDLE t)
{
    system("cls");
    // TerminateThread(t, 0);
    PauseGame(t);
    GabageCollect();
}
//Hàm xử lý khi người đụng xe
void ProcessDead()
{
    STATE = 0;
    // Ve ra chu SOS
    system("cls");
    GotoXY(20, 18);
    printf("Dead, type y to continue or anykey to exit");
    GotoXY(0, 5);
    Sleep(100);
    cout << "\t\t**********      ***********      ***********" << '\n';
    Sleep(100);
    cout << "\t\t**********      ***********      ***********" << '\n';
    Sleep(100);
    cout << "\t\t***             **       **      ***        " << '\n';
    Sleep(100);
    cout << "\t\t***             **       **      ***        " << '\n';
    Sleep(100);
    cout << "\t\t**********      **       **      ***********" << '\n';
    Sleep(100);
    cout << "\t\t**********      **       **      ***********" << '\n';
    Sleep(100);
    cout << "\t\t       ***      **       **              ***" << '\n';
    Sleep(100);
    cout << "\t\t       ***      **       **              ***" << '\n';
    Sleep(100);
    cout << "\t\t**********      ***********      ***********" << '\n';
    Sleep(100);
    cout << "\t\t**********      ***********      ***********" << '\n';
}
//Hàm xử lý khi người băng qua đường thành công
void ProcessFinish(POINT &p)
{
    SPEED == MAX_SPEED ? SPEED = 1 : SPEED++;
    preY[countY] = p.x;
    countY++;
    int pos = rand() % (WIDTH_CONSOLE - 1) + 1 + posBoard.x;
    p = {pos, posBoard.y + HEIGH_CONSOLE - 1}; // Vị trí lúc đầu của người
    MOVING = 'D';                              // Ban đầu cho người di chuyển sang phải
}
//Hàm vẽ các toa xe
void DrawCars(const string s)
{
    string y = "+";
    for (int i = 0; i < MAX_CAR; i++)
    {
        for (int j = 0; j < MAX_CAR_LENGTH; j++)
        {
            GotoXY(X[i][j].x, X[i][j].y);
            if ((dungXe - i) % 7 == 0)
                cout << y;
            else
                cout << s;
        }
    }
}
//Hàm vẽ người qua đường
void DrawSticker(const POINT &p, const string s)
{
    GotoXY(p.x, p.y);
    cout << s;
}

bool IsImpact(const POINT &p)
{
    if (p.y == posBoard.y + 1)
    {
        for (int i = 0; i < countY; i++)
        {
            if (p.x == preY[i])
                return true;
        }
    }
    if (p.y == posBoard.y + 1 || p.y == posBoard.y + HEIGH_CONSOLE - 1)
        return false;
    for (int i = 0; i < MAX_CAR_LENGTH; i++)
    {
        if (p.x == X[p.y - 2 - posBoard.y][i].x && p.y == X[p.y - 2 - posBoard.y][i].y)
            return true;
    }
    return false;
}

bool IsYPassed(const POINT &p)
{
    return p.y == posBoard.y + 1;
}
void MoveCars()
{
    if (tinhThoiGianDung == thoiGianDung)
    {
        dungXe = rand();
        tinhThoiGianDung = 0;
    }
    for (int i = MAX_CAR / 2; i < MAX_CAR; i++)
    {
        if ((dungXe - i) % 7 == 0)
        {
            continue;
        }
        cnt = 0;
        do
        {
            cnt++;
            for (int j = 0; j < MAX_CAR_LENGTH - 1; j++)
            {
                X[i][j] = X[i][j + 1];
            }
            if (X[i][MAX_CAR_LENGTH - 1].x + 1 == posBoard.x + WIDTH_CONSOLE)
                X[i][MAX_CAR_LENGTH - 1].x = posBoard.x + 1;
            else
                X[i][MAX_CAR_LENGTH - 1].x++; // Kiểm tra xem xe có đụng màn hình
        } while (cnt < SPEED);
    }
    for (int i = 0; i < MAX_CAR / 2; i++)
    {
        if ((dungXe - i) % 7 == 0)
        {
            continue;
        }
        cnt = 0;
        do
        {
            cnt++;
            for (int j = MAX_CAR_LENGTH - 1; j > 0; j--)
            {
                X[i][j] = X[i][j - 1];
            }
            if (X[i][0].x - 1 == posBoard.x)
                X[i][0].x = posBoard.x + WIDTH_CONSOLE - 1;
            else
                X[i][0].x--; // Kiểm tra xe co dung thanh hay khong
        } while (cnt < SPEED);
    }
}
void EraseCars()
{
    for (int i = 0; i < MAX_CAR / 2; i++)
    {
        cnt = 0;
        do
        {
            GotoXY(X[i][MAX_CAR_LENGTH - 1 - cnt].x, X[i][MAX_CAR_LENGTH - 1 - cnt].y);
            printf(" ");
            cnt++;
        } while (cnt < SPEED);
    }
    for (int i = MAX_CAR / 2; i < MAX_CAR; i++)
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
    if (Y.x + unit <= posBoard.x + WIDTH_CONSOLE - 1 &&
        Y.x + unit >= 1 + posBoard.x)
    {
        DrawSticker(Y, " ");
        Y.x += unit;
        DrawSticker(Y, "Y");
    }
}
void MoveLeft()
{
    if (Y.x - unit <= posBoard.x + WIDTH_CONSOLE - 1 &&
        Y.x - unit >= 1 + posBoard.x)
    {
        DrawSticker(Y, " ");
        Y.x -= unit;
        DrawSticker(Y, "Y");
    }
}
void MoveDown()
{
    if (Y.y + unit <= HEIGH_CONSOLE - 1 + posBoard.y &&
        Y.y + unit >= 1 + posBoard.y)
    {
        DrawSticker(Y, " ");
        Y.y += unit;
        DrawSticker(Y, "Y");
    }
}
void MoveUp()
{
    if (Y.y - unit <= HEIGH_CONSOLE - 1 + posBoard.y &&
        Y.y - unit >= 1 + posBoard.y)
    {
        DrawSticker(Y, " ");
        Y.y -= unit;
        DrawSticker(Y, "Y");
    }
}
void SubThread()
{
    while (1)
    {
        if (flag)
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
                DrawCars("-");
                if (IsImpact(Y))
                {
                    ProcessDead(); // Kiểm tra xe có đụng không
                }
                if (IsYPassed(Y))
                    ProcessFinish(Y); // Kiểm tra xem về đích chưa
                tinhThoiGianDung++;   // dem so vong lap
                Sleep(50);            //Hàm ngủ theo tốc độ SPEED
            }
        }
    }
}