//
// Created by Administrator on 05/12/2022.
//

#ifndef AVL_TREE_H_TESTNODE_H
#define AVL_TREE_H_TESTNODE_H

//------------------------TEST 3: COPYING FROM OLD AND REMOVING SHIT
template <class T>
class AVL_tree_copy {
public:
    class NodeCopy;


    explicit AVL_tree_copy(bool sort_by_score); // O(1)
    ~AVL_tree_copy(); // O(n[amount nodes])
    AVL_tree_copy(const AVL_tree_copy &) = delete; //cant copy trees
    AVL_tree_copy &operator=(AVL_tree_copy &other) = delete;

    AVL_tree_copy<T>::NodeCopy* add(T item);


private:
    const bool sort_by_score;
    AVL_tree_copy<T>::NodeCopy *root;
    int amount;
};


//--------------------------------NODE CLASS------------------------------------------//

//NodeCopys will be used in the AVL tree, and will allocate memory for an actual item.
template <class T>
class AVL_tree_copy<T>::NodeCopy{
public:
    AVL_tree_copy<T> *tree;
    AVL_tree_copy<T>::NodeCopy *parent;
    AVL_tree_copy<T>::NodeCopy *left;
    AVL_tree_copy<T>::NodeCopy *right;
    T content; //T is always a type of pointer.
    int balance_factor; //to manage the sorting of the AVL tree.
    int height;


    explicit NodeCopy(T);
    NodeCopy(const AVL_tree_copy &) = delete; //cant copy nodes. make new ones.
    NodeCopy &operator=(AVL_tree_copy &other) = delete;
    ~NodeCopy() = default;
};



//---------------------------PUBLIC FUNCTION DEFINITIONS------------------------------//

template<class T>
AVL_tree_copy<T>::AVL_tree_copy(bool sort_by_score) :
        sort_by_score(sort_by_score),
        root(nullptr),
        amount(0)
{

}

template<class T>
AVL_tree_copy<T>::~AVL_tree_copy() {
}


template<class T>
AVL_tree_copy<T>::NodeCopy::NodeCopy(T new_item)
        : tree(nullptr),
          parent(nullptr),
          left(nullptr),
          right(nullptr),
          content(nullptr),
          balance_factor(0),
          height(0)
{
    content = new_item;
}


template<class T>
typename AVL_tree_copy<T>::NodeCopy* AVL_tree_copy<T>::add(T item) {
    // returns a pointer to the node holding the pointer to the item. we need that
    // in order to store the list of nodes in the object, so we can delete all the nodes when
    //the object is deleted.
    //

    AVL_tree_copy<T>::NodeCopy attempt(item);
//TODO: debug segfault at this line.
    AVL_tree_copy<T>::NodeCopy* leaf(new NodeCopy(item));

    delete leaf;
    return leaf;
}







//------------------------TEST 2

//
//template <class T>
//class Tree {
//public:
//    class test_node2
//    {
//        public:
//        test_node2 *parent;
//        test_node2 *left;
//        test_node2 *right;
//        T content;
//        explicit test_node2(T item);
//    };
//
//
//    test_node2 root;
//    bool score;
//    explicit Tree(bool score);
//    Tree<T>::test_node2* add(T item);
//
//};
//
//template <class T>
//Tree<T>::Tree(bool score) : root(nullptr), score(score) {}
//
//template <class T>
//Tree<T>::test_node2::test_node2(T item)
//        : parent(nullptr),
//          left(nullptr),
//          right(nullptr),
//          content(item)
//{}
//
//template<class T>
//typename Tree<T>::test_node2 *Tree<T>::add(T item) {
////    Tree<T>::test_node2 attempt(item);
//    Tree<T>::test_node2* leaf(new test_node2(item));
//    delete leaf;
//}
//





//------------------TEST 1
//
//template <class T>
//class test_node {
//public:
//    test_node *parent;
//    test_node *left;
//    test_node *right;
//    T content;
//
//    test_node(T item);
//};
//
//template <class T>
//test_node<T>::test_node(T item)
//        : parent(nullptr),
//          left(nullptr),
//          right(nullptr),
//          content(item)
//{}

#endif //AVL_TREE_H_TESTNODE_H
