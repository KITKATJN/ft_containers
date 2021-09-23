#ifndef RBTREE
#define RBTREE

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

    void delete(int data)
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

    void deleteNode(NodePtr node, int key);

    void fixInsert(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == true)
        {
            if (k->parent->parent->right == k->parent)
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
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if ( k == m_root)
                break;
        }
        m_root->color = false;
    }

};




#endif /* RBTREE */
