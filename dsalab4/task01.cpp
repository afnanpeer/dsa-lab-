#include <cstdio>

#define MAX 4

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int value) {
	if (rear == MAX - 1) {
		std::printf("Queue Overflow! Cannot enqueue %d\n", value);
	} else {
		if (front == -1) {
			front = 0;
		}
		rear++;
		queue[rear] = value;
		std::printf("%d enqueued to queue\n", value);
	}
}

int main() {
	int totalValues;
	std::printf("How many values do you want to enqueue? ");
	std::scanf("%d", &totalValues);

	for (int i = 0; i < totalValues; i++) {
		int value;
		std::printf("Enter value %d: ", i + 1);
		std::scanf("%d", &value);
		enqueue(value);
	}

	std::printf("Front Index: %d, Rear Index: %d\n", front, rear);
	if (rear == MAX - 1) {
		std::printf("Queue is full\n");
	} else {
		std::printf("Queue is not full\n");
	}
	return 0;
}
