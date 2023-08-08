#include "main.h"
void inituserList()
{
    head = malloc(sizeof(struct user));
    memset(head, 0, sizeof(struct user));
    tail = malloc(sizeof(struct user));
    memset(tail, 0, sizeof(struct user));
    head->pf = NULL;
    tail->next = NULL;
    head->next = tail;
    tail->pf = head;
}
void readui(char *filePath, char *mode)
{
    FILE *pf;
    pf = fopen(filePath, mode);
    if (pf == NULL)
    {
        printf("打开文件失败\n");
    }
    else
    {
        fseek(pf, 0, SEEK_END);
        long pos = ftell(pf);
        fseek(pf, 0, SEEK_SET);
        char *q = malloc(pos + 1);
        q[pos] = '\0';
        fread(q, pos, 1, pf);
        printf("%s\n", q);
    }
    fclose(pf);
}
void function(int *node)
{
    char n[20] = {0};
    int num = atof(n);
    system("clear");
    readui("./ui/login.ui", "r");
    while (num != 1)
    {
        printf("------------------------------------\n");
        printf("请输入您的选项\n");
        scanf("%s", n);
        num = atof(n);
        // system("clear");
        switch (num)
        {
        case 1:
            printf("------------------------------------\n");
            signin(node);
            return;
            break;

        case 2:
            printf("------------------------------------\n");
            login(node);
            break;
        case 3:
            system("clear");
            printf("------------------------------------\n");
            printf("退出系统！\n");
            return;
            break;
        default:
            printf("------------------------------------\n");
            printf("非法输入！\n");
            break;
        }
    }
}
void signin(int *node)
{

    char name[128];
    long passwd;
again:
    printf("请输入登录信息\n");
    printf("用户名:");
    scanf("%s", name);
    printf("登录密码：");
    scanf("%ld", &passwd);
    struct user *p = head->next;
    // 遍历
    if ((strcmp(name, "yl") == 0) && (passwd == 1))
    {
        printf("您的身份为管理员，进入管理员页面\n");
        manage(node);
    }
    else
    {
        while (p != tail)
        {
            if ((strcmp(p->name, name) == 0) && (passwd == p->passwd))
            {
                printf("您的身份为普通用户，进入用户页面\n");
                user(name);
                break;
            }

            else if ((strcmp(p->name, name) == 0) && (passwd != p->passwd))
            {
                printf("密码不正确，请重新输入！\n");
                goto again;
                break;
            }
            p = p->next;
        }
        if (p == tail)
        {
            printf("没有该用户，请注册！\n");
            function(node);
        }
    }
}
void login(int *node)
{
    printf("------------------------------------\n");
    printf("请输入注册信息\n");
    adduser(node);
    printf("注册成功！\n");
    printf("------------------------------------\n");
}
void user(char *name)
{
    system("clear");
    readui("./ui/user.ui", "r");
    char n[20] = {0};
    int num = 0;
    while (1)
    {
        printf("------------------------------------\n");
        printf("请输入您的选项\n");
        scanf("%s", n);
        num = atof(n);
        switch (num)
        {
        case 1:
            printf("------------------------------------\n");
            printf("购买机票\n");
            buyfly(name);
            break;
        case 2:
            printf("------------------------------------\n");
            printf("查询机票信息\n");
            findflyuser(name);
            return;
            break;
        case 3:
            printf("------------------------------------\n");
            printf("退票\n");
            refundfly(name);
            break;
        case 4:
            printf("------------------------------------\n");
            printf("显示个人信息\n");
            displaybuy(name);
            break;
        case 5:
            printf("------------------------------------\n");
            printf("重置密码\n");
            reuserpwd(name);
            printf("是否查看审核结果(y/n)：");
            getchar();
            if (getchar() == 'y')
            {
                updateuserpwd(name);
            }
            break;
        case 6:
            printf("------------------------------------\n");
            printf("返回上一页\n");
            function(&node);
            return;
            break;
        case 7:
            system("clear");
            printf("------------------------------------\n");
            printf("退出系统！\n");
            return;
            break;
        default:
            printf("------------------------------------\n");
            printf("非法输入！\n");
            break;
        }
    }
}
void findflyuser(char *name)
{
    system("clear");
    readui("./ui/findfly.ui", "r");
    char n[20] = {0};
    int num = 0;
    while (1)
    {
        printf("---------------\n");
        printf("请输入您的选项\n");
        scanf("%s", n);
        num = atof(n);
        switch (num)
        {
        case 1:
            printf("---------------\n");
            printf("按航班编号查询\n");
            findflynum();
            break;
        case 2:
            printf("---------------\n");
            printf("按目的地查询\n");
            findflyend();
            break;
        case 3:
            printf("---------------\n");
            printf("按出发地查询\n");
            findflystart();
            break;
        case 4:
            printf("---------------\n");
            printf("按时间早晚排序\n");
            timesort();

            break;
        case 5:
            printf("---------------\n");
            printf("按价格高低排序\n");
            valuesort();

            break;
        case 6:
            printf("---------------\n");
            printf("按余票数量排序\n");
            inventorysort();

            break;
        case 7:
            printf("---------------\n");
            printf("输出全部航班信息\n");
            displayfly();
            break;
        case 8:
            printf("---------------\n");
            printf("返回上页！\n");
            user(name);
            return;
            break;
        case 9:
            printf("---------------\n");
            printf("返回主页面!\n");
            function(&node);
            return;
            break;
        case 10:
            printf("---------------\n");
            printf("退出系统！\n");
            return;
            break;
        default:
            printf("---------------\n");
            printf("非法输入！\n");
            break;
        }
    }
}
void manage(int *node)
{
    int used = 0;
    int count = 0;
    system("clear");
    readui("./ui/manage.ui", "r");
    char n[20] = {0};
    int num = atof(n);
    while (1)
    {
        printf("------------------------------------\n");
        printf("请输入您的选项\n");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            printf("------------------------------------\n");
            jpmanage();
            return;
            break;
        case 2:
            printf("------------------------------------\n");
            usermanage(node);
            return;
            break;
        case 3:
            function(node);
            return;
            break;
        case 4:
            system("clear");
            printf("------------------------------------\n");
            printf("退出系统！\n");
            return;
            break;
        default:
            printf("------------------------------------\n");
            printf("非法输入！\n");
            break;
        }
    }
}
void jpmanage()
{
    system("clear");
    readui("./ui/jpmanage.ui", "r");
    char n[20] = {0};
    int num = 0;
    while (1)
    {
        printf("------------------------------------\n");
        printf("请输入您的选项\n");
        scanf("%s", n);
        num = atof(n);
        switch (num)
        {
        case 1:
            printf("------------------------------------\n");
            printf("录入机票信息\n");
            addfly(&used, &count);
            break;
        case 2:
            printf("------------------------------------\n");
            printf("删除机票信息\n");
            delfly(&used, &count);
            break;
        case 3:
            printf("------------------------------------\n");
            printf("查询机票信息\n");
            findfly();
            return;
            break;
        case 4:
            printf("------------------------------------\n");
            printf("更改机票信息\n");
            updatafly();
            break;
        case 5:
            printf("------------------------------------\n");
            printf("返回上页！\n");
            manage(&node);
            return;
            break;
        case 6:
            printf("------------------------------------\n");
            printf("返回主页！\n");
            function(&node);
            return;
            break;
        case 7:
            system("clear");
            printf("------------------------------------\n");
            printf("退出系统！\n");
            return;
            break;
        }
    }
}
void findfly()
{
    system("clear");
    readui("./ui/findfly.ui", "r");
    char n[20] = {0};
    int num = 0;
    while (1)
    {
        printf("------------------------------------\n");
        printf("请输入您的选项\n");
        scanf("%s", n);
        num = atof(n);
        switch (num)
        {
        case 1:
            printf("------------------------------------\n");
            printf("按航班编号查询\n");
            findflynum();
            break;
        case 2:
            printf("------------------------------------\n");
            printf("按目的地查询\n");
            findflyend();
            break;
        case 3:
            printf("------------------------------------\n");
            printf("按出发地查询\n");
            findflystart();
            break;
        case 4:
            printf("------------------------------------\n");
            printf("按时间早晚排序\n");
            timesort();

            break;
        case 5:
            printf("------------------------------------\n");
            printf("按价格高低排序\n");
            valuesort();

            break;
        case 6:
            printf("------------------------------------\n");
            printf("按余票数量排序\n");
            inventorysort();

            break;
        case 7:
            printf("------------------------------------\n");
            printf("输出全部航班信息\n");
            displayfly();
            break;
        case 8:
            printf("------------------------------------\n");
            printf("返回上页！\n");
            jpmanage();
            return;
            break;
        case 9:
            printf("------------------------------------\n");
            printf("返回主页面!\n");
            function(&node);
            return;
            break;
        case 10:
            system("clear");
            printf("------------------------------------\n");
            printf("退出系统！\n");
            return;
            break;
        default:
            printf("------------------------------------\n");
            printf("非法输入！\n");
            break;
        }
    }
}
void usermanage(int *node)
{
    system("clear");
    readui("./ui/usermanage.ui", "r");
    char n[20] = {0};
    int num = 0;
    while (1)
    {
        printf("------------------------------------\n");
        printf("请输入您的选项\n");
        scanf("%s", n);
        num = atof(n);
        switch (num)
        {
        case 1:
            printf("------------------------------------\n");
            printf("增加用户\n");
            adduser(node);
            break;
        case 2:
            printf("------------------------------------\n");
            printf("删除用户\n");
            deluser(node);
            break;
        case 3:
            printf("------------------------------------\n");
            finduser();
            break;
        case 4:
            printf("------------------------------------\n");
            printf("更新用户信息\n");
            updateuser();
            break;
        case 5:
            printf("------------------------------------\n");
            printf("插入用户信息\n");
            insertuser(node);
            break;
        case 6:
            printf("------------------------------------\n");
            printf("打印全部用户信息\n");
            displayuser();
            break;
        case 7:
            printf("------------------------------------\n");
            printf("审批密码重置\n");
            manageuserpwd();
            break;
        case 8:
            printf("------------------------------------\n");
            printf("返回上一页面\n");
            manage(node);
            return;
            break;
        case 9:
            printf("------------------------------------\n");
            printf("返回主页!\n");
            function(node);
            return;
            break;
        case 10:
            system("clear");
            printf("------------------------------------\n");
            printf("退出系统!\n");
            return;
            break;
        default:
            printf("------------------------------------\n");
            printf("非法输入!\n");
            break;
        }
    }
}
void manageuserpwd()
{
    struct user *p = head->next;
    while (p != tail)
    {
        if (p->newpwd->newpasswd != 0)
        {
            printf("---------------\n");
            printf("用户名：%s 用户原密码：%ld 用户更新密码：%ld\n", p->newpwd->name, p->passwd, p->newpwd->newpasswd);
            printf("请输入您的审核结果(ok/no)：\n");
            scanf("%s", p->newpwd->permit);
            printf("---------------\n");
        }
        p = p->next;
    }
    saveuser();
}
