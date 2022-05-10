#pragma once
#pragma once
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<conio.h>
using namespace std;

//Đầu tiên là các hàm đồ họa sẽ sử dụng trong chương trình

//Chỉnh sửa tên cửa sổ Console
BOOL WINAPI SetConsoleTitle(
	_In_ LPCTSTR lpConsoleTitle
);

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}


//Tô màu chữ
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

//Setup khung câu hỏi
void KhungCauHoi() {
	gotoxy(19, 7); cout << char(201); //góc
	for (int i = 0; i < 76; i++)
		cout << char(205);

	cout << char(187);//góc
	gotoxy(19, 8); cout << char(186);
	gotoxy(96, 8); cout << char(186);
	gotoxy(19, 9); cout << char(186);
	gotoxy(96, 9); cout << char(186);
	gotoxy(96, 10); cout << char(186);
	gotoxy(19, 10); cout << char(186);
	gotoxy(19, 11); cout << char(200);//góc
	for (int i = 0; i < 76; i++) {
		cout << char(205);
	}
	cout << char(188);//góc
}

//Setup khung trả lời
void KhungTraLoi(int x, int y) {
	gotoxy(x, y); cout << char(201); //góc
	for (int i = 0; i < 29; i++)
		cout << char(205);

	cout << char(187);//góc
	gotoxy(x, y + 1); cout << char(186);
	gotoxy(x + 30, y + 1); cout << char(186);
	gotoxy(x, y + 2); cout << char(186);
	gotoxy(x + 30, y + 2); cout << char(186);
	gotoxy(x, y + 3); cout << char(186);
	gotoxy(x + 30, y + 3); cout << char(186);
	gotoxy(x, y + 4); cout << char(200);
	gotoxy(x + 30, y + 4); cout << char(200);
	gotoxy(x + 1, y + 4);
	for (int i = 0; i < 29; i++)
		cout << char(205);

	cout << char(188);//góc
}
