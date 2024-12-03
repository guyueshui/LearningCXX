#ifndef _A_STAR_H_
#define _A_STAR_H_

#include <vector>
#include <queue>

class Node
{
public:
    int val_;

private:
    Node* parent_;
};


class AStar
{
    typedef std::vector vector;
    typedef int a;
public:
    AStar() = default;
    AStar(const AStar&) = delete;
    AStar operator=(const AStar&) = delete;
    AStar(AStar&&) = delete;
    AStar operator=(AStar&&) = delete;

    void FindPath(const Node& start, const Node& end);
    void FindPath(const Node& start, const Node& end, const s);


private:
    std::priority_queue<Node> open_set_;
    std::vector<Node> close_set_;
};

#endif /* ifndef _A_STAR_H_ */
