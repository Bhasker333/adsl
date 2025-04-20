#include <iostream>
using namespace std;

struct AVLNode {
    int data;
    AVLNode *left;
    AVLNode *right;
    int height;
};

// Utility function to create a new node
AVLNode* createNode(int key) {
    AVLNode* newNode = new AVLNode;
    newNode->data = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int getHeight(AVLNode* root) {
    return root ? root->height : 0;
}

/*int getHeight(AVLNode* root) {
    if (root == nullptr) {
        return 0; // If the node is empty, height is 0
    } else {
        return root->height; // If the node exists, return its height
    }
}*/


int getBalanceFactor(AVLNode* root) {
    return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Right Rotation
AVLNode* rightRotation(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left Rotation
AVLNode* leftRotation(AVLNode* y) {
    AVLNode* x = y->right;
    AVLNode* t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Insert Operation
AVLNode* insert(AVLNode* node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;  // No duplicates allowed

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    // Balancing Cases
    if (bf > 1 && key < node->left->data)
        return rightRotation(node);

    if (bf < -1 && key > node->right->data)
        return leftRotation(node);

    if (bf > 1 && key > node->left->data) {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    if (bf < -1 && key < node->right->data) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}

// Delete Operation
AVLNode* Delete(AVLNode* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = Delete(root->left, key);
    else if (key > root->data)
        root->right = Delete(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            AVLNode* temp = root->right;
            while (temp->left)
                temp = temp->left;

            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    if (bf > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotation(root);

    if (bf < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotation(root);

    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

// Inorder Traversal (for leaderboard display)
void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Main Menu
int main() {
    AVLNode* root = NULL;
    int choice, val;

    do {
        cout << "\n----- Multiplayer Game Leaderboard -----\n";
        cout << "1. Player Registration\n2. Remove Player\n3. Display Leaderboard\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Player Score to Register: ";
                cin >> val;
                root = insert(root, val);
                break;

            case 2:
                cout << "Enter Player Score to Remove: ";
                cin >> val;
                root = Delete(root, val);
                break;

            case 3:
                cout << "Leaderboard (Inorder - Sorted by Score): ";
                inorder(root);
                cout << endl;
                break;

            case 4:
                cout << "Exiting game system.\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }

        cout << "Do you want to continue? (1 for Yes / 0 for No): ";
        cin >> choice;

    } while (choice == 1);

    return 0;
}
