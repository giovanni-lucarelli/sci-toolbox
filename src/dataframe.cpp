#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <numeric>
#include <variant>
#include <optional>         
#include <gsl/gsl_statistics.h>
#include <boost/histogram.hpp>
#include <boost/json.hpp>
#include <map> 
#include "dataframe.hpp"


const std::vector<ColumnType>& DataFrame::get_data(){
    return data;
}

// first = nrows, second = ncols
std::pair<unsigned int,unsigned int> DataFrame::shape() const {
    std::pair<unsigned int,unsigned int> dims=std::make_pair(data[0].size(),data.size());
    return dims;
}

const ColumnType& DataFrame::get_column(const size_t column){
    return data[column];
}

const std::vector<std::string>& DataFrame::get_header(){
    return column_names;
}

void DataFrame::add_column(const std::string& column_name, const ColumnType& new_col) {
// If data is not empty, check that the new column has the same length
    if (!data.empty() && new_col.size() != data[0].size()) {
        throw std::invalid_argument("New column must have the same number of rows as existing data");
    }
    
    // Add the column name
    column_names.push_back(column_name);
    
    // Add the column data
    data.push_back(new_col);
}

void DataFrame::set_header(const std::vector<std::string>& new_header){
    column_names.clear();
    column_names = new_header;
}

unsigned int DataFrame::find_idx(const std::string& name) const {
    // Find the attribute
    auto it = std::find(column_names.begin(), column_names.end(), name);
    if (it != column_names.end()) {
        // Calculate the index by subtracting the beginning iterator from the found iterator
        return std::distance(column_names.begin(), it);
    } else {
        std::cout << "Element not found\n";
        throw std::invalid_argument("Attribute not found");
    }
}

// Metodo per ottenere una colonna filtrata solo con double 
// serve per usare tutte le routine gls
std::vector<double> DataFrame::get_double_column(const std::string& name) const{
    std::vector<double> double_values{};
    for (const auto &cell : data[find_idx(name)])
    {
        if (cell && std::holds_alternative<double>(*cell))
        {
            double_values.push_back(std::get<double>(*cell));
        }
    }
    return double_values;
}

std::vector<std::string> DataFrame::get_string_column(const std::string& name) const{
    std::vector<std::string> string_values{};
    for (const auto &cell : data[find_idx(name)])
    {
        if (cell && std::holds_alternative<std::string>(*cell))
        {
            string_values.push_back(std::get<std::string>(*cell));
        }
    }
    return string_values;
}

double DataFrame::mean(const std::string& name) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values= get_double_column(name);
    // If values does not contain any numerical value, raise an error
    if (values.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }

    return gsl_stats_mean(values.data(), 1, values.size());
}

double DataFrame::median(const std::string& name) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values= get_double_column(name);
    // If values does not contain any numerical value, raise an error
    if (values.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }

    return gsl_stats_median(values.data(), 1, values.size());
}

double DataFrame::min(const std::string& name) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values= get_double_column(name);
    // If values does not contain any numerical value, raise an error
    if (values.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }

    return gsl_stats_min(values.data(), 1, values.size());
}

double DataFrame::max(const std::string& name) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values= get_double_column(name);
    // If values does not contain any numerical value, raise an error
    if (values.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }

    return gsl_stats_max(values.data(), 1, values.size());
}

double DataFrame::quantile(const std::string& name, const double& q) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values= get_double_column(name);
    // If values does not contain any numerical value, raise an error
    if (values.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }
    std::sort(values.begin(), values.end());

    return gsl_stats_quantile_from_sorted_data(values.data(), 1, values.size(), q);
    //return gsl_stats_max(values.data(), 1, values.size());
}

double DataFrame::var(const std::string& name) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values= get_double_column(name);
    // If values does not contain any numerical value, raise an error
    if (values.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }

    return gsl_stats_variance(values.data(), 1, values.size());
}

double DataFrame::sd(const std::string& name) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values= get_double_column(name);
    // If values does not contain any numerical value, raise an error
    if (values.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }

    return gsl_stats_sd(values.data(), 1, values.size());
}

