#include "Algorithm.h"

std::list<std::shared_ptr<Node>> A_star::get_path(Node &start_node, Node &end_node,
                                   bool isIgnoreCorner) {
  std::shared_ptr<Node> result = find_path(start_node, end_node, isIgnoreCorner);
  std::list<std::shared_ptr<Node>> path;
  // return path. if no path found, return empty list.
  while (result) {
    path.push_front(result);
    result = result->parent;
  }

  // clear openlist and closelist
  openlist.clear();
  closelist.clear();

  return path;
}

void A_star::init_map(std::vector<std::vector<int>> &_map) { map = _map; }

std::vector<std::vector<int> > A_star::get_path_coordinate(Node &start_node, Node &end_node, bool isIgnoreCorner)
{
    std::shared_ptr<Node> result = find_path(start_node, end_node, isIgnoreCorner);
    std::vector<std::vector<int>> path_coordinate;
    while(result){
        path_coordinate.insert(path_coordinate.begin(), {result->robot_config_.x, result->robot_config_.y});
        result = result->parent;
    }

    openlist.clear();
    closelist.clear();

    return path_coordinate;
}

std::shared_ptr<Node> A_star::find_path(Node &start_node, Node &end_node, bool isIgnoreCorner) {
  // copy the start node (seperate varibles inside and outside)
  RobotConfiguration start_config_ = start_node.robot_config_;
  Priority start_pri_ = start_node.priority_;

  // insert the start point into openlist
  openlist.push_back(std::make_shared<Node>(start_config_, start_pri_));

  // start find path only when the openlist is not empty
  while (!openlist.empty()) {
    // find node with minimum g+h
    auto current_node = get_min_cost();
    // remove the expanded node from openlist and instert into close list
    openlist.remove(current_node);
    closelist.push_back(current_node);

    // find the free nodes in the 8 surrounding nodes
    auto sur_nodes_ = get_surrounding_nodes(current_node, isIgnoreCorner);

    for (auto &target : sur_nodes_) {
      /// for certain target node, justify whether it is inside openlist.
      /// if not, insert it into openlist, set its parent node as the current
      /// node and calculate g,h,f
      if (!is_in_list(openlist, target)) {
        target->parent = current_node;

        target->priority_.g = calculate_g(current_node, target);
        target->priority_.h = calculate_h(target, std::make_shared<Node>(end_node));
        target->priority_.f = calculate_f(target);

        openlist.push_back(target);
      }
      /// for certain target node, justify whether it is inside openlist.
      /// if yes, calculate g.
      /// if g is greater than its original value, do nothing.
      /// else, set its parent node as current node and renew g and f.
      else {
        double temp_g = calculate_g(current_node, target);
        if (temp_g < target->priority_.g) {
          target->parent = current_node;
          target->priority_.g = temp_g;
          target->priority_.f = calculate_f(target);
        }
      }
      std::shared_ptr<Node> resNode = is_in_list(closelist, std::make_shared<Node>(end_node));
      if (resNode) {
        return resNode;
      }
    }
  }
  return NULL;
}

std::vector<std::shared_ptr<Node>> A_star::get_surrounding_nodes(const std::shared_ptr<Node> current_node,
                                                  bool isIgnoreCorner) const {

  std::vector<std::shared_ptr<Node>> surrounds;

  for (int x = current_node->robot_config_.x - 1;
       x <= current_node->robot_config_.x + 1; x++) {
    for (int y = current_node->robot_config_.y - 1;
         y <= current_node->robot_config_.y + 1; y++) {

      RobotConfiguration sur_config_;
      sur_config_.x = x;
      sur_config_.y = y;

      Priority sur_pri_;
      sur_pri_.g = 0;
      sur_pri_.h = 0;
      sur_pri_.f = 0;

      if (is_free(current_node, std::make_shared<Node>(sur_config_, sur_pri_),
                  isIgnoreCorner)) {
        surrounds.push_back(std::make_shared<Node>(sur_config_, sur_pri_));
      }
    }
  }

  return surrounds;
}

bool A_star::is_free(const std::shared_ptr<Node> current_node, const std::shared_ptr<Node> target_node,
                     bool isIgnoreCorner) const {
  /// if target node is the current node,
  /// target node exceeds the map,
  /// target node is obstacle,
  /// target node is in closelist,
  /// function return false
  if (target_node->robot_config_.x < 0 ||
      target_node->robot_config_.x > map.size() - 1 ||
      target_node->robot_config_.y < 0 ||
      target_node->robot_config_.y > map[0].size() - 1 ||
      map[target_node->robot_config_.x][target_node->robot_config_.y] == 1 ||
      (target_node->robot_config_.x == current_node->robot_config_.x &&
       target_node->robot_config_.y == current_node->robot_config_.y) ||
      is_in_list(closelist, target_node))
    return false;
  else {
    if (abs(current_node->robot_config_.x - target_node->robot_config_.x) +
            abs(current_node->robot_config_.y - target_node->robot_config_.y) ==
        1)
      return true;
    else {
      if (map[current_node->robot_config_.x][target_node->robot_config_.y] ==
              0 &&
          map[target_node->robot_config_.x][current_node->robot_config_.y] == 0)
        return true;
      else
        return isIgnoreCorner;
    }
  }
}

std::shared_ptr<Node> A_star::is_in_list(const std::list<std::shared_ptr<Node>> &list,
                         const std::shared_ptr<Node> node) const {
  for (auto list_node : list) {
    if (node->robot_config_.x == list_node->robot_config_.x &&
        node->robot_config_.y == list_node->robot_config_.y) {
      return list_node;
    }
  }
  return NULL;
}

std::shared_ptr<Node> A_star::get_min_cost() {
  // bubble sort
  if (!openlist.empty()) {
    auto resNode = openlist.front();
    for (auto &node : openlist) {
      if (node->priority_.f < resNode->priority_.f) {
        resNode = node;
      }
    }
    return resNode;
  } else {
    std::cout << "The Openlist is Empty" << std::endl;
    return NULL;
  }
}

double A_star::calculate_g(std::shared_ptr<Node> parent_node, std::shared_ptr<Node> current_node) {
  double current_g =
      (abs(current_node->robot_config_.x - parent_node->robot_config_.x) +
       abs(current_node->robot_config_.y - parent_node->robot_config_.y)) == 1
          ? move_straight
          : move_incline;

  double parent_g =
      current_node->parent == NULL ? 0 : current_node->parent->priority_.g;

  return current_g + parent_g;
}

double A_star::calculate_h(std::shared_ptr<Node> current_node, std::shared_ptr<Node> end_node) {
  // Use Euclidean distance as heuristic
  return sqrt((end_node->robot_config_.x - current_node->robot_config_.x) *
                  (end_node->robot_config_.x - current_node->robot_config_.x) +
              (end_node->robot_config_.y - current_node->robot_config_.y) *
                  (end_node->robot_config_.y - current_node->robot_config_.y)) *
         move_straight;
}

double A_star::calculate_f(std::shared_ptr<Node> current_node) {
  return current_node->priority_.g + current_node->priority_.h;
}
