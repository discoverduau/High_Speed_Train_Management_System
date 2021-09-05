#include<iostream>
#include<cstdio>
#include <time.h>//以下为获取系统时间函数 
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
int rooter_key = 0;//rooter 0为管理员，1为用户 (并用rooter_key传递) 

//再看程序前请先看看下面几段话 
//程序阅读手册（简化版）
//前面是按函数整体进行前置声明的，函数在后面，
//最前排为附件，增加效果和渲染 
//主函数再最后面，清查收
 


//以下两个函数均为管理字体颜色的函数 
enum Color
{
	black, blue, green, lakeBlue, red, purple, yellow, white, gray,
	lightBlue, lightGreen, lightSimpleGreen, lightRed, lightPurple, lightYellow, brightWhite
};


void setColor(unsigned short textColor = 0, unsigned short backColor = 7) {
	char command[9] = "color 07";		//默认颜色	
	command[6] = '0' + backColor;		//将backColor变量改为字符型 
	command[7] = '0' + textColor;		//将textColor变量改为字符型 
	system(command);				//调用系统函数
}


//以下为获取系统时间函数 

	time_t t;
	struct tm * lt;


void time_plus()
{
	time (&t);//获取Unix时间戳。
    lt = localtime (&t);//转为时间结构。
    printf ( "\n\n\t\t\t%d/%d/%d %d:%d:%d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);//输出结果
} 

//以下为用户的有关数据结构 
struct users
{
	char num[10];
	char name[20];
	int age;
	int sex;  //性别 1为男 0为女 
//	char 
//	char 
	int Bad_record;  // 不良记录 0是没有  1是存在
	//int num_car; 坐了几次车 
	char key[20];//密码 
	int rooter;//rooter 1为管理员，0为用户 
};

typedef struct node
{
	
	struct users data;  /*数据域*/
	struct node *next;  /*指针域*/
	
}Node,*Link; /*Node为node类型的结构变量，*Link为node类型的指针变量*/


//
////下面位车站列车查询 

typedef struct
{
	char id[5];//序号 
	char num[100];//车次 
	char departure[50];//始发站 
	char termination[50];//终点站 
	char cost[5];//票价 
	char quantities[5];//数量
	char start[10];//发车时间 
	char end[10];//到达时间 
}TRAIN;//火车信息 
typedef struct NODE
{
	TRAIN data;//数据域 
	struct NODE *next;//指针域 
}NODE, *LinkList;//链表 
static int TEMP = 0;//全局变量0表示没有修改，1有添加，2有修改，3有删除，保存重置为0

//以下为函数声明 

void Firstin_menu(Link l, LinkList head);//用于登陆时的动画和说明界面
void in_menu(Link l, LinkList head);//用于代表用户的登陆主界面
void users_menu(Link l, LinkList head);//用户主页面。这个为用户分支 
void out_sys();//用户退出的界面动画 
void rooters_menu(Link l, LinkList head);//管理员主页面。这个为管理员分支 
void rooters_menu_train_list(Link l, LinkList head) ;

void color_put_menu();

//用函数尾号进而区分用户还是管理员
//1----为用户，   0----为管理员 
//同下 

void register_1(Link l);//注册用户（仅限于用户）xi'xia
void login_0(Link l);//管理员登陆 （仅限于管理员） 
void Login_users(Link l);
void find_car_0(Link l,LinkList head);// 车辆信息查询（同下） 
void find_car_1(Link l,LinkList head);
void find_timeable_0(Link l);// 列车时刻表
void find_timeable_1(Link l);
void person_data_0(Link l); //个人信息管理
void person_data_1(Link l);

void user_disp_0(Link l);//查询个人信息
void user_disp_1(Link l, char searchinput[200]);

void user_modify(Link l);//修改用户信息 
void rooter_modify(Link l);

void Wrong(); 
void stringinput(char *t,int lens,char *notice);


void find_car_users_menu(Link l);

void Save(Link l);
void save_end(Link l);
int saveflag = 0;  /*是否需要存盘的标志变量*/

int Subtraction(Link l ,LinkList head);


void Nofind()  /*输出未查找此教师的信息*/
{
printf("\n=====>Not find this teacher!\n");
}

void printdata(Node *pp) /*格式化输出表中数据*/
{
 Node* p;
 p=pp;
 printf(FORMAT,DATA);

}


void Wrong()  /*输出按键错误信息*/
{
printf("\n\n\n\n\n***********Error:输入错误（这里出现问题）! 按任意键继续**********\n");
getchar();
}



//高铁函数声明//
int add(LinkList head);//添加模块
void Save_u(LinkList head);//保存模块
void Delete(LinkList head);//删除模块
void Update(LinkList head);//更新模块
void Out_Info(TRAIN a);//输出火车信息
//void save();//保存模块
void Save_Info(TRAIN a);//保存火车信息
void Save_List(LinkList head);//保存链表
int TXT_Purse(FILE *fp, TRAIN*a);//文件解析
LinkList Find(LinkList head, TRAIN a, int type);//查找返回一个存数据的链表  
void Push_Head(LinkList head, TRAIN a);//链表头插
void Get_Data(FILE *fp, char *pt);//获得数据 
LinkList CreatList(); 
LinkList appNode(TRAIN a);
int Size(LinkList head);
void Push_Head(LinkList head, TRAIN a);
void Print_List(LinkList head);
void List_DelBy_Id(LinkList head, char *id);
void Select(LinkList head);
LinkList Read_Info();
int Get_Node(FILE *fp, char *pt);
   //链表操作函数//
LinkList CreatList() //创建表头 
{
	LinkList head;
	head = (LinkList)malloc(sizeof(TRAIN));//开辟空间 
	head->next = NULL;//指向NULL 
	return head;
}
LinkList appNode(TRAIN a) //申请一个节点
{
	LinkList node = NULL;
	node = (LinkList)malloc(sizeof(NODE));//开辟空间 
	node->data = a;
	node->next = NULL;
	return node;//返回节点 
}
int Size(LinkList head) //求链表大小除去头结点
{
	int num = 0;
	LinkList p = head;//令P等于头节点 
	while (p != NULL)//当p不是最后一个节点时 
	{
		num++;
		p = p->next;
	}
	return num - 1;//除去头节点 
}
void Push_Head(LinkList head, TRAIN a) //链表头插
{
	LinkList p = head;
	LinkList node = appNode(a);
	if (!p->next)//判断p->next是否为空 
	{
		p->next = node;
	}
	else//插入新节点 
	{
		node->next = head->next;
		head->next = node;
	}

}
LinkList Find(LinkList head, TRAIN a, int form) //链表查找
{
	LinkList p = head->next;
	LinkList findInfo = CreatList();//创建链表储存查找的信息
	int amount = 0;
	if (form == 1)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.id, a.id) == 0)//判断是否有查找的列车序id
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//移到下一节点 
		}
	}
	else if (form == 2)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.num, a.num) == 0)//判断是否有查找的列车的num
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//移到下一节点 
		}
	}
	else if (form == 3)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.departure, a.departure) == 0)//判断是否有查找的列车的departure
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//移到下一节点 
		}
	}
	else if (form == 4)
	{
		while (p != NULL)
		{
			if (strcmp(p->data.termination, a.termination) == 0)//判断是否有查找的列车的terminantion 
			{
				Push_Head(findInfo, p->data);
			}
			p = p->next;//移到下一节点 
		}
	}
	//节点数据统计 
	amount = Size(findInfo);
	if (amount == 0)
		return NULL;
	else
		return findInfo;//返回findInfo链表 

}
void Save_List(LinkList head)
{
	FILE *fp = fopen("train.txt", "w+");//创建文件
	LinkList p = head->next;
	fclose(fp);//关闭文件 
	while (p != NULL)
	{
		Save_Info(p->data);//保存列车信息 
		p = p->next;
	}
	TEMP = 0;
	printf("\t\t\t\t保存到 train.txt  完毕.\n");
}
void Print_List(LinkList head)//打印列车信息 
{
	LinkList p = head->next;
	while (p)//判断p是否为空 
	{
		Out_Info(p->data);//输出列车信息 
		p = p->next;
	}
}
void List_DelBy_Id(LinkList head, char *id)//通过id删除列车信息 
{
	LinkList p = head->next;
	LinkList prep = head;//用于记录上一节点
	if (!p)
	{
		printf("\t\t\t\t没有数据可操作哦！\n");
		return;
	}
	while (p)
	{
		if (strcmp(p->data.id, id) == 0)//判断是否有所查找的列车的id 
		{
			printf("\t\t\t\t删除ing!\n");//上一个节点next指向p的next
			prep->next = p->next;
			free(p);//释放节点 
			printf("\t\t\t\t删除完成！\n");
			TEMP = 3;
			break;
		}
		prep = p;//令prep等于p 
		p = p->next;//p等于下一节点 
	}
	if (!p)
	{
		printf("\t\t\t\t没有该信息\n");
	}
}
//功能模块//
int add(LinkList head)//添加列车信息 
{
	int operation;
	TRAIN a;
	printf("\t\t\t\t请输入添加车次号:");
	scanf("%s", a.num);//获取用户输入 
	printf("\t\t\t\t请输入添加车次出发点:");
	scanf("%s", a.departure);//获取用户输入 
	printf("\t\t\t\t请输入添加车次目的地:");
	scanf("%s", a.termination);//获取用户输入 
	printf("\t\t\t\t请输入添加车次出发时间:");
	scanf("%s", a.start);//获取用户输入 
	printf("\t\t\t\t请输入添加车次到达时间:");
	scanf("%s", a.end);//获取用户输入 
	printf("\t\t\t\t请输入添加车次票价:");
	scanf("%s", a.cost);//获取用户输入 
	printf("\t\t\t\t请输入添加剩余票数量:");
	scanf("%s", a.quantities);//获取用户输入 
	itoa(Size(head) + 1, a.id, 10);
	Push_Head(head, a);//将新添加的列车信息插入到储存列车的链表中 
	TEMP = 1;
	printf("\t\t\t\t添加成功，输入0结束，其他键继续添加:");
	scanf("%d", &operation);//判断继续添加还是结束 
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
		printf("\n\n\t\t\t无法打开，等待管理员修复");
		system("cls");
		exit(0);
	}
	fread(rpp, 2, 50000, fp);
	printf("%s",rpp);
	fflush(stdin);
	fclose(fp);	
	printf("\n\n\n\n\t\t\t以上为上海虹桥火车站所有的列车表，请根据所提供的进行查找");
	printf("\n\n\t\t\t请按任意键继续...");
	getchar();	
	
	int thh;
	int operation;
	LinkList info = NULL;//创建链表 
	TRAIN a;
	int form = 2;
	if(l->data.Bad_record == 1)
	{
		printf("\n\n\t\t\a\a\t亲爱的用户，很抱歉，您存在不良记录已在公安机关登记备案，30天内不允许买票。请谅解");
		printf("\n\n\t\t\t请按任意键继续...");
		getchar();
		printf("\n\n\t\t\t\t正在退出中..");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中.....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中.......");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中.........");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中...........");
			Sleep(600);
			return 0;
		
	}
	
	while(flag_u)
	{
		printf("\n\n\t\t\t\t请输入添加车次号:");
		scanf("%s", a.num);//获取用户输入 
			info = Find(head, a, form);
		if (info)//判断是否查询到列车信息 
		{
			printf("\t\t\t\t找到%d个数据！\n", Size(info));
			Print_List(info);
			break ;
		}
		else{
			printf("\n\n\t\t\t\t很抱歉的通知你，您所输入的车次不存在，请在上图寻找");
			py:
			printf("\n\n\t\t\t退出请输入0,输入1继续");
			scanf("%d", &flag_u);
			if(flag_u != 0 && flag_u != 1)
			goto py;
		} 
	}
	
	printf("\n\n\t\t\t\t是否购票（1：购买,0：不购买)?");
	scanf("%d", &thh);
	if(thh == 1 && a.quantities > 0)
	{
		printf("\n\n\t\t\t购票成功");
	}
	else 
	{
		printf("\n\n\t\t\t感谢您的支持");
	}
	
	printf("\n\t\t\t\t添加成功，输入0结束，其他键继续添加:");
	scanf("%d", &operation);//判断继续添加还是结束 
	system("cls");
	if (operation == 0)
		return 0;
	else
		return 1;
	
}
void Save_u(LinkList head)//保存文件 
{
	FILE *fp;//打开文件 
	printf("\t\t\t\t保存文件ing！\n");
	Save_List(head);
}
void Out_Info(TRAIN a)//打印列车信息 
{
	printf("\t\t\t\t\t\t-----------------------高铁票----------------------\n");
	printf("\t\t\t\t\t\t|序号:   %10s                               |\n", a.id);
	printf("\t\t\t\t\t\t|车次号: %10s                               |\n", a.num);
	printf("\t\t\t\t\t\t|车站:   %10s   开往   %10s           |\n", a.departure, a.termination);
	printf("\t\t\t\t\t\t|时间:   %10s    ->   %10s            |\n", a.start, a.end);
	printf("\t\t\t\t\t\t|票价：  %10s                               |\n", a.cost);
	printf("\t\t\t\t\t\t|数量：  %10s                               |\n", a.quantities);
	printf("\t\t\t\t\t\t---------------------------------------------------\n");
}
void Select(LinkList head)//选择查询列车的方式 
{
	char name[30];//定义数组 
	LinkList info = NULL;//创建链表 
	TRAIN a;
	int form = 1;
	while (1)
	{
		system("cls");
		printf("\n\n\t\t\t\t\t此为上海虹桥火车站的高铁时刻表");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t  1: 序号\n\n\t\t\t\t\t  2: 车次号\n\n\t\t\t\t\t  3: 起点\n\n\t\t\t\t\t  4: 终点\n\n\t\t\t\t\t  5: 退出");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t请输入你要根据什么信息查询相关列车：");
		printf("\n\n\t\t\t\t\t请按照上面法则来经行操作，否则会导致错误\n\n\t\t\t\t请输入：");
		scanf("%d", &form);//获取用户输入 
		if (form == 1)
		{
			printf("\n\n\t\t\t\t请输入你要查询的列车序号:");
			scanf("%s", a.id);
			info = Find(head, a, form);
		if (info)//判断是否查询到列车信息 
		{
			printf("\t\t\t\t找到%d个数据！\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\t没有相关信息喔！\n");
			printf("\n\n\t\t\t\t请输入任意键继续...");
			getchar(); 
			getchar();
		}
		else if (form == 2)
		{
			printf("\n\n\t\t\t\t请输入你要查询的车次号:");
			scanf("%s", a.num);
			info = Find(head, a, form);//调用Find函数通过id查找 
		if (info)//判断是否查询到列车信息 
		{
			printf("\t\t\t\t找到%d个数据！\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\t没有相关信息喔！\n");
			printf("\n\n\t\t\t\t请输入任意键继续...");
			getchar();
			getchar();
		}
		else if (form == 3)
		{
			printf("\n\n\t\t\t\t请输入你要查询的列车起点站:");
			scanf("%s", a.departure);
			info = Find(head, a, form);//调用Find函数通过num查找
		if (info)//判断是否查询到列车信息 
		{
			printf("\t\t\t\t找到%d个数据！\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\t没有相关信息喔！\n");
			printf("\n\n\t\t\t\t请输入任意键继续...");
			getchar();
			getchar();
		}
		else if (form == 4)
		{
			printf("\n\n\t\t\t\t请输入你要查询的列车终点站:");
			scanf("%s", a.termination);
			info = Find(head, a, form);//调用Find函数通过termination查找
		if (info)//判断是否查询到列车信息 
		{
			printf("\t\t\t\t找到%d个数据！\n", Size(info));
			Print_List(info);
		}
		else printf("\t\t\t\t没有相关信息喔！\n");
			printf("\n\n\t\t\t\t请输入任意键继续...");
			getchar();
			getchar();
		}
		else if (form == 5)
		{
			printf("\n\n\t\t\t\t正在退出中..");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中.....");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中.......");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中.........");
			Sleep(200);system("cls");
			printf("\n\n\t\t\t\t正在退出中...........");
			Sleep(600);
			return ;
		}
		else
		{
			printf("\n\n\a\a\t\t\t\t警告输入错误，危险...");
		}
	}
}
void Delete(LinkList head)//删除列车信息 
{
	char id[5];//创建数组 
	printf("\t\t\t\t请输入要删除的列车序号:");
	scanf("%s", id);
	List_DelBy_Id(head, id);//调用List_DeLBy_Id函数删除列车信息 
}
LinkList Read_Info()//读取列车信息 
{
	LinkList info = CreatList();//创建链表储存信息 
	FILE *fp;//打开文件 
	TRAIN a;
	if (!(fp = fopen("train.txt", "r")))
	{
		printf("\t\t\t\t没有保存的数据！\n");
		return(info);
	}
	while (1)
	{
		if (TXT_Purse(fp, &a) == -1)
		{
			break;
		}
		Push_Head(info, a);//调用Push_Head函数 
	}
	fclose(fp);
	return info;
}
void Update(LinkList head)//更新列车信息 
{
	char id[5];//创建数组 
	LinkList p = head->next;//创建指针 
	printf("\t\t\t\t请输入要修改的列车序号:");
	scanf("%s", id);//获取用户输入id 
	if (!p)
	{
		printf("\t\t\t\t没有数据可操作！\n");
		return;
	}
	while (p)
	{
		if (strcmp(p->data.id, id) == 0)//比较输入的列车id和储存的id 
		{
			TRAIN a;
			printf("\t\t\t\t输入$不修改！");
			printf("\t\t\t\t请输入修改的车次号:");
			scanf("%s", a.num);//获取用户输入 
			printf("\t\t\t\t请输入修改的出发点:");
			scanf("%s", a.departure);//获取用户输入 
			printf("\t\t\t\t请输入修改的目的地:");
			scanf("%s", a.termination);//获取用户输入 
			printf("\t\t\t\t请输入修改的出发时间:");
			scanf("%s", a.start);//获取用户输入 
			printf("\t\t\t\t请输入修改的到达时间:");
			scanf("%s", a.end);//获取用户输入 
			printf("\t\t\t\t请输入修改的车次票价:");
			scanf("%s", a.cost);//获取用户输入 
			printf("\t\t\t\t请输入修改的车次可买票数量:");
			scanf("%s", a.quantities);//获取用户输入 
			if (strcmp(a.num, "$") != 0)
				strcpy(p->data.num, a.num);//更改列车车次号 
			if (strcmp(a.departure, "$") != 0)
				strcpy(p->data.departure, a.departure);//更改列车始发站 
			if (strcmp(a.start, "$") != 0)
				strcpy(p->data.start, a.start);//更改列车发车时间 
			if (strcmp(a.termination, "$") != 0)
				strcpy(p->data.termination, a.termination);//更改列车终点站 
			if (strcmp(a.end, "$") != 0)
				strcpy(p->data.end, a.end);//更改列车到达时间 
			if (strcmp(a.cost, "$") != 0)
				strcpy(p->data.cost, a.cost);//更改列车的票价 
			if (strcmp(a.quantities, "$") != 0)
				strcpy(p->data.quantities, a.quantities);//更改列车的车票数量 
			printf("\t\t\t\t修改完毕.\n");
			TEMP = 2;
			break;
		}
		p = p->next;
	}//循环结束
	if (!p)
	{
		printf("\t\t\t\t没有找到该信息喔！\n");
	}
}
//文件解析//
int Get_Node(FILE *fp, char *pt)//从文件中读取数据 
{
	char s;
	int i = 0;
	int ui = 0;
	while (1)
	{
		s = fgetc(fp);//从文件中读取字符 
		if (s == EOF)
		{
			return -1;
		}
		if (s == '<')//判断何时结束读取 
		{
			break;
		}
	}
	//开始读取
	while (1)
	{
		s = fgetc(fp);
		if (s == EOF) //文件结束
		{
			ui = -1;
			break;
		}
		if (s == '>') //节点结束
			break;
		pt[i] = s;//将读取到的数据储存到pt数组中 
		i++;
	}
	pt[i] = '\0';
	return ui;//返回ui 
}
void Save_Info(TRAIN a)//保存文件到train.txt
{
	FILE *fp = fopen("train.txt", "a");//追加
	char contents[500] = { '\0' };
	if (!fp) printf("\t\t\t\t404创建文件失败！");
	else
	{
		strcat(contents, "<train>\n");//将二者连结起来 

		strcat(contents, "\t<id>");
		strcat(contents, a.id);
		strcat(contents, "<\\id>\n");//将三者连结起来 

		strcat(contents, "\t<num>");
		strcat(contents, a.num);
		strcat(contents, "<\\num>\n");//将三者连结起来 

		strcat(contents, "\t<start>");
		strcat(contents, a.start);
		strcat(contents, "<\\start>\n");//将三者连结起来 

		strcat(contents, "\t<end>");
		strcat(contents, a.end);
		strcat(contents, "<\\end>\n");//将三者连结起来 

		strcat(contents, "\t<departure>");
		strcat(contents, a.departure);
		strcat(contents, "<\\departure>\n");//将三者连结起来 

		strcat(contents, "\t<termination>");
		strcat(contents, a.termination);
		strcat(contents, "<\\termination>\n");//将三者连结起来 

		strcat(contents, "\t<cost>");
		strcat(contents, a.cost);
		strcat(contents, "<\\cost>\n");//将三者连结起来 

		strcat(contents, "\t<quantities>");
		strcat(contents, a.quantities);
		strcat(contents, "<\\quantities>\n");//将三者连结起来 

		strcat(contents, "<\\train>\n");
		fputs(contents, fp);
		fclose(fp);//关闭文件 
	}
}
void Get_Data(FILE *fp, char *pt)
{
	char cmt;
	int i = 0;
	while (1)
	{
		cmt = fgetc(fp);
		if (cmt == '<' || cmt == -1) //判断cmt是否到达分界符 
		{
			break;
		}
		if (cmt == '>') //判断cmt是否到达分界符
		{
			continue;
		}
		pt[i] = cmt;//往后移动 
		i++;
	}
	pt[i] = '\0';
}
int TXT_Purse(FILE *fp, TRAIN *a) //文件解析
{
	char node[500];//建立足够大的数组，避免栈错误 
	int  fty = 0;
	if (Get_Node(fp, node) == -1)
	{
		fty = -1;
		return fty;
	} //获得节点
	if (strcmp(node, "train") == 0)
		while (1)
		{
			if (Get_Node(fp, node) == -1)
			{
				fty = -1;
				break;
			}
			if (strcmp(node, "id") == 0)
				Get_Data(fp, a->id);//获得id数据 
			if (strcmp(node, "num") == 0)
				Get_Data(fp, a->num);//获得num数据 
			if (strcmp(node, "start") == 0)
				Get_Data(fp, a->start);//获得start数据 
			if (strcmp(node, "end") == 0)
				Get_Data(fp, a->end);//获得end数据 
			if (strcmp(node, "departure") == 0)
				Get_Data(fp, a->departure);//获得departure数据 
			if (strcmp(node, "termination") == 0)
				Get_Data(fp, a->termination);//获得termination数据 
			if (strcmp(node, "cost") == 0)
				Get_Data(fp, a->cost);//获得cost数据 
			if (strcmp(node, "quantities") == 0)
				Get_Data(fp, a->quantities);//获得quantities数据 
			if (strcmp(node, "\\train") == 0)
				break;
		}
	return fty;

}




//

/*
参数：findmess[]保存要查找的具体内容; nameornum[]保存按什么查找;
    在单链表l中查找;
*/
Node* Locate(Link l,char findmess[],char nameornum[])
{
Node *r;
if(strcmp(nameornum,"num")==0) /*按编号查询*/
{
  r=l->next;
  while(r)
  {
   if(strcmp(r->data.num,findmess)==0) /*若找到findmess值的编号*/
    return r;
   r=r->next;
  }
}
else if(strcmp(nameornum,"name")==0)  /*按姓名查询*/
{
  r=l->next;
  while(r)
  {
   if(strcmp(r->data.name,findmess)==0)    /*若找到findmess值的教师姓名*/
    return r;
   r=r->next;
  }
}
return 0; /*若未找到，返回一个空指针*/
}


/*输入字符串，并进行长度验证(长度<lens)*/
void stringinput(char *t,int lens)
{
   char n[255];
   do{
      scanf("%s",n);  /*输入字符串*/
      if(strlen(n)>lens)
	  printf("\n exceed the required length! \n"); /*进行长度校验，超过lens值重新输入*/
     }while(strlen(n)>lens);
   strcpy(t,n); /*将输入的字符串拷贝到字符串t中*/
}


void register_1(Link l)
{
	Node *p, *r, *s;
	char ch, flag = 0, num[10], hum[20];
	r = l;
	s = l->next;
	//system("cls"); 不知道什么时候加比较好，待会回来看
//	Disp(l); 
	while(l)/*一次可输入多条记录，直至输入编号为0的记录结点添加操作*/
	{
		printf("\n\t\t\t输入0即可返回主菜单：(若继续请输入编号为10位)");
		stringinput(num,10); /*格式化输入编号并检验*/
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
			printf("\n\n\t\t\t此号码没有被注册（可以用该号码）[是否继续？？？(Y/N)]：");
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
			printf("\n\n\t\t\t系统故障，没有更多的存储空间");
			return ;
		}
		strcpy(p->data.num, num);
		printf("\n\t\t\t姓名:");
		stringinput(p->data.name,15);
		printf("\t\t\t性别(1为男 0为女 ):");
		scanf("%d",&p->data.sex);
		printf("\t\t\t年龄(请按真实年龄填写):");
		scanf("%d",&p->data.age);
		//默认开始没有不良记录 
		p->data.Bad_record = 0;
		
		//可以注释掉 
		printf("\t\t\t管理员:");
		scanf("%d",&p->data.rooter);
		// 
		
		while(1)
		{
			printf("\t\t\t密码:");
			stringinput(p->data.key,15);
			printf("\t\t\t再次输入密码:");
			stringinput( hum,15); 
			if(strcmp(p->data.key,hum)!=0)
        	{
        		printf("\n\t\t系统发现两次密码不一致,请重新输入");	
			}
			else break;
		}
  		p->next = NULL; /*表明这是链表的尾部结点*/
 		r->next = p;  /*将新建的结点加入链表尾部中*/
  		r = p;
  		saveflag = 1;
  		
  		Save(l);
	return ;
}

//直接把编号考进来就行，不用另外输入 
void user_disp_1(Link l, char searchinput[200])//查询个人信息和修改 
{
	int select;
	Node *p;
	if(!l->next)
	{
		system("cls");
		printf("\n\n\n\t\t\t不存在任何用户记录(系统故障)");
		printf("\n\n\n\t\t\t请按任意键继续");
		getchar();
		return ; 
	}
	system("cls");
	printf("正在读取中....");
	stringinput(searchinput,100);
	p = Locate(l,searchinput,"num");/*在l中查找编号为searchinput值的节点，并返回节点的指针*/
	if(p) /*若p!=NULL*/
	{
    	printdata(p);
    	printf("\n\n\n\t\t\t按任意键退出");
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
		printf("\n\n\t\t\t不存在用户记录");
		getchar();
		return ;
	}
	system("cls");
	printf("");
	
	//Disp(1)
	
	printf("\n\n\t\t\t请输入用户编号(10位)");
	stringinput(findmess, 10);
	p = Locate(l, findmess, "num");
	
	char th;
	if(p)
	{
		while(1)
		{
		printf("\n\n\t\t\t\t\t此 为 个 人 信 息 表");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t   1.姓名: %s",p->data.name);
		printf("\n\n\t\t\t\t\t   2.年龄: %d",p->data.age);
		printf("\n\n\t\t\t\t\t   3.性别: %d (1为男 0为女 )",p->data.sex);  
		printf("\n\n\t\t\t\t (不可修改)4.不良乘车记录: %d (0是没有  1是存在)",p->data.Bad_record);
		printf("\n\n\t\t\t\t\t   5.退出修改"); 
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\t\t\t\t\t若想修改信息,请输入要修改项的编号,输入 5 退出");
		printf("\n\t\t\t\t\t请按照上面法则来经行操作，否则会导致错误");
		th = getch();
		switch(th)
		{
			case '1':
				{
					printf("\n\n\t\t\t请输入新名字:");
					stringinput(p->data.name,15);
					Sleep(500);
				}break;
			case '2':
				{
					printf("\n\n\t\t\t请输入年龄:");
					scanf("%d", p->data.age);
					Sleep(500);
					
				}break;
			case '3':
				{
					printf("\n\n\t\t\t请输入性别:");
					scanf("%d", p->data.sex);
					Sleep(500);
					
				}break;
			case '4':
				{
					if(p->data.Bad_record == 1)
					{
						printf("\n\n\t\t\t\a您存在不良记录,在2019年不允许乘坐高铁,请见谅");
					}
					printf("\n\n\t\t\t此不可修改,(请按任意键继续...)");
					getchar();	
				}break;
			case '5':
				{
					printf("\n\n\t\t\t\t\t正在安全退出中,请稍后.....");
					Sleep(100);
					return ;
				}break;
			default :
				{
				printf("\t警告警告 \a\a错误，");//a\是发出的蜂鸣警告音 
				Sleep(100);//给用户一个过眼的时间，再刷新界面
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
		printf("\n\n\t\t\t不存在用户记录");
		getchar();
		return ;
	}
	system("cls");
	printf("");
	
	//Disp(1)
	
	printf("\n\n\t\t\t请输入用户编号(10位)");
	stringinput(findmess, 10);
	p = Locate(l, findmess, "num");
	
	char th;
	if(p)
	{
		while(1)
		{
		printf("\n\n\t\t\t\t\t此 为 个 人 信 息 表");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t   1.姓名: %s",p->data.name);
		printf("\n\n\t\t\t\t\t   2.年龄: %d",p->data.age);
		printf("\n\n\t\t\t\t\t   3.性别: %d (1为男 0为女 )",p->data.sex);
		printf("\n\n\t\t\t\t\t   4.不良乘车记录: %d (0是没有  1是存在)",p->data.Bad_record);  
		printf("\n\n\t\t\t\t\t   5.退出修改"); 
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\t\t\t\t\t若想修改信息,请输入要修改项的编号,输入 5 退出");
		th = getch();
		switch(th)
		{
			case '1':
				{
					printf("\n\n\t\t\t请输入新名字:");
					stringinput(p->data.name,15);
					Sleep(500);
				}break;
			case '2':
				{
					printf("\n\n\t\t\t请输入年龄:");
					scanf("%d", p->data.age);
					Sleep(500);
					
				}break;
			case '3':
				{
					printf("\n\n\t\t\t请输入性别:");
					scanf("%d", p->data.sex);
					Sleep(500);
					
				}break;
			case '4':
				{
					printf("\n\n\t\t\t请更改不灵记录:");
					scanf("%d", p->data.Bad_record);
					Sleep(500);
					
				}break;
			case '5':
				{
					printf("\n\n\t\t\t\t\t正在安全退出中,请稍后.....");
					Sleep(100);
					return ;
				}break;
			default :
				{
				printf("\t警告警告 \a\a错误，");//a\是发出的蜂鸣警告音 
				Sleep(100);//给用户一个过眼的时间，再刷新界面
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
	if(saveflag==1) /*若对链表的数据有修改且未进行存盘操作，则此标志为1*/
   { 
   		getchar();
     	printf("\n\n\t\t\t是否将修改后的记录保存到文件中？(y/n):");
     	scanf("%c",&ch);
     	if(ch=='y'||ch=='Y')
       Save(l);
   }
   printf("=====>thank you for useness!");
   getchar();
	
}





//以下为界面函数设定 

void Firstin_menu(Link l)//用于登陆时的动画和说明界面
{
	for(int i = 0; i < 2; i++)//此为登陆动画界面，使用户眼前一亮 
	{
	setColor(0, 1);
	Sleep(50);//此为延时，同下 
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
	printf("\n\n\n\t\t\t\t\t\t\t欢");
	Sleep(100);
	setColor(0, 2);
	printf("\n\n\t\t\t\t\t\t\t欢");
	Sleep(120);
	setColor(0, 3);
	printf("\n\n\t\t\t\t\t\t\t欢");
	Sleep(140);
	setColor(0, 4);
	printf("\n\n\t\t\t\t\t\t\t   迎");
	Sleep(160);
	setColor(0, 5);
	printf("\n\n\t\t\t\t\t\t\t   迎");
	Sleep(180);
	setColor(0, 6);
	printf("\n\n\t\t\t\t\t\t\t   迎");
	Sleep(200);
	setColor(0, 7);
	printf("\n\n\t\t\t\t\t\t\t欢 迎");
	Sleep(220);
	setColor(0, 8);
	printf("\n\n\t\t\t\t\t\t\t欢 迎");
	Sleep(240);
	setColor(0, 9);
	printf("\n\n\t\t\t\t\t\t\t欢 迎");
	Sleep(260);

	system("cls") ;
	
	printf("\n\n\t\t\t\t\t    欢 迎 使 用 本 系 统");
}


void out_sys()//用于退出界面（此退出为程序的大退出和其他小退出分开处理） 
{
	printf("                ********\n");
	setColor(0, 1);
	Sleep(150);//此为延时，同下 
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
    printf("\n\n\n\n\t\t\t 再  见 ");
	printf("\n\n\n\n\t\t欢  迎   下  次  使  用 ");


} 


//登陆 
void Login_users(Link l)
{
	//使用一个全局变量eppy，用来检测是否要二重退出 
    char u[20],c[20],temp_0[20];      //定义两个数组，存放键盘输入的用户名和密码
    char tth;
    char key_u[100];//密码 
    char searchinput[20]; /*保存用户输入的查询内容*/
    Node *p;
    FILE *fp;
    fp = fopen("users.txt","r+");
    if(!l->next) /*若链表为空*/
	{
 	system("cls");
 	printf("\n=====>No record!\n");
  	getchar();
  	return;
	}
	
	op://goto
	
    printf("\n\n\n\t\t\t\t用户登录");
    printf("\n\n\t\t用户编号:");	

    stringinput(searchinput,10);
    printf("\n\t\t用户密码:");	
    scanf("%s", key_u);
    
    p = Locate(l,searchinput,"num");/*在l中查找编号为searchinput值的节点，并返回节点的指针*/
    if(p) /*若p!=NULL*/
	{
		if(strcmp(p->data.key, key_u) != 0)
		{
			printf("\n\n\t\t\t密码错误,请重新输入\a\a"); 
			scanf("%s", key_u);
			if(strcmp(p->data.key, key_u) != 0)
			{
				eppy = 1;
				printf("\n\n\t\t\t密码错误\a\a");
				printf("\n\n\t\t\t自动返回主页面\a\a");
				Sleep(100);
				fclose(fp); 
				return ; 
			}
		}
		else 
		{
			printf("\n\n\t\t\t欢迎登陆");
		}
		fclose(fp); 
    	getchar();
   }
   else
   {
   		while(1)
   		{
   			printf("\n\n\t\t\t\t用户不存在,请选择以下方式:");
   			printf("\n\t\t1.返回主页面注册   2.重新登陆");
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
			else printf("\n\n\t\t\t警告警告 \a\a错误，");
			
		}
   		
   }

}

void login_0(Link l)
{
	//使用一个全局变量ppj，用来检测是否要二重退出 
    char u[20],c[20],temp_0[20];      //定义两个数组，存放键盘输入的用户名和密码
    char tth;
    char key_u[100];//密码 
    char searchinput[20]; /*保存用户输入的查询内容*/
    Node *p;
    FILE *fp;
    fp = fopen("users.txt","r+");
    if(!l->next) /*若链表为空*/
	{
 	system("cls");
 	printf("\n=====>No record!\n");
  	getchar();
  	return;
	}
	
	op://goto
	
    printf("\n\n\n\t\t\t\t管理员登录");
    printf("\n\n\t\t管理员编号:");	
	stringinput(searchinput,10);
	
    printf("\n\t\t管理员密码:");	
    scanf("%s", key_u);
    
    
    p = Locate(l,searchinput,"num");/*在l中查找编号为searchinput值的节点，并返回节点的指针*/
	if(p->data.rooter != 1)
		{
			printf("\n\n\a\a\t\t\t\t抱歉，您没有管理员权限,正在强制退出");
			ppj = 1; 
			Sleep(1000);
			return ;
		}
    if(p) /*若p!=NULL*/
	{
    	
		if(strcmp(p->data.key, key_u) != 0)
		{
			printf("\n\n\t\t\t密码错误,请重新输入\n\t\t\t\a\a"); 
			scanf("%s", key_u);
			if(strcmp(p->data.key, key_u) != 0)
			{
				ppj = 1;
				printf("\n\n\t\t\t密码错误\a\a");
				printf("\n\n\t\t\t自动返回主页面\a\a");
				Sleep(100);
				fclose(fp); 
				return ; 
			}
		}
		else 
		{
			printf("\n\n\t\t\t欢迎登陆");
		}
		fclose(fp); 
    	getchar();
   }
   else
   {
   		while(1)
   		{
   			printf("\n\n\t\t\t\t用户不存在,请选择以下方式:");
   			printf("\n\t\t1.返回主页面注册   2.重新登陆");
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
			else printf("\n\n\t\t\t警告警告 \a\a错误，");
			
		}
   		
   }

}


void color_put_menu()
{
		char th;
		printf("\n\n\t\t\t\t\t    选 一 种 你 喜 欢 的 颜 色 ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t******************************************");
		printf("\n\n\t\t\t\t\t*     0 = 白色        5 = 紫色           *");
		printf("\n\n\t\t\t\t\t*     1 = 蓝色        6 = 黄色           *");
		printf("\n\n\t\t\t\t\t*     2 = 绿色        7 = 浅灰色          *");
		printf("\n\n\t\t\t\t\t*     3 = 浅绿色      8 = 灰色           *");
		printf("\n\n\t\t\t\t\t*     4 = 红色        9 = 淡蓝色         *");
		printf("\n\n\t\t\t\t\t******************************************");
		printf("\n\n\t\t\t\t\t请按照上面法则来经行操作，否则会导致错误");
		th = getch();
		switch(th)
		{
			case '0':
				{
					setColor(0, 0);	
				}break;
			case '1'://用户登陆接口 
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
				printf("\t警告警告 \a\a错误，");//a\是发出的蜂鸣警告音 
				Sleep(100);//给用户一个过眼的时间，再刷新界面
				system("cls"); 			
				}break;			
		}
		system("cls");
}


//以下为分支页面管理




//以下为主菜单设置 

void in_menu(Link l, LinkList head)//用于代表用户的登陆主界面
{
	color_put_menu();
	nn://同下
	while (1)
	{
		char th;
		printf("\n\n\t\t\t\t\t    上 海 虹 桥 火 车 站 ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.用户登陆          *");
		printf("\n\n\t\t\t\t\t*       2.用户注册          *");
		printf("\n\n\t\t\t\t\t*       3.退出登陆          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       0.管理员系统        *");
		printf("\n\n\t\t\t\t\t请按照上面法则来经行操作，否则会导致错误");
		printf("\n\n\t\t\t\t\t非管理员请勿使用管理员功能");
		printf("\n\t\t\t系统时间如下："); 
		time_plus();
		th = getch();
		switch(th)
		{
			case '0':
				{
					system("cls");
					rooters_menu(l,head);
					//管理员主页面	
				}break;
			case '1'://用户登陆接口 
				{
					system("cls");
					users_menu(l,head);//用户主页面 
				}break;
			case '2':
				{
					register_1(l);//用户注册 
				}break;
			case '3':
				{
					save_end(l);
					printf("\n\n\t\t\t\t\t正在退出中请稍后");
					out_sys();//退出函数，（即为图形界面） 
					return ;
				}break;
			default :
				{
				printf("\t警告警告 \a\a错误，");//a\是发出的蜂鸣警告音 
				Sleep(100);//给用户一个过眼的时间，再刷新界面
				system("cls"); 
				goto nn;			
				}break;			
		}
		system ("cls");
	}
}



void users_menu(Link l,LinkList head)//用户主页面。这个为用户分支 
{
	Login_users(l);
	if(eppy == 1)
	{
		printf("\n\n\t\t\t\t密码错误自动退回主页面");
		Sleep(1000);
		return ;
	}
	FILE *fp, *pp;
	
	
	nn://功能同下（管理员界面）即为goto语句的转换 
	system("cls");
	while (1)
	{
		char th;
		printf("\n\n\t\t\t\t\t    上 海 虹 桥 火 车 站 ");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.个人信息管理      *");
		printf("\n\n\t\t\t\t\t*       2.车辆信息查询      *");
		printf("\n\n\t\t\t\t\t*       3.列车时刻表        *");
		printf("\n\n\t\t\t\t\t*       4.购票              *");
		printf("\n\n\t\t\t\t\t*       5.铁路管理手册      *");
		printf("\n\n\t\t\t\t\t*       6.退出登陆          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t请按照上面法则来经行操作，点击1-5中，否则会导致错误");
		printf("\n\n\t\t\t\t\t非管理员请勿使用管理员功能");
		printf("\n\t\t\t系统时间如下：");
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
						printf("\n\n\t\t\t无法打开，等待管理员修复");
						system("cls");
						exit(0);
						//可以弄一个一键保修页面 
					}
					fread(rpp, 2, 3000, fp);
					printf("%s",rpp);	
					fclose(fp);
					fflush(stdin);
					fflush(stdin);
					printf("\n\n\t\t\t请按任意键继续...");
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
						printf("\n\n\t\t\t无法打开，等待管理员修复");
						system("cls");
						exit(0);
						//可以弄一个一键保修页面 
					}
					fread(tpp, 2, 3000, pp);
					printf("\n\n\t\t\t%s",tpp);	
					fclose(pp);
					fflush(stdin);
					fflush(stdin);
					printf("\n\n\t\t\t请按任意键继续...");
					getchar();
				}break;
			case '6':
				{
					printf("\n\n\t\t\t\t\t正在退出中请稍后");
					Sleep(100); 
					out_sys();
					exit(0);
					
				}break;
			default :
				{
				printf("\t警告警告 \a\a错误，");//a\是发出的蜂鸣警告音 
				Sleep(100);//给用户一个过眼的时间，再刷新界面
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
		printf("\n\n\t\t\t\t     上 海 虹 桥 火 车 站 管 理 员 系 统");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.添加车次信息      *");
		printf("\n\n\t\t\t\t\t*       2.查询车次信息      *");
		printf("\n\n\t\t\t\t\t*       3.列车时刻表        *");
		printf("\n\n\t\t\t\t\t*       4.更新车次信息      *");
		printf("\n\n\t\t\t\t\t*       5.删除车次信息      *");
		printf("\n\n\t\t\t\t\t*       6.退出登陆          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t请按照上面法则来经行操作，点击1-5中，否则会导致错误");
		printf("\n\n\t\t\t\t\t非管理员请勿使用管理员功能");
		printf("\n\t\t\t系统时间如下：");
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
						printf("\n\n\t\t\t无法打开，等待管理员修复");
						system("cls");
						exit(0);
						//可以弄一个一键保修页面 
					}
					fread(rpp, 2, 50000, fp);
					printf("%s",rpp);
					fflush(stdin);
					fclose(fp);	
					printf("\n\n\t\t\t请按任意键继续...");
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
					printf("\n\n\t\t\t\t\t正在退出中请稍后");
					Sleep(100); 
					return ;
				}break;
			default :
				{
				printf("\t警告警告 \a\a错误，");//a\是发出的蜂鸣警告音 
				Sleep(100);//给用户一个过眼的时间，再刷新界面
				system("cls"); 
				goto nn;
					
				}break;			
		}
		system ("cls");
	}	
	
}



void rooters_menu(Link l, LinkList head)//管理员主页面。这个为管理员分支 
{
	login_0(l);
	if(ppj == 1)
	return ;
	
	nn://goto时用的，就是管理员按错键的时候，发出警告并回到管理员主页面 
	system("cls");
	while (1)
	{
		char th;
		printf("\n\n\t\t\t\t     上 海 虹 桥 火 车 站 管 理 员 系 统");
		printf("\n\n\t\t\t\t\t\t   M E N U");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t*       1.个人信息修改      *");
		printf("\n\n\t\t\t\t\t*       2.车辆信息修改      *");
		printf("\n\n\t\t\t\t\t*       3.列车时刻表        *");
		printf("\n\n\t\t\t\t\t*       4.铁路管理手册      *");
		printf("\n\n\t\t\t\t\t*       5.退出登陆          *");
		printf("\n\n\t\t\t\t\t*****************************");
		printf("\n\n\t\t\t\t\t请按照上面法则来经行操作，点击 1 - 6 中，否则会导致错误");
		printf("\n\n\t\t\t\t\t非管理员请勿使用管理员功能");
		printf("\n\t\t\t系统时间如下：");
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
						printf("\n\n\t\t\t无法打开，等待管理员修复");
						system("cls");
						exit(0);
						//可以弄一个一键保修页面 
					}
					fread(rpp, 2, 3000, fp);
					printf("%s",rpp);
					fclose(fp);
					fflush(stdin);
					printf("\n\n\t\t\t请按任意键继续...");
					getchar();	
				}break;
			case '4':
				{ 
					char tpp[7000];
					if((fp = fopen("Management_manual.txt","r")) == NULL)
					{
						printf("\n\n\t\t\t无法打开，等待管理员修复");
						system("cls");
						exit(0);
						//可以弄一个一键保修页面 
					}
					fread(tpp, 2, 3000, fp);
					printf("\n\n\t\t\t%s",tpp);
					fclose(fp);
					fflush(stdin);
					printf("\n\n\t\t\t请按任意键继续...");
					getchar();
				}break;
			case '5':
				{
					printf("\n\n\t\t\t\t\t正在退出中请稍后");
					Sleep(100); 
					return ;
				}break;
			default :
				{
				printf("\t警告警告 \a\a错误，");//a\是发出的蜂鸣警告音 
				Sleep(100);//给用户一个过眼的时间，再刷新界面
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
if(fp==NULL) /*打开文件失败*/
{
  printf("\n\n\t\t\t无法打开文件。\n");
  getchar();
  return ;
}
p=l->next;

while(p)
{
  if(fwrite(p,sizeof(Node),1,fp)==1)/*每次写一条记录或一个节点信息至文件*/
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
  printf("\n\n\n\n\n\t\t\t\t\t正在保存中，共保存文件 : %d\n",count);
  getchar();
  saveflag=0;
}
else
{system("cls");
 printf("\n\n\t\t\t\t没有记录保存\n");
 getchar();
 }
fclose(fp); /*关闭此文件*/
}



int main()
{
	LinkList head;
	head = Read_Info();
  	Link l;      /*定义链表*/
  	FILE *fp;    /*文件指针*/
  	int select;     /*保存选择结果变量*/
  	char ch;     /*保存(y,Y,n,N)*/
  	int count=0; /*保存文件中的记录条数（或结点个数）*/
  	Node *p,*r;   /*定义记录指针变量*/
	
	l = (Node*)malloc(sizeof(Node)) ;
	if(!l)
	{
		printf("\n\n\t\t\t系统内存不够 请通知管理员进行系统检测");
		return 0;	 
	}
	l->next = NULL;
	r = l;
	fp = fopen("users.txt", "at+");
	if(fp == NULL)
	{
		printf("\n\n\t\t\t无法打开该文件");
		exit(0);
		
	}
	while(!feof(fp))
	{
		p = (Node*)malloc(sizeof(Node));
	  if(!p)
	   {
 	     printf("\n\n\t\t\t系统内存不够 请通知管理员进行系统检测");    /*没有申请内存成功*/
	      exit(0);       /*退出*/
	   }
	   if(fread(p, sizeof(Node), 1, fp) == 1)
	   {
	   	p->next = NULL;
	   	r->next = p;
	   	r = p;
	   	count++;
	   }
	}
	fclose(fp); /*关闭文件*/
	
	system("cls");
	p = r;
	//Firstin_menu(l); //先是显示进入动画 
	in_menu(l,head);//这是主菜单 
	return 0;
}









