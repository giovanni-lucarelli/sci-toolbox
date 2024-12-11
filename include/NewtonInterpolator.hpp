#ifndef NEWTON_INTERPOLATOR_HPP
#define NEWTON_INTERPOLATOR_HPP

#include "Interpolator.hpp"

class NewtonInterpolator : public Interpolator {
public:
    // Constructor que inicializa los datos y calcula los coeficientes de Newton
    NewtonInterpolator(const std::vector<double>& x, const std::vector<double>& y);

    // Sobrecarga del operador para realizar la interpolación en el valor 'x'
    double operator()(double x) const override;

private:
    // Método para calcular los coeficientes de Newton
    void computeCoefficients();

    std::vector<double> coefficients; // Almacena los coeficientes de Newton
    
};

#endif // NEWTON_INTERPOLATOR_HPP 