//
// Created by dingchunhui on 2020/12/29.
//

#include "map.h"
#include "menu.h"
#include <stdio.h>
#include "windows.h"

void Menu() {
    int MainChoose;
    printf("***********************���н�ͨͼ**********************\n");
    MAINFALG:
    printf("\t\t\t1.����Ա��¼\n\t\t\t2.�ÿͲ�ѯ\n\t\t\t3.�˳�\n");
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
        printf("**************************��Ϣ�޸�*******************************\n");
        printf("\t\t\t1.��ͨͼ��ʼ��\n\t\t\t2.������Ϣ�޸�\n\t\t\t3.·����Ϣ�޸�\n\t\t\t4.��Ϣ��ѯ\n\t\t\t5.�˳�\n");
        scanf("%d", &RootChoose);
        system("cls");
        if (RootChoose == 1) {
            printf("*******************************************��ʼ��*************************************\n\t\t\t");
            Creat(&G);
            goto RootFlag;
        } else if (RootChoose == 2) {
            printf("**********************������Ϣ�޸�**************************\n");
            printf("\t\t\t1.���\n\t\t\t2.ɾ��\n");
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
            printf("****************************·���޸�*****************************\n");
            printf("\t\t\t1.����·��\n\t\t\t2.ɾ��·��\n\t\t\t3.������һ���˵�\n\t\t\t4.�˳�\n");
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
            printf("***************************��ͨ��Ϣ************************************\n");
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
    printf("*********************************·�߲�ѯ*********************************\n");
    printf("\t\t\t1.·�߾���\n\t\t\t2.��ͨͼ��Ϣ\n\t\t\t3.�˳�\n");
    scanf("%d", &CustChoose);
    system("cls");
    if (CustChoose == 1) {
        WayFlag:
        printf("***************************·�߾���ѡ��************************************\n");
        printf("\t\t\t��ѡ�����:\t\t\t\n\t1.��쵽��\t\t\t\n\t2.��ʡ���õ���\t\t\t\n\t3.������ת·����\t\t\t\n");
        scanf("%d", &WayChoose);
        if (WayChoose == 1) {
            printf("************��쵽��***********\n");
            ShortWay(&G);
        } else if (WayChoose == 2) {
            printf("************��ʡ���õ���***********\n");
            ShortWay(&G);
        } else if (WayChoose == 3) {
            printf("************������ת·����***********\n");
            Seek(&G);
        } else {
            printf("����������������룡��\n");
            goto WayFlag;
        }
    } else if (CustChoose == 2) {
        printf("***************************��ͨ��Ϣ************************************\n");
        CityTimeTable(&G);
        goto CustomerFlag;
    } else if (CustChoose == 3) {
        exit(0);
    } else {
        goto CustomerFlag;
    }

}