#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void InitBoard(char board[ROW][COL],int row,int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j != col - 1)
				printf("|");
		}
		printf("\n");

		if(i!=row)
		for (j = 1; j <= col ; j++)
		{
			if (j != col)
				printf("---|");
			else
				printf("---");
		}
		printf("\n");//捏麻麻的写个棋盘这么费劲
	}
}

void PlayerMove(char board[ROW][COL],int row,int col)
{
	int x, y;
	printf("玩家下棋\n");
	while (1)
	{
		scanf("%d %d", &x, &y);

		if (0 <= x - 1 && x - 1 < row && 0 <= y - 1 && y - 1 < col)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
				printf("格子已占用，请重新输入\n");
		}
		else
			printf("输入的值非法，请重新输入\n");
	}
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	int x, y;
	printf("电脑下棋\n");

	while (1)
	{
		x = rand() % row;
		y = rand() % col;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}

int Is_Full(char board[ROW][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}

	return 1;
}

char Is_win(char board[ROW][COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)//判断行
	{
		if (board[i][0] == board[i][1]&&board[i][0]==board[i][2] && board[i][0] != ' ')
			return board[i][0];
	}

	for (j = 0; j < col; j++)//判断列
	{
		if (board[0][j] == board[1][j] && board[0][j] == board[2][j] && board[0][j] != ' ')
			return board[0][j];
	}

	if ((board[0][0] == board[1][1]&&board[0][0] == board[2][2] && board[0][0] != ' ') || (board[2][0] == board[1][1] &&board[2][0]==board[0][2] && board[1][1] != ' '))
		return board[1][1];

	if (Is_Full(board,row,col))//调用函数时只需要使用数组名
		return 'p';

	return 'c';
}