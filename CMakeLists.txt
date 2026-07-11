cmake_minimum_required(VERSION 3.25)

project(vulkan-triangle LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options()
else()
    #add_compile_options(-Werror -Wall)
endif()

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS "src/*.cpp"       )
file(GLOB_RECURSE C_SOURCES   CONFIGURE_DEPENDS "src/*.c"         )
file(GLOB_RECURSE GLAD_SOURCE CONFIGURE_DEPENDS "includes/*glad.c")

add_executable(executable ${CPP_SOURCES} ${C_SOURCES} ${GLAD_SOURCE}
    src/vulkan/vertex.cpp
    includes/vulkan/vertex.inl)

target_include_directories(executable PRIVATE includes)

# -> GLM
add_subdirectory("dependencies/glm")
if (TARGET glm AND NOT MSVC)
    target_compile_options(glm PRIVATE -w)
endif()

# <- GLM

# -> GLFW
add_subdirectory("dependencies/glfw")

if (TARGET glfw AND NOT MSVC)
    target_compile_options(glfw PRIVATE -w)
endif()
# -> GLFW

target_link_libraries(
    executable PRIVATE
    Vulkan::Vulkan
    glfw
    glm
)

set_target_properties(executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Compile shaders ->
set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/shaders")
set(SHADER_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/compiled-shaders")

file(MAKE_DIRECTORY "${SHADER_OUTPUT_DIR}")

find_program(GLSLC_EXECUTABLE
    NAMES glslc
    HINTS
        "$ENV{VULKAN_SDK}/Bin"
        "$ENV{VULKAN_SDK}/Bin32"
    REQUIRED
)

file(GLOB_RECURSE SHADER_FILES
    CONFIGURE_DEPENDS
    "${SHADER_SOURCE_DIR}/*.vert"
    "${SHADER_SOURCE_DIR}/*.frag"
)

set(COMPILED_SHADERS)

foreach(SHADER ${SHADER_FILES})
    get_filename_component(SHADER_NAME "${SHADER}" NAME_WE)
    get_filename_component(SHADER_EXT "${SHADER}" EXT)

    set(OUTPUT "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv")

    add_custom_command(
        OUTPUT "${OUTPUT}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_OUTPUT_DIR}"
        COMMAND ${GLSLC_EXECUTABLE}
                "${SHADER}"
                -o "${OUTPUT}"
        DEPENDS "${SHADER}"
        COMMENT "Compiling shader ${SHADER_NAME}${SHADER_EXT}"
        VERBATIM
    )

    list(APPEND COMPILED_SHADERS "${OUTPUT}")
endforeach()

add_custom_target(
    shaders
    ALL
    DEPENDS ${COMPILED_SHADERS}
)

add_dependencies(executable shaders)

# <- Compile shaders