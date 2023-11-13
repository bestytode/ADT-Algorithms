#include <iostream>

// Node color for rbtree, either red or black
enum NodeColor {
    RED,
    BLACK
};

template <typename T>
class RBTree;

// Node definition for rbtree, by default RED
template <typename T>
class Node 
{
public:
    T value;
    NodeColor color;
    Node* left, * right, * parent;

    Node(T value) : value(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

    // Helper function to determine if a node is on the left
    bool isOnLeft() { return this == parent->left; }

    // Returns the sibling of the current node
    Node* sibling() {
        // If no parent, no sibling
        if (parent == nullptr) return nullptr;

        if (isOnLeft())
            return parent->right;
        return parent->left;
    }

    // Moves node down and moves given node in its place
    void moveDown(Node* nParent) {
        if (parent != nullptr) {
            if (isOnLeft()) {
                parent->left = nParent;
            }
            else {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild() {
        return (left != nullptr && left->color == RED) || (right != nullptr && right->color == RED);
    }
};

// rbtree implementation
template <typename T>
class RBTree {
private:
    Node<T>* root;

protected:
    void rotateLeft(Node<T>*& ptr) {
        Node<T>* rightChild = ptr->right;
        ptr->right = rightChild->left;

        if (ptr->right != nullptr)
            ptr->right->parent = ptr;

        rightChild->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = rightChild;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = rightChild;
        else
            ptr->parent->right = rightChild;

        rightChild->left = ptr;
        ptr->parent = rightChild;
    }
    
    void rotateRight(Node<T>*& ptr) {
        Node<T>* leftChild = ptr->left;
        ptr->left = leftChild->right;

        if (ptr->left != nullptr)
            ptr->left->parent = ptr;

        leftChild->parent = ptr->parent;

        if (ptr->parent == nullptr)
            root = leftChild;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = leftChild;
        else

            ptr->parent->right = leftChild;

        leftChild->right = ptr;
        ptr->parent = leftChild;
    }

    // This function fixes violations caused by BST insertion
    void fixViolation(Node<T>*& ptr) {
        Node<T>* parent = nullptr;
        Node<T>* grandparent = nullptr;

        // if the color of ptr's parent is RED(the same as newly inserted one) the violation occurs
        while (ptr != root && ptr->color != BLACK && ptr->parent->color == RED) {
            parent = ptr->parent;
            grandparent = parent->parent;

            /* Case : A
                Parent of ptr is left child of Grand-parent of ptr */
            if (parent == grandparent->left) {
                Node<T>* uncle = grandparent->right;

                /* Case : 1
                   The uncle of ptr is also red
                   Only Recoloring required */
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    ptr = grandparent;
                }
                else {
                    /* Case : 2
                       ptr is right child of its parent
                       Left-rotation required */
                    if (ptr == parent->right) {
                        rotateLeft(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }

                    /* Case : 3
                       ptr is left child of its parent
                       Right-rotation required */
                    rotateRight(grandparent);
                    std::swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }

            /* Case : B
               Parent of ptr is right child of Grand-parent of ptr */
            else {
                Node<T>* uncle = grandparent->left;

                /* Case : 1
                   The uncle of ptr is also red
                   Only Recoloring required */
                if ((uncle != nullptr) && (uncle->color == RED)) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    ptr = grandparent;
                }
                else {
                    /* Case : 2
                       ptr is left child of its parent
                       Right-rotation required */
                    if (ptr == parent->left) {
                        rotateRight(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }

                    /* Case : 3
                       ptr is right child of its parent
                       Left-rotation required */
                    rotateLeft(grandparent);
                    std::swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
        }

        root->color = BLACK;
    }

public:
    RBTree() : root(nullptr) {}

    // BST insertion and then fix violation
    void insert(const T& n) {
        Node<T>* newNode = new Node<T>(n);

        if (root == nullptr) {
            newNode->color = BLACK; // ensure the root node is always BLACK
            root = newNode;
        }
        else {
            Node<T>* temp = root;

            while (temp != nullptr) {
                if (n < temp->value) {
                    if (temp->left == nullptr) {
                        temp->left = newNode;
                        newNode->parent = temp;
                        break;
                    }
                    else {
                        temp = temp->left;
                    }
                }
                else if (n > temp->value) {
                    if (temp->right == nullptr) {
                        temp->right = newNode;
                        newNode->parent = temp;
                        break;
                    }
                    else {
                        temp = temp->right;
                    }
                }
                else {
                    // Equal values are not allowed in BST
                    return;
                }
            }

            fixViolation(newNode);
        }
    }

    Node<T>* search(T n) {
        Node<T>* temp = root;
        while (temp != nullptr) {
            if (n < temp->value) {
                temp = temp->left;
            }
            else if (n > temp->value) {
                temp = temp->right;
            }
            else {
                return temp; // Found the value
            }
        }
        return nullptr; // Value not found
    }

    // Function to do inorder and level order traversals
    void inorder() { inorderHelper(root); }
    void inorderHelper(Node<T>* ptr) {
        if (ptr == nullptr)
            return;
        inorderHelper(ptr->left);
        std::cout << ptr->value << " ";
        inorderHelper(ptr->right);
    }
};