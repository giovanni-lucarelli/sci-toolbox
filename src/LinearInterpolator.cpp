#include "LinearInterpolator.hpp"

// Constructor: inicializa los datos usando setData
LinearInterpolator::LinearInterpolator(const std::vector<double>& x, const std::vector<double>& y) {
    setData(x, y); // Verifica y almacena los datos
}

double LinearInterpolator::operator()(double x) const {
    // Verifica si x está dentro del rango de interpolación
    // if (x < x_nodes.front() || x > x_nodes.back()) {
    //      throw std::out_of_range("x is outside the interpolation range.");
    // }
    checkRange(x);

    // Busca el intervalo [x_nodes[i], x_nodes[i+1]] donde se encuentra x
    for (size_t i = 0; i < x_nodes.size() - 1; ++i) {
        if (x >= x_nodes[i] && x <= x_nodes[i + 1]) {
            // Calcula la pendiente y devuelve el valor interpolado
            double slope = (y_nodes[i + 1] - y_nodes[i]) / (x_nodes[i + 1] - x_nodes[i]);
            return y_nodes[i] + slope * (x - x_nodes[i]); // y = y_i + slope * (x - x_i)
        }
    }

     throw std::runtime_error("Interpolation failed. x should be within the data range.");
}
