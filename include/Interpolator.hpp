#ifndef INTERPOLATOR_HPP
#define INTERPOLATOR_HPP

#include <vector>

class Interpolator {
public:
    virtual ~Interpolator() = default;

    // Método puro para interpolar
    virtual double operator()(double x) const = 0;

    // Declaración del setter para los datos
    void setData(const std::vector<double>& x, const std::vector<double>& y);

    // Método para verificar si un valor x está dentro del rango de los nodos
    void checkRange(double x) const;

protected:
    std::vector<double> x_nodes;
    std::vector<double> y_nodes;
};

#endif // INTERPOLATOR_HPP

