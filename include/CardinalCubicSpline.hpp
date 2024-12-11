#ifndef CARDINAL_CUBIC_SPLINE_HPP
#define CARDINAL_CUBIC_SPLINE_HPP

#include "Interpolator.hpp"
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

class CardinalCubicSpline : public Interpolator {
    public:
    // Constructor que inicializa el spline con Boost
    // Constructor que inicializa los datos
    CardinalCubicSpline(const std::vector<double>& x, const std::vector<double>& y, double start, double step);
        
    // Destructor
    ~CardinalCubicSpline() override = default; // No se especifican excepciones

    // Método para evaluar la interpolación
    double operator()(double x) const override;

private:
    // Método para verificar si los pasos entre nodos son iguales
    void checkSteps(const std::vector<double>& x) const;

    // Método para verificar si el número de nodos es suficiente
    //void checkMinNodes(const std::vector<double>& x) const;

    boost::math::interpolators::cardinal_cubic_b_spline<double> spline; // Spline cúbico de Boost

};


#endif 
