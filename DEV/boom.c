##pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#define MINE_COUNT 80//��������
#define ROW 9//
#define COL 9//�����������任�Ѷȣ�
#define ROWS ROW+2
#define COLS COL+2
enum CHOOSE
{
	EXIT,
	PLAY,
};
extern int flag;
extern int setp;
void init_board(char a[][COLS], int r, int c, char set);//��ʼ������
void display_board(char a[][COLS], int r, int c);//��ӡ����
void set_mine(char mine[][COLS], int r, int c, int count);//������
void find_mine(char show[][COLS], char mine[][COLS], int r, int c);//�Ų��ף�
int get_mine(char show[][COLS], char mine[][COLS], int r, int c);//�õ��׵�����
bool is_mine(char mine[][COLS], int x, int y);//�ж���x��y�Ƿ�Ϊ�ף�
bool is_find(char show[][COLS], int x, int y);//�ж��Ƿ��Ų��
void surprise(char mine[][COLS], char show[][COLS], int r, int c, int x, int y);//չ��һƬ

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
void find_mine(char show[][COLS], char mine[][COLS], int r, int c)//�����ܲ������Ż���
{
	int x = 0;
	int y = 0;
	char ch = 0;
	while (1)
	{
		printf("��������Ҫ�Ų��λ��,��ѡ���Ƿ�Ըõ���б�ʶ(Y\\����Ĭ�ϲ����)>");//��ͬһ�����α�ǻ�ȡ����ǣ�
		scanf("%d %d %c", &x, &y, &ch);
		if (x >= 1 && x <= r && y >= 1 && y <= c)//����Ϸ�
		{
			if (!is_find(show, x, y))//δ���Ų��
			{
				if (show[x][y] == 'M' && 'Y' == ch)
				{
					show[x][y] = '*';
					printf("ȡ����ǳɹ�\n");
					system("cls");
					display_board(show, r, c);
					break;
				}
				if ('Y' == ch)//�ж�һ���Ƿ���Ҫ��ǣ�
				{
					show[x][y] = 'M';
					printf("��ǳɹ�\n");
					system("cls");
					display_board(show, r, c);
					break;
				}
				else
				{
					if (is_mine(mine, x, y))//��λ���ǵ���
					{
						printf("�㱻��ը����\n\a\a\a");
						show[x][y] = '#';//��ը���Ļط�չʾ����
						flag = 0;
						system("cls");
						display_board(mine, r, c);
						break;
					}
					else//������
					{
						surprise(mine, show, r, c, x, y);//��һ���жϸ�λ����Χ�׵���������Ϊ0�����н�һ��չ��
						system("cls");
						display_board(show, r, c);
						break;
					}
				}
			}
			else
			{
				printf("�������Ų��,����������:>\n");
			}

		}
		else
			printf("����Ƿ�,����������\n");
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
	if (!(x >= 1 && x <= r && y >= 1 && y <= c))//��ֹԽ�磻
		return;
	if (is_mine(mine, x, y) || is_find(show, x, y))//��չ����������1��û���Ų����2���Ų�λ�ò�����
		return;
	setp--;
	int count = get_mine(show, mine, x, y);//3���Ų�λ����Χû���ף�
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
//1�����̣�չʾ��
//2����ʼ�����̺�չʾ��//�ո��ʾû��#��ʾ�ף�*��ʼ��չʾ��
//3����ӡһ�����̣�
//4�������ף�
//5���Ų��ף�(ע�ⴥ����ϲ)
int setp = ROW * COL - MINE_COUNT;//��¼������ಽ������setp����0�Ǳ�ʾ��ȫλ���Ѿ����꣬��ս�ɹ�
int flag = 1;//��ʾδ������ը����������Ϸ������ը����������Ϸ��flag=0����սʧ�ܣ�
void game()
{
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };
	init_board(mine, ROW, COL, ' ');//��ʼ��
	init_board(show, ROW, COL, '*');//��ʼ��
	set_mine(mine, ROW, COL, MINE_COUNT);//������
	//display_board(mine, ROW, COL);//��͸��
	display_board(show, ROW, COL);//չʾ���̣�����ҿ�����
	setp = ROW * COL - MINE_COUNT;
	flag = 1;//����һ�£���ʼ�µ���Ϸ
	while (setp && flag)
	{
		find_mine(show, mine, ROW, COL);
	}
	if (!setp)
	{
		system("cls");
		printf("��ս�ɹ�\a\a\a\a\n");
	}
	else if (!flag)
	{
		system("cls");
		printf("��սʧ��\a\a\a\n");
	}
	display_board(show, ROW, COL);//չʾ���̣�����ҿ�����
	for (int j = 0; j <= COL; j++)
	{
		printf("--");
	}
	putchar('\n');
	display_board(mine, ROW, COL);
}

void menu()
{
	printf("**********  ɨ��С��Ϸ  ********* "); printf("             ��Ϸ����\n");
	printf("********      1. play    ******** "); printf("1�����ζ�ͬһ�����ǣ���ȡ����ǡ�\n");
	printf("********      0. exit    ******** "); printf("2�����һ������λ�����ǵ��ף����λ�ý��ᱻ��Ϊ#�Դ˸����������ԭ��\n");
	printf("********************************* "); printf("3�����������������Y���ʾ�Ըõ���б�ǣ�����Ĭ�ϲ���ǡ�\n");
}

int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case PLAY:
			system("cls");
			game(); break;
		case EXIT:
			system("cls"); printf("�˳���Ϸ\n"); break;
		default:
			system("cls"); printf("����������������:>\n"); break;
		}
	} while (input);
	return 0;
}

