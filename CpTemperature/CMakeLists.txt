project(cpptemperature)

# Find OpenMP package
find_package(OpenMP REQUIRED)

add_executable(cpptemperature main.cpp Data1d.cpp Data3d.cpp Temperature.cpp Siminfo.cpp)

# Link OpenMP libraries and flags to the target
if(OpenMP_CXX_FOUND)
    target_link_libraries(cpptemperature PUBLIC OpenMP::OpenMP_CXX)
endif()

install(TARGETS cpptemperature RUNTIME DESTINATION bin)
