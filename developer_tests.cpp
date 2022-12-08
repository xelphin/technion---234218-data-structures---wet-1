#include "./developer_tests.h"


#ifdef NDEBUG // I DONT want to debug
void printFail ();
void printSuccess ();
#define printFail() ((void)0)
#define printSuccess() ((void)0)
#else // I DO want to debug
#define printFail() (std::cout<< test_name <<" FAILED."<<std::endl)
#define printSuccess() (std::cout<< test_name <<" SUCCESS."<<std::endl)
#endif
#include <cassert>

bool run_all_tests() {
    std::string success_string = "ALL (OUR) TESTS SUCCEEDED";
    bool success = true;
    run_test(playerCompare, "playerCompare", success_string, success);
    run_test(createAVL, "createAVL", success_string, success);
    run_test(balanceAVL_LL, "balanceAVL_LL", success_string, success);
    run_test(balanceAVL_RR, "balanceAVL_RR", success_string, success);
    run_test(balanceAVL_LR, "balanceAVL_LR", success_string, success);
    run_test(balanceAVL_RL, "balanceAVL_RL", success_string, success);
    run_test(inorder_print, "inorder print", success_string, success);
    run_test(inorder_print_check2, "inorder_print_check2()", success_string, success);
    run_test(find_test, "find", success_string, success);
    run_test(remove_test, "remove", success_string, success);
    run_test(team_create, "team_create", success_string, success);
    run_test(createAVL_byMerge, "createAVL_byMerge", success_string, success);
    run_test(worldCup_Constructor, "worldCup_Constructor", success_string, success);
    run_test(worldCup_Add, "worldCup_Add", success_string, success);
    run_test(worldCup_Add_Player, "worldCup_Add_Player", success_string, success);
    run_test(worldCup_Remove_Player, "worldCup_Remove_Player", success_string, success);
    run_test(worldCup_Remove_Team, "worldCup_Remove_Team", success_string, success);
    run_test(worldCup_Update_Player_Stats, "worldCup_Update_Player_Stats", success_string, success);
    run_test(worldCup_Play_Match, "worldCup_Play_Match", success_string, success);
    run_test(worldCup_Get_Num_Played_Games, "worldCup_Get_Num_Played_Games", success_string, success);
    run_test(worldCup_Unite_Teams, "worldCup_Unite_Teams", success_string, success);
    run_test(worldCup_Get_All_Players_Count, "worldCup_Get_All_Players_Count", success_string, success);
    run_test(closest_player_test, "closest_player_test", success_string, success);
    run_test(nodeList_Teams_Basics, "nodeList_Teams_Basics", success_string, success);
    run_test(avl_Add_To_List, "avl_Add_To_List", success_string, success);
    run_test(worldCup_Knockout_Winner, "worldCup_Knockout_Winner", success_string, success);
    run_test(nodeList_Add, "nodeList_Add", success_string, success);
    run_test(nodeList_Remove, "nodeList_Remove", success_string, success);
    run_test(omeramir_tests_line, "omeramir_tests_line", success_string, success);

    run_test(avl_getClosestLeft, "avl_getClosestLeft", success_string, success);
    run_test(avl_getClosestRight, "avl_getClosestRight", success_string, success);
    run_test(worldCup_get_closest_player, "worldCup_get_closest_player", success_string, success);

    run_test(nodeList_Get_Closest, "nodeList_Get_Closest", success_string, success);
    run_test(worldCup_get_closest_player, "worldCup_get_closest_player", success_string, success);
    run_test(worldCup_get_closest_player_extended, "worldCup_get_closest_player_extended", success_string, success);

    std::cout << success_string << std::endl;
    return success;
}

void run_test(std::function<bool()> test, std::string test_name, std::string& success_string, bool& success)
{
    if(!test()){
        printFail();
        std::cout << std::endl;
        success_string = "FAILED TEST: " + test_name;
        success = false;
        return;
    }
    std::cout << "-------------------" << std::endl;
    printSuccess();
    std::cout << "-------------------" << std::endl;
    std::cout << std::endl;
}

bool treeCompare(const std::string& tree, const std::string& wantedTree)
{
    if (wantedTree.compare(tree) == 0)
        return true;
    return false;
}
// ----------------------------- TESTS -----------------------------


bool playerCompare()
{
    int count = 0;

    Player player1(1, 2, 5, 6, 4, false); // goals == 6
    Player player2(2, 2, 5, 4, 4, false); // goals == 4

    if ((player1 SCORE player2) > 0)
        count++;
    if (~(player1) - ~(player2) < 0)
        count++;

    return count == 2;
}

