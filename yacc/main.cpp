#include<stdio.h>
#include<stdlib.h>
#include<string.h>
////////////////////////////��Ź�Լ�����һ����������///////////////////////////////
int step_result[1000];//��Ź�Լ�����һ��ȫ������
int step_result_len=0;//ͳ��ȫ������ĳ���ÿ������Ӧ��
////////////////////////////////�����ķ��������ȱ���int�;����ʾ///////////////////
int Matux[8][8]={{1,1,-1,-1,-1,1,-1,1},{1,1,-1,-1,-1,1,-1,1},{1,1,1,1,-1,1,-1,1},{1,1,1,1,-1,1,-1,1},     
             {-1,-1,-1,-1,-1,0,-1,-3},{1,1,1,1,-2,1,-2,1},{1,1,1,1,-2,1,-2,1},{-1,-1,-1,-1,-1,-4,-1,0}};   
char *STR[6]={"N+N","N-N","N*N","N/N","(N)","i"};//�����ķ��ɹ�Լ�ɹ�Լ�ַ���
char stack[100];//�������ջ
int stack_len=0;//�����ʼ������ջ�ĳ���Ϊ0
int Getchar_len=0;//����ȡ���ַ���ȫ���ڴ��еı���
////////////////////////////////////////////////////////////////////////////////////////
bool IsLetter(char ch)//�жϵ�ǰch�Ƿ�Ϊ�ַ�///////////////////////////////////////////
{
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	{
		return 1;//���ch����ĸ�򷵻�1
	}
	else
	{
		return 0;//���������ĸ�򷵻�0
	}
}
bool IsDigit(char ch)//�жϵ�ǰch�Ƿ�Ϊ����/////////////////////////////////////////////
{
	if(ch>='0'&&ch<='9')
	{
		return 1;//���ch�������򷵻�1
	}
	else
	{
		return 0;//������������򷵻�0
	}
}
/////////////////////����ս����Ӧ�����ȱ�����е�����λ�õĺ���//////////////////////
int Find_two_table(char ch)//�����Ӧ�����ȱ��������������һ������
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
/////////////////////����Ԥ����������������ı��ʽ�����һ����ά���������һ������///////////////
int Find_num_string(char num_string[100][100])
{   
	int i,j,flag;
	char ch,old_ch=' ',string[20];
	FILE *fp;
	printf("����!��������Ԥ���������ļ�����:");
	gets(string);
	if((fp=fopen(string,"r"))==NULL) //���ļ��������ʧ������ʾ
	{
		printf("���򿪵��ļ�������,�������´��ļ�\n");//�ļ���ʧ�� ��ʾ�򿪵��ļ�������
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
/////////////////////////��������������ʽת���ɿ����봮�ĺ���/////////////////////////
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
////////////////////�Զ�ȡ���ǹ�Լ�����ַ���һ������///////////////////
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
//////////////////////�ж��Ƿ����ս��///////////////////////////////
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
///////////////////////�ж��ս��֮������ȹ�ϵ��һ������////////////////
int Find_relaion(char stack_ch,char ch)//�ҳ��ս��֮������ȹ�ϵ��һ������
{
	int row,lie,result;
	row=Find_two_table(stack_ch);
	lie=Find_two_table(ch);
	if((lie<0||lie>7)&&ch!='N')
	{
//		printf("�Ƿ���ʶ��%c",ch);
		return -10;
	}
	result=Matux[row][lie];
	return result;//�����ս����Ӧ����������������
}
////////////////////////////�������ӳ���///////////////////////////////
void Process_Error(int return_num)
{
	if(return_num==-2)//��������,һ�������ִ������
	{
		printf("Error!�������ʽȱ�������,��鿴����!\n");
	}
	else
	{
		if(return_num==-3)
		{
			printf("Error!�������ʽȱ��������,��鿴����!\n");
		}
		else
		{
			if(return_num==-4)
			{
				printf("Error!�������ʽȱ��������,��鿴����!\n");
			}
		}
	}
	return;//��������
}
////////////////////����һ���������ʽ�Ĺ�Լ���̵ĺ���///////////////////
void main_analyous(char input_string[100])
{
	int k,step=1,i,j,flag=0,p;int flag_temp=0,input_string_len;
	char ch,q_ch;
	char stack[100]={'\0'},temp_str[20]={'\0'};
	k=1;
	stack[k]='#';
    printf("�����   ����  ���ȹ�ϵ ��ǰ������  ����ջ      ʣ�����봮\n");
    printf("   1     Ԥ��      <                  #           %s\n",input_string);
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
//////////////////�ж����봮���ǲ��Ǵ��ڷǷ����ŵĴ����򷵻�-10/////////////
        error=Find_relaion(stack[j],ch);
		if(error==(-10))
		{
			printf("���봮�д��ڷǷ�����%c,���봮��������!\n",ch);
			return;
		}
///////////////////////////////////////////////////////////////////////////
		while(Find_relaion(stack[j],ch)==1)
		{
			for(int h=0;h<20;h++)//ÿ�ι�Լ�����д�ſɹ�Լ��������
			{
				temp_str[h]='\0';
			}
			flag=0;//////////////////ÿ�ι�Լflag����//////////////////
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
			temp_str[flag]=stack[p];//��stack[j+1]���ַ�����ʱ����temp+str�н��кͲ���ʽ�Ҳ����бȽ�
			while(p<k)//ѭ��һֱ��stack[j+1]==stack[k]����
			{
				p=p+1;
				flag++;
				temp_str[flag]=stack[p];			
			}
			for(i=0;i<6;i++)
			{
				if(strcmp(temp_str,STR[i])==0)
				{
					while(p<k)//ѭ��һֱ��stack[j+1]==stack[k]����ÿ�ι�Լ��ʱ��ͬʱ����Լ���ֵ�ջ���
					{
						p=p+1;
						stack[p]='\0';	
					}
					k=j+1;
					stack[k]='N';
/////////////////////////////�����Լ���̵�һ�еĴ���/////////////////////////////////////////////////////
					step++;
					step_result[step_result_len]=step;
					step_result_len++;
					printf("%4d    ",step);
					printf(" ��Լ    ");
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
				printf("Error!û�������Ĳ���ʽ!\n");
			}
		}
///////////////////stack[j+1]��stack[k]��Լ���̽���//////////////////
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
//////////////////////////�����Լ���̵�һ�еĴ���////////////////////////////////
    	step++;
     	printf("%4d    ",step);
    	printf(" �ƽ�    ");
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
////////////////////�ж����չ�Լ��ķ���ջ���Ƿ���#N#��ʽ���������ô�÷�����ȷ////
	if((stack[1]=='#')&&(stack[2]=='N')&&(stack[3]=='#'))
	{
		printf("������������ʽ��ȷ!\n");
	}
	else
	{
		printf("��������������ʽ�д���,����!\n");
	}
	return;
}
/////////////////////////��ӡÿ���������ʽ���Ĺ�Լ���̵�һ������/////////////////////
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
	printf("******************************��������﷨��������***************************\n");
	printf("* E->E+T|E-T|T             ��������������������ķ�                       *\n");
	printf("* T->T*F|T/F|F             ����:E��ʾ�������ʽ;T��ʾ��;                    *\n");
	printf("* F->(E)|i                 i��ʾ��������;                                 *\n");
	printf("*****************************************************************************\n");
	printf("*                          �ս�����ȱ�                                     *\n");
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
	len=Find_num_string(num_string);//����Find_num_string��������Ԥ����Ľ����ȳ�ÿ���������ʽ����ڶ�ά�ַ�����num_string��
    printf("\n");
	for(i=0;i<len;i++)//�������������������ʽѭ���Ľ���ת�������봮ͬʱ�����������������Ľ��
	{
		 for(j=0;j<100;j++)//ÿ��ѭ��������Ҫ����һ�����ת��������봮���
		 {
			 result_string[j]='\0';//ÿ��ѭ��������Ҫ����һ�����ת��������봮���
		 }
		 printf("��%d���������ʽ��%s\n ",i+1,num_string[i]);
		 Convert_input_string(num_string[i],result_string);//��ÿ���������ת�������봮��ʽ
         printf("ת��Ϊ���봮��ʽ��%s\n",result_string);
		 main_analyous(result_string);//����ÿ��ת��������봮����ͬʱ�����Լ�Ĺ���
		 printf("��%d���������ʽ%s�Ĺ�Լ������:",i+1,num_string[i]);
		 Print_step();//����ոշ����õ����봮�Ĺ�Լ����,�����ƽ�����!
		 printf("\n");
	 }
	 printf("\n");
	 return 0;
 }