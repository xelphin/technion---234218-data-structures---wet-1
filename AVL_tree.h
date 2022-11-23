/*
 * template for an AVL_tree, that will use Nodes.
 * the Nodes ALWAYS hold a ---POINTER--- to the item. it may be a unique_ptr or a shared_ptr or a regular one,
 * but it's always a pointer.
 * comparison should be between nodes, not content, since the nodes know which comparison function to call.
 *
 * in our code, AVL trees appear at:
 * all teams AVL.
 * valid teams AVL.
 * all players_id AVL.
 * all players_score AVL.
 * players AVL (for every team).
 *
 */

#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_AVL_TREE_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_AVL_TREE_H

#include "stdexcept"
#include "iostream"

#define SORT_BY_SCORE true
#define SORT_BY_ID false
#define UNBALANCED 2
#define SCORE !
#define ID ~


//-------------------------------AVL TREE CLASS---------------------------------------//

template <class T>
class AVL_tree {
    class Node;

public:
    explicit AVL_tree(bool sort_by_score);
    ~AVL_tree();
    AVL_tree(const AVL_tree &) = delete; //cant copy trees
    AVL_tree &operator=(AVL_tree &other) = delete;

    Node* add(T item);
    bool remove(int id);
    Node* find(int id);
    void merge(AVL_tree<T> &other); //merge 2 trees together

    void debugging_printTree(); // debugging -- erase later

private:
    const bool sort_by_score;
    Node *root;

    Node* find_designated_parent(Node* new_leaf);
    void climb_up_and_rebalance_tree(Node* leaf);
    void post_order_delete();

    void debugging_printTree(const std::string& prefix, const AVL_tree::Node* node, bool isLeft);
    void debugging_printTree(const AVL_tree::Node* node);
    
};


//--------------------------------NODE CLASS------------------------------------------//

//Nodes will be used in the AVL tree, and will allocate memory for an actual item.
template <class T>
class AVL_tree<T>::Node{
public:
    AVL_tree *tree;
    Node *parent;
    Node *left;
    Node *right;
    T content; //T is always a type of pointer.
    int balance_factor; //to manage the sorting of the AVL tree.
    int height;

    explicit Node(T);

    int get_comparison(const Node &other); 

    //tree sorting functions:
    int set_balance_factor();
    int set_height();
    int get_height(Node* node);
    void choose_roll();

private:
    void update_parent(Node* replacement);
    void roll_right();
    void roll_left();
    void LL_roll();
    void LR_roll();
    void RR_roll();
    void RL_roll();
};



//---------------------------PUBLIC FUNCTION DEFINITIONS------------------------------//

template<class T>
AVL_tree<T>::AVL_tree(bool sort_by_score) : sort_by_score(sort_by_score), root(nullptr){
}

template<class T>
AVL_tree<T>::~AVL_tree() {
    post_order_delete();
}


template<class T>
AVL_tree<T>::Node::Node(T new_item) 
: tree(nullptr), parent(nullptr), left(nullptr), right(nullptr),content(new_item), balance_factor(0), height(0)
{ 
    // may be changed once we move to pointers.
}


template<class T>
typename AVL_tree<T>::Node* AVL_tree<T>::add(T item) {
    // returns a pointer to the node holding the pointer to the item. we need that
    // in order to store the list of nodes in the object, so we can delete all the nodes when
    //the object is deleted.
    //

    Node *leaf = new Node(item); //in case of bad_alloc, memory is freed from the tree destructor.
    leaf->tree = this;

    std::cout << "Entering: " << ((*(*leaf).content)).get_id() << std::endl;

    try {
        Node *parent = find_designated_parent(leaf);
        if (parent == nullptr) {
            root = leaf;
            leaf->tree = this;
            return leaf;
        } 
        std::cout << "Parent id: " << ((*(*parent).content)).get_id() << std::endl;
        if ((*leaf).get_comparison(*parent) > 0) {
            parent->right = leaf;
        } else {
            parent->left = leaf;
        }
        leaf->parent = parent;
        leaf->tree=this;
        climb_up_and_rebalance_tree(leaf);
    }
    catch (...){
        delete leaf;
        throw;
    }
    return leaf;

}



template<class T>
bool AVL_tree<T>::remove(int id) {
    return false;
}


template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find(int id) {
    return nullptr;
}


template<class T>
void AVL_tree<T>::merge(AVL_tree<T> &other) {

}



//-----------------------------PRIVATE TREE FUNCTIONS-----------------------------//

template<class T>
void AVL_tree<T>::post_order_delete() {
    // called in tree destructor so may be called during an exception.
    if (root == nullptr){
        return;
    }
    Node* current = root;
    Node* temp = root;
    // while not in root or root has children:
    while (current->parent || (current == root && (root->left || root->right))){
        if (current->left != nullptr)
            current = current->left;
        else if (current->right){
            current = current->right;
        }
        else{ //its a leaf
            if (current->parent->left == current){ //if leaf is a left child
                current->parent->left = nullptr;
            } else{
                current->parent->right = nullptr;
            }
            temp = current->parent;
            delete current;
            current = temp;
        }
    }

    //finished deleting the tree. the root has no children.
    delete root;
    root = nullptr;
}


