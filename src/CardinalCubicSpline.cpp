#include "CardinalCubicSpline.hpp"

// Constructor que inicializa el spline cúbico de Boost
CardinalCubicSpline::CardinalCubicSpline(const std::vector<double>& x, const std::vector<double>& y, double start, double step)
    : spline(y.begin(), y.end(), start, step) {
    // Valida y almacena los nodos en la clase base
    setData(x, y); 

    //checkMinNodes(x);

    checkSteps(x);
}

// Método para evaluar la interpolación en un punto x
double CardinalCubicSpline::operator()(double x) const {
    checkRange(x); // Verifica si x está dentro del rango
    return spline(x);
}

// // Método para verificar si el número de nodos es suficiente (el propio spline lanza un error suyo)
// void CardinalCubicSpline::checkMinNodes(const std::vector<double>& x) const {
//     if (x.size() < 5) {
//         throw std::invalid_argument("Interpolation using a cubic b spline with derivatives estimated at the endpoint requires at least 5 points.");
//     }
// }

// Método para verificar si los pasos entre los nodos son iguales
void CardinalCubicSpline::checkSteps(const std::vector<double>& x) const {
    double step = x[1] - x[0]; // Paso esperado entre nodos
    double tolerance = 1e-9;  // Tolerancia para comparación
    for (size_t i = 1; i < x.size() - 1; ++i) {
        double actualStep = x[i+1] - x[i];
        if (std::fabs(actualStep - step) > tolerance) {
            throw std::invalid_argument("The x-nodes must have equal spacing between them.");
        }
    }
}





// // Constructor: Inicializa el spline con los valores y los parámetros
// CardinalCubicSpline::CardinalCubicSpline(const std::vector<double>& x, const std::vector<double>& y, double start, double step)
//     : Interpolator(), // Inicializamos la base
//       spline(y.begin(), y.end(), start, step) {} // Inicializamos el spline con Boost

// // Método para evaluar el spline
// double CardinalCubicSpline::operator()(double x) const {
//     return spline(x);
// }
