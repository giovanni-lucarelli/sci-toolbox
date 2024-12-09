# src/CMakeLists.txt

# Crea la libreria condivisa dataframe
add_library(dataframe SHARED
    dataframe.cpp
)

# Specifica i flag di compilazione per la libreria
target_compile_options(dataframe PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

# Linka GSL alla libreria condivisa dataframe
target_link_libraries(dataframe PUBLIC Boost::json Boost::system GSL::gsl GSL::gslcblas)

# Specifica il percorso degli header per la libreria
target_include_directories(dataframe PUBLIC ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
