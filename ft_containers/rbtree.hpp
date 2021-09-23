#ifndef RBTREE
#define RBTREE

#include "nullptr.hpp"
#include <string>
#include <iostream>

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    bool color; //true = red false = black
};

class rbtree
{
public:
    typedef Node *NodePtr;

    void delete_(int data)
    {
        deleteNode(this->m_root, data);
    }

    void insert(int key)
    {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = m_NodeNULL;
        node->right = m_NodeNULL;
        node->color = true;

        NodePtr y = nullptr;
        NodePtr x = this->m_root;

        while (x != m_NodeNULL)
        {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        // y now parent of x
        node->parent = y;
        if (y == nullptr)
            m_root = node;
        else if (node->data < y->data)
            y->left = node;
        else
            y->right = node;

        if (node->parent == nullptr)
        {
            node->color = false;
            return ;
        }

        if (node->parent->parent == nullptr)
            return ;
        
        fixInsert(node);
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != m_NodeNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->m_root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }


    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != m_NodeNULL)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            m_root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != m_NodeNULL)
            node = node->right;
        return node;
    }

    NodePtr minimum(NodePtr node)
    {
        while (node->left != m_NodeNULL)
            node = node->left;
        return node;
    }

    rbtree( )
    {
        m_NodeNULL = new Node;
        m_NodeNULL->color = false;
        m_NodeNULL->left = nullptr;
        m_NodeNULL->right = nullptr;
        m_root = m_NodeNULL;
    }

    ~rbtree()
    {
        //delete m_NodeNULL;
    }

    void printHelper(NodePtr root, std::string indent, bool last) {
        // print the tree structure on the screen
        if (root != m_NodeNULL) {
           std::cout<<indent;
           if (last) {
              std::cout<<"R----";
              indent += "     ";
           } else {
              std::cout<<"L----";
              indent += "|    ";
           }
            
           std::string sColor = root->color?"RED":"BLACK";
           std::cout<<root->data<<"("<<sColor<<")"<<std::endl;
           printHelper(root->left, indent, false);
           printHelper(root->right, indent, true);
        }
        // cout<<root->left->data<<endl;
    }

    void prettyPrint() {
        if (m_root) {
            printHelper(this->m_root, "", true);
        }
    }

private:
    NodePtr m_root;
    NodePtr m_NodeNULL;

    void fixDelete(NodePtr x)
    {
        NodePtr s;
        while (x != m_root && x->color == false)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color)
                {
                    s->color = false;
                    x->parent->color = true;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == false && s->right->color == false)
                {
                    s->color = true;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == false)
                    {
                        s->left->color = false;
                        s->color = true;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->right->color = false;
                    leftRotate(x->parent);
                    x = m_root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color)
                {
                    s->color = false;
                    x->parent->color = true;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == false && s->left->color == false)
                {
                    s->color = true;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == false)
                    {
                        s->right->color = false;
                        s->color = true;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = false;
                    s->left->color = false;
                    rightRotate(x->parent);
                    x = m_root;
                }
            }
        }
        x->color = false;
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
            m_root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void deleteNode(NodePtr node, int key)
    {
        NodePtr z = m_NodeNULL;
        NodePtr x,y;
        while (node != m_NodeNULL)
        {
            if (node->data == key)
                z = node;
            if (node->data <= key)
                node = node->right;
            else
                node = node->left;
        }
        if (z == m_NodeNULL)
        {
            // no the same key
            return ;
        }
        y = z;
        bool y_orig_color = y->color;
        if (z->left == m_NodeNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == m_NodeNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_orig_color = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_orig_color == false)
            fixDelete(x);
    }

    void fixInsert(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == true)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color)
                {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;
                if (u->color)
                {
                    u->color = false;
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = false;
                    k->parent->parent->color = true;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == m_root)
                break ;
        }
        m_root->color = false;
    }

};


int main() {
    rbtree bst;
    bst.insert(8);
    bst.insert(18);
    bst.insert(5);
    bst.insert(15);
    bst.insert(17);
    bst.insert(25);
    bst.insert(40);
    bst.insert(80);
    //bst.delete_(25);
    bst.prettyPrint();
    return 0;
}



#endif /* RBTREE */
