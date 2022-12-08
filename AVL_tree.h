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
#include "NodeList.h"

#define SORT_BY_SCORE true
#define SORT_BY_ID false
#define UNBALANCED 2
#define SCORE >>=
#define ID ~

template<class T>
class AVL_testing;

//-------------------------------AVL TREE CLASS---------------------------------------//

template <class T>
class AVL_tree {
public:
    class Node;


    explicit AVL_tree(bool sort_by_score); // O(1)
    ~AVL_tree(); // O(n[amount nodes])
    AVL_tree(const AVL_tree &) = delete; //cant copy trees
    AVL_tree &operator=(AVL_tree &other) = delete;

    AVL_tree<T>::Node* add(T item);
    bool remove(int id);
    bool remove_by_item(const T& item);
    bool remove_internal(AVL_tree<T>::Node* node);

    int get_amount();
    AVL_tree<T>::Node* find(const T& item);
    AVL_tree<T>::Node* find_id(int id);
    AVL_tree<T>::Node* find_rightmost(AVL_tree<T>::Node* node);
    AVL_tree<T>::Node* find_leftmost(AVL_tree<T>::Node* node);

    // CLOSEST functions
    AVL_tree<T>::Node* find_closest_left(AVL_tree<T>::Node* node);
    AVL_tree<T>::Node* find_closest_right(AVL_tree<T>::Node* node);
    AVL_tree<T>::Node* find_a_closest(AVL_tree<T>::Node* node);

    T get_content(int id);
    T get_biggest_in_tree();


    AVL_tree<T>::Node* make_AVL_tree_from_array(T arr[], int start, int end);
    static void merge_sort(T newArr[], T arr1[], int size1, T arr2[], int size2, bool sort_by_score);
    static void fill_array(T newArr[], T oldArr[], int size, int& indexNew, int& indexOld);

    template<class F>
    explicit AVL_tree(AVL_tree<T>& tree1, AVL_tree<T>& tree2, bool sort_by_score, F functor);

    template<class F>
    void in_order_traversal_wrapper(F functor); // used to iterate on all the nodes.

    // KNOCKOUT function
    void add_to_list(NodeList& list, int minId, int maxId);
    void add_to_list_aux(AVL_tree<T>::Node* root, bool& passedMin, bool& passedMax, NodeList& list, int minId, int maxId);


    // TESTS AND DEBUGGING FUNCTIONS
    std::string debugging_printTree();
    std::string debugging_printTree_new();
    static void print_node(AVL_tree<T>::Node* node);
    void find_test_wrapper(int id);
    #ifndef NDEBUG
        friend AVL_testing<T>;
    #endif
private:
    const bool sort_by_score;
    AVL_tree<T>::Node *root;
    int amount;

    AVL_tree<T>::Node* find_designated_parent(AVL_tree<T>::Node* new_leaf);
    void climb_up_and_rebalance_tree(AVL_tree<T>::Node* leaf);
    void post_order_delete();
    AVL_tree<T>::Node* find_next_in_order(AVL_tree<T>::Node* node);
    void replace_nodes(AVL_tree<T>::Node* node, AVL_tree<T>::Node* replacement);

    template<class F>
    void in_order_traversal(AVL_tree<T>::Node* node, F* functor);


    // TESTS AND DEBUGGING FUNCTIONS
    void debugging_printTree(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str);
    void debugging_printTree(const AVL_tree::Node* node, std::string& str);
    void debugging_printTree_new(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str);
    void debugging_printTree_new(const AVL_tree::Node* node, std::string& str);
};


//--------------------------------NODE CLASS------------------------------------------//

//Nodes will be used in the AVL tree, and will allocate memory for an actual item.
template <class T>
class AVL_tree<T>::Node{
public:
    AVL_tree<T> *tree;
    AVL_tree<T>::Node *parent;
    AVL_tree<T>::Node *left;
    AVL_tree<T>::Node *right;
    T content; //T is always a type of pointer.
    int balance_factor; //to manage the sorting of the AVL tree.
    int height;

    explicit Node(T);
    Node(const AVL_tree &) = delete; //cant copy nodes. make new ones.
    Node &operator=(AVL_tree &other) = delete;
    ~Node() = default;

    int get_comparison(const AVL_tree<T>::Node &other);

    //tree sorting functions:
    int set_balance_factor();
    int set_height();
    int get_height(AVL_tree<T>::Node* node);
    void choose_roll();

