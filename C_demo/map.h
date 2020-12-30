//
// Created by dingchunhui on 2020/12/28.
//

#ifndef C_DEMO_MAP_H
#define C_DEMO_MAP_H

//导入头文件
#include "global.h"

//函数声明

//初始化图
void Creat(AdjMatrix *G);

//查找城市与数组下标对应关系
int Locate(AdjMatrix *G, char city[]);

//增加路线
void AddWay(AdjMatrix *G);

//删除路线
void Delway(AdjMatrix *G);

//增加城市
void CityAdd(AdjMatrix *G);

//删除城市
void CityDel(AdjMatrix *G);

//队列操作函数
//初始化队
int InitQueue(CSeQueue *q);

//入队
int InSeQueue(CSeQueue *q, int x);

//出队
int OutSeQueue(CSeQueue *q, int *x);

//判空队
int EmptySeQueuue(CSeQueue *q);

//广度搜索
void BFSTravel(AdjMatrix *G);

void BFS(AdjMatrix *G, int start,int end);

void Seek(AdjMatrix *G);

//最短路径Djkstra

void Djkstra(AdjMatrix *G, int start, int end, int dist[], int path[][MAXVEX]);

//最短路径
void ShortWay(AdjMatrix *G);

//查询信息
void CityTimeTable(AdjMatrix *G);

//写入文件
void MapFileWrite(AdjMatrix *G);

//读文件
void MapFileRead(AdjMatrix *G);

//管理员登录
int Login();

void test();
SlowList CreatList();

#endif //C_DEMO_MAP_H
