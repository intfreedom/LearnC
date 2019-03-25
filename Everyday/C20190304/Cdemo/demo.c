#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define LEN sizeof(struct student)

struct student *creat();
struct student *del(struct student *head, int num);

void print(struct student *head);

struct student
{
		int num;
		float score;
		struct student *next;
};

int n;//global variety, data;


void main()
{
	struct student *stu, *p;
//	int n;

	stu = creat();
	p = stu;
	print(p);

	printf("Please enter the num to delete: ");
	scanf("%d",&n);
	printf(del(p,n));

	printf("\n\n");
	system("pause");
}

struct student *creat()
{
	struct student *head;
	struct student *p1,*p2;

	p1 = p2 = (struct student *)malloc(LEN);

	printf("Please enter the num: ");
	scanf("%d",&p1->num);
	printf("Please enter the score");
	scanf("%f",&p1->score);

	head = NULL;
	n=0;

	while(p1->num)
	{
		n++;
		if(n == 1)
		{
			head = p1;
		}
		else
		{
			p2->next = p1;
		}

		p2 = p1;

		p1 = (struct student *)malloc(LEN);//why create new one?

		printf("\nPlease enter the num: ");
		scanf("%d", &p1->num);
		printf("Please enter the score: ");
		scanf("%f", &p1->score);
	}

	p2->next = NULL;

	return head;
}

void print(struct student *head)
{
	struct student *p;
	printf("\nThere are %d records!\n\n",n);

	p = head;
	if(head)
	{
		do
		{
			printf("Score is %d: %f\n",p->num,p->score);
			p = p->next;
		}while(p);
	}
}

struct student *del(struct student *head,int num)
{
	struct student *p1,*p2;

	if(NULL == head)
	{
		printf("\nThis list is null!\n");
		goto END;
	}

	p1 = head;
	while(p1->num != num && p1->next != NULL)
	{
		p2 = p1;
		p1 = p1->next;
	}
	if(num == p1->num)
	{
		if(p1 == head)
		{
			head = p1->next;
		}
		else
		{
			p2->next = p1->next;
		}

		printf("\nDelete No: %d succeed!\n",num);
		n = n-1;
	}
	else
	{
		printf("%d not been found!\n",num);
	}
END:
	return head;
}
