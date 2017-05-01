#include <string>
#include <iostream>
#include <cstdlib>
#include "Generated.h"
using namespace std;

// 随机符号
char randomOperation()
{
	int n = rand() % 4;
	char sym;
	switch (n)
	{
		case 0: sym = '+'; break;
		case 1: sym = '-'; break;
		case 2: sym = '*'; break;
		case 3: sym = '/'; break;
	}
	return sym;
}

// 随机数字
int randomNumber()
{
	int num;
	num = rand()%10+1;
	return num;
}


// 随机括号
string bracket(string n)
{
	int random = rand() % 2;
	if (random == 1)
	{
		n = '(' + n + ')';
	}
	return n;
}

// 数字转字符串
string int_str(int number)
{
	char str[3];
	_itoa_s(number, str, 10);
	string i_s = str;
	return i_s;
}

// 连接数字运算符
string connect(string str1, string str2, char s)
{
	string equ = str1 + s + str2;
	return equ;
}


string generateExpression()
{
	char symbol;
	int n1, n2, i, exchange;
	string str_n1, str_n2, equation, temp;
	n1 = randomNumber();;
	n2 = randomNumber();
	symbol = randomOperation();
	str_n1 = int_str(n1);
	str_n2 = int_str(n2);
	equation = connect(str_n1, str_n2, symbol);
	for (i = 0; i < 2; i++)
	{
		str_n1 = equation;
		str_n1 = bracket(equation);
		n2 = randomNumber();
		str_n2 = int_str(n2);
		
		// 对字符串位置进行随机交换
		exchange = rand() % 2;
		if (exchange == 1)
		{
			temp = str_n1;
			str_n1 = str_n2;
			str_n2 = temp;
		}
		symbol = randomOperation();
		equation = connect(str_n1, str_n2, symbol);
	}
	return equation;
}