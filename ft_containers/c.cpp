#include "rbtree.hpp"

int main() {
    ft::rbtree<int, ft::less<int> > bst;
    //bst.insert(ft::pair<int,int>(1, 5));
    bst.insert(1);
    bst.insert(5);
    bst.insert(15);
    bst.insert(17);
    bst.insert(25);
    //std::cout << "111111111111\n";
    bst.erase(bst.begin());
    //std::cout << "1111111111112\n";
    bst.insert(40);
    std::cout << bst.erase(40) << std::endl;
    bst.insert(80);
    // //bst.delete_(25);
    bst.prettyPrint();
    return 0;
}
