#include<iostream>
#include<cstdio>
#include <time.h>//����Ϊ��ȡϵͳʱ�亯�� 
#include<cstring>
#include<cstdlib>
#include <conio.h>
#include <cstdlib>
#include<Windows.h>
#define bool int
#define true 1
#define false 0
#define FORMAT  "     |%-10s|%-10s|%6d|%6d|%8d|\n"
#define DATA  p->data.num,p->data.name,p->data.age,p->data.sex,p->data.Bad_record




using namespace std;

FILE* fp;
bool judge = true;

int eppy = 0; 
int ppj = 0;
int rooter_key = 0;//rooter 0Ϊ����Ա��1Ϊ�û� (����rooter_key����) 

//�ٿ�����ǰ���ȿ������漸�λ� 
//�����Ķ��ֲᣨ�򻯰棩
//ǰ���ǰ������������ǰ�������ģ������ں��棬
//��ǰ��Ϊ����������Ч������Ⱦ 
//������������棬�����
 


//��������������Ϊ����������ɫ�ĺ��� 
enum Color
{
	black, blue, green, lakeBlue, red, purple, yellow, white, gray,
	lightBlue, lightGreen, lightSimpleGreen, lightRed, lightPurple, lightYellow, brightWhite
};


void setColor(unsigned short textColor = 0, unsigned short backColor = 7) {
	char command[9] = "color 07";		//Ĭ����ɫ	
	command[6] = '0' + backColor;		//��backColor������Ϊ�ַ��� 
	command[7] = '0' + textColor;		//��textColor������Ϊ�ַ��� 
	system(command);				//����ϵͳ����
}


//����Ϊ��ȡϵͳʱ�亯�� 

	time_t t;
	struct tm * lt;


