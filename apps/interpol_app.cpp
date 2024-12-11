#include <iostream>
#include <cmath>
#include <chrono>
#include <map>
#include <functional>
#include "LinearInterpolator.hpp"
#include "GslPolynomialInterpolator.hpp"
#include "NewtonInterpolator.hpp"
#include "CardinalCubicSpline.hpp"
// #include "PolynomialInterpolator.hpp"
// #include "GslCardinal.hpp"

// FINAL MAIN??

// Funciones a interpolar
double f1(double x) {
    return std::exp(x); //
}

// Generar nodos y valores correspondientes
void generate_nodes_and_values(double a, double b, int n, std::vector<double>& x_nodes, std::vector<double>& y_nodes, double (*func)(double)) {
    double delta_x = (b - a) / (n - 1);
    for (int i = 0; i < n; ++i) {
        double x = a + i * delta_x;
        x_nodes.push_back(x);
        y_nodes.push_back(func(x));
    }
}

// Estructura para almacenar los interpoladores
struct Interpolators {
    LinearInterpolator linearInterp;
    GslPolynomialInterpolator lagrangeInterp;
    NewtonInterpolator newtonInterp;
    CardinalCubicSpline cubicSpline;
};

// Comparar métodos de interpolación
Interpolators compareInterpolationMethods(
    const std::vector<double>& x_nodes, 
    const std::vector<double>& y_nodes, 
    double (*trueFunction)(double), 
    const std::vector<double>& test_points) 
    {
    
    // Crear interpoladores
    LinearInterpolator linearInterp(x_nodes, y_nodes);
    GslPolynomialInterpolator lagrangeInterp(x_nodes, y_nodes);
    NewtonInterpolator newtonInterp(x_nodes, y_nodes);
    double delta_x = x_nodes[1] - x_nodes[0];
    CardinalCubicSpline cubicSpline(x_nodes, y_nodes, x_nodes[0], delta_x);


    // Mostrar encabezado
    std::cout << std::left << std::setw(10) << "x"
            << std::setw(15) << "True Value"
            << std::setw(15) << "Linear"
            << std::setw(15) << "Lagrange"
            << std::setw(15) << "Newton"
            << std::setw(15) << "Cubic Spline"
            << std::setw(15) << "Error Linear"
            << std::setw(15) << "Error Lagrange"
            << std::setw(15) << "Error Newton"
            << std::setw(15) << "Error Cubic Spline" << "\n";
    std::cout << std::string(140, '-') << "\n";

    // Evaluar los métodos para cada punto de prueba
    for (double x : test_points) {
        double true_value = trueFunction(x);
        double linear_value = linearInterp(x);
        double lagrange_value = lagrangeInterp(x);
        double newton_value = newtonInterp(x);
        double cubic_spline_value = cubicSpline(x);

        double error_linear = std::abs(true_value - linear_value);
        double error_lagrange = std::abs(true_value - lagrange_value);
        double error_newton = std::abs(true_value - newton_value);
        double error_cubic_spline = std::abs(true_value - cubic_spline_value);

        std::cout << std::left << std::setw(10) << x
              << std::setw(15) << true_value
              << std::setw(15) << linear_value
              << std::setw(15) << lagrange_value
              << std::setw(15) << newton_value
              << std::setw(15) << cubic_spline_value
              << std::setw(15) << error_linear
              << std::setw(15) << error_lagrange
              << std::setw(15) << error_newton
              << std::setw(15) << error_cubic_spline << "\n";
    }

    return {linearInterp, lagrangeInterp, newtonInterp, cubicSpline};
}

// Función para medir el tiempo de ejecución
double measure_execution_time(std::function<void()> f) {
    // Obtener el tiempo antes de la ejecución del código
    auto start = std::chrono::high_resolution_clock::now();
    // Ejecutar el bloque de código que se pasa como parámetro
    f();
    // Obtener el tiempo después de la ejecución del código
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start; // Calcular la diferencia de tiempo entre start y end (en segundos)
    return duration.count();
}

void evaluateEfficiency(const Interpolators& interpolators, const std::vector<double>& test_points) {
    std::cout << "\nEfficiency (Time to interpolate all test points):\n";
    std::cout << std::left << std::setw(15) << "Method" 
              << std::setw(15) << "Time (seconds)" << "\n";
    std::cout << std::string(30, '-') << "\n";

    // Medir tiempo de ejecución para Linear Interpolation
    double linear_time = measure_execution_time([&]() {
        for (double x : test_points) interpolators.linearInterp(x);
    });
    std::cout << std::left << std::setw(15) << "Linear"
              << std::setw(15) << linear_time << "\n";

    // Medir tiempo de ejecución para Lagrange Interpolation
    double lagrange_time = measure_execution_time([&]() {
        for (double x : test_points) interpolators.lagrangeInterp(x);
    });
    std::cout << std::left << std::setw(15) << "Lagrange"
              << std::setw(15) << lagrange_time << "\n";

    // Medir tiempo de ejecución para Newton Interpolation
    double newton_time = measure_execution_time([&]() {
        for (double x : test_points) interpolators.newtonInterp(x);
    });
    std::cout << std::left << std::setw(15) << "Newton"
              << std::setw(15) << newton_time << "\n";

    // Medir tiempo de ejecución para Cubic Spline
    double cubic_spline_time = measure_execution_time([&]() {
        for (double x : test_points) interpolators.cubicSpline(x);
    });
    std::cout << std::left << std::setw(15) << "Cubic Spline"
              << std::setw(15) << cubic_spline_time << "\n";
}

