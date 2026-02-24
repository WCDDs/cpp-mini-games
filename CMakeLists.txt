cmake_minimum_required(VERSION 3.10)
project(shahuang)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 库路径配置
set(LIB_BASE_PATH "D:/yixi/huituxianguan/f_1")
set(GLEW_INCLUDE_DIR "${LIB_BASE_PATH}/include")
set(GLEW_LIBRARY "${LIB_BASE_PATH}/lib/glew32.lib")
set(GLFW_INCLUDE_DIR "${LIB_BASE_PATH}/include")
set(GLFW_LIBRARY "${LIB_BASE_PATH}/lib/glfw3.lib")
set(SOIL2_INCLUDE_DIR "${LIB_BASE_PATH}/lib/SOIL2")
set(SOIL2_LIBRARY_DEBUG "${LIB_BASE_PATH}/lib/soil2-debug.lib")
set(SOIL2_LIBRARY_RELEASE "${LIB_BASE_PATH}/lib/soil2-debug.lib")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SOIL2_LIBRARY ${SOIL2_LIBRARY_DEBUG})
else()
    set(SOIL2_LIBRARY ${SOIL2_LIBRARY_RELEASE})
endif()

find_package(OpenGL REQUIRED)

# 添加可执行文件
add_executable(shahuang 
    main.cpp
    Utils.cpp
    fangkuai.h
    Utils.h
)

set_target_properties(shahuang PROPERTIES VS_STARTUP_PROJECT ON)

target_include_directories(shahuang PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${SOIL2_INCLUDE_DIR}
)

target_link_libraries(shahuang 
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY}
    ${SOIL2_LIBRARY}
)

# ========== 复制文件到输出目录 ==========
# 复制着色器文件
add_custom_command(TARGET shahuang POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/fragShader.glsl
        $<TARGET_FILE_DIR:shahuang>/fragShader.glsl
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/vertShader.glsl
        $<TARGET_FILE_DIR:shahuang>/vertShader.glsl
    COMMENT "Copying shader files"
)

# 复制GLEW DLL
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/glew32.dll")
    add_custom_command(TARGET shahuang POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_SOURCE_DIR}/glew32.dll
            $<TARGET_FILE_DIR:shahuang>/glew32.dll
        COMMENT "Copying GLEW DLL"
    )
endif()