#include <iostream>
using namespace std;
#include "Stack.h"
#include "MyStack.h"
#include "Queue.h"
#include "MyQueue.h"

/*
1. this task is about using queue in a fast food restaurant system.
customers place orders and those orders must be served in the same order.

2. i will make an order class and then use queue to store order ids.
order details will be stored in arrays and queue will control the sequence.

3. queue is best here because first order placed should be first order served.

4. learned how queue can solve real life problems like restaurant order handling.

5. now i can make queue based systems like tokens, orders and service lines.
*/

class Order
{
public:
    int id;
    string item;
    int price;
    int timeTaken;

    Order()
    {
        id = 0;
        item = "";
        price = 0;
        timeTaken = 0;
    }

    Order(int i, string it, int p, int t)
    {
        id = i;
        item = it;
        price = p;
        timeTaken = t;
    }
};

// show one order
void showOrder(Order o)
{
    cout << "order id: " << o.id << endl;
    cout << "item: " << o.item << endl;
    cout << "price: " << o.price << endl;
    cout << "time taken: " << o.timeTaken << " minutes" << endl;
}

// place order in queue
void placeOrder(Queue* q, Order orders[], int& count, string item, int price, int timeTaken)
{
    orders[count] = Order(count + 1, item, price, timeTaken);
    q->enqueue(count);
    cout << "order placed\n";
    showOrder(orders[count]);
    cout << endl;
    count++;
}

// serve next order
void serveOrder(Queue* q, Order orders[], int& totalEarned, int& totalTime)
{
    if (q->isEmpty())
    {
        cout << "no order to serve\n\n";
        return;
    }

    int index = q->dequeue();

    cout << "order served\n";
    showOrder(orders[index]);
    cout << endl;

    totalEarned += orders[index].price;
    totalTime += orders[index].timeTaken;
}

// show pending orders
void displayPendingOrders(Queue* q, Order orders[])
{
    if (q->isEmpty())
    {
        cout << "no pending orders\n\n";
        return;
    }

    int n = 0;
    Queue* temp = new MyQueue(20);

    while (!q->isEmpty())
    {
        int index = q->dequeue();
        temp->enqueue(index);
        n++;
    }

    cout << "pending orders:\n";
    for (int i = 0; i < n; i++)
    {
        int index = temp->dequeue();
        showOrder(orders[index]);
        cout << endl;
        q->enqueue(index);
    }

    delete temp;
}

// show summary
void showSummary(int totalEarned, int totalTime)
{
    cout << "total money earned: " << totalEarned << endl;
    cout << "total preparation time: " << totalTime << " minutes" << endl;
}

int main()
{
    const int MAX_ORDERS = 20;

    Queue* orderQueue = new MyQueue(MAX_ORDERS);
    Order orders[MAX_ORDERS];

    int orderCount = 0;
    int totalEarned = 0;
    int totalTime = 0;

    // test sequence 1
    placeOrder(orderQueue, orders, orderCount, "Burger", 200, 20);
    placeOrder(orderQueue, orders, orderCount, "Sandwich", 250, 30);
    placeOrder(orderQueue, orders, orderCount, "French Fries", 100, 10);
    placeOrder(orderQueue, orders, orderCount, "Fried Chicken", 400, 40);
    placeOrder(orderQueue, orders, orderCount, "Pizza", 350, 40);

    displayPendingOrders(orderQueue, orders);

    serveOrder(orderQueue, orders, totalEarned, totalTime);
    serveOrder(orderQueue, orders, totalEarned, totalTime);

    cout << "after serving two orders\n";
    displayPendingOrders(orderQueue, orders);

    // test sequence 2
    placeOrder(orderQueue, orders, orderCount, "Burger", 200, 20);
    placeOrder(orderQueue, orders, orderCount, "Pizza", 350, 40);

    cout << "updated pending list\n";
    displayPendingOrders(orderQueue, orders);

    // serve all remaining orders
    while (!orderQueue->isEmpty())
    {
        serveOrder(orderQueue, orders, totalEarned, totalTime);
    }

    cout << "final summary\n";
    showSummary(totalEarned, totalTime);

    delete orderQueue;
    return 0;
}