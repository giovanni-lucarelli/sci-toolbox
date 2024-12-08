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
    std::cout<< "species " <<iris.get_header()[5] <<"\n";
    std::cout<< "mean " <<iris.mean("SepalWidthCm")<<"\n"; 

    std::vector<std::string> att ={"SepalLengthCm","SepalWidthCm"};

    std::cout<< "correlation " <<iris.correlation("SepalWidthCm", "PetalWidthCm")<<"\n";
    iris.correlation_matrix(att);

    iris.table("Species");

    std::cout <<"Quantile-25:" <<iris.quantile("SepalWidthCm", 0.25)<<"\n";
    std::cout <<"Quantile-50:" <<iris.quantile("SepalWidthCm", 0.50)<<"\n";
    std::cout <<"Quantile-75:" <<iris.quantile("SepalWidthCm", 0.75)<<"\n";
    std::cout <<"Quantile-100:" <<iris.quantile("SepalWidthCm", 1.0)<<"\n";


    return 0;
}
