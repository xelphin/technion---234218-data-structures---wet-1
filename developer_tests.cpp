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
    return treeCompare(finalTree,wantedTree);
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