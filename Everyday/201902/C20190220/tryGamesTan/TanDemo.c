#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS 1
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>


#define U 1
#define D 2
#define L 3
#define R 4

typedef struct snake
{
	int x;
	int y;
	struct snake*next;
} snake;
int score=0,add=10;
int status,sleeptime=200;
snake *head,*food;
snake *q;
int endgamestatus=0;
HANDLE hOut;

void gotoxy(int x, int y);
int color(int c);
void welcometogame();
void createMap();
void scoreandtips();
void initsnake();
void createfood();
int biteself();
void cantcrosswall();
void speedup();
void speeddown();
void snakemove();
void keyboardControl();
void Lostdraw();
void endgame();
void choose();
void explation();

void gotoxy(int x, int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}

void welcometogame()
{
	int n;
	gotoxy(43,10);
	color(11);
	printf("Snake off!!!");
	color(12);
	gotoxy(25,22);
	printf("1.Start Games");
	gotoxy(45,22);
	printf("2.Games Introduction");
	gotoxy(65,22);
	printf("3.Quit Game");
	gotoxy(40,27);
	color(3);
	printf("Please choose 1 2 3: ");
	color(14);
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			system("cls");
			createMap();
			initsnake();
			createfood();
			keyboardControl();
			break;
		case 2:
			explation();
			break;
		case 3:
			exit(0);
			break;
		default:
			color(12);
			gotoxy(40,28);
			printf("Please input 1-3!!!");
			_getch();
			system("cls");
			welcometogame();
	}
}

void createMap()
{
	int i,j;
	for(i=0;i<58;i+=2)
	{
		gotoxy(i,0);
		color(5);
		printf("��");
		gotoxy(i,26);
		printf("��");
	}
	for(i=1;i<26;i++)
	{
		gotoxy(0,i);
		printf("��");
		gotoxy(56,i);
		printf("��");
	}
	for(i=2;i<56;i+=2)
	{
		for(j=1;j<26;j++)
		{
			gotoxy(i,j);
			color(3);
			printf("��");
		}
	}
}

void scoreandtips()
{
	gotoxy(64,8);
	color(14);
	printf("Gores:%d",score);

	gotoxy(64,14);
	printf("Every food score is:%d",add);
	gotoxy(64,16);
	printf("Can't through the wall, cant't bite yourself");
	gotoxy(64,18);
	printf("use keyboard control the moving of snake");
	gotoxy(64,20);
	printf("F1 is speed up,F2 is speed down");
	gotoxy(64,22);
	printf("space: pause games");
	gotoxy(64,24);
	printf("ESC: quit games");
}

void initsnake()
{
	snake *tail;
	int i;
	tail=(snake*)malloc(sizeof(snake));//��̬�����ڴ�
	tail->x=24;//�߳�ʼλ�ã�24��5��
	tail->y=5;
	tail->next=NULL;
	for(i=1;i<=4;i++)
	{
		head=(snake*)malloc(sizeof(snake));
		head->next=tail;
		head->x=24+2*i;
		head->y=5;
		tail=head;
	}
	while(tail!=NULL)
	{
		gotoxy(tail->x,tail->y);
		color(14);
		printf("��");
		tail=tail->next;
	}
}

void createfood()
{
	snake *food_1;
	srand((unsigned)time(NULL));
	food_1=(snake*)malloc(sizeof(snake));
	while((food_1->x%2)!=0)
	{
		food_1->x=rand()%52+2;
	}
	food_1->y=rand()%52+2;
	q=head;
	while(q->next==NULL)
	{
		if(q->x==food_1->x && q->y==food_1->y)
		{
			free(food_1);
			createfood();
		}
		q=q->next;
	}
	gotoxy(food_1->x,food_1->y);
	food=food_1;
	color(12);
	printf("��");
}

int biteself()
{
	snake *self;
	self=head->next;
	while(self!=NULL)
	{
		if(self->x==head->x&&self->y==head->y)
		{
			return 1;
		}
		self=self->next;
	}
	return 0;
}

void cantcrosswall()
{
	if(head->x==0 || head->x==56 || head->y==0 || head->y==26)
	{
		endgamestatus=1;
		endgame();
	}
}



void speedup()
{
	if(sleeptime>=50)
	{
		sleeptime=sleeptime-10;
		add=add+2;
	}
}

void speeddown()
{
	if(sleeptime<350)
	{
		sleeptime=sleeptime+30;
		add=add-2;
	}
}


