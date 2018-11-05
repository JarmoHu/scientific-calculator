#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

#define Pi 3.1415926

typedef struct
{
	float data[10];
	int top;	//ͷ��ַ
	int base;   //����ַ
	int length; //����
} Stack;

int isAvail(char temp);
int detect(char temp);
char Priority(float temp, char optr);
float evaluate1(float a, float b, char oper);
float evaluate2(float a, char oper);
int isOperate(char temp);
int isValue(char temp);
void initshuzhu(float (*shuzhu)[2]);
void inputexpress(char *express);
void zhuanhua(char *express, float (*shuzhu)[2]);
void push(float n, Stack *st);
float calculateExpress(float (*shuzhu)[2]);
void init(Stack *st);
float getTop(Stack *st);
float pop(Stack *st);
void gongneng1(void);
void gongneng2(void);
void gongneng3(void);

int jh = 1;
float jhs = 1;
int endend = 0; //�˳�

int main(void)
{
again:
	puts("��ӭʹ��!\n-------------------");
	printf("��ݼ�˵��:\nF1\tF2\tF3\tF4\t F5\t F6\t   F7\nsin\tcos\ttan\tarcsin\t arccos\t arctan\t   ^^^(�˷�)\n-------------------\n");
	switch (jh)
	{
	case 1:
		printf("��ǰΪ������\n");
		break;
	case 2:
		printf("��ǰΪ�Ƕ���\n");
		break;
	}
	printf("-------------------\n");
	printf("����ָ�����������в�ͬ����\n1������ת��\n2����ѧ������\n3��������/�Ƕ���ת��\n4���˳�\n-------------------\n");
	char gongneng;
	gongneng = getch();
	printf("\n");
	switch (gongneng)
	{
	case '1':
		gongneng1();
		system("cls");
		break;
	case '2':
		gongneng2();
		break;
	case '3':
		gongneng3();
		system("cls");
		break;
	case '4':
		goto end;
	default:
		printf("�����������ڿ���\n");
		system("pause");
		system("cls");
		break;
	}
	goto again;
end:
	printf("�ټ�!\n");
	system("pause");
}

void gongneng1(void)
{
	printf("����������ԭ�����ƣ�������ƣ���֧��2��8��10��16���ƣ�������0�˳���\n");
	int a, b = 0, yuanshu, shizhi = 0, jieguo = 0, i = 0;
	scanf("%d", &a);
	if (a == 0)
	{
		return;
	}
	scanf("%d", &b);
	printf("������ԭ��x=");
	switch (a)
	{
	case 8:
		scanf("%o", &shizhi);
		break;
	case 10:
		scanf("%d", &shizhi);
		break;
	case 16:
		scanf("%x", &shizhi);
		break;
	case 2:
		scanf("%d", &yuanshu);
		i = 0;
		while (yuanshu != 0)
		{
			shizhi += yuanshu % 2 * (int)pow(2, i);
			yuanshu = yuanshu / 10;
			i++;
		}
		break;
	}
	switch (b)
	{
	case 8:
		printf("%o\n", shizhi);
		break;
	case 10:
		printf("%d\n", shizhi);
		break;
	case 16:
		printf("%x\n", shizhi);
		break;
	case 2:
		i = 1;
		while (shizhi != 0)
		{
			jieguo += (shizhi % 2) * i;
			shizhi = shizhi / 2;
			i *= 10;
			;
		}
		printf("%d\n", jieguo);
		break;
	}
	system("pause");
}
void gongneng3(void)
{
	switch (jh)
	{
	case 1:
		jh = 2;
		jhs = (float)Pi / 180;
		break;
	case 2:
		jh = 1;
		jhs = 1;
		break;
	}
}

void gongneng2(void)
{
	printf("��������ʽ(����esc������һ�˵�)\n");
	char express[100];
	float shuzhu[100][2];
	initshuzhu(shuzhu);
	inputexpress(express);
	if (endend == 0)
	{
		zhuanhua(express, shuzhu);
		float result = calculateExpress(shuzhu);
		printf("=%.5f\n\n", result);
		system("pause");
		system("cls");
	}
	else
	{
		endend--;
		system("cls");
	}
}

void initshuzhu(float (*shuzhu)[2])
{
	for (int i = 0; i < 100; i++)
	{
		shuzhu[i][1] = 0;
		shuzhu[i][0] = 3;
	}
}

