#include <iostream>
#include <cstring>
#include <stack>
#include <time.h> 
#include <stdlib.h>
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
double CalculateResult(char express[])
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
void scan1()
{
	
	cout<<"��ѡ���������ͣ����İ�������C��Ӣ�İ�������E ��"<<endl;
	cout<<"Please input the type of laungue which you want, if you choose Chinese,please input C,if you choose English,then input E." <<endl;
}
void scan2(char language)
{
	if(language=='C')
	{
		cout<<"������Ҫ���������⣻"<<endl;
	}
	if(language=='E')
	{
		cout<<"Please input the number of formula you want to calculate:"<<endl;
	}
}
void scan3(char language)
{
	if(language=='C')  cout<<"����������⣬������ ��q �� "<<endl;
	if(language=='E')  cout<<"If you want to quit, please input q"<<endl;
}

void print(char language,int right,int wrong,int wronganswer[],int i)
{
	if(language=='C')
		{
			cout << "\n����"<< right << "��"<<endl; 
		    cout << "����"<< wrong << "��"<<endl;
		}
		if(language=='E')
		{
			cout << "\n"<<right <<" is right"<<endl;
			cout <<  wrong <<" is wrong"<<endl;
		}
		if(language=='C') 
		{
			cout << "����� ";
		for(int k=0;k<wrong;k++)
		{
			cout << wronganswer[k] << "�� ";
		}
		cout << "��"<<endl;
		}
		if(language=='E')
		{
				cout << "NO. ";
		for( int k=0;k<wrong;k++)
		{
			cout << wronganswer[k] << "�� ";
		}
		cout << "is wrong"<<endl;
		}
		
		if(language=='C')
		{
			cout << "��ȷ��Ϊ" << right/i <<endl; 
		}
		if(language=='E')
		{
			cout << "The accuracy is " << right/i <<endl;
		}
}
char RandomNumber()
{
	return rand()%10+48;
}
char RandomOperation()
{
	return change(rand()%4);
}

int main()
{
	char language;scan1();
	cin >> language;
	char express[15];//���ʽ
	int i,j,k;
	double right=0,wrong=0;//��ȷ���ʹ������ļ��� 
	int n;//���� 
	int casenum;//�������ŵ������� 
	double answers[1000];//һ�γ��� ��ൽ��1000�⣬
	int inputanswer[1000];//����Ĵ�
	int wronganswer[1000];//����� 
	scan2(language);cin >> n;scan3(language);
	char a,b,c,d;//������� 
	char oper1,oper2,oper3;//�������� 
	srand((unsigned)time(NULL));//��������ͬ������� 

	for(i=0;i<n;i++)
	{
		a=RandomNumber();
		b=RandomNumber();
		c=RandomNumber();
		d=RandomNumber();
		oper1=RandomOperation();
		oper2=RandomOperation();
		oper3=RandomOperation();
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
		answers[i]=CalculateResult(express);//������ȷ�� 
		
		
		
		if(answers[i]==(int)answers[i]) //����Ƿ����С�� ��������� 
		{
			if(language=='C')
			{
				cout <<"��"<< i+1 <<"��  :"<<express ;
			}
			if(language=='E')
			{
				cout <<"NO. "<< i+1 << ": "<< express ;
			} 
			cin >> inputanswer[i];
			if(inputanswer[i]==answers[i]) 
			{
			right++;//��ȷ��++
			if(language=='C')
			cout << "	  ����ȷ"<<endl; 
			if(language=='E')
			cout << "	  	right"<<endl; 
			} 
			else 
			{
				wrong++;
				if(language=='C')
				cout << "	  �𰸴�����ȷ��Ϊ"<< answers[i]<<endl; 
				if(language=='E')
				cout << "	  	wrong��right anwer :"<< answers[i]<<endl;
				j=wrong-1;
				wronganswer[j]=i+1; 
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
	print(language,right,wrong,wronganswer,i);
		
	return 0;
}
