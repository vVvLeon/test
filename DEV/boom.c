##pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#define MINE_COUNT 80//地雷数量
#define ROW 9//
#define COL 9//更改这三部变换难度；
#define ROWS ROW+2
#define COLS COL+2
enum CHOOSE
{
	EXIT,
	PLAY,
};
extern int flag;
extern int setp;
void init_board(char a[][COLS], int r, int c, char set);//初始化棋盘
void display_board(char a[][COLS], int r, int c);//打印棋盘
void set_mine(char mine[][COLS], int r, int c, int count);//布置雷
void find_mine(char show[][COLS], char mine[][COLS], int r, int c);//排查雷；
int get_mine(char show[][COLS], char mine[][COLS], int r, int c);//得到雷的数量
bool is_mine(char mine[][COLS], int x, int y);//判断下x，y是否为雷；
bool is_find(char show[][COLS], int x, int y);//判断是否被排查过
void surprise(char mine[][COLS], char show[][COLS], int r, int c, int x, int y);//展开一片

#include "game.h"
#pragma warning (disable:6031)
void init_board(char a[][COLS], int r, int c, char set)
{
	int i = 1;
	int j = 1;
	for (i = 1; i <= r; i++)
	{
		for (j = 1; j <= c; j++)
		{
			a[i][j] = set;
		}
	}
}
void display_board(char a[][COLS], int r, int c)
{
	int i = 1;
	int j = 1;
	printf(" ");
	for (j = 0; j <= c; j++)
	{
		if (j < 10)
			printf("%d ", j);
		else
		{
			printf("%c ", 'A' + j - 10);
		}
	}
	putchar('\n');
	for (j = 0; j <= c; j++)
	{
		printf("--");
	}
	putchar('\n');
	for (i = 1; i <= r; i++)
	{
		if (i < 10)
			printf("%d| ", i);
		else
		{
			printf("%c| ", 'A' + i - 10);
		}
		for (j = 1; j <= c; j++)
		{
			printf("%c ", a[i][j]);
		}
		printf("\n");
	}
}
void set_mine(char mine[][COLS], int r, int c, int count)
{
	int x = 0;
	int y = 0;
	while (count)
	{
		x = rand() % r + 1;
		y = rand() % c + 1;
		if (mine[x][y] == ' ')
		{
			mine[x][y] = '#';
			count--;
		}
	}
}
void find_mine(char show[][COLS], char mine[][COLS], int r, int c)//看看能不能在优化；
{
	int x = 0;
	int y = 0;
	char ch = 0;
	while (1)
	{
		printf("请输入你要排查的位置,并选择是否对该点进行标识(Y\\其它默认不标记)>");//对同一个点多次标记会取消标记；
		scanf("%d %d %c", &x, &y, &ch);
		if (x >= 1 && x <= r && y >= 1 && y <= c)//坐标合法
		{
			if (!is_find(show, x, y))//未被排查过
			{
				if (show[x][y] == 'M' && 'Y' == ch)
				{
					show[x][y] = '*';
					printf("取消标记成功\n");
					system("cls");
					display_board(show, r, c);
					break;
				}
				if ('Y' == ch)//判断一下是否需要标记；
				{
					show[x][y] = 'M';
					printf("标记成功\n");
					system("cls");
					display_board(show, r, c);
					break;
				}
				else
				{
					if (is_mine(mine, x, y))//该位置是地雷
					{
						printf("你被雷炸死了\n\a\a\a");
						show[x][y] = '#';//将炸死的回访展示出来
						flag = 0;
						system("cls");
						display_board(mine, r, c);
						break;
					}
					else//不是雷
					{
						surprise(mine, show, r, c, x, y);//进一步判断该位置周围雷的数量，若为0，进行进一步展开
						system("cls");
						display_board(show, r, c);
						break;
					}
				}
			}
			else
			{
				printf("坐标已排查过,请重新输入:>\n");
			}

		}
		else
			printf("坐标非法,请重新输入\n");
	}
}
int get_mine(char show[][COLS], char mine[][COLS], int x, int y)
{
	int count = 0;
	if (mine[x - 1][y - 1] == '#')
		count++;
	if (mine[x - 1][y] == '#')
		count++;
	if (mine[x - 1][y + 1] == '#')
		count++;
	if (mine[x][y - 1] == '#')
		count++;
	if (mine[x][y + 1] == '#')
		count++;
	if (mine[x + 1][y - 1] == '#')
		count++;
	if (mine[x + 1][y] == '#')
		count++;
	if (mine[x + 1][y + 1] == '#')
		count++;
	return count;
}
bool is_mine(char mine[][COLS], int x, int y)
{
	if (mine[x][y] == ' ')
		return false;
	return true;
}
bool is_find(char show[][COLS], int x, int y)
{
	if (show[x][y] == '*' || show[x][y] == 'M')
		return false;
	return true;
}
void surprise(char mine[][COLS], char show[][COLS], int r, int c, int x, int y)
{
	if (!(x >= 1 && x <= r && y >= 1 && y <= c))//防止越界；
		return;
	if (is_mine(mine, x, y) || is_find(show, x, y))//能展开的条件：1、没被排查过；2、排查位置不是雷
		return;
	setp--;
	int count = get_mine(show, mine, x, y);//3、排查位置周围没有雷；
	show[x][y] = count + '0';
	if (count == 0)
	{
		surprise(mine, show, r, c, x - 1, y - 1);
		surprise(mine, show, r, c, x - 1, y);
		surprise(mine, show, r, c, x - 1, y + 1);
		surprise(mine, show, r, c, x, y - 1);
		surprise(mine, show, r, c, x, y + 1);
		surprise(mine, show, r, c, x + 1, y - 1);
		surprise(mine, show, r, c, x + 1, y);
		surprise(mine, show, r, c, x + 1, y + 1);
	}
}
#include"game.h"
#pragma warning (disable:6031)
//1、雷盘，展示盘
//2、初始化雷盘和展示盘//空格表示没雷#表示雷；*初始化展示盘
//3、打印一下棋盘；
//4、布置雷；
//5、排查雷；(注意触发惊喜)
int setp = ROW * COL - MINE_COUNT;//记录排雷最多步数；当setp等于0是表示安全位置已经排完，挑战成功
int flag = 1;//表示未被地雷炸死而结束游戏，地雷炸死而结束游戏的flag=0，挑战失败；
void game()
{
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };
	init_board(mine, ROW, COL, ' ');//初始化
	init_board(show, ROW, COL, '*');//初始化
	set_mine(mine, ROW, COL, MINE_COUNT);//布置雷
	//display_board(mine, ROW, COL);//开透视
	display_board(show, ROW, COL);//展示棋盘（给玩家看）；
	setp = ROW * COL - MINE_COUNT;
	flag = 1;//重置一下，开始新的游戏
	while (setp && flag)
	{
		find_mine(show, mine, ROW, COL);
	}
	if (!setp)
	{
		system("cls");
		printf("挑战成功\a\a\a\a\n");
	}
	else if (!flag)
	{
		system("cls");
		printf("挑战失败\a\a\a\n");
	}
	display_board(show, ROW, COL);//展示棋盘（给玩家看）；
	for (int j = 0; j <= COL; j++)
	{
		printf("--");
	}
	putchar('\n');
	display_board(mine, ROW, COL);
}

void menu()
{
	printf("**********  扫雷小游戏  ********* "); printf("             游戏介绍\n");
	printf("********      1. play    ******** "); printf("1、两次对同一个点标记，可取消标记。\n");
	printf("********      0. exit    ******** "); printf("2、最后一次输入位置若是地雷，则该位置将会被标为#以此告诉玩家死亡原因。\n");
	printf("********************************* "); printf("3、若在坐标后面输入Y则表示对该点进行标记，其它默认不标记。\n");
}

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case PLAY:
			system("cls");
			game(); break;
		case EXIT:
			system("cls"); printf("退出游戏\n"); break;
		default:
			system("cls"); printf("输入有误，重新输入:>\n"); break;
		}
	} while (input);
	return 0;
}

