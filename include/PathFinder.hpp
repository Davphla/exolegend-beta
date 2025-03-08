#pragma once

#include "gladiator.h"
#include <algorithm>
#include <deque>
#include <memory>
#include <unordered_map>
#include <vector>


extern Gladiator *gladiator;

namespace navigation {
    class Node {
    private:
        MazeSquare *_square;
        std::shared_ptr<Node> _parent;
        int16_t _g;
        int16_t _h;

    public:
        explicit Node(MazeSquare *square) : _square(square), _parent(nullptr), _g(0), _h(0) {}
        explicit Node(MazeSquare *square, std::shared_ptr<Node> parent) : _square(square), _parent(parent), _g(0), _h(0) {}
        ~Node() = default;

        bool operator==(const Node &node) const {
            return this->_square == node._square;
        }

        MazeSquare *getSquare() const {
            return this->_square;
        }

        std::shared_ptr<Node> getParent() const {
            return this->_parent;
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
    };

    class PathFinder {
    public:
        PathFinder() = delete;

        static std::unordered_map<MazeSquare *, std::shared_ptr<Node>> getNeighbours(std::shared_ptr<Node> node) {
            std::unordered_map<MazeSquare* ,std::shared_ptr<Node>> neighbours;
            if (node->getSquare()->northSquare != nullptr) {
                neighbours[node->getSquare()->northSquare] = std::make_shared<Node>(node->getSquare()->northSquare, node);
            }
            if (node->getSquare()->southSquare != nullptr) {
                neighbours[node->getSquare()->southSquare] = std::make_shared<Node>(node->getSquare()->southSquare, node);
            }
            if (node->getSquare()->eastSquare != nullptr) {
                neighbours[node->getSquare()->eastSquare] = std::make_shared<Node>(node->getSquare()->eastSquare, node);
            }
            if (node->getSquare()->westSquare != nullptr) {
                neighbours[node->getSquare()->westSquare] = std::make_shared<Node>(node->getSquare()->westSquare, node);
            }
            return neighbours;
        }

        static auto getLeastF(std::unordered_map<MazeSquare *, std::shared_ptr<Node>> &openList) {
            auto leastFIndex = openList.begin();
            for (auto it = openList.begin(); it != openList.end(); it++) {
                if (it->second->getF() <= it->second->getF()) {
                    leastFIndex = it;
                }
            }
            return leastFIndex;
        }

        static int16_t getManhattanDistance(MazeSquare *start, MazeSquare *end) {
            return abs(start->i - end->i) + abs(start->j - end->j);
        }

        static void modifyNode(std::vector<std::shared_ptr<Node>>& openList, std::shared_ptr<Node> successor) {
            for (auto& node: openList) {
                if (node->getSquare() == successor->getSquare() && node->getF() > successor->getF()) {
                    *node = *successor;
                    return;
                }
            }
            openList.push_back(successor);
        }

        static std::deque<MazeSquare *> reconstructPath(std::shared_ptr<Node> node) {
            std::deque<MazeSquare *> path;
            while (node != nullptr) {
                path.push_back(node->getSquare());
                node = node->getParent();
            }
            return path;
        }

        static std::deque<MazeSquare *> findPath(MazeSquare *start, MazeSquare *goal) {
            std::unordered_map<MazeSquare *, std::shared_ptr<Node>> openList;
            std::unordered_map<MazeSquare *, std::shared_ptr<Node>> closedList;

            openList[start] = std::make_shared<Node>(start);
            uint16_t iteration = 0;
            while (!openList.empty()) {
                auto it = getLeastF(openList);
                auto* ms = it->first;
                auto q = it->second;
                openList.erase(it);
                closedList[ms] = q;
                if (q->getSquare() == goal) {
                    gladiator->log("Path found on %d iterations", iteration);
                    return reconstructPath(q);
                }
                auto successors = getNeighbours(q);

                for (auto [successorMS, successorQ]: successors) {
                    if (closedList.find(successorMS) != closedList.end()) {
                        continue;
                    }
                    if (successorMS == goal) {
                        gladiator->log("Path found on %d iterations", iteration);
                        return reconstructPath(successorQ);
                    }
                    successorQ->setG(q->getG() + 1);
                    successorQ->setH(getManhattanDistance(successorQ->getSquare(), goal));
                    if (auto it = openList.find(successorMS); it != openList.end() && it->second->getF() < successorQ->getF()) {
                        continue;
                    }
                    if (auto it = closedList.find(successorMS); it != closedList.end() && it->second->getF() < successorQ->getF()) {
                        continue;
                    } else {
                        openList[successorMS] = successorQ;
                    }
                }
                iteration++;
            }
            gladiator->log("No path found on %u iteration\n", iteration);
            return std::deque<MazeSquare *>();
        };
    };
};
