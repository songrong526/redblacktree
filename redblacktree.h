#ifndef STACK_AND_LIST_H
#define STACK_AND_LIST_H
#include <memory>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

struct Node {
    int data;
    bool color; // true for red, false for black
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    weak_ptr<Node> parent;

    Node(int data) : data(data), color(true), left(nullptr), right(nullptr) {}
};
class RedBlackTree {
public:
    friend class RBTreeVisualizer;
    RedBlackTree() : root(nullptr) {}
    explicit RedBlackTree(int key)
    {
        auto newNode = make_shared<Node>(key);
        newNode->color = false; // root is always black
        root = newNode;
    }
    shared_ptr<Node> getRoot() const { return root; }

    ~RedBlackTree() = default;

    void insert(int key)
    {
        auto pt = make_shared<Node>(key);
        if (!root)
        {
            pt->color = false;
            root = pt;
            return;
        }
        BSTInsert(root, pt);
        fixViolation(pt);
    }

    void showInfo()
    {
        cout << "红黑树信息\n";
        cout << "树高度: " << getHeight(root) << endl;
        cout << "节点总数: " << countNodes(root) << endl;
        cout << "红节点数: " << countRedNodes(root) << endl;
        cout << "黑节点数: " << countBlackNodes(root) << endl;
        if (root)
        {
            cout << "根节点: " << root->data << "("
                << (root->color ? "R" : "B") << ")\n";
        }

    }

    // 显示层序遍历
    void showLevelOrder() 
    {
        cout << "红黑树层序遍历\n";
        if (!root)
        {
            cout << "空树\n";
            return;
        }
        queue<shared_ptr<Node>> q;
        q.push(root);
        int level = 0;

        while (!q.empty())
        {
            int levelSize = q.size();
            cout << "Level " << level << ": ";
            for (int i = 0; i < levelSize; i++)
            {
                auto node = q.front();
                q.pop();
                cout << node->data << "(" << (node->color ? "R" : "B") << ") ";
                if (node->left)
                {
                    q.push(node->left);
                }
                if (node->right)
                {
                    q.push(node->right);
                }
            }
            cout << endl;
            level++;
        }
    }
    void showSimple() 
    {
        cout << "红黑树\n";
        if (!root) 
        {
            cout << "空树\n";
            return;
        }
        printSimpleTree(root, "", true);
    }

    shared_ptr<Node> search(int key) const 
    {
        return searchHelper(root, key);
    }
    void deleteNode(int key)
    {
		queue<shared_ptr<Node>> q;
		queue<shared_ptr<Node>> p;
        if(root->data!=key)
            p.push(root);
        q.push(root);
        int level = 0;

        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++)
            {
                auto node = q.front();
                q.pop();
                if (node->left)
                {
                    q.push(node->left);
					if (node->left->data != key)
                        p.push(node->left);
                }
                if (node->right)
                {
                    q.push(node->right);
                    if (node->right->data != key)
                        p.push(node->right);
                }
            }
        }
		root = nullptr;
        while(!p.empty())
        {
            auto node = p.front();
            p.pop();
            insert(node->data);
		}
    }
    void clear_tree()
    {
		root = nullptr;
	}

