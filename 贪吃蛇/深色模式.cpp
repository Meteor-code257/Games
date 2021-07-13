
/*----̰����----*/
/***********************************
ע�⣺��������                      *
-	'1'�����ϡ��յ㣻-	'*'����ʳ�*
-	'2'�����¡��յ㣻-	'#'������ͷ��*
-	'3'�����󡱹յ㣻-	'@'��������*
-	'4'�����ҡ��յ㣻               *
���汾0.4���£�                     *
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
#define map Map
#define Clock clock()/CLOCKS_PER_SEC
bool b;
char map[24][24], k1, k;
int hx, hy, tx, ty, direction, score, Sleeptime = 45, t, Last_time;

COORD coord = { 0, 0 };
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void HideCursor() {
	/*���ع��*/
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void MakeFood() {
	/*����ʳ��*/
	srand(time(0));
	int x, y;
	do {
		x = rand() % 24;
		y = rand() % 24;
	} while (map[x][y] != ' ');
	map[x][y] = '*';
}

void Init() {
	/*��ʼ�������͵�ͼ*/
	HideCursor();
	hx = 3, hy = 10, tx = 3, ty = 6, b = 0, direction = 4, k1 = 77, k = 77,
		 score = 0;
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 24; j++)
			map[i][j] = ' ';
	for (int i = ty; i <= hy; i++)
		map[3][i] = '@';
	MakeFood();
}

void print() {
	/*���Ƶ�ͼ���ȴ�*/
	for (int i = 1; i <= 83; i++)
		printf("-");
	printf("| ");
	SetConsoleTextAttribute(hOutput, 128);
	for(int i = 1; i <= 26; i++)
		printf("  ");
	SetConsoleTextAttribute(hOutput, 15);
	printf("      ̰������Ϸ\t\t  |");
	for (int i = 0; i < 24; i++) {
		printf("| ");
		SetConsoleTextAttribute(hOutput, 128);
		printf("  ");
		for (int j = 0; j < 24; j++) {
			if (map[i][j] != ' ') {
				if (isdigit(map[i][j]) || map[i][j] == '@') {
					SetConsoleTextAttribute(hOutput, 48);
					printf("  ");
				} else if (map[i][j] == '#') {
					SetConsoleTextAttribute(hOutput,96);
					printf("  ");
				} else if (map[i][j] == '*') {
					SetConsoleTextAttribute(hOutput,64);
					printf("  ");
				}
			} else {
				SetConsoleTextAttribute(hOutput, 0);
				printf("  ");
			}
		}
		SetConsoleTextAttribute(hOutput, 128);
		printf("  ");
		SetConsoleTextAttribute(hOutput, 15);
		if (i == 1)
			printf("    �� w  �� %c  �ƶ�\t  |\n", 24);
		else if (i == 2)
			printf("     s a d  %c %c %c\t\t\t|\n", 27, 25, 26);
		else if (i == 3)
			printf("     ���ո����ͣ��\t\t|\n");
		else if (i == 4)
			printf("     Esc�˳���Ϸ\t\t  |\n");
		else if (i==6)
			printf("       �ٶȣ�%d  \t\t  |\n",Sleeptime);
		else if (i == 7)
			printf("       ������%d  \t\t  |\n", score);
		else if (i==23)
			t=Clock - Last_time,printf("      ��ʱ��%d��%d��\t\t|\n",t / 60, t % 60);
		else
			printf("\t\t\t\t  |\n");
	}
	printf("| ");
	SetConsoleTextAttribute(hOutput, 128);
	for (int i = 1; i <= 26; i++)
		printf("  ");
	SetConsoleTextAttribute(hOutput, 15);
	printf("\t\t\t\t  |\n");
	for (int i = 1; i <= 83; i++)
		printf("-");
	SetConsoleCursorPosition(hOutput, coord);		//����
	Sleep(Sleeptime);	//�ӳ�
}

void GameOver() {
	/*��Ϸ����*/
	if (MessageBox(NULL, "��ʧ���ˣ�\n����һ�飿", "��ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
		Init(), b = 1, Last_time = Clock;
	else
		exit(0);
}

void tail_move(int d) {
	/*�ƶ�β��*/
	switch (d) {
		case 1:
			if (--tx == -1)
				tx = 23;
			break;
		case 2:
			if (++tx == 24)
				tx = 0;
			break;
		case 3:
			if (--ty == -1)
				ty = 23;
			break;
		case 4:
			if (++ty == 24)
				ty = 0;
			break;
	}
}

void move(char k) {
	/*�����ƶ�*/
	while (!_kbhit()) {
		if (isdigit(map[tx][ty]))
			direction = map[tx][ty] - 48;
		map[tx][ty] = ' ';
		if (!isdigit(map[hx][hy]))
			map[hx][hy] = '@';
		tail_move(direction);
		switch(k) {
			case 72:
				if (--hx == -1)
					hx = 23;
				break;
			case 80:
				if (++hx == 24)
					hx = 0;
				break;
			case 75:
				if (--hy == -1)
					hy = 23;
				break;
			case 77:
				if (++hy == 24)
					hy = 0;
				break;
		}
		if (map[hx][hy] == '@' || map[hx][hy] == '#' || isdigit(map[hx][hy])) {
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
		map[hx][hy] = '#';
		print();
	}
}

void work() {
	/*ʶ�����벢�ƶ�*/
	switch (k) {
		case 32:		//��ͣ
			k = k1, b = 1;
			_getch();
			break;
		case 'w':
		case 72:		//��
			if (k1 == 80) {
				k = 80, b = 1;
				break;
			} else if (k1 != 72)
				map[hx][hy] = '1';
			k1 = 72;
			move(72);
			break;
		case 's':
		case 80:		//��
			if (k1 == 72) {
				k = 72, b = 1;
				break;
			} else if (k1 != 80)
				map[hx][hy] = '2';
			k1 = 80;
			move(80);
			break;
		case 'a':
		case 75:		//��
			if (k1 == 77) {
				k = 77, b = 1;
				break;
			} else if (k1 != 75)
				map[hx][hy] = '3';
			k1 = 75;
			move(75);
			break;
		case 'd':
		case 77:		//��
			if (k1 == 75) {
				k = 75, b = 1;
				break;
			} else if (k1 != 77)
				map[hx][hy] = '4';
			k1 = 77;
			move(77);
			break;
		case '\e':
			exit(0);
		default:
			k = k1, b = 1;
	}
}

int main() {
	system("mode con cols=83 lines=29");
	Init();
	while (1) {
		b = 0;
		work();
		if (!b)
			k = _getch();
	}
}

/*
0.1:--���γɹ�--
-	�����������ˣ���������Щ��
-	2021.01.25 11:12
0.2:--�򻯴���--
-	�򻯴��룬252�е�221��
-	�޸�ʳ�����ɵ�����
-	2021.1.29 11:21
0.3:--��������--
-	������ͷ����ʱ
-	2021.2.??? ...
0.4:--�������--
-	������ͽ�����ӵ���ɫ
-	����ע��
-	��ʱ������ʾ����
*	bug:��ͣ��Ȼ����ʱ��
-	2021.2.15 20:34
*/
