#include <iostream>
#include <string>

#include "Food.h"
#include "Restaurant.h"

using namespace std;

extern "C"
{
    #include "../dsa/dsa.h"
}

int main()
{
    string command;

    cout << "SmartFood C++ Engine Started" << endl;

    Food burger(
        101,
        "Burger",
        120,
        "Fast Food"
    );

    Food pizza(
        102,
        "Pizza",
        200,
        "Fast Food"
    );

    Food coke(
        103,
        "Coke",
        50,
        "Drinks"
    );

    Restaurant restaurant(
        1,
        "Food Corner",
        "Dehradun",
        burger,
        pizza,
        coke
    );

    while (true)
    {
        cin >> command;

        if (command == "MENU")
        {
            cout << "MENU_START" << endl;

            cout << burger.getId() << "|"
                 << burger.getName() << "|"
                 << burger.getPrice() << endl;

            cout << pizza.getId() << "|"
                 << pizza.getName() << "|"
                 << pizza.getPrice() << endl;

            cout << coke.getId() << "|"
                 << coke.getName() << "|"
                 << coke.getPrice() << endl;

            cout << "MENU_END" << endl;
        }

        else if (command == "HELP")
        {
            cout << "Available Commands:" << endl;
            cout << "MENU     - Display food menu" << endl;
            cout << "ADD      - Add food to cart" << endl;
            cout << "DISPLAY  - Display cart and total" << endl;
            cout << "REMOVE   - Remove item from cart" << endl;
            cout << "CLEAR    - Clear cart" << endl;
            cout << "ORDER    - Place an order" << endl;
            cout << "ORDERS   - Display orders" << endl;
            cout << "PROCESS  - Process an order" << endl;
            cout << "ROUTE    - Calculate shortest route" << endl;
            cout << "TRACE    - Display route trace" << endl;
            cout << "HELP     - Display available commands" << endl;
            cout << "EXIT     - Exit the program" << endl;
        }

        else if (command == "ADD")
        {
            int foodId;

            cin >> foodId;

            if (foodId == burger.getId())
            {
                addToCart(
                    burger.getId(),
                    burger.getPrice()
                );
            }

            else if (foodId == pizza.getId())
            {
                addToCart(
                    pizza.getId(),
                    pizza.getPrice()
                );
            }

            else if (foodId == coke.getId())
            {
                addToCart(
                    coke.getId(),
                    coke.getPrice()
                );
            }

            else
            {
                cout << "Food not found!" << endl;
                continue;
            }

            cout << "Food added successfully!" << endl;
        }

        else if (command == "DISPLAY")
        {
            displayCart();

            cout << "TOTAL "
                 << getCartTotal()
                 << endl;
        }

        else if (command == "REMOVE")
        {
            int foodId;

            cin >> foodId;

            removeFromCart(foodId);

            cout << "Item removed successfully!" << endl;
        }

        else if (command == "CLEAR")
        {
            clearCart();

            cout << "Cart cleared successfully!" << endl;
        }

        else if (command == "EXIT")
        {
            break;
        }
        else if (command == "ORDER")
{
    int orderId;

    cin >> orderId;

    int total = getCartTotal();

    if (total == 0)
    {
        cout << "Cart is empty!" << endl;
        continue;
    }

    enqueueOrder(orderId, total);

    clearCart();

    cout << "ORDER_PLACED "
         << orderId
         << " "
         << total
         << endl;
}



        else if (command == "ORDERS")
        {
            displayOrders();
            cout << "ORDERS_END" << endl;
        }

        else if (command == "PROCESS")
        {
            processOrder();
        }

        else if (command == "ROUTE")
        {
            int destination;
            cin >> destination;

            calculateShortestPath(destination);
        }
        
else if (command == "TRACE")
{
    int destination;
    cin >> destination;

    calculateShortestPathTrace(destination);
}

        else
        {
            cout << "Unknown command" << endl;
            cout <<"Try using HELP command"<<endl;
        }
    }


    return 0;
}