//
// Created by Administrator on 04/12/2022.
//

#include "NodeList_Teams.h"

NodeList_Teams::NodeList_Teams() : start(nullptr), end(nullptr)
{}

NodeList_Teams::~NodeList_Teams() {
    NodeList_Teams::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList_Teams::Node* nextNode = currentNode->next;
        std::cout << "deleting: " << (currentNode->id) << std::endl;
        delete currentNode;
        currentNode = nextNode;
    }
    if (end)
        delete end;
}

void NodeList_Teams::add(int id, int total_points, int total_goals, int total_cards)
{
    // O(1)
    Node* newNode = new Node(id, total_points, total_goals, total_cards);
    // List is empty:
    if (start == nullptr) {
        start = newNode;
        end = newNode;
    } else {
    // List not empty:
        if (end == nullptr)
            throw;
        end->next = newNode;
        end = newNode; // update end to point at most recent node addition
    }
}

std::string NodeList_Teams::debug_print()
{
    std::string str = "";
    NodeList_Teams::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList_Teams::Node* nextNode = currentNode->next;
        str += std::to_string(currentNode->id) + " ";
        currentNode = nextNode;
    }
    return str;
}

NodeList_Teams::Node::Node(int id, int total_points, int total_goals, int total_cards)
        : next(nullptr), id(id), total_points(total_points), total_goals(total_goals), total_cards(total_cards){}