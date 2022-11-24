# NOTES

## RUN code

g++ -std=c++11 -DNDEBUG -Wall *.cpp

valgrind --leak-check=full ./a.out

## TODO

- AVL_tree: Implement remove functions + tests
- AVL_tree: Implement search/find_id/return functions + tests
- AVL_tree: Implement exceptions (case enter node that has same id/score as another...)
- Team: Implement + tests
- Player: Update to have Team pointer + Update tests (c'tor of Player in tests doesnt have *Team)

-----

- Implement functions from worldcup23a1.h
