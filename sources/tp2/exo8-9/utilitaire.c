// utilitaire.c

#include "utilitaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Fonctions pour la gestion de la pile
Stack *createStack()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;

    return stack;
}

void push(Stack *stack, int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;

    stack->top = newNode;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        fprintf(stderr, "Error: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;

    free(temp);
    return data;
}

int top(Stack *stack)
{
    if (isEmpty(stack))

    {
        fprintf(stderr, "Error: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}


int isEmpty(Stack *stack)
{
    return stack->top == NULL;
}

void freeStack(Stack *stack)

{

    while (!isEmpty(stack))
    {
        pop(stack);

    }

    free(stack);
}

// Fonctions pour la gestion de la file

Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue));

    queue->front = queue->rear = NULL;
    return queue;
}


void enqueue(Queue *queue, char data)
{
    QueueNode *newNode = malloc(sizeof(QueueNode));
    newNode->data = data;

    newNode->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = queue->rear = newNode;

        return;
    }
    queue->rear->next = newNode;

    queue->rear = newNode;
}

char dequeue(Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        fprintf(stderr, "Erreur le pile est vide.\n");

        exit(EXIT_FAILURE);

    }
    QueueNode *temp = queue->front;
    char data = temp->data;

    queue->front = temp->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

int isQueueEmpty(Queue *queue)
{
    return queue->front == NULL;

}

void freeQueue(Queue *queue)
{
    while (!isQueueEmpty(queue))

    {
        dequeue(queue);

    }
    free(queue);
}

// Fonction pour convertir une expression infixée en postfixée sans priorité

void exp_post_fixe_sans_prio(const char *expression)
{
    Queue *output = createQueue();
    while (*expression)
    {
        if (isdigit(*expression))
        {
            while (isdigit(*expression))
            {

                enqueue(output, *expression);

                expression++;
            }
            enqueue(output, ' '); // Séparateur

        }
        else if (*expression == '+' || *expression == '*')

        {
            enqueue(output, *expression);

            enqueue(output, ' '); // Séparateur

            expression++;
        }
        else
        {
            expression++;
        }
    }

    printf("Expression postgi sans priorité: ");
    while (!isQueueEmpty(output))
    {
        printf("%c", dequeue(output));
    }
    printf("\n");

    freeQueue(output);
}

// conversion de express infixer en postfixer avec prio

int precedence(char op)
{

    if (op == '*' || op == '/')

        return 2; 

    if (op == '+' || op == '-')
        return 1;
    return 0;
}


void exp_post_fixe_avec_prio(const char *expression)
{
    Stack *operators = createStack();

    Queue *output = createQueue();

    while (*expression)
    {
        if (isdigit(*expression))
        {
            while (isdigit(*expression))
            {
                enqueue(output, *expression);

                expression++;
            }
            enqueue(output, ' '); // Séparateur

        }
        else if (*expression == '+' || *expression == '*')
        
        {
            while (!isEmpty(operators) && precedence(top(operators)) >= precedence(*expression))
            {
                enqueue(output, pop(operators));
                enqueue(output, ' '); 
            }
            push(operators, *expression);
            expression++;
        }
        else
        {
            expression++;
        }
    }

    while (!isEmpty(operators))
    {
        enqueue(output, pop(operators));

        enqueue(output, ' '); // Séparateur
    }

    printf("Expression postfixée avec priorité: ");

    while (!isQueueEmpty(output))
    {

        printf("%c", dequeue(output));

    }
    printf("\n");

    freeStack(operators);
    
    freeQueue(output);
}
