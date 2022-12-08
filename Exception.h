//
// Created by Administrator on 26/11/2022.
//

#ifndef AVL_TREE_H_EXCEPTION_H
#define AVL_TREE_H_EXCEPTION_H

#include <exception>

class ID_ALREADY_EXISTS : public std::exception {
public:
    const char* what() const noexcept override {
        return "Id already exists in AVL tree";
    }
};

class ID_DOES_NOT_EXIST : public std::exception {
public:
    const char* what() const noexcept override {
        return "Id does not exist in AVL tree";
    }
};

class IDENTICAL_IDS : public std::exception {
public:
    const char* what() const noexcept override {
        return "both IDs where identical. excepted two different objects and received the same one.";
    }
};

#endif //AVL_TREE_H_EXCEPTION_H
