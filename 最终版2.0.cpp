#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
using namespace std;
template <class T>
void StackClear(stack<T> &s)			//清空栈
{
	while(!s.empty())
		s.pop();
}
/*
判断读取到的字符是否是运算符
*/
int IsOperator(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '=':
			return 1;
			break;
		default:
			return 0;
			break;
	}
}
/*
比较前后两个运算符的优先级
(为了判断方便，增设一个等号“=”作为表达式的定界符)
oper1>=oper2返回1
oper1<oper2返回-1
oper1、oper2分别为左右括号返回0
*/
int Priority(char oper1,char oper2)
{
	int pri;
	switch(oper2)
	{
		case '+':
		case '-':
			if(oper1=='(' || oper1=='=')
				pri=-1;
			else
				pri=1;
			break;
		case '*':
		case '/':
			if(oper1=='*' || oper1=='/' || oper1==')')
				pri=1;
			else
				pri=-1;
			break;
		case '('://优先级小 
				pri=-1;
			break;

		case ')':
			if(oper1=='(')
				pri=0;		 //左右括号配对
			else
				pri=1;
			break;
		case '=':
			if(oper1=='=')
				pri=0;		//等号配对，返回0
			else
				pri=1;
			break;
	}
	return pri;
}
/*
根据运算符和两个操作数进行运算
*/
double calculate(double a,int oper,double b)
{
	switch(oper)
	{
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/':
			if (b!=0)
				return a/b;
			else
				return 0.1;//除0的情况返回成小数，然后在筛选题目时删除 

	}
}
/*
计算表达式的值：
初始化两个栈：一个操作数栈，一个运算符栈。
从左至右遍历每一个字符，遍历过程中遵循步骤和原则如下：
（1）遇到数字则直接压到数字栈顶。
（2）遇到运算符（+-* /）时，若操作符栈为空，则直接放到操作符栈顶，否则，见（3）。
（3）若操作符栈顶元素的优先级比当前运算符的优先级小，则直接压入栈顶，否则执行步骤（4）。
（4）弹出数字栈顶的两个数字并弹出操作符栈顶的运算符进行运算，把运算结果压入数字栈顶，重复（2）和（3）
	 直到当前运算符被压入操作符栈顶。
（5）遇到左括号“（”时则直接压入操作符栈顶。
（6）遇到右括号“）”时则依次弹出操作符栈顶的运算符运算数字栈的最顶上两个数字，直到弹出的操作符为左括号。
*/
double CalcExp(char express[])
{
	double a,b;				//两个操作数
	char opera;				//运算符
	char c;					//字符变量
	char x;					//x用来获取运算符栈栈顶的运算符
	stack<char> oper;
	stack<double> data;	//运算符栈栈顶的运算符，操作数栈
	int j=0;
	int i=0;
	oper.push('=');			//先将定界符(=)推入操作符栈
	c = express[i++];
	double num=0;
	while(c!='=' || x!='=')			//循环处理表达式中的每个字符
	{
		if(IsOperator(c))	//若是运算符
		{
			num = 0; 				//入栈之后清空某一个操作数的暂存值
			switch(Priority(x,c))
			{
				case -1:	//当前运算符c大于前一运算符x
					//cout << "o----" << c << endl;
					oper.push(c);		//当前运算符进栈
					c=express[i++];		//取表达式下一字符
					break;

				case 0:					//括号（等号）配对
					oper.pop();		//运算符左半部分出栈（抛弃）
					c=express[i++];		//取表达式下一字符
					break;
				case 1:						//当前运算符c小于等于前一运算符x
					opera = oper.top();		//出栈之前取得栈顶元素
					oper.pop();				//运算符出栈

					b = data.top();
					data.pop();
					a = data.top();
					data.pop();				//两个操作数出栈
					double t = calculate(a,opera,b);	//计算结果
					data.push(t);		//将结算结果入栈
					break;
			}
		}
		else if(c>='0' && c<='9')	//若输入的是数字字符 入栈
		{

			num=c-'0';
			data.push(num);
			c=express[i++];
		}

		x = oper.top();		//获取运算符栈顶的元素
	}
		num = data.top();	
		StackClear(oper);
		StackClear(data);		//清空两个栈
		return 	num;	//返回数字栈栈顶元素，即为计算结果
}

