#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

void Inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void levelOrderTraversal(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (temp == NULL) {
            cout << endl;
            if (!q.empty()) {
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left) {
                q.push(temp->left);
            }

            if (temp->right) {
                q.push(temp->right);
            }
        }
    }
}

Node* insertIntoBST(Node* &root, int d) {
    // base case
    if (root == NULL) {
        root = new Node(d);
        return root;
    }
    if (d > root->data) {
        // insert in right subtree
        root->right = insertIntoBST(root->right, d);
    } else {
        // insert in left subtree
        root->left = insertIntoBST(root->left, d);
    }
    return root;
}

Node* minVal(Node* root) {
    Node* temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

Node* deleteFromBST(Node* root, int value) {
    // base case
    if (root == NULL)
        return root;

    if (root->data == value) {
        // 0 child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        // 1 child (left child only)
        if (root->left != NULL && root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // 1 child (right child only)
        if (root->left == NULL && root->right != NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // 2 children
        if (root->left != NULL && root->right != NULL) {
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deleteFromBST(root->right, mini);
            return root;
        }
    } else if (root->data > value) {
        root->left = deleteFromBST(root->left, value);
        return root;
    } else {
        root->right = deleteFromBST(root->right, value);
        return root;
    }
    return root;
}

void takeInput(Node* &root) {
    int data;
    cin >> data;

    while (data != -1) {
        root = insertIntoBST(root, data);
        cin >> data;
    }
}

Node* searchBST(Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (root->data < key) {
        return searchBST(root->right, key);
    }
    return searchBST(root->left, key);
}

int main() {
    Node* root = NULL;

    cout << "Enter data to create BST" << endl;
    takeInput(root);

    cout << "printing the BST" << endl;
    levelOrderTraversal(root);

    // insertion
    int insertValue;
    cout << "Enter value to insert: ";
    cin >> insertValue;
    insertIntoBST(root, insertValue);

    cout << "printing the BST after insertion" << endl;
    levelOrderTraversal(root);

    // selection (searching)
    int searchValue;
    cout << "Enter value to search: ";
    cin >> searchValue;
    Node* searchResult = searchBST(root, searchValue);
    if (searchResult != NULL) {
        cout << "Value " << searchValue << " found in the BST." << endl;
    } else {
        cout << "Value " << searchValue << " not found in the BST." << endl;
    }

    // deletion
    int deleteValue;
    cout << "Enter value to delete: ";
    cin >> deleteValue;
    root = deleteFromBST(root, deleteValue);

    cout << "Printing Inorder" << endl;
    Inorder(root);

    cout << endl << "Printing preorder" << endl;
    preorder(root);

    cout << endl << "Printing postorder" << endl;
    postorder(root);

    return 0;
}
