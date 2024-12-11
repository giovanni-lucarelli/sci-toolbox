#include "GslPolynomialInterpolator.hpp"
#include <stdexcept>

// Constructor que inicializa los datos
GslPolynomialInterpolator::GslPolynomialInterpolator(const std::vector<double>& x, const std::vector<double>& y) {
    // Llama a setData para almacenar los datos
    setData(x, y);  
    // Luego, inicializa los coeficientes
    computeCoefficients();
}

void GslPolynomialInterpolator::computeCoefficients() {
    std::size_t n = x_nodes.size();

    // Creamos el interpolador de GSL (polinómico) y el acelerador
    interp = gsl_interp_alloc(gsl_interp_polynomial, n);
    acc = gsl_interp_accel_alloc();

     // Establecemos los datos de entrada en el interpolador de GSL
    int status = gsl_interp_init(interp, x_nodes.data(), y_nodes.data(), n);
    if (status != GSL_SUCCESS) {
        throw std::runtime_error("Error al inicializar el interpolador de GSL.");
    }
}

double GslPolynomialInterpolator::operator()(double x) const {
    // Usamos GSL para calcular la interpolación en el punto x
    checkRange(x);
    return gsl_interp_eval(interp, x_nodes.data(), y_nodes.data(), x, acc);
}

GslPolynomialInterpolator::~GslPolynomialInterpolator() {
    // Liberamos los recursos de GSL si han sido inicializados
    if (interp != nullptr) {
        gsl_interp_free(interp);
    }
    if (acc != nullptr) {
        gsl_interp_accel_free(acc);
    }
}