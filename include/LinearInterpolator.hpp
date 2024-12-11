#ifndef LINEAR_INTERPOLATOR_HPP
#define LINEAR_INTERPOLATOR_HPP

#include "Interpolator.hpp"
#include <stdexcept>

class LinearInterpolator : public Interpolator {
public:
    LinearInterpolator(const std::vector<double>& x, const std::vector<double>& y);
        // : Interpolator(){
        //     setData(x,y);
        // }

    double operator()(double x) const override;
};

#endif // LINEAR_INTERPOLATOR_HPP