// Función para calcular los errores de interpolación
void calculateInterpolationErrors(
    const Interpolators& interpolators,
    const std::vector<double>& test_points,
    double (*trueFunction)(double))
{
    // Mostrar encabezado
    std::cout << std::left << std::setw(15) << "Method"
              << std::setw(20) << "Max Abs Error"
              << std::setw(20) << "RMSE"
              << "\n";
    std::cout << std::string(55, '-') << "\n";

    // Definir los interpoladores en un mapa para procesarlos automáticamente
    std::map<std::string, std::function<double(double)>> methods = {
        {"Linear", [&](double x) { return interpolators.linearInterp(x); }},
        {"Lagrange", [&](double x) { return interpolators.lagrangeInterp(x); }},
        {"Newton", [&](double x) { return interpolators.newtonInterp(x); }},
        {"Cubic Spline", [&](double x) { return interpolators.cubicSpline(x); }}
    };

    // Calcular errores para cada método
    for (const auto& [method_name, interpolator] : methods) {
        double max_abs_error = 0.0;
        double total_squared_error = 0.0;

        for (double x : test_points) {
            double true_value = trueFunction(x);
            double interpolated_value = interpolator(x);
            double error = std::abs(true_value - interpolated_value);

            max_abs_error = std::max(max_abs_error, error);
            total_squared_error += error * error;
        }

        double rmse = std::sqrt(total_squared_error / test_points.size());

        // Mostrar los errores
        std::cout << std::left << std::setw(15) << method_name
                  << std::setw(20) << max_abs_error
                  << std::setw(20) << rmse
                  << "\n";
    }
}

// // Calcular el orden de convergencia entre dos valores de error
// double calculate_convergence_order(double error_n1, double error_n2, int n1, int n2) {
//     return std::log(error_n2 / error_n1) / std::log(n2 / n1);
// }


int main() {
    // Intervalo y número de nodos para f(x) = x^6
    double a_f1 = 0.0;
    double b_f1 = 2.0;
    int n_f1_1 = 15;
    int n_f1_2 = 30;

    // Vectores para almacenar los nodos y valores
    std::vector<double> x_nodes_f1_1, y_nodes_f1_1;
    std::vector<double> x_nodes_f1_2, y_nodes_f1_2;

    // Generar nodos y valores para x^6
    generate_nodes_and_values(a_f1, b_f1, n_f1_1, x_nodes_f1_1, y_nodes_f1_1, f1);
    generate_nodes_and_values(a_f1, b_f1, n_f1_2, x_nodes_f1_2, y_nodes_f1_2, f1);

    // Mostrar nodos generados
    std::cout << "\nNodes (x_i) and values (y_i) for f(x) = e^x with n = 15:\n";
    for (int i = 0; i < n_f1_1; ++i) {
        std::cout << "x[" << i << "] = " << x_nodes_f1_1[i] << ", y[" << i << "] = " << y_nodes_f1_1[i] << "\n";
    }

    // Mostrar nodos generados
    std::cout << "\nNodes (x_i) and values (y_i) for f(x) = e^x with n = 30:\n";
    for (int i = 0; i < n_f1_2; ++i) {
        std::cout << "x[" << i << "] = " << x_nodes_f1_2[i] << ", y[" << i << "] = " << y_nodes_f1_2[i] << "\n";
    }

    // Puntos de prueba
    std::vector<double> test_points_f1 = {0.1, 0.25, 0.35, 0.5, 0.75, 0.9, 1.25, 1.5, 1.75};
    
    // Comparar métodos de interpolación para f(x) = x^6
    std::cout << "\nInterpolation of f(x) = e^x with n = 15: True Values, Approximations from Different Methods, and Accuracy\n";
    Interpolators interpolators_n1 = compareInterpolationMethods(x_nodes_f1_1, y_nodes_f1_1, f1, test_points_f1);
    std::cout << "\nInterpolation of f(x) = e^x with n = 30: True Values, Approximations from Different Methods, and Accuracy\n";
    Interpolators interpolators_n2 = compareInterpolationMethods(x_nodes_f1_2, y_nodes_f1_2, f1, test_points_f1);
    
    // Evaluar eficiencia para n = 15
    std::cout << "\nEfficiency for n = 15:\n";
    evaluateEfficiency(interpolators_n1, test_points_f1);
    

    // Error para n = 15
    calculateInterpolationErrors(interpolators_n1, test_points_f1, f1);

    // Error para n = 30
    calculateInterpolationErrors(interpolators_n2, test_points_f1, f1);


    // // Calcular el orden de convergencia
    // std::cout << "\nOrder of convergence for each method:\n";
    // double linear_order_f1 = calculate_convergence_order(error_linear_f1_1, error_linear_f1_2, n_f1_1, n_f1_2);
    // std::cout << "Order of convergence (Linear): " << linear_order_f1 << std::endl;
    
    // double lagrange_order_f1 = calculate_convergence_order(error_lagrange_f1_1, error_lagrange_f1_2, n_f1_1, n_f1_2);
    // std::cout << "Order of convergence (Lagrange): " << lagrange_order_f1 << std::endl;

    // // Calcular el orden de convergencia para Newton
    // double newton_order_f1 = calculate_convergence_order(error_newton_f1_1, error_newton_f1_2, n_f1_1, n_f1_2);
    // std::cout << "Order of convergence (Newton): " << newton_order_f1 << std::endl;

    // // Calcular el orden de convergencia para Cubic Spline
    // double cubic_spline_order_f1 = calculate_convergence_order(error_cubic_spline_f1_1, error_cubic_spline_f1_2, n_f1_1, n_f1_2);
    // std::cout << "Order of convergence (Cubic Spline): " << cubic_spline_order_f1 << std::endl;


    return 0;
}