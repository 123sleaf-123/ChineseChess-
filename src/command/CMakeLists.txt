# 将 command 目录下的源文件添加到主目标
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} DIR_SRCS_COMMAND)
target_sources(${PROJECT_NAME} PRIVATE ${DIR_SRCS_COMMAND})