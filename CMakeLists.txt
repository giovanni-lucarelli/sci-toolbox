cmake_minimum_required(VERSION 3.10)

# Nome del progetto e linguaggio
project(MyStatApp LANGUAGES CXX)

# Imposta lo standard C++ (es. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Trova la libreria GSL
find_package(GSL REQUIRED)
# Trova Boost con la libreria JSON
find_package(Boost REQUIRED COMPONENTS json system)

if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Aggiungi la directory src per includere i file della libreria
add_subdirectory(src)

# Aggiungi le directory di include
include_directories(${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

# Crea l'eseguibile stat_app nella cartella apps
add_executable(stat_app
    apps/stat_app.cpp
)

# Linka la libreria condivisa dataframe all'eseguibile stat_app
target_link_libraries(stat_app PRIVATE dataframe Boost::json Boost::system GSL::gsl GSL::gslcblas)
