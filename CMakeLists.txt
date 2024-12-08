cmake_minimum_required(VERSION 3.10)

# Nome del progetto e linguaggio
project(MyStatApp LANGUAGES CXX)

# Imposta lo standard C++ (es. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Trova la libreria GSL
find_package(GSL REQUIRED)

# Crea la libreria condivisa da dataframe.cpp
add_library(dataframe SHARED
    dataframe.cpp
)

# Specifica i flag di compilazione per la libreria
target_compile_options(dataframe PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

# Linka GSL alla libreria condivisa dataframe
target_link_libraries(dataframe PUBLIC GSL::gsl GSL::gslcblas)

# Specifica il percorso degli header per la libreria
target_include_directories(dataframe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Crea l'eseguibile stat_app
add_executable(stat_app
    stat_app.cpp
)

# Linka la libreria condivisa dataframe all'eseguibile stat_app
target_link_libraries(stat_app PRIVATE dataframe GSL::gsl GSL::gslcblas)

# Copy datasets and output directories to build directory
file(COPY ${CMAKE_SOURCE_DIR}/datasets DESTINATION ${CMAKE_BINARY_DIR})