double DataFrame::covariance(const std::string& name1, const std::string& name2) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values1= get_double_column(name1);
    std::vector<double> values2= get_double_column(name2);
    // If values does not contain any numerical value, raise an error
    if (values1.empty()||values2.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }
    // If sizes don't match, raise an error
    if (values1.size() != values2.size()) {
        throw std::runtime_error("Error in computeCov(): incompatible sizes to compute covariance.");
    }
    // If everything is ok, return the covariance
    return gsl_stats_covariance(values1.data(), 1, values2.data(),1,values1.size());
}

double DataFrame::correlation(const std::string& name1, const std::string& name2) {
    // If values does not contain any numerical value, raise an error
    // Convert the column into a std::vector of doubles
    std::vector<double> values1= get_double_column(name1);
    std::vector<double> values2= get_double_column(name2);
    // If values does not contain any numerical value, raise an error
    if (values1.empty()||values2.empty()) {
        throw std::runtime_error("Error in function mean(): vector is empty.");
    }
    // If sizes don't match, raise an error
    if (values1.size() != values2.size()) {
        throw std::runtime_error("Error in computeCov(): incompatible sizes to compute covariance.");
    }
    // If everything is ok, return the covariance
    return gsl_stats_correlation(values1.data(), 1, values2.data(),1,values1.size());
}

bool DataFrame::is_numeric(const std::string& name){
    for (const auto &cell : data[find_idx(name)])
    {
        if (std::holds_alternative<std::string>(*cell))
        { 
            return false;
        } 
    }
    return true;
}

void DataFrame::correlation_matrix(std::vector<std::string>& names) {
    // Determine the maximum length of a numeric name for formatting
    int max_name_len = 0;
    for (const auto& name : names) {
        if (is_numeric(name)) {
            max_name_len = std::max(max_name_len, static_cast<int>(name.length()));
        }
    }

    // Print the header row with appropriate spacing
    for (const auto& name : names) {
        if (is_numeric(name)) {
            std::cout << std::setw(max_name_len + 1) << name;
        }
    }
    std::cout << std::endl;

    // Print the correlation matrix with formatted output
    for (const auto& name1 : names) {
        if (is_numeric(name1)) {
            for (const auto& name2 : names) {
                if (is_numeric(name2)) {
                    // Assuming correlation() returns a double value
                    std::cout << std::fixed << std::setprecision(4) << std::setw(max_name_len + 1) << correlation(name1, name2);
                }
            }
            std::cout << std::endl;
        }
    }
}

void DataFrame::table(const std::string& name){
    std::map<std::string,unsigned int> table{};
    for (auto& val : get_string_column(name)) {
        table[val] ++; // Update the frequency
    }

    for(auto &el : table){
        std::cout<<std::right<<std::setw(15)<<el.first << " ";
    }
    std::cout << std::endl;

    for(auto &el : table){
        std::cout<<std::right<<std::setw(15)<<el.second << " ";
    }
    std::cout << std::endl;

}

// Metodo per generare un istogramma da una colonna specifica
void DataFrame::histogram(const std::string& name, int num_bins) const
{
    std::vector<double> values{get_double_column(name)};
    
    if (values.empty())
    {
        std::cerr << "Empty column: " << name << std::endl;
        return;
    }

    // Determine the minimum and maximum values
    double min_value = *std::min_element(values.begin(), values.end());
    double max_value = *std::max_element(values.begin(), values.end());

    // Add a small epsilon to the maximum value to ensure it falls in the last bin
    double epsilon = std::numeric_limits<double>::epsilon();
    double max_value_adjusted = max_value + 10*epsilon;

    // Build a histogram with an inclusive upper bound
    auto hist = boost::histogram::make_histogram(
        boost::histogram::axis::regular<>(num_bins, min_value, max_value_adjusted)
    );

    // Fill the histogram
    for (double value : values)
    {
        hist(value);
    }

    // Print the histogram
    for (auto&& bin : boost::histogram::indexed(hist))
    {
        std::cout << "[" << bin.index() << "] " << bin.bin(0).lower() << " - " << bin.bin(0).upper()
                  << ": " << *bin << std::endl;
    }
}


DataFrame::row_iterator::row_iterator(const DataFrame& df, size_t row) 
    : dataframe(df), current_row(row) {
    // Calcola il numero massimo di righe come la dimensione della colonna più corta
    max_rows = std::numeric_limits<size_t>::max();
    for (const auto& column : dataframe.data) {
        max_rows = std::min(max_rows, column.size());
    }
}

