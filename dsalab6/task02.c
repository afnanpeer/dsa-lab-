#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node *insert(struct Node *root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        printf("Duplicate value %d is not allowed in BST.\n", key);
    }

    return root;
}

struct Node *search(struct Node *root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

struct Node *findMin(struct Node *root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct Node *findMax(struct Node *root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

struct Node *deleteNode(struct Node *root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *successor = findMin(root->right);
        root->key = successor->key;
        root->right = deleteNode(root->right, successor->key);
    }

    return root;
}

void inOrder(struct Node *root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->key);
    inOrder(root->right);
}

void preOrder(struct Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(struct Node *root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->key);
}

void freeTree(struct Node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

struct Node *buildRequiredTree(void) {
    int values[] = {50, 30, 20, 40, 70, 60, 80};
    int n = (int)(sizeof(values) / sizeof(values[0]));
    struct Node *root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    return root;
}

struct Node *runTestingScenario(struct Node *root) {
    freeTree(root);
    root = buildRequiredTree();

    printf("\nTesting Scenario (Required by Assignment)\n");
    printf("Initial In-Order: ");
    inOrder(root);
    printf("\n");

    printf("Delete leaf node 20 -> In-Order: ");
    root = deleteNode(root, 20);
    inOrder(root);
    printf("\n");

    printf("Delete node 30 (now one-child case) -> In-Order: ");
    root = deleteNode(root, 30);
    inOrder(root);
    printf("\n");

    printf("Delete root node 50 (two-children case) -> In-Order: ");
    root = deleteNode(root, 50);
    inOrder(root);
    printf("\n\n");

    return root;
}

void printMenu(void) {
    printf("===== BST Management System (Task 02) =====\n");
    printf("1. Insert\n");
    printf("2. Search\n");
    printf("3. Find Minimum\n");
    printf("4. Find Maximum\n");
    printf("5. Delete\n");
    printf("6. In-Order Traversal\n");
    printf("7. Pre-Order Traversal\n");
    printf("8. Post-Order Traversal\n");
    printf("9. Run Required Testing Scenario\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int main(void) {
    struct Node *root = NULL;
    int choice;
    int value;

    while (1) {
        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &value) == 1) {
                    root = insert(root, value);
                } else {
                    printf("Invalid value.\n");
                    return 1;
                }
                break;

            case 2: {
                printf("Enter value to search: ");
                if (scanf("%d", &value) == 1) {
                    struct Node *found = search(root, value);
                    if (found != NULL) {
                        printf("Value %d found in BST.\n", value);
                    } else {
                        printf("Value %d not found.\n", value);
                    }
                } else {
                    printf("Invalid value.\n");
                    return 1;
                }
                break;
            }

            case 3: {
                struct Node *minNode = findMin(root);
                if (minNode != NULL) {
                    printf("Minimum value: %d\n", minNode->key);
                } else {
                    printf("Tree is empty.\n");
                }
                break;
            }

            case 4: {
                struct Node *maxNode = findMax(root);
                if (maxNode != NULL) {
                    printf("Maximum value: %d\n", maxNode->key);
                } else {
                    printf("Tree is empty.\n");
                }
                break;
            }

            case 5:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) == 1) {
                    if (search(root, value) == NULL) {
                        printf("Value %d not found.\n", value);
                    } else {
                        root = deleteNode(root, value);
                        printf("Value %d deleted.\n", value);
                    }
                } else {
                    printf("Invalid value.\n");
                    return 1;
                }
                break;

            case 6:
                printf("In-Order: ");
                inOrder(root);
                printf("\n");
                break;

            case 7:
                printf("Pre-Order: ");
                preOrder(root);
                printf("\n");
                break;

            case 8:
                printf("Post-Order: ");
                postOrder(root);
                printf("\n");
                break;

            case 9:
                root = runTestingScenario(root);
                break;

            case 0:
                freeTree(root);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    }

    freeTree(root);
    return 0;
}