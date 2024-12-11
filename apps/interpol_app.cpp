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

// Estimar el orden de convergencia
double estimate_convergence_order(double error_n, double error_half_n) {
    return std::log(error_n / error_half_n) / std::log(2.0);
}

// Comparar métodos de interpolación
void compareInterpolationMethods(
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
}

// Calcular el error de interpolación para los puntos de prueba
double calculate_interpolation_error(
    const std::vector<double>& test_points, 
    double (*trueFunction)(double),
    const std::function<double(double)>& interpolator,
    const std::string& method_name,
    int n)
    {
    double total_error = 0.0;
    for (double x : test_points) {
        double true_value = trueFunction(x);
        double interpolated_value = interpolator(x);
        total_error += std::pow(true_value - interpolated_value, 2); // Error cuadrático
    }
    double mean_squared_error = std::sqrt(total_error / test_points.size()); // Error medio cuadrático
    // Imprimir el error medio cuadrático
    std::cout << "Error medio cuadrático para " << method_name << " usando n = " << n << ": " << mean_squared_error << std::endl;
    return mean_squared_error;
}

// Calcular el orden de convergencia entre dos valores de error
double calculate_convergence_order(double error_n1, double error_n2, int n1, int n2) {
    return std::log(error_n2 / error_n1) / std::log(n2 / n1);
}


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
    compareInterpolationMethods(x_nodes_f1_1, y_nodes_f1_1, f1, test_points_f1);
    std::cout << "\nInterpolation of f(x) = e^x with n = 30: True Values, Approximations from Different Methods, and Accuracy\n";
    compareInterpolationMethods(x_nodes_f1_2, y_nodes_f1_2, f1, test_points_f1);
    
    // Medir el tiempo de ejecución de cada método de interpolación
    LinearInterpolator linearInterp(x_nodes_f1_1, y_nodes_f1_1);
    GslPolynomialInterpolator lagrangeInterp(x_nodes_f1_1, y_nodes_f1_1);
    NewtonInterpolator newtonInterp(x_nodes_f1_1, y_nodes_f1_1);
    double delta_x_1 = x_nodes_f1_1[1] - x_nodes_f1_1[0];
    CardinalCubicSpline cubicSpline(x_nodes_f1_1, y_nodes_f1_1, x_nodes_f1_1[0], delta_x_1);
     
    // Medir la eficiencia para cada método
    double linear_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) linearInterp(x); 
    });
    double lagrange_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) lagrangeInterp(x); 
    });
    double newton_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) newtonInterp(x); 
    });
    double cubic_spline_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) cubicSpline(x); 
    });

    // Mostrar la eficiencia
    std::cout << "\nEfficiency (Time to interpolate all test points):\n";
    std::cout << std::left << std::setw(15) << "Method"
              << std::setw(15) << "Time (seconds)" << "\n";
    std::cout << std::string(30, '-') << "\n";
    std::cout << std::left << std::setw(15) << "Linear" 
              << std::setw(15) << linear_time << "\n";
    std::cout << std::left << std::setw(15) << "Lagrange" 
              << std::setw(15) << lagrange_time << "\n";
    std::cout << std::left << std::setw(15) << "Newton" 
              << std::setw(15) << newton_time << "\n";
    std::cout << std::left << std::setw(15) << "Cubic Spline" 
              << std::setw(15) << cubic_spline_time << "\n";
    
    // Creamos interpoladores para n_f1_2
    LinearInterpolator linearInterp2(x_nodes_f1_2, y_nodes_f1_2);
    GslPolynomialInterpolator lagrangeInterp2(x_nodes_f1_2, y_nodes_f1_2);
    NewtonInterpolator newtonInterp2(x_nodes_f1_2, y_nodes_f1_2);
    double delta_x_2 = x_nodes_f1_2[1] - x_nodes_f1_2[0];
    CardinalCubicSpline cubicSpline2(x_nodes_f1_2, y_nodes_f1_2, x_nodes_f1_2[0], delta_x_2);

    // Calcular el error de interpolación para n_f1_1 y n_f1_2 para Linear, Lagrange, Newton, y Cubic Spline
    std::cout << "\nRMSE:\n";
    double error_linear_f1_1 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return linearInterp(x); }, "Lineal", 15);
    double error_linear_f1_2 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return linearInterp2(x); }, "Lineal", 30);

    double error_lagrange_f1_1 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return lagrangeInterp(x); }, "Lagrange", 15);
    double error_lagrange_f1_2 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return lagrangeInterp2(x); }, "Lagrange", 30);

    double error_newton_f1_1 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return newtonInterp(x); }, "Newton", 15);
    double error_newton_f1_2 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return newtonInterp2(x); }, "Newton", 30);

    double error_cubic_spline_f1_1 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return cubicSpline(x); }, "Cubic Spline", 15);
    double error_cubic_spline_f1_2 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return cubicSpline2(x); }, "Cubic Spline", 30);


    // Calcular el orden de convergencia
    std::cout << "\nOrder of convergence for each method:\n";
    double linear_order_f1 = calculate_convergence_order(error_linear_f1_1, error_linear_f1_2, n_f1_1, n_f1_2);
    std::cout << "Order of convergence (Linear): " << linear_order_f1 << std::endl;
    
    double lagrange_order_f1 = calculate_convergence_order(error_lagrange_f1_1, error_lagrange_f1_2, n_f1_1, n_f1_2);
    std::cout << "Order of convergence (Lagrange): " << lagrange_order_f1 << std::endl;

    // Calcular el orden de convergencia para Newton
    double newton_order_f1 = calculate_convergence_order(error_newton_f1_1, error_newton_f1_2, n_f1_1, n_f1_2);
    std::cout << "Order of convergence (Newton): " << newton_order_f1 << std::endl;

    // Calcular el orden de convergencia para Cubic Spline
    double cubic_spline_order_f1 = calculate_convergence_order(error_cubic_spline_f1_1, error_cubic_spline_f1_2, n_f1_1, n_f1_2);
    std::cout << "Order of convergence (Cubic Spline): " << cubic_spline_order_f1 << std::endl;


    return 0;
}



