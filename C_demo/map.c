//
// Created by dingchunhui on 2020/12/28.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include"map.h"

//初始化无向图
void Creat(AdjMatrix *G) {
    char city1[21], city2[21];
    int way, n, m;
    printf("请输入交通图中的[城市数]与[路线数】[两个城市只有一条路线]\n");
    scanf("%d%d", &G->citynum, &G->waynum);
    for (int i = 1; i <= G->citynum; i++) {
        for (int j = 1; j <= G->citynum; j++) {
            G->way[i][j] = INFINITY;
        }
    }
    printf("请输入交通图中的%d个城市\n", G->citynum);
    for (int i = 1; i <= G->citynum; i++) {
        printf("第%d个城市\n", i);
        scanf("%s", G->city[i].name);
        _flushall();
    }
    for (int i = 1; i <= G->waynum; i++) {
        printf("请输入两个城市间的路线【两个城市只有一条路线】:\n");
        WAY:
        printf("起点城市:");
        scanf("%s", city1);
        printf("终点城市:");
        scanf("%s", city2);
        if (strcmp(city1, city2) == 0) {
            printf("输入错误,起点城市和终点城市相同【逻辑错误】!请重新输入!!\n");
            goto WAY;
        }
        printf("公里数:");
        scanf("%d", &way);
        n = Locate(G, city1);
        m = Locate(G, city2);
        G->way[n][m] = way;
        G->way[m][n] = way;
    }
    MapFileWrite(G);
}

//定位函数
int Locate(AdjMatrix *G, char city[]) {
    for (int i = 1; i <= G->citynum; i++) {
        if (!strcmp(G->city[i].name, city)) {
            return i;
        }
    }
    return -1;
}

void CityAdd(AdjMatrix *G) {
    MapFileRead(G);
    printf("请输入要添加的城市名称:");
    scanf("%s", G->city[G->citynum + 1].name);
    G->citynum = G->citynum + 1;
    for (int i = 1; i <= G->citynum; i++) {
        G->way[i][G->citynum] = INFINITY;
        for (int j = 1; j <= G->citynum; j++) {
            G->way[G->citynum][j] = INFINITY;
        }
    }
    MapFileWrite(G);
}

void CityDel(AdjMatrix *G) {
    MapFileRead(G);
    int No;
    char city[21];
    printf("请输入要删除的城市名称:");
    scanf("%s", city);
    No = Locate(G, city);
    for (int i = 1; i <= G->citynum; i++) {
        G->way[i][G->citynum] = INFINITY;
        for (int j = 1; j <= G->citynum; j++) {
            G->way[G->citynum][j] = INFINITY;
        }
    }
    G->citynum = G->citynum - 1;
    MapFileWrite(G);
}

//初始化队列
int InitQueue(CSeQueue *q) {
    q->front = 0;
    q->rear = 0;
    return True;
}

//入队
int InSeQueue(CSeQueue *q, int x) {
    if ((q->rear + 1) % MaxSize == q->front) {
        printf("队满\n");
        return False;
    } else {
        q->rear = (q->rear + 1) % MaxSize;
        q->elem[q->rear] = x;
        return True;
    }
}

//出队
int OutSeQueue(CSeQueue *q, int *x) {
    if (q->front == q->rear) {
        printf("队空\n");
        return False;
    } else {
        q->front = (q->front + 1) % MaxSize;
        *x = q->elem[q->front];
        return True;
    }
}

//判队空
int EmptySeQueuue(CSeQueue *q) {
    if (q->front == q->rear) {
        return True;
    } else {
        return False;
    }
}

void Seek(AdjMatrix *G) {
    MapFileRead(G);
    int start, end;
    char city1[21], city2[21];
    printf("请输入起点城市名称:");
    scanf("%s", city1);
    start = Locate(G, city1);
    printf("请输入起点城市名称:");
    scanf("%s", city2);
    end = Locate(G, city2);
    BFS(G, start, end);
//    BFSTravel(G);
}