DataFrame::row_iterator::value_type DataFrame::row_iterator::operator*() const {
    value_type row;
    for (const auto& column : dataframe.data) {
        // Check if the index is valid for this column
        if (current_row < column.size()) {
            const auto& optional_value = column[current_row];
            
            // Check if the optional value exists
            if (optional_value.has_value()) {
                const auto& value = optional_value.value();
                
                // Add the value to the row, preserving its original type
                if (std::holds_alternative<double>(value)) {
                    row.push_back(std::get<double>(value));
                }
                else if (std::holds_alternative<std::string>(value)) {
                    row.push_back(std::get<std::string>(value));
                }
            }
            else {
                // Optional: handle null values (you might want to push a specific variant or skip)
                row.push_back(std::numeric_limits<double>::quiet_NaN()); // or some other default
            }
        }
    }
    return row;
}

DataFrame::row_iterator& DataFrame::row_iterator::operator++() {
    ++current_row;
    return *this;
}

// Post-increment operator
DataFrame::row_iterator DataFrame::row_iterator::operator++(int) {
    row_iterator temp = *this;
    ++current_row;
    return temp;
}

// Addition operator
DataFrame::row_iterator DataFrame::row_iterator::operator+(difference_type n) const {
    return row_iterator(dataframe, current_row + n);
}

// Comparison operators
bool DataFrame::row_iterator::operator<(const row_iterator& other) const {
    return current_row < other.current_row;
}

bool DataFrame::row_iterator::operator!=(const row_iterator& other) const {
    return current_row != other.current_row;
}

bool DataFrame::row_iterator::operator==(const row_iterator& other) const {
    return current_row == other.current_row;
}

// Metodi nella classe DataFrame per supportare l'iterazione per righe
DataFrame::row_iterator DataFrame::begin() const { 
    return row_iterator(*this, 0); 
}

DataFrame::row_iterator DataFrame::end() const { 
    // Calcola il numero massimo di righe come la dimensione della colonna più corta
    size_t max_rows = std::numeric_limits<size_t>::max();
    for (const auto& column : data) {
        max_rows = std::min(max_rows, column.size());
    }
    return row_iterator(*this, max_rows); 
}

void DataFrame::head(){
    
    // Determine the maximum length of a numeric name for formatting
    int max_name_len{0};
    for (const auto& name : column_names) {
        max_name_len = std::max(max_name_len, static_cast<int>(name.length()));
    }

    const int spacing{max_name_len + 2};
    // Print the header row with appropriate spacing
    for (const auto& name : column_names) {
        std::cout << std::setw(spacing) << name;
    }
    std::cout << std::endl;
    
    for (auto rowIt = this->begin(); rowIt < std::min(this->begin()+5, this->end()); rowIt++)  
    {   
        for (const auto& val : *rowIt) {
            if (std::holds_alternative<double>(val)) {
                std::cout << std::setw(spacing)<< std::get<double>(val);
            }
            else if (std::holds_alternative<std::string>(val)) {
                std::cout << std::setw(spacing)<< std::get<std::string>(val);
            }
        }
        std::cout << std::endl;
    } 
}

void DataFrame::read_csv(const std::string& filename, char separator, bool has_header) {
    // Clear existing data
    column_names.clear();
    data.clear();

    // Open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
        
    // Read header if specified
    if (has_header) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Empty CSV file");
        }

        std::istringstream header_stream(line);
        std::string column_name;
        
        // Parse header columns
        while (std::getline(header_stream, column_name, separator)) {
            column_names.push_back(column_name);
        }
    }

    // Read all rows and store in raw_data

    std::vector<std::vector<std::string>> raw_data;
    while (std::getline(file, line)) {
        std::istringstream row_stream(line);
        std::string cell;
        std::vector<std::string> row_cells;

        // Parse each cell in the row
        while (std::getline(row_stream, cell, separator)) {
            // Trim whitespace
            cell.erase(0, cell.find_first_not_of(" \t\r\n"));
            cell.erase(cell.find_last_not_of(" \t\r\n") + 1);

            // TODO aggiungere degli if per castare come double/nullptr o string!
            row_cells.push_back(cell);
        }

        // Add row to raw data
        raw_data.push_back(row_cells);
    }

    // If no header was specified, create default column names
    if (column_names.empty()) {
        for (size_t i = 0; i < raw_data[0].size(); ++i) {
            column_names.push_back("Column_" + std::to_string(i));
        }
    }

    // Transpose and convert raw_data to column-based storage
    if (!raw_data.empty()) {
        // Initialize columns
        data.resize(column_names.size());
        for (auto& column : data) {
            column.clear();
        }

        // Populate columns
        for (const auto& row : raw_data) {
            for (size_t col = 0; col < column_names.size(); ++col) {
                if (col < row.size()) {
                    // Try to convert to double, otherwise store as string
                    try {
                        if (row[col].empty()) {
                            data[col].push_back(std::nullopt);
                        } else {
                            double numeric_value = std::stod(row[col]);
                            data[col].push_back(numeric_value);
                        }
                    } catch (const std::invalid_argument&) {
                        data[col].push_back(row[col]);
                    }
                } else {
                    // If row is shorter, push null
                    data[col].push_back(std::nullopt);
                }
            }
        }
    }
}