/*
// FINAL MAIN (NO)
// Funciones a interpolar
double f1(double x) {
    return std::pow(x, 6); // Ejemplo: f(x) = x^6
}

double f2(double x) {
    return std::sin(x) * std::cos(5*x); // Ejemplo: f(x) = sin(x)
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

// Estimar el orden de convergencia
double estimate_convergence_order(double error_n, double error_half_n) {
    return std::log(error_n / error_half_n) / std::log(2.0);
}

// Comparar métodos de interpolación
void compareInterpolationMethods(
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
}

// Calcular el error de interpolación para los puntos de prueba
double calculate_interpolation_error(
    const std::vector<double>& test_points, 
    double (*trueFunction)(double),
    const std::function<double(double)>& interpolator)
    {
    double total_error = 0.0;
    for (double x : test_points) {
        double true_value = trueFunction(x);
        double interpolated_value = interpolator(x);
        total_error += std::pow(true_value - interpolated_value, 2); // Error cuadrático
    }
    return std::sqrt(total_error / test_points.size()); // Error medio cuadrático
}

// Calcular el orden de convergencia entre dos valores de error
double calculate_convergence_order(double error_n1, double error_n2, int n1, int n2) {
    return std::log(error_n2 / error_n1) / std::log(n2 / n1);
}


int main() {
    // Intervalo y número de nodos para f(x) = x^6
    double a_f1 = 0.0;
    double b_f1 = 2.0;
    int n_f1_1 = 15;
    int n_f1_2 = 30;

    // // Intervalo y número de nodos para f(x) = ...
    // double a_f2 = 0.0;
    // double b_f2 = 2 * M_PI;
    // int n_f2 = 15;

    // Vectores para almacenar los nodos y valores
    std::vector<double> x_nodes_f1_1, y_nodes_f1_1;
    std::vector<double> x_nodes_f1_2, y_nodes_f1_2;
    //std::vector<double> x_nodes_f2, y_nodes_f2;

    // Generar nodos y valores para x^6
    generate_nodes_and_values(a_f1, b_f1, n_f1_1, x_nodes_f1_1, y_nodes_f1_1, f1);
    generate_nodes_and_values(a_f1, b_f1, n_f1_2, x_nodes_f1_2, y_nodes_f1_2, f1);

    // Generar nodos y valores
    //generate_nodes_and_values(a_f2, b_f2, n_f2, x_nodes_f2, y_nodes_f2, f2);

    // Mostrar nodos generados
    std::cout << "Nodes (x_i) and values (y_i) for f(x) = x^6:\n";
    for (int i = 0; i < n_f1_1; ++i) {
        std::cout << "x[" << i << "] = " << x_nodes_f1_1[i] << ", y[" << i << "] = " << y_nodes_f1_2[i] << "\n";
    }

    // // Mostrar nodos generados
    // std::cout << "Nodes (x_i) and values (y_i) for f(x) = sin(x):\n";
    // for (int i = 0; i < n_f2; ++i) {
    //     std::cout << "x[" << i << "] = " << x_nodes_f2[i] << ", y[" << i << "] = " << y_nodes_f2[i] << "\n";
    // }

    // Puntos de prueba
    std::vector<double> test_points_f1 = {0.1, 0.25, 0.35, 0.5, 0.75, 0.9, 1.25, 1.5, 1.75};
    //std::vector<double> test_points_f2 =  { 0.1, M_PI / 3, M_PI / 2, 2 * M_PI / 3, 5 * M_PI / 6, 6.1 };
    
    // Comparar métodos de interpolación para f(x) = x^6
    std::cout << "\nInterpolating f(x) = x^6:\n";
    compareInterpolationMethods(x_nodes_f1_1, y_nodes_f1_1, f1, test_points_f1);

    // // Comparar métodos de interpolación para f(x) = sin(x)
    // std::cout << "\nInterpolating f(x) = sin(x):\n";
    // compareInterpolationMethods(x_nodes_f2, y_nodes_f2, f2, test_points_f2);
    
    // Medir el tiempo de ejecución de cada método de interpolación
    LinearInterpolator linearInterp(x_nodes_f1_1, y_nodes_f1_1);
    GslPolynomialInterpolator lagrangeInterp(x_nodes_f1_1, y_nodes_f1_1);
    NewtonInterpolator newtonInterp(x_nodes_f1_1, y_nodes_f1_1);
    double delta_x = x_nodes_f1_1[1] - x_nodes_f1_1[0];
    CardinalCubicSpline cubicSpline(x_nodes_f1_1, y_nodes_f1_1, x_nodes_f1_1[0], delta_x);
     
    // Medir la eficiencia para cada método
    double linear_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) linearInterp(x); 
    });
    double lagrange_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) lagrangeInterp(x); 
    });
    double newton_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) newtonInterp(x); 
    });
    double cubic_spline_time = measure_execution_time([&]() { 
        for (double x : test_points_f1) cubicSpline(x); 
    });

    // Mostrar la eficiencia
    std::cout << "\nEfficiency (Time to interpolate all test points):\n";
    std::cout << std::left << std::setw(15) << "Method"
              << std::setw(15) << "Time (seconds)" << "\n";
    std::cout << std::string(30, '-') << "\n";
    std::cout << std::left << std::setw(15) << "Linear" 
              << std::setw(15) << linear_time << "\n";
    std::cout << std::left << std::setw(15) << "Lagrange" 
              << std::setw(15) << lagrange_time << "\n";
    std::cout << std::left << std::setw(15) << "Newton" 
              << std::setw(15) << newton_time << "\n";
    std::cout << std::left << std::setw(15) << "Cubic Spline" 
              << std::setw(15) << cubic_spline_time << "\n";
    
    // Creamos interpoladores para n_f1_1 y n_f1_2
    LinearInterpolator linearInterp1(x_nodes_f1_1, y_nodes_f1_1);
    LinearInterpolator linearInterp2(x_nodes_f1_2, y_nodes_f1_2);
    
    // Calcular el error de interpolación para n_f1_1 y n_f1_2 para Lagrange, Newton, y Cubic Spline
    double error_linear_f1_1 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return linearInterp1(x); });
    double error_linear_f1_2 = calculate_interpolation_error(test_points_f1, f1, [&](double x){ return linearInterp2(x); });
    
    // Calcular el orden de convergencia
    double linear_order_f1 = calculate_convergence_order(error_linear_f1_1, error_linear_f1_2, n_f1_1, n_f1_2);

    // Mostrar el orden de convergencia
    std::cout << "Order of convergence (Linear): " << linear_order_f1 << std::endl;
    
    return 0;
}
*/

