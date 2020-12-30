//
// Created by dingchunhui on 2020/12/29.
//

#ifndef C_DEMO_GLOBAL_H
#define C_DEMO_GLOBAL_H

#define  MAXVEX 20
#define  INFINITY 32767
#define MaxSize 19
#define True 1;
#define False 0;
extern int visited[MAXVEX];
typedef struct {
    int elem[MaxSize];
    int front;//��ͷָ��
    int rear;//��βָ��
} CSeQueue;

typedef struct {
    char name[21];
} City;

typedef struct {
    int way[MAXVEX][MAXVEX];
    City city[MAXVEX];//������Ϣ
    int citynum;//���и���
    int waynum;//��·����
} AdjMatrix;//�ڽӾ���

typedef struct SlowFlag{
    int slow;
    struct SlowFlag *Next;
}Slow, *SlowList;
#endif //C_DEMO_GLOBAL_H
