#include <stdlib.h>
#include <iostream>
using namespace std;

struct queue {
    int* a;
    int front;
    int rear;
    int size;
    unsigned c;
};

queue* creat(unsigned c) {
    queue* q = new queue();
    // q = (queue*)malloc(sizeof(queue));
    q->c = c;
    q->front = 0;
    q->rear = (c - 1);
    q->size = 0;
    // q->a = (int*)malloc(sizeof(int));
    return q;
}

int isfull(queue* q) {
    return (q->size == q->c);
}

int isempty(queue* q) {
    return (q->size == 0);
}

void add_to_queue(queue* q, int item) {
    if (isfull(q)) {
        cout << "the queue is full :(" << '\n';
        return;
    }
    q->rear = q->rear + 1;
    int i = q->rear;
    q->a[i] = item;
    q->size = q->size + 1;
    cout << "the item has been added ! :]" << '\n';
}

int delete_queue(queue* q) {
    if (isempty(q))
        cout << "queue is empty; add an item ! :)" << '\n';
    int i = q->front;
    int item = q->a[i];
    q->front = q->front + 1 % q->c;
    q->size = q->size - 1;
    cout << "the item has been deleted ! ;]" << '\n' << "that item was " << item << '\n';
    return item;
}

int main() {
    queue* q = new queue();

    while (true) {
        cout << "1) add an item ." << '\n'
             << "2) delete an item ." << '\n'
             << "3) creat a queue. " << '\n';
        int menu;
        cin >> menu;
        switch (menu) {
            case 1:
                cout << "enter the element you want to add:" << endl;
                int a;
                cin >> a;
                add_to_queue(q, a);
                break;

            case 2:
                delete_queue(q);
                break;

            case 3: {
                int c;
                cout << "enter the size of queue :" << endl;
                cin >> c;
                q = creat(c);
                cout << "queue has been created !" << '\n';
                break;
            }
            case 0:
                cout << "G00D Luck! :]" << '\n';
                return 0;
        }
    }

    return 0;
}