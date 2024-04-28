#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define CHUNKSIZE 4 
#define n 26
char blank = '#';	// 全局变量,用于填补空余    
typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;
typedef struct
{
	Chunk* head, * tail;
	int curlen;
}LString;
void InitString(LString* T)// 初始化(产生空串)字符串T。
{
	(*T).curlen = 0;
	(*T).head = NULL;
	(*T).tail = NULL;
}
int StrAssign(LString* T, char* chars)// 生成一个其值等于chars的串T， 成功返回1，否则返回0  
{
	int i, j, k, l;
	Chunk* p, * q;
	i = strlen(chars); // i为串的长度 
	if (!i || strchr(chars, blank)) // 串长为0或chars中包含填补空余的字符 
		return 0;
	(*T).curlen = i;
	j = i / CHUNKSIZE;	// j为块链的结点数，块的个数 
	if (i % CHUNKSIZE)	//不足一个块的，当成一个块即块数加1
		j++;
	printf("长度是%d\n行数是%d\n", i, j);
	for (k = 0; k < j; k++)
	{
		p = (Chunk*)malloc(sizeof(Chunk));
		if (!p)
			return 0;
		if (k == 0) // 第一个链块 
			(*T).head = q = p;
		else
		{
			q->next = p;
			q = p;
		}
		for (l = 0; l < CHUNKSIZE && *chars; l++)
			*(q->ch + l) = *chars++;
		if (!*chars) // 最后一个链块 
		{
			(*T).tail = q;
			q->next = NULL;
			for (; l < CHUNKSIZE; l++)// 用填补空余的字符（blank=‘#’）填满链表
				*(q->ch + l) = blank;
		}
	}
	return 1;
}
int StrEmpty(LString S)
{
	if (S.curlen)
		return 0;
	else
		return 1;
}
void StrPrint(LString T)// 输出字符串T
{
	int i = 0, j;
	Chunk* h;
	h = T.head;
	while (i < T.curlen)
	{
		for (j = 0; j < CHUNKSIZE; j++)
			if (*(h->ch + j) != blank) // 不是填补空余的字符 
			{
				printf("%c", *(h->ch + j));
				i++;
			}
		printf("\n");
		h = h->next;
	}
	printf("\n");
}
void chazhao(LString* T, char* chars, char* chars1)///查找和替换函数///
{
	Chunk* p, * q;
	int m = 0, c = 0, a = 1, b = 0, d = 0, a1 = 0, c1 = 0, c2 = 0, x = 0;
	char u;
	p = q = T->head;
	while (1)
	{
		if (c == CHUNKSIZE)
		{
			q = q->next;
			a++;
			c = 0;
		}
		for (x = 0; q->ch[c] == chars[m]; x++)
		{
			m++; c++;
			if (x == 0)
			{
				b = a; d = c - 1;
			}
			if (c == CHUNKSIZE)
			{
				q = q->next; c = 0;
			}
			if (chars[m] == '\0')//字符查完
			{
				printf("所查字符所在行位置是%d,第%d个位置开始\n", b, d + 1);
				printf("若需替换该字符，输入Y，否则输入N\n");
				scanf("%c", &u);
				fflush(stdin);
				if (u != 'N')
				{
					p = T->head;
					a = b; c = d;
					for (a1 = 1; a1 < a; a1++)
						p = p->next;
					q = p;
					for (; c1 < m; c1++)//替换后的字符chars1
					{
						if (c == CHUNKSIZE)
						{
							q = q->next;
							c = 0;
						}
						q->ch[c] = chars1[c2];
						c2++; c++;
					}
					c2 = 0; c1 = 0;
					StrPrint(*T);
				}//替换完毕
				c = d; a = b;
			}
		}
		if (!*(q->ch + c + 1 + m))//串查完/
		{
			printf("查找完成，已无匹配字符\n");
			break;
		}
		else
		{
			p = T->head;

			for (a1 = 1; a1 < a; a1++)
			{
				p = p->next; q = p;
			}
			c = c + 1; m = 0;
		}
	}
}
void main()
{
	char s1[n], s2[n], s3[n];//char *s3="22",*s2="aa";
	LString t1;
	int k, meum = 0, L, h;
	printf("\t=========说明：首先连续输入几个字符初始化串,以回车结束.==== ==\n");
	printf("\t=====================1：查看串的信息=====================\n\n");
	printf("\t=====================2：查找与替换=====================\n\n");
	printf("\t=====================3：退      出=====================\n\n");
	printf("请输入文本信息!\n");
	scanf("%s", &s1); fflush(stdin);
	L = strlen(s1);
	h = L / CHUNKSIZE; h++;
	InitString(&t1); printf("初始化串t1后， \n");
	k = StrAssign(&t1, s1);
	StrEmpty(t1);
	if (k == 1)
	{
		printf("串t1为:\n ");
		StrPrint(t1);
	}
	else
		printf("出错\n"); // 不能生成空串
	while (1)
	{
		printf("\t请输入命令!(参照说明)\n");
		scanf("%d", &meum); fflush(stdin);
		switch (meum)
		{
		case 1:
		{
			printf("初始化串t1后， \n");
			StrEmpty(t1);
			k = StrAssign(&t1, s1);
			if (k == 1)
			{
				printf("串t1为:\n ");
				StrPrint(t1);
			}
			else
				printf("出错\n"); // 不能生成空串
		}break;
		case 2:
		{
			printf("请输入查找的字符!\n");
			scanf("%s", &s2);
			fflush(stdin);
			printf("请输入替换后的字符!\n");
			scanf("%s", &s3);
			fflush(stdin);
			chazhao(&t1, s2, s3);
		}break;
		case 3: {exit(0); }break;
		default:
			printf("输入错误!!请重新输入!\n");
			break;
		}
	}
}