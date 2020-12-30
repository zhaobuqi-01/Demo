//
// Created by dingchunhui on 2020/12/29.
//

#include "map.h"
#include "menu.h"
#include <stdio.h>
#include "windows.h"

void Menu() {
    int MainChoose;
    printf("***********************城市交通图**********************\n");
    MAINFALG:
    printf("\t\t\t1.管理员登录\n\t\t\t2.旅客查询\n\t\t\t3.退出\n");
    scanf("%d", &MainChoose);
    system("cls");
    if (MainChoose == 1) {
        RootMenu();
    } else if (MainChoose == 2) {
        CustomerMenu();
    } else if (MainChoose == 3) {
        exit(0);
    } else {
        goto MAINFALG;
    }
}

void RootMenu() {
    int sure, RootChoose, citychoose, waychoose;
    AdjMatrix G;
    sure = Login();
    system("cls");
    if (sure) {
        RootFlag:
        printf("**************************信息修改*******************************\n");
        printf("\t\t\t1.交通图初始化\n\t\t\t2.城市信息修改\n\t\t\t3.路线信息修改\n\t\t\t4.信息查询\n\t\t\t5.退出\n");
        scanf("%d", &RootChoose);
        system("cls");
        if (RootChoose == 1) {
            printf("*******************************************初始化*************************************\n\t\t\t");
            Creat(&G);
            goto RootFlag;
        } else if (RootChoose == 2) {
            printf("**********************城市信息修改**************************\n");
            printf("\t\t\t1.添加\n\t\t\t2.删除\n");
            scanf("%d", &citychoose);
            system("cls");
            if (citychoose == 1) {
                CityAdd(&G);
                goto RootFlag;
            } else if (citychoose == 2) {
                CityDel(&G);
                goto RootFlag;
            }
        } else if (RootChoose == 3) {
            printf("****************************路线修改*****************************\n");
            printf("\t\t\t1.增加路线\n\t\t\t2.删除路线\n\t\t\t3.返回上一级菜单\n\t\t\t4.退出\n");
            scanf("%d", &waychoose);
            system("cls");
            if (waychoose == 1) {
                AddWay(&G);
                goto RootFlag;
            } else if (waychoose == 2) {
                Delway(&G);
                goto RootFlag;
            } else if (waychoose == 3) {
                goto RootFlag;
            } else if (waychoose == 4) {
                exit(0);
            } else {
                goto RootFlag;
            }
        } else if (RootChoose == 4) {
            printf("***************************交通信息************************************\n");
            CityTimeTable(&G);
            goto RootFlag;
        } else if (RootChoose == 5) {
            exit(0);
        } else {
            goto RootFlag;
        }
    }
}

void CustomerMenu() {
    int CustChoose, WayChoose;
    AdjMatrix G;
    CustomerFlag:
    printf("*********************************路线查询*********************************\n");
    printf("\t\t\t1.路线决策\n\t\t\t2.交通图信息\n\t\t\t3.退出\n");
    scanf("%d", &CustChoose);
    system("cls");
    if (CustChoose == 1) {
        WayFlag:
        printf("***************************路线决策选择************************************\n");
        printf("\t\t\t请选择决策:\t\t\t\n\t1.最快到达\t\t\t\n\t2.最省费用到达\t\t\t\n\t3.最少中转路线数\t\t\t\n");
        scanf("%d", &WayChoose);
        if (WayChoose == 1) {
            printf("************最快到达***********\n");
            ShortWay(&G);
        } else if (WayChoose == 2) {
            printf("************最省费用到达***********\n");
            ShortWay(&G);
        } else if (WayChoose == 3) {
            printf("************最少中转路线数***********\n");
            Seek(&G);
        } else {
            printf("输入错误！请重新输入！！\n");
            goto WayFlag;
        }
    } else if (CustChoose == 2) {
        printf("***************************交通信息************************************\n");
        CityTimeTable(&G);
        goto CustomerFlag;
    } else if (CustChoose == 3) {
        exit(0);
    } else {
        goto CustomerFlag;
    }

}