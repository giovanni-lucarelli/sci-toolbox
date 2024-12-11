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
    std::vector<std::string> column_names;
    std::vector<ColumnType> data;
public:
    DataFrame() = default; 
    ~DataFrame() = default;

    /* ---------------------------------------------------------------------- */
    /*                         DATA STRUCTURE METHODS                         */
    /* ---------------------------------------------------------------------- */

    void read_csv(const std::string& filename, char separator = ',', bool has_header = true);

    void read_json(const std::string& filename);

    const std::vector<ColumnType>& get_data() const;

    std::pair<unsigned int,unsigned int> shape() const;

    const ColumnType& get_column(const size_t column) const;

    const std::vector<std::string>& get_header() const;
    
    void add_column(const std::string& column_name, const ColumnType& new_col);

    void set_header(const std::vector<std::string>& new_header);

    void drop_row(const unsigned int& row);

    void drop_col(const std::string& name);

    unsigned int find_idx(const std::string& name) const;

    bool is_numeric(const std::string& name) const;

    void table_nan() const;

    void drop_row_nan();

    // Metodo per ottenere una colonna filtrata solo con double 
    // serve per usare tutte le routine gls
    std::vector<double> get_double_column(const std::string& name) const;

    std::vector<std::string> get_string_column(const std::string& name) const;

    // usefull to display the output in a formatted style
    unsigned int formatting_width() const;

    /* ---------------------------------------------------------------------- */
    /*                               STATISTICS                               */
    /* ---------------------------------------------------------------------- */

    double mean(const std::string& name) const;

    double median(const std::string& name) const;
    
    double min(const std::string& name) const;
    
    double max(const std::string& name) const;

    double quantile(const std::string& name, const double& q) const;
    
    double var(const std::string& name) const;

    double sd(const std::string& name) const;
    
    double covariance(const std::string& name1, const std::string& name2) const;

    double correlation(const std::string& name1, const std::string& name2) const;

    void correlation_matrix(std::vector<std::string>& names) const;

    void table(const std::string& name) const;

    void head() const;

    void histogram(const std::string& name, int num_bins = 10) const;

    void summary() const;

    /* ---------------------------------------------------------------------- */
    /*                           ROW ITERATOR CLASS                           */
    /* ---------------------------------------------------------------------- */

    class row_iterator {
    private:
        const DataFrame& dataframe;
        size_t current_row;
        size_t max_rows;

    public:
        // Tipi richiesti per gli iterator traits
        using iterator_category = std::forward_iterator_tag;
        using value_type = ColumnType;
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

    row_iterator begin() const;

    row_iterator end() const;

};

#endif // DATAFRAME_HPP
