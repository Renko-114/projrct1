#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i, j;
	printf("------ɨ����Ϸ------\n");
	for (i = 0; i <= row; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	for (i = 1; i <=row; i++)
	{
		printf("%d ", i);
		for (j = 1; j<=col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("------ɨ����Ϸ------\n");
}

void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;

		if (board[x][y] = '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

int get_mine_count(char mine[ROWS][COLS],int x,int y)
{
	int i, j, count=0;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (mine[x+i][y+j] == '1')
				count++;
		}
	}
	return count;
}

int is_surrounding_empty(char mine[ROWS][COLS], int x, int y)//���庯����ʱ��Ҫд������
{
	if (get_mine_count(mine, x, y) != 0)
		return 0;
	else
		return 1;
}

int is_surrounding_not_shown(char show[ROWS][COLS], int x, int y)//����������������⵫���Ҳ�֪����������
{
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			if (show[x + i][y + j] != '*');
			return 0;
		}
	}
	return 1;
}

//�ж���ѡ���������Ƿ�Ϊ�գ�1.�����겻���� 2.��������Χû���� 3.��������Χû�б��Ų��
void unfold(char mine[ROWS][COLS],char show[ROWS][COLS], int x, int y,int row,int col)
{
	if (x < 1 || x > row && y < 1 && y > col || show[x][y] != '*')
	{
		return;
	}

	int count = get_mine_count(mine, x, y);
	if (count != 0)//��Χ����
	{
		show[x][y] = get_mine_count(mine, x, y) + '0';
	}

	else if (count == 0)//��Χû����
	{
		show[x][y] = ' ';//��������ַ�Ҫ�ǵ�����
		int i, j;
		for (i = -1; i <= 1; i++)
		{
			for (j = -1; j <= 1; j++)
			{
				if (show[x + i][y + j] == '*');
				unfold(mine, show, x+i, y+j, row, col);
			}
		}
	}
}


void FindMine(char show[ROWS][COLS], char mine[ROWS][COLS], int row, int col)
{
	printf("����������:>\n");
	int x = 0;
	int y = 0;
	char z = '0';
	int win = 0;
	int i, j;
	while (win<row*col-EASY_COUNT)
	{
		scanf("%d %d", &x, &y);

		if (show[x][y] != '*')//����Ƿ��Ų����
		{
			printf("�������Ѿ����Ų���ˣ�����������\n");
		}
		else 
		{
			if(x >= 1 && x <= row && y >= 1 && y <= col)//����Ϸ�
			{
				unfold(mine, show, x, y, row, col);
				DisplayBoard(show, ROW, COL);
			}
			else
			{
				printf("����Ƿ�������������\n");
			}
		}

		win = 0;
		for (i = 1; i <= row; i ++ )
		{
			for (j = 1; j <= col; j++)
			{
				if (show[i][j] != '*' && show[i][j] != '#')
				win++;
			}
		}
	}

	if (win == row * col - EASY_COUNT)//����Ƿ�ʤ��
	{
		printf("��ϲ��,���׳ɹ�\n");
		DisplayBoard(mine, ROW, COL);
	}
}

//��ǵĹ���
//չ��һƬ�Ĺ���