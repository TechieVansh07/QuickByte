#include "Food.h"

Food::Food(int id, string n, int p, string c)
{
    foodId = id;
    name = n;
    price = p;
    category = c;
}

int Food::getId()
{
    return foodId;
}

string Food::getName()
{
    return name;
}

int Food::getPrice()
{
    return price;
}

string Food::getCategory()
{
    return category;
}