#include <iostream>
#include "Restaurant.h"

using namespace std;

Restaurant::Restaurant(
    int id,
    string n,
    string l,
    Food f1,
    Food f2,
    Food f3
)
    : menu{f1, f2, f3}
{
    restaurantId = id;
    name = n;
    location = l;
    foodCount = 3;
}

int Restaurant::getId()
{
    return restaurantId;
}

string Restaurant::getName()
{
    return name;
}

string Restaurant::getLocation()
{
    return location;
}

void Restaurant::showRestaurant()
{
    cout << "\nRestaurant: " << name << endl;
    cout << "Location: " << location << endl;
}

void Restaurant::showMenu()
{
    cout << "\nMenu:\n";

    for (int i = 0; i < foodCount; i++)
    {
        cout << menu[i].getId()
             << " - "
             << menu[i].getName()
             << " - Rs."
             << menu[i].getPrice()
             << menu[i].showFood()
             << endl;
    }
}