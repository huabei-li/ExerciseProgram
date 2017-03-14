#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
#include<fstream>
#include<string>
#include<cmath>
using namespace std;
template <class T>
void StackClear(stack<T> &s)			//���ջ
{
	while(!s.empty())
		s.pop();
}
/*
�ж϶�ȡ�����ַ��Ƿ��������
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
�Ƚ�ǰ����������������ȼ�
(Ϊ���жϷ��㣬����һ���Ⱥš�=����Ϊ���ʽ�Ķ����)
oper1>=oper2����1
oper1<oper2����-1
oper1��oper2�ֱ�Ϊ�������ŷ���0
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
		case '('://���ȼ�С 
				pri=-1;
			break;

		case ')':
			if(oper1=='(')
				pri=0;		 //�����������
			else
				pri=1;
			break;
		case '=':
			if(oper1=='=')
				pri=0;		//�Ⱥ���ԣ�����0
			else
				pri=1;
			break;
	}
	return pri;
}
/*
�����������������������������
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
				return 0.1;//��0��������س�С����Ȼ����ɸѡ��Ŀʱɾ�� 

	}
}
/*
������ʽ��ֵ��
��ʼ������ջ��һ��������ջ��һ�������ջ��
�������ұ���ÿһ���ַ���������������ѭ�����ԭ�����£�
��1������������ֱ��ѹ������ջ����
��2�������������+-* /��ʱ����������ջΪ�գ���ֱ�ӷŵ�������ջ�������򣬼���3����
��3����������ջ��Ԫ�ص����ȼ��ȵ�ǰ����������ȼ�С����ֱ��ѹ��ջ��������ִ�в��裨4����
��4����������ջ�����������ֲ�����������ջ����������������㣬��������ѹ������ջ�����ظ���2���ͣ�3��
	 ֱ����ǰ�������ѹ�������ջ����
��5�����������š�����ʱ��ֱ��ѹ�������ջ����
��6�����������š�����ʱ�����ε���������ջ�����������������ջ������������֣�ֱ�������Ĳ�����Ϊ�����š�
*/
double CalcExp(char express[])
{
	double a,b;				//����������
	char opera;				//�����
	char c;					//�ַ�����
	char x;					//x������ȡ�����ջջ���������
	stack<char> oper;
	stack<double> data;	//�����ջջ�����������������ջ
	int j=0;
	int i=0;
	oper.push('=');			//�Ƚ������(=)���������ջ
	c = express[i++];
	double num=0;
	while(c!='=' || x!='=')			//ѭ��������ʽ�е�ÿ���ַ�
	{
		if(IsOperator(c))	//���������
		{
			num = 0; 				//��ջ֮�����ĳһ�����������ݴ�ֵ
			switch(Priority(x,c))
			{
				case -1:	//��ǰ�����c����ǰһ�����x
					//cout << "o----" << c << endl;
					oper.push(c);		//��ǰ�������ջ
					c=express[i++];		//ȡ���ʽ��һ�ַ�
					break;

				case 0:					//���ţ��Ⱥţ����
					oper.pop();		//�������벿�ֳ�ջ��������
					c=express[i++];		//ȡ���ʽ��һ�ַ�
					break;
				case 1:						//��ǰ�����cС�ڵ���ǰһ�����x
					opera = oper.top();		//��ջ֮ǰȡ��ջ��Ԫ��
					oper.pop();				//�������ջ

					b = data.top();
					data.pop();
					a = data.top();
					data.pop();				//������������ջ
					double t = calculate(a,opera,b);	//������
					if(t!=(int)t) 		//�����0�ٳ������� 
					return 0.1;
					else 
					data.push(t);		//����������ջ
					break;
			}
		}
		else if(c>='0' && c<='9')	//��������������ַ� ��ջ
		{

			num=c-'0';
			data.push(num);
			c=express[i++];
		}

		x = oper.top();		//��ȡ�����ջ����Ԫ��
	}
		num = data.top();	
		StackClear(oper);
		StackClear(data);		//�������ջ
		return 	num;	//��������ջջ��Ԫ�أ���Ϊ������
}

char change(int x)//�����ת�������� 
{
	switch(x)
	{
		case 0:return '+';
		case 1:return '-';
		case 2:return '*';
		default:return '/';
	}
}
void Choose(char c,int a)//����ѡ�� 
{
	string s;
	int sb;
	ifstream inf;	//��ȡ�ļ� 
	if(c=='C')
		inf.open("e://CAL//Chinese.txt");//������Դ·�� 
	if(c=='E')
		inf.open("e://CAL//English.txt");
	if(c=='J')
		inf.open("e://CAL//Japanese.txt");
	if(c=='F')
		inf.open("e://CAL//French.txt");
	if(c=='G')
		inf.open("e://CAL//German.txt");
	switch(a)//�ж���������ı��� 
	{
		case 1:	getline(inf,s,'\n'); 
			   	cout <<s<<endl;
				getline(inf,s,'\n');
				cout <<s<<endl; 
				getline(inf,s,'\n'); 
				cout <<s;
				break;
		case 2:	for(sb=0;sb<4;sb++)
				getline(inf,s,'\n'); 
			   	cout <<s;
				break;
		case 3:	for(sb=0;sb<5;sb++)
				getline(inf,s,'\n'); 
			   	cout <<s<<endl;
				break;
		case 4:	for(sb=0;sb<6;sb++)
				getline(inf,s,'\n'); 
			   	cout <<s;
				break;
	}
	inf.close();//�ر��ļ�	
}
int main()
{
	
	cout<<"��ѡ��������:"<<endl;
	cout<<"C.����	E.Ӣ��	J.����	F.����	G.����" <<endl;
	char language;
	srand((unsigned)time(NULL));//��������ͬ������� 
	char express[15];//���ʽ
	int i,j,k;
	double right=0;//��ȷ���ļ��� 
	int n;//���� 
	int casenum;//�������ŵ������� 
	double answers;//һ�γ��� ��ൽ��1000�⣬
	int inputanswer;//����Ĵ�
	char a,b,c,d;//������� 
	char oper1,oper2,oper3;//�������� 
	cin >> language;
	Choose(language,1);
	cin >> n;
	for(i=0;i<n;i++)
	{
		a=rand()%10+48;
		b=rand()%10+48;
		c=rand()%10+48;
		d=rand()%10+48;
		oper1=change(rand()%4);
		oper2=change(rand()%4);
		oper3=change(rand()%4);
		casenum=rand()%6;//������� 
		switch(casenum)
		{
			case 0://��������� 
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
		answers=CalcExp(express);//������ȷ�� 
		if(answers==(int)answers) //����Ƿ����С�� ��������� 
		{
			cout << i+1 <<".  "<<express ;
			cin >> inputanswer;
			if(inputanswer==answers) 
			{
			right++;//��ȷ��++
			Choose(language,3);	
			} 
			else 
			{
				Choose(language,2);
				cout << answers<<endl; 
			}
			for(j=0;j<=9;j++)//�����ʽ���±�Ϊ�� 
			{
			express[j]='\0';
			}
		}
		else//�����ΪС���������½���ѭ�� 
		{
			i=i-1;
			for(j=0;j<=9;j++)
			{
			express[j]='\0';
			}
			continue;
		}	
	}	
		Choose(language,4);
		cout << right/i <<endl; 
	return 0;
}
