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
        delete currentNode;
        currentNode = nextNode;
    }
    if (end)
        delete end;
}

NodeList_Teams::Node::Node(int id, int total_points, int total_goals, int total_cards)
        : next(nullptr), id(id), total_points(total_points), total_goals(total_goals), total_cards(total_cards){}