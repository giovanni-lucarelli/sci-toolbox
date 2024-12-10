#include "dataframe.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{   
    try
    {
        if(argc<3)
        { 
            throw std::runtime_error("Not enough arguments provided.");
        }

        std::string in_dir_name="../datasets/";
        std::string in_file_name=argv[1];

        std::string out_dir_name="../output/";
        std::string out_file_name=argv[2];

        // Open a file for writing
        std::ofstream file(out_dir_name+out_file_name);
        // Check if the output file is opened correctly
        if (!file.is_open()) {
            std::cerr << "Error in opening output file." << std::endl;
            return 1; 
        }

        // redirect the output to the output file
        std::streambuf *original_buffer = std::cout.rdbuf();
        std::cout.rdbuf(file.rdbuf());

        /* ------------------------------------------------------------------ */
        /*               Dataframe Methods Testing: Iris Dataset              */
        /* ------------------------------------------------------------------ */
        DataFrame iris{};
        iris.read_csv(in_dir_name+in_file_name);

        
        iris.head();
    
        iris.summary();

        // print variance and standard deviation for each numerical feature
        for (auto &&name : iris.get_header())
        {
            if (iris.is_numeric(name))
            {
                std::cout << name << "\tVariance: " << iris.var(name) << "\tSd: " << iris.sd(name) << std::endl;
            }    
        }
        
        // print the frequency count table

        iris.table("Species");
        
        // look for nans
        iris.table_nan();
        
        // drop rows containing nans in order to compute covariance etc
        iris.drop_row_nan();

        // look at the head to check that the rows have been removed
        iris.head();
        iris.table_nan();
        iris.drop_row(1);
        iris.head();
        iris.table_nan();

/*         // compute covariance and correlation between two numerical features
        std::cout << "covariance(SepalLengthCm,SepalWidthCm)" << iris.correlation("SepalWidthCm", "PetalWidthCm")<<"\n\n";
        std::cout << "correlation(SepalLengthCm,SepalWidthCm)" << iris.correlation("SepalWidthCm", "PetalWidthCm")<<"\n\n";
        
        // print the correlation matrix between all the pairs of (numerical) features
        std::vector<std::string> att ={"SepalLengthCm",
                                        "SepalWidthCm",
                                        "PetalLengthCm",
                                        "PetalWidthCm"};
        std::cout << "CORRELATION MATRIX" << std::endl;
        iris.correlation_matrix(att); */

        // print the histogram of a (numerical) feature
        // remark: the histogram for a categorical il just the frequency table

        std::cout<<"HISTOGRAM (10 bins):   Sepal Width (Cm)"<<"\n";
        iris.histogram("SepalWidthCm");

        std::cout<<"HISTOGRAM (5 bins):   Sepal Width (Cm)"<<"\n";
        iris.histogram("SepalWidthCm", 5);


        // testing the drop col method
        iris.drop_col("SepalWidthCm");
        std::cout<<"The following table should not have the column SepalWidthCm"<<std::endl;
        iris.head();   

        /* ------------------------------------------------------------------ */

        // Restore the original standard output
        std::cout.rdbuf(original_buffer);
        std::cout<<out_file_name<<" saved successfully in "<<out_dir_name<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    


    /* DataFrame df{};

    std::vector<std::string> head{"Col0", "Col1"};
    std::vector<std::optional<std::variant<double, std::string>>> col0{"mario", std::nullopt,"pippo", std::nullopt,std::nullopt};
    std::vector<std::optional<std::variant<double, std::string>>> col1{1.,std::nullopt,2., 3., 7.};

    df.add_column("Col0", col0);
    df.add_column("Col1", col1);

    std::cout<< "min: "<< df.min("Col1")<<"\n";
    std::cout<< "max: "<< df.max("Col1")<<"\n";
    std::cout<< "mean: "<< df.mean("Col1")<<"\n"; // errore!!!!!!!!!!!!
    std::cout<< "median: "<< df.median("Col1")<<"\n";
    std::cout<< "shape: "<< df.shape().first << "," << df.shape().second <<"\n";
    std::cout<< "double col: "<< df.get_double_column("Col1")[0] << "\n";
    std::cout<< "double col: "<< df.get_double_column("Col1")[1] << "\n";
    std::cout<< "double col: "<< df.get_double_column("Col1")[2] << "\n";
    std::cout<< "double col: "<< df.get_double_column("Col1")[3] << "\n"; 
    std::cout<< "size double col: "<< df.get_double_column("Col1").size() << "\n"; 
    std::cout<< "number of nan: "<< df.count_nan("Col0") << "\n"; 
    
    df.head();

    df.table("Col0"); */
    
    // JSON VERSION
    /* DataFrame iris{};
    iris.read_json("./datasets/iris.json");

    iris.table_nan();
    iris.head();
    iris.drop_row_nan();
    iris.head();
    iris.table_nan(); */
  
    /* // CSV VERSION

    DataFrame iris;
    iris.read_csv("./datasets/iris.csv");
    std::cout<< "mean " <<iris.mean("SepalWidthCm")<<"\n"; 

    std::cout <<"names:" <<iris.get_header()[0]<<"\n";
    std::cout <<"names:" <<iris.get_header()[1]<<"\n";
    std::cout <<"names:" <<iris.get_header()[2]<<"\n";
    std::cout <<"names:" <<iris.get_header()[3]<<"\n";
    std::cout <<"names:" <<iris.get_header()[4]<<"\n";
    std::cout <<"Quantile-25:" <<iris.quantile("SepalWidthCm", 0.25)<<"\n";
    std::cout <<"Quantile-50:" <<iris.quantile("SepalWidthCm", 0.50)<<"\n";
    std::cout <<"Quantile-75:" <<iris.quantile("SepalWidthCm", 0.75)<<"\n";
    std::cout <<"Quantile-100:" <<iris.quantile("SepalWidthCm", 1.0)<<"\n";
    iris.table_nan();
    iris.head();
    iris.drop_row_nan();
    iris.head();
    iris.table_nan();
    

    std::vector<std::string> att ={"SepalLengthCm","SepalWidthCm"};

    std::cout<< "correlation " <<iris.correlation("SepalWidthCm", "PetalWidthCm")<<"\n";
    iris.correlation_matrix(att);

    iris.table("Species");

    iris.histogram("SepalWidthCm");

    iris.drop_col("SepalWidthCm");
    iris.head();
    iris.table_nan(); */

    return 0;
}
