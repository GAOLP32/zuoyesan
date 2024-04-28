#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define CHUNKSIZE 4 
#define n 26
char blank = '#';	// ȫ�ֱ���,���������    
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
void InitString(LString* T)// ��ʼ��(�����մ�)�ַ���T��
{
	(*T).curlen = 0;
	(*T).head = NULL;
	(*T).tail = NULL;
}
int StrAssign(LString* T, char* chars)// ����һ����ֵ����chars�Ĵ�T�� �ɹ�����1�����򷵻�0  
{
	int i, j, k, l;
	Chunk* p, * q;
	i = strlen(chars); // iΪ���ĳ��� 
	if (!i || strchr(chars, blank)) // ����Ϊ0��chars�а����������ַ� 
		return 0;
	(*T).curlen = i;
	j = i / CHUNKSIZE;	// jΪ�����Ľ��������ĸ��� 
	if (i % CHUNKSIZE)	//����һ����ģ�����һ���鼴������1
		j++;
	printf("������%d\n������%d\n", i, j);
	for (k = 0; k < j; k++)
	{
		p = (Chunk*)malloc(sizeof(Chunk));
		if (!p)
			return 0;
		if (k == 0) // ��һ������ 
			(*T).head = q = p;
		else
		{
			q->next = p;
			q = p;
		}
		for (l = 0; l < CHUNKSIZE && *chars; l++)
			*(q->ch + l) = *chars++;
		if (!*chars) // ���һ������ 
		{
			(*T).tail = q;
			q->next = NULL;
			for (; l < CHUNKSIZE; l++)// ���������ַ���blank=��#������������
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
void StrPrint(LString T)// ����ַ���T
{
	int i = 0, j;
	Chunk* h;
	h = T.head;
	while (i < T.curlen)
	{
		for (j = 0; j < CHUNKSIZE; j++)
			if (*(h->ch + j) != blank) // �����������ַ� 
			{
				printf("%c", *(h->ch + j));
				i++;
			}
		printf("\n");
		h = h->next;
	}
	printf("\n");
}
void chazhao(LString* T, char* chars, char* chars1)///���Һ��滻����///
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
			if (chars[m] == '\0')//�ַ�����
			{
				printf("�����ַ�������λ����%d,��%d��λ�ÿ�ʼ\n", b, d + 1);
				printf("�����滻���ַ�������Y����������N\n");
				scanf("%c", &u);
				fflush(stdin);
				if (u != 'N')
				{
					p = T->head;
					a = b; c = d;
					for (a1 = 1; a1 < a; a1++)
						p = p->next;
					q = p;
					for (; c1 < m; c1++)//�滻����ַ�chars1
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
				}//�滻���
				c = d; a = b;
			}
		}
		if (!*(q->ch + c + 1 + m))//������/
		{
			printf("������ɣ�����ƥ���ַ�\n");
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
	printf("\t=========˵���������������뼸���ַ���ʼ����,�Իس�����.==== ==\n");
	printf("\t=====================1���鿴������Ϣ=====================\n\n");
	printf("\t=====================2���������滻=====================\n\n");
	printf("\t=====================3����      ��=====================\n\n");
	printf("�������ı���Ϣ!\n");
	scanf("%s", &s1); fflush(stdin);
	L = strlen(s1);
	h = L / CHUNKSIZE; h++;
	InitString(&t1); printf("��ʼ����t1�� \n");
	k = StrAssign(&t1, s1);
	StrEmpty(t1);
	if (k == 1)
	{
		printf("��t1Ϊ:\n ");
		StrPrint(t1);
	}
	else
		printf("����\n"); // �������ɿմ�
	while (1)
	{
		printf("\t����������!(����˵��)\n");
		scanf("%d", &meum); fflush(stdin);
		switch (meum)
		{
		case 1:
		{
			printf("��ʼ����t1�� \n");
			StrEmpty(t1);
			k = StrAssign(&t1, s1);
			if (k == 1)
			{
				printf("��t1Ϊ:\n ");
				StrPrint(t1);
			}
			else
				printf("����\n"); // �������ɿմ�
		}break;
		case 2:
		{
			printf("��������ҵ��ַ�!\n");
			scanf("%s", &s2);
			fflush(stdin);
			printf("�������滻����ַ�!\n");
			scanf("%s", &s3);
			fflush(stdin);
			chazhao(&t1, s2, s3);
		}break;
		case 3: {exit(0); }break;
		default:
			printf("�������!!����������!\n");
			break;
		}
	}
}