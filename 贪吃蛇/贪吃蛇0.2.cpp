#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
#define map Map
bool b;
char map[24][24], k1, k;
int hx, hy, tx, ty, direction, score, Sleeptime = 25;

COORD coord = { 0, 0 };
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void HideCursor() {		//隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void MakeFood() {
	srand(time(0));
	int x, y;
	do {
		x = rand() % 24;
		y = rand() % 24;
	} while (map[x][y] != ' ');
	map[x][y] = '*';
}

void Init() {
	HideCursor();
	hx = tx = 3, hy = 10, ty = 6, b = 0, direction = 4, k1 = k = 77,
		score = 0;
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 24; j++)
			map[i][j] = ' ';
	for (int i = ty; i <= hy; i++)
		map[3][i] = '@';
	MakeFood();
}

void print() {
	for (int i = 1; i <= 25; i++)
		printf(" -");
	printf("\t贪吃蛇游戏\n");
	for (int i = 0; i < 24; i++) {
		printf(" |");
		for (int j = 0; j < 24; j++) {
			printf("%c ", map[i][j]);
		}
		if (i == 1)
			printf("|\t按 w   或 %c  移动\n", 24);
		else if (i == 2)
			printf("|\t s a d  %c %c %c\n", 27, 25, 26);
		else if (i == 3)
			printf("|\t按空格键暂停\n");
		else if (i == 5)
			printf("|\t分数：%d\t\n", score);
		else
			printf("|\n");
	}
	for (int i = 1; i <= 25; i++)
		printf(" -");
	SetConsoleCursorPosition(hOutput, coord);		//清屏
	for (int i = 1; i <= Sleeptime; i++) {		//延迟
		if (_kbhit())
			break;
		Sleep(1);
	}
}

void GameOver() {
	if (MessageBox(NULL, "你失败了！\n再来一遍？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
		Init(), b = 1;
	else
		exit(0);
}

void tail_move(int t) {
	switch (t) {
	case 1:
		tx--;
		if (tx == -1)
			tx = 23;
		break;
	case 2:
		tx++;
		if (tx == 24)
			tx = 0;
		break;
	case 3:
		ty--;
		if (ty == -1)
			ty = 23;
		break;
	case 4:
		ty++;
		if (ty == 24)
			ty = 0;
		break;
	}
}

void work(char k) {
	while (!_kbhit()) {
		if (map[tx][ty] >= '1' && map[tx][ty] <= '4')
			direction = map[tx][ty] - 48;
		map[tx][ty] = ' ';
		tail_move(direction);
		switch (k) {
		case 72:
			hx--;
			if (hx == -1)
				hx = 23;
			break;
		case 80:
			hx++;
			if (hx == 24)
				hx = 0;
			break;
		case 75:
			hy--;
			if (hy == -1)
				hy = 23;
			break;
		case 77:
			hy++;
			if (hy == 24)
				hy = 0;
			break;
		}
		if (map[hx][hy] == '@' || (map[hx][hy] >= '1' && map[hx][hy] <= '4')) {
			GameOver();
			break;
		}
		if (map[hx][hy] == '*') {
			map[hx][hy] = '@';
			score++;
			if (direction == 1 || direction == 3)
				tail_move(direction + 1);
			else
				tail_move(direction - 1);
			MakeFood();
		}
		map[hx][hy] = '@';
		print();
	}
}

void move() {
	switch (k) {
	case 32:		//暂停
		k = k1, b = 1;
		_getch();
		break;
	case 'w':
	case 72:		//上
		if (k1 == 80) {
			k = 80, b = 1;
			break;
		}
		else if (k1 != 72)
			map[hx][hy] = '1';
		k1 = 72;
		work(72);
		break;
	case 's':
	case 80:		//下
		if (k1 == 72) {
			k = 72, b = 1;
			break;
		}
		else if (k1 != 80)
			map[hx][hy] = '2';
		k1 = 80;
		work(80);
		break;
	case 'a':
	case 75:		//左
		if (k1 == 77) {
			k = 77, b = 1;
			break;
		}
		else if (k1 != 75)
			map[hx][hy] = '3';
		k1 = 75;
		work(75);
		break;
	case 'd':
	case 77:		//右
		if (k1 == 75) {
			k = 75, b = 1;
			break;
		}
		else if (k1 != 77)
			map[hx][hy] = '4';
		k1 = 77;
		work(77);
		break;
	default:
		k = k1, b = 1;
	}
}

int main() {
	system("mode con cols=81 lines=27");
	Init();
	while (1) {
		b = 0;
		move();
		if (!b)
			k = _getch();
	}
}
/*
功能是完善了，但代码有些长
2021-01-25 11:12
简化代码，252行到221行
修复食物生成的问题
2021.1.29 11.21
*/