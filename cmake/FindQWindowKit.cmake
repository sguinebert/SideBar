# Assume QWindowKit is located at ${QWindowKit_SOURCE_DIR}
# And its binary output at ${QWindowKit_BINARY_DIR}

# Include directories
set(QWindowKit_INCLUDE_DIRS "${QWindowKit_SOURCE_DIR}/include")

# Library paths
# Adjust these paths based on where QWindowKit outputs its binaries
#set(QWindowKit_LIBRARY "${CMAKE_BINARY_DIR}/qwindowkit/lib/libQWindowKit.a") # Example for static lib
# Search for QWKCore.a

find_library(QWINDOWKIT_CORE_LIB
    NAMES QWKCore
    PATHS ${CMAKE_BINARY_DIR}/qwindowkit/lib
    NO_DEFAULT_PATH
)

# Search for QWKWidgets.a
find_library(QWINDOWKIT_WIDGETS_LIB
    NAMES QWKWidgets
    PATHS ${CMAKE_BINARY_DIR}/qwindowkit/lib
    NO_DEFAULT_PATH
)

# Search for QWKQuick.a
find_library(QWINDOWKIT_QUICK_LIB
    NAMES QWKQuick
    PATHS ${CMAKE_BINARY_DIR}/qwindowkit/lib
    NO_DEFAULT_PATH
)


# Define imported target for ease of linking
add_library(QWindowKit::QWindowKit UNKNOWN IMPORTED)
set_target_properties(QWindowKit::QWindowKit PROPERTIES
    IMPORTED_LOCATION "${QWindowKit_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${QWindowKit_INCLUDE_DIRS}"
)
