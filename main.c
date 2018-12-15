#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define LEN sizeof(struct teacher)//宏定义结构体字节数
int n=0;
struct teacher//定义结构体
{
	long num;//教师号
	char name[20];//姓名
	char sex[5];//性别
	int age;//年龄
	char edu[20];//学历
	char title[20];//职称
	long wage;//工资
	char addr[100];//地址
	char telep[15];//电话
	struct teacher *next;//指向下一个结点
}*head=NULL;
void key()
{
	int i;
	long a;
	for(i=0;i<3;i++)
	{
		printf("请输入学号(还可输入%d次)：\n",3-i);
    	scanf("%ld",&a);
		if(a==1714010234)
		{
			printf("欢迎进入系统\n");
			break;
		}
		else printf("口令错误\n");
	}
	if(i==3)
	{
		printf("可使用的口令输入次数已用完，将自动退出！\n");
		exit(0);
	}
}
void save()
{
	FILE *fp;
	int i;
	char filename[20];
	struct teacher *p;
	printf("\n        是否把此次登录系统录入和修改后的教师信息保存到文件中\n");
	printf("                       1:【是】                    0:【否】\n请选择：");
	scanf("%d",&i);
	while((i!=0)&&(i!=1))
	{
		printf("选择无效，请重新输入正确选项：");
		scanf("%d",&i);
	}
	if(i==1)
	{
		printf("\n请输入要保存数据的文件名：");
	    scanf("%s",filename);
	    if((fp=fopen(filename,"wb"))==NULL)
		{
			printf("\n无法打开文件\n");
		    exit(0);
		}
	    for(p=head;p!=NULL;p=p->next)
		    if(fwrite(p,sizeof(struct teacher),1,fp)!=1)
			    printf("\n此处数据有误\n");
		fclose(fp);
	}
	exit(0);
}
void read()
{
	struct teacher teach[299],temp;
	int i=0;
	FILE *fp;
	char filename[20];
	printf("\n请输入存有教师信息的文件名：");
	scanf("%s",filename);
    if((fp=fopen(filename,"rb"))==NULL)
	{printf("\n无法打开文件\n");
		exit(0);
	}
	fseek(fp,-sizeof(struct teacher),2);
	fread(&temp,sizeof(struct teacher),1,fp);
	fseek(fp,0,0);
	if(fread(&teach[i],sizeof(struct teacher),1,fp)==1)
	{
		printf("\n存有的教师信息如下:\n");
		while(teach[i].num!=temp.num)
		{
			printf("教师号:%ld,姓名:%s,性别:%s,年龄:%d,学历:%s,",teach[i].num,teach[i].name,teach[i].sex,teach[i].age,teach[i].edu);
		    printf("职称:%s\n    月薪:%ld,住址:%s,电话:%s\n",teach[i].title,teach[i].wage,teach[i].addr,teach[i].telep);
		    i=i+1;
		    fread(&teach[i],sizeof(struct teacher),1,fp);
		}

        printf("教师号:%ld,姓名:%s,性别:%s,年龄:%d,学历:%s,",teach[i].num,teach[i].name,teach[i].sex,teach[i].age,teach[i].edu);
	    printf("职称:%s\n    月薪:%ld,住址:%s,电话:%s\n",teach[i].title,teach[i].wage,teach[i].addr,teach[i].telep);
	    fclose(fp);
	}
	else printf("该文件中无教师信息\n");
}
void creat()
{
	struct teacher *p1,*p2,*p3;
	p1=p2=(struct teacher *)malloc(LEN);
	printf("请输入一位教师的教师号（结束录入请输入0）：");
	scanf("%ld",&p1->num);
	if(p1->num!=0)
		if(head==NULL) head=p1;
		else
		{
			p3=head;
			while(p3->next!=NULL)
				p3=p3->next;
			p3->next=p1;
		}
	while(p1->num!=0)
	{

		printf("姓名: ");
		scanf("%s",p1->name);
		printf("性别：");
		scanf("%s",p1->sex);
		printf("年龄：");
		scanf("%d",&p1->age);
		printf("学历：");
		scanf("%s",p1->edu);
		printf("职称：");
		scanf("%s",p1->title);
		printf("月薪：");
		scanf("%ld",&p1->wage);
		printf("住址：");
		scanf("%s",p1->addr);
		printf("电话：");
		scanf("%s",p1->telep);
		n=n+1;
	   if(n==1) head=p1;
      else p2->next=p1;
		p2=p1;
		p1=(struct teacher *)malloc(LEN);
		printf("请输入一位教师的教师号(结束录入请输入0): ");
		scanf("%ld",&p1->num);
	}
	p2->next=NULL;
}
void print()
{
	struct teacher *p;
	int i;
	p=head;
	if(head!=NULL)
	{
    	printf("\n这%d位教师的信息为:\n",n);
		do
		{
			printf("教师号:%ld,姓名:%s,性别:%s,年龄:%d,学历:%s,职称:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    月薪:%ld,住址:%s,电话:%s\n",p->wage,p->addr,p->telep);
			p=p->next;
		}while(p!=NULL);
	}
	else
	{
		printf("\n你此次登录系统还没有录入教师信息，可进行以下操作：\n");
		printf("         1:【浏览以前保存在文件中的教师信息】             2:【开始录入教师信息】\n");
		printf("         3:【退出系统】                                   4:【返回菜单】\n");
		printf("请选择：");
		scanf("%d",&i);
		while((i<1)&&(i>4))
		{
			printf("选择无效，请重新输入正确选项：");
			scanf("%d",&i);
		}
		if(i==1) read();
	    if(i==2) creat();
		if(i==3) exit(0);
	}
}
void del()
{
	struct teacher *p1,*p2;
	long i;
	if(head==NULL)
	{
		printf("\n还未录入过教师信息\n");
		return;
	}
	printf("请输入要删除教师信息的教师号：");
	scanf("%ld",&i);
	p1=head;
	while(i!=p1->num)
	{
		if(p1->next==NULL) break;
		p2=p1;
		p1=p1->next;
	}
	if(i==p1->num)
	{
		if(p1==head) head=p1->next;
		else p2->next=p1->next;
		printf("\n已删除教师号为%ld的教师信息\n",i);
		n=n-1;
	}

	else printf("\n已录入的教师信息中没有教师号为%ld的\n",i);
	return;
}
void sort1()
{
	struct teacher *p1,*p2,*p3,*p4;
	int i,j;
	if(head==NULL)
	{printf("\n还未录入过教师信息\n");
			return;
	}
	if(head->next!=NULL)
	{
		p1=head;
	    p2=head->next;
	    for(i=1;i<n;i++)
		{
		    for(j=0;j<n-i;j++)
			{
			    if(p1->num>p2->num)
				{
					if(p1==head) head=p2;
					else p3->next=p2;
					p4=p2->next;
					p2->next=p1;
					p1->next=p4;
					p3=p2;
					p2=p4;
				}
				else
				{
					p3=p1;
					p1=p2;
					p2=p2->next;
				}
			}
			p1=head;
			p2=p1->next;
		}
	}
	printf("\n按教师号排序后的教师信息如下：\n");
	print();
}
void sort2()
{
	struct teacher *p1,*p2,*p3,*p4;
	int i,j;
	if(head==NULL)
	{
		printf("\n还未录入过教师信息\n");
		return;
	}
	if(head->next!=NULL)
	{
		p1=head;
	    p2=head->next;
	    for(i=1;i<n;i++)
		{
		    for(j=0;j<n-i;j++)
			{
			    if(p1->wage>p2->wage)
				{
					if(p1==head) head=p2;
					else p3->next=p2;
					p4=p2->next;
					p2->next=p1;
					p1->next=p4;
					p3=p2;
					p2=p4;
				}
				else
				{
					p3=p1;
					p1=p2;
					p2=p2->next;
				}
			}
			p1=head;
			p2=p1->next;
		}
	}
	printf("\n按月薪排序后的教师信息如下：\n");
	print();
}
void sort3()
{
	struct teacher *p1,*p2,*p3,*p4;
	int i,j;
    if(head==NULL)
	{
		printf("\n还未录入过教师信息\n");
		return;
	}
	if(head->next!=NULL)
	{
		p1=head;
	    p2=head->next;
	    for(i=1;i<n;i++)
		{
		    for(j=0;j<n-i;j++)
			{
			    if(p1->age>p2->age)
				{
					if(p1==head) head=p2;
					else p3->next=p2;
					p4=p2->next;
					p2->next=p1;
					p1->next=p4;
					p3=p2;
					p2=p4;
				}
				else
				{
					p3=p1;
					p1=p2;
					p2=p2->next;
				}
			}
			p1=head;
			p2=p1->next;
		}
	}
	printf("\n按年龄排序后的教师信息如下：\n");
	print();
}
void choose1()
{
	int i;
	printf("                                   排序方式\n");
	printf("           1:【按教师号排序】                    2:【按年龄排序】\n");
	printf("           3:【按月薪排序】\n");
	printf("请选择：");
	scanf("%d",&i);
    	while((i<1)||(i>3))
	{
		printf("选择无效，请重新输入正确选项：");
		scanf("%d",&i);
	}
	switch(i)
	{
	    case 1:sort1();break;
	    case 2:sort3();break;
	    case 3:sort2();break;
	}
}
void search1()
{
	struct teacher *p;
	long i;
	if(head==NULL)
	{
		printf("\n还未录入过教师信息\n");
		return;
	}
	printf("请输入要查找的教师信息的教师号：");
    scanf("%ld",&i);
	for(p=head;p!=NULL;p=p->next)

		if(p->num==i)
		{
            printf("教师号:%ld,姓名:%s,性别:%s,年龄:%d,学历:%s,职称:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    月薪:%ld,住址:%s,电话:%s\n",p->wage,p->addr,p->telep);
			return;
		}
	printf("已录入的教师信息中不存在该教师号\n");
}
void search2()
{
	struct teacher *p;
	char i[20];
	int j=0;
	if(head==NULL)
	{
		printf("\n还未录入过教师信息\n");
		return;
	}
	printf("请输入要查找的信息的教师姓名：");
    scanf("%s",i);
	for(p=head;p!=NULL;p=p->next)
		if(strcmp(p->name,i)==0)

		{
            printf("教师号:%ld,姓名:%s,性别:%s,年龄:%d,学历:%s,职称:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    月薪:%ld,住址:%s,电话:%s\n",p->wage,p->addr,p->telep);
			j=j+1;
		}
	if(j==0) printf("已录入的教师信息中不存在该姓名的教师\n");
}
void search3()
{
	struct teacher *p;
	char i[20];
	int j=0;
	if(head==NULL)
	{
		printf("\n还未录入过教师信息\n");
		return;
	}
	printf("请输入要查找的信息的教师职称：");
    scanf("%s",i);
	for(p=head;p!=NULL;p=p->next)
		if(strcmp(p->title,i)==0)
		{
            printf("教师号:%ld,姓名:%s,性别:%s,年龄:%d,学历:%s,职称:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    月薪:%ld,住址:%s,电话:%s\n",p->wage,p->addr,p->telep);
		    j=j+1;
		}
	if(j==0) printf("已录入的教师信息中不存在该职称的教师\n");
}
void search4()
{
	struct teacher *p;
	int i,j=0;
	if(head==NULL)
	{
		printf("\n还未录入过教师信息\n");
		return;
	}
	printf("请输入要查找的信息的教师年龄：");
    scanf("%d",&i);
	for(p=head;p!=NULL;p=p->next)
		if(p->age==i)
		{
			printf("教师号:%ld,姓名:%s,性别:%s,年龄:%d,学历:%s,职称:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    月薪:%ld,住址:%s,电话:%s\n",p->wage,p->addr,p->telep);
		    j=j+1;
		}
	if(j==0) printf("已录入的教师信息中不存在该年龄的教师\n");
}
void choose2()
{
	int i;
	printf("                                   查询方式\n");
	printf("             1:【按教师号查询】                   2:【按姓名查询】\n");
	printf("             3:【按职称查询】                     4:【按年龄查询】\n");
	printf("请选择：");
	scanf("%d",&i);
	while((i<1)||(i>4))
	{
		printf("选择无效，请重新输入正确选项：");
		scanf("%d",&i);
	}
	switch(i)
	{
	    case 1:search1();break;
	    case 2:search2();break;
	    case 3:search3();break;
		case 4:search4();break;
	}
}
void menu()
{
	int i;
	printf("                                      菜单\n");
	printf("               1:【教师信息录入】                2:【教师信息输出】\n");
	printf("               3:【教师信息删除】                4:【查询个人信息】\n");
	printf("               5:【排序】                        6:【退出系统】\n");
	printf("请选择: ");
	scanf("%d",&i);
	while((i<1)||(i>6))
	{
		printf("选择无效，请重新输入正确选项：");
		scanf("%d",&i);
	}
	switch(i)
	{
	    case 1:creat();break;
	    case 2:print();break;
	    case 3:del();break;
	    case 4:choose2();break;
	    case 5:choose1();break;
	    case 6:save();
	}
	menu();
}
void main()
{
	key();
	menu();
}
