//
// Created by dingchunhui on 2020/12/28.
//

#ifndef C_DEMO_MAP_H
#define C_DEMO_MAP_H

//����ͷ�ļ�
#include "global.h"

//��������

//��ʼ��ͼ
void Creat(AdjMatrix *G);

//���ҳ����������±��Ӧ��ϵ
int Locate(AdjMatrix *G, char city[]);

//����·��
void AddWay(AdjMatrix *G);

//ɾ��·��
void Delway(AdjMatrix *G);

//���ӳ���
void CityAdd(AdjMatrix *G);

//ɾ������
void CityDel(AdjMatrix *G);

//���в�������
//��ʼ����
int InitQueue(CSeQueue *q);

//���
int InSeQueue(CSeQueue *q, int x);

//����
int OutSeQueue(CSeQueue *q, int *x);

//�пն�
int EmptySeQueuue(CSeQueue *q);

//�������
void BFSTravel(AdjMatrix *G);

void BFS(AdjMatrix *G, int start,int end);

void Seek(AdjMatrix *G);

//���·��Djkstra

void Djkstra(AdjMatrix *G, int start, int end, int dist[], int path[][MAXVEX]);

//���·��
void ShortWay(AdjMatrix *G);

//��ѯ��Ϣ
void CityTimeTable(AdjMatrix *G);

//д���ļ�
void MapFileWrite(AdjMatrix *G);

//���ļ�
void MapFileRead(AdjMatrix *G);

//����Ա��¼
int Login();

void test();
SlowList CreatList();

#endif //C_DEMO_MAP_H
