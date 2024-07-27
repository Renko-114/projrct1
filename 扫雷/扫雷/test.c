#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"


void menu()
{
	printf("*****************************\n");
	printf("********** 1. play **********\n");
	printf("********** 0. exit **********\n");
	printf("*****************************\n");
}

void game()
{
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };
	//初始化
	InitBoard(mine, ROWS, COLS,'0');
	InitBoard(show, ROWS, COLS,'*');
	//打印
	SetMine(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//扫雷
	FindMine(show, mine, ROW, COL);

}

int main()
{
	int input;
	do
	{
		srand((unsigned int)time(NULL));
		menu();
		scanf("%d", &input);
		if (input == 1)
			game();
		else if (input == 0)
			break;
		else
			printf("输入错误，请重新输入\n");
	} while (input);
	return 0;
}