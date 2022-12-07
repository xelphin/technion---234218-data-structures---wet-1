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
        newNode->prev = end;
        end = newNode; // update end to point at most recent node addition
    }
}

NodeList_Teams::Node* NodeList_Teams::add(Node* nodeNextTo, int id, int total_points, int total_goals, int total_cards)
{
    Node* newNode = new Node(id, total_points, total_goals, total_cards);
    // Empty list
    if (nodeNextTo == nullptr) { // empty list
        if (start != nullptr || end != nullptr) {
            std::cout << "mistake" << std::endl;
            return nullptr;
        }
        std::cout << "adding " << (id) << " to empty list" << std::endl;
        start = newNode;
        end = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        std::cout << "list: " << (this->debug_print()) << std::endl;
        return newNode;
    }
    // Not empty
    int winnerId = get_winnerId(*nodeNextTo, *newNode);
    if (winnerId == nodeNextTo->get_id()) { // prevNode < newNode < nodeNextTo
        std::cout << "Entering " << (id) << " before " << (nodeNextTo->get_id()) << std::endl;
        NodeList_Teams::Node* prevNode = nodeNextTo->prev;
        if (prevNode != nullptr) {
            prevNode->next = newNode;
        } else {
            std::cout << "Made " << (id) << " start of list" << std::endl;
            start = newNode;
        }
        newNode->prev = prevNode;
        newNode->next = nodeNextTo;
        nodeNextTo->prev = newNode;
    } else { // nodeNextTo < newNode < postNode
        NodeList_Teams::Node* postNode = nodeNextTo->next;
        if (postNode != nullptr)
            postNode->prev = newNode;
        else {
            std::cout << "Made " << (id) << " end of list" << std::endl;
            end = newNode;
        }
        newNode->next = postNode;
        newNode->prev = nodeNextTo;
        nodeNextTo->next = newNode;
    }
    std::cout << "list: " << (this->debug_print()) << std::endl;
    return newNode;
}

int NodeList_Teams::knockout() // O(r)
{
    if (start == nullptr || end == nullptr)
        return -1;
    while (start != end) {
        this->call_match();
    }
    if (start != nullptr && end!=nullptr && start == end) {
        return (start->id);
    }
    return 0;
}

void NodeList_Teams::call_match() // O(current amount of teams playing)
{
    // empty
    if (start == nullptr || end == nullptr)
        return;
    // only one node
    if (start == end)
        return;
    // Play matches
    NodeList_Teams::Node* prevNode = this->start;
    NodeList_Teams::Node* team1 = this->start;
    NodeList_Teams::Node* team2 = team1->next;
    NodeList_Teams::Node* nextNode;
    if (team2 !=nullptr)
        nextNode = team2->next;

    while (team1 && team2) { // prevNode -> team1 -> team2 -> nextNode
        int winnerId = get_winnerId(*team1, *team2);
        std::cout << "Match: " << (team1->id) << " :: " << (team2->id) << " winner: " << (winnerId) << std::endl;
        // Create new node
        Node* newNode = new Node(winnerId,
                                 team1->total_points + team2->total_points + 3,
                                 team1->total_goals + team2->total_goals,
                                 team1->total_cards + team2->total_cards);
        // Arrange list
        try {
            prevNode->next = newNode;
            newNode->next = nextNode;
            if (start == team1)
                start = newNode;
            if (end == team2)
                end = newNode;
        } catch(...) {
            delete team1;
            delete team2;
            throw;
        }
        // Delete old teams
        delete team1;
        delete team2;

        // Update for match of next two teams
        prevNode = newNode;
        if (nextNode == nullptr)
            break;
        team1 = nextNode;
        team2 = team1->next;
        if (team2 == nullptr)
            break;
        nextNode = team2->next;

        // debug
        std::cout << "list: " << (this->debug_print()) << std::endl;
    }
    std::cout << "list end: " << (this->debug_print()) << std::endl;
}

int NodeList_Teams::get_winnerId(Node& team1, Node& team2)
{
    int winnerId = 0;
    if (team1.get_match_points() > team2.get_match_points()) {
        winnerId = team1.id;
    } else if (team1.get_match_points() > team2.get_match_points()) {
        winnerId = team2.id;
    } else if (team1.id > team2.id){
        winnerId = team1.id;
    } else {
        winnerId = team2.id;
    }
    return winnerId;
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
        : next(nullptr), id(id), total_points(total_points), total_goals(total_goals), total_cards(total_cards)
        {}

int NodeList_Teams::Node::get_match_points() const
{
    return total_points + total_goals - total_cards;
}

int NodeList_Teams::Node::get_id() const
{
    return this->id;
}