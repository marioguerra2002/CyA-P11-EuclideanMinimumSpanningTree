#include "point_set.h"

namespace CyA {
    point_set::point_set(const point_vector &points) : points_(points), cost_(0.0) {}

    double point_set::distance(const point &a, const point &b) const {
        return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
    }

    void point_set::EMST() {
        tree_.clear();
        cost_ = 0.0;

        if (points_.empty()) return;

        std::vector<bool> in_tree(points_.size(), false);
        std::vector<double> min_distance(points_.size(), std::numeric_limits<double>::max());
        std::vector<int> nearest(points_.size(), -1);

        min_distance[0] = 0.0;

        for (size_t i = 0; i < points_.size(); ++i) {
            int u = -1;
            for (size_t j = 0; j < points_.size(); ++j) {
                if (!in_tree[j] && (u == -1 || min_distance[j] < min_distance[u])) {
                    u = j;
                }
            }

            if (nearest[u] != -1) {
                tree_.emplace_back(points_[u], points_[nearest[u]]);
                cost_ += distance(points_[u], points_[nearest[u]]);
            }

            in_tree[u] = true;

            for (size_t v = 0; v < points_.size(); ++v) {
                double dist = distance(points_[u], points_[v]);
                if (!in_tree[v] && dist < min_distance[v]) {
                    min_distance[v] = dist;
                    nearest[v] = u;
                }
            }
        }
    }

    const point_vector &point_set::get_points() const {
        return points_;
    }

    const edge_vector &point_set::get_tree() const {
        return tree_;
    }

    double point_set::get_cost() const {
        return cost_;
    }
}
