#include "main.h"
int node;
int used;
int count;
struct fly *pflyArr = NULL;
struct user *head = NULL;
struct user *tail = NULL;
int main()
{
    inituserList();
    emptyuser();
    readuser(&node);
    readfly(&used, &count);
    // printf("%d %d %d\n", node, used, count);
    function(&node);
}