char change(int x)//随机数转变成运算符 
{
	switch(x)
	{
		case 0:return '+';
		case 1:return '-';
		case 2:return '*';
		default:return '/';
	}
}
int main()
{
	
	cout<<"请选择语言类型，中文版请输入C，英文版请输入E 。"<<endl;
	cout<<"Please input the type of laungue which you want, if you choose Chinese,please input C,if you choose English,then input E." <<endl;
	char language;
	srand((unsigned)time(NULL));//不出现相同的随机数 
	char express[15];//表达式
	int i,j;
	int n;//题数 
	int casenum;//有无括号的随机情况 
	double answers[1000];//一次程序 最多到达1000题，
	char a,b,c,d;//随机整数 
	char oper1,oper2,oper3;//随机运算符 
	cin >> language;
	if(language=='C')
	{
		cout<<"请输入要几个计算题；"<<endl;
	}
	if(language=='E')
	{
		cout<<"Please input the number of formula you want to calculate:"<<endl;
	}
	cin >> n;
	if(language=='C')  cout<<"若想结束答题，请输入 “q ” "<<endl;
	if(language=='E')  cout<<"If you want to quit, please input q "<<endl;

	for(i=0;i<n;i++)
	{
		a=rand()%10+48;
		b=rand()%10+48;
		c=rand()%10+48;
		d=rand()%10+48;
		oper1=change(rand()%4);
		oper2=change(rand()%4);
		oper3=change(rand()%4);
		casenum=rand()%6;//六种情况 
		switch(casenum)
		{
			case 0://无括号情况 
			express[0]=a;
			express[1]=oper1;
			express[2]=b;
			express[3]=oper2;
			express[4]=c;
			express[5]=oper3;
			express[6]=d;
			express[7]='=';break;
			case 1://(a o1 b)o2 c o3 g = ?
			express[0]='(';
			express[1]=a;
			express[2]=oper1;
			express[3]=b;
			express[4]=')';
			express[5]=oper2;
			express[6]=c;
			express[7]=oper3;
			express[8]=d;
			express[9]='=';	break;
			case 2://(a o1 b o2 c) o3 d = ?
			express[0]='(';
			express[1]=a;
			express[2]=oper1;
			express[3]=b;
			express[4]=oper2;
			express[5]=c;
			express[6]=')';
			express[7]=oper3;
			express[8]=d;
			express[9]='=';	
			break;
			case 3://a o1 ( b o2 c) o3 d = ?
			express[0]=a;
			express[1]=oper1;
			express[2]='(';
			express[3]=b;
			express[4]=oper2;
			express[5]=c;
			express[6]=')';
			express[7]=oper3;
			express[8]=d;
			express[9]='=';
			break;
			case 4://a o1 (b o2 c o3 d) = ?
			express[0]=a;
			express[1]=oper1;
			express[2]='(';
			express[3]=b;
			express[4]=oper2;
			express[5]=c;
			express[6]=oper3;
			express[7]=d;
			express[8]=')';
			express[9]='=';
			break;
			default://a o1 b o2 (c o3 d) =?
			express[0]=a;
			express[1]=oper1;
			express[2]=b;
			express[3]=oper2;
			express[4]='(';
			express[5]=c;
			express[6]=oper3;
			express[7]=d;
			express[8]=')';
			express[9]=	'=';
			
		}
		answers[i]=CalcExp(express);//储存正确答案 
		if(answers[i]==(int)answers[i]) //检查是否存在小数 ，结果检验 
		{
			if(language=='C')
			{
				cout <<"第"<< i+1 <<"题  :"<<express <<endl;
			}
			if(language=='E')
			{
				cout <<"NO. "<< i+1 << ": "<< express <<endl;
			} 
			for(j=0;j<=9;j++)//将表达式重新变为零 
			{
			express[j]='\0';
			}
		}
		else//如果答案为小数，则重新进行循环 
		{
			i=i-1;
			for(j=0;j<=9;j++)
			{
			express[j]='\0';
			}
			continue;
		}	
	}
		double right=0,wrong=0;//正确数和错误数的计算 
		int inputanswer[1000];//输入的答案
		int wronganswer[1000];//记录错误答案题号 
		int k;
		for(i=0;i<n;i++)
		{	
			
		    if(language=='C')
		    {
		    	cout <<"第" << i+1 << "题答案： "; 
			}
			if(language=='E')
			{
				cout<<"The answer of NO." << i+1 <<" is ";
			}
			cin >> inputanswer[i];                           //输入答案 
			if(inputanswer[i]==answers[i]) 
			{
			right++;//正确则++
			if(language=='C')
			cout << "	  答案正确"<<endl; 
			if(language=='E')
			cout << "	  	right"<<endl; 
			} 
			else 
			{
				wrong++;
				if(language=='C')
				cout << "	  答案错误，正确答案为"<< answers[i]<<endl; 
				if(language=='E')
				cout << "	  	wrong，right anwer :"<< answers[i]<<endl;
				k=wrong-1;
				wronganswer[k]=i+1; 
			}
		}
		if(language=='C')
		{
			cout << "\n对了"<< right << "题"<<endl; 
		    cout << "错了"<< wrong << "题"<<endl;
		}
		if(language=='E')
		{
			cout << "\n"<<right <<" is right"<<endl;
			cout <<  wrong <<" is wrong"<<endl;
		}
		if(language=='C') 
		{
			cout << "做错第 ";
		for( k=0;k<wrong;k++)
		{
			cout << wronganswer[k] << "、 ";
		}
		cout << "题"<<endl;
		}
		if(language=='E')
		{
				cout << "NO. ";
		for( k=0;k<wrong;k++)
		{
			cout << wronganswer[k] << "、 ";
		}
		cout << "is wrong"<<endl;
		}
		
		if(language=='C')
		{
			cout << "正确率为" << right/i <<endl; 
		}
		if(language=='E')
		{
			cout << "The accuracy is " << right/i <<endl;
		}
	return 0;
}
