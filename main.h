#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void inituserList();
void readui(char *filePath, char *mode);
void function(int *node);
void signin(int *node);
void adduser(int *node);
void insertuser(int *node);
void deluser(int *node);
void finduser();
void updateuser();
void displayuser();
void login(int *node);
void manage(int *node);
void jpmanage();
void usermanage(int *node);
void user();
void saveuser();
void readuser(int *node);
void addfly(int *used, int *count);
void delfly(int *used, int *count);
void updatafly();
void findfly();
void findflyuser(char *name);
void findflynum();
void findflystart();
void findflyend();
void displayfly();
void timesort();
void valuesort();
void inventorysort();
void buyfly(char *name);
void refundfly(char *name);
struct user *userdata(char *name);
void displaybuy(char *name);
void savefly();
void readfly(int *used, int *count);
void reuserpwd(char *name);
void manageuserpwd();
void updateuserpwd(char *name);
void emptyuser();

struct user
{
    char name[128];
    long int passwd;
    long int time;
    int buynumber;
    struct updatepwd *newpwd;
    struct buyfly *buy;
    char end[128];
    struct user *pf;
    struct user *next;
};
struct fly
{
    int num;
    char start[128];
    char end[128];
    long int flytime;
    int value;
    int inventory;
};
struct buyfly
{
    int flynum;
    char start[128];
    char end[128];
    long int flytime;
    int value;
    int buynum;
};
struct updatepwd
{
    char name[128];
    long int newpasswd;
    char permit[20];
};

extern int node;
extern int used;
extern int count;

extern struct fly *pflyArr;
extern struct user *head;
extern struct user *tail;
#endif
