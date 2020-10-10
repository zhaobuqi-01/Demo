
#include <stdio.h>
#include <stdlib.h>

#define ROW 10
#define COL 10

/*迷宫中位置信息*/
typedef struct position {
    int x;
    int y;
} position;

/*在迷宫中的当前位置的信息，也是入栈的基本元素*/
typedef struct Elem {
    int di;
    position seat;
} Elem;

/*链式栈中节点的定义*/
typedef struct Stack {
    Elem p;
    struct Stack *next;
} *Stack_pNode, Stack_Node;

void InitStack(Stack_pNode *Link) {//
    *Link = NULL;
}

void push(Stack_pNode *Link, Elem e) {
    Stack_pNode new_Elem = (Stack_pNode) malloc(sizeof(Stack_Node));
    new_Elem->p = e;
    new_Elem->next = NULL;
    if (*Link == NULL)
        *Link = new_Elem;
    else {
        new_Elem->next = *Link;
        *Link = new_Elem;
    }
}

int pop(Stack_pNode *Link, Elem *e) {
    if (*Link == NULL)
        return 0;
    *e = (*Link)->p;
    Stack_pNode q = *Link;
    *Link = (*Link)->next;
    free(q);
    return 1;
}

int top(Stack_pNode Link, Elem *e) {
    if (Link == NULL)
        return 0;
    *e = Link->p;
    return 1;
}

int empty(Stack_pNode Link) {
    if (Link == NULL)
        return 1;
    else
        return 0;
}

int reverse(Stack_pNode *Link) {
    Stack_pNode p, q, r;
    if (*Link == NULL || (*Link)->next == NULL)
        return 0;
    r = *Link;
    p = (*Link)->next;
    q = NULL;
    while (p) {
        r->next = q;
        q = r;
        r = p;
        p = p->next;
    }
    r->next = q;
    *Link = r;
}

void print(Stack_pNode Link) {
    Stack_pNode r = Link;
    while (r) {
        printf("(%d,%d,%d) ", r->p.seat.x, r->p.seat.y, r->p.di);
        r = r->next;
    }
}

int curstep = 1;
int m[ROW + 2][COL + 2] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
        1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
        1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1,
        1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
position dir_set[4] = {{0,  1},
                       {1,  0},
                       {0,  -1},
                       {-1, 0}};

int pass(position p) {
    if (m[p.x][p.y])
        return 0;
    else
        return 1;
}

void nextPos(position *p, int di) {
    (*p).x += dir_set[di].x;
    (*p).y += dir_set[di].y;
}

void markPrint(position p) {
    m[p.x][p.y] = 1;
}

int find_path(Stack_pNode *Maze_stack, position start, position end) {
    position curpos = start;
    Elem e;
    do {
        if (pass(curpos)) {
            m[curpos.x][curpos.y] = 1;
            e.seat = curpos;
            e.di = 0;
            push(Maze_stack, e);
            if (curpos.x == end.x && curpos.y == end.y)
                return 1;
            nextPos(&curpos, e.di);
        } else {
            if (!empty(*Maze_stack)) {
                pop(Maze_stack, &e);
                while (e.di == 3 && !empty(*Maze_stack)) {
                    markPrint(e.seat);
                    pop(Maze_stack, &e);
                    --curstep;
                }
                if (e.di < 3) {
                    ++e.di;
                    push(Maze_stack, e);
                    curpos = e.seat;
                    nextPos(&curpos, e.di);
                }//end if
            }//end if
        }//end else
    } while (!empty(*Maze_stack));
    return 0;
}


int main() {
    position start = {1, 1};
    position end = {10, 10};
    Stack_pNode maze_stack;
    InitStack(&maze_stack);//地址传递
    if (find_path(&maze_stack, start, end)) {
        reverse(&maze_stack);
        print(maze_stack);
    } else {
        printf("没有路\n");
    }

    return 0;
}