void BFSTravel(AdjMatrix *G) {
    for (int v = 1; v <= G->citynum; v++) {
        visited[v] = 0;
    }
    for (int v = 1; v <= G->citynum; v++) {
        if (!visited[v])
            BFS(G, v, G->citynum);
    }
}

void BFS(AdjMatrix *G, int start, int end) {
    SlowList H;
    int flag;
    int x, slow;
    for (int i = 1; i <= G->citynum; i++) {
        visited[start] = 0;
    }
    printf("%s ", G->city[start].name);
    visited[start] = 1;
    CSeQueue Q;
    InitQueue(&Q);
    InSeQueue(&Q, start);
    while (!EmptySeQueuue(&Q)) {
        OutSeQueue(&Q, &x);
        for (int i = 1; i <= G->citynum; i++) {
            //未实现非其他
            //直达
            if (!visited[i] && G->way[x][i] != INFINITY && i == end) {
                //printf("%s ",G->city[x].name);
                visited[i] = 1;
                //printf("%s ", G->city[i].name);
                InSeQueue(&Q, i);
                break;
            }
            if (!visited[i] && G->way[x][i] != INFINITY) {
                visited[i] = 1;
                printf("%s ", G->city[i].name);
                InSeQueue(&Q, i);
            }
            if (x == end) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
        }

    }
}

//时刻表查询
void CityTimeTable(AdjMatrix *G) {
    MapFileRead(G);
    char city[21];
    int No = 0;
    printf("输入要查询的城市:");
    scanf("%s", city);
    No = Locate(G, city);
    for (int i = 1; i <= G->citynum; i++) {
        if (i == No) {
            for (int j = 1; j <= G->citynum; j++) {
                if (G->way[i][j] != INFINITY) {
                    printf("%s<------->%s距离:%dkm\n", G->city[No].name, G->city[j].name, G->way[i][j]);
                }
            }
        }
    }
}

//增加路线
void AddWay(AdjMatrix *G) {
    MapFileRead(G);
    char city1[21], city2[21];
    int start, end, way;
    WAY:
    printf("请输入增加路线的起点城市:\n");
    scanf("%s", city1);
    start = Locate(G, city1);
    printf("请输入增加路线的终点城市:\n");
    scanf("%s", city2);
    end = Locate(G, city2);
    if (strcmp(city1, city2) == 0) {
        printf("输入错误,起点城市和终点城市相同【逻辑错误】!请重新输入!!\n");
        goto WAY;
    }
    printf("距离:\n");
    scanf("%d", &way);
    if (G->way[start][end] == INFINITY && G->way[end][start] == INFINITY) {
        G->way[start][end] = way;
        G->way[end][start] = way;
        printf("\t\t\t成功\n");
    } else {
        printf("已有铁路!添加失败\n");
    }
    G->waynum += 1;
    MapFileWrite(G);
}

//删除路线
void Delway(AdjMatrix *G) {
    MapFileRead(G);
    int flag = 0;
    char city[21];
    int start, end, way;
    printf("请输入删除路线的起点城市:\n");
    scanf("%s", city);
    start = Locate(G, city);
    printf("请输入删除路线的终点城市:\n");
    scanf("%s", city);
    end = Locate(G, city);
    if (G->way[start][end] != INFINITY && G->way[end][start] != INFINITY) {
        G->way[start][end] = INFINITY;
        G->way[end][start] = INFINITY;
        printf("\t\t\t成功\n");
    } else {
        printf("没有铁路!删除失败\n");
    }
    G->waynum -= 1;
    MapFileWrite(G);
}