/* SECOND MAIN
// Función a interpolar
double function(double x) {
    return std::pow(x,6); // Ejemplo: f(x) = x^2
}

// Generar nodos y valores correspondientes
void generate_nodes_and_values(double a, double b, int n, std::vector<double>& x_nodes, std::vector<double>& y_nodes) {
    double delta_x = (b - a) / (n - 1);
    for (int i = 0; i < n; ++i) {
        double x = a + i * delta_x;
        x_nodes.push_back(x);
        y_nodes.push_back(function(x));
    }
}

int main() {
    // Intervalo y número de nodos
    double a = 0.0;
    double b = 1;
    int n = 4;

    double delta_x = (b-a) / (n-1);

    // Vectores vacíos para almacenar los nodos xi y sus valores correspondientes yi
    std::vector<double> x_nodes;
    std::vector<double> y_nodes;

    // Generar nodos
    generate_nodes_and_values(a, b, n, x_nodes, y_nodes);

    // Mostrar nodos generados
    std::cout << "Nodes (x_i) and values (y_i):\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "x[" << i << "] = " << x_nodes[i] << ", y[" << i << "] = " << y_nodes[i] << "\n";
    }

    // Menú interactivo para elegir la interpolación
    int option;
    std::cout << "Choose the interpolation method:" << std::endl;
    std::cout << "1. Linear Interpolation" << std::endl;
    std::cout << "2. Polynomial Interpolation (Lagrange)" << std::endl;
    std::cout << "3. Polynomial Interpolation (Newton)" << std::endl;
    std::cout << "4. Cardinal Cubic Spline Interpolation" << std::endl; 
    std::cout << "5. Both Linear and Polynomial Interpolation" << std::endl;
    std::cout << "Enter your choice (1/2/3/4/5): ";
    std::cin >> option;

    double user_x;
    std::cout << "Enter a value of x: ";
    std::cin >> user_x;

    if (std::cin.fail()){
        throw std::invalid_argument("Invalid input. Please enter a numerical value. ");
    }

    try {
        // Creamos interpoladores
        LinearInterpolator LinearInterp(x_nodes, y_nodes);
        // PolynomialInterpolator PolyInterp(x_nodes, y_nodes);
        GslPolynomialInterpolator GslPolyInterp(x_nodes, y_nodes);
        NewtonInterpolator NewtonInterp(x_nodes, y_nodes);
        // CardinalCubicSpline Spline(x_nodes, y_nodes);
        CardinalCubicSpline Spline(x_nodes, y_nodes, 0 , delta_x);

        switch (option) {
            case 1:
                std::cout << "Linear interpolation at x = " << user_x << ": " << LinearInterp(user_x) << "\n";
                break;
            case 2:
                std::cout << "Polynomial (Lagrange) interpolation at x = " << user_x << ": " << GslPolyInterp(user_x) << "\n";
                break;
            case 3:
                std::cout << "Polynomial (Newton) interpolation at x = " << user_x << ": " << NewtonInterp(user_x) << "\n"; // Aquí sustituiría con NewtonInterpolator
                break;
            case 4:
                std::cout << "Cardinal cubic B-spline interpolation at x = " << user_x << ": " << Spline(user_x) << "\n";
                break;
            case 5:
                std::cout << "Linear interpolation at x = " << user_x << ": " << LinearInterp(user_x) << "\n";
                std::cout << "Polynomial (Lagrange) interpolation at x = " << user_x << ": " << GslPolyInterp(user_x) << "\n";
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error:" << e.what() << std::endl;
    }

    return 0;
}

*/

