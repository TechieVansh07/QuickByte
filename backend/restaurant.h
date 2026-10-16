#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include "Food.h"

using namespace std;

class Restaurant
{
private:
    int restaurantId;
    string name;
    string location;

    Food menu[3];
    int foodCount;

public:

    Restaurant(
        int id,
        string n,
        string l,
        Food f1,
        Food f2,
        Food f3
    );

    int getId();
    string getName();
    string getLocation();

    void showRestaurant();
    void showMenu();
};

#endif