template<class T>
typename AVL_tree<T>::Node* AVL_tree<T>::find_designated_parent(AVL_tree::Node* new_leaf) {
    Node* current = root;
    if (!current){
        return nullptr;
    }
    
    while(true){ //while true loop ok because in every case we either return or go down tree.

        if ((*new_leaf).get_comparison(*current)>0)  { //proceed to left branch.
            std::cout << "id: " << std::to_string((*(*new_leaf).content).get_id())
            << " is bigger than: " << std::to_string((*(*current).content).get_id()) << std::endl;
            if ((*current).right != nullptr){
                std::cout << "check right" << std::endl;
                current = (*current).right;
            }
            else{ //no right child
                std::cout << std::to_string((*(*current).content).get_id()) <<  " has no right child so: " << std::endl;
                return current;
            }
        }
        else{ //proceed to right branch
            std::cout << "id: " << std::to_string((*(*new_leaf).content).get_id())
            << " is smaller than: " << std::to_string((*(*current).content).get_id()) << std::endl;
            if ((*current).left != nullptr){
                std::cout << "check left" << std::endl;
                current = (*current).left;
            }
            else{
                std::cout << std::to_string((*(*current).content).get_id()) << " has no left child so: " << std::endl;
                return current;
            }
        }
    }
    
}


template <class T>
int AVL_tree<T>::Node::get_comparison(const Node &other) {
    // since its unknown if the tree is sorted by id or by score, we need this function to work on both.
    // '!' operator is for score. '~' operator is for id.
    // the comparison is done between the dereferences of the pointers the nodes holds.
    
    if (tree == nullptr ) {
        std::cout << "tree is a nullptr!" << std::endl;
        return 0;
    }
    if (tree->sort_by_score == SORT_BY_SCORE){
        int score = SCORE(*(this->content)) - SCORE(*other.content);
        if (score != 0)
            return score;
        else
            return ID(*(this->content)) - ID(*other.content);
    }
    else
    {
        return ID(*(this->content)) - ID(*other.content);
    }
    
   return 0;
}


//----------------------------TREE SORTING FUNCTIONS------------------------------//


template<class T>
int AVL_tree<T>::Node::set_height() {
    int left_height = get_height(left);
    int right_height = get_height(right);
    height = left_height > right_height ? left_height + 1 : right_height + 1; //max
    return height;
}

template<class T>
int AVL_tree<T>::Node::get_height(AVL_tree<T>::Node *node) {
    if (node == nullptr){
        return -1; //leaf child is 0, non-existent child is -1
    }
    else{
        return node->height;
    }
}

template<class T>
int AVL_tree<T>::Node::set_balance_factor() {
    int height_difference = get_height(left) - get_height(right);
    balance_factor = height_difference;
    return height_difference;
}

template<class T>
void AVL_tree<T>::climb_up_and_rebalance_tree(AVL_tree::Node *leaf) {
    Node* current = leaf; //not node.parent, so it also updates the height of the node to 0 if its a leaf.
    
    while (current){ //climbs up tree. stops after iterating on root.
        current->set_height();
        current->set_balance_factor();
        std::cout << "Currently on: " << ((*(*current).content)).get_id()
        << " -> balance factor " << std::to_string((*current).balance_factor) 
        << ", height " << std::to_string((*current).height)<< std::endl;
        if (abs((*current).balance_factor) == UNBALANCED){
            current->choose_roll(); //because roll switches parent and child, we will still get to the new parent.
        }
        current->set_height();
        current = (*current).parent;
    }
    
}

template<class T>
void AVL_tree<T>::Node::update_parent(Node* replacement) {
    //updates the parent after a roll to point to the replacement of the old child.
    if (parent) {
        if (parent->left == this) {
            parent->left = replacement;
        }
        else if (parent->right == this){
            parent->right = replacement;
        }
    } else { // no parent implies this is the root
        tree->root = replacement;
    }
    replacement->parent = parent;
    parent = replacement;
}

template<class T>
void AVL_tree<T>::Node::choose_roll() {
    //if this function is called, it means the BF of this node is ±2, and it should roll.
    //the numbers are according to the chart in the slides.
    std::cout << "the tree is unbalanced -> do roll" << std::endl;
    
    if (balance_factor == 2){
        if (left->balance_factor >= 0){
            std::cout << "roll: LL" << std::endl;
            this->LL_roll();
        }
        else if (left->balance_factor == -1){
            std::cout << "roll: LR" << std::endl;
            this->LR_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else if (balance_factor == -2){
        if (right->balance_factor <= 0){
            std::cout << "roll: RR" << std::endl;
            this->RR_roll();
        }
        else if (right->balance_factor == 1){
            std::cout << "roll: RL" << std::endl;
            this->RL_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else throw std::invalid_argument("bad balance factor");
    
}

template<class T>
void AVL_tree<T>::Node::roll_left() {
    Node* original_right = right;
    right->left->parent = this;
    right = right->left;
    original_right->left = this;
    update_parent(original_right);
    set_balance_factor();
}

template<class T>
void AVL_tree<T>::Node::roll_right() {
    Node* original_left = left;
    left->right->parent = this;
    left = left->right;
    original_left->right = this;
    update_parent(original_left);
    set_balance_factor();
}

template<class T>
void AVL_tree<T>::Node::LL_roll() {
    this->roll_right();
}

template<class T>
void AVL_tree<T>::Node::LR_roll() {
    left->roll_left();
    roll_right();
}

template<class T>
void AVL_tree<T>::Node::RR_roll() {
    this->roll_left();
}

template<class T>
void AVL_tree<T>::Node::RL_roll() {
    right->roll_right();
    roll_left();
}



// ONLY FOR DEBUGGING - ERASE LATER
template<class T>
void AVL_tree<T>::debugging_printTree(const std::string& prefix, const AVL_tree::Node* node, bool isLeft) 
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << (*(node->content)).get_id() << std::endl;

        // enter the next tree level - left and right branch
        AVL_tree<T>::debugging_printTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
        AVL_tree<T>::debugging_printTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template<class T>
void AVL_tree<T>::debugging_printTree(const AVL_tree::Node* node)
{
    debugging_printTree("", node, false);
}

template<class T>
void AVL_tree<T>::debugging_printTree()
{
    debugging_printTree(root);
}
// ----------------------------------



#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_AVL_TREE_H