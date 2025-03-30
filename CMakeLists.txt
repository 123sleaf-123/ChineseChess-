cmake_minimum_required(VERSION 3.10.0) # CMake 最低版本号要求
project(ChineseChess VERSION 0.1.0) # 项目信息

include(CTest)
enable_testing()

aux_source_directory(./src DIR_CRCS)
add_executable(ChineseChess ${DIR_CRCS})

add_library(pdcurses STATIC IMPORTED)
set_target_properties(pdcurses PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/pdcurses.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
)
target_link_libraries(ChineseChess PRIVATE pdcurses)
# target_compile_options(ChineseChess PRIVATE -fexec-charset=UTF-8)

set(EXECUTABLE_OUTPUT_PATH ./output)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
