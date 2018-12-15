#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define LEN sizeof(struct teacher)//�궨��ṹ���ֽ���
int n=0;
struct teacher//����ṹ��
{
	long num;//��ʦ��
	char name[20];//����
	char sex[5];//�Ա�
	int age;//����
	char edu[20];//ѧ��
	char title[20];//ְ��
	long wage;//����
	char addr[100];//��ַ
	char telep[15];//�绰
	struct teacher *next;//ָ����һ�����
}*head=NULL;
void key()
{
	int i;
	long a;
	for(i=0;i<3;i++)
	{
		printf("������ѧ��(��������%d��)��\n",3-i);
    	scanf("%ld",&a);
		if(a==1714010234)
		{
			printf("��ӭ����ϵͳ\n");
			break;
		}
		else printf("�������\n");
	}
	if(i==3)
	{
		printf("��ʹ�õĿ���������������꣬���Զ��˳���\n");
		exit(0);
	}
}
void save()
{
	FILE *fp;
	int i;
	char filename[20];
	struct teacher *p;
	printf("\n        �Ƿ�Ѵ˴ε�¼ϵͳ¼����޸ĺ�Ľ�ʦ��Ϣ���浽�ļ���\n");
	printf("                       1:���ǡ�                    0:����\n��ѡ��");
	scanf("%d",&i);
	while((i!=0)&&(i!=1))
	{
		printf("ѡ����Ч��������������ȷѡ�");
		scanf("%d",&i);
	}
	if(i==1)
	{
		printf("\n������Ҫ�������ݵ��ļ�����");
	    scanf("%s",filename);
	    if((fp=fopen(filename,"wb"))==NULL)
		{
			printf("\n�޷����ļ�\n");
		    exit(0);
		}
	    for(p=head;p!=NULL;p=p->next)
		    if(fwrite(p,sizeof(struct teacher),1,fp)!=1)
			    printf("\n�˴���������\n");
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
	printf("\n��������н�ʦ��Ϣ���ļ�����");
	scanf("%s",filename);
    if((fp=fopen(filename,"rb"))==NULL)
	{printf("\n�޷����ļ�\n");
		exit(0);
	}
	fseek(fp,-sizeof(struct teacher),2);
	fread(&temp,sizeof(struct teacher),1,fp);
	fseek(fp,0,0);
	if(fread(&teach[i],sizeof(struct teacher),1,fp)==1)
	{
		printf("\n���еĽ�ʦ��Ϣ����:\n");
		while(teach[i].num!=temp.num)
		{
			printf("��ʦ��:%ld,����:%s,�Ա�:%s,����:%d,ѧ��:%s,",teach[i].num,teach[i].name,teach[i].sex,teach[i].age,teach[i].edu);
		    printf("ְ��:%s\n    ��н:%ld,סַ:%s,�绰:%s\n",teach[i].title,teach[i].wage,teach[i].addr,teach[i].telep);
		    i=i+1;
		    fread(&teach[i],sizeof(struct teacher),1,fp);
		}

        printf("��ʦ��:%ld,����:%s,�Ա�:%s,����:%d,ѧ��:%s,",teach[i].num,teach[i].name,teach[i].sex,teach[i].age,teach[i].edu);
	    printf("ְ��:%s\n    ��н:%ld,סַ:%s,�绰:%s\n",teach[i].title,teach[i].wage,teach[i].addr,teach[i].telep);
	    fclose(fp);
	}
	else printf("���ļ����޽�ʦ��Ϣ\n");
}
void creat()
{
	struct teacher *p1,*p2,*p3;
	p1=p2=(struct teacher *)malloc(LEN);
	printf("������һλ��ʦ�Ľ�ʦ�ţ�����¼��������0����");
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

		printf("����: ");
		scanf("%s",p1->name);
		printf("�Ա�");
		scanf("%s",p1->sex);
		printf("���䣺");
		scanf("%d",&p1->age);
		printf("ѧ����");
		scanf("%s",p1->edu);
		printf("ְ�ƣ�");
		scanf("%s",p1->title);
		printf("��н��");
		scanf("%ld",&p1->wage);
		printf("סַ��");
		scanf("%s",p1->addr);
		printf("�绰��");
		scanf("%s",p1->telep);
		n=n+1;
	   if(n==1) head=p1;
      else p2->next=p1;
		p2=p1;
		p1=(struct teacher *)malloc(LEN);
		printf("������һλ��ʦ�Ľ�ʦ��(����¼��������0): ");
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
    	printf("\n��%dλ��ʦ����ϢΪ:\n",n);
		do
		{
			printf("��ʦ��:%ld,����:%s,�Ա�:%s,����:%d,ѧ��:%s,ְ��:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    ��н:%ld,סַ:%s,�绰:%s\n",p->wage,p->addr,p->telep);
			p=p->next;
		}while(p!=NULL);
	}
	else
	{
		printf("\n��˴ε�¼ϵͳ��û��¼���ʦ��Ϣ���ɽ������²�����\n");
		printf("         1:�������ǰ�������ļ��еĽ�ʦ��Ϣ��             2:����ʼ¼���ʦ��Ϣ��\n");
		printf("         3:���˳�ϵͳ��                                   4:�����ز˵���\n");
		printf("��ѡ��");
		scanf("%d",&i);
		while((i<1)&&(i>4))
		{
			printf("ѡ����Ч��������������ȷѡ�");
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
		printf("\n��δ¼�����ʦ��Ϣ\n");
		return;
	}
	printf("������Ҫɾ����ʦ��Ϣ�Ľ�ʦ�ţ�");
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
		printf("\n��ɾ����ʦ��Ϊ%ld�Ľ�ʦ��Ϣ\n",i);
		n=n-1;
	}

	else printf("\n��¼��Ľ�ʦ��Ϣ��û�н�ʦ��Ϊ%ld��\n",i);
	return;
}
void sort1()
{
	struct teacher *p1,*p2,*p3,*p4;
	int i,j;
	if(head==NULL)
	{printf("\n��δ¼�����ʦ��Ϣ\n");
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
	printf("\n����ʦ�������Ľ�ʦ��Ϣ���£�\n");
	print();
}
void sort2()
{
	struct teacher *p1,*p2,*p3,*p4;
	int i,j;
	if(head==NULL)
	{
		printf("\n��δ¼�����ʦ��Ϣ\n");
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
	printf("\n����н�����Ľ�ʦ��Ϣ���£�\n");
	print();
}
void sort3()
{
	struct teacher *p1,*p2,*p3,*p4;
	int i,j;
    if(head==NULL)
	{
		printf("\n��δ¼�����ʦ��Ϣ\n");
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
	printf("\n�����������Ľ�ʦ��Ϣ���£�\n");
	print();
}
void choose1()
{
	int i;
	printf("                                   ����ʽ\n");
	printf("           1:������ʦ������                    2:������������\n");
	printf("           3:������н����\n");
	printf("��ѡ��");
	scanf("%d",&i);
    	while((i<1)||(i>3))
	{
		printf("ѡ����Ч��������������ȷѡ�");
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
		printf("\n��δ¼�����ʦ��Ϣ\n");
		return;
	}
	printf("������Ҫ���ҵĽ�ʦ��Ϣ�Ľ�ʦ�ţ�");
    scanf("%ld",&i);
	for(p=head;p!=NULL;p=p->next)

		if(p->num==i)
		{
            printf("��ʦ��:%ld,����:%s,�Ա�:%s,����:%d,ѧ��:%s,ְ��:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    ��н:%ld,סַ:%s,�绰:%s\n",p->wage,p->addr,p->telep);
			return;
		}
	printf("��¼��Ľ�ʦ��Ϣ�в����ڸý�ʦ��\n");
}
void search2()
{
	struct teacher *p;
	char i[20];
	int j=0;
	if(head==NULL)
	{
		printf("\n��δ¼�����ʦ��Ϣ\n");
		return;
	}
	printf("������Ҫ���ҵ���Ϣ�Ľ�ʦ������");
    scanf("%s",i);
	for(p=head;p!=NULL;p=p->next)
		if(strcmp(p->name,i)==0)

		{
            printf("��ʦ��:%ld,����:%s,�Ա�:%s,����:%d,ѧ��:%s,ְ��:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    ��н:%ld,סַ:%s,�绰:%s\n",p->wage,p->addr,p->telep);
			j=j+1;
		}
	if(j==0) printf("��¼��Ľ�ʦ��Ϣ�в����ڸ������Ľ�ʦ\n");
}
void search3()
{
	struct teacher *p;
	char i[20];
	int j=0;
	if(head==NULL)
	{
		printf("\n��δ¼�����ʦ��Ϣ\n");
		return;
	}
	printf("������Ҫ���ҵ���Ϣ�Ľ�ʦְ�ƣ�");
    scanf("%s",i);
	for(p=head;p!=NULL;p=p->next)
		if(strcmp(p->title,i)==0)
		{
            printf("��ʦ��:%ld,����:%s,�Ա�:%s,����:%d,ѧ��:%s,ְ��:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    ��н:%ld,סַ:%s,�绰:%s\n",p->wage,p->addr,p->telep);
		    j=j+1;
		}
	if(j==0) printf("��¼��Ľ�ʦ��Ϣ�в����ڸ�ְ�ƵĽ�ʦ\n");
}
void search4()
{
	struct teacher *p;
	int i,j=0;
	if(head==NULL)
	{
		printf("\n��δ¼�����ʦ��Ϣ\n");
		return;
	}
	printf("������Ҫ���ҵ���Ϣ�Ľ�ʦ���䣺");
    scanf("%d",&i);
	for(p=head;p!=NULL;p=p->next)
		if(p->age==i)
		{
			printf("��ʦ��:%ld,����:%s,�Ա�:%s,����:%d,ѧ��:%s,ְ��:%s\n",p->num,p->name,p->sex,p->age,p->edu,p->title);
			printf("    ��н:%ld,סַ:%s,�绰:%s\n",p->wage,p->addr,p->telep);
		    j=j+1;
		}
	if(j==0) printf("��¼��Ľ�ʦ��Ϣ�в����ڸ�����Ľ�ʦ\n");
}
void choose2()
{
	int i;
	printf("                                   ��ѯ��ʽ\n");
	printf("             1:������ʦ�Ų�ѯ��                   2:����������ѯ��\n");
	printf("             3:����ְ�Ʋ�ѯ��                     4:���������ѯ��\n");
	printf("��ѡ��");
	scanf("%d",&i);
	while((i<1)||(i>4))
	{
		printf("ѡ����Ч��������������ȷѡ�");
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
	printf("                                      �˵�\n");
	printf("               1:����ʦ��Ϣ¼�롿                2:����ʦ��Ϣ�����\n");
	printf("               3:����ʦ��Ϣɾ����                4:����ѯ������Ϣ��\n");
	printf("               5:������                        6:���˳�ϵͳ��\n");
	printf("��ѡ��: ");
	scanf("%d",&i);
	while((i<1)||(i>6))
	{
		printf("ѡ����Ч��������������ȷѡ�");
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
