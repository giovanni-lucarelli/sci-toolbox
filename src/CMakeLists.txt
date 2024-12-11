# src/CMakeLists.txt
# Add the src and apps directories conditionally
if (BUILD_LIB_DATAFRAME)
    # Create the shared library dataframe
    add_library(dataframe SHARED
        dataframe.cpp
    )

    # Link Boost and GSL to the dataframe shared library
    target_link_libraries(dataframe PUBLIC
        Boost::json
        Boost::system
        GSL::gsl
        GSL::gslcblas
    )

    # Specify the header paths for the library
    target_include_directories(dataframe PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
    )

    message(STATUS "Building the first library and its app")

endif()

# Add the src and apps directories conditionally
if (BUILD_LIB_INTERPOL)
    # Create the shared library interpolation
    add_library(interpolation SHARED
                CardinalCubicSpline.cpp
                GslPolynomialInterpolator.cpp
                Interpolator.cpp
                LinearInterpolator.cpp
                NewtonInterpolator.cpp
    )

    # Link Boost and GSL to the interpolation shared library
    target_link_libraries(interpolation PUBLIC
        Boost::json
        Boost::system
        Boost::filesystem
        GSL::gsl
        GSL::gslcblas
    )

    # Specify the header paths for the library
    target_include_directories(interpolation PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
    )

    message(STATUS "Building the second library and its app")

endif()
