#pragma once

#include "gladiator.h"
#include <algorithm>
#include <vector>
#include <valgrind/memcheck.h>

extern Gladiator *gladiator;

namespace navigation {
    class Node {
    private:
        MazeSquare *_square;
        Node *_parent;
        int16_t _g;
        int16_t _h;

    public:
        explicit Node(MazeSquare *square) : _square(square), _parent(nullptr), _g(0), _h(0) {}
        explicit Node(MazeSquare *square, Node *parent) : _square(square), _parent(parent), _g(0), _h(0) {}
        ~Node() = default;

        bool operator==(const Node &node) const {
            return this->_square == node._square;
        }

        MazeSquare *getSquare() const {
            return this->_square;
        }

        Node *getParent() const {
            return this->_parent;
        }

        void setParent(Node *parent) {
            this->_parent = parent;
        }

        int16_t getG() const {
            return this->_g;
        }

        void setG(int16_t g) {
            this->_g = g;
        }

        int16_t getH() const {
            return this->_h;
        }

        void setH(int16_t h) {
            this->_h = h;
        }

        int16_t getF() const {
            return this->_g + this->_h;
        }

        std::vector<Node *> getNeighbours() {
            std::vector<Node *> neighbours;
            if (this->_square->northSquare != nullptr) {
                neighbours.push_back(new Node(this->_square->northSquare, this));
            }
            if (this->_square->southSquare != nullptr) {
                neighbours.push_back(new Node(this->_square->southSquare, this));
            }
            if (this->_square->eastSquare != nullptr) {
                neighbours.push_back(new Node(this->_square->eastSquare, this));
            }
            if (this->_square->westSquare != nullptr) {
                neighbours.push_back(new Node(this->_square->westSquare, this));
            }
            return neighbours;
        }
    };

    class PathFinder {
    public:
        static int16_t getLeastF(std::vector<Node *> &openList) {
            int16_t leastFIndex = 0;
            for (uint16_t i = 0; i < openList.size(); i++) {
                if (openList[i]->getF() <= openList[leastFIndex]->getF()) {
                    leastFIndex = i;
                }
            }
            return leastFIndex;
        }

        static int16_t getManhattanDistance(MazeSquare *start, MazeSquare *end) {
            return abs(start->i - end->i) + abs(start->j - end->j);
        }

        static void modifyNode(std::vector<Node *>& openList, Node* successor) {
            for (auto& node: openList) {
                if (node->getSquare() == successor->getSquare() && node->getF() > successor->getF()) {
                    *node = *successor;
                    return;
                }
            }
            openList.push_back(successor);
        }

        static std::vector<MazeSquare *> reconstructPath(Node *node) {
            std::vector<MazeSquare *> path;
            while (node != nullptr) {
                path.push_back(node->getSquare());
                node = node->getParent();
            }
            return path;
        }

        static std::vector<MazeSquare *> findPath(MazeSquare *start, MazeSquare *goal) {
            std::vector<Node *> openList;
            std::vector<Node *> closedList;

            openList.push_back(new Node(start));
            uint16_t iteration = 0;
            while (!openList.empty()) {
                auto index = getLeastF(openList);
                auto q = openList[index];
                openList.erase(openList.cbegin() + index);
                closedList.push_back(q);
                if (q->getSquare() == goal) {
                    gladiator->log("Path found on %d iterations", iteration);
                    return reconstructPath(q);
                }
                auto successors = q->getNeighbours();

                for (auto successor: successors) {
                    if (std::find(closedList.begin(), closedList.end(), successor) != closedList.end()) {
                        continue;
                    }
                    successor->setG(q->getG() + 1);
                    successor->setH(getManhattanDistance(successor->getSquare(), goal));
                    modifyNode(openList, successor);
                }
                iteration++;
            }
            gladiator->log("No path found on %u iteration\n", iteration);
            return std::vector<MazeSquare *>();
        };
    };
};

        /*static bool lowerF(std::vector<Node>& openList, Node& successor) {
            for (auto& node: openList) {
                if (node.getSquare() == successor.getSquare() && node.getF() < successor.getF()) {
                    return true;
                }
            }
            return false;
        }

        static void addNode(std::vector<Node>& openList, std::vector<Node>& closedList, Node& successor) {
            for (auto& node: closedList) {
                if (node.getSquare() == successor.getSquare()) {
                    if (node.getF() < successor.getF()) {
                        return;
                    } else {
                        openList.push_back(node);
                    }
                }
            }
        }*/