void zhuanhua(char *express, float (*shuzhu)[2])
{
	int i = 0, m = 0;
	while (express[i] != '\0')
	{
		if (isOperate(express[i]))
		{
			if (express[i] == '-' && i == 0 || express[i] == '-' && isOperate(express[i - 1]))
			{
				i++;
				shuzhu[m][1] = 0;
				shuzhu[m][0] = 0;
				while (isValue(express[i]))
				{
					shuzhu[m][1] = 10 * shuzhu[m][1] + express[i] - '0';
					i++;
				}
				if (express[i] == '.')
				{
					i++;
					int j = 1;
					while (isValue(express[i]))
					{
						shuzhu[m][1] += (float)(express[i] - '0') * pow(0.1, j++);
						i++;
					}
				}
				shuzhu[m][1] = shuzhu[m][1] * (-1);
				m++;
			}
			shuzhu[m][1] = express[i];
			shuzhu[m][0] = 1;
			i++;
			m++;
		}
		else
		{
			shuzhu[m][1] = 0;
			shuzhu[m][0] = 0;
			while (isValue(express[i]))
			{
				shuzhu[m][1] = 10 * shuzhu[m][1] + express[i] - '0';
				i++;
			}
			if (express[i] == '.')
			{
				i++;
				int j = 1;
				while (isValue(express[i]))
				{
					shuzhu[m][1] += (float)(express[i] - '0') * pow(0.1, j++);
					i++;
				}
			}
			m++;
		}
	}
}

void inputexpress(char *express)
{
	for (int i = 0; i < 100; i++)
	{
		int m, n;
		m = getch();
		if (m == 0)
		{
			printf("%c", m);
			express[i] = m;
			n = getch();
			switch (n)
			{
			case 59:
				express[i] = 's';
				printf("\b \bsin");
				break;
			case 60:
				express[i] = 'c';
				printf("\b \bcos");
				break;
			case 61:
				express[i] = 't';
				printf("\b \btan");
				break;
			case 62:
				express[i] = 'i';
				printf("\b \barcsin");
				break;
			case 63:
				express[i] = 'o';
				printf("\b \barccos");
				break;
			case 64:
				express[i] = 'a';
				printf("\b \barctan");
				break;
			case 65:
				express[i] = 'p';
				printf("\b \b^^^");
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				i++;
				express[i] = n;
				printf("%c", n);
				break;
			}
		}
		else if (m <= 57 && m >= 48)
		{
			express[i] = m;
			printf("%d", m - 48);
		}
		else if (m >= 40 && m <= 43 || m == 45 || m == 47)
		{
			express[i] = m;
			printf("%c", m);
		}
		else if (m == 27)
		{
			endend++;
			return;
		}
		else if (m == 8)
		{
			if (i == 0)
			{
			}
			else if (express[i - 1] == 'c' || express[i - 1] == 's' || express[i - 1] == 't' || express[i - 1] == 'p')
			{
				printf("\b\b\b   \b\b\b");
				express[i] = '\0';
				i--;
			}
			else if (express[i - 1] == 'i' || express[i - 1] == 'o' || express[i - 1] == 'a')
			{
				printf("\b\b\b\b\b\b      \b\b\b\b\b\b");
				express[i] = '\0';
				i--;
			}
			else
			{
				printf("\b \b");
				express[i] = '\0';
				i--;
			}
			i--;
		}
		else if (m == 's' || m == 'c' || m == 't' || m == '|' || m == '^' || m == '&' || m == '~' || m == '.' || m == '%')
		{
			switch (m)
			{
			case 's':
				express[i] = 's';
				printf("sin");
				break;
			case 'c':
				express[i] = 'c';
				printf("cos");
				break;
			case 't':
				express[i] = 't';
				printf("tan");
				break;
			case '|':
				express[i] = '|';
				printf("|");
				break;
			case '^':
				express[i] = '^';
				printf("^");
				break;
			case '&':
				express[i] = '&';
				printf("&");
				break;
			case '~':
				express[i] = 't';
				printf("~");
				break;
			case '.':
				express[i] = '.';
				printf(".");
				break;
			case '%':
				express[i] = '%';
				printf("%%");
				break;
			}
		}
		else if (m == 13)
		{
			express[i] = '#';
			express[i + 1] = '\0';
			break;
		}
		else
		{
			i--;
		}
	}
}

void init(Stack *st) //��ʼ��ջ
{
	st->base = 0;
	st->top = 0;
	st->length = 0;
}

int isEmpty(Stack *st)
{
	int n = 0, top, base;
	top = st->top;
	base = st->base;
	if (top == base)
	{
		return 1;
	}
	return n;
}

int isFull(Stack *st)
{
	int n = 0, top, base;
	top = st->top;
	if (top >= 4000)
	{
		return 1;
	}
	return n;
}

float getTop(Stack *st) // ����topֵ�����ı�ջ�Ľṹ
{
	float n;
	if (isEmpty(st))
	{
		return 0;
	}
	int positon = st->top - 1;
	n = st->data[positon]; //ȡ������;
	return n;
}

float pop(Stack *st) // ��ջ������
{
	float n;
	if (isEmpty(st))
	{
		printf("ջΪ��\n");
		return 0;
	}
	int positon = st->top - 1;
	n = st->data[positon]; //ȡ������;
	st->top--;
	st->length--;
	st->data[positon] = 0; //��������
	return n;
}

