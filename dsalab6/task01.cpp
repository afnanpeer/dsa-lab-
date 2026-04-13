#include <iostream>
using namespace std;

#define V 4

void initMatrix(int matrix[][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			matrix[i][j] = 0;
		}
	}
}

void addEdge(int matrix[][V], int src, int dest) {
	matrix[src][dest] = 1;
	matrix[dest][src] = 1;
}

void printMatrix(int matrix[][V]) {
	cout << "Adjacency Matrix:\n";
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	int adjMatrix[V][V];

	initMatrix(adjMatrix);

	addEdge(adjMatrix, 0, 1);
	addEdge(adjMatrix, 1, 2);
	addEdge(adjMatrix, 2, 3);
	addEdge(adjMatrix, 3, 0);

	printMatrix(adjMatrix);

	return 0;
}
