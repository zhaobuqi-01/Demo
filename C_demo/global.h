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
    int front;//队头指针
    int rear;//队尾指针
} CSeQueue;

typedef struct {
    char name[21];
} City;

typedef struct {
    int way[MAXVEX][MAXVEX];
    City city[MAXVEX];//城市信息
    int citynum;//城市个数
    int waynum;//铁路个数
} AdjMatrix;//邻接矩阵

typedef struct SlowFlag{
    int slow;
    struct SlowFlag *Next;
}Slow, *SlowList;
#endif //C_DEMO_GLOBAL_H
