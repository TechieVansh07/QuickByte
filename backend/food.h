#ifndef FOOD_H
#define FOOD_H

#include <string>

using namespace std;

class Food
{
private:
    int foodId;
    string name;
    int price;
    string category;

public:

    Food(int id, string n, int p, string c);

    int getId();
    string getName();
    int getPrice();
    string getCategory();
};

#endif