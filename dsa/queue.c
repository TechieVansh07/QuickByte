#include <stdio.h>
#include <stdlib.h>

struct Order
{
    int orderId;
    int total;

    struct Order *next;
};

struct Order *front = NULL;
struct Order *rear = NULL;


void enqueueOrder(int orderId, int total)
{
    struct Order *newOrder;

   newOrder = (struct Order *)malloc(sizeof(struct Order));

if (newOrder == NULL)
{
    printf("Memory allocation failed!\n");
    return;
}

newOrder->orderId = orderId;
    newOrder->total = total;
    newOrder->next = NULL;


    if (rear == NULL)
    {
        front = newOrder;
        rear = newOrder;
    }

    else
    {
        rear->next = newOrder;
        rear = newOrder;
    }
}


void displayOrders()
{
    struct Order *temp = front;

    if (temp == NULL)
    {
        printf("No pending orders\n");
        return;
    }

    while (temp != NULL)
    {
        printf(
            "ORDER %d %d\n",
            temp->orderId,
            temp->total
        );

        temp = temp->next;
    }
}


void processOrder()
{
    if (front == NULL)
    {
        printf("No pending orders\n");
        return;
    }

    struct Order *temp = front;

    printf(
        "PROCESSED %d %d\n",
        temp->orderId,
        temp->total
    );

    front = front->next;

    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);
}