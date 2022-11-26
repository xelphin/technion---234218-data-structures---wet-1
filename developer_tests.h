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

#include "./AVL_tree.h"
#include "./Player.h"
#include "./Team.h"
#include "./worldcup23a1.h"
#include "./wet1util.h"

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
bool find_test();
bool remove_test();
bool team_create();
bool createAVL_byMerge();

#endif