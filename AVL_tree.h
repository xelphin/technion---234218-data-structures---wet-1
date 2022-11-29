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
#include "Exception.h"

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
    explicit AVL_tree(bool sort_by_score); // O(1)
    explicit AVL_tree(AVL_tree<T>& tree1, AVL_tree<T>& tree2, bool sort_by_score);
    ~AVL_tree(); // O(n[amount nodes])
    AVL_tree(const AVL_tree &) = delete; //cant copy trees
    AVL_tree &operator=(AVL_tree &other) = delete;

    Node* add(T item);
    bool remove(int id);

    Node* find_id(int id);

    T get_content(int id);


    void merge(AVL_tree<T> &other); //merge 2 trees together
    int get_amount();
    Node* make_AVL_tree_from_array(T arr[], int start, int end);

    void in_order_traversal_wrapper(T arr[], int size); // used to iterate on all the nodes. im not sure if it should be private or public.
    static void merge_sort(T newArr[], T arr1[], int size1, T arr2[], int size2, bool sort_by_score);
    static void fill_array(T newArr[], T oldArr[], int size, int& indexNew, int& indexOld);

    // TESTS AND DEBUGGING FUNCTIONS
    std::string debugging_printTree();
    static void print_node(Node* node);
    void find_test_wrapper(int id);

private:
    const bool sort_by_score;
    Node *root;
    int amount;

    Node* find_designated_parent(Node* new_leaf);
    void climb_up_and_rebalance_tree(Node* leaf);
    void post_order_delete();
    void in_order_traversal(Node* node, T arr[], int size, int& currIndex);
    Node* find_next_in_order(Node* node);
    void replace_nodes(Node* node, Node* replacement);

    void debugging_printTree(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str);
    void debugging_printTree(const AVL_tree::Node* node, std::string& str);
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
    Node(const AVL_tree &) = delete; //cant copy nodes. make new ones.
    Node &operator=(AVL_tree &other) = delete;

    int get_comparison(const Node &other); 

    //tree sorting functions:
    int set_balance_factor();
    int set_height();
    int get_height(Node* node);
    void choose_roll();

    void update_parent(Node* replacement);

private:
    void roll_right();
    void roll_left();
    void LL_roll();
    void LR_roll();
    void RR_roll();
    void RL_roll();
};



//---------------------------PUBLIC FUNCTION DEFINITIONS------------------------------//

template<class T>
AVL_tree<T>::AVL_tree(bool sort_by_score) : sort_by_score(sort_by_score), root(nullptr), amount(0){
}

