#include "dataframe.hpp"
#include <iostream>

int main()
{
    /* DataFrame df{};

    std::vector<std::string> head{"Col0", "Col1"};
    std::vector<std::optional<std::variant<double, std::string>>> col0{"mario","franco","pippo"};
    std::vector<std::optional<std::variant<double, std::string>>> col1{1.,2.,3.};

    df.add_column("Col0", col0);
    df.add_column("Col1", col1);

    std::cout<< "max: "<< df.max("Col1")<<"\n";
    std::cout<< "shape: "<< df.shape().first << "," << df.shape().second <<"\n";
    
    df.head(); */
    

    DataFrame iris{};
    
    iris.read_csv("./datasets/iris.csv");
    iris.head();
    std::cout<< "mean " <<iris.mean("SepalWidthCm")<<"\n"; 

    std::vector<std::string> att ={"SepalLengthCm","SepalWidthCm"};

    std::cout<< "correlation " <<iris.correlation("SepalWidthCm", "PetalWidthCm")<<"\n";
    iris.correlation_matrix(att);

    iris.table("Species");
    return 0;
}
