cmake_minimum_required(VERSION 3.18)
project(tess-tools LANGUAGES CXX)

add_subdirectory(CpTemperature)

# ────────────────────────────────────────────────────────────────
# Install the entire tess/testdata tree into the Python package
install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/tess/testdata/Head
  DESTINATION tess
  FILES_MATCHING PATTERN "*"
)