    void update_parent(AVL_tree<T>::Node* replacement);

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
AVL_tree<T>::AVL_tree(bool sort_by_score) :
sort_by_score(sort_by_score),
root(nullptr),
amount(0)
{

}

template<class T>
AVL_tree<T>::~AVL_tree() {
    post_order_delete();
}


template<class T>
AVL_tree<T>::Node::Node(T new_item) 
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
typename AVL_tree<T>::Node* AVL_tree<T>::add(T item) {
    // returns a pointer to the node holding the pointer to the item. we need that
    // in order to store the list of nodes in the object, so we can delete all the nodes when
    // the object is deleted.
    //

    AVL_tree<T>::Node* leaf(new Node(item));
    try {
        leaf->tree = this;
        AVL_tree<T>::Node *parent = find_designated_parent(leaf);
        if (parent == nullptr) {
            root = leaf;
            leaf->tree = this;
            this->amount++;
            return leaf;
        } 

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
bool AVL_tree<T>::remove_by_item(const T& item) {
    // true if the node was removed. false otherwise.
    // time complexity: O(log(nodes))
    AVL_tree<T>::Node* node = find(item);
    if (node == nullptr){
        return false;
    }
    else{
        return remove_internal(node);
    }
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find(const T& item) {
    //item acts like "this->content"
    AVL_tree<T>::Node* current = root;
    if (!current){
        return nullptr;
    }

    while(true){ //while true loop ok because in every case we either return or go down tree.
        int difference = ((*current->content).get_id()) - item->get_id();
        if (difference == 0){
            return current;
        }

        if (sort_by_score == SORT_BY_SCORE){
            difference = *(current->content) SCORE (*(item));

        }
        else
        {
            difference = ID(*(current->content)) - ID(*(item));
        }
        if ( difference < 0)  { //proceed to right branch. current id smaller than wanted id.
            if (current->right != nullptr){
                //std::cout << "check right" << std::endl;
                current = current->right;
            }
            else{ //no right child
                return nullptr; //search failed
            }
        }
        else{ //proceed to left branch
            if (current->left != nullptr){
                current = current->left;
            }
            else{
                return nullptr;
            }
        }
    }
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_rightmost(AVL_tree<T>::Node* node) {
    if (node == nullptr){
        return nullptr;
    }
    Node* current = node->right;
    if (current == nullptr){ //no nodes to the right of this node
        return nullptr;
    }

    while(true){ //while true loop ok because in every case we either return or go down tree.
        if (current->right != nullptr){
            current = current->right;
        }
        else{
            return current; //returns when there is no right child
        }
    }
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_closest_left(AVL_tree<T>::Node* node)
{
    // Called after add_player() -> log(n)
    // Called before remove_player() -> log(n)
    // ((*leaf).get_comparison(*parent) > 0)
    if (node == nullptr)
        return nullptr;
    if (root == nullptr)
        return nullptr;
    Node* node_immediate_left = node->left;

    // Has no left child -> search through ancestors
    if (node_immediate_left == nullptr) {
        Node* top = root;
        while (top != nullptr && top != node) {
            if (top->get_comparison(*node) < 0) { // top > node
                if (top->right == nullptr)
                    return nullptr;
                if (top->right->get_comparison(*node) >= 0) // top->right >= node
                    return top;
                top = top->right;
            } else {
                top = top->left;
                if (top == node) // smallest
                    return nullptr;
            }
        }
    }

    // Has left child -> search through children
    Node* current = node_immediate_left->right;
    if (current == nullptr)
        return node_immediate_left;
    // Get the rightmost from node_immediate_left
    while(current) {
        if (current->right == nullptr)
            return current;
        current = current->right;
    }
    return current;
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_closest_right(AVL_tree<T>::Node* node)
{
    // Called after add_player() -> log(n)
    // Called before remove_player() -> log(n)
    // ((*leaf).get_comparison(*parent) > 0)
    if (node == nullptr)
        return nullptr;
    if (root == nullptr)
        return nullptr;

    Node* node_immediate_right = node->right;

    // Has no right child -> search through ancestors
    if (node_immediate_right == nullptr) {
        Node* top = root;
        while (top != nullptr && top != node) {
            if (top->get_comparison(*node) > 0) { // top < node
                if (top->left == nullptr)
                    return nullptr;
                if (top->left->get_comparison(*node) <= 0) // top->right >= node
                    return top;
                top = top->left;
            } else {
                top = top->right;
                if (top == node) // smallest
                    return nullptr;
            }
        }
    }

    // Has right child -> search through children
    Node* current = node_immediate_right->left;
    if (current == nullptr)
        return node_immediate_right;
    // Get the rightmost from node_immediate_right
    while(current) {
        if (current->left == nullptr)
            return current;
        current = current->left;
    }
    return current;
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_a_closest(AVL_tree<T>::Node* node)
{
    if (node == nullptr || node->content == nullptr)
        return nullptr;
    if (this->amount == 1) {
        return nullptr;
    }
    Node* closest_right = this->find_closest_right(node);
    if (closest_right != nullptr)
        return closest_right;
    return this->find_closest_left(node);
}

template<class T>
bool AVL_tree<T>::remove(int id) {
    // true if the node was removed. false otherwise.
    // time complexity: O(log(nodes))
    AVL_tree<T>::Node* node = find_id(id);
    if (node == nullptr){
        return false;
    }
    else{
        return remove_internal(node);
    }

}

template<class T>
bool AVL_tree<T>::remove_internal(AVL_tree<T>::Node* node) {
    //needs to be O(log(n)), where n is either players or teams in system, depending on calling function.
    AVL_tree<T>::Node* next_unbalanced_node = nullptr;
    AVL_tree<T>::Node* replacement = nullptr;
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
        replacement = find_next_in_order(node->right); // replacement does not have a left child this way.

        if (replacement == nullptr){
            throw std::invalid_argument("next in order activated on nullptr");
        }

        if (replacement->left != nullptr){
            throw std::logic_error("not supposed to have left son");
        }
        else if (replacement->right != nullptr){ // if it has a right child
            next_unbalanced_node = replacement->right;
            // his right cant have a child node because that makes replacement have a BF of -2.
        }
        else if (replacement != node->right) //replacement has no children, and is not the right child of the removed node.
        {
            next_unbalanced_node = replacement->parent;
        }
        else
        { // replacement is the right child of the removed node.
            next_unbalanced_node = replacement;
        }


        if (replacement != node->right){
            replacement->update_parent(replacement->right); // update parent should work even on nullptr
        }
        replace_nodes(node, replacement);
    }

    // found next unbalanced, replaced if necessary.
    if (next_unbalanced_node != nullptr) //if not removed root and now empty tree
    {
        climb_up_and_rebalance_tree(next_unbalanced_node);
    }

    delete node;
    this->amount--;
    return true;
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_id(int id) {
    AVL_tree<T>::Node* current = root;
    if (!current){
        return nullptr;
    }

    while(true){ //while true loop ok because in every case we either return or go down tree.
        int difference = ((*current->content).get_id()) - id;
        if (difference == 0){
            return current;
        }
        else if ( difference < 0)  { //proceed to right branch. current id smaller than wanted id.
            if (current->right != nullptr){
                //std::cout << "check right" << std::endl;
                current = current->right;
            }
            else{ //no right child
                return nullptr; //search failed
            }
        }
        else{ //proceed to left branch
            if (current->left != nullptr){
                current = current->left;
            }
            else{
                return nullptr;
            }
        }
    }
}

template<class T>
T AVL_tree<T>::get_content(int id) {
    AVL_tree<T>::Node* node = find_id(id);
    if (node){
        return node->content;
    }
    else
    {
        return nullptr;
    }
}

template<class T>
T AVL_tree<T>::get_biggest_in_tree() {
    AVL_tree<T>::Node* node = find_rightmost(root);
    if (node != nullptr){
        T value = node->content;
        return value;
    }
    else if (root){
        return root->content;
    }
    else{
        return nullptr;
    }
}

template<class T>
template<class F>
void AVL_tree<T>::in_order_traversal_wrapper(F functor) {
    in_order_traversal(root, &functor);
}


template <class T, class F>
class ArrayFillerFunctor{
private:
    int size;
    int currIndex;
    F functor;
    T* arr;
public:
    ArrayFillerFunctor(T* arr, int size, F func) : size(size), currIndex(0), functor(func), arr(arr) {}

    // call is: functor(node->content);
    void operator() (T node_content) {
        if (currIndex > size - 1){
            throw std::exception();
        }
        functor(node_content);
        arr[currIndex] = node_content;
        currIndex++;
    }
    //typename AVL_tree<T>::Node* node, T arr[], int size, int& currIndex, F functor)
};

template <class T>
class ArrayFillerFunctor_ID{
private:
    int size;
    int currIndex;
    int* arr;
public:
    ArrayFillerFunctor_ID(int* arr, int size) : size(size), currIndex(0), arr(arr) {}

    // call is: functor(node->content);
    void operator() (T node_content) {
        if (currIndex > size - 1){
            throw std::exception();
        }
        arr[currIndex] = node_content.get()->get_id();
        currIndex++;
    }
};

//this constructor is used to merge 2 trees together.
template<class T>
template <class F>
AVL_tree<T>::AVL_tree(AVL_tree<T>& tree1, AVL_tree<T>& tree2, bool sort_by_score, F functor)
        : sort_by_score(sort_by_score), root(nullptr), amount(0)
{
    // Complexity: O( sizeTree1 + sizeTree2)
    int sizeTree1 = tree1.get_amount();
    int sizeTree2 = tree2.get_amount();
    T *arrTree1 = new T [sizeTree1];
    T *arrTree2;
    try
    {
        arrTree2 = new T [sizeTree2];
    }
    catch (...){
        delete[] arrTree1;
        throw;
    }

    try {
        // Fill an inorder array for each tree
        tree1.in_order_traversal_wrapper(ArrayFillerFunctor<T, F>(arrTree1, sizeTree1, functor));
        tree2.in_order_traversal_wrapper(ArrayFillerFunctor<T, F>(arrTree2, sizeTree2, functor));
    }
    catch (...){
        delete[] arrTree1;
        delete[] arrTree2;
        throw;
    }
    // Create new array
    T *arrTree = new T [sizeTree1 + sizeTree2];

    try{
        AVL_tree<T>::merge_sort(arrTree, arrTree1, sizeTree1, arrTree2, sizeTree2, sort_by_score);
    }
    catch (...){
        delete[] arrTree1;
        delete[] arrTree2;
        delete[] arrTree;
        throw;
    }

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


    AVL_tree<T>::Node *node = new Node(arr[midIndex]); //in case of bad_alloc, memory is freed from the tree destructor.

    try {
        node->tree = this;
        node->left = this->AVL_tree<T>::make_AVL_tree_from_array(arr, start, midIndex - 1);
        node->right = this->AVL_tree<T>::make_AVL_tree_from_array(arr, midIndex + 1, end);
    }
    catch (...){
        delete node;
        throw;
    }
    if (node->left != nullptr)
        node->left->parent = node;
    if (node->right != nullptr)
        node->right->parent = node;
    return node;
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
    AVL_tree<T>::Node* current = root;
    AVL_tree<T>::Node* temp = root;
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
template<class F>
void AVL_tree<T>::in_order_traversal(AVL_tree::Node *node, F *functor) {
    //receives a function, and activates it on every node in the tree in order.
    //takes O(nodes_in_tree) time, O(log(nodes)) memory.
    if (node == nullptr){
        return;
    }

    in_order_traversal(node->left, functor);
    (*functor)(node->content);
    in_order_traversal(node->right, functor);
}

//template<typename T, typename P>
//void transform(Queue<T> &queue, P function) {
//    //can't use range based for loop because it needs *it and not it.
//    for (typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it)
//    {
//        function(*it);
//    }
//}


template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_next_in_order(AVL_tree::Node *node) {
    // used only in remove. this is called on the right child, and then we go as left as possible.
    if (node == nullptr){
        throw std::invalid_argument("next in order activated on nullptr");
    }
    AVL_tree<T>::Node* current = node;
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
    AVL_tree<T>::Node* current = root;
    if (!current){
        return nullptr;
    }
    
    while(true){ //while true loop ok because in every case we either return or go down tree.

        if (new_leaf->get_comparison(*current)>0)  { //proceed to right branch.
            if (current->right != nullptr){
                current = current->right;
            }
            else{ //no right child
                return current;
            }
        }
        else{ //proceed to left branch
            if (current->left != nullptr){
                current = current->left;
            }
            else{
                return current;
            }
        }
    }
}


template <class T>
int AVL_tree<T>::Node::get_comparison(const AVL_tree<T>::Node &other) {
    // since its unknown if the tree is sorted by id or by score, we need this function to work on both.
    // '!' operator is for score. '~' operator is for id.
    // the comparison is done between the dereferences of the pointers the nodes holds.
    
    if (tree == nullptr ) {
        //std::cout << "tree is a nullptr!" << std::endl;
        return 0;
    }
    if (tree->sort_by_score == SORT_BY_SCORE){
        return *(this->content) SCORE *(other.content);

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
void AVL_tree<T>::climb_up_and_rebalance_tree(AVL_tree<T>::Node *leaf) {
    AVL_tree<T>::Node* current = leaf; //not node.parent, so it also updates the height of the node to 0 if it's a leaf.

    while (current != nullptr){ //climbs up tree. stops after iterating on root.
        current->set_height();

        current->set_balance_factor();
        if (abs(current->balance_factor) == UNBALANCED){
            current->choose_roll(); //because roll switches parent and child, we will still get to the new parent.
        }
        current->set_height();
        current = current->parent;
    }
    
}

template<class T>
void AVL_tree<T>::Node::update_parent(AVL_tree<T>::Node* replacement) {
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
    // std::cout << "the tree is unbalanced -> do roll" << std::endl;
    set_balance_factor();
    if (balance_factor == 2){
        if (left->set_balance_factor() >= 0){
            //std::cout << "roll: LL" << std::endl;
            this->LL_roll();
        }
        else if (left->set_balance_factor() == -1){
            //std::cout << "roll: LR" << std::endl;
            this->LR_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else if (balance_factor == -2){
        if (right->set_balance_factor() <= 0){
            //std::cout << "roll: RR" << std::endl;
            this->RR_roll();
        }
        else if (right->set_balance_factor() == 1){
            //std::cout << "roll: RL" << std::endl;
            this->RL_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else throw std::invalid_argument("bad balance factor");
}

template<class T>
void AVL_tree<T>::Node::roll_left() {
    AVL_tree<T>::Node* original_right = right;
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
    AVL_tree<T>::Node* original_left = left;
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




//-------------------------------------------DEBUGGING-------------------------------------------//
// ONLY FOR DEBUGGING - ERASE LATER
// TODO: Erase before submission
template<class T>
void AVL_tree<T>::debugging_printTree_new(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str)
{
    if( node != nullptr )
    {
        str += prefix;

        str += (isLeft ? "└──" : "├──" );

        // print the value of the node
        str += std::to_string((*(node->content)).get_id());
        str += "\n";

        // enter the next tree level - left and right branch
        AVL_tree<T>::debugging_printTree_new( prefix + (isLeft ? "    " : "│   "), node->right, false, str);
        AVL_tree<T>::debugging_printTree_new( prefix + (isLeft ? "    " : "│   "), node->left, true, str);
    }
}

template<class T>
void AVL_tree<T>::debugging_printTree_new(const AVL_tree::Node* node, std::string& str)
{
    debugging_printTree_new("", node, true, str);
}

template<class T>
std::string AVL_tree<T>::debugging_printTree_new()
{
    std::string tree = "";
    debugging_printTree_new(root, tree);
    return tree;
}


//------------------------------------------KNOCKOUT FUNCTIONS-----------------//

template<class T>
void AVL_tree<T>::add_to_list(NodeList& list, int minId, int maxId)
{
    bool passedMin = false;
    bool passedMax = false;
    add_to_list_aux(root, passedMin, passedMax, list, minId, maxId);
}

template<class T>
void AVL_tree<T>::add_to_list_aux(AVL_tree::Node* node, bool& passedMin, bool& passedMax, NodeList& list, int minId, int maxId)
{
    if (node == nullptr)
        return;
    if (node->content == nullptr)
        return;
    // CHECK LEFT of tree
    if ((*(node->content)).get_id() > minId) {
        add_to_list_aux(node->left, passedMin, passedMax, list, minId, maxId);
    }

    // ADD Team to list and UPDATE passed arguments
    if ((*(node->content)).get_id() >= minId && (*(node->content)).get_id() <= maxId) {
        list.add((*(node->content)).get_id(),
                 (*(node->content)).get_total_points(),
                 (*(node->content)).get_goals(),
                 (*(node->content)).get_cards());
        if ((*(node->content)).get_id() == minId)
            passedMin = true;
        if ((*(node->content)).get_id() == maxId)
            passedMax = true;
    }

    // CHECK RIGHT of tree
    if ((*(node->content)).get_id() < maxId) {
        add_to_list_aux(node->right, passedMin, passedMax, list, minId, maxId);
    }

}

//------------------------------------------OLD DEBUG FUNCTIONS FOR TESTS TO WORK-----------------//

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
void AVL_tree<T>::print_node(AVL_tree<T>::Node* node){
    //the format is: self, parent, left, right
    if (node == nullptr){
//        std::cout << "NULL\n";
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