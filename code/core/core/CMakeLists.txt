#=======================================================================================================================
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_compile_features(${PROJECT_NAME}   PRIVATE cxx_std_23)
target_sources(${PROJECT_NAME}            PRIVATE file.cpp)
#=======================================================================================================================