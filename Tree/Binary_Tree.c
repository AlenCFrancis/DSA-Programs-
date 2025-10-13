
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* newNode(int val) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->data = val;
    n->left = n->right = NULL;
    return n;
}

// Insert a new node (level order)
struct node* insert(struct node* root, int val) {
    if (!root)
        return newNode(val);

    struct node *queue[100], *temp;
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        if (!temp->left) {
            temp->left = newNode(val);
            return root;
        } else {
            queue[rear++] = temp->left;
        }

        if (!temp->right) {
            temp->right = newNode(val);
            return root;
        } else {
            queue[rear++] = temp->right;
        }
    }
    return root;
}

// Delete deepest node
void deleteDeepest(struct node* root, struct node* del) {
    struct node *queue[100], *temp;
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        if (temp->left) {
            if (temp->left == del) {
                temp->left = NULL;
                free(del);
                return;
            } else {
                queue[rear++] = temp->left;
            }
        }

        if (temp->right) {
            if (temp->right == del) {
                temp->right = NULL;
                free(del);
                return;
            } else {
                queue[rear++] = temp->right;
            }
        }
    }
}

// Delete a node by value
struct node* deleteNode(struct node* root, int val) {
    if (!root)
        return NULL;

    struct node *queue[100], *temp, *keyNode = NULL;
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        temp = queue[front++];

        if (temp->data == val)
            keyNode = temp;

        if (temp->left)
            queue[rear++] = temp->left;

        if (temp->right)
            queue[rear++] = temp->right;
    }

    if (keyNode) {
        int x = temp->data;
        deleteDeepest(root, temp);
        keyNode->data = x;
    }
    return root;
}

// Tree traversals
void inorder(struct node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct node* root = NULL;
    int choice, val;
    printf("\n1. Insert\n2. Delete\n3. Inorder\n4. Preorder\n5. Postorder\n6. Exit\n");
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
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
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    } while (1);
}
