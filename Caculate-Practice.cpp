#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <map> 
#include <fstream>
using namespace std;

string equation[100];
float answer[100];
float input[100];
char LanguageRead[20][200];
char location[100]="";
int t=0,f,count;

// 随机符号
char randomOperation()
{
    int n = rand()%4;
    char sym;
    switch(n)
    {
        case 0: sym='+';break;
        case 1: sym='-';break;
        case 2: sym='*';break;
        case 3: sym='/';break;
    }
return sym;
}

// 随机符号
string bracket(string n)
{
    int random=rand()%2;
    if (random==1)
    {
        n='('+n+')';
    }
return n; 
}

// 数字转字符串
string int_str(int number)
{
    char str[1];
    itoa(number,str,10);
    string i_s = str;
return i_s;
}

// 连接数字运算符
string connect(string str1,string str2,char a)
{
    string equ = str1+a+str2;
return equ;
}

// 将中缀表达式转换成后缀表达式
string InfixToPostfix(string infix)
{
    char current = 0;
    string postfix;//后缀表达式

    stack<char> mark;//符号栈

    map<char,int> priority;//符号优先级
    priority['+'] = 0;
    priority['-'] = 0;
    priority['*'] = 1;
    priority['/'] = 1;

    for(int i = 0;i < infix.size(); ++i)
    {
        current = infix[i];
        switch(current)
        {
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.':
                postfix.push_back(current);//数字直接写入
                break;
            case '+':case '-':case '*':case '/':
                //如果运算符的前一项不是右括号即说明前一个数字输入完毕，用#标识
                if(infix[i-1] != ')')
                    postfix.push_back('#');
                //如果符号栈非空，即比较目前符号与栈顶符号优先级，低于等于出栈(并写入输出字符串)，
                //直至符号全部出栈或者遇到了'('或者大于栈顶符号的优先级
                if(!mark.empty())
                {
                    char tempTop = mark.top();
                    while(tempTop != '(' && priority[current] <= priority[tempTop])
                    {
                        postfix.push_back(tempTop);
                        mark.pop();
                        if(mark.empty())
                            break;
                        tempTop = mark.top();
                    }
                }
                mark.push(current);//新符号入栈
                break;
            case '(':
                if(infix[i-1] >= '0' && infix[i-1] <= '9')// for expression 2-5*2(6/2)
                {
                    postfix.push_back('#');
                    mark.push('*');
                }
                mark.push(current);
                break;
            case ')':
                postfix.push_back('#');//右括号说明前方数字输入完成，标识一下
                while(mark.top() != '(')
                {
                    postfix.push_back(mark.top());
                    mark.pop();
                }
                mark.pop();//左括号出栈
                break;
            default:
                break;//忽略其他字符
        }
    }
    if(infix[infix.size()-1] != ')')
        postfix.push_back('#');//中缀表达式最后一个是数字需要加上#。
    while(!mark.empty())//如果栈非空，全部出栈并写入输出字符串
    {
	    postfix.push_back(mark.top());
        mark.pop();
    }
    return postfix;
}

// 计算后缀表达式
float posfixCompute(string s)
{
    stack<float> tempResult;

    string strNum;
    float currNum = 0;

    float tempNum = 0;
    for(string::const_iterator i = s.begin(); i != s.end(); ++i)
    {
        switch(*i)
        {
            case '0':case '1':case '2':case '3':case '4':case '5':
            case '6':case '7':case '8':case '9':case '.':
                strNum.push_back(*i);
                break;
            case '+':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum += tempResult.top();
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '-':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum = tempResult.top() - tempNum;
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '*':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum *= tempResult.top();
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '/':
                tempNum = tempResult.top();
                tempResult.pop();
                tempNum = tempResult.top() / tempNum;
                tempResult.pop();
                tempResult.push(tempNum);
                break;
            case '#':
                currNum = atof(strNum.c_str());
                strNum.clear();
                tempResult.push(currNum);
                break;
        }
    }
    return tempResult.top();
}


//语言列表
void LanguageList()
{
    int num = 1;
    char Language[20];
    fstream file;
    file.open("language\\Languagelist.txt");

    while(file.getline(Language,20))
    {
        cout<<num<<"."<<Language<<endl;
        num++;
    }

    file.close();
}

bool JudgeLanguage(char *llanguage)
{
    
    strcat(location,"language\\");
    strcat(location,llanguage);
    strcat(location,".txt");

    fstream file;
    file.open(location);

    if (file.is_open())
    {
        file.close();
        return true;
    }
    else
        return NULL;
}

//将文件读入数组中
void dispose(char *location)
{
    fstream File;
    File.open(location);
    
    int i;
    for (i = 0;File.getline(LanguageRead[i],200);  ++i)
    {}
    File.close();
}



// 表达式计算
float calculateResult(string s)
{
    return posfixCompute(InfixToPostfix(s));
}


//记录正确题数
void scan(float answer,float input) 
{
    if(answer==input)
    {
        t++;
        cout<<LanguageRead[2]<<endl;
    }
    else
    {
        cout<<LanguageRead[3]<<answer<<endl;       
    }
}

//显示结果 
void result(int t,int f)
{
    char end;
    cout<<LanguageRead[4]<<endl;
    cin>>end;
    if(end=='Q'||end=='q')
    {
        cout<<LanguageRead[5]<<t<<LanguageRead[7]<<endl;
        cout<<LanguageRead[6]<<f<<LanguageRead[7]; 
    }          
}

void generateExpression(string equation[100],float answer[100],float input[100])
{
    char symbol,end;
    int n1,n2,i,j,exchange,temp2;
    string str_n1,str_n2,temp;
    n1=rand()%10+1;
    n2=rand()%10+1;
    symbol=randomOperation();
    str_n1=int_str(n1);
    str_n2=int_str(n2);
    equation[i]=connect(str_n1,str_n2,symbol);
    for (j = 0; j < 2; j++)
    {           
        str_n1=equation[i];
        str_n1=bracket(equation[i]);
        n2=rand()%10+1;
        str_n2=int_str(n2);
        // 对字符串位置进行随机交换
        exchange=rand()%2;
        if (exchange==1)
        {
            temp=str_n1;
            str_n1=str_n2;
            str_n2=temp;
        }
        symbol=randomOperation();
        equation[i]=connect(str_n1,str_n2,symbol);
    }
    cout<<'<'<<i+1<<">. "<<equation[i]<<'=';
    cin>>input[i];
    answer[i]=calculateResult(equation[i]);
    //四舍五入保留两位小数
    temp2=(int)(answer[i]*100+0.5f);
    answer[i]=(float)temp2/100;
    //正确题目数量和是否正确的提示
    scan(answer[i],input[i]);
}

int main()
{
    srand(unsigned(time(0)));
    char clanguage[1];
    int i,temp2;
    cout<<"Enter the serial number to select the language."<<endl;
    cout<<"============================================================================"<<endl;
    LanguageList();
    cout<<"============================================================================"<<endl;
    cin>>clanguage;
    while(JudgeLanguage(clanguage)==false)
    {
        cout<<"Your input is wrong or software does not support your language.  "<<endl;
        cin>>clanguage;
    }        
    dispose(location);
    cout<<LanguageRead[0]<<endl;
    cout<<LanguageRead[1];
    cin>>count;
    
    for (i = 0; i < count; i++)
    {
        generateExpression(equation,answer,input);
    }
    f=count-t; 
    result(t,f);
return 0;
}
