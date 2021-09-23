#ifndef RBTREE
#define RBTREE

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    bool color;
};

class rbtree
{
public:
    typedef Node *NodePtr;

    void rightRotate(NodePtr y)
    {
        NodePtr x = y->left;
        y->left = x->right;
        if (y->right != m_NodeNULL)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
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
        delete m_NodeNULL;
    }

private:
    NodePtr m_root;
    NodePtr m_NodeNULL;


};




#endif /* RBTREE */
