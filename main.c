#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

#define Pi 3.1415926

typedef struct
{
	float data[10];
	int top;	//头地址
	int base;   //基地址
	int length; //长度
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
int endend = 0; //退出

int main(void)
{
again:
	puts("欢迎使用!\n-------------------");
	printf("快捷键说明:\nF1\tF2\tF3\tF4\t F5\t F6\t   F7\nsin\tcos\ttan\tarcsin\t arccos\t arctan\t   ^^^(乘方)\n-------------------\n");
	switch (jh)
	{
	case 1:
		printf("当前为弧度制\n");
		break;
	case 2:
		printf("当前为角度制\n");
		break;
	}
	printf("-------------------\n");
	printf("输入指定按键可运行不同功能\n1、进制转换\n2、科学计算器\n3、弧度制/角度制转换\n4、退出\n-------------------\n");
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
		printf("其他功能正在开发\n");
		system("pause");
		system("cls");
		break;
	}
	goto again;
end:
	printf("再见!\n");
	system("pause");
}

void gongneng1(void)
{
	printf("请依次输入原数进制，结果进制（仅支持2、8、10、16进制）（输入0退出）\n");
	int a, b = 0, yuanshu, shizhi = 0, jieguo = 0, i = 0;
	scanf("%d", &a);
	if (a == 0)
	{
		return;
	}
	scanf("%d", &b);
	printf("请输入原数x=");
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
	printf("请输入表达式(输入esc返回上一菜单)\n");
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

void init(Stack *st) //初始化栈
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

float getTop(Stack *st) // 返回top值，不改变栈的结构
{
	float n;
	if (isEmpty(st))
	{
		return 0;
	}
	int positon = st->top - 1;
	n = st->data[positon]; //取出数据;
	return n;
}

float pop(Stack *st) // 出栈，返回
{
	float n;
	if (isEmpty(st))
	{
		printf("栈为空\n");
		return 0;
	}
	int positon = st->top - 1;
	n = st->data[positon]; //取出数据;
	st->top--;
	st->length--;
	st->data[positon] = 0; //消除数据
	return n;
}

void push(float n, Stack *st) //入栈
{
	int positon;
	if (isFull(st))
	{
		printf("栈满\n");
	}
	else
	{
		positon = st->top;	 //获取位置
		st->data[positon] = n; //存入数据
		st->top++;			   //改变位置
	}
}

int isOperate(char temp) //是否是操作符
{
	if (temp == '+' || temp == '~' || temp == '-' || temp == '*' || temp == '/' || temp == '(' || temp == ')' || temp == '#' || temp == 's' || temp == 'c' || temp == 't' || temp == 'i' || temp == 'o' || temp == 'a' || temp == 'p' || temp == '|' || temp == '^' || temp == '&' || temp == '%' || temp == '~')
	{
		return 1;
	}
	return 0;
}

int isValue(char temp) //是否是数值
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

int isAvail(char temp) //是否有效字符
{
	if (isOperate(temp) || isValue(temp)) //如果temp既不是操作符和数值的话，则它是非法的

	{
		return 1;
	}
	return 0;
}

int detect(char temp) //搜索矩阵位置
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

char Priority(float temp, char optr) //判断优先级
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

	row = detect((char)(int)temp); //找出对应的矩阵下标;
	col = detect(optr);

	return priority[row][col];
}

float evaluate1(float a, float b, char oper) //双目运算
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

float evaluate2(float a, char oper) //单目运算
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

float calculateExpress(float (*shuzhu)[2]) //计算表达式
{
	int result = 0;
	float a, b;
	Stack OPTR, OPND; //OPTR存储操作符，OPND操作数值
	init(&OPTR);
	init(&OPND);
	push('#', &OPTR); //默认第一个位'#'
					  ////////////////////-算法-////////////////////////////
	int i = 0;
	while (shuzhu[i][0] != 3)
	{
		float temp;
		temp = shuzhu[i][1];
		if (shuzhu[i][0] == 1) //输入的是操作符
		{
			float result;
			char oper;
			char optr = (char)getTop(&OPTR);   //栈中top位的操作符
			char prior = Priority(temp, optr); //判断优先级
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
					a = pop(&OPND); //双目运算
					b = pop(&OPND);
					oper = (char)pop(&OPTR);
					result = evaluate1(b, a, oper); //出栈一个操作符，计算结果
					push(result, &OPND);			//结果入OPND
					break;
				case 's':
				case 't':
				case 'c':
				case 'i':
				case 'o':
				case 'a':
				case '~':
					a = pop(&OPND); //单目运算
					oper = (char)pop(&OPTR);
					result = evaluate2(a, oper);
					push(result, &OPND);
					break;
				}
				break;
			case '=':
				//消除括号
				pop(&OPTR);
				i++;
				break;
			}
		}
		else //输入的是数值
		{
			push(temp, &OPND); //将数值位入栈;
			i++;
		}
	}
	return getTop(&OPND);
}