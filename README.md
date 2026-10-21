# Smart Online Food Ordering and Shortest-Path Delivery System

## Overview

The **Smart Online Food Ordering and Shortest-Path Delivery System** is
a C/C++-based academic project that demonstrates the practical use of
**Data Structures, Algorithms, and Object-Oriented Programming (OOP)**
in a real-world food-ordering and delivery scenario.

The system provides a structured workflow for customers to browse
restaurants and menus, select food items, manage their cart, calculate
the bill, and place orders. Restaurants/admins can manage menus and
process incoming orders. The delivery component represents locations and
roads using a **weighted graph** and uses **Dijkstra's shortest-path
algorithm** to calculate the shortest route from the restaurant to the
customer.

## Objectives

-   Develop a working online food-ordering system prototype.
-   Implement customer registration, login, and menu browsing.
-   Provide cart management and bill calculation.
-   Implement restaurant/admin menu and order management.
-   Manage pending orders using a FIFO queue.
-   Represent delivery locations using a weighted graph.
-   Apply Dijkstra's algorithm for shortest-path delivery routing.
-   Demonstrate Data Structures and OOP concepts in a practical
    application.

## Main Workflow

``` text
Customer Login / Registration
            ↓
Browse Restaurants & Menu
            ↓
Select Food & Add to Cart
            ↓
Review Cart & Calculate Bill
            ↓
Place Order
            ↓
Restaurant Receives Order
            ↓
Order Accepted & Food Prepared
            ↓
Calculate Shortest Delivery Route
            ↓
Food Delivered
            ↓
Order Completed
```

## Data Structures & Algorithms

  Component            Concept
  -------------------- ----------------------
  Menu data            Array
  Cart / Order items   Linked List
  Pending orders       Queue (FIFO)
  Menu operations      Searching & Sorting
  Delivery network     Weighted Graph
  Delivery routing     Dijkstra's Algorithm

### Dijkstra's Shortest-Path Example

The delivery network is represented as a predefined weighted graph:

``` text
Restaurant A ──2 km──> C ──1 km──> D ──2 km──> Customer F

Shortest path:
A → C → D → F = 5 km
```

The project uses a predefined graph rather than live GPS or real-time
map data so that the shortest-path algorithm can be demonstrated
clearly.

## Object-Oriented Programming

The major system entities are represented using C++ classes:

-   `Customer`
-   `Food`
-   `Restaurant`
-   `Order`
-   `Delivery`

The project uses OOP to organize these real-world entities and their
related operations.

## Technology Stack

-   **Languages:** C and C++
-   **Development Environment:** Visual Studio Code
-   **Libraries:** Standard C/C++ libraries
-   **Data Structures:** Arrays, Linked Lists, Queue, Weighted Graph
-   **Algorithms:** Searching, Sorting, Dijkstra's Algorithm
-   **Programming Approach:** Object-Oriented Programming in C++

## Project Scope

This is an **academic prototype** and does not attempt to replicate
large commercial platforms such as Zomato or Swiggy. The focus is on
implementing the essential ordering workflow and demonstrating the
underlying Data Structures, Algorithms, and OOP concepts.

The initial scope does not include:

-   Real payment gateway integration
-   Live GPS/map integration
-   Real-time map data
-   Live notifications

## Expected Deliverables

-   Working C/C++ Online Food Ordering System prototype
-   Customer, restaurant/admin, and delivery modules
-   Menu management
-   Cart and bill calculation
-   Pending-order queue and status processing
-   Weighted delivery graph
-   Dijkstra-based shortest-path routing
-   Commented source code
-   Design documentation
-   Test cases
-   Final working demonstration

## Team

**Team Name:** TEAM QUIKEE\
**Team ID:** DSCPP-III-2026-T221

  Member                  Student ID Role
  --------------------- ------------ ------------------------
  Addhyan Kumar              2027536 Team Lead
  Vansh Bharadwaj            2029026 Technical Lead
  Parth Singh Chauhan        2029074 Research Lead
  Akash Kumar                2028629 Operations Coordinator

## References

1.  Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. ---
    *Introduction to Algorithms*.
2.  Horowitz, E., Sahni, S., & Anderson-Freed --- *Fundamentals of Data
    Structures in C*.
3.  Deitel, P. J., & Deitel, H. M. --- *C++ How to Program*.
4.  Course material and lecture notes on Data Structures and
    Object-Oriented Programming.
