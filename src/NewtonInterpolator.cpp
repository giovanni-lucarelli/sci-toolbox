#include "NewtonInterpolator.hpp"

NewtonInterpolator::NewtonInterpolator(const std::vector<double>& x, const std::vector<double>& y) {
    // Llama a setData para almacenar los datos
    setData(x, y);  
    // Luego, inicializa los coeficientes
    computeCoefficients();
}
// Método para calcular los coeficientes de Newton (diferencias divididas)
void NewtonInterpolator::computeCoefficients() {
    std::size_t n = x_nodes.size();
    coefficients.resize(n); // Estos coeficientes representan las diferencias divididas f[x0], f[x0,x1],...

// Copiar los valores de y en el primer conjunto de coeficientes (P(x) = f[x0] + ...)
    for (std::size_t i = 0; i < n; ++i) {
        coefficients[i] = y_nodes[i]; // los valores de yi se copian al vector coefficients
    }

    // Calcular las diferencias divididas de Newton
    for (std::size_t j = 1; j < n; ++j) {
        for (std::size_t i = n - 1; i >= j; --i) {
            coefficients[i] = (coefficients[i] - coefficients[i - 1]) / (x_nodes[i] - x_nodes[i - j]);
        }
    }
}

// Sobrecarga del operador para realizar la interpolación en el valor 'x'
double NewtonInterpolator::operator()(double x) const {
    checkRange(x);
    std::size_t n = x_nodes.size();
    double result = coefficients[n - 1];

    // Evaluación del polinomio de Newton usando la fórmula de Horner!!!!!
    for (int i = static_cast<int>(n) - 2; i >= 0; --i) {
        result = result * (x - x_nodes[i]) + coefficients[i];
    }

    return result;
}