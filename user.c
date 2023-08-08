#include "main.h"
struct user *userdata(char *name)
{
    struct user *p = head->next;
    while (p != tail)
    {
        if (strcmp(p->name, name) == 0)
        {
            break;
        }
        p = p->next;
    }
    return p;
}
void adduser(int *node)
{
    struct user *temp = malloc(sizeof(struct user));
    temp->buynumber = 0;
    strcpy(temp->end, "end");
    temp->buy = malloc(sizeof(struct buyfly));
    memset(temp->buy, 0, sizeof(struct buyfly));
    temp->newpwd = malloc(sizeof(struct updatepwd));
    memset(temp->newpwd, 0, sizeof(struct updatepwd));
    printf("用户名:");
    scanf("%s", temp->name);
    strcpy(temp->newpwd->name, temp->name);
    temp->newpwd->newpasswd = 0;
    strcpy(temp->newpwd->permit, "kong");
    printf("登录密码：");
    scanf("%ld", &temp->passwd);
    printf("------------------------------------\n");
    time_t result = time(NULL);
    temp->time = result;
    // printf("%ld\n", temp->time);
    tail->pf->next = temp;
    temp->pf = tail->pf;
    temp->next = tail;
    tail->pf = temp;
    (*node)++;
    saveuser();
}
void insertuser(int *node)
{
    char name[128];
    printf("请输入您将在哪个用户位置之前插入：");
    scanf("%s", name);
    struct user *p = head->next;
    struct user *temp = malloc(sizeof(struct user));
    temp->buy = malloc(sizeof(struct buyfly));
    memset(temp->buy, 0, sizeof(struct buyfly));
    temp->newpwd = malloc(sizeof(struct updatepwd));
    memset(temp->newpwd, 0, sizeof(struct updatepwd));
    printf("请输入您要插入的用户信息\n");
    printf("用户名:");
    scanf("%s", temp->name);
    strcpy(temp->newpwd->name, temp->name);
    temp->newpwd->newpasswd = 0;
    strcpy(temp->newpwd->permit, "kong");
    printf("登录密码：");
    scanf("%ld", &temp->passwd);
    time_t result = time(NULL);
    temp->time = result;
    strcpy(temp->end, "end");
    while (p != tail)
    {
        if (strcmp(p->name, name) == 0)
        {
            printf("找到该位置！\n");
            break;
        }
        p = p->next;
    }
    if (p == tail)
    {
        printf("没有找到该用户，将信息插入链表尾部！\n");
    }
    p->pf->next = temp;
    temp->pf = p->pf;
    temp->next = p;
    p->pf = temp;
    (*node)++;
    saveuser();
}
void deluser(int *node)
{
    char name[128];
    printf("请输入您要删除用户的姓名：");
    scanf("%s", name);
    struct user *p = head->next;
    struct user *s;
    int count = 0;
    while (p != tail)
    {
        if (strcmp(p->name, name) == 0)
        {
            p->pf->next = p->next;
            p->next->pf = p->pf;
            s = p->next;
            free(p);
            p = s;
            count++;
            (*node)--;
        }
        else
        {
            p = p->next;
        }
    }
    if (count == 0)
    {
        printf("没有找到该用户！\n");
    }
    saveuser();
}
void finduser()
{

    printf("查询用户信息\n");
    char name[128];
    printf("请输入您查找的用户姓名：");
    scanf("%s", name);
    struct user *p = head->next;
    while (p != tail)
    {
        if (strcmp(p->name, name) == 0)
        {
            // time_t time1 = time(0);
            //  //转换为本地时间（年月日...）
            struct tm *t = localtime(&p->time);
            printf("用户姓名：%s，登录密码：%ld，注册时间：%d/%d/%d %d:%d\n", p->name, p->passwd, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
        }
        p = p->next;
    }
}
void updateuser()
{
    char name[128];
    printf("请输入您要更新的用户姓名：");
    scanf("%s", name);
    struct user *p = head->next;
    while (p != tail)
    {
        if (strcmp(p->name, name) == 0)
        {
            printf("请输入您要插入的用户信息\n");
            printf("用户名:");
            scanf("%s", p->name);
            strcpy(p->newpwd->name, p->name);
            printf("登录密码：");
            scanf("%ld", &p->passwd);
            time_t result = time(NULL);
            p->time = result;
            break;
        }
        p = p->next;
    }
    saveuser(node);
}
void displayuser()
{
    struct user *p = head->next;
    while (p != tail)
    {
        struct tm *t = localtime(&p->time);
        // printf("%d/%d/%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
        printf("用户姓名：%s 登录密码：%ld 注册时间：%d/%d/%d %d:%d\n", p->name, p->passwd, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
        p = p->next;
    }
}
void buyfly(char *name)
{
    displayfly();
again:
    printf("请输入您要购买的航班编号:");
    int flynum;
    scanf("%d", &flynum);
    int i = 0;
    for (i = 0; i < used; i++)
    {
        if (flynum == pflyArr[i].num)
        {
            printf("------------------------------------------\n");
            printf("航班%d的信息如下所示\n", pflyArr[i].num);
            struct tm *t = localtime(&pflyArr[i].flytime);
            printf("航班%d将于%d年%d月%d日%d时%d分 从%s 飞往 %s \n", pflyArr[i].num, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, pflyArr[i].start, pflyArr[i].end);
            printf("本次航班机票价格：%d 余票：%d\n", pflyArr[i].value, pflyArr[i].inventory);
            printf("------------------------------------------\n");
            break;
        }
    }
    if (i == used)
    {
        printf("没有此航班信息！\n");
        return;
    }
    struct user *p = userdata(name);
    int k = 0;
    for (k = 0; k < p->buynumber; k++)
    {
        if (p->buy[k].flynum == flynum)
        {
            break;
        }
    }

    char n[20];
    printf("您是否要购买此次航班(y/n):");
    scanf("%s", n);
    if (strcmp(n, "y") == 0)
    {
        int number = 0;
        printf("请输入您要购买的数量：");
        scanf("%d", &number);
        if (pflyArr[i].inventory >= number)
        {

            if (p->buy[k].flynum == flynum)
            {
                pflyArr[i].inventory -= number;
                p->buy[k].buynum += number;
            }
            else
            {
                p->buynumber = p->buynumber + 1;
                pflyArr[i].inventory = pflyArr[i].inventory - number;
                struct buyfly *temp = malloc(sizeof(struct buyfly) * (p->buynumber));
                memcpy(temp, p->buy, sizeof(struct buyfly) * ((p->buynumber) - 1));
                strcpy(temp[(p->buynumber) - 1].start, pflyArr[i].start);
                strcpy(temp[(p->buynumber) - 1].end, pflyArr[i].end);
                temp[(p->buynumber) - 1].flytime = pflyArr[i].flytime;
                temp[(p->buynumber) - 1].value = pflyArr[i].value;
                temp[(p->buynumber) - 1].flynum = pflyArr[i].num;
                temp[(p->buynumber) - 1].buynum = number;
                p->buy = malloc(sizeof(struct buyfly) * (p->buynumber));
                memcpy(p->buy, temp, sizeof(struct buyfly) * (p->buynumber));
                free(temp);
            }
        }
        else
        {
            printf("您购买的数量超过上限！\n");
            goto again;
        }
    }
    memset(p->newpwd, 0, sizeof(struct updatepwd));
    strcpy(p->newpwd->name, name);
    strcpy(p->newpwd->permit, "kong");
    p->newpwd->newpasswd = 0;
    saveuser();
    savefly();
}
void refundfly(char *name)
{

    displaybuy(name);
    struct user *p = userdata(name);
    printf("请输入您要退票的航班编号:");
    int flynum;
    scanf("%d", &flynum);
    int i = 0;
    for (i = 0; i < used; i++)
    {
        if (flynum == pflyArr[i].num)
        {
            break;
        }
    }

    int tp = 0;
    printf("请输入您要退票的张数:");
    scanf("%d", &tp);
    for (int j = 0; j < (p->buynumber); j++)
    {
        if (p->buy[j].flynum == flynum)
        {
            if (tp < p->buy[j].buynum)
            {
                p->buy[j].buynum -= tp;
                pflyArr[i].inventory += tp;
                printf("您已退%d张航班%d的机票!\n", tp, p->buy[j].flynum);
            }
            else if (tp == p->buy[j].buynum)
            {
                pflyArr[i].inventory += tp;
                (p->buynumber)--;
                struct buyfly *flybuy = p->buy;
                if (i < p->buy[j].buynum)
                {
                    memmove(flybuy + j, flybuy + j + 1, sizeof(struct buyfly) * ((p->buynumber) - j));
                }
            }
            else
            {
                printf("超出上限，退票失败！\n");
            }
        }
    }
    saveuser();
    savefly();
}
void reuserpwd(char *name)
{
    struct user *p = userdata(name);
    p->newpwd = malloc(sizeof(struct updatepwd));
    memset(p->newpwd, 0, sizeof(struct updatepwd));
    long int newpwd;
    strcpy(p->newpwd->name, p->name);
    printf("请输入您的新密码：");
    scanf("%ld", &newpwd);
    p->newpwd->newpasswd = newpwd;
    strcpy(p->newpwd->permit, "kong");
    printf("等待管理员审核！\n");
    saveuser();
}
void updateuserpwd(char *name)
{
    emptyuser();
    readuser(&node);
    struct user *p = userdata(name);
    if (strcmp(p->newpwd->permit, "ok") == 0)
    {
        p->passwd = p->newpwd->newpasswd;
        printf("审核通过，密码更新成功！\n");
        p->newpwd->newpasswd = 0;
        strcpy(p->newpwd->permit, "kong");
    }
    else
    {
        printf("审核未通过！\n");
        p->newpwd->newpasswd = 0;
        strcpy(p->newpwd->permit, "kong");
    }
    saveuser();
}
void displaybuy(char *name)
{
    struct user *p = userdata(name);
    struct tm *t = localtime(&p->time);
    printf("用户姓名：%s，登录密码：%ld，注册时间：%d/%d/%d %d:%d\n", p->name, p->passwd, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
    printf("购票信息\n");
    if (p->buynumber == 0)
    {
        printf("购票信息为空！\n");
    }
    for (int i = 0; i < p->buynumber; i++)
    {
        struct tm *t1 = localtime(&(p->buy[i].flytime));
        printf("%d/%d/%d %d:%d 从%s开往%s的航班%d 购买价格为%d，购买数量为：%d张\n", t1->tm_year + 1900, t1->tm_mon + 1, t1->tm_mday, t1->tm_hour, t1->tm_min, p->buy[i].start, p->buy[i].end, p->buy[i].flynum, p->buy[i].value, p->buy[i].buynum);
    }
}
void emptyuser()
{
    //  printf("清空\n");
    struct user *p = head->next;
    while (p != tail)
    {
        p = p->next;
        free(p->pf->buy);
        free(p->pf->newpwd);
        free(p->pf);
    }
    head->next = tail;
    tail->pf = head;
}
void saveuser()
{
    FILE *fp;
    fp = fopen("userpwd.txt", "wb");
    if ((fp = fopen("userpwd.txt", "wb")) == NULL)
    {
        printf("打开失败");
        return;
    }
    struct user *p = head->next;

    fprintf(fp, "%d", node);
    while (p != tail)
    {
        fprintf(fp, "\n");
        fprintf(fp, "%ld %ld %s %d ", p->time, p->passwd, p->name, p->buynumber);
        fprintf(fp, "%s %ld %s ", p->newpwd->name, p->newpwd->newpasswd, p->newpwd->permit);

        for (int i = 0; i < p->buynumber; i++)
        {
            fprintf(fp, "%s %d %ld %s %d %d |", p->buy[i].end, p->buy[i].flynum, p->buy[i].flytime, p->buy[i].start, p->buy[i].value, p->buy[i].buynum);
        }
        fprintf(fp, "%s", p->end);
        p = p->next;
    }
    // printf("信息已保存！\n");
    /* struct user *p = head->next;
     fwrite(&count, sizeof(int), 1, fp);
     while (p != tail)
     {
         fwrite(p, sizeof(struct user), 1, fp);
         fwrite(p->newpwd, sizeof(struct updatepwd), 1, fp);
         fwrite(p->buy, sizeof(struct buyfly), p->buynumber, fp);
         p = p->next;
     }*/
    fclose(fp);
}
void readuser(int *node)
{

    FILE *fp;
    fp = fopen("userpwd.txt", "r+");
    if (fp == NULL)
    {
        printf("打开失败！\n");
        return;
    }

    struct user *p = head->next;
    fscanf(fp, "%d", node);
    int a = (*node);
    while (a)
    {

        fscanf(fp, "\n");
        p = malloc(sizeof(struct user));
        p->newpwd = malloc(sizeof(struct updatepwd));
        fscanf(fp, "%ld %ld %s %d ", &p->time, &p->passwd, p->name, &p->buynumber);
        fscanf(fp, "%s %ld %s ", p->newpwd->name, &p->newpwd->newpasswd, p->newpwd->permit);
        p->buy = malloc(sizeof(struct buyfly) * (p->buynumber));

        for (int i = 0; i < (p->buynumber); i++)
        {
            fscanf(fp, "%s %d %ld %s %d %d |", p->buy[i].end, &p->buy[i].flynum, &p->buy[i].flytime, p->buy[i].start, &p->buy[i].value, &p->buy[i].buynum);
        }
        fscanf(fp, "%s", p->end);
        tail->pf->next = p;
        p->pf = tail->pf;
        tail->pf = p;
        p->next = tail;
        a--;
    }
    /*  fread(node, sizeof(int), 1, fp);
      p->newpwd = malloc(sizeof(struct updatepwd));
      memset(p->newpwd, 0, sizeof(struct updatepwd));
      for (int i = 0; i < (*node); i++)
      {
          fread(p, sizeof(struct user), 1, fp);
          fread(p->newpwd, sizeof(struct updatepwd), 1, fp);
          p->buy = malloc((p->buynumber) * sizeof(struct buyfly));
          memset(p->buy, 0, sizeof(struct buyfly) * (p->buynumber));
          fread(p->buy, sizeof(struct buyfly), p->buynumber, fp);
      }*/

    fclose(fp);
}