void Dijkstra(AdjMatrix *G, int start, int end, int dist[], int path[][MAXVEX]) {
    int mindist, i, j, k, t = 1;
    for (i = 1; i < G->citynum; i++) {
        dist[i] = G->way[start][i];
        if (G->way[start][i] != INFINITY) {
            path[i][1] = start;
        }
    }
    path[start][0] = 1;
    for (i = 2; i <= G->citynum; i++) {
        mindist = INFINITY;
        for (j = 1; j <= G->citynum; j++) {
            if (!path[j][0] && dist[j] < mindist) {
                k = j;
                mindist = dist[j];
            }
        }
        if (mindist == INFINITY) return;
        path[k][0] = 1;
        for (j = 1; j <= G->citynum; j++) {
            if (!path[j][0] && G->way[k][j] < INFINITY && dist[k] + G->way[k][j] < dist[j]) {
                dist[j] = dist[k] + G->way[k][j];
                t = 1;
                while (path[k][t] != 0) {
                    path[j][t] = path[k][t];
                    t++;
                    path[j][k] = k;
                    path[j][t + 1] = 0;
                }
            }
        }
    }
    for (i = 1; i <= G->citynum; i++) {
        if (i == end) {
            break;
        }
    }
    printf("%s--->%s最短路线为从%s", G->city[start].name, G->city[end].name, G->city[start].name);
    for (j = 2; path[i][j] != 0; j++) {
        printf("-->%s", G->city[path[i][j]].name);
    }
    printf("-->%s,距离为%d km\n", G->city[end].name, dist[i]);
}

//最短路径
void ShortWay(AdjMatrix *G) {
    MapFileRead(G);
    char city1[21],city2[21];
    int start, end;
    int dist[MAXVEX], path[MAXVEX][MAXVEX] = {0};
    printf("请输入起点城市:");
    scanf("%s", city1);
    start = Locate(G, city1);
    printf("请输入终点城市:");
    scanf("%s", city2);
    end = Locate(G, city2);
    Dijkstra(G, start, end, dist, path);
}

//文件操作
void MapFileWrite(AdjMatrix *G) {
    FILE *fp;
    fp = fopen("map.txt", "w");
    if (fp == NULL) {
        printf("The file can not be opened.\n");
        exit(1);
    } else {
        printf("The file now be opened.\n");
        fprintf(fp, "%5d%5d", G->citynum, G->waynum);
        for (int i = 1; i <= G->citynum; i++) {
            fprintf(fp, "%10s", G->city[i].name);
        }
        for (int i = 1; i <= G->citynum; i++) {
            for (int j = 1; j <= G->citynum; j++) {
                fprintf(fp, "%10d", G->way[i][j]);
            }
        }
    }
    if (fclose(fp) != 0) {
        printf("File can not be closed.\n");
        exit(1);
    } else {
        printf("File is now closed.\n");
    }
}

void MapFileRead(AdjMatrix *G) {
    FILE *fp;
    fp = fopen("map.txt", "r");
    if (fp == NULL) {
        printf("The file can not be opened.\n");
        exit(1);
    } else {
        fscanf(fp, "%5d%5d", &G->citynum, &G->waynum);
        for (int i = 1; i <= G->citynum; i++) {
            fscanf(fp, "%10s", G->city[i].name);
        }
        for (int i = 1; i <= G->citynum; i++) {
            for (int j = 1; j <= G->citynum; j++) {
                fscanf(fp, "%10d", &G->way[i][j]);
            }
        }
    }
    if (fclose(fp) != 0) {
        printf("File can not be closed.\n");
        exit(1);
    } else {
        printf("File is now closed.\n");
    }
}

int Login() {
    char RootName[] = "root";
    char PassWord[] = "admin";
    char username[10], passwd[21];
    char ch;
    printf("*****************登录系统*******************\n");
    for (int j = 1; j <= 3; j++) {
        printf("\t\t请输入用户名\n");
        scanf("%s", username);
        if (strcmp(username, RootName) == 0) {
            for (int i = 1; i <= 3; i++) {
                printf("\t\t请输入密码\n");
                scanf("%s", passwd);
                if (strcmp(PassWord, passwd) == 0) {
                    printf("********************登录成功******************\n");
                    return True;
                }
            }
            printf("*******************登录失败*******************\n");
            return False;
        } else {
            printf("*****************账号错误********************\n");
        }
    }
    return False;
}

void test() {
    printf("ok");
}

SlowList CreatList() {
    SlowList H = (Slow *) malloc(sizeof(Slow));
    H->Next = NULL;
    return H;
}