template<class T>
AVL_tree<T>::AVL_tree(AVL_tree<T>& tree1, AVL_tree<T>& tree2, bool sort_by_score)
    : sort_by_score(sort_by_score), root(nullptr), amount(0)
{
    // Complexity: O( sizeTree1 + sizeTree2)
    int sizeTree1 = tree1.get_amount();
    int sizeTree2 = tree2.get_amount();
    T *arrTree1 = new T [sizeTree1];
    T *arrTree2 = new T [sizeTree2];

    // Fill an inorder array for each tree
    tree1.in_order_traversal_wrapper(arrTree1, sizeTree1);
    tree2.in_order_traversal_wrapper(arrTree2, sizeTree2);

    // Create new array
    T *arrTree = new T [sizeTree1 + sizeTree2];
    AVL_tree<T>::merge_sort(arrTree, arrTree1, sizeTree1, arrTree2, sizeTree2, sort_by_score);

    // Create tree
    this->root = this->AVL_tree<T>::make_AVL_tree_from_array(arrTree, 0, (sizeTree1 + sizeTree2) -1);
    this->amount = sizeTree1 + sizeTree2;

    // Free arrays
    delete[] arrTree1;
    delete[] arrTree2;
    delete[] arrTree;
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::make_AVL_tree_from_array(T arr[], int start, int end)
{
    int diff = end-start;
    if (diff < 0)
        return nullptr;
    int midIndex = start + diff/2;
    if (arr[midIndex] == nullptr)
        throw;

    Node *node = new Node(arr[midIndex]); //in case of bad_alloc, memory is freed from the tree destructor.
    node->tree = this;
    node->left = this->AVL_tree<T>::make_AVL_tree_from_array(arr,start,midIndex-1);
    node->right = this->AVL_tree<T>::make_AVL_tree_from_array(arr,midIndex+1,end);
    if (node->left != nullptr)
        node->left->parent = node;
    if (node->right != nullptr)
        node->right->parent = node;
    return node;
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

    //std::cout << "Entering: " << ((*(*leaf).content)) << std::endl;

    try {
        Node *parent = find_designated_parent(leaf);
        if (parent == nullptr) {
            root = leaf;
            leaf->tree = this;
            this->amount++;
            return leaf;
        } 
        //std::cout << "Parent id: " << ((*(*parent).content)) << std::endl;
        if ((*leaf).get_comparison(*parent) > 0) {
            parent->right = leaf;
        } else if ((*leaf).get_comparison(*parent) < 0) {
            parent->left = leaf;
        } else {
            delete leaf;
            throw ID_ALREADY_EXISTS();
        }
        leaf->parent = parent;
        leaf->tree=this;
        climb_up_and_rebalance_tree(leaf);
        this->amount++;
    }
    catch (std::bad_alloc const&){
        delete leaf;
        throw std::bad_alloc();
    }
    return leaf;

}


template<class T>
bool AVL_tree<T>::remove(int id) {
    // true if the node was removed. false otherwise.
    // time complexity: O(log(nodes))
    Node* node = find_id(id);
    if (node == nullptr){
        return false;
    }
    Node* next_unbalanced_node;
    // updates parent and children before deletion
    if (node->left == nullptr && node->right == nullptr) //if leaf
    {
        node->update_parent(nullptr);
        next_unbalanced_node = node->parent;
    }
    else if (node->left != nullptr && node->right == nullptr){ // only left child
        next_unbalanced_node = node->left;
        node->update_parent(node->left);
    }
    else if (node->left == nullptr && node->right != nullptr){ // only right child
        next_unbalanced_node = node->right;
        node->update_parent(node->right);
    }
    else { // 2 children
        Node* replacement = find_next_in_order(node->right); // replacement does not have a left child this way.
        if (replacement != node->right){
            //std::cout << "SWAP1\n";
            next_unbalanced_node = replacement->parent;
            replacement->update_parent(replacement->right); // update parent should work even on nullptr
        }
        else{ // replacement is the right child of the removed node.
            next_unbalanced_node = replacement;
            //std::cout << "SWAP2\n";
        }
        replace_nodes(node, replacement);
    }
    climb_up_and_rebalance_tree(next_unbalanced_node);
    delete node;
    this->amount--;
    return true;
}


template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_id(int id) {
    Node* current = root;
    if (!current){
        return nullptr;
    }

    while(true){ //while true loop ok because in every case we either return or go down tree.
        int difference = ((*current->content).get_id()) - id;
        if (difference == 0){
            return current;
        }
        else if ( difference < 0)  { //proceed to right(?) branch. current id smaller than wanted id.
            //std::cout << "id: " << id
            //          << " is bigger than: " << *current->content << std::endl;
            if (current->right != nullptr){
                //std::cout << "check right" << std::endl;
                current = current->right;
            }
            else{ //no right child
                //std::cout << (*current->content) <<  " has no right child so: " << std::endl;
                return nullptr; //search failed
            }
        }
        else{ //proceed to right branch
            //std::cout << "id: " << id
            //          << " is smaller than: " << *current->content << std::endl;
            if (current->left != nullptr){
                //std::cout << "check left" << std::endl;
                current = current->left;
            }
            else{
                //std::cout << *current->content << " has no left child so: " << std::endl;
                return nullptr;
            }
        }
    }
}


template<class T>
T AVL_tree<T>::get_content(int id) {
    Node* node = find_id(id);
    if (node){
        return node->content;
    }
    else
    {
        return nullptr;
    }
}


template<class T>
void AVL_tree<T>::merge(AVL_tree<T> &other) {

}


template<class T>
void AVL_tree<T>::in_order_traversal_wrapper(T arr[], int size) {
    int currIndex = 0;
    in_order_traversal(root, arr, size, currIndex);
}

template<class T>
void AVL_tree<T>::merge_sort(T newArr[], T arr1[], int size1, T arr2[], int size2, bool sort_by_score)
{
    int index1 = 0;
    int index2 = 0;
    int index = 0;
    // size of newArr[] MUST BE == size1+size2 !!!!!
    if (size1 < 0 || size2 < 0)
            throw;

    while(index1 < size1 && index2 < size2) {
        if (arr1[index1] == nullptr || arr2[index2] == nullptr)
            throw;
        int comparison = (*arr1[index1]).compare(*(arr2[index2]), sort_by_score);
        if (comparison < 0) {
            newArr[index] = arr1[index1];
            index1++;
        } else if (comparison > 0) {
            newArr[index] = arr2[index2];
            index2++;
        } else {
            throw;
        }
        index++;
    }

    if (index1 != size1) { // fill the rest of newArr with the remainder of arr1
        fill_array(newArr, arr1, size1, index, index1);
        return;
    }
    if (index2 != size2) { // fill the rest of newArr with the remainder of arr2
        fill_array(newArr, arr2, size2, index, index2);
        return;
    }

}

template<class T>
void AVL_tree<T>::fill_array(T newArr[], T oldArr[], int size, int& indexNew, int& indexOld)
{
    for (int i=indexOld; i<size; i++) {
        if (oldArr[i] == nullptr)
                throw;
        newArr[indexNew] = oldArr[i];
        indexNew++;
    }
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
void AVL_tree<T>::in_order_traversal(Node* node,T arr[], int size, int& currIndex)  {
    //receives a function, and activates it on every node in the tree in order.
    //takes O(nodes_in_tree) time, O(log(nodes)) memory.
    if (node == nullptr){
        return;
    }

    in_order_traversal(node->left, arr, size,currIndex);
    if (currIndex > size-1)
        throw;
    arr[currIndex] = node->content;
    currIndex++;
    in_order_traversal(node->right, arr, size,currIndex);
}


template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_next_in_order(AVL_tree::Node *node) {
    // used only in remove. this is called on the right child, and then we go as left as possible.
    if (node == nullptr){
        throw std::invalid_argument("next in order activated on nullptr");
    }
    Node* current = node;
    while(current->left != nullptr) // while left child
    {
        current = current->left;
    }
    return current;
}


template<class T>
void AVL_tree<T>::replace_nodes(AVL_tree::Node *node, AVL_tree::Node *replacement) {
    // to be used ONLY in remove().
    // this function is called only when node has 2 children.
    // after this function, no pointers should point at node.
    replacement->left = node->left;
    node->left->parent = replacement;
    if (node->right != replacement){ // sometimes the replacement is the right child. delicate edge case.
        replacement->right = node->right;
        node->right->parent = replacement;
    }
    node->update_parent(replacement);
}


template<class T>
typename AVL_tree<T>::Node* AVL_tree<T>::find_designated_parent(AVL_tree::Node* new_leaf) {
    //I THINK DOCUMENTATION IN THIS FUNCTION IS WRONG.
    Node* current = root;
    if (!current){
        return nullptr;
    }
    
    while(true){ //while true loop ok because in every case we either return or go down tree.

        if (new_leaf->get_comparison(*current)>0)  { //proceed to left branch.
            //std::cout << "id: " << (*new_leaf->content)
            //<< " is bigger than: " << (*current->content) << std::endl;
            if (current->right != nullptr){
                //std::cout << "check right" << std::endl;
                current = current->right;
            }
            else{ //no right child
                //std::cout << (*current->content) <<  " has no right child so: " << std::endl;
                return current;
            }
        }
        else{ //proceed to right branch
            //std::cout << "id: " << (*new_leaf->content)
            //<< " is smaller than: " << (*current->content) << std::endl;
            if (current->left != nullptr){
                //std::cout << "check left" << std::endl;
                current = current->left;
            }
            else{
                //std::cout << (*current->content) << " has no left child so: " << std::endl;
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
        //std::cout << "tree is a nullptr!" << std::endl;
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

template <class T>
int AVL_tree<T>::get_amount() {
    return amount;
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
    Node* current = leaf; //not node.parent, so it also updates the height of the node to 0 if it's a leaf.
    
    while (current){ //climbs up tree. stops after iterating on root.
        current->set_height();
        current->set_balance_factor();
        //std::cout << "Currently on: " << (*current->content)
        //<< " -> balance factor " << std::to_string(current->balance_factor)
        //<< ", height " << std::to_string(current->height)<< std::endl;
        if (abs(current->balance_factor) == UNBALANCED){
            current->choose_roll(); //because roll switches parent and child, we will still get to the new parent.
        }
        current->set_height();
        current = current->parent;
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
    if (replacement){
        replacement->parent = parent;
    }
    parent = replacement;
}

template<class T>
void AVL_tree<T>::Node::choose_roll() {
    //if this function is called, it means the BF of this node is ±2, and it should roll.
    //the numbers are according to the chart in the slides.
    std::cout << "the tree is unbalanced -> do roll" << std::endl;
    
    if (balance_factor == 2){
        if (left->balance_factor >= 0){
            //std::cout << "roll: LL" << std::endl;
            this->LL_roll();
        }
        else if (left->balance_factor == -1){
            //std::cout << "roll: LR" << std::endl;
            this->LR_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else if (balance_factor == -2){
        if (right->balance_factor <= 0){
            //std::cout << "roll: RR" << std::endl;
            this->RR_roll();
        }
        else if (right->balance_factor == 1){
            //std::cout << "roll: RL" << std::endl;
            this->RL_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else throw std::invalid_argument("bad balance factor");
    
}

template<class T>
void AVL_tree<T>::Node::roll_left() {
    Node* original_right = right;
    if (right->left){
    right->left->parent = this;
    }
    right = right->left;
    original_right->left = this;
    update_parent(original_right);
    set_balance_factor();
}

template<class T>
void AVL_tree<T>::Node::roll_right() {
    Node* original_left = left;
    if(left->right){
        left->right->parent = this;
    }
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
// TODO: Erase before submission
template<class T>
void AVL_tree<T>::debugging_printTree(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str)
{
    if( node != nullptr )
    {
        str += prefix;

        str += (isLeft ? "├──" : "└──" );

        // print the value of the node
        str += std::to_string((*(node->content)).get_id());
        str += "\n";

        // enter the next tree level - left and right branch
        AVL_tree<T>::debugging_printTree( prefix + (isLeft ? "│   " : "    "), node->left, true, str);
        AVL_tree<T>::debugging_printTree( prefix + (isLeft ? "│   " : "    "), node->right, false, str);
    }
}

template<class T>
void AVL_tree<T>::debugging_printTree(const AVL_tree::Node* node, std::string& str)
{
    debugging_printTree("", node, false, str);
}

template<class T>
std::string AVL_tree<T>::debugging_printTree()
{
    std::string tree = "";
    debugging_printTree(root, tree);
    return tree;
}

template<class T>
void AVL_tree<T>::find_test_wrapper(int id) {
    print_node(find_id(id));
}

template<class T>
void AVL_tree<T>::print_node(Node* node){
    //the format is: self, parent, left, right
    if (node == nullptr){
        std::cout << "NULL\n";
        return;
    }
    //std::cout << (*(node->content)).get_id() << " " <<
    //        ((node->parent) ? (*(node->parent->content)).get_id() : 0 ) << " " <<
    //        ((node->left) ? (*(node->left->content)).get_id() : 0 ) << " " <<
    //        ((node->right) ? (*(node->right->content)).get_id() : 0 ) <<std::endl;
    if (node->left){
        if ((node->left && node->left->parent != node) || (node->right && node->right->parent != node)){
            throw std::invalid_argument("parent and child dont point at each other");
        }
    }
}

// ----------------------------------



#endif //TECHNION_234218_DATA_STRUCTURES_WET_1_AVL_TREE_H