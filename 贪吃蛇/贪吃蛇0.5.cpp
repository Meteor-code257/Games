
/*----贪吃蛇----*/
/***********************************
注意：本程序中                      *
-	'1'代表“上”拐点；-	'*'代表食物；*
-	'2'代表“下”拐点；-	'#'代表蛇头；*
-	'3'代表“左”拐点；-	'@'代表蛇身；*
-	'4'代表“右”拐点；               *
（版本0.4更新）                     *
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
int hx, hy, tx, ty, direction, score, Sleeptime = 20, t, Last_time;

COORD coord = { 0, 0 };
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void HideCursor() {
	/*隐藏光标*/
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void MakeFood() {
	/*生成食物*/
	srand(time(0));
	int x, y;
	do {
		x = rand() % 24;
		y = rand() % 24;
	} while (map[x][y] != ' ');
	map[x][y] = '*';
}

void Init() {
	/*初始化变量和地图*/
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
	/*绘制地图并等待*/
	for(int i = 0; i < 7; i++)
		putchar('\t');
	printf("   贪吃蛇游戏\n");
	for (int i = 0; i < 24; i++) {
		printf("  ");
		for (int j = 0; j < 24; j++) {
			if (map[i][j] != ' ') {
				if (isdigit(map[i][j]) || map[i][j] == '@' || map[i][j] == '*') {
					SetConsoleTextAttribute(hOutput, 176);
					 printf("  ");
					 SetConsoleTextAttribute(hOutput, 240);
				} else if (map[i][j] == '#') {
					SetConsoleTextAttribute(hOutput,144);
					 printf("  ");
					 SetConsoleTextAttribute(hOutput, 240);
				}
			} else {
				SetConsoleTextAttribute(hOutput, 240);
				printf("  ");
			}
		}
		SetConsoleTextAttribute(hOutput, 15);
		if (i == 1)
			printf("\t按 w  或 %c  移动\n", 24);
		else if (i == 2)
			printf("\t s a d  %c %c %c\n", 27, 25, 26);
		else if (i == 3)
			printf("\t按空格键暂停，\n");
		else if (i == 4)
			printf("\tEsc退出游戏\n");
		else if (i==6)
			printf("\t速度：%d  \n",Sleeptime);
		else if (i == 7)
			printf("\t分数：%d  \n", score);
		else if (i==23)
			t=Clock - Last_time,printf("\t用时：%d分%d秒  \n",t / 60, t % 60);
		else
			printf("\n");
	}
	SetConsoleCursorPosition(hOutput, coord);		//清屏
	for (int i = 1; i <= Sleeptime; i++){	//延迟
		Sleep(1);
		if (_kbhit())
			break;
	}
}

void GameOver() {
	/*游戏结束*/
	if (MessageBox(NULL, "你失败了！\n再来一遍？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
		Init(), b = 1, Last_time = Clock;
	else
		exit(0);
}

void tail_move(int d) {
	/*移动尾巴*/
	if (d == 1 && --tx == -1)
		tx = 23;
	else if (d == 2 && ++tx == 24)
		tx = 0;
	else if (d == 3 && --ty == -1)
		ty = 23;
	else if (d == 4 && ++ty == 24)
		ty = 0;
}

void move(char k) {
	/*蛇身移动并检测食物和死亡*/
	while (!_kbhit()) {
		if (isdigit(map[tx][ty]))
			direction = map[tx][ty] - 48;
		map[tx][ty] = ' ';
		if (!isdigit(map[hx][hy]))
			map[hx][hy] = '@';
		tail_move(direction);
		if (k == 72 && --hx == -1)
			hx = 23;
		else if (k == 80 && ++hx == 24)
			hx = 0;
		else if (k == 75 && --hy == -1)
			hy = 23;
		else if (k == 77 && ++hy == 24)
			hy = 0;
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
	/*识别输入并移动*/
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
			} else if (k1 != 72)
				map[hx][hy] = '1';
			k1 = 72;
			move(72);
			break;
		case 's':
		case 80:		//下
			if (k1 == 72) {
				k = 72, b = 1;
				break;
			} else if (k1 != 80)
				map[hx][hy] = '2';
			k1 = 80;
			move(80);
			break;
		case 'a':
		case 75:		//左
			if (k1 == 77) {
				k = 77, b = 1;
				break;
			} else if (k1 != 75)
				map[hx][hy] = '3';
			k1 = 75;
			move(75);
			break;
		case 'd':
		case 77:		//右
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
	system("mode con cols=81 lines=26");
	Init();
	while (1) {
		b = 0;
		work();
		if (!b)
			k = _getch();
	}
}

/*
0.1:--初次成功--
-	功能是完善了，但代码有些长
-	2021.01.25 11:12
0.2:--简化代码--
-	简化代码，252行到221行
-	修复食物生成的问题
-	2021.1.29 11:21
0.3:--功能增加--
-	增加蛇头、计时
-	2021.2.??? ...
0.4:--界面更新--
-	给蛇身和界面添加点颜色
-	更新注释
-	计时器可显示分钟
*	bug:暂停依然计入时间
-	2021.2.15 20:34
0.5:
-	再次简化代码
*/
