#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>			//接收键盘输入输出

#define U 1
#define D 2
#define L 3
#define R 4      //蛇的状态，U：上 ；D：下；L:左 R：右



typedef struct snake
{
	int x;
	int y;
	struct snake* next;
}snake;
int score=0,add=10;
int status,sleeptime=200;
snake* head, *food;
snake *q;
int endgamestatus=0;
HANDLE hOut;

void gotoxy(int x,int y);   //设置光标位置
int color(int c);           //更改文字颜色
void welcometogame();       //开始界面
void createMap();           //绘制地图
void scoreandtips();		//游戏界面右侧的得分和小提示
void initsnake();           //初始化蛇身，画蛇身
void createfood();          //创建并随机出现食物
int biteself();             //判断是否咬到了自己
void cantcrosswall();       //设置蛇撞墙的情况
void speedup();				//加速
void speeddown();			//减速
void snakemove();           //控制蛇前进方向
void keyboardControl();     //控制键盘按键
void Lostdraw();            //游戏结束界面
void endgame();             //游戏结束
void choose();				//游戏失败之后的选择
void explation();           //游戏说明

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
	printf("Games");
	color(12);
	gotoxy(25,22);
	printf("1.Start");
	gotoxy(45, 22);
	printf("2.游戏说明");
	gotoxy(65, 22);
	printf("3.退出游戏");
	gotoxy(40,27);
	color(3);
	printf("请选择 1 2 3:");
	color(14);
    scanf("%d", &n);    		//输入选项
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
    		printf("please input 1-3 number!");
    		_getch();
    		system("cls");
    		welcometogame();

    }
}

void createMap()
{
    int i,j;
    for(i=0;i<58;i+=2)		//打印上下边框
    {
        gotoxy(i,0);
		color(5);
        printf("□");
        gotoxy(i,26);
        printf("□");
    }
    for(i=1;i<26;i++)		//打印左右边框
    {
        gotoxy(0,i);
        printf("□");
        gotoxy(56,i);
        printf("□");
    }
	for(i = 2;i<56;i+=2)	//打印中间网格
	{
		for(j = 1;j<26;j++)
		{
			gotoxy(i,j);
			color(3);
			printf("■");
		}
	}
}

void scoreandtips()
{

	gotoxy(64,8);
	color(14);
	printf("得分：%d  ",score);

	gotoxy(64,14);
	printf("每个食物得分：%d分",add);
	gotoxy(64,16);
	printf("不能穿墙，不能咬到自己");
	gotoxy(64,18);
	printf("用↑ ↓ ← →分别控制蛇的移动");
	gotoxy(64,20);
	printf("F1 为加速，F2 为减速");
	gotoxy(64,22);
	printf("space：暂停游戏");
	gotoxy(64,24);
    printf("ESC ：退出游戏");
}



void initsnake()
{
	snake* tail;
	int i;
	tail=(snake*)malloc(sizeof(snake));
	tail->x=24;
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
		printf("★");
		tail=tail->next;
	}
}


void createfood()
{
	snake* food_1;
	srand((unsigned)time(NULL));
	food_1=(snake*)malloc(sizeof(snake));
	while((food_1->x%2)!=0)
	{
		food_1->x=rand()%52+2;
	}
	food_1->y=rand()%24+1;
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
	printf("●");
}

int biteself()
{
	snake* self;
	self=head->next;
	while(self!=NULL)
	{
		if(self->x==head->x && self->y==head->y)
		{
			return 1;
		}
		self=self->next;
	}
	return 0;
}

void cantcrosswall()
{
    if(head->x==0 || head->x==56 ||head->y==0 || head->y==26) //如果蛇头碰到了墙壁
    {
        endgamestatus=1;        //返回第一种情况
        endgame();              //出现游戏结束界面
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

/**
 *  加速，按F2会减速
 */
void speeddown()
{
	if(sleeptime<350)               //如果时间间隔小于350
    {
        sleeptime=sleeptime+30;     //时间间隔加上30
        add=add-2;                  //每吃一次食物的得分减2

    }
}

/**
 *  控制方向    问题：为什么要设置status，而不使用前两章中接收键盘按键的方法
 */
void snakemove()
{
	snake* nexthead;
	cantcrosswall();
	nexthead=(snake*)malloc(sizeof(snake));
	if(status==U)
	{
		nexthead->x=head->x;
		nexthead->y=head->y-1;
		nexthead->next=head;
		head=nexthead;
		q=head;
		if(nexthead->x==food->x && nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("★");
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
				printf("★");
				q=q->next;
			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("■");
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
		if(nexthead->x==food->x && nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("★");
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
				printf("★");
				q=q->next;
			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("■");
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
				printf("★");
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
				printf("★");
				q=q->next;
			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("■");
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
				printf("★");
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
				printf("★");
				q=q->next;
			}
			gotoxy(q->next->x,q->next->y);
			color(3);
			printf("■");
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
	status = R;
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
		else if (GetAsyncKeyState(VK_F1))
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
	printf("1.can't cross wall, can't bite yourself!");
	color(10);
	gotoxy(30,11);
	printf("2.use up down left right move");
	color(14);
	gotoxy(30,14);
	gotoxy(30,14);
	printf("3. F1 为加速，F2 为减速");
	color(11);
	gotoxy(30,17);
	printf("4. 按空格键暂停游戏，再按空格键继续");
	color(4);
	gotoxy(30,20);
	printf("5. ESC ：退出游戏.space：暂停游戏");
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
		printf("Game ove!");
	}
	else if(endgamestatus==2)
	{
		gotoxy(43,9);
		color(12);
		printf("game over!");
	}
	else if(endgamestatus==3)
	{
		gotoxy(40,9);
		color(12);
		printf("have finish the game!");
	}
	gotoxy(43,12);
	color(13);
	printf("your score is %d",score);
	choose();
}

void choose()
{
	int n;
	gotoxy(25,23);
	color(12);
	printf("Coutinue_________1");
	gotoxy(52,23);
	printf("Exit----------2");
	gotoxy(45, 25);
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
		printf("input error ,repeat!");
		system("pause > null");
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
	printf("\\\\\\\\|////////");
	gotoxy(43,3);
	printf("\\\\\\");
	gotoxy(47,3);
	color(15);
	printf("._._");
	gotoxy(54,3);
	color(6);
	printf("///");
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
	printf("+------------------------");

	gotoxy(35,5);
	color(14);
	printf("oOOo");

	gotoxy(39,5);
	color(11);
	printf("----------");

	gotoxy(48,5);
	color(14);
	printf("(_)");

	gotoxy(51,5);
	color(11);
	printf("----------");

	gotoxy(61,5);
	color(14);
	printf("oOOo");

	gotoxy(65,5);
	color(11);
	printf("-----------------+");

	for(i = 6;i<=19;i++)        //竖边框
	{
		gotoxy(17,i);
		printf("|");
		gotoxy(82,i);
		printf("|");
	}

	gotoxy(17,20);
	printf("+---------------------------------");

	gotoxy(52,20);
	color(14);
	printf("☆☆☆〃");

	gotoxy(60,20);
	color(11);
	printf("----------------------+");

}




int main()
{

	system("mode con cols=100 lines=30");
	welcometogame();

	keyboardControl();
	endgame();
	return 0;

}
































