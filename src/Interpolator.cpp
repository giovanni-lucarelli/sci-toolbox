#include "Interpolator.hpp"
#include <stdexcept>

// Definición del método setData and issues that we can experiment
void Interpolator::setData(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Vectors x and y must have the same non-zero size.");
    }
    if (x.size() < 2 || y.size() < 2) {
        throw std::invalid_argument("At least two nodes are required for interpolation.");
    }
    // Check for duplicate x-values
    for (size_t i = 1; i < x.size(); ++i) {
        if (x[i] == x[i - 1]) {
            throw std::invalid_argument("Duplicate x-values detected. x-values must be unique.");
        }
    }
    // Ensure x-values are strictly increasing
    for (size_t i = 1; i < x.size(); ++i) {
    if (x[i] <= x[i - 1]) {
        throw std::invalid_argument("x-values must be strictly increasing.");
    }
}

    x_nodes = x;
    y_nodes = y;
}

//  Prevent invalid queries or extrapolation in unsupported methods
void Interpolator::checkRange(double x) const {
    if (x < x_nodes.front() || x > x_nodes.back()) {
        throw std::out_of_range("x is outside the interpolation range.");
    }
}


