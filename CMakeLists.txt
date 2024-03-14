cmake_minimum_required(VERSION 3.14)
project(qtBourse VERSION 0.1 LANGUAGES CXX)

# Enable C++ latest standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the necessary Qt packages
find_package(Qt6 COMPONENTS Core Quick QuickWidgets QuickControls2 REQUIRED)

# Uncomment the following lines if those modules are needed
# find_package(Qt6 COMPONENTS OpenGL REQUIRED)
# find_package(Qt6 COMPONENTS Svg REQUIRED)
find_package(Qt6 COMPONENTS WebSockets REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Charts)
# Set the module path so CMake can find FindQWindowKit.cmake
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(QWINDOWKIT_BUILD_QUICK ON CACHE BOOL "Build quick module" FORCE)
add_subdirectory(qwindowkit)

# Add the application target
add_subdirectory(RibbonUI)
#set_target_properties(QWindowKit PROPERTIES QWINDOWKIT_BUILD_QUICK ON)
#set_target_properties(QWKCore QWKWidgets QWKQuick PROPERTIES
    # ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qwindowkit/lib"
    # LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qwindowkit/lib"
    # RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qwindowkit/bin"
#)
#

# include(ExternalProject)
# ExternalProject_Add(QWindowKit
#     SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/qwindowkit
#     BINARY_DIR ${CMAKE_BINARY_DIR}/qwindowkit_build
#     INSTALL_DIR ${CMAKE_BINARY_DIR}/qwindowkit_install
#     CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/qwindowkit
# )
#list(APPEND CMAKE_PREFIX_PATH "C:/Users/gsylv/source/repos/build-mySideBar-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/qwindowkit/src/CMakeFiles/Export/fedb68827e47645b781ae9e32c483318")

set(QWindowKit_DIR "${CMAKE_BINARY_DIR}/qwindowkit/src")
set(QWindowKit_INCLUDE "${CMAKE_BINARY_DIR}/qwindowkit/include")

# find_package(QWindowKit REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/QWK
    #${QWindowKit_INCLUDE}
    # ${CMAKE_CURRENT_SOURCE_DIR}/qwindowkit/src/core
    # ${CMAKE_CURRENT_SOURCE_DIR}/qwindowkit/src/quick
    # ${CMAKE_CURRENT_SOURCE_DIR}/qwindowkit/src/widgets
)

# Add your sources
set(SOURCES
    Property.cpp
    main.cpp
    model/Filter.cpp
    model/FilterListProxy.cpp
    model/FiltersList.cpp
    model/Header.cpp
    model/HeaderList.cpp
    model/HeaderListProxy.cpp
    model/Stocks.cpp
    model/Stock.cpp
    model/TableModel.cpp
    model/TableModelProxy.cpp
)

# Add your header files
set(HEADERS
    MyType.h
    Property.h
    model/Filter.h
    model/FilterListProxy.h
    model/FiltersList.h
    model/Header.h
    model/HeaderList.h
    model/HeaderListProxy.h
    model/Stocks.h
    model/Stock.h
    model/TableModel.h
    model/TableModelProxy.h
    model/DataProvider.h
)

# Add your QML files
set(RESOURCES qml.qrc)

# Define your executable and link the necessary Qt libraries
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES}
    model/StocksProxyModel.h model/StocksProxyModel.cpp
    model/GraphList.h model/GraphList.cpp
    )
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::QuickWidgets
    Qt6::QuickControls2)
# Uncomment the following lines if those modules are needed
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::OpenGL)
# target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Svg)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::WebSockets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Sql)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Charts)
# add_dependencies(${PROJECT_NAME} QWKCore)
# target_link_libraries(${PROJECT_NAME} PUBLIC QWindowKit::Widgets)
#target_link_libraries(${PROJECT_NAME} PUBLIC QWindowKit::Quick)

target_include_directories(${PROJECT_NAME} PUBLIC ${QWindowKit_INCLUDE})

if(RIBBONUI_BUILD_STATIC_LIB)
    add_definitions(-DRIBBONUI_BUILD_STATIC_LIB)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt::Quick
        RibbonUIplugin
    )

else()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt::Quick
        RibbonUI
    )
endif()


# Set the C++ standard to the latest version (C++20 or later)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Additional configurations for resources and QML modules might be required based on your project specifics.
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/qwindowkit/include)
# include_directories(C:/Users/gsylv/source/repos/build-mySideBar-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/qwindowkit/include)
# message("qcsqdcqsdcqds : ${CMAKE_BINARY_DIR}/qwindowkit/include")
# target_include_directories(${PROJECT_NAME} PRIVATE
#   $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/qwindowkit/include>
# )
