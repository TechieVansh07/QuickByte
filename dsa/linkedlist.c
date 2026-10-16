#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int foodId;
    int price;
    int quantity;

    struct Node *next;
};


struct Node *head = NULL;

void addToCart(int foodId, int price)
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        if (temp->foodId == foodId)
        {
            temp->quantity++;
            return;
        }

        temp = temp->next;
    }

    struct Node *newNode;

    newNode = (struct Node *)malloc(
        sizeof(struct Node)
    );

    newNode->foodId = foodId;
    newNode->price = price;
    newNode->quantity = 1;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }

    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}


void displayCart()
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        printf(
            "%d %d %d\n",
            temp->foodId,
            temp->price,
            temp->quantity
        );

        temp = temp->next;
    }
}


int getCartTotal()
{
    struct Node *temp = head;

    int total = 0;

    while (temp != NULL)
    {
        total = total +
                (temp->price * temp->quantity);

        temp = temp->next;
    }

    return total;
}

void removeFromCart(int foodId)
{
    struct Node *temp = head;
    struct Node *previous = NULL;

    while (temp != NULL)
    {
        if (temp->foodId == foodId)
        {
            if (temp->quantity > 1)
            {
                temp->quantity--;
                return;
            }

            if (previous == NULL)
            {
                head = temp->next;
            }

            else
            {
                previous->next = temp->next;
            }

            free(temp);

            return;
        }

        previous = temp;
        temp = temp->next;
    }
}


void clearCart()
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        struct Node *next = temp->next;

        free(temp);

        temp = next;
    }

    head = NULL;
}