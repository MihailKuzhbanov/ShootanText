// DelegateCPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>


using namespace std;

const int x = 25;
const int y = 10;
const int renderTime = 100;
const int range = 5;
const int chns = 30;

const char basic = '_';
const char control = 'P';
const char action = '-';
const char hit = '#';
const char target = 'E';
const char item = 'a';
const char pick = '!';

int enemies = 0;
int ammo = 0;
int health = 0;

void Show(char **a)
{
	
	system("cls");
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			//cout << a[j][i];
			if (a[j][i] == basic)
			{
				cout << a[j][i];
			}
			else
			{
				int color = 0;
				switch (a[j][i])
				{
				case control: color = 10;	break;
				case action: color = 14; break;
				case hit: color = 12; break;
				case target: color = 11; break;
				case item: color = 9; break;
				case pick: color = 13; break;
					/*	0   BLACK, 1   BLUE, 2   GREEN, 3   CYAN, 4   RED, 5   MAGENTA, 6   BROWN, 7   LIGHTGRAY,
					8   DARKGRAY, 9   LIGHTBLUE, 10  LIGHTGREEN, 11  LIGHTCYAN, 12  LIGHTRED, 13  LIGHTMAGENTA, 14  YELLOW, 15  WHITE	*/
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
				cout << a[j][i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			}
			
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << endl << "E: " << enemies;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "\ta: " << ammo;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << "\t+: " << health;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	//Sleep(renderTime);
}



void FillZero(char **a)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			a[j][i] = basic;
		}
	}
}

char** Create(int rows, int cols)
{
	char** array = new char*[rows];
	for (int row = 0; row < rows; row++)
	{
		array[row] = new char[cols];
	}
	FillZero(array);
	return array;
}

void Pick(char **a, int nowX, int nowY)
{
	if (nowX+1 < x)	a[nowX + 1][nowY] = pick;
	if (nowX-1 >=0) a[nowX - 1][nowY] = pick;
	Show(a);
	if (nowX+1 < x) a[nowX + 1][nowY] = basic;
	if (nowX-1 >=0) a[nowX - 1][nowY] = basic;
	ammo++;
}

bool Chance(int a)
{
	return (rand() % a > rand() % 100);
}

int MoveRight(char **a, int nowX, int nowY)
{

	if (nowX < x-1 && (a[nowX+1][nowY] != target))
	{
		if (a[nowX+1][nowY] == item)
		{
			Pick(a, nowX, nowY);
		}
		a[nowX][nowY] = basic;
		nowX++;
		a[nowX][nowY] = control;
		Show(a);
	}
	else health--;
	return nowX;
}



int MoveLeft(char **a, int nowX, int nowY)
{
	if (nowX > 0 && (a[nowX-1][nowY] != target))
	{
		if (a[nowX-1][nowY] == item)
		{
			Pick(a, nowX, nowY);
		}
	a[nowX][nowY] = basic;
	nowX--;
	a[nowX][nowY] = control;
	Show(a);
	}
	else health--;
	return nowX;
}

int MoveUp(char **a, int nowX, int nowY)
{

	if (nowY > 0 && (a[nowX][nowY-1] != target))
	{
		if (a[nowX][nowY - 1] == item)
		{
			Pick(a, nowX, nowY);
		}
		a[nowX][nowY] = basic;
		nowY--;
		a[nowX][nowY] = control;
		Show(a);
	}
	else health--;
	return nowY;
}

int MoveDown(char **a, int nowX, int nowY)
{
	if (nowY < y-1 && (a[nowX][nowY+1] != target))
	{
		if (a[nowX][nowY + 1] == item)
		{
			Pick(a, nowX, nowY);
		}
		a[nowX][nowY] = basic;
		nowY++;
		a[nowX][nowY] = control;
		Show(a);
	}
	else health--;
	return nowY;
}

void FireRight(char **a, int nowX, int nowY)
{
	if (ammo > 0)
	{
		for (int i = 1; i < range; i++)
		{
			if (nowX + i < x)
			{
				if (a[nowX + i][nowY] == target)
				{
					a[nowX + i][nowY] = hit;
					Show(a);
					if (Chance(10*chns)) a[nowX + i][nowY] = item;
					else a[nowX + i][nowY] = basic;
					enemies--;
				}
				else
				{
					a[nowX + i][nowY] = action;
					Show(a);
					a[nowX + i][nowY] = basic;
				}
			}
		}
		ammo--;
	}
	
	Show(a);
}



void FireLeft(char **a, int nowX, int nowY)
{
	if (ammo > 0)
	{
		for (int i = 1; i < range; i++)
		{
			if (nowX - i >= 0)
			{
				if (a[nowX - i][nowY] == target)
				{
					a[nowX - i][nowY] = hit;
					Show(a);
					if (Chance(10*chns)) a[nowX - i][nowY] = item;
					else a[nowX - i][nowY] = basic;
					enemies--;
				}
				else
				{
					a[nowX - i][nowY] = action;
					Show(a);
					a[nowX - i][nowY] = basic;
				}
			}
		}
		ammo--;
	}
	Show(a);

}

int CreateEnemy(char **a)
{
	int count = 0;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (Chance(chns))
			{
				a[j][i] = target;
				count++;
			}
		}
	}
	return count;
}

int main()
{
	int nowX = rand()%x+1;
	int nowY = rand()%y+1;
	char** field = Create(x, y);
	srand(time(0));
	enemies = CreateEnemy(field);
	health = 6;
	ammo = enemies/y;
	field[nowX][nowY] = control;
	Show(field);
	
	while (health > 0 && enemies > 0)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'd': nowX = MoveRight(field, nowX, nowY); break;
			case 'a': nowX = MoveLeft(field, nowX, nowY); break;
			case 'w': nowY = MoveUp(field, nowX, nowY); break;
			case 's': nowY = MoveDown(field, nowX, nowY); break;
			case 'e': FireRight(field, nowX, nowY); break;
			case 'q': FireLeft(field, nowX, nowY); break;
			}
			
		}
	}
	delete field;
	if (!health)
	{
		system("cls");
		cout << "Y O U   L O S E" << endl;
	}
	else
	{
		system("cls");
		cout << "Y O U   W I N" << endl;
	}
	Sleep(5000);
	main();
	system("pause");
}