bool createAVL()
{
    int tests = 0;
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player1(4, 2, 5, 6, 4, false); // id: 4
    Player player2(1, 2, 3, 3, 4, false); // id: 1
    Player player3(7, 2, 3, 3, 4, false); // id: 7
    Player player4(3, 2, 3, 3, 4, false); // id: 3
    tree1.add(&player1);
    std::cout << tree1.debugging_printTree_new();
    tree1.add(&player2);
    std::cout << tree1.debugging_printTree_new();
    tree1.add(&player3);
    std::cout << tree1.debugging_printTree_new();
    tree1.add(&player4);

    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──4\n    ├──1\n    │   └──3\n    └──7\n";
    tests += treeCompare(finalTree,wantedTree);

    std::cout << "amount of nodes " << std::to_string(tree1.get_amount()) << std::endl;
    tests += (tree1.get_amount() == 4);

    if (not AVL_testing<Player*>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return tests == 2;
}

bool balanceAVL_LL()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player1(8, 2, 5, 6, 4, false); // id: 8
    Player player2(5, 2, 3, 3, 4, false); // id: 5
    Player player3(3, 2, 3, 3, 4, false); // id: 3
    Player player4(2, 2, 3, 3, 4, false); // id: 2
    Player player5(1, 2, 3, 3, 4, false); // id: 1
    tree1.add(&player1);
    tree1.add(&player2);
    tree1.add(&player3);
    tree1.add(&player4);
    tree1.add(&player5);

    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──5\n    ├──2\n    │   ├──1\n    │   └──3\n    └──8\n";
    if (not AVL_testing<Player*>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return treeCompare(finalTree,wantedTree);
}

bool balanceAVL_RR()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player1(1, 2, 5, 6, 4, false); // id: 1
    Player player2(2, 2, 5, 6, 4, false); // id: 2
    Player player3(3, 2, 3, 3, 4, false); // id: 3
    Player player4(4, 2, 3, 3, 4, false); // id: 4
    Player player5(5, 2, 3, 3, 4, false); // id: 5
    Player player6(6, 2, 3, 3, 4, false); // id: 6
    Player player7(7, 2, 3, 3, 4, false); // id: 7
    tree1.add(&player1);
    tree1.add(&player2);
    tree1.add(&player3);
    tree1.add(&player4);
    tree1.add(&player5);
    tree1.add(&player6);
    tree1.add(&player7);

    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──4\n    ├──2\n    │   ├──1\n    │   └──3\n    └──6\n        ├──5\n        └──7\n";
    if (not AVL_testing<Player*>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return treeCompare(finalTree,wantedTree);
}

bool balanceAVL_LR()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player2(2, 2, 5, 6, 4, false); // id: 2
    Player player3(3, 2, 3, 3, 4, false); // id: 3
    Player player4(4, 2, 3, 3, 4, false); // id: 4
    Player player5(5, 2, 3, 3, 4, false); // id: 5
    Player player6(6, 2, 3, 3, 4, false); // id: 6
    Player player7(7, 2, 3, 3, 4, false); // id: 7
    Player player8(8, 2, 3, 3, 4, false); // id: 8
    Player player10(10, 2, 3, 3, 4, false); // id: 10
    Player player20(20, 2, 3, 3, 4, false); // id: 20
    Player player21(21, 2, 3, 3, 4, false); // id: 21
    tree1.add(&player10);
    tree1.add(&player4);
    tree1.add(&player20);
    tree1.add(&player21);
    tree1.add(&player3);
    tree1.add(&player7);
    tree1.add(&player2);
    tree1.add(&player6);
    tree1.add(&player8);
    std::cout << tree1.debugging_printTree_new();
    //
    tree1.add(&player5);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──7\n    ├──4\n    │   ├──3\n    │   │   ├──2\n    │   └──6";
    wantedTree += "\n    │       ├──5\n    └──10\n        ├──8\n        └──20\n            └──21\n";
    if (not AVL_testing<Player*>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return treeCompare(finalTree,wantedTree);
}

bool balanceAVL_RL()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player10(10, 2, 3, 3, 4, false);
    Player player5(5, 2, 3, 3, 4, false);
    Player player20(20, 2, 3, 3, 4, false);
    Player player4(4, 2, 3, 3, 4, false);
    Player player6(6, 2, 3, 3, 4, false);
    Player player15(15, 2, 3, 3, 4, false);
    Player player30(30, 2, 3, 3, 4, false);
    Player player12(12, 2, 3, 3, 4, false);
    Player player18(18, 2, 3, 3, 4, false);
    Player player25(25, 2, 3, 3, 4, false);
    Player player40(40, 2, 3, 3, 4, false);
    //
    Player player19(19, 2, 3, 3, 4, false);
    //
    tree1.add(&player10);
    tree1.add(&player5);
    tree1.add(&player20);
    tree1.add(&player4);
    tree1.add(&player6);
    tree1.add(&player15);
    tree1.add(&player30);
    tree1.add(&player12);
    tree1.add(&player18);
    tree1.add(&player25);
    tree1.add(&player40);
    std::cout << tree1.debugging_printTree_new();
    //
    tree1.add(&player19);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──15\n    ├──10\n    │   ├──5\n    │   │   ├──4\n    │   │   └──6\n    │   └──12\n    └──20\n        ├──18";
    wantedTree += "\n        │   └──19\n        └──30\n            ├──25\n            └──40\n";
    if (not AVL_testing<Player*>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return treeCompare(finalTree,wantedTree);
}

bool inorder_print(){
    // TODO: Update function so that it puts values into array //
    AVL_tree<std::shared_ptr<Player>> tree1(false); // sort by ID
    Player player10(10, 2, 3, 3, 4, false);
    Player player5(5, 2, 3, 3, 4, false);
    Player player20(20, 2, 3, 3, 4, false);
    Player player4(4, 2, 3, 3, 4, false);
    Player player6(6, 2, 3, 3, 4, false);
    Player player15(15, 2, 3, 3, 4, false);
    Player player30(30, 2, 3, 3, 4, false);
    Player player12(12, 2, 3, 3, 4, false);
    Player player18(18, 2, 3, 3, 4, false);
    Player player25(25, 2, 3, 3, 4, false);
    Player player40(40, 2, 3, 3, 4, false);
    //
    Player player19(19, 2, 3, 3, 4, false);
    //
    tree1.add(std::make_shared<Player>(player10));
    tree1.add(std::make_shared<Player>(player5));
    tree1.add(std::make_shared<Player>(player20));
    tree1.add(std::make_shared<Player>(player4));
    tree1.add(std::make_shared<Player>(player6));
    tree1.add(std::make_shared<Player>(player15));
    tree1.add(std::make_shared<Player>(player30));
    tree1.add(std::make_shared<Player>(player12));
    tree1.add(std::make_shared<Player>(player18));
    tree1.add(std::make_shared<Player>(player25));
    tree1.add(std::make_shared<Player>(player40));
    std::cout << tree1.debugging_printTree_new();
    //
    tree1.add(std::make_shared<Player>(player19));

    std::cout << "inorder traversal print: \n";

    // TODO: Check function actually works
    int arrSize = tree1.get_amount();
    std::string myOutput = "";
    auto *arrTree = new std::shared_ptr<Player>[arrSize];
    try {
        std::cout << tree1.debugging_printTree_new();
        tree1.in_order_traversal_wrapper(
                ArrayFillerFunctor<std::shared_ptr<Player>, Functor>(arrTree, arrSize,
                                                                     Functor(nullptr)));
        std::cout
                << "CHECKING INORDER --------------------------------------------------------------------------"
                << std::endl;
        for (int i = 0; i < arrSize; i++) {
            if (arrTree[i] != nullptr) {
                myOutput += std::to_string(arrTree[i]->get_id()) + " ";
            }
        }
        std::cout << std::endl;
    }
    catch (...){
        delete[] arrTree;
        throw;
    }
    delete[] arrTree;
    std::cout << tree1.debugging_printTree_new(); // TODO: make sure my tree isn't deleted
    if (not AVL_testing<std::shared_ptr<Player>>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return myOutput.compare( "4 5 6 10 12 15 18 19 20 25 30 40 ") == 0;


}

bool inorder_print_check2(){
    // TODO: Update function so that it puts values into array
    AVL_tree<std::shared_ptr<Player>> tree1(false); // sort by ID
    std::shared_ptr<Player> player2 = std::make_shared<Player>(2, 2, 3, 3, 4, false);
    std::shared_ptr<Player> player5 = std::make_shared<Player>(5, 2, 3, 3, 4, false);
    std::shared_ptr<Player> player6 = std::make_shared<Player>(6, 2, 3, 3, 4, false);
    tree1.add(player2);
    tree1.add(player5);
    tree1.add(player6);

    int arrSize = tree1.get_amount();
    std::string myOutput = "";

    auto *arrTree = new std::shared_ptr<Player>[arrSize];
    try {
        tree1.debugging_printTree_new();
        tree1.in_order_traversal_wrapper(
                ArrayFillerFunctor<std::shared_ptr<Player>, Functor>(arrTree, arrSize,
                                                                     Functor(nullptr)));
        std::cout
                << "CHECKING INORDER --------------------------------------------------------------------------"
                << std::endl;
        for (int i = 0; i < arrSize; i++) {
            if (arrTree[i] != nullptr) {
                myOutput += std::to_string(arrTree[i]->get_id()) + " ";
            }
        }
        std::cout << myOutput << std::endl;
    }
    catch (...){
        delete[] arrTree;
    }
    delete[] arrTree;

    if (not AVL_testing<std::shared_ptr<Player>>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return true;
}

bool find_test() {
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player10(10, 2, 3, 3, 4, false);
    Player player5(5, 2, 3, 3, 4, false);
    Player player20(20, 2, 3, 3, 4, false);
    Player player4(4, 2, 3, 3, 4, false);
    Player player6(6, 2, 3, 3, 4, false);
    Player player15(15, 2, 3, 3, 4, false);
    Player player30(30, 2, 3, 3, 4, false);
    Player player12(12, 2, 3, 3, 4, false);
    Player player18(18, 2, 3, 3, 4, false);
    Player player25(25, 2, 3, 3, 4, false);
    Player player40(40, 2, 3, 3, 4, false);
    //
    Player player19(19, 2, 3, 3, 4, false);
    //
    tree1.add(&player10);
    tree1.add(&player5);
    tree1.add(&player20);
    tree1.add(&player4);
    tree1.add(&player6);
    tree1.add(&player15);
    tree1.add(&player30);
    tree1.add(&player12);
    tree1.add(&player18);
    tree1.add(&player25);
    tree1.add(&player40);
    tree1.add(&player19);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;

    std::cout << "find test, id range: 1-11\n";
    for (int id = 1; id <= 11; ++id) {
        tree1.find_test_wrapper(id);
    }

    return true;
}

bool remove_test() {
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player10(10, 2, 3, 3, 4, false);
    Player player5(5, 2, 3, 3, 4, false);
    Player player20(20, 2, 3, 3, 4, false);
    Player player4(4, 2, 3, 3, 4, false);
    Player player6(6, 2, 3, 3, 4, false);
    Player player15(15, 2, 3, 3, 4, false);
    Player player30(30, 2, 3, 3, 4, false);
    Player player12(12, 2, 3, 3, 4, false);
    Player player18(18, 2, 3, 3, 4, false);
    Player player25(25, 2, 3, 3, 4, false);
    Player player40(40, 2, 3, 3, 4, false);
    //
    Player player19(19, 2, 3, 3, 4, false);
    //
    tree1.add(&player10);
    tree1.add(&player5);
    tree1.add(&player20);
    tree1.add(&player4);
    tree1.add(&player6);
    tree1.add(&player15);
    tree1.add(&player30);
    tree1.add(&player12);
    tree1.add(&player18);
    tree1.add(&player25);
    tree1.add(&player40);
    tree1.add(&player19);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    //tree1.in_order_traversal_wrapper(AVL_tree<Player*>::print_node);

    std::cout << "remove test: \n";
    std::cout << "remove test, id range: 9-20\n";
    for (int id = 9; id <= 20; ++id) {
        std::cout << "-----------------------REMOVAL. id: " << id << std::endl;
        if(tree1.remove(id)){
            //tree1.in_order_traversal_wrapper(AVL_tree<Player*>::print_node);
            finalTree = tree1.debugging_printTree();
            std::cout << finalTree;
        }
    }
    finalTree = tree1.debugging_printTree();
    std::cout << finalTree;

    if (not AVL_testing<Player*>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    return tree1.get_amount() == 6;
}


bool team_create() {
    // Check that I can create a Team
    int tests = 0;
    std::shared_ptr<Player> player1(new Player(1, 2, 5, 4, 4, false));
    std::shared_ptr<Player> player2(new Player(2, 2, 5, 3, 4, false));
    std::shared_ptr<Player> player3(new Player(3, 2, 5, 2, 4, false));
    std::shared_ptr<Player> player4(new Player(4, 2, 5, 1, 4, false));

    Team team(1,0);
    team.add_player(player1);
    team.add_player(player2);
    team.add_player(player3);
    team.add_player(player4);

    std::string team_treeID = (*(team.get_AVL_tree_id())).debugging_printTree();
    std::cout << team_treeID;

    std::string wantedTree = "└──2\n    ├──1\n    └──3\n        └──4\n";
    std::cout << wantedTree;
    tests += treeCompare(team_treeID,wantedTree);

    std::string team_treeScore = (*(team.get_AVL_tree_score())).debugging_printTree();
    std::cout << team_treeScore;
    wantedTree = "└──2\n    ├──3\n    │   ├──4\n    └──1\n";
    std::cout << wantedTree;
    tests += treeCompare(team_treeScore,wantedTree);
    return tests == 2;
}

bool createAVL_byMerge()
{

    // Create trees 1 and 2
    AVL_tree<std::shared_ptr<Player>> tree1(false); // sort by ID
    AVL_tree<std::shared_ptr<Player>> tree2(false); // sort by ID
    std::shared_ptr<Player> player1 = std::make_shared<Player>(1, 2, 5, 6, 4, false);
    std::shared_ptr<Player> player2 = std::make_shared<Player>(2, 2, 5, 6, 4, false);
    std::shared_ptr<Player> player3 = std::make_shared<Player>(3, 2, 3, 3, 4, false);
    std::shared_ptr<Player> player4 = std::make_shared<Player>(4, 2, 3, 3, 4, false);
    std::shared_ptr<Player> player5 = std::make_shared<Player>(5, 2, 3, 3, 4, false);
    std::shared_ptr<Player> player6 = std::make_shared<Player>(6, 2, 3, 3, 4, false);
    std::shared_ptr<Player> player7 = std::make_shared<Player>(7, 2, 3, 3, 4, false);
    std::shared_ptr<Player> player8 = std::make_shared<Player>(8, 2, 3, 3, 4, false);

    tree1.add(player1);
    tree1.add(player3);
    tree1.add(player4);
    tree1.add(player7);

    tree2.add(player2);
    tree2.add(player5);
    tree2.add(player6);
    tree2.add(player8);
    std::cout << tree1.debugging_printTree_new();
    std::cout << tree2.debugging_printTree_new();
    //
    AVL_tree<std::shared_ptr<Player>> tree(tree1, tree2, false, Functor(nullptr));
    std::cout << tree.debugging_printTree_new();
    std::string finalTree = tree.debugging_printTree();

    std::string wantedTree = "└──4\n    ├──2\n    │   ├──1\n    │   └──3\n    └──6\n        ├──5\n        └──7\n            └──8\n";
    if (not AVL_testing<std::shared_ptr<Player>>::run_tests_on_tree(&tree1))
    {
        return false;
    }
    if (not AVL_testing<std::shared_ptr<Player>>::run_tests_on_tree(&tree2))
    {
        return false;
    }
    return treeCompare(finalTree,wantedTree);
}

bool worldCup_Constructor()
{
    world_cup_t worldCup;
    return true;
}

bool worldCup_Add()
{
    int test = 0;
    world_cup_t worldCup;
    test += StatusType::SUCCESS == worldCup.add_team(1,2);
    test += StatusType::FAILURE == worldCup.add_team(1,2);
    test += StatusType::INVALID_INPUT == worldCup.add_team(-1,2);
    test += StatusType::SUCCESS == worldCup.add_team(2,2);
    return test == 4;
}



bool worldCup_Add_Player()
{
    int tests = 0;
    world_cup_t worldCup;
    worldCup.add_team(1,0);
    worldCup.add_team(2,0);
    tests += StatusType::SUCCESS == worldCup.add_player(1, 2, 5, 6, 4, false);
    tests += StatusType::FAILURE == worldCup.add_player(1, 1, 5, 6, 4, false);
    tests += StatusType::SUCCESS == worldCup.add_player(2, 2, 5, 6, 4, false);
    tests += StatusType::INVALID_INPUT == worldCup.add_player(3, 2, 5, -1, 4, false);
    tests += StatusType::INVALID_INPUT == worldCup.add_player(3, 2, 0, 2, 0, false);
    tests += StatusType::SUCCESS == worldCup.add_player(3, 2, 5, 2, 0, false);
    tests += StatusType::FAILURE == worldCup.add_player(4, 3, 5, 2, 0, false);
    tests += StatusType::SUCCESS == worldCup.add_player(4, 2, 5, 2, 0, false);
    return tests == 8;
}

bool worldCup_Remove_Player()
{
    int tests = 0;
    world_cup_t worldCup;
    worldCup.add_team(1,0);
    worldCup.add_team(2,0);
    worldCup.add_team(3,0);
    worldCup.add_player(1, 1, 5, 6, 4, false);
    worldCup.add_player(2, 3, 5, 6, 4, false);
    worldCup.add_player(4, 3, 5, 6, 4, false);

    tests += StatusType::SUCCESS == worldCup.remove_player(1);
    tests += StatusType::FAILURE == worldCup.remove_player(1);
    tests += StatusType::INVALID_INPUT == worldCup.remove_player(-1);
    tests += StatusType::SUCCESS == worldCup.add_player(1, 2, 5, 6, 4, false);
    tests += StatusType::SUCCESS == worldCup.remove_player(1);
    tests += StatusType::SUCCESS == worldCup.remove_player(2);
    tests += StatusType::FAILURE == worldCup.remove_player(3);
    return tests == 7;
}
bool worldCup_Remove_Team()
{
    int tests = 0;
    world_cup_t worldCup;
    worldCup.add_team(1,0);
    worldCup.add_team(2,0);
    worldCup.add_team(3,0);
    worldCup.add_team(4,0);
    worldCup.add_player(1, 1, 5, 6, 4, false);
    worldCup.add_player(2, 2, 5, 6, 4, false);
    worldCup.add_player(3, 2, 5, 6, 4, false);
    //
    tests += StatusType::SUCCESS == worldCup.remove_team(3);
    tests += StatusType::FAILURE == worldCup.remove_team(2);
    tests += StatusType::FAILURE == worldCup.remove_team(3);
    tests += StatusType::FAILURE == worldCup.remove_team(5);
    tests += StatusType::SUCCESS == worldCup.remove_team(4);
    worldCup.add_team(4,0);
    tests += StatusType::SUCCESS == worldCup.remove_team(4);
    tests += StatusType::INVALID_INPUT == worldCup.remove_team(-1);
    tests += StatusType::INVALID_INPUT == worldCup.remove_team(0);
    //
    tests += StatusType::FAILURE == worldCup.remove_team(1);
    worldCup.remove_player(1);
    tests += StatusType::SUCCESS == worldCup.remove_team(1);
    //
    worldCup.remove_player(2);
    tests += StatusType::FAILURE == worldCup.remove_team(2);
    worldCup.remove_player(3);
    tests += StatusType::SUCCESS == worldCup.remove_team(2);

    return tests == 12;
}

bool worldCup_Update_Player_Stats()
{
    int tests = 0;
    world_cup_t worldCup;
    worldCup.add_team(1,0);
    worldCup.add_team(2,0);
    worldCup.add_team(3,0);
    worldCup.add_team(4,0);
    worldCup.add_player(1, 1, 5, 6, 4, false);
    worldCup.add_player(2, 2, 5, 6, 4, false);
    worldCup.add_player(3, 2, 5, 6, 4, false);
    //
    tests += StatusType::SUCCESS == worldCup.update_player_stats(1, 2, 3, 0);
    tests += StatusType::FAILURE == worldCup.update_player_stats(4, 2, 3, 0);
    tests += StatusType::INVALID_INPUT == worldCup.update_player_stats(2, -1, 3, 0);
    return tests == 3;
}

bool worldCup_Play_Match()
{

    int tests = 0;

    world_cup_t worldCup;
    worldCup.add_team(1,0);
    worldCup.add_team(2,0);
    worldCup.add_team(4,0);
    //
    worldCup.add_player(1, 1, 5, 6, 4, true);
    worldCup.add_player(2, 1, 5, 6, 4, false);
    worldCup.add_player(3, 1, 5, 6, 4, false);
    worldCup.add_player(4, 1, 5, 6, 4, false);
    worldCup.add_player(5, 1, 5, 6, 4, false);
    worldCup.add_player(6, 1, 5, 6, 4, false);
    worldCup.add_player(7, 1, 5, 6, 4, false);
    worldCup.add_player(8, 1, 5, 6, 4, false);
    worldCup.add_player(9, 1, 5, 6, 4, false);
    worldCup.add_player(10, 1, 5, 6, 4, false);
    worldCup.add_player(11, 1, 5, 6, 4, false);
    //
    worldCup.add_player(21, 2, 5, 6, 4, true);
    worldCup.add_player(22, 2, 5, 6, 4, false);
    worldCup.add_player(23, 2, 5, 6, 4, false);
    worldCup.add_player(24, 2, 5, 6, 4, false);
    worldCup.add_player(25, 2, 5, 6, 4, false);
    worldCup.add_player(26, 2, 5, 6, 4, false);
    worldCup.add_player(27, 2, 5, 6, 4, false);
    worldCup.add_player(28, 2, 5, 6, 4, false);
    worldCup.add_player(29, 2, 5, 6, 4, false);
    worldCup.add_player(30, 2, 5, 6, 4, false);
    worldCup.add_player(31, 2, 5, 6, 4, false);
    worldCup.add_player(32, 2, 0, 0, 0, false);
    //
    worldCup.add_player(41, 4, 5, 6, 4, false);
    //
    tests += StatusType::SUCCESS == worldCup.play_match(1, 2);
    tests += (1 == (worldCup.get_team_points(1)).ans());
    tests += (1 == (worldCup.get_team_points(2)).ans());
    tests += StatusType::FAILURE == worldCup.play_match(1, 4);
    tests += StatusType::FAILURE == worldCup.play_match(1, 5);

    std::cout << "running tests on play_match worldcup line 655 before removing player 21: \n"
              << AVL_testing<Player*>::run_tests_on_worldCup(&worldCup);
    worldCup.remove_player(21); //TODO: fix segfault
    tests += StatusType::FAILURE == worldCup.play_match(1, 2);

    std::cout << "running tests on play_match worldcup line 661 before adding player 33: \n"
    << AVL_testing<Player*>::run_tests_on_worldCup(&worldCup);

    worldCup.add_player(33, 2, 5, 6, 0, true); // ERROR CODE
    std::cout << "running tests on play_match worldcup line 655 before adding player 33: \n"
              << AVL_testing<Player*>::run_tests_on_worldCup(&worldCup);
    tests += StatusType::SUCCESS == worldCup.play_match(1, 2);
    tests += (1 == (worldCup.get_team_points(1)).ans());
    tests += (4 == (worldCup.get_team_points(2)).ans());
    tests += (StatusType::FAILURE == (worldCup.get_team_points(3)).status());
    //

    // TODO: Checked a bit with prints, but difficult to check directly because no public function gives me direct access to Team pointer
    return tests == 10;
}

bool worldCup_Get_Num_Played_Games()
{
    int tests = 0;
    world_cup_t worldCup;
    worldCup.add_team(1,1);
    worldCup.add_team(2,3);
    worldCup.add_player(2, 1, 5, 6, 4, false);
    worldCup.add_player(3, 1, 5, 6, 4, false);
    worldCup.add_player(4, 1, 5, 6, 4, false);
    worldCup.add_player(5, 1, 5, 6, 4, false);
    worldCup.add_player(6, 1, 5, 6, 4, false);
    worldCup.add_player(7, 1, 5, 6, 4, false);
    worldCup.add_player(8, 1, 5, 6, 4, false);
    worldCup.add_player(9, 1, 5, 6, 4, false);
    worldCup.add_player(10, 1, 5, 6, 4, false);
    worldCup.add_player(11, 1, 5, 6, 4, false);
    worldCup.add_player(22, 2, 5, 6, 4, false);
    worldCup.add_player(23, 2, 5, 6, 4, false);
    worldCup.add_player(24, 2, 5, 6, 4, false);
    worldCup.add_player(25, 2, 5, 6, 4, false);
    worldCup.add_player(26, 2, 5, 6, 4, false);
    worldCup.add_player(27, 2, 5, 6, 4, false);
    worldCup.add_player(28, 2, 5, 6, 4, false);
    worldCup.add_player(29, 2, 5, 6, 4, false);
    worldCup.add_player(30, 2, 5, 6, 4, false);
    worldCup.add_player(31, 2, 5, 6, 4, false);
    worldCup.add_player(32, 2, 0, 0, 0, false);
    //
    worldCup.add_player(1, 1, 2, 6, 4, true);
    worldCup.add_player(21, 2, 3, 6, 4, true);
    //
    tests += (2 == (worldCup.get_num_played_games(1)).ans());
    tests += (3 == (worldCup.get_num_played_games(21)).ans());
    //
    worldCup.play_match(1, 2);
    tests += (3 == (worldCup.get_num_played_games(1)).ans());
    tests += (4 == (worldCup.get_num_played_games(21)).ans());

    return tests == 4;
}

bool worldCup_Unite_Teams()
{
    world_cup_t worldCup;
    worldCup.add_team(1,1);
    worldCup.add_team(2,3);
    worldCup.add_team(4,5);


    worldCup.add_player(1, 1, 5, 6, 4, true);
    worldCup.add_player(2, 1, 5, 6, 4, false);
    worldCup.add_player(3, 1, 5, 6, 4, false);
    worldCup.add_player(4, 1, 5, 6, 4, false);
    worldCup.add_player(5, 1, 5, 6, 4, false);
    worldCup.add_player(6, 1, 5, 6, 4, false);
    worldCup.add_player(7, 1, 5, 6, 4, false);
    worldCup.add_player(8, 1, 5, 6, 4, false);
    worldCup.add_player(9, 1, 5, 6, 4, false);
    worldCup.add_player(10, 1, 5, 6, 4, false);
    worldCup.add_player(11, 1, 5, 6, 4, false);
    //
    worldCup.add_player(21, 2, 5, 6, 4, true);
    worldCup.add_player(22, 2, 5, 6, 4, false);
    worldCup.add_player(23, 2, 5, 6, 4, false);
    worldCup.add_player(24, 2, 5, 6, 4, false);
    worldCup.add_player(25, 2, 5, 6, 4, false);
    worldCup.add_player(26, 2, 5, 6, 4, false);
    worldCup.add_player(27, 2, 5, 6, 4, false);
    worldCup.add_player(28, 2, 5, 6, 4, false);
    worldCup.add_player(29, 2, 5, 6, 4, false);
    worldCup.add_player(30, 2, 5, 6, 4, false);
    worldCup.add_player(31, 2, 5, 6, 4, false);
    worldCup.add_player(32, 2, 0, 0, 0, false);


    worldCup.unite_teams(1,2,3);
    int team_points = worldCup.get_team_points(3).ans();
    int players_count = worldCup.get_all_players_count(3).ans();

    if (team_points != 1 + 3 || players_count != 11 + 12){
        return false;
    }
    if (not AVL_testing<std::shared_ptr<int>>::run_tests_on_worldCup(&worldCup))
        return false;


    // second test is pretty much the same as the first. just checking if readding is a problem. also adding the same id.
    // also adding a bit more points.
    worldCup.unite_teams(4,3,3);

    worldCup.unite_teams(1,2,3);
    team_points = worldCup.get_team_points(3).ans();
    players_count = worldCup.get_all_players_count(3).ans();

    if (team_points != 1 + 3 + 5 || players_count != 11 + 12){
        return false;
    }
    if (not AVL_testing<std::shared_ptr<int>>::run_tests_on_worldCup(&worldCup))
        return false;

    return true;
}

bool worldCup_Get_All_Players_Count()
{
    int tests = 0;
    world_cup_t worldCup;
    worldCup.add_team(1,1);
    worldCup.add_team(2,3);
    worldCup.add_player(11, 1, 5, 6, 4, false);
    worldCup.add_player(12, 1, 5, 6, 4, false);
    worldCup.add_player(21, 2, 5, 6, 4, false);
    //
    tests += (2 == (worldCup.get_all_players_count(1)).ans());
    tests += (1 == (worldCup.get_all_players_count(2)).ans());
    tests += (3 == (worldCup.get_all_players_count(-1)).ans());
    worldCup.remove_player(12);
    tests += (1 == (worldCup.get_all_players_count(1)).ans());
    tests += (2 == (worldCup.get_all_players_count(-1)).ans());
    return tests == 5;
}

bool closest_player_test() {
//    world_cup_t worldCup;
//    worldCup.add_team(1,1);
//    worldCup.add_team(2,3);
//    worldCup.add_team(4,5);
//
//
//    worldCup.add_player(1, 1, 5, 6, 4, true);
//    worldCup.add_player(2, 1, 5, 6, 4, false);
//    worldCup.add_player(3, 1, 5, 6, 4, false);
//    worldCup.add_player(4, 1, 5, 6, 4, false);
//    worldCup.add_player(5, 1, 5, 6, 4, false);
//    worldCup.add_player(6, 1, 5, 6, 4, false);
//    worldCup.add_player(7, 1, 5, 6, 4, false);
//    worldCup.add_player(8, 1, 5, 6, 4, false);
//    worldCup.add_player(9, 1, 5, 6, 4, false);
//    worldCup.add_player(10, 1, 5, 6, 4, false);
//    worldCup.add_player(11, 1, 5, 6, 4, false);
//    //
//    worldCup.add_player(21, 2, 5, 6, 4, true);
//    worldCup.add_player(22, 2, 5, 6, 4, false);
//    worldCup.add_player(23, 2, 5, 6, 4, false);
//
//    worldCup.add_player(50, 2, 5, 5, 3, false);
//    worldCup.add_player(25, 2, 5, 5, 4, false); //32
//    worldCup.add_player(51, 2, 5, 5, 4, false); //25
//
//    worldCup.add_player(27, 2, 5, 6, 4, false);
//    worldCup.add_player(28, 2, 5, 6, 4, false);
//    worldCup.add_player(29, 2, 5, 6, 4, false);
//    worldCup.add_player(30, 2, 5, 6, 4, false);
//    worldCup.add_player(31, 2, 5, 6, 4, false);
//    worldCup.add_player(32, 2, 0, 0, 0, false);
//
//
//    std::cout << "running tests on closest_player worldcup: \n" << AVL_testing<Player*>::run_tests_on_worldCup(&worldCup);
//    output_t<int> close5 = worldCup.get_closest_player(5,1);
//    output_t<int> close32 = worldCup.get_closest_player(32,2);
//    output_t<int> close25 = worldCup.get_closest_player(25,2);
//    output_t<int> false_id = worldCup.get_closest_player(15,1);
//    output_t<int> false_team = worldCup.get_closest_player(5,2);
//
//    return (close5.ans() == 6 && close32.ans() == 25 && close25.ans() == 51 &&
//
//    close5.status() == StatusType::SUCCESS && close32.status() == StatusType::SUCCESS &&
//    close25.status() == StatusType::SUCCESS && false_id.status() == StatusType::FAILURE &&
//    false_team.status() == StatusType::FAILURE);
    return true;
    // TODO: understand what this is for?
}

bool nodeList_Add()
{
    int tests = 0;
    NodeList list;
    NodeList::Node* p1 = list.add(nullptr, 1, 20, 20, 0);
    std::cout << list.debug_print() << std::endl;
    NodeList::Node* p2 =list.add(p1, 2, 27, 27, 2);
    std::cout << list.debug_print() << std::endl;
    NodeList::Node* p3 =list.add(p1, 3, 18, 18, 0);
    std::cout << list.debug_print() << std::endl;
    NodeList::Node* p4 =list.add(p2, 4, 27, 27, 0);
    std::cout << list.debug_print() << std::endl;
    list.add(p3, 5,19,19,0);
    std::cout << list.debug_print() << std::endl;
    list.add(p4, 6,30,30,0);
    std::cout << list.debug_print() << std::endl;
    tests += ("3 5 1 2 4 6 " == list.debug_print() );

    std::cout << list.debug_print() << std::endl;
    return tests == 1;
}

bool nodeList_Remove()
{
    int tests = 0;
    NodeList list;
    NodeList::Node* p1 = list.add(nullptr, 1, 20, 20, 0);
    NodeList::Node* p2 =list.add(p1, 2, 25, 25, 0);
    NodeList::Node* p3 =list.add(p1, 3, 18, 18, 0);
    NodeList::Node* p4 =list.add(p2, 4, 27, 27, 0);
    NodeList::Node* p5 = list.add(p3, 5, 19, 19, 0);
    NodeList::Node* p6 = list.add(p4, 6, 30, 30, 0);
    tests += ("3 5 1 2 4 6 " == list.debug_print() );
    // Start removing
    list.remove(p5);
    tests += ("3 1 2 4 6 " == list.debug_print() );
    list.remove(p3);
    tests += ("1 2 4 6 " == list.debug_print() );
    list.remove(p6);
    tests += ("1 2 4 " == list.debug_print() );

    NodeList::Node* p3_new = list.add(p1, 3, 10, 10, 0);

    tests += ("3 1 2 4 " == list.debug_print() );
    list.remove(p4);
    tests += ("3 1 2 " == list.debug_print() );
    list.remove(p3_new);
    tests += ("1 2 " == list.debug_print() );
    // std::cout << "Final: " << list.debug_print() << std::endl;
    list.remove(p2);
    tests += ("1 " == list.debug_print() );
    list.remove(p1);
    tests += ("" == list.debug_print() );

    return tests == 9;
}

bool nodeList_Get_Closest()
{
    int tests = 0;
    NodeList list;
    tests += (list.get_closest(nullptr) == 0);
    NodeList::Node* p1 = list.add(nullptr, 1, 0, 1, 0);
    tests += (list.get_closest(p1) == 0);
    NodeList::Node* p2 = list.add(p1, 2, 0, 5, 0);
    NodeList::Node* p3 = list.add(p2, 3, 0, 8, 0);
    NodeList::Node* p4 =list.add(p3, 4, 0, 10, 0);
    list.add(p3, 5, 0, 7, 0);
    list.add(p2, 6, 0, 5, 0);
    tests += ("1 2 6 5 3 4 " == list.debug_print() );

    tests += (list.get_closest(p2) == 6);
    tests += (list.get_closest(p3) == 5);
    tests += (list.get_closest(p4) == 3);

    return tests == 6;
}

bool nodeList_Teams_Basics()
{
    int tests = 0;
    NodeList list;
    list.add(1,20,0,0);
    list.add(3,20,0,0);
    list.add(6,5,0,0);
    list.add(7,30,0,0);
    list.add(10,11,0,0);
    tests += ("1 3 6 7 10 " == list.debug_print() );
    //
    tests += (3 == list.knockout());

    return tests == 2;
}

bool avl_Add_To_List()
{
    int tests = 0;
    NodeList list;
    AVL_tree<Team*> tree1(false); // sort by ID
    Team team1(1, 20);
    Team team2(2, 10);
    Team team3(3, 30);
    Team team4(4, 60);
    Team team5(5, 40);
    Team team6(6, 40);
    Team team7(7, 40);
    Team team8(8, 40);
    tree1.add(&team1);
    tree1.add(&team2);
    tree1.add(&team3);
    tree1.add(&team4);
    tree1.add(&team5);
    tree1.add(&team6);
    tree1.add(&team7);
    tree1.add(&team8);
    //
    std::cout << tree1.debugging_printTree_new();
    //
    tree1.add_to_list(list, 2, 6);
    std::cout << "list: " << list.debug_print() << std::endl;
    tests +=  ("2 3 4 5 6 " == list.debug_print() );
    tests += (4 == list.knockout());

    return tests == 2;
}

bool worldCup_Knockout_Winner()
{
    // Functionality checked using avl_Add_To_List() test
    // This is just for checking that the function runs
    world_cup_t worldCup;

    return (StatusType::FAILURE == (worldCup.knockout_winner(2,3)).status());;
}

bool avl_getClosestLeft()
{
    int tests = 0;
    AVL_tree<std::shared_ptr<Player>> tree1(true); // sort by SCORE
    std::shared_ptr<Player> player4(new Player(4, 2, 1, 4, 0, false));
    std::shared_ptr<Player> player5(new Player(5, 2, 1, 5, 0, false));
    std::shared_ptr<Player> player8(new Player(8, 2, 1, 8, 0, false));
    std::shared_ptr<Player> player6(new Player(6, 2, 1, 6, 0, false));
    std::shared_ptr<Player> player9(new Player(9, 2, 1, 9, 0, false));
    std::shared_ptr<Player> player3(new Player(3, 2, 1, 3, 0, false));
    //

    player4->set_global_score_node(tree1.add(player4));
    player5->set_global_score_node(tree1.add(player5));
    player8->set_global_score_node(tree1.add(player8));
    tests += (*(tree1.find_closest_left(player8->get_global_score_node()))->content).get_id() == 5;
    player6->set_global_score_node(tree1.add(player6));
    player9->set_global_score_node(tree1.add(player9));
    tests += (*(tree1.find_closest_left(player9->get_global_score_node()))->content).get_id() == 8;
    player3->set_global_score_node(tree1.add(player3));
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    //
    tests += (*(tree1.find_closest_left(player6->get_global_score_node()))->content).get_id() == 5;
    tests += (*(tree1.find_closest_left(player5->get_global_score_node()))->content).get_id() == 4;
    tests += (*(tree1.find_closest_left(player9->get_global_score_node()))->content).get_id() == 8;
    tests += (*(tree1.find_closest_left(player4->get_global_score_node()))->content).get_id() == 3;
    tests += (tree1.find_closest_left(player3->get_global_score_node()) == nullptr);
    //

    std::shared_ptr<Player> player10(new Player(10, 2, 1, 10, 0, false));
    std::shared_ptr<Player> player11(new Player(11, 2, 1, 11, 0, false));
    std::shared_ptr<Player> player12(new Player(12, 2, 1, 12, 0, false));
    std::shared_ptr<Player> player13(new Player(13, 2, 1, 13, 0, false));
    player10->set_global_score_node(tree1.add(player10));
    player11->set_global_score_node(tree1.add(player11));
    player12->set_global_score_node(tree1.add(player12));
    player13->set_global_score_node(tree1.add(player13));
    finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    //
    tests += (*(tree1.find_closest_left(player12->get_global_score_node()))->content).get_id() == 11;
    tests += (*(tree1.find_closest_left(player11->get_global_score_node()))->content).get_id() == 10;
    tests += (*(tree1.find_closest_left(player6->get_global_score_node()))->content).get_id() == 5;

    return tests == 10;
}

bool avl_getClosestRight()
{
    int tests = 0;
    AVL_tree<std::shared_ptr<Player>> tree1(true); // sort by SCORE
    std::shared_ptr<Player> player4(new Player(4, 2, 1, 4, 0, false));
    std::shared_ptr<Player> player5(new Player(5, 2, 1, 5, 0, false));
    std::shared_ptr<Player> player8(new Player(8, 2, 1, 8, 0, false));
    std::shared_ptr<Player> player6(new Player(6, 2, 1, 6, 0, false));
    std::shared_ptr<Player> player9(new Player(9, 2, 1, 9, 0, false));
    std::shared_ptr<Player> player3(new Player(3, 2, 1, 3, 0, false));
    //

    player4->set_global_score_node(tree1.add(player4));
    player5->set_global_score_node(tree1.add(player5));
    player8->set_global_score_node(tree1.add(player8));
    tests += (*(tree1.find_closest_right(player4->get_global_score_node()))->content).get_id() == 5;
    player6->set_global_score_node(tree1.add(player6));
    player9->set_global_score_node(tree1.add(player9));
    tests += (*(tree1.find_closest_right(player8->get_global_score_node()))->content).get_id() == 9;
    player3->set_global_score_node(tree1.add(player3));
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    //
    tests += (*(tree1.find_closest_right(player5->get_global_score_node()))->content).get_id() == 6;
    tests += (*(tree1.find_closest_right(player4->get_global_score_node()))->content).get_id() == 5;
    tests += (*(tree1.find_closest_right(player8->get_global_score_node()))->content).get_id() == 9;
    tests += (*(tree1.find_closest_right(player3->get_global_score_node()))->content).get_id() == 4;
    tests += (tree1.find_closest_right(player9->get_global_score_node()) == nullptr);
    //

    std::shared_ptr<Player> player10(new Player(10, 2, 1, 10, 0, false));
    std::shared_ptr<Player> player11(new Player(11, 2, 1, 11, 0, false));
    std::shared_ptr<Player> player12(new Player(12, 2, 1, 12, 0, false));
    std::shared_ptr<Player> player13(new Player(13, 2, 1, 13, 0, false));
    player10->set_global_score_node(tree1.add(player10));
    player11->set_global_score_node(tree1.add(player11));
    player12->set_global_score_node(tree1.add(player12));
    player13->set_global_score_node(tree1.add(player13));
    finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    //
    tests += (*(tree1.find_closest_right(player11->get_global_score_node()))->content).get_id() == 12;
    tests += (*(tree1.find_closest_right(player10->get_global_score_node()))->content).get_id() == 11;
    tests += (*(tree1.find_closest_right(player5->get_global_score_node()))->content).get_id() == 6;
    //
    // Find a closest()
    tests += (*(tree1.find_a_closest(player10->get_global_score_node()))->content).get_id() == 11;
    tests += (*(tree1.find_a_closest(player13->get_global_score_node()))->content).get_id() == 12;
    tests += (*(tree1.find_a_closest(player3->get_global_score_node()))->content).get_id() == 4;
    AVL_tree<std::shared_ptr<Player>> tree2(true); // sort by SCORE
    std::shared_ptr<Player> player20(new Player(20, 2, 1, 10, 0, false));
    player20->set_global_score_node(tree2.add(player20));
    if (player20->get_global_score_node() != nullptr)
        tests += (tree2.find_a_closest(player20->get_global_score_node()) == nullptr);
    std::shared_ptr<Player> player21(new Player(21, 2, 1, 10, 0, false));
    player21->set_global_score_node(tree2.add(player21));
    tests += (*(tree2.find_a_closest(player21->get_global_score_node()))->content).get_id() == 20;

    return tests == 15;
}

bool worldCup_get_closest_player()
{
    int tests = 0;
    world_cup_t worldCup;

    worldCup.add_team(1,0);
    worldCup.add_team(2,0);
    worldCup.add_player(1, 2, 5, 5, 0, false);
    worldCup.add_player(2, 2, 5, 2, 0, false);
    worldCup.add_player(3, 2, 5, 7, 0, false);
    worldCup.add_player(4, 1, 5, 8, 0, false);
    worldCup.add_player(5, 1, 5, 1, 0, false);
    worldCup.add_player(6, 1, 5, 5, 0, false);
    //
    tests += (worldCup.get_closest_player(3,2).ans() == 4);
    tests += (worldCup.get_closest_player(5,1).ans() == 2);

    return tests == 2;

}

bool omeramir_tests_line(){
    std::cout << ("add teams and players - segel test - remove at random stages") << std::endl;
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 10000);
        assert(res == StatusType::SUCCESS);
        res = obj->add_team(2, 20000);
        assert(res == StatusType::SUCCESS);
        res = obj->add_team(3, 30000);
        assert(res == StatusType::SUCCESS);
        res = obj->add_team(4, 40000);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 0, 2, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1006, 1, 10, 4, 3, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1007, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
//
//        std::cout << "test 1 :" <<AVL_testing<Player*>::run_tests_on_worldCup(obj);
//        assert(AVL_testing<Player*>::run_tests_on_worldCup(obj));

        res = obj->remove_player(1007);
        assert(res == StatusType::SUCCESS);

//        std::cout << "test 2 :" <<AVL_testing<Player*>::run_tests_on_worldCup(obj);
//        assert(AVL_testing<Player*>::run_tests_on_worldCup(obj));

        res = obj->remove_player(1002);
        assert(res == StatusType::SUCCESS);

//        std::cout << "test 3 :" <<AVL_testing<Player*>::run_tests_on_worldCup(obj);
//        assert(AVL_testing<Player*>::run_tests_on_worldCup(obj));

        res = obj->add_player(1008, 1, 10, 0, 0, true);
        assert(res == StatusType::SUCCESS);

//        std::cout << "test 4 :" <<AVL_testing<Player*>::run_tests_on_worldCup(obj);
//        assert(AVL_testing<Player*>::run_tests_on_worldCup(obj));

        res = obj->add_player(1009, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1010, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);

//        std::cout << "test 5 :" <<AVL_testing<Player*>::run_tests_on_worldCup(obj);
//        assert(AVL_testing<Player*>::run_tests_on_worldCup(obj));

        //TODO: first leak
        res = obj->add_player(1011, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
//
//        std::cout << "test 6 :" <<AVL_testing<Player*>::run_tests_on_worldCup(obj);
//        assert(AVL_testing<Player*>::run_tests_on_worldCup(obj));

        res = obj->remove_player(1001);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1012, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);

//        std::cout << "test 7 :" <<AVL_testing<Player*>::run_tests_on_worldCup(obj);
//        assert(AVL_testing<Player*>::run_tests_on_worldCup(obj));


        res = obj->add_player(2001, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2002, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2003, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2004, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2005, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(1011);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2006, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2007, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2008, 2, 20, 6, 4, true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2009, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(2001);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2010, 2, 0, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(2011, 2, 20, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(2010);
        assert(res == StatusType::SUCCESS);

        res = obj->add_player(3001, 3, 30, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3002, 3, 30, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3003, 3, 30, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3004, 3, 30, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3005, 3, 30, 2, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3006, 3, 30, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3007, 3, 30, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3008, 3, 30, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3009, 3, 30, 0, 2, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3010, 3, 30, 0, 0, true);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(3011, 3, 30, 0, 0, true);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3011);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3008);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3002);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3010);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3009);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3005);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3004);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3006);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3007);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3001);
        assert(res == StatusType::SUCCESS);
        res = obj->remove_player(3003);
        assert(res == StatusType::SUCCESS);

        res = obj->add_player(4001, 4, 2, 1, 2, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(4002, 4, 2, 2, 2, false);
        assert(res == StatusType::SUCCESS);

        delete obj;
    }

    std::cout <<("get_top_scorer from all 5 players")<< std::endl;
    {
        world_cup_t *obj = new world_cup_t();
        StatusType res = obj->add_team(1, 2);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1001, 1, 10, 15, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1002, 1, 10, 33, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1003, 1, 10, 3, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1004, 1, 10, 20, 0, false);
        assert(res == StatusType::SUCCESS);
        res = obj->add_player(1005, 1, 10, 0, 0, false);
        assert(res == StatusType::SUCCESS);
        output_t<int> resn1 = obj->get_top_scorer(-10);
        assert(resn1.status() == StatusType::SUCCESS);
        assert(resn1.ans() == 1002);

        delete obj;
    }

    std::cout << ("unite teams stuff") << std::endl;
    {
        std::cout << ("unite_teams failure");
        {
            world_cup_t *obj = new world_cup_t();
            StatusType res = obj->unite_teams(1, 2, 1);
            assert(res == StatusType::FAILURE);

            res = obj->add_team(1, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->unite_teams(1, 2, 5);
            assert(res == StatusType::FAILURE);

            res = obj->add_team(2, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(5, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->unite_teams(1, 2, 5);
            assert(res == StatusType::FAILURE);

            delete obj;
        }

        std::cout << ("unite_teams invalid input");
        {
            world_cup_t *obj = new world_cup_t();
            StatusType res = obj->unite_teams(0, 1, 1);
            assert(res == StatusType::INVALID_INPUT);
            res = obj->unite_teams(1, 0, 1);
            assert(res == StatusType::INVALID_INPUT);
            res = obj->unite_teams(1, 2, 0);
            assert(res == StatusType::INVALID_INPUT);
            res = obj->unite_teams(-1, 1, 1);
            assert(res == StatusType::INVALID_INPUT);
            res = obj->unite_teams(1, -1, 1);
            assert(res == StatusType::INVALID_INPUT);
            res = obj->unite_teams(1, 3, -1);
            assert(res == StatusType::INVALID_INPUT);
            res = obj->unite_teams(1, 1, 1);
            assert(res == StatusType::INVALID_INPUT);

            delete obj;
        }

        std::cout << ("unite_teams simple");
        {
            world_cup_t *obj = new world_cup_t();
            StatusType res = obj->add_team(1, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1001, 1, 1, 5, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(2, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1002, 2, 1, 3, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->unite_teams(1, 2, 3);
            assert(res == StatusType::SUCCESS);
            int players[10] = {};
            res = obj->get_all_players(3, players);
            assert(res == StatusType::SUCCESS);
            assert(players[0] == 1002);
            assert(players[1] == 1001);
            assert(players[2] == 0);
            assert(players[3] == 0);
            assert(players[4] == 0);
            assert(players[5] == 0);
            assert(players[6] == 0);
            assert(players[7] == 0);
            assert(players[8] == 0);
            assert(players[9] == 0);

            res = obj->add_team(3, 2);
            assert(res == StatusType::FAILURE);
            res = obj->add_team(1, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(2, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(4, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1001, 3, 1, 5, 2, true);
            assert(res == StatusType::FAILURE);
            res = obj->add_player(1002, 3, 1, 3, 4, false);
            assert(res == StatusType::FAILURE);
            res = obj->add_player(1003, 3, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1004, 4, 1, 1, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1005, 4, 1, 1, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1006, 4, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1007, 4, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->unite_teams(3, 4, 5);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(5, 2);
            assert(res == StatusType::FAILURE);
            res = obj->add_team(3, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(4, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1008, 3, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1004, 3, 1, 1, 1, false);
            assert(res == StatusType::FAILURE);
            res = obj->add_player(1009, 4, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1005, 4, 1, 1, 1, false);
            assert(res == StatusType::FAILURE);
            res = obj->unite_teams(3, 4, 3);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(3, 2);
            assert(res == StatusType::FAILURE);

            res = obj->add_team(4, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1009, 3, 1, 1, 1, false);
            assert(res == StatusType::FAILURE);

            delete obj;
        }

        std::cout << ("unite_teams that makes it legal team");
        {
            world_cup_t *obj = new world_cup_t();

            StatusType res = obj->add_team(1, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1001, 1, 1, 5, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1002, 1, 1, 3, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1003, 1, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1004, 1, 1, 1, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1005, 1, 1, 1, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(2, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1006, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1007, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1008, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1009, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1010, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1011, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1012, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1013, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1014, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1015, 2, 1, 1, 1, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1016, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1017, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            output_t<int> resn3 = obj->knockout_winner(1, 4);
            assert(resn3.status() == StatusType::SUCCESS);
            assert(resn3.ans() == 2);

            res = obj->unite_teams(1, 2, 3);
            assert(res == StatusType::SUCCESS);

            output_t<int> resn1 = obj->get_all_players_count(3);
            assert(resn1.status() == StatusType::SUCCESS);
            assert(resn1.ans() == 17);
            output_t<int> resn2 = obj->knockout_winner(1, 4);
            assert(resn2.status() == StatusType::SUCCESS);
            assert(resn2.ans() == 3);

            delete obj;
        }

        std::cout << ("unite_teams two legal teams");
        {
            world_cup_t *obj = new world_cup_t();

            StatusType res = obj->add_team(1, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1001, 1, 1, 5, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1002, 1, 1, 3, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1003, 1, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1004, 1, 1, 1, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1005, 1, 1, 1, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1301, 1, 1, 5, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1302, 1, 1, 3, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1303, 1, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1304, 1, 1, 1, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1305, 1, 1, 1, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(101, 1, 1, 5, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(333, 1, 1, 3, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(103, 1, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(6004, 1, 1, 1, 2, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(19005, 1, 1, 1, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(2, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1006, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1007, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1008, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1009, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1010, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1011, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1012, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1013, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1014, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1015, 2, 1, 1, 1, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1016, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1017, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            output_t<int> resn3 = obj->knockout_winner(1, 4);
            assert(resn3.status() == StatusType::SUCCESS);
            assert(resn3.ans() == 2);

            res = obj->unite_teams(1, 2, 3);
            assert(res == StatusType::SUCCESS);

            output_t<int> resn1 = obj->get_all_players_count(3);
            assert(resn1.status() == StatusType::SUCCESS);
            assert(resn1.ans() == 27);
            output_t<int> resn2 = obj->knockout_winner(1, 4);
            assert(resn2.status() == StatusType::SUCCESS);
            assert(resn2.ans() == 3);

            delete obj;
        }

        std::cout << ("unite_teams legal and not legal teams to the not legal");
        {
            world_cup_t *obj = new world_cup_t();

            StatusType res = obj->add_team(1, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1001, 1, 1, 5, 2, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1002, 1, 1, 3, 4, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1003, 1, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_team(2, 2);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1006, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1007, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1008, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1009, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1010, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1011, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1012, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1013, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1014, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1015, 2, 1, 1, 1, true);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1016, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            res = obj->add_player(1017, 2, 1, 1, 1, false);
            assert(res == StatusType::SUCCESS);
            output_t<int> resn3 = obj->knockout_winner(1, 4);
            assert(resn3.status() == StatusType::SUCCESS);
            assert(resn3.ans() == 2);

            res = obj->unite_teams(1, 2, 1);
            assert(res == StatusType::SUCCESS);

            output_t<int> resn1 = obj->get_all_players_count(1);
            assert(resn1.status() == StatusType::SUCCESS);
            assert(resn1.ans() == 15);
            output_t<int> resn2 = obj->knockout_winner(1, 4);
            assert(resn2.status() == StatusType::SUCCESS);
            assert(resn2.ans() == 1);

            delete obj;
        }
    }


    return true;
}


bool worldCup_get_closest_player_extended()
{
    // TODO: Erase after finish debugging
    return true;
}
