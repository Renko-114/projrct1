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
	printf("------扫雷游戏------\n");
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
	printf("------扫雷游戏------\n");
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

int is_surrounding_empty(char mine[ROWS][COLS], int x, int y)//定义函数的时候要写类型名
{
	if (get_mine_count(mine, x, y) != 0)
		return 0;
	else
		return 1;
}

int is_surrounding_not_shown(char show[ROWS][COLS], int x, int y)//捏麻麻的这里有问题但是我不知道问题在哪
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

//判断所选坐标四周是否为空，1.该坐标不是雷 2.该坐标周围没有雷 3.该坐标周围没有被排查过
void unfold(char mine[ROWS][COLS],char show[ROWS][COLS], int x, int y,int row,int col)
{
	if (x < 1 || x > row && y < 1 && y > col || show[x][y] != '*')
	{
		return;
	}

	int count = get_mine_count(mine, x, y);
	if (count != 0)//周围有雷
	{
		show[x][y] = get_mine_count(mine, x, y) + '0';
	}

	else if (count == 0)//周围没有雷
	{
		show[x][y] = ' ';//捏麻麻的字符要是单引号
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
	printf("请输入坐标:>\n");
	int x = 0;
	int y = 0;
	char z = '0';
	int win = 0;
	int i, j;
	while (win<row*col-EASY_COUNT)
	{
		scanf("%d %d", &x, &y);

		if (show[x][y] != '*')//检测是否排查过了
		{
			printf("该坐标已经被排查过了，请重新输入\n");
		}
		else 
		{
			if(x >= 1 && x <= row && y >= 1 && y <= col)//输入合法
			{
				unfold(mine, show, x, y, row, col);
				DisplayBoard(show, ROW, COL);
			}
			else
			{
				printf("输入非法，请重新输入\n");
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

	if (win == row * col - EASY_COUNT)//检测是否胜利
	{
		printf("恭喜你,排雷成功\n");
		DisplayBoard(mine, ROW, COL);
	}
}

//标记的功能
//展开一片的功能