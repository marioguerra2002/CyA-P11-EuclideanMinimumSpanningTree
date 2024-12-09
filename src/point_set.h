#ifndef POINT_SET_H
#define POINT_SET_H

#include <vector>
#include <utility> // std::pair
#include <limits>  // std::numeric_limits
#include <cmath>   // std::sqrt
#include <algorithm> // std::min, std::find

namespace CyA {
    using point = std::pair<int, int>;
    using point_vector = std::vector<point>;
    using edge = std::pair<point, point>;
    using edge_vector = std::vector<edge>;

    class point_set {
    public:
        point_set(const point_vector &points);
        void EMST();
        const point_vector &get_points() const;
        const edge_vector &get_tree() const;
        double get_cost() const;

    private:
        point_vector points_;
        edge_vector tree_;
        double cost_;

        double distance(const point &a, const point &b) const;
    };
}

#endif // POINT_SET_H