void time_plus()
{
	time (&t);//��ȡUnixʱ�����
    lt = localtime (&t);//תΪʱ��ṹ��
    printf ( "\n\n\t\t\t%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//������
} 

//����Ϊ�û����й����ݽṹ 
struct users
{
	char num[10];
	char name[20];
	int age;
	int sex;  //�Ա� 1Ϊ�� 0ΪŮ 
//	char 
//	char 
	int Bad_record;  // ������¼ 0��û��  1�Ǵ���
	//int num_car; ���˼��γ� 
	char key[20];//���� 
	int rooter;//rooter 1Ϊ����Ա��0Ϊ�û� 
};

typedef struct node
{
	
	struct users data;  /*������*/
	struct node *next;  /*ָ����*/
	
}Node,*Link; /*NodeΪnode���͵Ľṹ������*LinkΪnode���͵�ָ�����*/


//
////����λ��վ�г���ѯ 

typedef struct
{
	char id[5];//��� 
	char num[100];//���� 
	char departure[50];//ʼ��վ 
	char termination[50];//�յ�վ 
	char cost[5];//Ʊ�� 
	char quantities[5];//����
	char start[10];//����ʱ�� 
	char end[10];//����ʱ�� 
}TRAIN;//����Ϣ 
typedef struct NODE
{
	TRAIN data;//������ 
	struct NODE *next;//ָ���� 
}NODE, *LinkList;//���� 
static int TEMP = 0;//ȫ�ֱ���0��ʾû���޸ģ�1����ӣ�2���޸ģ�3��ɾ������������Ϊ0

//����Ϊ�������� 

void Firstin_menu(Link l, LinkList head);//���ڵ�½ʱ�Ķ�����˵������
void in_menu(Link l, LinkList head);//���ڴ����û��ĵ�½������
void users_menu(Link l, LinkList head);//�û���ҳ�档���Ϊ�û���֧ 
void out_sys();//�û��˳��Ľ��涯�� 
void rooters_menu(Link l, LinkList head);//����Ա��ҳ�档���Ϊ����Ա��֧ 
void rooters_menu_train_list(Link l, LinkList head) ;

void color_put_menu();

//�ú���β�Ž��������û����ǹ���Ա
//1----Ϊ�û���   0----Ϊ����Ա 
//ͬ�� 

void register_1(Link l);//ע���û����������û���xi'xia
void login_0(Link l);//����Ա��½ �������ڹ���Ա�� 
void Login_users(Link l);
void find_car_0(Link l,LinkList head);// ������Ϣ��ѯ��ͬ�£� 
void find_car_1(Link l,LinkList head);
void find_timeable_0(Link l);// �г�ʱ�̱�
void find_timeable_1(Link l);
void person_data_0(Link l); //������Ϣ����
void person_data_1(Link l);

void user_disp_0(Link l);//��ѯ������Ϣ
void user_disp_1(Link l, char searchinput[200]);

void user_modify(Link l);//�޸��û���Ϣ 
void rooter_modify(Link l);

void Wrong(); 
void stringinput(char *t,int lens,char *notice);


void find_car_users_menu(Link l);

void Save(Link l);
void save_end(Link l);
int saveflag = 0;  /*�Ƿ���Ҫ���̵ı�־����*/

int Subtraction(Link l ,LinkList head);


void Nofind()  /*���δ���Ҵ˽�ʦ����Ϣ*/
{
printf("\n=====>Not find this teacher!\n");
}

void printdata(Node *pp) /*��ʽ�������������*/
{
 Node* p;
 p=pp;
 printf(FORMAT,DATA);

}


void Wrong()  /*�������������Ϣ*/
{
printf("\n\n\n\n\n***********Error:�����������������⣩! �����������**********\n");
getchar();
}



//������������//
int add(LinkList head);//���ģ��
void Save_u(LinkList head);//����ģ��
void Delete(LinkList head);//ɾ��ģ��
void Update(LinkList head);//����ģ��
void Out_Info(TRAIN a);//�������Ϣ
//void save();//����ģ��
void Save_Info(TRAIN a);//�������Ϣ
void Save_List(LinkList head);//��������
int TXT_Purse(FILE *fp, TRAIN*a);//�ļ�����
LinkList Find(LinkList head, TRAIN a, int type);//���ҷ���һ�������ݵ�����  
void Push_Head(LinkList head, TRAIN a);//����ͷ��
void Get_Data(FILE *fp, char *pt);//������� 
LinkList CreatList(); 
LinkList appNode(TRAIN a);
int Size(LinkList head);
void Push_Head(LinkList head, TRAIN a);
void Print_List(LinkList head);
void List_DelBy_Id(LinkList head, char *id);
void Select(LinkList head);
LinkList Read_Info();
int Get_Node(FILE *fp, char *pt);
   //�����������//
LinkList CreatList() //������ͷ 
{
	LinkList head;
	head = (LinkList)malloc(sizeof(TRAIN));//���ٿռ� 
	head->next = NULL;//ָ��NULL 
	return head;
}
LinkList appNode(TRAIN a) //����һ���ڵ�
{
	LinkList node = NULL;
	node = (LinkList)malloc(sizeof(NODE));//���ٿռ� 
	node->data = a;
	node->next = NULL;
	return node;//���ؽڵ� 
}
int Size(LinkList head) //�������С��ȥͷ���
{
	int num = 0;
	LinkList p = head;//��P����ͷ�ڵ� 
	while (p != NULL)//��p�������һ���ڵ�ʱ 
	{
		num++;
		p = p->next;
	}
	return num - 1;//��ȥͷ�ڵ� 
}
void Push_Head(LinkList head, TRAIN a) //����ͷ��
{
	LinkList p = head;
	LinkList node = appNode(a);
	if (!p->next)//�ж�p->next�Ƿ�Ϊ�� 
	{
		p->next = node;
	}
	else//�����½ڵ� 
	{
		node->next = head->next;
		head->next = node;
	}

}
LinkList Find(LinkList head, TRAIN a, int form) //�������
{
	LinkList p = head->next;
	LinkList findInfo = CreatList();//������������ҵ���Ϣ
	int amount = 0;
	if (form == 1)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.id, a.id) == 0)//�ж��Ƿ��в��ҵ��г���id
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//�Ƶ���һ�ڵ� 
		}
	}
	else if (form == 2)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.num, a.num) == 0)//�ж��Ƿ��в��ҵ��г���num
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//�Ƶ���һ�ڵ� 
		}
	}
	else if (form == 3)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.departure, a.departure) == 0)//�ж��Ƿ��в��ҵ��г���departure
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//�Ƶ���һ�ڵ� 
		}
	}
	else if (form == 4)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.termination, a.termination) == 0)//�ж��Ƿ��в��ҵ��г���terminantion 
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//�Ƶ���һ�ڵ� 
		}
	}
	//�ڵ�����ͳ�� 
	amount = Size(findInfo);
	if (amount == 0)
		return NULL;
	else
		return findInfo;//����findInfo���� 

}
void Save_List(LinkList head)
{
	FILE *fp = fopen("train.txt", "w+");//�����ļ�
	LinkList p = head->next;
	fclose(fp);//�ر��ļ� 
	while (p != NULL)
	{
		Save_Info(p->data);//�����г���Ϣ 
		p = p->next;
	}
	TEMP = 0;
	printf("\t\t\t\t���浽 train.txt  ���.\n");
}
void Print_List(LinkList head)//��ӡ�г���Ϣ 
{
	LinkList p = head->next;
	while (p)//�ж�p�Ƿ�Ϊ�� 
	{
		Out_Info(p->data);//����г���Ϣ 
		p = p->next;
	}
}
void List_DelBy_Id(LinkList head, char *id)//ͨ��idɾ���г���Ϣ 
{
	LinkList p = head->next;
	LinkList prep = head;//���ڼ�¼��һ�ڵ�
	if (!p)
	{
		printf("\t\t\t\tû�����ݿɲ���Ŷ��\n");
		return;
	}
	while (p)
	{
		if (strcmp(p->data.id, id) == 0)//�ж��Ƿ��������ҵ��г���id 
		{
			printf("\t\t\t\tɾ��ing!\n");//��һ���ڵ�nextָ��p��next
			prep->next = p->next;
			free(p);//�ͷŽڵ� 
			printf("\t\t\t\tɾ����ɣ�\n");
			TEMP = 3;
			break;
		}
		prep = p;//��prep����p 
		p = p->next;//p������һ�ڵ� 
	}
	if (!p)
	{
		printf("\t\t\t\tû�и���Ϣ\n");
	}
}
//����ģ��//
int add(LinkList head)//����г���Ϣ 
{
	int operation;
	TRAIN a;
	printf("\t\t\t\t��������ӳ��κ�:");
	scanf("%s", a.num);//��ȡ�û����� 
	printf("\t\t\t\t��������ӳ��γ�����:");
	scanf("%s", a.departure);//��ȡ�û����� 
	printf("\t\t\t\t��������ӳ���Ŀ�ĵ�:");
	scanf("%s", a.termination);//��ȡ�û����� 
	printf("\t\t\t\t��������ӳ��γ���ʱ��:");
	scanf("%s", a.start);//��ȡ�û����� 
	printf("\t\t\t\t��������ӳ��ε���ʱ��:");
	scanf("%s", a.end);//��ȡ�û����� 
	printf("\t\t\t\t��������ӳ���Ʊ��:");
	scanf("%s", a.cost);//��ȡ�û����� 
	printf("\t\t\t\t���������ʣ��Ʊ����:");
	scanf("%s", a.quantities);//��ȡ�û����� 
	itoa(Size(head) + 1, a.id, 10);
	Push_Head(head, a);//������ӵ��г���Ϣ���뵽�����г��������� 
	TEMP = 1;
	printf("\t\t\t\t��ӳɹ�������0�������������������:");
	scanf("%d", &operation);//�жϼ�����ӻ��ǽ��� 
	if (operation == 0)
		return 0;
	else
		return 1;
}
int Subtraction(Link l ,LinkList head)
{
	int flag_u = 1;
	char rpp[100000];
	if((fp = fopen("High-speed_rail_timetable.txt","r")) == NULL)
	{
		printf("\n\n\t\t\t�޷��򿪣��ȴ�����Ա�޸�");
		system("cls");
		exit(0);
	}
	fread(rpp, 2, 50000, fp);
	printf("%s",rpp);
	fflush(stdin);
	fclose(fp);	
	printf("\n\n\n\n\t\t\t����Ϊ�Ϻ����Ż�վ���е��г�����������ṩ�Ľ��в���");
	printf("\n\n\t\t\t�밴���������...");
	getchar();	
	
	int thh;
	int operation;
	LinkList info = NULL;//�������� 
	TRAIN a;
	int form = 2;
	if(l->data.Bad_record == 1)
	{
		printf("\n\n\t\t\a\a\t�װ����û����ܱ�Ǹ�������ڲ�����¼���ڹ������صǼǱ�����30���ڲ�������Ʊ�����½�");
		printf("\n\n\t\t\t�밴���������...");
		getchar();
		printf("\n\n\t\t\t\t�����˳���..");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���.....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���.......");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���.........");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���...........");
			Sleep(600);
			return 0;
		
	}
	
	while(flag_u)
	{
		printf("\n\n\t\t\t\t��������ӳ��κ�:");
		scanf("%s", a.num);//��ȡ�û����� 
			info = Find(head, a, form);
		if (info)//�ж��Ƿ��ѯ���г���Ϣ 
		{
			printf("\t\t\t\t�ҵ�%d�����ݣ�\n", Size(info));
			Print_List(info);
			break ;
		}
		else{
			printf("\n\n\t\t\t\t�ܱ�Ǹ��֪ͨ�㣬��������ĳ��β����ڣ�������ͼѰ��");
			py:
			printf("\n\n\t\t\t�˳�������0,����1����");
			scanf("%d", &flag_u);
			if(flag_u != 0 && flag_u != 1)
			goto py;
		} 
	}
	
	printf("\n\n\t\t\t\t�Ƿ�Ʊ��1������,0��������)?");
	scanf("%d", &thh);
	if(thh == 1 && a.quantities > 0)
	{
		printf("\n\n\t\t\t��Ʊ�ɹ�");
	}
	else 
	{
		printf("\n\n\t\t\t��л����֧��");
	}
	
	printf("\n\t\t\t\t��ӳɹ�������0�������������������:");
	scanf("%d", &operation);//�жϼ�����ӻ��ǽ��� 
	system("cls");
	if (operation == 0)
		return 0;
	else
		return 1;
	
}
void Save_u(LinkList head)//�����ļ� 
{
	FILE *fp;//���ļ� 
	printf("\t\t\t\t�����ļ�ing��\n");
	Save_List(head);
}
void Out_Info(TRAIN a)//��ӡ�г���Ϣ 
{
	printf("\t\t\t\t\t\t-----------------------����Ʊ----------------------\n");
	printf("\t\t\t\t\t\t|���:   %10s                               |\n", a.id);
	printf("\t\t\t\t\t\t|���κ�: %10s                               |\n", a.num);
	printf("\t\t\t\t\t\t|��վ:   %10s   ����   %10s           |\n", a.departure, a.termination);
	printf("\t\t\t\t\t\t|ʱ��:   %10s    ->   %10s            |\n", a.start, a.end);
	printf("\t\t\t\t\t\t|Ʊ�ۣ�  %10s                               |\n", a.cost);
	printf("\t\t\t\t\t\t|������  %10s                               |\n", a.quantities);
	printf("\t\t\t\t\t\t---------------------------------------------------\n");
}
void Select(LinkList head)//ѡ���ѯ�г��ķ�ʽ 
{
	char name[30];//�������� 
	LinkList info = NULL;//�������� 
	TRAIN a;
	int form = 1;
	while (1)
	{
		system("cls");
		printf("\n\n\t\t\t\t\t��Ϊ�Ϻ����Ż�վ�ĸ���ʱ�̱�");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t  1: ���\n\n\t\t\t\t\t  2: ���κ�\n\n\t\t\t\t\t  3: ���\n\n\t\t\t\t\t  4: �յ�\n\n\t\t\t\t\t  5: �˳�");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t��������Ҫ����ʲô��Ϣ��ѯ����г���");
		printf("\n\n\t\t\t\t\t�밴�����淨�������в���������ᵼ�´���\n\n\t\t\t\t�����룺");
		scanf("%d", &form);//��ȡ�û����� 
		if (form == 1)
		{
			printf("\n\n\t\t\t\t��������Ҫ��ѯ���г����:");
			scanf("%s", a.id);
			info = Find(head, a, form);
		if (info)//�ж��Ƿ��ѯ���г���Ϣ 
		{
			printf("\t\t\t\t�ҵ�%d�����ݣ�\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\tû�������Ϣร�\n");
			printf("\n\n\t\t\t\t���������������...");
			getchar(); 
			getchar();
		}
		else if (form == 2)
		{
			printf("\n\n\t\t\t\t��������Ҫ��ѯ�ĳ��κ�:");
			scanf("%s", a.num);
			info = Find(head, a, form);//����Find����ͨ��id���� 
		if (info)//�ж��Ƿ��ѯ���г���Ϣ 
		{
			printf("\t\t\t\t�ҵ�%d�����ݣ�\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\tû�������Ϣร�\n");
			printf("\n\n\t\t\t\t���������������...");
			getchar();
			getchar();
		}
		else if (form == 3)
		{
			printf("\n\n\t\t\t\t��������Ҫ��ѯ���г����վ:");
			scanf("%s", a.departure);
			info = Find(head, a, form);//����Find����ͨ��num����
		if (info)//�ж��Ƿ��ѯ���г���Ϣ 
		{
			printf("\t\t\t\t�ҵ�%d�����ݣ�\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\tû�������Ϣร�\n");
			printf("\n\n\t\t\t\t���������������...");
			getchar();
			getchar();
		}
		else if (form == 4)
		{
			printf("\n\n\t\t\t\t��������Ҫ��ѯ���г��յ�վ:");
			scanf("%s", a.termination);
			info = Find(head, a, form);//����Find����ͨ��termination����
		if (info)//�ж��Ƿ��ѯ���г���Ϣ 
		{
			printf("\t\t\t\t�ҵ�%d�����ݣ�\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\tû�������Ϣร�\n");
			printf("\n\n\t\t\t\t���������������...");
			getchar();
			getchar();
		}
		else if (form == 5)
		{
			printf("\n\n\t\t\t\t�����˳���..");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���.....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���.......");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���.........");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t�����˳���...........");
			Sleep(600);
			return ;
		}
		else
		{
			printf("\n\n\a\a\t\t\t\t�����������Σ��...");
		}
	}
}
void Delete(LinkList head)//ɾ���г���Ϣ 
{
	char id[5];//�������� 
	printf("\t\t\t\t������Ҫɾ�����г����:");
	scanf("%s", id);
	List_DelBy_Id(head, id);//����List_DeLBy_Id����ɾ���г���Ϣ 
}
LinkList Read_Info()//��ȡ�г���Ϣ 
{
	LinkList info = CreatList();//������������Ϣ 
	FILE *fp;//���ļ� 
	TRAIN a;
	if (!(fp = fopen("train.txt", "r")))
	{
		printf("\t\t\t\tû�б�������ݣ�\n");
		return(info);
	}
	while (1)
	{
		if (TXT_Purse(fp, &a) == -1)
		{
			break;
		}
		Push_Head(info, a);//����Push_Head���� 
	}
	fclose(fp);
	return info;
}
void Update(LinkList head)//�����г���Ϣ 
{
	char id[5];//�������� 
	LinkList p = head->next;//����ָ�� 
	printf("\t\t\t\t������Ҫ�޸ĵ��г����:");
	scanf("%s", id);//��ȡ�û�����id 
	if (!p)
	{
		printf("\t\t\t\tû�����ݿɲ�����\n");
		return;
	}
	while (p)
	{
		if (strcmp(p->data.id, id) == 0)//�Ƚ�������г�id�ʹ����id 
		{
			TRAIN a;
			printf("\t\t\t\t����$���޸ģ�");
			printf("\t\t\t\t�������޸ĵĳ��κ�:");
			scanf("%s", a.num);//��ȡ�û����� 
			printf("\t\t\t\t�������޸ĵĳ�����:");
			scanf("%s", a.departure);//��ȡ�û����� 
			printf("\t\t\t\t�������޸ĵ�Ŀ�ĵ�:");
			scanf("%s", a.termination);//��ȡ�û����� 
			printf("\t\t\t\t�������޸ĵĳ���ʱ��:");
			scanf("%s", a.start);//��ȡ�û����� 
			printf("\t\t\t\t�������޸ĵĵ���ʱ��:");
			scanf("%s", a.end);//��ȡ�û����� 
			printf("\t\t\t\t�������޸ĵĳ���Ʊ��:");
			scanf("%s", a.cost);//��ȡ�û����� 
			printf("\t\t\t\t�������޸ĵĳ��ο���Ʊ����:");
			scanf("%s", a.quantities);//��ȡ�û����� 
			if (strcmp(a.num, "$") != 0)
				strcpy(p->data.num, a.num);//�����г����κ� 
			if (strcmp(a.departure, "$") != 0)
				strcpy(p->data.departure, a.departure);//�����г�ʼ��վ 
			if (strcmp(a.start, "$") != 0)
				strcpy(p->data.start, a.start);//�����г�����ʱ�� 
			if (strcmp(a.termination, "$") != 0)
				strcpy(p->data.termination, a.termination);//�����г��յ�վ 
			if (strcmp(a.end, "$") != 0)
				strcpy(p->data.end, a.end);//�����г�����ʱ�� 
			if (strcmp(a.cost, "$") != 0)
				strcpy(p->data.cost, a.cost);//�����г���Ʊ�� 
			if (strcmp(a.quantities, "$") != 0)
				strcpy(p->data.quantities, a.quantities);//�����г��ĳ�Ʊ���� 
			printf("\t\t\t\t�޸����.\n");
			TEMP = 2;
			break;
		}
		p = p->next;
	}//ѭ������
	if (!p)
	{
		printf("\t\t\t\tû���ҵ�����Ϣร�\n");
	}
}
//�ļ�����//
int Get_Node(FILE *fp, char *pt)//���ļ��ж�ȡ���� 
{
	char s;
	int i = 0;
	int ui = 0;
	while (1)
	{
		s = fgetc(fp);//���ļ��ж�ȡ�ַ� 
		if (s == EOF)
		{
			return -1;
		}
		if (s == '<')//�жϺ�ʱ������ȡ 
		{
			break;
		}
	}
	//��ʼ��ȡ
	while (1)
	{
		s = fgetc(fp);
		if (s == EOF) //�ļ�����
		{
			ui = -1;
			break;
		}
		if (s == '>') //�ڵ����
			break;
		pt[i] = s;//����ȡ�������ݴ��浽pt������ 
		i++;
	}
	pt[i] = '\0';
	return ui;//����ui 
}
void Save_Info(TRAIN a)//�����ļ���train.txt
{
	FILE *fp = fopen("train.txt", "a");//׷��
	char contents[500] = { '\0' };
	if (!fp) printf("\t\t\t\t404�����ļ�ʧ�ܣ�");
	else
	{
		strcat(contents, "<train>\n");//�������������� 

		strcat(contents, "\t<id>");
		strcat(contents, a.id);
		strcat(contents, "<\\id>\n");//�������������� 

		strcat(contents, "\t<num>");
		strcat(contents, a.num);
		strcat(contents, "<\\num>\n");//�������������� 

		strcat(contents, "\t<start>");
		strcat(contents, a.start);
		strcat(contents, "<\\start>\n");//�������������� 

		strcat(contents, "\t<end>");
		strcat(contents, a.end);
		strcat(contents, "<\\end>\n");//�������������� 

		strcat(contents, "\t<departure>");
		strcat(contents, a.departure);
		strcat(contents, "<\\departure>\n");//�������������� 

		strcat(contents, "\t<termination>");
		strcat(contents, a.termination);
		strcat(contents, "<\\termination>\n");//�������������� 

		strcat(contents, "\t<cost>");
		strcat(contents, a.cost);
		strcat(contents, "<\\cost>\n");//�������������� 

		strcat(contents, "\t<quantities>");
		strcat(contents, a.quantities);
		strcat(contents, "<\\quantities>\n");//�������������� 

		strcat(contents, "<\\train>\n");
		fputs(contents, fp);
		fclose(fp);//�ر��ļ� 
	}
}
void Get_Data(FILE *fp, char *pt)
{
	char cmt;
	int i = 0;
	while (1)
	{
		cmt = fgetc(fp);
		if (cmt == '<' || cmt == -1) //�ж�cmt�Ƿ񵽴�ֽ�� 
		{
			break;
		}
		if (cmt == '>') //�ж�cmt�Ƿ񵽴�ֽ��
		{
			continue;
		}
		pt[i] = cmt;//�����ƶ� 
		i++;
	}
	pt[i] = '\0';
}
int TXT_Purse(FILE *fp, TRAIN *a) //�ļ�����
{
	char node[500];//�����㹻������飬����ջ���� 
	int  fty = 0;
	if (Get_Node(fp, node) == -1)
	{
		fty = -1;
		return fty;
	} //��ýڵ�
	if (strcmp(node, "train") == 0)
		while (1)
		{
			if (Get_Node(fp, node) == -1)
			{
				fty = -1;
				break;
			}
			if (strcmp(node, "id") == 0)
				Get_Data(fp, a->id);//���id���� 
			if (strcmp(node, "num") == 0)
				Get_Data(fp, a->num);//���num���� 
			if (strcmp(node, "start") == 0)
				Get_Data(fp, a->start);//���start���� 
			if (strcmp(node, "end") == 0)
				Get_Data(fp, a->end);//���end���� 
			if (strcmp(node, "departure") == 0)
				Get_Data(fp, a->departure);//���departure���� 
			if (strcmp(node, "termination") == 0)
				Get_Data(fp, a->termination);//���termination���� 
			if (strcmp(node, "cost") == 0)
				Get_Data(fp, a->cost);//���cost���� 
			if (strcmp(node, "quantities") == 0)
				Get_Data(fp, a->quantities);//���quantities���� 
			if (strcmp(node, "\\train") == 0)
				break;
		}
	return fty;

}




//

/*
������findmess[]����Ҫ���ҵľ�������; nameornum[]���水ʲô����;
    �ڵ�����l�в���;
*/
Node* Locate(Link l,char findmess[],char nameornum[])
{
Node *r;
if(strcmp(nameornum,"num")==0) /*����Ų�ѯ*/
{
  r=l->next;
  while(r)
  {
   if(strcmp(r->data.num,findmess)==0) /*���ҵ�findmessֵ�ı��*/
    return r;
   r=r->next;
  }
}
else if(strcmp(nameornum,"name")==0)  /*��������ѯ*/
{
  r=l->next;
  while(r)
  {
   if(strcmp(r->data.name,findmess)==0)    /*���ҵ�findmessֵ�Ľ�ʦ����*/
    return r;
   r=r->next;
  }
}
return 0; /*��δ�ҵ�������һ����ָ��*/
}


/*�����ַ����������г�����֤(����<lens)*/
void stringinput(char *t,int lens)
{
   char n[255];
   do{
      scanf("%s",n);  /*�����ַ���*/
      if(strlen(n)>lens)
	  printf("\n exceed the required length! \n"); /*���г���У�飬����lensֵ��������*/
     }while(strlen(n)>lens);
   strcpy(t,n); /*��������ַ����������ַ���t��*/
}


void register_1(Link l)
{
	Node *p, *r, *s;
	char ch, flag = 0, num[10], hum[20];
	r = l;
	s = l->next;
	//system("cls"); ��֪��ʲôʱ��ӱȽϺã����������
//	Disp(l); 
	while(l)/*һ�ο����������¼��ֱ��������Ϊ0�ļ�¼�����Ӳ���*/
	{
		printf("\n\t\t\t����0���ɷ������˵���(��������������Ϊ10λ)");
		stringinput(num,10); /*��ʽ�������Ų�����*/
   		flag=0;  
   		if(strcmp(num, "0") == 0) return ;
   		s = l->next;
		while(s)
  		{
   			if(strcmp(s->data.num, num) == 0)
   			{
   				flag = 1;
   				break;
			}
			s = s->next;
		}
			
		if(flag == 1)
		{
			getchar();
			printf("\n\n\t\t\t�˺���û�б�ע�ᣨ�����øú��룩[�Ƿ����������(Y/N)]��");
			scanf("%c", &ch);
			if (ch=='y'||ch=='Y')
				continue;
			else 
				return; 
		}
		else 
		{
			break;
		}
	}
		p = (Node *)malloc(sizeof(Node));
		if(!p)
		{
			printf("\n\n\t\t\tϵͳ���ϣ�û�и���Ĵ洢�ռ�");
			return ;
		}
		strcpy(p->data.num, num);
		printf("\n\t\t\t����:");
		stringinput(p->data.name,15);
		printf("\t\t\t�Ա�(1Ϊ�� 0ΪŮ ):");
		scanf("%d",&p->data.sex);
		printf("\t\t\t����(�밴��ʵ������д):");
		scanf("%d",&p->data.age);
		//Ĭ�Ͽ�ʼû�в�����¼ 
		p->data.Bad_record = 0;
		
		//����ע�͵� 
		printf("\t\t\t����Ա:");
		scanf("%d",&p->data.rooter);
		// 
		
		while(1)
		{
			printf("\t\t\t����:");
			stringinput(p->data.key,15);
			printf("\t\t\t�ٴ���������:");
			stringinput( hum,15); 
			if(strcmp(p->data.key,hum)!=0)
        	{
        		printf("\n\t\tϵͳ�����������벻һ��,����������");	
			}
			else break;
		}
  		p->next = NULL; /*�������������β�����*/
 		r->next = p;  /*���½��Ľ���������β����*/
  		r = p;
  		saveflag = 1;
  		
  		Save(l);
	return ;
}

//ֱ�Ӱѱ�ſ��������У������������� 
void user_disp_1(Link l, char searchinput[200])//��ѯ������Ϣ���޸� 
{
	int select;
	Node *p;
	if(!l->next)
	{
		system("cls");
		printf("\n\n\n\t\t\t�������κ��û���¼(ϵͳ����)");
		printf("\n\n\n\t\t\t�밴���������");
		getchar();
		return ; 
	}
	system("cls");
	printf("���ڶ�ȡ��....");
	stringinput(searchinput,100);
	p = Locate(l,searchinput,"num");/*��l�в��ұ��Ϊsearchinputֵ�Ľڵ㣬�����ؽڵ��ָ��*/
	if(p) /*��p!=NULL*/
	{
    	printdata(p);
    	printf("\n\n\n\t\t\t��������˳�");
    	getchar();
	}
}

void user_modify(Link l)
{
	Node *p;
	char findmess[20];
	if(!l->next)
	{
		system("cls");
		printf("\n\n\t\t\t�������û���¼");
		getchar();
		return ;
	}
	system("cls");
	printf("");
	
	//Disp(1)
	
	printf("\n\n\t\t\t�������û����(10λ)");
	stringinput(findmess, 10);
	p = Locate(l, findmess, "num");
	
	char th;
	if(p)
	{
		while(1)
		{
		printf("\n\n\t\t\t\t\t�� Ϊ �� �� �� Ϣ ��");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t   1.����: %s",p->data.name);
		printf("\n\n\t\t\t\t\t   2.����: %d",p->data.age);
		printf("\n\n\t\t\t\t\t   3.�Ա�: %d (1Ϊ�� 0ΪŮ )",p->data.sex);  
		printf("\n\n\t\t\t\t (�����޸�)4.�����˳���¼: %d (0��û��  1�Ǵ���)",p->data.Bad_record);
		printf("\n\n\t\t\t\t\t   5.�˳��޸�"); 
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\t\t\t\t\t�����޸���Ϣ,������Ҫ�޸���ı��,���� 5 �˳�");
		printf("\n\t\t\t\t\t�밴�����淨�������в���������ᵼ�´���");
		th = getch();
		switch(th)
		{
			case '1':
				{
					printf("\n\n\t\t\t������������:");
					stringinput(p->data.name,15);
					Sleep(500);
				}break;
			case '2':
				{
					printf("\n\n\t\t\t����������:");
					scanf("%d", p->data.age);
					Sleep(500);
					
				}break;
			case '3':
				{
					printf("\n\n\t\t\t�������Ա�:");
					scanf("%d", p->data.sex);
					Sleep(500);
					
				}break;
			case '4':
				{
					if(p->data.Bad_record == 1)
					{
						printf("\n\n\t\t\t\a�����ڲ�����¼,��2019�겻�����������,�����");
					}
					printf("\n\n\t\t\t�˲����޸�,(�밴���������...)");
					getchar();	
				}break;
			case '5':
				{
					printf("\n\n\t\t\t\t\t���ڰ�ȫ�˳���,���Ժ�.....");
					Sleep(100);
					return ;
				}break;
			default :
				{
				printf("\t���澯�� \a\a����");//a\�Ƿ����ķ��������� 
				Sleep(100);//���û�һ�����۵�ʱ�䣬��ˢ�½���
				system("cls"); 		
				}break;			
			}
		system ("cls");	
		}
	}
}


void rooter_modify(Link l)
{
	Node *p;
	char findmess[20];
	if(!l->next)
	{
		system("cls");
		printf("\n\n\t\t\t�������û���¼");
		getchar();
		return ;
	}
	system("cls");
	printf("");
	
	//Disp(1)
	
	printf("\n\n\t\t\t�������û����(10λ)");
	stringinput(findmess, 10);
	p = Locate(l, findmess, "num");
	
	char th;
	if(p)
	{
		while(1)
		{
		printf("\n\n\t\t\t\t\t�� Ϊ �� �� �� Ϣ ��");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t   1.����: %s",p->data.name);
		printf("\n\n\t\t\t\t\t   2.����: %d",p->data.age);
		printf("\n\n\t\t\t\t\t   3.�Ա�: %d (1Ϊ�� 0ΪŮ )",p->data.sex);
		printf("\n\n\t\t\t\t\t   4.�����˳���¼: %d (0��û��  1�Ǵ���)",p->data.Bad_record);  
		printf("\n\n\t\t\t\t\t   5.�˳��޸�"); 
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\t\t\t\t\t�����޸���Ϣ,������Ҫ�޸���ı��,���� 5 �˳�");
		th = getch();
		switch(th)
		{
			case '1':
				{
					printf("\n\n\t\t\t������������:");
					stringinput(p->data.name,15);
					Sleep(500);
				}break;
			case '2':
				{
					printf("\n\n\t\t\t����������:");
					scanf("%d", p->data.age);
					Sleep(500);
					
				}break;
			case '3':
				{
					printf("\n\n\t\t\t�������Ա�:");
					scanf("%d", p->data.sex);
					Sleep(500);
					
				}break;
			case '4':
				{
					printf("\n\n\t\t\t����Ĳ����¼:");
					scanf("%d", p->data.Bad_record);
					Sleep(500);
					
				}break;
			case '5':
				{
					printf("\n\n\t\t\t\t\t���ڰ�ȫ�˳���,���Ժ�.....");
					Sleep(100);
					return ;
				}break;
			default :
				{
				printf("\t���澯�� \a\a����");//a\�Ƿ����ķ��������� 
				Sleep(100);//���û�һ�����۵�ʱ�䣬��ˢ�½���
				system("cls"); 		
				}break;			
			}
		system ("cls");	
		}
	}
}










void save_end(Link l)
{
	char ch;
	if(saveflag==1) /*����������������޸���δ���д��̲�������˱�־Ϊ1*/
   { 
   		getchar();
     	printf("\n\n\t\t\t�Ƿ��޸ĺ�ļ�¼���浽�ļ��У�(y/n):");
     	scanf("%c",&ch);
     	if(ch=='y'||ch=='Y')
       Save(l);
   }
   printf("=====>thank you for useness!");
   getchar();
	
}





//����Ϊ���溯���趨 

void Firstin_menu(Link l)//���ڵ�½ʱ�Ķ�����˵������
{
	for(int i = 0; i < 2; i++)//��Ϊ��½�������棬ʹ�û���ǰһ�� 
	{
	setColor(0, 1);
	Sleep(50);//��Ϊ��ʱ��ͬ�� 
	setColor(0, 2);
	Sleep(50);
	setColor(0, 3);
	Sleep(50);
	setColor(0, 4);
	Sleep(50);
	setColor(0, 5);
	Sleep(50);
	setColor(0, 6);
	Sleep(50);
	setColor(0, 7);
	Sleep(50);
	setColor(0, 8);
	Sleep(50);
	setColor(0, 9);
	Sleep(50);
	}
	setColor(0, 1);
	printf("\n\n\n\t\t\t\t\t\t\t��");
	Sleep(100);
	setColor(0, 2);
	printf("\n\n\t\t\t\t\t\t\t��");
	Sleep(120);
	setColor(0, 3);
	printf("\n\n\t\t\t\t\t\t\t��");
	Sleep(140);
	setColor(0, 4);
	printf("\n\n\t\t\t\t\t\t\t   ӭ");
	Sleep(160);
	setColor(0, 5);
	printf("\n\n\t\t\t\t\t\t\t   ӭ");
	Sleep(180);
	setColor(0, 6);
	printf("\n\n\t\t\t\t\t\t\t   ӭ");
	Sleep(200);
	setColor(0, 7);
	printf("\n\n\t\t\t\t\t\t\t�� ӭ");
	Sleep(220);
	setColor(0, 8);
	printf("\n\n\t\t\t\t\t\t\t�� ӭ");
	Sleep(240);
	setColor(0, 9);
	printf("\n\n\t\t\t\t\t\t\t�� ӭ");
	Sleep(260);

	system("cls") ;
	
	printf("\n\n\t\t\t\t\t    �� ӭ ʹ �� �� ϵ ͳ");
}


void out_sys()//�����˳����棨���˳�Ϊ����Ĵ��˳�������С�˳��ֿ����� 
{
	printf("                ********\n");
	setColor(0, 1);
	Sleep(150);//��Ϊ��ʱ��ͬ�� 
    printf("               ************\n");
    printf("               ####....#.\n");
	setColor(0, 2);
	Sleep(150);
    printf("             #..###.....##....\n");
    printf("             ###.......######              ###            ###\n");
	setColor(0, 3);
	Sleep(150);
    printf("                ...........               #...#          #...#\n");
    printf("               ##*#######                 #.#.#          #.#.#\n");
	setColor(0, 4);
	Sleep(150);
    printf("            ####*******######             #.#.#          #.#.#\n");
    printf("           ...#***.****.*###....          #...#          #...#\n");
	setColor(0, 5);
	Sleep(150);
    printf("           ....**********##.....           ###            ###\n");
    printf("           ....****    *****....\n");
	setColor(0, 6);
	Sleep(150);
    printf("             ####        ####\n");
    printf("           ######        ######\n");
	setColor(0, 7);
	Sleep(150);
	printf("##############################################################\n");
    printf("#...#......#.##...#......#.##...#......#.##------------------#\n");
	setColor(0, 8);
	Sleep(180);
    printf("###########################################------------------#\n");
    printf("#..#....#....##..#....#....##..#....#....#####################\n");
	setColor(0, 9);
    Sleep(1000);
    system("cls"); 
    printf("\n\n\n\n\t\t\t ��  �� ");
	printf("\n\n\n\n\t\t��  ӭ   ��  ��  ʹ  �� ");


} 


//��½ 
void Login_users(Link l)
{
	//ʹ��һ��ȫ�ֱ���eppy����������Ƿ�Ҫ�����˳� 
    char u[20],c[20],temp_0[20];      //�����������飬��ż���������û���������
    char tth;
    char key_u[100];//���� 
    char searchinput[20]; /*�����û�����Ĳ�ѯ����*/
    Node *p;
    FILE *fp;
    fp = fopen("users.txt","r+");
    if(!l->next) /*������Ϊ��*/
	{
 	system("cls");
 	printf("\n=====>No record!\n");
  	getchar();
  	return;
	}
	
	op://goto
	
    printf("\n\n\n\t\t\t\t�û���¼");
    printf("\n\n\t\t�û����:");	

    stringinput(searchinput,10);
    printf("\n\t\t�û�����:");	
    scanf("%s", key_u);
    
    p = Locate(l,searchinput,"num");/*��l�в��ұ��Ϊsearchinputֵ�Ľڵ㣬�����ؽڵ��ָ��*/
    if(p) /*��p!=NULL*/
	{
		if(strcmp(p->data.key, key_u) != 0)
		{
			printf("\n\n\t\t\t�������,����������\a\a"); 
			scanf("%s", key_u);
			if(strcmp(p->data.key, key_u) != 0)
			{
				eppy = 1;
				printf("\n\n\t\t\t�������\a\a");
				printf("\n\n\t\t\t�Զ�������ҳ��\a\a");
				Sleep(100);
				fclose(fp); 
				return ; 
			}
		}
		else 
		{
			printf("\n\n\t\t\t��ӭ��½");
		}
		fclose(fp); 
    	getchar();
   }
   else
   {
   		while(1)
   		{
   			printf("\n\n\t\t\t\t�û�������,��ѡ�����·�ʽ:");
   			printf("\n\t\t1.������ҳ��ע��   2.���µ�½");
   			tth = getch();
   			eppy = 1;
   			if(tth = '1')
   			{
   				fclose(fp); 
   				return ;
			}
			else if(tth = '2')
			{
				goto op;
			}
			else printf("\n\n\t\t\t���澯�� \a\a����");
			
		}
   		
   }

}

void login_0(Link l)
{
	//ʹ��һ��ȫ�ֱ���ppj����������Ƿ�Ҫ�����˳� 
    char u[20],c[20],temp_0[20];      //�����������飬��ż���������û���������
    char tth;
    char key_u[100];//���� 
    char searchinput[20]; /*�����û�����Ĳ�ѯ����*/
    Node *p;
    FILE *fp;
    fp = fopen("users.txt","r+");
    if(!l->next) /*������Ϊ��*/
	{
 	system("cls");
 	printf("\n=====>No record!\n");
  	getchar();
  	return;
	}
	
	op://goto
	
    printf("\n\n\n\t\t\t\t����Ա��¼");
    printf("\n\n\t\t����Ա���:");	
	stringinput(searchinput,10);
	
    printf("\n\t\t����Ա����:");	
    scanf("%s", key_u);
    
    
    p = Locate(l,searchinput,"num");/*��l�в��ұ��Ϊsearchinputֵ�Ľڵ㣬�����ؽڵ��ָ��*/
	if(p->data.rooter != 1)
		{
			printf("\n\n\a\a\t\t\t\t��Ǹ����û�й���ԱȨ��,����ǿ���˳�");
			ppj = 1; 
			Sleep(1000);
			return ;
		}
    if(p) /*��p!=NULL*/
	{
    	
		if(strcmp(p->data.key, key_u) != 0)
		{
			printf("\n\n\t\t\t�������,����������\n\t\t\t\a\a"); 
			scanf("%s", key_u);
			if(strcmp(p->data.key, key_u) != 0)
			{
				ppj = 1;
				printf("\n\n\t\t\t�������\a\a");
				printf("\n\n\t\t\t�Զ�������ҳ��\a\a");
				Sleep(100);
				fclose(fp); 
				return ; 
			}
		}
		else 
		{
			printf("\n\n\t\t\t��ӭ��½");
		}
		fclose(fp); 
    	getchar();
   }
   else
   {
   		while(1)
   		{
   			printf("\n\n\t\t\t\t�û�������,��ѡ�����·�ʽ:");
   			printf("\n\t\t1.������ҳ��ע��   2.���µ�½");
   			tth = getch();
   			ppj = 1;
   			if(tth = '1')
   			{
   				fclose(fp); 
   				return ;
			}
			else if(tth = '2')
			{
				goto op;
			}
			else printf("\n\n\t\t\t���澯�� \a\a����");
			
		}
   		
   }

}


void color_put_menu()
{
		char th;
		printf("\n\n\t\t\t\t\t    ѡ һ �� �� ϲ �� �� �� ɫ ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t******************************************");
		printf("\n\n\t\t\t\t\t*     0 = ��ɫ        5 = ��ɫ           *");
		printf("\n\n\t\t\t\t\t*     1 = ��ɫ        6 = ��ɫ           *");
		printf("\n\n\t\t\t\t\t*     2 = ��ɫ        7 = ǳ��ɫ          *");
		printf("\n\n\t\t\t\t\t*     3 = ǳ��ɫ      8 = ��ɫ           *");
		printf("\n\n\t\t\t\t\t*     4 = ��ɫ        9 = ����ɫ         *");
		printf("\n\n\t\t\t\t\t******************************************");
		printf("\n\n\t\t\t\t\t�밴�����淨�������в���������ᵼ�´���");
		th = getch();
		switch(th)
		{
			case '0':
				{
					setColor(0, 0);	
				}break;
			case '1'://�û���½�ӿ� 
				{
					setColor(0, 1);
				}break;
			case '2':
				{
					setColor(0, 2);
				}break;
			case '3':
				{
					setColor(0, 3);
				}break;
			case '4':
				{
					setColor(0, 4);
				}break;
			case '5':
				{
					setColor(0, 5);
				}break;
			case '6':
				{
					setColor(0, 6);
				}break;
			case '7':
				{
					setColor(0, 7);
				}break;
			case '8':
				{
					setColor(0, 8);
				}break;
			case '9':
				{
					setColor(0, 9);
				}break;
			default :
				{
				printf("\t���澯�� \a\a����");//a\�Ƿ����ķ��������� 
				Sleep(100);//���û�һ�����۵�ʱ�䣬��ˢ�½���
				system("cls"); 			
				}break;			
		}
		system("cls");
}


//����Ϊ��֧ҳ�����




//����Ϊ���˵����� 

void in_menu(Link l, LinkList head)//���ڴ����û��ĵ�½������
{
	color_put_menu();
	nn://ͬ��
	while (1)
	{
		char th;
		printf("\n\n\t\t\t\t\t    �� �� �� �� �� �� վ ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.�û���½          *");
		printf("\n\n\t\t\t\t\t*       2.�û�ע��          *");
		printf("\n\n\t\t\t\t\t*       3.�˳���½          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       0.����Աϵͳ        *");
		printf("\n\n\t\t\t\t\t�밴�����淨�������в���������ᵼ�´���");
		printf("\n\n\t\t\t\t\t�ǹ���Ա����ʹ�ù���Ա����");
		printf("\n\t\t\tϵͳʱ�����£�"); 
		time_plus();
		th = getch();
		switch(th)
		{
			case '0':
				{
					system("cls");
					rooters_menu(l,head);
					//����Ա��ҳ��	
				}break;
			case '1'://�û���½�ӿ� 
				{
					system("cls");
					users_menu(l,head);//�û���ҳ�� 
				}break;
			case '2':
				{
					register_1(l);//�û�ע�� 
				}break;
			case '3':
				{
					save_end(l);
					printf("\n\n\t\t\t\t\t�����˳������Ժ�");
					out_sys();//�˳�����������Ϊͼ�ν��棩 
					return ;
				}break;
			default :
				{
				printf("\t���澯�� \a\a����");//a\�Ƿ����ķ��������� 
				Sleep(100);//���û�һ�����۵�ʱ�䣬��ˢ�½���
				system("cls"); 
				goto nn;			
				}break;			
		}
		system ("cls");
	}
}



void users_menu(Link l,LinkList head)//�û���ҳ�档���Ϊ�û���֧ 
{
	Login_users(l);
	if(eppy == 1)
	{
		printf("\n\n\t\t\t\t��������Զ��˻���ҳ��");
		Sleep(1000);
		return ;
	}
	FILE *fp, *pp;
	
	
	nn://����ͬ�£�����Ա���棩��Ϊgoto����ת�� 
	system("cls");
	while (1)
	{
		char th;
		printf("\n\n\t\t\t\t\t    �� �� �� �� �� �� վ ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.������Ϣ����      *");
		printf("\n\n\t\t\t\t\t*       2.������Ϣ��ѯ      *");
		printf("\n\n\t\t\t\t\t*       3.�г�ʱ�̱�        *");
		printf("\n\n\t\t\t\t\t*       4.��Ʊ              *");
		printf("\n\n\t\t\t\t\t*       5.��·�����ֲ�      *");
		printf("\n\n\t\t\t\t\t*       6.�˳���½          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t�밴�����淨�������в��������1-5�У�����ᵼ�´���");
		printf("\n\n\t\t\t\t\t�ǹ���Ա����ʹ�ù���Ա����");
		printf("\n\t\t\tϵͳʱ�����£�");
		time_plus();
		th = getch();
		switch(th)
		{
			case '1':
				{
					user_modify(l);
				}break;
			case '2':
				{
					system("cls");
					Select(head); 
				}break;
			case '3':
				{
					char rpp[6000];
					if((fp = fopen("High-speed_rail_timetable.txt","r")) == NULL)
					{
						printf("\n\n\t\t\t�޷��򿪣��ȴ�����Ա�޸�");
						system("cls");
						exit(0);
						//����Ūһ��һ������ҳ�� 
					}
					fread(rpp, 2, 3000, fp);
					printf("%s",rpp);	
					fclose(fp);
					fflush(stdin);
					fflush(stdin);
					printf("\n\n\t\t\t�밴���������...");
					getchar();
					
				}break;
			case '4':
				{
					system("cls");
					int tt = 1;
					while (tt)
					{
						tt = Subtraction(l,head); 
					}
				}break;
			case '5':
				{
					char tpp[6000];
					if((pp = fopen("Management_manual.txt","r")) == NULL)
					{
						printf("\n\n\t\t\t�޷��򿪣��ȴ�����Ա�޸�");
						system("cls");
						exit(0);
						//����Ūһ��һ������ҳ�� 
					}
					fread(tpp, 2, 3000, pp);
					printf("\n\n\t\t\t%s",tpp);	
					fclose(pp);
					fflush(stdin);
					fflush(stdin);
					printf("\n\n\t\t\t�밴���������...");
					getchar();
				}break;
			case '6':
				{
					printf("\n\n\t\t\t\t\t�����˳������Ժ�");
					Sleep(100); 
					out_sys();
					exit(0);
					
				}break;
			default :
				{
				printf("\t���澯�� \a\a����");//a\�Ƿ����ķ��������� 
				Sleep(100);//���û�һ�����۵�ʱ�䣬��ˢ�½���
				system("cls"); 
				goto nn;
					
				}break;			
		}
		system ("cls");
	}	
}


void rooters_menu_train_list(Link l, LinkList head) 
{
	int pph = 1;
	nn:
	system("cls");
	while (1)
	{
		char th;
		printf("\n\n\t\t\t\t     �� �� �� �� �� �� վ �� �� Ա ϵ ͳ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.��ӳ�����Ϣ      *");
		printf("\n\n\t\t\t\t\t*       2.��ѯ������Ϣ      *");
		printf("\n\n\t\t\t\t\t*       3.�г�ʱ�̱�        *");
		printf("\n\n\t\t\t\t\t*       4.���³�����Ϣ      *");
		printf("\n\n\t\t\t\t\t*       5.ɾ��������Ϣ      *");
		printf("\n\n\t\t\t\t\t*       6.�˳���½          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t�밴�����淨�������в��������1-5�У�����ᵼ�´���");
		printf("\n\n\t\t\t\t\t�ǹ���Ա����ʹ�ù���Ա����");
		printf("\n\t\t\tϵͳʱ�����£�");
		time_plus();
		th = getch();
		switch(th)
		{
			case '1':
				{
					while(pph)
					{
						pph = add(head);
						Save_u(head);
					}	
				}break;
			case '2':
				{
				  Select(head);
				}break;
			case '3':
				{
					char rpp[100000];
					if((fp = fopen("High-speed_rail_timetable.txt","r")) == NULL)
					{
						printf("\n\n\t\t\t�޷��򿪣��ȴ�����Ա�޸�");
						system("cls");
						exit(0);
						//����Ūһ��һ������ҳ�� 
					}
					fread(rpp, 2, 50000, fp);
					printf("%s",rpp);
					fflush(stdin);
					fclose(fp);	
					printf("\n\n\t\t\t�밴���������...");
					getchar();	
					
				}break;
			case '4':
				{
					Update(head);
					Save_u(head);
				}break;
			case '5':
				{
					Delete(head);
					Save_u(head);
					Sleep(100); 
				}break;
			case '6':
				{
					printf("\n\n\t\t\t\t\t�����˳������Ժ�");
					Sleep(100); 
					return ;
				}break;
			default :
				{
				printf("\t���澯�� \a\a����");//a\�Ƿ����ķ��������� 
				Sleep(100);//���û�һ�����۵�ʱ�䣬��ˢ�½���
				system("cls"); 
				goto nn;
					
				}break;			
		}
		system ("cls");
	}	
	
}



void rooters_menu(Link l, LinkList head)//����Ա��ҳ�档���Ϊ����Ա��֧ 
{
	login_0(l);
	if(ppj == 1)
	return ;
	
	nn://gotoʱ�õģ����ǹ���Ա�������ʱ�򣬷������沢�ص�����Ա��ҳ�� 
	system("cls");
	while (1)
	{
		char th;
		printf("\n\n\t\t\t\t     �� �� �� �� �� �� վ �� �� Ա ϵ ͳ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.������Ϣ�޸�      *");
		printf("\n\n\t\t\t\t\t*       2.������Ϣ�޸�      *");
		printf("\n\n\t\t\t\t\t*       3.�г�ʱ�̱�        *");
		printf("\n\n\t\t\t\t\t*       4.��·�����ֲ�      *");
		printf("\n\n\t\t\t\t\t*       5.�˳���½          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t�밴�����淨�������в�������� 1 - 6 �У�����ᵼ�´���");
		printf("\n\n\t\t\t\t\t�ǹ���Ա����ʹ�ù���Ա����");
		printf("\n\t\t\tϵͳʱ�����£�");
		time_plus();
		th = getch();
		switch(th)
		{
			case '1':
				{
					rooter_modify(l); 
				}break;
			case '2':
				{
					rooters_menu_train_list(l, head);
					
				}break;
			case '3':
				{
					char rpp[6000];
					if((fp = fopen("High-speed_rail_timetable.txt","r")) == NULL)
					{
						printf("\n\n\t\t\t�޷��򿪣��ȴ�����Ա�޸�");
						system("cls");
						exit(0);
						//����Ūһ��һ������ҳ�� 
					}
					fread(rpp, 2, 3000, fp);
					printf("%s",rpp);
					fclose(fp);
					fflush(stdin);
					printf("\n\n\t\t\t�밴���������...");
					getchar();	
				}break;
			case '4':
				{ 
					char tpp[7000];
					if((fp = fopen("Management_manual.txt","r")) == NULL)
					{
						printf("\n\n\t\t\t�޷��򿪣��ȴ�����Ա�޸�");
						system("cls");
						exit(0);
						//����Ūһ��һ������ҳ�� 
					}
					fread(tpp, 2, 3000, fp);
					printf("\n\n\t\t\t%s",tpp);
					fclose(fp);
					fflush(stdin);
					printf("\n\n\t\t\t�밴���������...");
					getchar();
				}break;
			case '5':
				{
					printf("\n\n\t\t\t\t\t�����˳������Ժ�");
					Sleep(100); 
					return ;
				}break;
			default :
				{
				printf("\t���澯�� \a\a����");//a\�Ƿ����ķ��������� 
				Sleep(100);//���û�һ�����۵�ʱ�䣬��ˢ�½���
				system("cls"); 
				goto nn;
				}break;	
		}
		system ("cls");
	}	
}


void Save(Link l)
{
FILE* fp;
Node *p;
int count=0;
fp=fopen("users.txt", "at+");
if(fp==NULL) /*���ļ�ʧ��*/
{
  printf("\n\n\t\t\t�޷����ļ���\n");
  getchar();
  return ;
}
p=l->next;

while(p)
{
  if(fwrite(p,sizeof(Node),1,fp)==1)/*ÿ��дһ����¼��һ���ڵ���Ϣ���ļ�*/
  { 
   p=p->next;
   count++;
  }
  else
  {
   break;
  }
}
if(count>0)
{
  getchar();
  printf("\n\n\n\n\n\t\t\t\t\t���ڱ����У��������ļ� : %d\n",count);
  getchar();
  saveflag=0;
}
else
{system("cls");
 printf("\n\n\t\t\t\tû�м�¼����\n");
 getchar();
 }
fclose(fp); /*�رմ��ļ�*/
}



int main()
{
	LinkList head;
	head = Read_Info();
  	Link l;      /*��������*/
  	FILE *fp;    /*�ļ�ָ��*/
  	int select;     /*����ѡ��������*/
  	char ch;     /*����(y,Y,n,N)*/
  	int count=0; /*�����ļ��еļ�¼���������������*/
  	Node *p,*r;   /*�����¼ָ�����*/
	
	l = (Node*)malloc(sizeof(Node)) ;
	if(!l)
	{
		printf("\n\n\t\t\tϵͳ�ڴ治�� ��֪ͨ����Ա����ϵͳ���");
		return 0;	 
	}
	l->next = NULL;
	r = l;
	fp = fopen("users.txt", "at+");
	if(fp == NULL)
	{
		printf("\n\n\t\t\t�޷��򿪸��ļ�");
		exit(0);
		
	}
	while(!feof(fp))
	{
		p = (Node*)malloc(sizeof(Node));
	  if(!p)
	   {
 	     printf("\n\n\t\t\tϵͳ�ڴ治�� ��֪ͨ����Ա����ϵͳ���");    /*û�������ڴ�ɹ�*/
	      exit(0);       /*�˳�*/
	   }
	   if(fread(p, sizeof(Node), 1, fp) == 1)
	   {
	   	p->next = NULL;
	   	r->next = p;
	   	r = p;
	   	count++;
	   }
	}
	fclose(fp); /*�ر��ļ�*/
	
	system("cls");
	p = r;
	//Firstin_menu(l); //������ʾ���붯�� 
	in_menu(l,head);//�������˵� 
	return 0;
}









