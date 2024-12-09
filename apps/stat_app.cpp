#include "dataframe.hpp"
#include <iostream>

int main()
{
    DataFrame df{};

    std::vector<std::string> head{"Col0", "Col1"};
    std::vector<std::optional<std::variant<double, std::string>>> col0{"mario", std::nullopt,"pippo", std::nullopt};
    std::vector<std::optional<std::variant<double, std::string>>> col1{1.,std::nullopt,2., 3.};

    df.add_column("Col0", col0);
    df.add_column("Col1", col1);

    std::cout<< "max: "<< df.max("Col1")<<"\n";
    std::cout<< "mean: "<< df.mean("Col1")<<"\n"; // errore!!!!!!!!!!!!
    std::cout<< "median: "<< df.median("Col1")<<"\n";
    /* std::cout<< "shape: "<< df.shape().first << "," << df.shape().second <<"\n";
    
    df.head();

    df.table("Col0"); */
    

    //DataFrame iris{};
    
    // JSON VERSION
    
    /* iris.read_json("iris.json");
    iris.head();
    std::cout<< "species " <<iris.get_header()[0] <<"\n";
    std::cout<< "species " <<iris.get_header()[1] <<"\n";
    std::cout<< "species " <<iris.get_header()[2] <<"\n";
    std::cout<< "species " <<iris.get_header()[3] <<"\n";
    std::cout<< "species " <<iris.get_header()[4] <<"\n";

    std::cout<< "mean " <<iris.mean("sepalWidth")<<"\n"; 

    std::vector<std::string> att ={"sepalLength","sepalWidth"};

    std::cout<< "correlation " <<iris.correlation("sepalWidth", "petalWidth")<<"\n";
    iris.correlation_matrix(att);

    iris.table("species");

    std::cout <<"Quantile-25:" <<iris.quantile("sepalWidth", 0.25)<<"\n";
    std::cout <<"Quantile-50:" <<iris.quantile("sepalWidth", 0.50)<<"\n";
    std::cout <<"Quantile-75:" <<iris.quantile("sepalWidth", 0.75)<<"\n";
    std::cout <<"Quantile-100:" <<iris.quantile("sepalWidth", 1.0)<<"\n";

    iris.histogram("sepalWidth"); */


    // CSV VERSION

    //iris.read_csv("./datasets/iris.csv");
   /*  std::cout<< "mean " <<iris.mean("SepalWidthCm")<<"\n"; 

    std::vector<std::string> att ={"SepalLengthCm","SepalWidthCm"};

    std::cout<< "correlation " <<iris.correlation("SepalWidthCm", "PetalWidthCm")<<"\n";
    iris.correlation_matrix(att);

    iris.table("Species");

    std::cout <<"Quantile-25:" <<iris.quantile("SepalWidthCm", 0.25)<<"\n";
    std::cout <<"Quantile-50:" <<iris.quantile("SepalWidthCm", 0.50)<<"\n";
    std::cout <<"Quantile-75:" <<iris.quantile("SepalWidthCm", 0.75)<<"\n";
    std::cout <<"Quantile-100:" <<iris.quantile("SepalWidthCm", 1.0)<<"\n";

    iris.histogram("SepalWidthCm"); */

    return 0;
}
