#ifndef GSL_POLYNOMIAL_INTERPOLATOR_HPP
#define GSL_POLYNOMIAL_INTERPOLATOR_HPP

#include "Interpolator.hpp"
#include <gsl/gsl_interp.h>
#include <gsl/gsl_errno.h>

class GslPolynomialInterpolator : public Interpolator {
public:
    // Constructor que inicializa los datos
    GslPolynomialInterpolator(const std::vector<double>& x, const std::vector<double>& y);
    // Destructor
    ~GslPolynomialInterpolator();

    // Sobrecarga del operador para la interpolación
    double operator()(double x) const override;

private:
    void computeCoefficients();
    gsl_interp* interp = nullptr;          // Puntero al interpolador GSL
    gsl_interp_accel* acc = nullptr;       // Puntero al acelerador GSL
};

#endif // GSL_POLYNOMIAL_INTERPOLATOR_HPP
