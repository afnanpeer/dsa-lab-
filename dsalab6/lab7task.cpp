#include <iostream>
using namespace std;

const int MAXV = 100;

// Set all cells to 0 (no edges).
void initMatrix(int matrix[][MAXV], int vertices) {
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			matrix[i][j] = 0;
		}
	}
}

// Add an undirected edge between src and dest.
void addEdge(int matrix[][MAXV], int vertices, int src, int dest) {
	if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
		cout << "Invalid edge: vertex out of range." << '\n';
		return;
	}

	matrix[src][dest] = 1;
	matrix[dest][src] = 1;
}

// Print adjacency matrix row by row.
void printMatrix(int matrix[][MAXV], int vertices) {
	cout << "Adjacency Matrix:" << '\n';
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			cout << matrix[i][j] << ' ';
		}
		cout << '\n';
	}
}

// Count undirected edges from the upper triangle of the matrix.
int countEdges(int matrix[][MAXV], int vertices) {
	int edges = 0;
	for (int i = 0; i < vertices; i++) {
		for (int j = i + 1; j < vertices; j++) {
			if (matrix[i][j] == 1) {
				edges++;
			}
		}
	}
	return edges;
}

// Apply assignment edges that fit inside current vertex range.
void applyRequiredEdges(int matrix[][MAXV], int vertices) {
	const int requiredEdges[6][2] = {
		{0, 1}, {0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 5}
	};

	for (int i = 0; i < 6; i++) {
		int src = requiredEdges[i][0];
		int dest = requiredEdges[i][1];
		if (src < vertices && dest < vertices) {
			addEdge(matrix, vertices, src, dest);
		}
	}
}

// Depth-First Search using recursion.
void DFS(int matrix[][MAXV], int vertices, int startNode, int visited[]) {
	// Visit current node first.
	visited[startNode] = 1;
	cout << startNode << ' ';

	// Explore every unvisited neighbor.
	for (int i = 0; i < vertices; i++) {
		if (matrix[startNode][i] == 1 && !visited[i]) {
			DFS(matrix, vertices, i, visited);
		}
	}
}

// Breadth-First Search using a simple array-based queue.
void BFS(int matrix[][MAXV], int vertices, int startNode) {
	int visited[MAXV] = {0};
	int queue[MAXV];
	int front = 0;
	int rear = 0;

	// Start from given node.
	visited[startNode] = 1;
	queue[rear++] = startNode;

	// Process nodes level by level.
	while (front < rear) {
		int node = queue[front++];
		cout << node << ' ';

		// Enqueue all unvisited adjacent nodes.
		for (int i = 0; i < vertices; i++) {
			if (matrix[node][i] == 1 && !visited[i]) {
				visited[i] = 1;
				queue[rear++] = i;
			}
		}
	}
}

// A graph is connected if DFS from node 0 reaches every vertex.
bool isConnected(int matrix[][MAXV], int vertices) {
	if (vertices == 0) {
		return true;
	}

	int visited[MAXV] = {0};
	DFS(matrix, vertices, 0, visited);
	cout << '\n';

	for (int i = 0; i < vertices; i++) {
		if (!visited[i]) {
			return false;
		}
	}
	return true;
}

// Build and run the assignment's fixed test graph.
void runRequiredScenario() {
	int matrix[MAXV][MAXV];
	int vertices = 6;
	initMatrix(matrix, vertices);

	addEdge(matrix, vertices, 0, 1);
	addEdge(matrix, vertices, 0, 2);
	addEdge(matrix, vertices, 1, 3);
	addEdge(matrix, vertices, 2, 4);
	addEdge(matrix, vertices, 3, 5);
	addEdge(matrix, vertices, 4, 5);

	cout << "\nRequired Testing Scenario" << '\n';
	printMatrix(matrix, vertices);

	int visited[MAXV] = {0};
	cout << "DFS from node 0: ";
	DFS(matrix, vertices, 0, visited);
	cout << '\n';

	cout << "BFS from node 0: ";
	BFS(matrix, vertices, 0);
	cout << '\n';

	cout << "Comparison:" << '\n';
	cout << "DFS goes deep first along a branch before backtracking." << '\n';
	cout << "BFS visits neighbors level-by-level from the start node." << '\n';
}

