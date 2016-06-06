#include<stdio.h>
#include<stdlib.h>
#include<string.h>
////////////////////////////存放归约步骤的一个整形数组///////////////////////////////
int step_result[1000];//存放归约步骤的一个全局数组
int step_result_len=0;//统计全局数组的长度每次清零应该
////////////////////////////////定义文法符号优先表用int型矩阵表示///////////////////
int Matux[8][8]={{1,1,-1,-1,-1,1,-1,1},{1,1,-1,-1,-1,1,-1,1},{1,1,1,1,-1,1,-1,1},{1,1,1,1,-1,1,-1,1},     
             {-1,-1,-1,-1,-1,0,-1,-3},{1,1,1,1,-2,1,-2,1},{1,1,1,1,-2,1,-2,1},{-1,-1,-1,-1,-1,-4,-1,0}};   
char *STR[6]={"N+N","N-N","N*N","N/N","(N)","i"};//定义文法可规约可归约字符串
char stack[100];//定义符号栈
int stack_len=0;//定义初始化符号栈的长度为0
int Getchar_len=0;//定义取得字符的全局在窜中的变量
////////////////////////////////////////////////////////////////////////////////////////
bool IsLetter(char ch)//判断当前ch是否为字符///////////////////////////////////////////
{
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	{
		return 1;//如果ch是字母则返回1
	}
	else
	{
		return 0;//如果不是字母则返回0
	}
}
bool IsDigit(char ch)//判断当前ch是否为数字/////////////////////////////////////////////
{
	if(ch>='0'&&ch<='9')
	{
		return 1;//如果ch是数字则返回1
	}
	else
	{
		return 0;//如果不是数字则返回0
	}
}
/////////////////////求出终结符对应的优先表矩阵中的行列位置的函数//////////////////////
int Find_two_table(char ch)//求出对应的优先表的行数和列数的一个函数
{
	switch(ch)
	{
	   case '+': return 0;
	   case '-': return 1;
	   case '*': return 2;
	   case '/': return 3;
	   case '(': return 4;
	   case ')': return 5;
	   case 'i': return 6;
	   case '#': return 7;
       default:  return -1;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////根据预处理求出算数分析的表达式存放在一个二维数组里面的一个函数///////////////
int Find_num_string(char num_string[100][100])
{   
	int i,j,flag;
	char ch,old_ch=' ',string[20];
	FILE *fp;
	printf("您好!请您输入预处理程序的文件名称:");
	gets(string);
	if((fp=fopen(string,"r"))==NULL) //打开文件，如果打开失败则提示
	{
		printf("您打开的文件不存在,请您重新打开文件\n");//文件打开失败 提示打开的文件不存在
	}
	i=0;
	while(!feof(fp))
	{
		j=0;
		ch=fgetc(fp);
		while(ch!='='&&!feof(fp))
		{
			old_ch=ch;
			ch=fgetc(fp);		
		}
		if(old_ch!='>'&&old_ch!='<'&&old_ch!='!')
		{
			ch=fgetc(fp);
			if(ch!='=')
			{
				while(ch!=';'&&!feof(fp))
				{
					num_string[i][j]=ch;
					ch=fgetc(fp);
					j++;
				}
				i++;
				num_string[i][j]='\0';
			}
		}
	}
	flag=i-1;
	fclose(fp);
	return flag;
}
/////////////////////////将求出的算术表达式转化成可输入串的函数/////////////////////////
void Convert_input_string(char num_string[100],char input_string[100])
{
	int i=0,i_input_str=0;
	char ch,flag_ch;
/////////////////////begin////////////////////////////////
	ch=num_string[i];
	while(ch!='\0')
	{
		if(IsDigit(ch))
		{
			flag_ch='0';
		}
	   	else
		{
	     	if(IsLetter(ch))
			{
				flag_ch='a';
			}
		    else
			{
				flag_ch=ch;
			}
		}
	   	switch(flag_ch)
		{
		   case 'a':
			   {   
				   while((IsLetter(ch)||IsDigit(ch)||ch=='_')&&ch!='\0')
				   {
					   i++;
					   ch=num_string[i];
				   }
				   input_string[i_input_str]='i';
				   i--;
				   break;
			   }
	       case '0':
			   {
				   while((IsDigit(ch)||ch=='.')&&ch!='\0')
				   {
					   i++;
					   ch=num_string[i];			   
				   }
			       input_string[i_input_str]='i'; 
				   i--;
				   break;
			   }
		   case ' ':
			   {
				   break;
			   }
	       default :
			   {
				   input_string[i_input_str]=ch;
				   break;
			   }
		}
	    i++;
		ch=num_string[i];
		if(ch!=' ')
		{
			i_input_str++;
		}
		
	}
	input_string[i_input_str]='#';
//////////////////////end///////////////////////
	return;
}
////////////////////自动取得是规约串中字符的一个函数///////////////////
char Getchar(char input_string[100])
{
	char ch;
	int i,len;
	char input_string_temp[100]={'\0'};
	len=strlen(input_string);
	ch=input_string[0];
	for(i=1;i<len;i++)
	{
		input_string_temp[i-1]=input_string[i];
		if(input_string[i-1]=='#')
		{
			break;
		}
	}
	strcpy(input_string,input_string_temp);
	return ch;
}
//////////////////////判断是否是终结符///////////////////////////////
bool Char_IsVt(char ch)
{
	if(Find_two_table(ch)>=0&&Find_two_table(ch)<=9)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
///////////////////////判断终结符之间的优先关系的一个函数////////////////
int Find_relaion(char stack_ch,char ch)//找出终结符之间的优先关系的一个函数
{
	int row,lie,result;
	row=Find_two_table(stack_ch);
	lie=Find_two_table(ch);
	if((lie<0||lie>7)&&ch!='N')
	{
//		printf("非法标识符%c",ch);
		return -10;
	}
	result=Matux[row][lie];
	return result;//返回终结符对应的行数或者是列数
}
////////////////////////////出错处理子程序///////////////////////////////
void Process_Error(int return_num)
{
	if(return_num==-2)//出错处理函数,一共有三种错误情况
	{
		printf("Error!算术表达式缺少运算符,请查看更改!\n");
	}
	else
	{
		if(return_num==-3)
		{
			printf("Error!算术表达式缺少右括号,请查看更改!\n");
		}
		else
		{
			if(return_num==-4)
			{
				printf("Error!算术表达式缺少左括号,请查看更改!\n");
			}
		}
	}
	return;//函数结束
}
////////////////////处理一个算术表达式的规约过程的函数///////////////////
void main_analyous(char input_string[100])
{
	int k,step=1,i,j,flag=0,p;int flag_temp=0,input_string_len;
	char ch,q_ch;
	char stack[100]={'\0'},temp_str[20]={'\0'};
	k=1;
	stack[k]='#';
    printf("步骤号   动作  优先关系 当前分析符  符号栈      剩余输入串\n");
    printf("   1     预备      <                  #           %s\n",input_string);
	ch=Getchar(input_string);
	char stack_pop=' ';
	while(stack_pop!='#')
	{
		if(Char_IsVt(ch))
		{
			j=k;
		}
		else
		{
			j=k-1;
		}
		int error;
//////////////////判断输入串中是不是存在非法符号的存在则返回-10/////////////
        error=Find_relaion(stack[j],ch);
		if(error==(-10))
		{
			printf("输入串中存在非法符号%c,输入串分析结束!\n",ch);
			return;
		}
///////////////////////////////////////////////////////////////////////////
		while(Find_relaion(stack[j],ch)==1)
		{
			for(int h=0;h<20;h++)//每次规约过程中存放可归约变量清零
			{
				temp_str[h]='\0';
			}
			flag=0;//////////////////每次规约flag清零//////////////////
			do
			{
				q_ch=stack[j];
				if(Char_IsVt(stack[j-1]))
				{
					j=j-1;
				}
				else
				{
					j=j-2;
				}
			}while((Find_relaion(stack[j],q_ch)==1)||(Find_relaion(stack[j],q_ch)==0));
/////////////////////////////////////////////////////////////////////////
			p=j+1;
			temp_str[flag]=stack[p];//将stack[j+1]的字符给临时数组temp+str中进行和产生式右部进行比较
			while(p<k)//循环一直到stack[j+1]==stack[k]结束
			{
				p=p+1;
				flag++;
				temp_str[flag]=stack[p];			
			}
			for(i=0;i<6;i++)
			{
				if(strcmp(temp_str,STR[i])==0)
				{
					while(p<k)//循环一直到stack[j+1]==stack[k]结束每次规约的时候同时讲规约部分的栈清空
					{
						p=p+1;
						stack[p]='\0';	
					}
					k=j+1;
					stack[k]='N';
/////////////////////////////输出归约过程的一行的代码/////////////////////////////////////////////////////
					step++;
					step_result[step_result_len]=step;
					step_result_len++;
					printf("%4d    ",step);
					printf(" 归约    ");
					printf("  >  ");
					printf("%7c    ",ch);
					printf("     ");
                    for(int r=1;r<=k;r++)
					{
                		printf("%c",stack[r]);
					}
					for(int r=0;r<12-k;r++)
					{
	                	printf(" ");
					}					
					input_string_len=strlen(input_string);
                    for(int r=0;r<=input_string_len;r++)
					{
                    	printf("%c",input_string[r]);
					}
					printf("\n");
//////////////////////////////////////////////////////////////////////////////////////////////////////////
					flag_temp=1;
					break;
				}
			}
			if(flag_temp==0)
			{
				printf("Error!没有这样的产生式!\n");
			}
		}
///////////////////stack[j+1]到stack[k]规约过程结束//////////////////
		if((Find_relaion(stack[j],ch)==-1)||(Find_relaion(stack[j],ch)==0))
		{
			k=k+1;
			stack[k]=ch;
		}
		else
		{
			int error;
			error=Find_relaion(stack[j],ch);
			Process_Error(error);
			return;  
		}
//////////////////////////输出归约过程的一行的代码////////////////////////////////
    	step++;
     	printf("%4d    ",step);
    	printf(" 移进    ");
     	if(Find_relaion(stack[j],ch)==-1)
		{
    		printf("  <  ");
		}
    	if(Find_relaion(stack[j],ch)==0)
		{
    		printf("  =  ");
		}
    	printf("%7c    ",ch);
    	printf("     ");
        for(int r=1;r<=k;r++)
		{
    		printf("%c",stack[r]);
		}
    	for(int r=0;r<12-k;r++)
		{
    		printf(" ");
		}
		input_string_len=strlen(input_string);
        for(int r=0;r<=input_string_len;r++)
		{
        	printf("%c",input_string[r]);
		}
    	printf("\n");
/////////////////////////////////////////////////////////////////////////////////////////
    	ch=Getchar(input_string);
    	stack_pop=stack[k];
    }
////////////////////判断最终规约后的符号栈中是否是#N#形式，如果是那么久分析正确////
	if((stack[1]=='#')&&(stack[2]=='N')&&(stack[3]=='#'))
	{
		printf("输入的算术表达式正确!\n");
	}
	else
	{
		printf("您输入的算术表达式有错误,请检查!\n");
	}
	return;
}
/////////////////////////打印每个算术表达式求解的归约过程的一个函数/////////////////////
void Print_step()
{
	int i;
	for(i=0;i<step_result_len;i++)
	{
		printf("%d ",step_result[i]);
	}
	printf("\n");
    step_result_len=0;
}
////////////////////main()/////////////////////////////
 int main()
 {
	int i,j,len,result;
	char num_string[100][100]={'\0'};
	char result_string[100];
	printf("******************************算符优先语法分析程序***************************\n");
	printf("* E->E+T|E-T|T             分析的是四则混合运算的文法                       *\n");
	printf("* T->T*F|T/F|F             其中:E表示算术表达式;T表示项;                    *\n");
	printf("* F->(E)|i                 i表示变量或常数;                                 *\n");
	printf("*****************************************************************************\n");
	printf("*                          终结符优先表                                     *\n");
	printf("*                  +   -   *   /   (   )   i   #                            *\n");
	printf("*              +   >   >   <   <   <   >   <   >                            *\n");
    printf("*              -   >   >   <   <   <   >   <   >                            *\n");
	printf("*              *   >   >   >   >   <   >   <   >                            *\n");
	printf("*              /   >   >   >   >   <   >   <   >                            *\n");
	printf("*              (   <   <   <   <   <   =   <   e1                           *\n");
	printf("*              )   >   >   >   >   e2  >   e2  >                            *\n");
	printf("*              i   >   >   >   >   e2  >   e2  >                            *\n");
	printf("*              #   <   <   <   <   <   e3  <   =                            *\n");
	printf("*****************************************************************************\n");
	printf("*****************************************************************************\n");
	len=Find_num_string(num_string);//调用Find_num_string函数根据预处理的结果求救出每个算术表达式存放在二维字符数组num_string中
    printf("\n");
	for(i=0;i<len;i++)//根据求解出来的算术表达式循环的将其转换成输入串同时分析并且输出分析后的结果
	{
		 for(j=0;j<100;j++)//每次循环回来都要将上一个存放转换后的输入串清空
		 {
			 result_string[j]='\0';//每次循环回来都要将上一个存放转换后的输入串清空
		 }
		 printf("第%d个算术表达式是%s\n ",i+1,num_string[i]);
		 Convert_input_string(num_string[i],result_string);//将每个算术表达转换成输入串形式
         printf("转换为输入串形式是%s\n",result_string);
		 main_analyous(result_string);//分析每个转换后的输入串并且同时输出归约的过程
		 printf("第%d个算术表达式%s的归约步骤是:",i+1,num_string[i]);
		 Print_step();//输出刚刚分析好的输入串的规约步骤,不是移进步骤!
		 printf("\n");
	 }
	 printf("\n");
	 return 0;
 }