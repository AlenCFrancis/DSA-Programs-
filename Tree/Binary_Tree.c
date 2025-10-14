#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

// Queue structure for level order insertion & deletion
struct Queue {
    int front, rear;
    int size;
    struct Node **arr;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Create queue
struct Queue* createQueue(int size) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = -1;
    q->size = size;
    q->arr = (struct Node**)malloc(size * sizeof(struct Node*));
    return q;
}

// Queue helper functions
int isEmpty(struct Queue* q) { return q->front == -1; }
void enqueue(struct Queue* q, struct Node* node) {
    if (q->rear == q->size - 1) return;
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = node;
}
struct Node* dequeue(struct Queue* q) {
    if (isEmpty(q)) return NULL;
    struct Node* temp = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return temp;
}

// Insert a new node (level-wise)
void insert(struct Node **root, int data) {
    struct Node *newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    struct Queue* q = createQueue(100);
    enqueue(q, *root);

    while (!isEmpty(q)) {
        struct Node* temp = dequeue(q);

        if (!temp->left) {
            temp->left = newNode;
            break;
        } else enqueue(q, temp->left);

        if (!temp->right) {
            temp->right = newNode;
            break;
        } else enqueue(q, temp->right);
    }

    free(q->arr);
    free(q);
}

// Find and delete a node (by value)
void deleteNode(struct Node **root, int key) {
    if (*root == NULL) return;

    struct Queue* q = createQueue(100);
    enqueue(q, *root);

    struct Node *keyNode = NULL, *temp, *last;

    // Level order traversal to find keyNode and lastNode
    while (!isEmpty(q)) {
        temp = dequeue(q);
        if (temp->data == key) keyNode = temp;
        if (temp->left) enqueue(q, temp->left);
        if (temp->right) enqueue(q, temp->right);
        last = temp;
    }

    if (keyNode != NULL) {
        int x = last->data; // deepest node data
        // Delete the deepest node
        struct Queue* q2 = createQueue(100);
        enqueue(q2, *root);
        while (!isEmpty(q2)) {
            temp = dequeue(q2);
            if (temp->left) {
                if (temp->left == last) {
                    free(temp->left);
                    temp->left = NULL;
                    break;
                } else enqueue(q2, temp->left);
            }
            if (temp->right) {
                if (temp->right == last) {
                    free(temp->right);
                    temp->right = NULL;
                    break;
                } else enqueue(q2, temp->right);
            }
        }
        free(q2->arr);
        free(q2);

        keyNode->data = x;
    }

    free(q->arr);
    free(q);
}

// Traversals
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// Menu driven main function
int main() {
    struct Node* root = NULL;
    int choice, val;
    printf("\n\n--- Binary Tree Menu ---\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Inorder Traversal\n");
        printf("4. Preorder Traversal\n");
        printf("5. Postorder Traversal\n");
        printf("6. Exit\n");
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insert(&root, val);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                deleteNode(&root, val);
                break;
            case 3:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 5:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
