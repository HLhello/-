#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<io.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 //�洢�ռ��ʼ������
#define MAX_TREE_SIZE 100 // ���������������

typedef int Status;
typedef int TElemType;

/*
 * ADT ����tree��
 * Data
 * 	   ������һ�����ڵ�����ɿ��������ɣ����нڵ������ͬ�������ͼ���ι�ϵ
 * Operation
 * 	   InitTree(*T)
 * 	   DestortyTree(*T)
 * 	   CreateTree(*T,definition)
 * 	   ClearTree(*T)
 * 	   TreeEmpty(T)
 * 	   TreeDepth(T)
 * 	   Root(T)
 * 	   Value(T,*cur_e)
 * 	   Assign(T,cur_e,value)
 * 	   Parent(T,cur_e)
 * 	   LiftChild(T,cur_e)
 * 	   RightSibling(T,cur_e)
 * 	   InsertChild(*T,*p,i,c)
 * 	   DeleteChild(*T,*p,i)
 * endADT
 */

typedef TElemType SqBitree[MAX_TREE_SIZE];

typedef struct
{
	int level;//
	int order;// 
}Position;

Status InitBiTree(SqBitree T)
{
	int i;
	for(i=0;i<MAX_TREE_SIZE;i++)
	{
		T[i] = 0;
	}
	return OK;
}
//�������������������н���ֵ(�ַ��ͻ�����), ����˳��洢�Ķ�����T
Status CreateBiTree(SqBitree T)
{
	int i=0;
	printf("�밴�����������ֵ(����)��0��ʾ�ս�㣬��999�������������%d:\n",MAX_TREE_SIZE);
	
	///////////////////////////////////////////////////////////|�ⲿ���ǳ�ʼ����һ����ȫ������
	while(i<10)										  /////////|T�д洢���ǽڵ������
	{                                                 /////////|T�г�ʼ��ӳ����Ϣ�ǵڼ����ڵ�
		T[i] = i+1;                                   /////////|�ڵ�����ݿ����Լ��Ժ�ֵ
		if(i!=0 && T[(i+1)/2-1]==0 && T[i]!=0)        /////////|
		{                                             /////////|
			printf("������˫�׵ķǸ����%d\n",T[i]);    /////////|
			return ERROR;                             /////////|
		}                                             /////////|
		i++;                                          /////////|
	}                                                 /////////|
	///////////////////////////////////////////////////////////|
	while(i<MAX_TREE_SIZE)
	{
		T[i] = 0;
		i++;
	}
	return OK;
}

