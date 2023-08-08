#include "main.h"
void addfly(int *used, int *count)
{
    struct fly *temp = NULL;
    if ((*count) == (*used))
    {
        if ((*count == 0))
        {
            // printf("当前是第一个空间\n");
            pflyArr = temp = malloc(sizeof(struct fly));
            (*count) = 1;
        }
        else
        {
            (*count) = (*count) + (*count) / 2;
            if ((*count) == 1)
            {
                (*count)++;
            }
            // printf("当前是第%d个航班，由于空间不够，现在重新分配了%d个空间\n", (*used), (*count));
            temp = malloc(sizeof(struct fly) * (*count));
        }
        if ((*count) != 1)
        {
            memcpy(temp, pflyArr, sizeof(struct fly) * (*used));
            free(pflyArr);
            pflyArr = temp;
        }
    }
    (*used)++;
    printf("请输入航班信息\n");
    printf("航班编号:");
    scanf("%d", &pflyArr[(*used) - 1].num);
    printf("出发地：");
    scanf("%s", pflyArr[(*used) - 1].start);
    printf("目的地：");
    scanf("%s", pflyArr[(*used) - 1].end);
    printf("起飞时间\n");
    struct tm t;
    printf("年 月 日 小时 分钟\n");
    scanf("%d %d %d %d %d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min);
    t.tm_year -= 1900;
    t.tm_mon -= 1;
    time_t t1 = mktime(&t);
    pflyArr[(*used) - 1].flytime = t1;
    printf("价格：");
    scanf("%d", &pflyArr[(*used) - 1].value);
    printf("余票: ");
    scanf("%d", &pflyArr[(*used) - 1].inventory);
    savefly();
}
void delfly(int *used, int *count)
{
    int num;
    int i = 0;
    int a = 0;
    printf("请输入您要删除航班的编号:");
    scanf("%d", &num);
    for (i = 0; i < (*used); i++)
    {
        if (pflyArr[i].num == num)
        {
            a++;
            (*used)--;
            if ((*used) + (*used) / 2 == (*count))
            {
                int newSize = (*used);
                struct fly *ptemp = malloc(sizeof(struct fly) * newSize);
                if (i < (*used))
                {
                    memmove(pflyArr + i, pflyArr + i + 1, sizeof(struct fly) * ((*used) - i));
                }
                memcpy(ptemp, pflyArr, sizeof(struct fly) * (*used));
                free(pflyArr);
                pflyArr = ptemp;
            }
            else
            {
                if (i < (*used))
                {
                    memmove(pflyArr + i, pflyArr + i + 1, sizeof(struct fly) * ((*used) - i));
                }
            }
        }
    }
    if (a == 0)
    {
        printf("未找到该航班信息，无法删除！\n");
    }
    savefly();
}
void updatafly()
{
    int num;
    int i = 0;
    printf("请输入您要更新的航班编号:");
    scanf("%d", &num);
    for (i = 0; i < used; i++)
    {
        if (pflyArr[i].num == num)
        {
            break;
        }
    }
    if (i >= used)
    {
        printf("未找到该航班信息，无法更改！\n");
    }
    printf("请输入更新的航班信息\n");
    printf("航班编号:");
    scanf("%d", &pflyArr[i].num);
    printf("出发地：");
    scanf("%s", pflyArr[i].start);
    printf("目的地：");
    scanf("%s", pflyArr[i].end);
    printf("起飞时间\n");
    struct tm t;
    printf("年 月 日 小时 分钟\n");
    scanf("%d %d %d %d %d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour, &t.tm_min);
    t.tm_year -= 1900;
    t.tm_mon -= 1;
    time_t t1 = mktime(&t);
    pflyArr[i].flytime = t1;
    printf("价格：");
    scanf("%d", &pflyArr[i].value);
    printf("余票: ");
    scanf("%d", &pflyArr[i].inventory);
    savefly();
}
void findflynum()
{
    int target;
    printf("请输入您要查找的航班编号：");
    scanf("%d", &target);
    int left = 0;
    int right = used - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int numsMid = pflyArr[mid].num;
        if (numsMid < target)
        {
            left = mid + 1;
        }
        else if (numsMid > target)
        {
            right = mid - 1;
        }
        else
        {
            printf("航班%d的信息如下所示\n", pflyArr[mid].num);
            struct tm *t = localtime(&pflyArr[mid].flytime);
            printf("----------------------------------------------\n");
            printf("航班%d将于%d年%d月%d日%d时%d分 从%s 飞往 %s \n", pflyArr[mid].num, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, pflyArr[mid].start, pflyArr[mid].end);
            printf("本次航班机票价格：%d 余票：%d\n", pflyArr[mid].value, pflyArr[mid].inventory);
            printf("----------------------------------------------\n");
            break;
        }
    }
}
void findflystart()
{
    printf("请输入您要查找航班的出发地：");
    char start[128];
    scanf("%s", start);
    int sum = 0;
    for (int i = 0; i < used; i++)
    {
        if (strcmp(pflyArr[i].start, start) == 0)
        {
            printf("----------------------------------------------\n");
            struct tm *t = localtime(&pflyArr[i].flytime);
            printf("航班%d将于%d年%d月%d日%d时%d分 从%s 飞往 %s \n", pflyArr[i].num, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, pflyArr[i].start, pflyArr[i].end);
            printf("本次航班机票价格：%d 余票：%d\n", pflyArr[i].value, pflyArr[i].inventory);
            printf("----------------------------------------------\n");
            sum++;
        }
    }
    if (sum == 0)
    {
        printf("没有找到该航班信息！\n");
    }
}
void findflyend()
{
    printf("请输入您要查找航班的目的地：");
    char end[128];
    scanf("%s", end);
    int sum = 0;
    for (int i = 0; i < used; i++)
    {
        if (strcmp(pflyArr[i].end, end) == 0)
        {
            printf("----------------------------------------------\n");
            struct tm *t = localtime(&pflyArr[i].flytime);
            printf("航班%d将于%d年%d月%d日%d时%d分 从%s 飞往 %s \n", pflyArr[i].num, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, pflyArr[i].start, pflyArr[i].end);
            printf("本次航班机票价格：%d 余票：%d\n", pflyArr[i].value, pflyArr[i].inventory);
            printf("----------------------------------------------\n");
            sum++;
        }
    }
    if (sum == 0)
    {
        printf("没有找到该航班信息！\n");
    }
}
void displayfly()
{

    for (int i = 0; i < used; i++)
    {

        printf("----------------------------------------------\n");
        struct tm *t = localtime(&pflyArr[i].flytime);
        printf("航班%d将于%d年%d月%d日%d时%d分 从%s 飞往 %s \n", pflyArr[i].num, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, pflyArr[i].start, pflyArr[i].end);
        printf("本次航班机票价格：%d 余票：%d\n", pflyArr[i].value, pflyArr[i].inventory);
        printf("----------------------------------------------\n");
    }
}
void timesort()
{
    struct fly temp;
    for (int i = 0; i < used - 1; i++)
    {
        for (int j = 0; j < used - 1 - i; j++)
        {
            if (pflyArr[j].flytime > pflyArr[j + 1].flytime)
            {
                temp = pflyArr[j];
                pflyArr[j] = pflyArr[j + 1];
                pflyArr[j + 1] = temp;
            }
        }
    }
    printf("按出发时间从早到晚排序后的信息如下所示\n");
    displayfly();
}
void valuesort()
{
    int min;
    struct fly temp;
    for (int i = 0; i < used - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < used; j++)
        {
            if (pflyArr[min].value > pflyArr[j].value)
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = pflyArr[i];
            pflyArr[i] = pflyArr[min];
            pflyArr[min] = temp;
        }
    }
    printf("按价格从低到高排序后的信息如下所示\n");
    for (int i = 0; i < used; i++)
    {

        printf("----------------------------------------------\n");
        struct tm *t = localtime(&pflyArr[i].flytime);
        printf("航班%d将于%d年%d月%d日%d时%d分 从%s 飞往 %s \n", pflyArr[i].num, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, pflyArr[i].start, pflyArr[i].end);
        printf("本次航班机票价格：%d 余票：%d\n", pflyArr[i].value, pflyArr[i].inventory);
        printf("----------------------------------------------\n");
    }
}
void inventorysort()
{
    int min;
    struct fly temp;
    struct fly *flyarr = pflyArr;
    for (int i = 0; i < used - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < used; j++)
        {
            if (flyarr[min].inventory > flyarr[j].inventory)
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = flyarr[i];
            flyarr[i] = flyarr[min];
            flyarr[min] = temp;
        }
    }
    printf("按余票数量从小到大排序后的信息如下所示\n");
    for (int i = 0; i < used; i++)
    {

        printf("----------------------------------------------\n");
        struct tm *t = localtime(&flyarr[i].flytime);
        printf("航班%d将于%d年%d月%d日%d时%d分 从%s 飞往 %s \n", flyarr[i].num, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, flyarr[i].start, flyarr[i].end);
        printf("本次航班机票价格：%d 余票：%d\n", flyarr[i].value, flyarr[i].inventory);
        printf("----------------------------------------------\n");
    }
    free(flyarr);
}
void savefly()
{
    FILE *fp = fopen("jpdata.txt", "w+");
    if (fp == NULL)
    {
        printf("打开失败！\n");
        return;
    }
    fprintf(fp, "%d", used);
    fprintf(fp, "\n");
    for (int i = 0; i < used; i++)
    {
        fprintf(fp, "%s %d %s %ld %d %d", pflyArr[i].start, pflyArr[i].num, pflyArr[i].end, pflyArr[i].flytime, pflyArr[i].value, pflyArr[i].inventory);
        fprintf(fp, "\n");
    }
    // printf("信息已保存！\n");
    fclose(fp);
}
void readfly(int *used, int *count)
{
    FILE *fp;
    fp = fopen("jpdata.txt", "r+");
    if (fp == NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    struct fly *p;
    fscanf(fp, "%d", used);
    printf("%d\n", *used);
    (*count) = (*used);
    printf("%d\n", *count);
    p = malloc(sizeof(struct fly) * (*used));
    printf("123\n");
    fscanf(fp, "\n");
    for (int i = 0; i < (*used); i++)
    {

        fscanf(fp, "%s %d %s %ld %d %d", p[i].start, &p[i].num, p[i].end, &p[i].flytime, &p[i].value, &p[i].inventory);
        fscanf(fp, "\n");
    }
    pflyArr = malloc(sizeof(struct fly) * (*used));
    memcpy(pflyArr, p, sizeof(struct fly) * (*used));
    free(p);
    fclose(fp);
}