void snakemove()
{
	snake *nexthead;
	cantcrosswall();
	nexthead=(snake*)malloc(sizeof(snake));
	if(status==U)
	{
		nexthead->x=head->x;
		nexthead->y=head->y-1;
		nexthead->next=head;
		head=nexthead;
		q=head;
		if(nexthead->x==food->x&&nexthead->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
		else
		{
			while(q->next->next!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;

			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("��");
			free(q->next);
			q->next=NULL;
		}
	}
	if(status==D)
	{
		nexthead->x=head->x;
		nexthead->y=head->y+1;
		nexthead->next=head;
		head=nexthead;
		q=head;
		if(nexthead->x==food->x && nexthead ->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();//tan.c line 350;
			createfood();
		}
		else
		{
			while(q->next->next!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("��");
			free(q->next);
			q->next=NULL;
		}
	}
	if(status==L)
	{
		nexthead->x=head->x-2;
		nexthead->y=head->y;
		nexthead->next=head;
		head=nexthead;
		q=head;
		if(nexthead->x==food->x && nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
		else
		{
			while(q->next->next!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("��");
			free(q->next);
			q->next=NULL;
		}
	}
	if(status==R)
	{
		nexthead->x=head->x+2;
		nexthead->y=head->y;
		nexthead->next=head;
		head=nexthead;
		q=head;
		if(nexthead->x==food->x && nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
		else
		{
			while(q->next->next!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("��");
				q=q->next;
			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("��");
			free(q->next);
			q->next=NULL;
		}
	}
	if(biteself()==1)
	{
		endgamestatus=2;
		endgame();
	}
}


void keyboardControl()
{
	status=R;
	while(1)
	{
		scoreandtips();
		if(GetAsyncKeyState(VK_UP) && status!=D)
		{
			status=U;
		}
		else if(GetAsyncKeyState(VK_DOWN) && status!=U)
		{
			status=D;
		}
		else if(GetAsyncKeyState(VK_LEFT) && status!=R)
		{
			status=L;
		}
		else if(GetAsyncKeyState(VK_RIGHT) && status!=L)
		{
			status=R;
		}
		if(GetAsyncKeyState(VK_SPACE))
		{
			while(1)
			{
				Sleep(300);
				if(GetAsyncKeyState(VK_SPACE))
				{
					break;
				}

			}
		}
		else if(GetAsyncKeyState(VK_ESCAPE))
		{
			endgamestatus=3;
			break;
		}
		else if(GetAsyncKeyState(VK_F1))
		{
			speedup();
		}
		else if(GetAsyncKeyState(VK_F2))
		{
			speeddown();
		}
		Sleep(sleeptime);
		snakemove();
	}
}


void explation()
{
	system("cls");
	color(3);
	gotoxy(30,8);
	printf("1.can't through wall, can't bite yourself");
	color(10);
	gotoxy(30,11);
	printf("2.Use up down control the move of snake");
	color(14);
	gotoxy(30,14);
	printf("3.F1 is speedup,F2 is slow down");
	color(11);
	gotoxy(30,17);
	printf("4.use space key pause games, and use space key continue");
	color(4);
	gotoxy(30,20);
	printf("5.ESC:quit games.space:pause games");
	_getch();
	system("cls");
	welcometogame();
}


void endgame()
{
	system("cls");
	if(endgamestatus==1)
	{
		gotoxy(43,9);
		color(12);
		printf("GAME OVER!");
	}
	else if(endgamestatus==2)
	{
		gotoxy(43,9);
		color(12);
		printf("GAME OVER!");
	}
	else if(endgamestatus==3)
	{
		gotoxy(40,9);
		color(13);
		printf("your score is %d",score);
		choose();
	}
}

void choose()
{
	int n;
	gotoxy(25,23);
	color(12);
	printf("Continue -------- 1");
	gotoxy(52,23);
	printf("Exit -------- 2");
	gotoxy(45,25);
	color(11);
	printf("choose: ");
	scanf("%d",&n);
	switch(n)
	{
	case 1:
		system("cls");
		score=0;
		sleeptime=200;
		add = 10;
		welcometogame();
		break;
	case 2:
		exit(0);
		break;
	default:
		gotoxy(35,27);
		color(12);
		printf("Repeat, error");
		system("pause>nul");
		endgame();
		choose();
		break;
	}
}


void Lostdraw()
{
	system("cls");
	int i;
	gotoxy(45,2);
	color(6);
	printf("\\\\\\|/////");
	gotoxy(43,3);
	printf("\\\\\\\\");
	gotoxy(47,3);
	color(15);
	printf(".-.-");
	gotoxy(54,3);
	color(6);
	printf("//");

	gotoxy(44,4);
	color(14);
	printf("(");

	gotoxy(47,4);
	color(15);
	printf(".@.@");

	gotoxy(54,4);
	color(14);
	printf(")");

	gotoxy(17,5);
	color(11);
	printf("+------------------------------");

	gotoxy(35,5);
	color(14);
	printf("0OO0");

	gotoxy(39,5);
	color(11);
	printf("-----------------");

	gotoxy(48,5);
	color(14);
	printf("(_)");

	gotoxy(51,5);
	color(11);
	printf("--------------");

	gotoxy(61,5);
	color(14);
	printf("0OO0");

	gotoxy(65,5);
	color(11);
	printf("-----------------+");

	for(i = 6;i<=19;i++)
	{
		gotoxy(17,i);
		printf("|");
		gotoxy(82,i);
		printf("|");
	}

	gotoxy(17,20);
	printf("+---------------------------");

	gotoxy(52,20);
	color(14);
	printf("���");

	gotoxy(60,20);
	color(11);
	printf("--------------------+");
}

int main()
{
	system("mode con cols =100 lines=30");
	welcometogame();

	keyboardControl();
	endgame();
	return 0;
}