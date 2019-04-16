cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

add_library(FrontPanelIOSimpleGraphicWidgets
    STATIC
        "ValueBarDrawer.cpp"
        "TextField.cpp"
)

target_include_directories(FrontPanelIOSimpleGraphicWidgets PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(FrontPanelIOSimpleGraphicWidgets FpBase FpGfx)