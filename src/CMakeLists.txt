# 主可执行文件
add_executable(${PROJECT_NAME})

# 添加主源文件
aux_source_directory(. DIR_SRCS)
target_sources(${PROJECT_NAME} PRIVATE ${DIR_SRCS})

# 添加 command 子目录
add_subdirectory(command)

# 包含目录设置
target_include_directories(${PROJECT_NAME} PRIVATE 
    .               # 可以包含 src/ 下的头文件
    command         # 可以包含 command/ 下的头文件
)