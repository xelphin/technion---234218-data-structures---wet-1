/*
 * template for an AVL_tree, that will use AVL_Nodes.
 * the Nodes receive the item, and a comparison function,
 * since we use the item in different contexts.
 *
 * in our code, AVL trees appear at:
 * all teams AVL.
 * valid teams AVL.
 * all players AVL.
 * players AVL (for every team).
 *
 */

#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_AVL_TREE_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_AVL_TREE_H
#define SORT_BY_SCORE true
#define SORT_BY_ID false


template <class T>
class AVL_tree {
public:
    explicit AVL_tree(bool sort_by_score);
    bool sort_by_score;

private:
    class Node;

};

template<class T>
AVL_tree<T>::AVL_tree(bool sort_by_score) {

}

//Nodes will be used in the AVL tree, and will allocate memory for an actual item
template <class T>
class AVL_tree<T>::Node{
public:
    AVL_tree *tree;
    Node *parent;
    Node *left;
    Node *right;
    T *content; //may be changed to shared pointer later
    int balance_factor; //to manage the sorting of the AVL tree.
    
    bool operator==(const Node &other);
private:
    int get_comparison(const Node &other);
};

template <class T>
int AVL_tree<T>::Node::get_comparison(const Node &other) {
    // since its unknown if the tree is sorted by id or by score, we need this function to work on both.
    // '!' operator is for score. '~' operator is for id.
    if (tree->sort_by_score == SORT_BY_SCORE){
        return !(this->content) - !(other.content);
    }
    else
    {
        return ~this->content - ~other.content;
    }
}

template<class T>
bool AVL_tree<T>::Node::operator==(const AVL_tree<T>::Node &other) {
    return get_comparison(other) == 0; //their comparators are equal
}


#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_AVL_TREE_H