void push(float n, Stack *st) //��ջ
{
	int positon;
	if (isFull(st))
	{
		printf("ջ��\n");
	}
	else
	{
		positon = st->top;	 //��ȡλ��
		st->data[positon] = n; //��������
		st->top++;			   //�ı�λ��
	}
}

int isOperate(char temp) //�Ƿ��ǲ�����
{
	if (temp == '+' || temp == '~' || temp == '-' || temp == '*' || temp == '/' || temp == '(' || temp == ')' || temp == '#' || temp == 's' || temp == 'c' || temp == 't' || temp == 'i' || temp == 'o' || temp == 'a' || temp == 'p' || temp == '|' || temp == '^' || temp == '&' || temp == '%' || temp == '~')
	{
		return 1;
	}
	return 0;
}

int isValue(char temp) //�Ƿ�����ֵ
{
	if (temp >= '0' && temp <= '9') //

	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isAvail(char temp) //�Ƿ���Ч�ַ�
{
	if (isOperate(temp) || isValue(temp)) //���temp�Ȳ��ǲ���������ֵ�Ļ��������ǷǷ���

	{
		return 1;
	}
	return 0;
}

int detect(char temp) //��������λ��
{
	int i = 0;
	char oper[19] = {'|', '^', '&', '+', '-', '*', '/', '%', 's', 'c', 't', 'i', 'o', 'a', 'p', '~', '(', ')', '#'};
	for (i = 0; i < 19; i++)
	{
		if (temp == oper[i])
		{
			return i;
		}
	}
}

char Priority(float temp, char optr) //�ж����ȼ�
{
	int row, col;
	char priority[19][19] =
		{
			{'>', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '<', '<', '<', '<', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '<', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>'},
			{'>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '>', '=', '>'},
			{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '0', '>'},
			{'<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '<', '=', '0', '='},
		};

	row = detect((char)(int)temp); //�ҳ���Ӧ�ľ����±�;
	col = detect(optr);

	return priority[row][col];
}

float evaluate1(float a, float b, char oper) //˫Ŀ����
{
	switch (oper)
	{
	case '+':
		return (float)a + b;
	case '-':
		return (float)a - b;
	case '*':
		return (float)a * b;
	case '/':
		return (float)a / b;
	case '|':
		return ((int)a) | ((int)b);
	case '&':
		return ((int)a) & ((int)b);
	case '^':
		return ((int)a) ^ ((int)b);
	case 'p':
		return (float)powf(a, b);
	case '%':
		return (float)fmod(a, b);
	default:
		return 0;
	}
}

float evaluate2(float a, char oper) //��Ŀ����
{
	switch (oper)
	{
	case '~':
		return (float)(~(int)a);
	case 's':
		return (float)(sin(a * jhs));
	case 'c':
		return (float)(cos(a * jhs));
	case 't':
		return (float)(sin(a * jhs) / cos(a * jhs));
	case 'i':
		return (float)(asin(a) / jhs);
	case 'o':
		return (float)(acos(a) / jhs);
	case 'a':
		return (float)(atan(a) / jhs);
	}
}

float calculateExpress(float (*shuzhu)[2]) //������ʽ
{
	int result = 0;
	float a, b;
	Stack OPTR, OPND; //OPTR�洢��������OPND������ֵ
	init(&OPTR);
	init(&OPND);
	push('#', &OPTR); //Ĭ�ϵ�һ��λ'#'
					  ////////////////////-�㷨-////////////////////////////
	int i = 0;
	while (shuzhu[i][0] != 3)
	{
		float temp;
		temp = shuzhu[i][1];
		if (shuzhu[i][0] == 1) //������ǲ�����
		{
			float result;
			char oper;
			char optr = (char)getTop(&OPTR);   //ջ��topλ�Ĳ�����
			char prior = Priority(temp, optr); //�ж����ȼ�
			switch (prior)
			{
			case '>':
				push(temp, &OPTR);
				i++;
				break;
			case '<':
				switch (optr)
				{
				case '+':
				case '-':
				case '*':
				case '/':
				case '|':
				case '&':
				case '^':
				case 'p':
				case '%':
					a = pop(&OPND); //˫Ŀ����
					b = pop(&OPND);
					oper = (char)pop(&OPTR);
					result = evaluate1(b, a, oper); //��ջһ����������������
					push(result, &OPND);			//�����OPND
					break;
				case 's':
				case 't':
				case 'c':
				case 'i':
				case 'o':
				case 'a':
				case '~':
					a = pop(&OPND); //��Ŀ����
					oper = (char)pop(&OPTR);
					result = evaluate2(a, oper);
					push(result, &OPND);
					break;
				}
				break;
			case '=':
				//��������
				pop(&OPTR);
				i++;
				break;
			}
		}
		else //���������ֵ
		{
			push(temp, &OPND); //����ֵλ��ջ;
			i++;
		}
	}
	return getTop(&OPND);
}