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
    printSuccess();
    std::cout << std::endl;
}


// ----------------------------- TESTS -----------------------------


bool playerCompare()
{
    int count = 0;

    Player player1(1, 2, 5, 6, 4, false); // goals == 6
    Player player2(2, 2, 5, 4, 4, false); // goals == 4

    if (player1.compare(player2, SORT_BY_SCORE) == AVL_tree<Player>::COMPARISON::A_BIGGER_THAN_B)
        count++;
    if (player1.compare(player2, SORT_BY_ID) == AVL_tree<Player>::COMPARISON::A_SMALLER_THAN_B)
        count++;

    return count == 2;
}