/* FIRST MAIN

// Estamos probando el buen funcionamiento de las diferentes interpolaciones
int main() {
    // Nodos de ejemplo
    std::vector<double> x_nodes = {0.0, 1.0, 2.0, 3.0};
    std::vector<double> y_nodes = {1.0, 2.0, 0.0, 5.0};

    // Menú interactivo para elegir la interpolación
    int option;
    std::cout << "Choose the interpolation method:" << std::endl;
    std::cout << "1. Linear Interpolation" << std::endl;
    std::cout << "2. Polynomial Interpolation (Lagrange)" << std::endl;
    std::cout << "3. Polynomial Interpolation (Newton)" << std::endl;
    std::cout << "4. Both Linear and Polynomial Interpolation" << std::endl;
    std::cout << "Enter your choice (1/2/3/4): ";
    std::cin >> option;

    double user_x;
    std::cout << "Enter a value of x: ";
    std::cin >> user_x;

    if (std::cin.fail()){
        throw std::invalid_argument("Invalid input. Please enter a numerical value. ");
    }

    try {
        // Creamos interpoladores
        LinearInterpolator LinearInterp(x_nodes, y_nodes);
        PolynomialInterpolator PolyInterp(x_nodes, y_nodes);
        GslPolynomialInterpolator GslPolyInterp(x_nodes, y_nodes);
        NewtonInterpolator NewtonInterp(x_nodes, y_nodes);

        if (option == 1) {
            // Interpolación lineal
            std::cout << "Linear interpolation at x = " << user_x << ": " << LinearInterp(user_x) << std::endl; // 1 cuando x = 1.5
        } else if (option == 2) {
            // Interpolación polinómica (Lagrange)
            std::cout << "Polynomial (Lagrange) interpolation at x = " << user_x << ": " << PolyInterp(user_x) << std::endl; // 0.75 cuando x = 1.5 y -13 cuando x igual a -1
            // Interpolación polinómica (Lagrange con GSL)
            std::cout << "Polynomial interpolation at x = " << user_x << ": " << GslPolyInterp(user_x) << std::endl; 
        } else if (option == 3) {
            // Interpolación polinómica (Newton) 
            std::cout << "Newton interpolation at x = " << user_x << ": " << NewtonInterp(user_x) << std::endl; 
        } else if (option == 3) {
        } else if (option == 4) {
            std::cout << "Polynomial (Lagrange) interpolation at x = " << user_x << ": " << PolyInterp(user_x) << std::endl; // 0.75 cuando x = 1.5 y -13 cuando x igual a -1
            std::cout << "Linear interpolation at x =  " << user_x << ": " << LinearInterp(user_x) << std::endl; // 1 cuando x = 1.5
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

*/
