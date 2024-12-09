#ifndef DATAFRAME_HPP
#define DATAFRAME_HPP

#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <cmath>

using DataType = std::variant<double, std::string>;
using ColumnType = std::vector<std::optional<DataType>>;

class DataFrame
{   
    
private:
    std::vector<std::string> column_names{};
    std::vector<ColumnType> data{};
public:
    DataFrame() = default; // consente di creare DataFrame df{}, senza inizializzazione
    ~DataFrame() = default;


    // ############################################
    //      methods to manage the data frame     
    // ############################################

    void read_csv(const std::string& filename, char separator = ',', bool has_header = true);

    void read_json(const std::string& filename);

    const std::vector<ColumnType>& get_data();

    std::pair<unsigned int,unsigned int> shape() const;

    const ColumnType& get_column(const size_t column);

    const std::vector<std::string>& get_header();
    
    void add_column(const std::string& column_name, const ColumnType& new_col);

    void set_header(const std::vector<std::string>& new_header);

    unsigned int find_idx(const std::string& name) const;

    bool is_numeric(const std::string& name);

    // Metodo per ottenere una colonna filtrata solo con double 
    // serve per usare tutte le routine gls
    std::vector<double> get_double_column(const std::string& name) const;

    std::vector<std::string> get_string_column(const std::string& name) const;

    // ################################
    // #     stastistical methods     #
    // ################################

    double mean(const std::string& name);

    double median(const std::string& name);
    
    double min(const std::string& name);
    
    double max(const std::string& name);

    double quantile(const std::string& name, const double& q);
    
    double var(const std::string& name);

    double sd(const std::string& name);
    
    double covariance(const std::string& name1, const std::string& name2);

    double correlation(const std::string& name1, const std::string& name2);

    void correlation_matrix(std::vector<std::string>& names);

    void table(const std::string& name);

    void head();

    void histogram(const std::string& name, int num_bins = 10) const;


    // ##############################
    // #     row iterator class     #
    // ##############################

    class row_iterator {
    private:
        const DataFrame& dataframe;
        size_t current_row;
        size_t max_rows;

    public:
        // Tipi richiesti per gli iterator traits
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::vector<std::variant<double, std::string>>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        row_iterator(const DataFrame& df, size_t row = 0);

        value_type operator*() const;

        row_iterator& operator++();
        
        // Post-increment operator
        row_iterator operator++(int);

        // Addition operator
        row_iterator operator+(difference_type n) const;

        // Comparison operators
        bool operator<(const row_iterator& other) const;

        bool operator!=(const row_iterator& other) const;

        bool operator==(const row_iterator& other) const;
    };

    // Metodi nella classe DataFrame per supportare l'iterazione per righe
    row_iterator begin() const;

    row_iterator end() const;

};

#endif // DATAFRAME_HPP
