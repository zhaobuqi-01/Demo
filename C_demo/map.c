//
// Created by dingchunhui on 2020/12/28.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include"map.h"

//��ʼ������ͼ
void Creat(AdjMatrix *G) {
    char city1[21], city2[21];
    int way, n, m;
    printf("�����뽻ͨͼ�е�[������]��[·������[��������ֻ��һ��·��]\n");
    scanf("%d%d", &G->citynum, &G->waynum);
    for (int i = 1; i <= G->citynum; i++) {
        for (int j = 1; j <= G->citynum; j++) {
            G->way[i][j] = INFINITY;
        }
    }
    printf("�����뽻ͨͼ�е�%d������\n", G->citynum);
    for (int i = 1; i <= G->citynum; i++) {
        printf("��%d������\n", i);
        scanf("%s", G->city[i].name);
        _flushall();
    }
    for (int i = 1; i <= G->waynum; i++) {
        printf("�������������м��·�ߡ���������ֻ��һ��·�ߡ�:\n");
        WAY:
        printf("������:");
        scanf("%s", city1);
        printf("�յ����:");
        scanf("%s", city2);
        if (strcmp(city1, city2) == 0) {
            printf("�������,�����к��յ������ͬ���߼�����!����������!!\n");
            goto WAY;
        }
        printf("������:");
        scanf("%d", &way);
        n = Locate(G, city1);
        m = Locate(G, city2);
        G->way[n][m] = way;
        G->way[m][n] = way;
    }
    MapFileWrite(G);
}

//��λ����
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
    printf("������Ҫ��ӵĳ�������:");
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
    printf("������Ҫɾ���ĳ�������:");
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

//��ʼ������
int InitQueue(CSeQueue *q) {
    q->front = 0;
    q->rear = 0;
    return True;
}

//���
int InSeQueue(CSeQueue *q, int x) {
    if ((q->rear + 1) % MaxSize == q->front) {
        printf("����\n");
        return False;
    } else {
        q->rear = (q->rear + 1) % MaxSize;
        q->elem[q->rear] = x;
        return True;
    }
}

//����
int OutSeQueue(CSeQueue *q, int *x) {
    if (q->front == q->rear) {
        printf("�ӿ�\n");
        return False;
    } else {
        q->front = (q->front + 1) % MaxSize;
        *x = q->elem[q->front];
        return True;
    }
}

//�жӿ�
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
    printf("����������������:");
    scanf("%s", city1);
    start = Locate(G, city1);
    printf("����������������:");
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
            //δʵ�ַ�����
            //ֱ��
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

//ʱ�̱��ѯ
void CityTimeTable(AdjMatrix *G) {
    MapFileRead(G);
    char city[21];
    int No = 0;
    printf("����Ҫ��ѯ�ĳ���:");
    scanf("%s", city);
    No = Locate(G, city);
    for (int i = 1; i <= G->citynum; i++) {
        if (i == No) {
            for (int j = 1; j <= G->citynum; j++) {
                if (G->way[i][j] != INFINITY) {
                    printf("%s<------->%s����:%dkm\n", G->city[No].name, G->city[j].name, G->way[i][j]);
                }
            }
        }
    }
}

//����·��
void AddWay(AdjMatrix *G) {
    MapFileRead(G);
    char city1[21], city2[21];
    int start, end, way;
    WAY:
    printf("����������·�ߵ�������:\n");
    scanf("%s", city1);
    start = Locate(G, city1);
    printf("����������·�ߵ��յ����:\n");
    scanf("%s", city2);
    end = Locate(G, city2);
    if (strcmp(city1, city2) == 0) {
        printf("�������,�����к��յ������ͬ���߼�����!����������!!\n");
        goto WAY;
    }
    printf("����:\n");
    scanf("%d", &way);
    if (G->way[start][end] == INFINITY && G->way[end][start] == INFINITY) {
        G->way[start][end] = way;
        G->way[end][start] = way;
        printf("\t\t\t�ɹ�\n");
    } else {
        printf("������·!���ʧ��\n");
    }
    G->waynum += 1;
    MapFileWrite(G);
}

//ɾ��·��
void Delway(AdjMatrix *G) {
    MapFileRead(G);
    int flag = 0;
    char city[21];
    int start, end, way;
    printf("������ɾ��·�ߵ�������:\n");
    scanf("%s", city);
    start = Locate(G, city);
    printf("������ɾ��·�ߵ��յ����:\n");
    scanf("%s", city);
    end = Locate(G, city);
    if (G->way[start][end] != INFINITY && G->way[end][start] != INFINITY) {
        G->way[start][end] = INFINITY;
        G->way[end][start] = INFINITY;
        printf("\t\t\t�ɹ�\n");
    } else {
        printf("û����·!ɾ��ʧ��\n");
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
    printf("%s--->%s���·��Ϊ��%s", G->city[start].name, G->city[end].name, G->city[start].name);
    for (j = 2; path[i][j] != 0; j++) {
        printf("-->%s", G->city[path[i][j]].name);
    }
    printf("-->%s,����Ϊ%d km\n", G->city[end].name, dist[i]);
}

//���·��
void ShortWay(AdjMatrix *G) {
    MapFileRead(G);
    char city1[21],city2[21];
    int start, end;
    int dist[MAXVEX], path[MAXVEX][MAXVEX] = {0};
    printf("������������:");
    scanf("%s", city1);
    start = Locate(G, city1);
    printf("�������յ����:");
    scanf("%s", city2);
    end = Locate(G, city2);
    Dijkstra(G, start, end, dist, path);
}

//�ļ�����
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
    printf("*****************��¼ϵͳ*******************\n");
    for (int j = 1; j <= 3; j++) {
        printf("\t\t�������û���\n");
        scanf("%s", username);
        if (strcmp(username, RootName) == 0) {
            for (int i = 1; i <= 3; i++) {
                printf("\t\t����������\n");
                scanf("%s", passwd);
                if (strcmp(PassWord, passwd) == 0) {
                    printf("********************��¼�ɹ�******************\n");
                    return True;
                }
            }
            printf("*******************��¼ʧ��*******************\n");
            return False;
        } else {
            printf("*****************�˺Ŵ���********************\n");
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