// ��ʼ����: ������T���� 
// �������: ��TΪ�ն�����,�򷵻�TRUE,����FALSE 
Status BiTreeEmpty(SqBitree T)
{
	if(T[0]==0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//��ʼ����: ������T���� 
//�������: �����������
/* ע�����Ϊk�����������Ľڵ���Ϊn����n��k�Ĺ�ϵΪ n = (2^k)-1
 *     ��ȫ�������Ľڵ���n�����k�Ĺ�ϵ n<(2^k)-1
 *     ��˳��洢�����һ���ڵ�Ҳ������������Ľڵ���
 *     ��˳��洢���ǰ�����ȫ��������ӳ��������
 *     �����ڼ������ʱ����ʹ������ļ��㹫ʽ
 */
int BiTreeDepth(SqBitree T)
{
	int i,j=-1;
	for(i=MAX_TREE_SIZE-1;i>=0;i--)
	{
		if(T[i] != 0) break;//�ҵ����һ���ڵ�
	}
	i++;//�����һ���ڵ��1
	do
	{
		j++;
	}while(i>=pow(2,j));//do-while ���������ѭ��
	return j;
}
//��ʼ����: ������T���� 
//�������: �������ĸ��ڵ�ֵ
Status Root(SqBitree T,TElemType *e)
{
	if(BiTreeEmpty(T))
	{
		return ERROR;
	}
	else
	{
		*e = T[0];
		return OK;
	}
}
//��ʼ����: ������T���ڣ�e��T�е�ĳ���ڵ�
//�������: ���ش���λ��e�Ľڵ��ֵ
TElemType Value(SqBitree T, Position e)
{
	return T[(int)pow(2,e.level-1)+e.order-2];
}

//��ʼ������������T���ڣ�e��T��ĳ���ڵ��λ��
//���������������λ��e�Ľڵ㸳��ֵvalue
//���⣺������������һ���������Ľڵ����ݴ�0�أ�
Status Assign(SqBitree T,Position e,TElemType value)
{
	int i=(int)pow(2,e.level-1)+e.order-2;
	if(value != 0 && T[(i+1)/2-1]==0)//�����������ݲ���Ϊ0������������Ǳ���ֵ�ڵ�ĸ��ڵ㲻��Ϊ0
	{								//���ڵ�ĺ��ӽڵ㲻��Ϊ0��
		return ERROR;
	}
	else if(value==0 && (T[i*2+1] != 0 || T[i*2+2] != 0))//valueΪ0�������Һ��ӽڵ���ڲ�Ϊ0�Ľڵ�
	{													//���һ���ڵ��к��ӽڵ㣬��ô���Ľڵ���ֵ�Ͳ���Ϊ0	
		return ERROR;									//����ʲô����
	}
	//����˵��һ���£�����������ڵ�Ϊ0����ô����ֵ�ĺ��ӽڵ�Ҳ��Ϊ0��
	//�������ֵ�ĸ��ڵ�Ϊ0����ô����ֵ�ڵ�����Һ��ӽڵ㶼����0��
	//Ҳ����˵0������Ϊ����ڵ�ĸ��ڵ㣬
	//�Ᵽ֤�������������Ϊ��ȫ��������ֻ�е�����һ�����ߺ͵����ڶ�����ұ߿�����Ҷ�ӽڵ�
	T[i] = value;
	return OK;
}

//��ʼ������������T���ڣ�e��T��ĳ���ڵ��λ��
//�������������Ǹ��ڵ�e��˫��
TElemType Parent(SqBitree T, TElemType e)
{
	int i;
	if(T[0] == 0)
	{
		return 0;
	}
	for(i=1;i<=MAX_TREE_SIZE-1;i++)		///|����˫�׽ڵ�   return T[(i+1)/2-1];
	{                                   ///|�������ӽڵ� return T[i*2+1];
		if(T[i]==e) return T[(i+1)/2-1];///|�����Һ��ӽڵ� return T[i*2+2];
	}                                   ///|�����ֵܽڵ� if�ж�i�Ƿ�Ϊ�����ж����Һ���   return T[i+1]
	return 0;
}

//��ʼ���������ڷǿն�����T
//��������������������������
Status Print(SqBitree T)
{
	int j,k;
	Position p;
	TElemType e;
	for(j=1;j<=BiTreeDepth(T);j++)
	{
		printf("��%d��:",j);
		for(k=1;k<=pow(2,j-1);k++)
		{
			p.level = j;
			p.order = k;
			e = Value(T,p);
			if(e!=0)
			{
				printf("%d:%d ",k,e);
			}
		}
		printf("\n");
	}
	return OK;
}

Status visit(TElemType c)
{
	printf("%d",c);
	return OK;
}


//���������� �����ң�ǰ��
void PreTraverse(SqBitree T, int e)
{
	visit(T[e]);//root
	if(T[2*e+1]!=0)//left
	{
		PreTraverse(T,2*e+1);
	}
	if(T[2*e+2]!=0)//right
	{
		PreTraverse(T,2*e+2);
	}
}

//���������� ����ң�����
void InTraverse(SqBitree T, int e)
{
	if(T[2*e+1]!=0)//left
	{
		PreTraverse(T,2*e+1);
	}
	visit(T[e]);//root
	if(T[2*e+2]!=0)//right
	{
		PreTraverse(T,2*e+2);
	}
}

//���������� ���Ҹ�������
void PostTraverse(SqBitree T, int e)
{
	if(T[2*e+1]!=0)//left
	{
		PreTraverse(T,2*e+1);
	}
	if(T[2*e+2]!=0)//right
	{
		PreTraverse(T,2*e+2);
	}
	visit(T[e]);//root
}

//ǰ����������������򣩣�����
Status OrderTraverse(SqBitree T)
{
	if(!BiTreeEmpty(T))
	{
		PreTraverse(T,0);
	}
	printf("\n");
	return OK;
}




void main()
{
	Status init_x,crea_x,isempty_x,depth_x,root_x,ass_x,par_x,pri_x,pre_x;
	TElemType e,e1;
	SqBitree T;
	init_x = InitBiTree(T);
	printf("%d\n",init_x);
	crea_x = CreateBiTree(T);
	printf("%d\n",crea_x);
	isempty_x = BiTreeEmpty(T);
	printf("%d\n",isempty_x);
	depth_x = BiTreeDepth(T);
	printf("%d\n",depth_x);
	root_x = Root(T,&e);
	printf("%d\n",root_x);
	Position ee = {1,1};
	e1 = Value(T, ee);
	printf("%d\n",e1);
	ass_x = Assign(T,ee,5);
	printf("%d\n",ass_x);
	e1 = Value(T, ee);
	printf("%d\n",e1);
	par_x = Parent(T,2);
	printf("%d\n",par_x);
	pri_x = Print(T);
	printf("%d\n",pri_x);
	pre_x = OrderTraverse(T);
	printf("%d\n",pre_x);
}