/* void DataFrame::read_json(const std::string& filename)
{
    try
    {
        // Apri il file
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Errore nell'apertura del file: " << filename << std::endl;
            throw std::invalid_argument("file not found");
        }

        // Leggi il contenuto del file in una stringa
        std::string json_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Parsing del JSON
        boost::json::value json_value = boost::json::parse(json_content);

        // Estrai i nomi delle colonne
        const auto& json_object = json_value.as_object();
        column_names.clear();
        for (const auto& col_name : json_object.at("columns").as_array())
        {
            column_names.push_back(col_name.as_string().c_str());
        }

        // Inizializza le colonne vuote
        data.clear();
        data.resize(column_names.size());

        // Estrai i dati riga per riga
        const auto& rows = json_object.at("data").as_array();
        for (const auto& row : rows)
        {
            const auto& row_array = row.as_array();
            for (size_t i = 0; i < row_array.size(); ++i)
            {
                const auto& cell = row_array[i];
                if (cell.is_null())
                {
                    data[i].push_back(std::nullopt);
                }
                else if (cell.is_double() || cell.is_int64())
                {
                    data[i].push_back(cell.to_number<double>());
                }
                else if (cell.is_string())
                {
                    data[i].push_back(cell.as_string().c_str());
                }
                else
                {
                    std::cerr << "Tipo di dato non supportato nella cella" << std::endl;
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Errore durante la lettura del JSON: " << e.what() << std::endl;
    }
} */

void DataFrame::read_json(const std::string& filename) {
    // Clear existing data
    column_names.clear();
    data.clear();

    // Read file contents
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Parse entire file contents
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonStr = buffer.str();

    // Parse JSON 
    boost::json::value parsedJson = boost::json::parse(jsonStr);

    // Ensure it's an array
    if (!parsedJson.is_array()) {
        throw std::runtime_error("JSON must be an array of objects");
    }

    const boost::json::array& jsonArray = parsedJson.as_array();
    
    if (jsonArray.empty()) {
        throw::std::runtime_error("No data to load");
    }

    // Extract column names from first object
    const boost::json::object& firstObj = jsonArray[0].as_object();
    for (const auto& [key, value] : firstObj) {
        column_names.push_back(std::string(key));
    }

    // Prepare columns
    data.resize(column_names.size());

    // Populate data
    for (const auto& jsonRow : jsonArray) {
        const boost::json::object& rowObj = jsonRow.as_object();
        
        // Iterate through expected columns
        for (size_t colIndex = 0; colIndex < column_names.size(); ++colIndex) {
            const std::string& colName = column_names[colIndex];
            
            // Find the value for this column
            auto it = rowObj.find(colName);
            if (it == rowObj.end()) {
                // Column not found, add null
                data[colIndex].push_back(std::optional<DataType>{std::nullopt});
                continue;
            }

            // Convert value based on type
            const boost::json::value& value = it->value();
            
            if (value.is_double()) {
                data[colIndex].push_back(value.as_double());
            }
            else if (value.is_string()) {
                data[colIndex].push_back(std::string(value.as_string()));
            }
            else {
                // Unsupported type, add null
                data[colIndex].push_back(std::optional<DataType>{std::nullopt});
            }
        }
    }
}