private:
    shared_ptr<Node> root;

    void printSimpleTree(const shared_ptr<Node>& node, const string& prefix, bool isLast) 
    {
        if (!node) return;

        cout << prefix;
        if (isLast) 
        {
            cout << "└── ";
        }
        else 
        {
            cout << "├── ";
        }

        cout << node->data << "(" << (node->color ? "R" : "B") << ")" << endl;

        // 获取子节点
        bool hasRight = (node->right != nullptr);
        bool hasLeft = (node->left != nullptr);

        string childPrefix = prefix + (isLast ? "    " : "│   ");

        if (hasRight) 
        {
            printSimpleTree(node->right, childPrefix, !hasLeft);
        }
        if (hasLeft) 
        {
            printSimpleTree(node->left, childPrefix, true);
        }
    }

    // 旋转和修复函数
    void rotateLeft(shared_ptr<Node>& pt) 
    {
        auto pt_y = pt->right;
        pt->right = pt_y->left;

        if (pt->right) 
        {
            pt->right->parent = pt;
        }

        pt_y->parent = pt->parent;

        auto parent_ptr = pt->parent.lock();
        if (!parent_ptr) 
        {
            root = pt_y;
        }
        else if (pt == parent_ptr->left) 
        {
            parent_ptr->left = pt_y;
        }
        else 
        {
            parent_ptr->right = pt_y;
        }

        pt_y->left = pt;
        pt->parent = pt_y;
    }

    void rotateRight(shared_ptr<Node>& pt) 
    {
        auto pt_y = pt->left;
        pt->left = pt_y->right;

        if (pt->left) 
        {
            pt->left->parent = pt;
        }

        pt_y->parent = pt->parent;

        auto parent_ptr = pt->parent.lock();
        if (!parent_ptr) 
        {
            root = pt_y;
        }
        else if (pt == parent_ptr->left) 
        {
            parent_ptr->left = pt_y;
        }
        else 
        {
            parent_ptr->right = pt_y;
        }

        pt_y->right = pt;
        pt->parent = pt_y;
    }

    void fixViolation(shared_ptr<Node>& pt) 
    {
        shared_ptr<Node> parent_ptr = nullptr;
        shared_ptr<Node> grandparent_ptr = nullptr;

        while (pt != root && pt->color && pt->parent.lock() && pt->parent.lock()->color) 
        {
            parent_ptr = pt->parent.lock();
            grandparent_ptr = parent_ptr->parent.lock();

            if (parent_ptr == grandparent_ptr->left) 
            {
                auto uncle = grandparent_ptr->right;

                if (uncle && uncle->color) 
                {
                    grandparent_ptr->color = true;
                    parent_ptr->color = false;
                    uncle->color = false;
                    pt = grandparent_ptr;
                }
                else 
                {
                    if (pt == parent_ptr->right) 
                    {
                        rotateLeft(parent_ptr);
                        pt = parent_ptr;
                        parent_ptr = pt->parent.lock();
                    }

                    rotateRight(grandparent_ptr);
                    swap(parent_ptr->color, grandparent_ptr->color);
                    pt = parent_ptr;
                }
            }
            else 
            {
                auto uncle = grandparent_ptr->left;

                if (uncle && uncle->color) 
                {
                    grandparent_ptr->color = true;
                    parent_ptr->color = false;
                    uncle->color = false;
                    pt = grandparent_ptr;
                }
                else 
                {
                    if (pt == parent_ptr->left) 
                    {
                        rotateRight(parent_ptr);
                        pt = parent_ptr;
                        parent_ptr = pt->parent.lock();
                    }

                    rotateLeft(grandparent_ptr);
                    swap(parent_ptr->color, grandparent_ptr->color);
                    pt = parent_ptr;
                }
            }
        }

        root->color = false;
    }

    void BSTInsert(shared_ptr<Node>& rootNode, shared_ptr<Node>& pt) 
    {
        if (!rootNode) 
        {
            rootNode = pt;
            return;
        }

        shared_ptr<Node> current = rootNode;
        shared_ptr<Node> parent = nullptr;

        while (current) 
        {
            parent = current;
            if (pt->data < current->data) 
            {
                current = current->left;
            }
            else if (pt->data > current->data) 
            {
                current = current->right;
            }
            else 
            {
                return; // 重复值不插入
            }
        }

        pt->parent = parent;
        if (pt->data < parent->data) 
        {
            parent->left = pt;
        }
        else 
        {
            parent->right = pt;
        }
    }

    // 辅助函数
    int getHeight(const shared_ptr<Node>& node) 
    {
        if (!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int countNodes(const shared_ptr<Node>& node) 
    {

        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countRedNodes(const shared_ptr<Node>& node) 
    {
        if (!node) return 0;
        int count = node->color ? 1 : 0;
        return count + countRedNodes(node->left) + countRedNodes(node->right);
    }

    int countBlackNodes(const shared_ptr<Node>& node) 
    {
        if (!node) return 0;
        int count = node->color ? 0 : 1;
        return count + countBlackNodes(node->left) + countBlackNodes(node->right);
    }

    shared_ptr<Node> searchHelper(const shared_ptr<Node>& node, int key) const 
    {
        if (!node) return nullptr;
        if (key == node->data) return node;
        if (key < node->data) return searchHelper(node->left, key);
        return searchHelper(node->right, key);
    }
};




#endif
