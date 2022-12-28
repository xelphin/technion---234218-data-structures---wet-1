////
//// Created by Administrator on 04/12/2022.
////

#include "NodeList.h"

NodeList::NodeList() : start(nullptr), end(nullptr)
{}

NodeList::~NodeList() {
    NodeList::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList::Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}

void NodeList::add(int id, int total_points, int total_goals, int total_cards)
{
    // O(1)
    NodeList::Node* newNode = new NodeList::Node(id, total_points, total_goals, total_cards);
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

NodeList::Node* NodeList::add(Node* nodeNextTo, int id, int total_points, int total_goals, int total_cards)
{
    NodeList::Node* newNode = new NodeList::Node(id, total_points, total_goals, total_cards);
    // Empty list
    if (nodeNextTo == nullptr) { // empty list
        if (start != nullptr || end != nullptr) {
            std::cout << "mistake" << std::endl;
            return nullptr;
        }
        start = newNode;
        end = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }
    // Not empty
    bool nodeNextTo_BiggerScorer = player1_biggerScorer(*nodeNextTo, *newNode);

    if (nodeNextTo_BiggerScorer) { // prevNode < newNode < nodeNextTo
        NodeList::Node* prevNode = nodeNextTo->prev;
        if (prevNode != nullptr) {
            prevNode->next = newNode;
        } else {

            start = newNode;
        }
        newNode->prev = prevNode;
        newNode->next = nodeNextTo;
        nodeNextTo->prev = newNode;
    } else { // nodeNextTo < newNode < postNode
        NodeList::Node* postNode = nodeNextTo->next;
        if (postNode != nullptr)
            postNode->prev = newNode;
        else {
            end = newNode;
        }
        newNode->next = postNode;
        newNode->prev = nodeNextTo;
        nodeNextTo->next = newNode;
    }
    return newNode;
}

void NodeList::remove(Node* node)
{
    if (node == nullptr)
        return;
    NodeList::Node* prevNode = node->prev;
    NodeList::Node* nextNode = node->next;
    // ONE NODE
    if (prevNode == nullptr && nextNode == nullptr) {
        if (start != end && start != nullptr) {
            std::cout << "ERROR!" << std::endl;
            return;
        }
        delete node;
        start = nullptr;
        end = nullptr;
        return;
    }
    // node == start
    if (prevNode == nullptr) {
        if (start != node) {
            std::cout << "ERROR!" << std::endl;
            return;
        }
        start = nextNode;
        if (start == nullptr)
            std::cout << "ERROR!" << std::endl;
        nextNode->prev = nullptr;
        delete node;
        return;
    }
    // node == end
    if (nextNode == nullptr) {
        if (end != node) {
            std::cout << "ERROR2!" << std::endl;
            return;
        }
        end = prevNode;
        prevNode->next = nullptr;
        delete node;
        return;
    }
    // node is in middle
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete node;
}

int NodeList::knockout() // O(r)
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

void NodeList::call_match() // O(current amount of teams playing)
{
    // empty
    if (start == nullptr || end == nullptr)
        return;
    // only one node
    if (start == end)
        return;
    // Play matches
    NodeList::Node* prevNode = this->start;
    NodeList::Node* team1 = this->start;
    NodeList::Node* team2 = team1->next;
    NodeList::Node* nextNode;
    if (team2 !=nullptr)
        nextNode = team2->next;

    while (team1 && team2) { // prevNode -> team1 -> team2 -> nextNode
        int winnerId = get_winnerId(*team1, *team2);
        //std::cout << "Match: " << (team1->id) << " :: " << (team2->id) << " winner: " << (winnerId) << std::endl;
        // Create new node
        NodeList::Node* newNode = new NodeList::Node(winnerId,
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
        //std::cout << "list: " << (this->debug_print()) << std::endl;
    }
    //std::cout << "list end: " << (this->debug_print()) << std::endl;
}

int NodeList::get_winnerId(Node& team1, Node& team2)
{
    int winnerId = 0;
    if (team1.get_match_points() > team2.get_match_points()) {
        winnerId = team1.id;
    } else if (team2.get_match_points() > team1.get_match_points()) {
        winnerId = team2.id;
    } else if (team1.id > team2.id){
        winnerId = team1.id;
    } else {
        winnerId = team2.id;
    }
    return winnerId;
}

int NodeList::get_closest(Node* node) const
{
    if (node == nullptr)
        return 0;
    NodeList::Node* prev = node->prev;
    NodeList::Node* next = node->next;
    if (prev == nullptr && next == nullptr)
        return 0;
    if (prev == nullptr)
        return next->get_id();
    if (next == nullptr)
        return prev->get_id();

    // Both nodes exist
    if (abs(prev->total_goals - node->total_goals) > abs(next->total_goals - node->total_goals))
        return next->get_id();
    if (abs(prev->total_goals - node->total_goals) < abs(next->total_goals - node->total_goals))
        return prev->get_id();
    if (abs(prev->total_cards - node->total_cards) > abs(next->total_cards - node->total_cards))
        return next->get_id();
    if (abs(prev->total_cards - node->total_cards) < abs(next->total_cards - node->total_cards))
        return prev->get_id();
    if (abs(prev->id - node->id) > abs(next->id - node->id))
        return next->get_id();
    if (abs(prev->id - node->id) < abs(next->id - node->id))
        return prev->get_id();
    if (prev->id > next->id)
        return prev->get_id();
    if (prev->id < next->id)
        return next->get_id();
    return 0;
}

bool NodeList::player1_biggerScorer(Node& player1, Node& player2)
{
    if (player1.total_goals > player2.total_goals)
        return true;
    if (player1.total_goals < player2.total_goals)
        return false;
    if (player1.total_cards > player2.total_cards)
        return false;
    if (player1.total_cards < player2.total_cards)
        return true;
    if ((player1.id > player2.id))
        return true;
    return false;
}

NodeList::Node::Node(int id, int total_points, int total_goals, int total_cards)
        : prev(nullptr), next(nullptr), id(id), total_points(total_points), total_goals(total_goals), total_cards(total_cards)
        {}

int NodeList::Node::get_match_points() const
{
    return total_points + total_goals - total_cards;
}

int NodeList::Node::get_id() const
{
    return this->id;
}