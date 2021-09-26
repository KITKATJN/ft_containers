#ifndef RBTREE
#define RBTREE

// #include "iterator.hpp"
// #include "enable_if.hpp"
// #include <string>
// #include <iostream>

namespace ft
{

template <typename T>
struct Node
{
    T    *data;
    Node *parent;
    Node *left;
    Node *right;
    bool color; //true = red false = black

    Node(T *data) {
        this->data = data;
        left = right = parent = NULL;
        this->color = true;
    }
};

// template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T>, typename NAlloc = std::allocator<Node<T> > >
// class rbtree
// {
// public:
//     typedef T                                                           value_type;
//     typedef Alloc                                                       allocator_type;
//     typedef NAlloc                                                      nalloc_type;
//     typedef const T                                                     &const_reference;
//     typedef T                                                           *pointer;
//     typedef const T                                                     *const_pointer;
//     typedef Compare                                                     compare_type;
//     typedef typename ft::bidirectional_iterator<T, T*, T&>              iterator;
//     typedef typename ft::bidirectional_iterator<T, const T*, const T&>  const_iterator;
//     typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
//     typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;
//     typedef	ptrdiff_t                                                   difference_type;
//     typedef size_t                                                      size_type;
//     typedef Node<value_type>                                            *NodePtr;

//     void delete_(int data)
//     {
//         deleteNode(this->m_root, data);
//     }

//     void insert(int key)
//     {
//         NodePtr node = new Node;
//         node->parent = NULL;
//         node->data = key;
//         node->left = m_end;
//         node->right = m_end;
//         node->color = true;

//         NodePtr y = NULL;
//         NodePtr x = this->m_root;

//         while (x != m_end)
//         {
//             y = x;
//             if (node->data < x->data)
//                 x = x->left;
//             else
//                 x = x->right;
//         }

//         // y now parent of x
//         node->parent = y;
//         if (y == NULL)
//             m_root = node;
//         else if (node->data < y->data)
//             y->left = node;
//         else
//             y->right = node;

//         if (node->parent == NULL)
//         {
//             node->color = false;
//             return ;
//         }

//         if (node->parent->parent == NULL)
//             return ;

//         fixInsert(node);
//     }

//     void rightRotate(NodePtr x) {
//         NodePtr y = x->left;
//         x->left = y->right;
//         if (y->right != m_end) {
//             y->right->parent = x;
//         }
//         y->parent = x->parent;
//         if (x->parent == NULL) {
//             this->m_root = y;
//         } else if (x == x->parent->right) {
//             x->parent->right = y;
//         } else {
//             x->parent->left = y;
//         }
//         y->right = x;
//         x->parent = y;
//     }


//     void leftRotate(NodePtr x)
//     {
//         NodePtr y = x->right;
//         x->right = y->left;
//         if (y->left != m_end)
//             y->left->parent = x;
//         y->parent = x->parent;
//         if (x->parent == NULL)
//             m_root = y;
//         else if (x == x->parent->left)
//             x->parent->left = y;
//         else
//             x->parent->right = y;
//         y->left = x;
//         x->parent = y;
//     }

//     NodePtr maximum(NodePtr node)
//     {
//         while (node->right != m_end)
//             node = node->right;
//         return node;
//     }

//     NodePtr minimum(NodePtr node)
//     {
//         while (node->left != m_end)
//             node = node->left;
//         return node;
//     }

//     rbtree( )
//     {
//         m_end = new Node;
//         m_end->color = false;
//         m_end->left = NULL;
//         m_end->right = NULL;
//         m_root = m_end;
//     }

//     ~rbtree()
//     {
//         //delete m_end;
//     }

//     void printHelper(NodePtr root, std::string indent, bool last) {
//         // print the tree structure on the screen
//         if (root != m_end) {
//            std::cout<<indent;
//            if (last) {
//               std::cout<<"R----";
//               indent += "     ";
//            } else {
//               std::cout<<"L----";
//               indent += "|    ";
//            }

//            std::string sColor = root->color?"RED":"BLACK";
//            std::cout<<root->data<<"("<<sColor<<")"<<std::endl;
//            printHelper(root->left, indent, false);
//            printHelper(root->right, indent, true);
//         }
//         // cout<<root->left->data<<endl;
//     }

//     void prettyPrint() {
//         if (m_root) {
//             printHelper(this->m_root, "", true);
//         }
//     }

// private:
//     NodePtr             m_root;
//     NodePtr             m_end;
//     compare_type        m_compare;
//     allocator_type      m_allocator;
//     nalloc_type         m_nodeAllocator;
//     size_type           m_size;

//     void fixDelete(NodePtr x)
//     {
//         NodePtr s;
//         while (x != m_root && x->color == false)
//         {
//             if (x == x->parent->left)
//             {
//                 s = x->parent->right;
//                 if (s->color)
//                 {
//                     s->color = false;
//                     x->parent->color = true;
//                     leftRotate(x->parent);
//                     s = x->parent->right;
//                 }
//                 if (s->left->color == false && s->right->color == false)
//                 {
//                     s->color = true;
//                     x = x->parent;
//                 }
//                 else
//                 {
//                     if (s->right->color == false)
//                     {
//                         s->left->color = false;
//                         s->color = true;
//                         rightRotate(s);
//                         s = x->parent->right;
//                     }
//                     s->color = x->parent->color;
//                     x->parent->color = false;
//                     s->right->color = false;
//                     leftRotate(x->parent);
//                     x = m_root;
//                 }
//             }
//             else
//             {
//                 s = x->parent->left;
//                 if (s->color)
//                 {
//                     s->color = false;
//                     x->parent->color = true;
//                     rightRotate(x->parent);
//                     s = x->parent->left;
//                 }
//                 if (s->right->color == false && s->left->color == false)
//                 {
//                     s->color = true;
//                     x = x->parent;
//                 }
//                 else
//                 {
//                     if (s->left->color == false)
//                     {
//                         s->right->color = false;
//                         s->color = true;
//                         leftRotate(s);
//                         s = x->parent->left;
//                     }
//                     s->color = x->parent->color;
//                     x->parent->color = false;
//                     s->left->color = false;
//                     rightRotate(x->parent);
//                     x = m_root;
//                 }
//             }
//         }
//         x->color = false;
//     }

//     void rbTransplant(NodePtr u, NodePtr v)
//     {
//         if (u->parent == NULL)
//             m_root = v;
//         else if (u == u->parent->left)
//             u->parent->left = v;
//         else
//             u->parent->right = v;
//         v->parent = u->parent;
//     }

//     void deleteNode(NodePtr node, int key)
//     {
//         NodePtr z = m_end;
//         NodePtr x,y;
//         while (node != m_end)
//         {
//             if (node->data == key)
//                 z = node;
//             if (node->data <= key)
//                 node = node->right;
//             else
//                 node = node->left;
//         }
//         if (z == m_end)
//         {
//             // no the same key
//             return ;
//         }
//         y = z;
//         bool y_orig_color = y->color;
//         if (z->left == m_end)
//         {
//             x = z->right;
//             rbTransplant(z, z->right);
//         }
//         else if (z->right == m_end)
//         {
//             x = z->left;
//             rbTransplant(z, z->left);
//         }
//         else
//         {
//             y = minimum(z->right);
//             y_orig_color = y->color;
//             x = y->right;
//             if (y->parent == z)
//                 x->parent = y;
//             else
//             {
//                 rbTransplant(y, y->right);
//                 y->right = z->right;
//                 y->right->parent = y;
//             }
//             rbTransplant(z, y);
//             y->left = z->left;
//             y->left->parent = y;
//             y->color = z->color;
//         }
//         delete z;
//         if (y_orig_color == false)
//             fixDelete(x);
//     }

//     void fixInsert(NodePtr k)
//     {
//         NodePtr u;
//         while (k->parent->color == true)
//         {
//             if (k->parent == k->parent->parent->right)
//             {
//                 u = k->parent->parent->left;
//                 if (u->color)
//                 {
//                     u->color = false;
//                     k->parent->color = false;
//                     k->parent->parent->color = true;
//                     k = k->parent->parent;
//                 }
//                 else
//                 {
//                     if (k == k->parent->left)
//                     {
//                         k = k->parent;
//                         rightRotate(k);
//                     }
//                     k->parent->color = false;
//                     k->parent->parent->color = true;
//                     leftRotate(k->parent->parent);
//                 }
//             }
//             else
//             {
//                 u = k->parent->parent->right;
//                 if (u->color)
//                 {
//                     u->color = false;
//                     k->parent->color = false;
//                     k->parent->parent->color = true;
//                     k = k->parent->parent;
//                 }
//                 else
//                 {
//                     if (k == k->parent->right)
//                     {
//                         k = k->parent;
//                         leftRotate(k);
//                     }
//                     k->parent->color = false;
//                     k->parent->parent->color = true;
//                     rightRotate(k->parent->parent);
//                 }
//             }
//             if (k == m_root)
//                 break ;
//         }
//         m_root->color = false;
//     }

// };


// int main() {
//     rbtree<int, int> bst;
//     bst.insert(8);
//     bst.insert(18);
//     bst.insert(5);
//     bst.insert(15);
//     bst.insert(17);
//     bst.insert(25);
//     bst.insert(40);
//     bst.insert(80);
//     //bst.delete_(25);
//     bst.prettyPrint();
//     return 0;
// }
}

 #endif /* RBTREE */
