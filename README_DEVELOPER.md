# NOTES

# RUN code

g++ -std=c++11 -DNDEBUG -Wall *.cpp

valgrind --leak-check=full ./a.out

## CURRENT

Functions: int get_comparison(const Node &other)

needs to be tested, called from:

typename AVL_tree<T>::Node* AVL_tree<T>::add(T item)

commented out so that code will work