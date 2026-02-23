#include <iostream>
#include <array>
#include <chrono>
#include <limits>

using namespace std;

constexpr int MAX = 4;
array<int, MAX> queueArr{};
int front = -1;
int rear = -1;

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return front == (rear + 1) % MAX;
}

void enqueue(int val) {
    if (isFull()) {
        cout << "Queue Overflow\n";
        return;
    }

    if (isEmpty()) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    queueArr[rear] = val;
    cout << val << " enqueued\n";

    if (isFull()) {
        cout << "Queue is full\n";
    }
}

int dequeueVal() {
    if (isEmpty()) {
        cout << "Queue Underflow\n";
        return -1;
    }

    int removed = queueArr[front];

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX;
    }

    return removed;
}

void display() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return;
    }

    cout << "Queue: ";
    int i = front;
    while (true) {
        cout << queueArr[i] << " ";
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    cout << "\n";
}

void benchmark() {
    const int N = 50000;

    int idxMod = 0;
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) idxMod = (idxMod + 1) % MAX;
    auto t2 = chrono::high_resolution_clock::now();

    int idxAdd = 0;
    auto t3 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        idxAdd = idxAdd + 1;
        if (idxAdd == MAX) idxAdd = 0;
    }
    auto t4 = chrono::high_resolution_clock::now();

    front = -1;
    rear = -1;
    auto t5 = chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        enqueue(i);
        dequeueVal();
    }
    auto t6 = chrono::high_resolution_clock::now();

    auto modNs = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
    auto addNs = chrono::duration_cast<chrono::nanoseconds>(t4 - t3).count();
    auto queueNs = chrono::duration_cast<chrono::nanoseconds>(t6 - t5).count();

    cout << "Modulo loop time: " << modNs << " ns\n";
    cout << "Addition+reset loop time: " << addNs << " ns\n";
    cout << "Circular enqueue+dequeue (50,000 ops): " << queueNs << " ns\n";
}

int main() {
    int choice, value;

    while (true) {
        cout << "\n1. Enqueue\n2. Dequeue\n3. Display\n4. Benchmark\n5. Exit\nEnter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;
        }

        if (choice == 1) {
            cout << "Enter value: ";
            if (!(cin >> value)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input\n";
                continue;
            }
            enqueue(value);
        } else if (choice == 2) {
            int removed = dequeueVal();
            if (removed != -1) cout << removed << " dequeued\n";
        } else if (choice == 3) {
            display();
        } else if (choice == 4) {
            benchmark();
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}