// Build the required fixed graph directly (no manual edge input needed).
void buildDefaultGraph(int matrix[][MAXV], int &vertices, bool &initialized) {
	vertices = 6;
	initMatrix(matrix, vertices);
	applyRequiredEdges(matrix, vertices);

	initialized = true;
}

int main() {
	int matrix[MAXV][MAXV];
	int vertices = 0;
	bool initialized = false;

	// Auto-load assignment graph at startup.
	buildDefaultGraph(matrix, vertices, initialized);
	cout << "Default graph loaded with 6 vertices and required edges." << '\n';

	int choice;
	while (true) {
		// Menu-driven graph operations.
		cout << "\n===== LAB 7 TASK 02: BFS & DFS =====" << '\n';
		cout << "1. Set number of vertices (reset graph)" << '\n';
		cout << "2. Apply required edges automatically" << '\n';
		cout << "3. Print adjacency matrix" << '\n';
		cout << "4. Run DFS" << '\n';
		cout << "5. Run BFS" << '\n';
		cout << "6. Check if graph is connected" << '\n';
		cout << "7. Run required testing scenario" << '\n';
		cout << "0. Exit" << '\n';
		cout << "Enter choice: ";

		if (!(cin >> choice)) {
			cout << "Invalid input. Exiting." << '\n';
			return 1;
		}

		if (choice == 0) {
			cout << "Exiting..." << '\n';
			break;
		}

		if (choice == 1) {
			// User sets graph size once before custom operations.
			cout << "Enter number of vertices (1-" << MAXV << "): ";
			cin >> vertices;
			if (vertices < 1 || vertices > MAXV) {
				cout << "Invalid vertex count." << '\n';
				initialized = false;
				continue;
			}
			initMatrix(matrix, vertices);
			applyRequiredEdges(matrix, vertices);
			initialized = true;
			cout << "Graph initialized with " << vertices << " vertices." << '\n';
			cout << "Required edges were applied automatically where valid for this size." << '\n';
			continue;
		}

		if (choice == 7) {
			// Runs the exact testing scenario from the task statement.
			runRequiredScenario();
			continue;
		}

		if (!initialized) {
			cout << "Please set number of vertices first (option 1)." << '\n';
			continue;
		}

		if (choice == 2) {
			// Re-apply required edges to current graph.
			applyRequiredEdges(matrix, vertices);
			cout << "Required edges applied for current vertices." << '\n';
		} else if (choice == 3) {
			printMatrix(matrix, vertices);
			if (countEdges(matrix, vertices) == 0) {
				cout << "No valid required edges for this vertex count." << '\n';
			}
		} else if (choice == 4) {
			// DFS traversal from selected start node.
			int startNode;
			int visited[MAXV] = {0};
			cout << "Enter DFS start node: ";
			cin >> startNode;
			if (startNode < 0 || startNode >= vertices) {
				cout << "Invalid start node." << '\n';
				continue;
			}
			cout << "DFS traversal: ";
			DFS(matrix, vertices, startNode, visited);
			cout << '\n';
		} else if (choice == 5) {
			// BFS traversal from selected start node.
			int startNode;
			cout << "Enter BFS start node: ";
			cin >> startNode;
			if (startNode < 0 || startNode >= vertices) {
				cout << "Invalid start node." << '\n';
				continue;
			}
			cout << "BFS traversal: ";
			BFS(matrix, vertices, startNode);
			cout << '\n';
		} else if (choice == 6) {
			// Connectivity check via DFS from node 0.
			cout << "DFS visited sequence from node 0: ";
			if (isConnected(matrix, vertices)) {
				cout << "Graph is connected." << '\n';
			} else {
				cout << "Graph is disconnected." << '\n';
			}
		} else {
			cout << "Invalid choice." << '\n';
		}
	}

	return 0;
}
