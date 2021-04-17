#pragma once
#include "game.h"
#include "consoleM.h"
#include <fstream>
//Hằng số
void saveFile()
{
    system("cls");
    flag = false;
    string fileName{""};
    system("cls");
    cout << "Nhap ten file: ";

    getline(cin, fileName);
    fileName = "./GameSaved/" + fileName; // luu gan vao folder GameSaaved
    ofstream ifs{fileName};
    if (ifs.is_open())
    {
        ifs << Y.x << " " << Y.y << '\n'; //Toa do cua Y
        ifs << SPEED << '\n';             // Speed
        // moi xe chi can luu toa do dau tien
        for (int i = 0; i < MAX_CAR; i++)
        {
            ifs << X[i][0].x << " " << X[i][0].y << "\n";
        }
        // luu mang PreY
        ifs << countY << "\n";
        for (int i = 0; i < countY; i++)
        {
            ifs << preY[i] << " ";
        }

        ifs.close();
    }
    cout << "Da luu vao file.\n";
    system("pause");
    system("cls");
    DrawBoard(posBoard.x, posBoard.y, WIDTH_CONSOLE, HEIGH_CONSOLE);
    for (int i = 0; i < countY; i++)
    {
        DrawSticker({preY[i], posBoard.y + 1}, "Y");
    }
    DrawSticker(Y, "Y");
    flag = true;
}

void loadFile()
{
    system("cls");
    flag = false;
    string fileName{""};
    system("cls");
    cout << "Nhap ten file da luu: ";

    getline(cin, fileName);
    fileName = "./GameSaved/" + fileName; // luu gan vao folder GameSaaved
    ifstream ifs{fileName};
    if (ifs.is_open())
    {
        ifs >> Y.x >> Y.y; //Toa do cua Y
        ifs >> SPEED;      // Speed
        if (X == NULL)
        {
            X = new POINT *[MAX_CAR];
            for (int i = 0; i < MAX_CAR; i++)
                X[i] = new POINT[MAX_CAR_LENGTH];
        }
        for (int i = 0; i < MAX_CAR; i++)
        {
            ifs >> X[i][0].x >> X[i][0].y;
            for (int j = 1; j < MAX_CAR_LENGTH; j++)
            {
                X[i][j].x = X[i][0].x + j;
                if (X[i][j].x >= posBoard.x + WIDTH_CONSOLE)
                {
                    /* code */
                    X[i][j].x = 1 + X[i][j].x - WIDTH_CONSOLE;
                }

                X[i][j].y = X[i][0].y;
            }
        }
        // luu mang PreY
        ifs >> countY;
        if (preY == NULL)
        {
            preY = new long[WIDTH_CONSOLE];
        }
        for (int i = 0; i < countY; i++)
        {
            ifs >> preY[i];
        }

        ifs.close();
    }
    cout << "Da load vao file.\n";
    system("pause");
    system("cls");
    DrawBoard(posBoard.x, posBoard.y, WIDTH_CONSOLE, HEIGH_CONSOLE);
    // ve Y da ve dich
    DrawSticker({Y.x, Y.y}, "Y");
    for (int j = 0; j < countY; j++)
    {
        DrawSticker({preY[j], posBoard.y + 1}, "Y");
    }
    STATE = true;
    flag = true;
}
