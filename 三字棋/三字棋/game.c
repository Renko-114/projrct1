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
		printf("\n");//�������д��������ô�Ѿ�
	}
}

void PlayerMove(char board[ROW][COL],int row,int col)
{
	int x, y;
	printf("�������\n");
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
				printf("������ռ�ã�����������\n");
		}
		else
			printf("�����ֵ�Ƿ�������������\n");
	}
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	int x, y;
	printf("��������\n");

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
	for (i = 0; i < row; i++)//�ж���
	{
		if (board[i][0] == board[i][1]&&board[i][0]==board[i][2] && board[i][0] != ' ')
			return board[i][0];
	}

	for (j = 0; j < col; j++)//�ж���
	{
		if (board[0][j] == board[1][j] && board[0][j] == board[2][j] && board[0][j] != ' ')
			return board[0][j];
	}

	if ((board[0][0] == board[1][1]&&board[0][0] == board[2][2] && board[0][0] != ' ') || (board[2][0] == board[1][1] &&board[2][0]==board[0][2] && board[1][1] != ' '))
		return board[1][1];

	if (Is_Full(board,row,col))//���ú���ʱֻ��Ҫʹ��������
		return 'p';

	return 'c';
}