cmake_minimum_required(VERSION 3.10)

# Nome del progetto e linguaggio
project(MyStatApp LANGUAGES CXX)

# Imposta lo standard C++ (es. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Trova la libreria GSL
find_package(GSL REQUIRED)

# Aggiungi la directory src per includere i file della libreria
add_subdirectory(src)

# Specifica il percorso degli header per la libreria
include_directories(${CMAKE_SOURCE_DIR}/src)

# Crea l'eseguibile stat_app nella cartella apps
add_executable(stat_app
    apps/stat_app.cpp
)

# Linka la libreria condivisa dataframe all'eseguibile stat_app
target_link_libraries(stat_app PRIVATE dataframe GSL::gsl GSL::gslcblas)

# Copia datasets e output directories nella build directory
file(COPY ${CMAKE_SOURCE_DIR}/datasets DESTINATION ${CMAKE_BINARY_DIR})

