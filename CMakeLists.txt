cmake_minimum_required(VERSION 3.20)

project(lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

add_subdirectory(external/glm)

target_link_libraries(main glm)

add_custom_command(TARGET main
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_SOURCE_DIR}/Iris.txt $<TARGET_FILE_DIR:main>
)