#ifndef UTILITAIRE_H
#define UTILITAIRE_H


// definition des structure de donnees a utiliser
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

typedef struct QueueNode
{
    char data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

// definition de prototypes de fonction
Stack *createStack();
void push(Stack *stack, int data);
int pop(Stack *stack);
int top(Stack *stack);
int isEmpty(Stack *stack);
void freeStack(Stack *stack);

Queue *createQueue();
void enqueue(Queue *queue, char data);
char dequeue(Queue *queue);
int isQueueEmpty(Queue *queue);
void freeQueue(Queue *queue);

void exp_post_fixe_sans_prio(const char *expression);
void exp_post_fixe_avec_prio(const char *expression);

#endif 
