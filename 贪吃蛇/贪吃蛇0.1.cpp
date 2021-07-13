#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
#define map Map
bool b1;
char map[24][24], k1, k;
int hx, hy, tx, ty, direction, score, Sleeptime = 25;

COORD coord = { 0, 0 };
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void HideCursor() {		//���ع��
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
	hx = 3, hy = 10, tx = 3, ty = 6, b1 = 0, direction = 4, k1 = 77, k = 77, score = 0;
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
	printf("\t̰������Ϸ\n");
	for (int i = 0; i < 24; i++) {
		printf(" |");
		for (int j = 0; j < 24; j++) {
			printf("%c ", map[i][j]);
		}
		if (i == 1)
			printf("|\t�� w   �� %c  �ƶ�\n", 24);
		else if (i == 2)
			printf("|\t s a d  %c %c %c\n", 27, 25, 26);
		else if (i == 3)
			printf("|\t���ո����ͣ\n");
		else if (i == 5)
			printf("|\t������%d\t\n", score);
		else
			printf("|\n");
	}
	for (int i = 1; i <= 25; i++)
		printf(" -");
	SetConsoleCursorPosition(hOutput, coord);		//����
	for (int i = 1; i <= Sleeptime; i++) {		//�ӳ�
		if (_kbhit())
			break;
		Sleep(1);
	}
}

void GameOver() {
	if (MessageBox(NULL, "��ʧ���ˣ�\n����һ�飿", "��ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
		Init(), b1 = 1;
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

void turn() {
	if (map[tx][ty] >= '1' && map[tx][ty] <= '4')
		direction = map[tx][ty] - 48;
}

void move() {
	switch (k) {
		case 32:		//��ͣ
			k = k1, b1 = 1;
			_getch();
			break;
		case 'w':
		case 72:		//��
			if (k1 == 80) {
				k = 80, b1 = 1;
				break;
			} else if (k1 != 72)
				map[hx][hy] = '1';
			k1 = 72;
			while (!_kbhit()) {
				turn();
				map[tx][ty] = ' ';
				tail_move(direction);
				hx--;
				if (hx == -1)
					hx = 23;
				if (map[hx][hy] == '@' || (map[hx][hy] >= '1' && map[hx][hy] <= '4')) {
					GameOver();
					break;
				}
				if (map[hx][hy] == '*') {
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
			break;
		case 's':
		case 80:		//��
			if (k1 == 72) {
				k = 72, b1 = 1;
				break;
			} else if (k1 != 80)
				map[hx][hy] = '2';
			k1 = 80;
			while (!_kbhit()) {
				turn();
				map[tx][ty] = ' ';
				tail_move(direction);
				hx++;
				if (hx == 24)
					hx = 0;
				if ( map[hx][hy] == '@' || (map[hx][hy] >= '1' && map[hx][hy] <= '4')) {
					GameOver();
					break;
				}
				if (map[hx][hy] == '*') {
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
			break;
		case 'a':
		case 75:		//��
			if (k1 == 77) {
				k = 77, b1 = 1;
				break;
			} else if (k1 != 75)
				map[hx][hy] = '3';
			k1 = 75;
			while (!_kbhit()) {
				turn();
				map[tx][ty] = ' ';
				tail_move(direction);
				hy--;
				if (hy == -1)
					hy = 23;
				if ( map[hx][hy] == '@' || (map[hx][hy] >= '1' && map[hx][hy] <= '4')) {
					GameOver();
					break;
				}
				if (map[hx][hy] == '*') {
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
			break;
		case 'd':
		case 77:		//��
			if (k1 == 75) {
				k = 75, b1 = 1;
				break;
			} else if (k1 != 77)
				map[hx][hy] = '4';
			k1 = 77;
			while (!_kbhit()) {
				turn();
				map[tx][ty] = ' ';
				tail_move(direction);
				hy++;
				if (hy == 24)
					hy = 0;
				if ( map[hx][hy] == '@' || (map[hx][hy] >= '1' && map[hx][hy] <= '4')) {
					GameOver();
					break;
				}
				if (map[hx][hy] == '*') {
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
			break;
		default:
			k = k1, b1 = 1;
	}
}

int main() {
	system("mode con cols=81 lines=26");
	Init();
	while (1) {
		b1 = 0;
		move();
		if (!b1)
			k = _getch();
	}
}
/*
�����������ˣ���������Щ��
2021-01-25 11:12
*/