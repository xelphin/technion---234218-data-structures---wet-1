#ifndef TECHNION_234218_DATA_STRUCTURES_WET_1_TESTS_H
#define TECHNION_234218_DATA_STRUCTURES_WET_1_TESTS_H

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <functional>
#include <cmath>

#include "./AVL_tree.h"
#include "./Player.h"
#include "./Team.h"
#include "./worldcup23a1.h"
#include "./wet1util.h"
#include "./NodeList_Teams.h"

template<class T>
class AVL_testing{
public:
    static bool run_tests_on_tree(AVL_tree<T>* tree);
    static bool height_test(AVL_tree<T>* tree);
    static bool parent_child_relationship_test(AVL_tree<T>* tree);
    static bool node_relationship_test(typename AVL_tree<T>::Node* node);
    static bool run_tests_on_worldCup(world_cup_t* cup);
};

template<class T>
bool AVL_testing<T>::run_tests_on_worldCup(world_cup_t* cup) {
    std::cout << "all players avl: \n";
    bool a = AVL_testing<std::shared_ptr<Player>>::run_tests_on_tree(&cup->all_players_AVL);
    std::cout << "all players scores avl: \n";
    bool b = AVL_testing<std::shared_ptr<Player>>::run_tests_on_tree(&cup->all_players_score_AVL);
    std::cout << "all teams avl: \n";
    bool c = AVL_testing<std::shared_ptr<Team>>::run_tests_on_tree(&cup->teams_AVL);
    std::cout << "all valid teams avl: \n";
    bool d = AVL_testing<std::shared_ptr<Team>>::run_tests_on_tree(&cup->valid_teams_AVL);
    return (a && b && c && d);
}

template<class T>
bool AVL_testing<T>::run_tests_on_tree(AVL_tree<T> *tree) {
    std::cout << tree->debugging_printTree_new();
//    std::cout<< "old debug: \n" << tree->debugging_printTree();
    return ( //all tests should be true
            height_test(tree) &&
            parent_child_relationship_test(tree)
            );
}

template<class T>
bool AVL_testing<T>::height_test(AVL_tree<T>* tree) {
    if (tree->root == nullptr){
        return true; //if no tree, it has the right hieght.
    }
    int N = tree->get_amount();
    int H = tree->root->height;
    int min_height = (int)log2(N);
    int max_height = (int)(1.44 * log2(N + 2) - 0.3277);
    return (min_height <= H && H <= max_height);
    //numbers taken from wikipedia AVL tree height, and log base conversion.
}

template<class T>
bool AVL_testing<T>::parent_child_relationship_test(AVL_tree<T> *tree) {
    return node_relationship_test(tree->root);
}

template<class T>
bool AVL_testing<T>::node_relationship_test(typename AVL_tree<T>::Node *node) {
    if (node == nullptr){
        return true;
    }
    if (node->tree->root != node){
        if (node->parent == nullptr || //not root but no parent
        not (node->parent->left == node || node->parent->right == node)//not parent's child
        )
        {
            return false;
        }
    }
    else{ //root
        if (node->parent != nullptr) //has parent even when root. this bad.
        {
            return false;
        }
    }
    if (node->left != nullptr && node->left == node->right){ // both children are the same node.
        return false;
    }
    return node_relationship_test(node->left) && node_relationship_test(node->right); //continues testing all nodes.
}



bool run_all_tests();
void run_test(std::function<bool()> test, std::string test_name, std::string& success_string, bool& success);

// TEST UTILS
void init_tree(AVL_tree<Player*> tree);
// TREE COMPARE
bool treeCompare(const std::string& tree, const std::string& wantedTree);
// PLAYER
bool playerCompare();
bool createAVL();
bool balanceAVL_LL();
bool balanceAVL_RR();
bool balanceAVL_LR();
bool balanceAVL_RL();
bool inorder_print();
bool inorder_print_check2();
bool find_test();
bool remove_test();
bool team_create();
bool createAVL_byMerge();

bool worldCup_Constructor();
bool worldCup_Add();
bool worldCup_Add_Player();
bool worldCup_Remove_Player();
bool worldCup_Remove_Team();
bool worldCup_Update_Player_Stats();
bool worldCup_Play_Match();
bool worldCup_Get_Num_Played_Games();
bool worldCup_Unite_Teams();
bool worldCup_Get_All_Players_Count();
bool closest_player_test();

bool worldCup_knockoutWinner();


#endif