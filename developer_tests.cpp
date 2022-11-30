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

    if (!(player1) - !(player2) > 0)
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
    std::cout << tree1.debugging_printTree();
    tree1.add(&player2);
    std::cout << tree1.debugging_printTree();
    tree1.add(&player3);
    std::cout << tree1.debugging_printTree();
    tree1.add(&player4);

    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──4\n    ├──1\n    │   └──3\n    └──7\n";
    tests += treeCompare(finalTree,wantedTree);

    std::cout << "amount of nodes " << std::to_string(tree1.get_amount()) << std::endl;
    tests += (tree1.get_amount() == 4);

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
    std::cout << tree1.debugging_printTree();
    //
    tree1.add(&player5);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──7\n    ├──4\n    │   ├──3\n    │   │   ├──2\n    │   └──6";
    wantedTree += "\n    │       ├──5\n    └──10\n        ├──8\n        └──20\n            └──21\n";
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
    std::cout << tree1.debugging_printTree();
    //
    tree1.add(&player19);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──15\n    ├──10\n    │   ├──5\n    │   │   ├──4\n    │   │   └──6\n    │   └──12\n    └──20\n        ├──18";
    wantedTree += "\n        │   └──19\n        └──30\n            ├──25\n            └──40\n";
    return treeCompare(finalTree,wantedTree);
}

bool inorder_print(){
    // TODO: Update function so that it puts values into array
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
    tree1.debugging_printTree();
    //
    tree1.add(&player19);

    std::cout << "inorder traversal print: \n";

    // TODO: Check function actually works
    int arrSize = tree1.get_amount();
    Player **arrTree = new Player *[arrSize];
    tree1.debugging_printTree();
    tree1.in_order_traversal_wrapper(arrTree, arrSize);
    std::cout << "CHECKING INORDER --------------------------------------------------------------------------" << std::endl;
    std::string myOutput = "";
    for(int i=0; i< arrSize; i++) {
        if (arrTree[i]!=nullptr) {
            myOutput += std::to_string(arrTree[i]->get_id()) + " ";
        }
    }
    std::cout << std::endl;
    delete[] arrTree;
    std::cout << tree1.debugging_printTree(); // TODO: make sure my tree isn't deleted

    return myOutput.compare( "4 5 6 10 12 15 18 19 20 25 30 40 ") == 0;


}

bool inorder_print_check2(){
    // TODO: Update function so that it puts values into array
    AVL_tree<Player*> tree1(false); // sort by ID
    Player player2(2, 2, 3, 3, 4, false);
    Player player5(5, 2, 3, 3, 4, false);
    Player player6(6, 2, 3, 3, 4, false);
    tree1.add(&player2);
    tree1.add(&player5);
    tree1.add(&player6);

    int arrSize = tree1.get_amount();
    Player **arrTree = new Player *[arrSize];
    tree1.debugging_printTree();
    tree1.in_order_traversal_wrapper(arrTree, arrSize);
    std::cout << "CHECKING INORDER --------------------------------------------------------------------------" << std::endl;
    std::string myOutput = "";
    for(int i=0; i< arrSize; i++) {
        if (arrTree[i]!=nullptr) {
            myOutput += std::to_string(arrTree[i]->get_id()) + " ";
        }
    }
    std::cout << myOutput << std::endl;
    delete[] arrTree;

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
    AVL_tree<Player*> tree1(false); // sort by ID
    AVL_tree<Player*> tree2(false); // sort by ID
    Player player1(1, 2, 5, 6, 4, false);
    Player player2(2, 2, 5, 6, 4, false);
    Player player3(3, 2, 3, 3, 4, false);
    Player player4(4, 2, 3, 3, 4, false);
    Player player5(5, 2, 3, 3, 4, false);
    Player player6(6, 2, 3, 3, 4, false);
    Player player7(7, 2, 3, 3, 4, false);
    Player player8(8, 2, 3, 3, 4, false);

    tree1.add(&player1);
    tree1.add(&player3);
    tree1.add(&player4);
    tree1.add(&player7);

    tree2.add(&player2);
    tree2.add(&player5);
    tree2.add(&player6);
    tree2.add(&player8);
    std::cout << tree1.debugging_printTree();
    std::cout << tree2.debugging_printTree();
    //
    AVL_tree<Player*> tree(tree1, tree2, false);
    std::cout << tree.debugging_printTree();
    std::string finalTree = tree.debugging_printTree();

    std::string wantedTree = "└──4\n    ├──2\n    │   ├──1\n    │   └──3\n    └──6\n        ├──5\n        └──7\n            └──8\n";
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
    worldCup.add_team(1,1);
    worldCup.add_team(2,1);
    worldCup.add_team(4,2);
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
    tests += StatusType::FAILURE == worldCup.play_match(1, 4);
    //tests += StatusType::FAILURE == worldCup.play_match(1, 5);
    //worldCup.remove_player(21);
    //tests += StatusType::FAILURE == worldCup.play_match(1, 2);
    //worldCup.add_player(33, 2, 5, 6, 0, true);
    //tests += StatusType::SUCCESS == worldCup.play_match(1, 2);

    // TODO: Checked a bit with prints, but difficult to check directly because no public function gives me direct access to Team pointer
    return tests == 2;
}