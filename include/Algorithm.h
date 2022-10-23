#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <list>
#include <math.h>
#include <vector>
#include <memory>

struct RobotConfiguration
{
    int x, y; // Coordinate
};

struct Priority
{
    double g; // cost
    double h; // heuristic
    double f; // f = g+h
};

struct Node
{
    RobotConfiguration robot_config_;
    Priority priority_;
//    Node *parent;
    std::shared_ptr<Node> parent;

    // initialize node
    Node(RobotConfiguration config, Priority pri)
        : robot_config_(config), priority_(pri), parent(NULL) {}
};

class A_star
{
    public:
     // Get path API
     std::list<std::shared_ptr<Node>> get_path(Node &start_node, Node &end_node,
                             bool isIgnoreCorner);

     // Initialize map
     void init_map(std::vector<std::vector<int>> &_map);

     std::vector<std::vector<int>> get_path_coordinate(Node &start_node, Node &end_node,
                                                          bool isIgnoreCorner);

    private:
        // Find path from start_node to end_node
        std::shared_ptr<Node> find_path(Node &start_node, Node &end_node, bool isIgnoreCorner);

        // Get Surrounding nodes
        std::vector<std::shared_ptr<Node>> get_surrounding_nodes(const std::shared_ptr<Node> current_node,
                                               bool isIgnoreCorner) const;

        // Justify whether node is free or is inside obstacle
        bool is_free(const std::shared_ptr<Node> current_node, const std::shared_ptr<Node> target_node,
                   bool isIgnoreCorner) const;

        // Justify whether node is in open/close list or not
        std::shared_ptr<Node>is_in_list(const std::list<std::shared_ptr<Node>> &list, const std::shared_ptr<Node> node) const;

        // Get node with minimum cost
        std::shared_ptr<Node> get_min_cost();

        // Calculate Priority
        double calculate_g(std::shared_ptr<Node> parent_node, std::shared_ptr<Node> current_node);
        double calculate_h(std::shared_ptr<Node> current_node, std::shared_ptr<Node> end_node);
        double calculate_f(std::shared_ptr<Node> current_node);

    private:
        std::vector<std::vector<int>> map;
        std::list<std::shared_ptr<Node>> openlist;
        std::list<std::shared_ptr<Node>> closelist;

        // Define constant cost
        const int move_straight = 10;
        const int move_incline = 14;



};

#endif // ALGORITHM_H
