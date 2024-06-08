cmake_minimum_required(VERSION 3.10)
project(OnlineFoodOrderingSystem)

set(CMAKE_CXX_STANDARD 17)

# Find required packages
find_package(Crow CONFIG REQUIRED)
find_package(MySQL CONFIG REQUIRED)

# Add source files
set(SOURCES
        main.cpp
        db_connection.cpp
        user_controller.cpp
        restaurant_controller.cpp
        menu_controller.cpp
        order_controller.cpp
)

# Include directories
include_directories(${Crow_INCLUDE_DIRS})
include_directories(${MySQL_INCLUDE_DIRS})

# Add the executable
add_executable(OnlineFoodOrderingSystem ${SOURCES})

# Link libraries
target_link_libraries(OnlineFoodOrderingSystem PRIVATE Crow::Crow ${MySQL_LIBRARIES})

# Install the executable
install(TARGETS OnlineFoodOrderingSystem DESTINATION bin)

# add test cases
# enable_testing()
# add_subdirectory(tests)
