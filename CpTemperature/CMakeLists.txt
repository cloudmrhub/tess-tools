project(cpptemperature)

add_executable(cpptemperature main.cpp Data1d.cpp Data3d.cpp Temperature.cpp Siminfo.cpp)

install(TARGETS cpptemperature RUNTIME DESTINATION bin)
