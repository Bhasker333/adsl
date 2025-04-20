#include<iostream>
using namespace std;

// Define structure for a BST node
struct Tree {
    int data;
    Tree* left;
    Tree* right;

    Tree(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insert node into BST
Tree* insert(Tree* node, int data) {
    if (node == NULL)
        return new Tree(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

// Inorder traversal
void inorder(Tree* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(Tree* root) {
    if (root != NULL) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(Tree* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

// Search a node
Tree* search(Tree* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Delete a node
Tree* Delete(Tree* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->data) {
        root->left = Delete(root->left, key);
    } else if (key > root->data) {
        root->right = Delete(root->right, key);
    } else {
        // Node found
        if (root->left == NULL) {
            Tree* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Tree* temp = root->left;
            delete root;
            return temp;
        }

        // Two children case: Find inorder successor
        Tree* succ = root->right;
        while (succ->left != NULL)
            succ = succ->left;
        root->data = succ->data;
        root->right = Delete(root->right, succ->data);
    }

    return root;
}

// Mirror the tree
void mirror(Tree* root) {
    if (root == NULL)
        return;

    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

// Copy and display (inorder)
void copy(Tree* root) {
    if (root == NULL) {
        cout << "Empty tree can't be copied.\n";
        return;
    }

    Tree* newRoot = new Tree(root->data);
    newRoot->left = root->left;
    newRoot->right = root->right;

    cout << "Copied tree (inorder): ";
    inorder(newRoot);
    cout << endl;
}

// Display level-wise (manual approach)
void display_level(Tree* root) {
    if (root == NULL)
        return;

    cout << root->data << " ";
    if (root->left != NULL)
        cout << root->left->data << " ";
    if (root->right != NULL)
        cout << root->right->data << " ";

    if (root->left != NULL) {
        display_level(root->left->left);
        display_level(root->left->right);
    }

    if (root->right != NULL) {
        display_level(root->right->left);
        display_level(root->right->right);
    }
}

int main() {
    Tree* root = NULL;
    int choice;

    do {
        cout << "\n--- Binary Search Tree Menu ---\n";
        cout << "1. INSERT\n2. INORDER DISPLAY\n3. PREORDER DISPLAY\n4. POSTORDER DISPLAY\n";
        cout << "5. SEARCH\n6. DELETE\n7. LEVEL-WISE DISPLAY\n8. COPY TREE\n9. MIRROR TREE\n10. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Inserting into Tree...\n";
                root = insert(root, 100);
                root = insert(root, 50);
                root = insert(root, 150);
                root = insert(root, 70);
                root = insert(root, 20);
                root = insert(root, 120);
                root = insert(root, 180);
                root = insert(root, 10);
                break;
            }
            case 2:
                cout << "Inorder traversal: ";
                inorder(root);
                cout << endl;
                break;

            case 3:
                cout << "Preorder traversal: ";
                preorder(root);
                cout << endl;
                break;

            case 4:
                cout << "Postorder traversal: ";
                postorder(root);
                cout << endl;
                break;

            case 5: {
                int key;
                cout << "Enter value to search: ";
                cin >> key;
                Tree* found = search(root, key);
                cout << (found ? "Node found.\n" : "Node not found.\n");
                break;
            }

            case 6: {
                int key;
                cout << "Enter value to delete: ";
                cin >> key;
                root = Delete(root, key);
                cout << "Tree after deletion (inorder): ";
                inorder(root);
                cout << endl;
                break;
            }

            case 7:
                cout << "Level-wise display: ";
                display_level(root);
                cout << endl;
                break;

            case 8:
                cout << "Copying the tree...\n";
                copy(root);
                break;

            case 9:
                cout << "Mirror of the tree (inorder): ";
                mirror(root);
                inorder(root);
                cout << endl;
                break;

            case 10:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

        cout << "Do you want to continue (1 for Yes, any other for No): ";
        cin >> choice;

    } while (choice == 1);

    return 0;
}
