cmake_minimum_required(VERSION 3.25)

project(vulkan-tutorial LANGUAGES C CXX)

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

set(ProjectName "vulkan-tutorial-x86_64")

add_executable(
    ${ProjectName} 
    ${CPP_SOURCES} ${C_SOURCES} ${GLAD_SOURCE}
)
target_compile_definitions(${ProjectName} PRIVATE GLM_FORCE_DEPTH_ZERO_TO_ONE)
target_compile_definitions(${ProjectName} PRIVATE GLM_FORCE_RADIANS)

target_include_directories(${ProjectName} PRIVATE includes)

# -> Assimp
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) 

# CRITICAL FIX: Force Assimp to build and use its internal zlib copy
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

add_subdirectory("dependencies/assimp")

if (TARGET assimp AND NOT MSVC)
    target_compile_options(assimp PRIVATE -w)
endif()
# <- Assimp

# -> STB
target_include_directories(${ProjectName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb)
# <- STB

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
    ${ProjectName} PRIVATE
    Vulkan::Vulkan
    glfw
    glm
    assimp
)

set_target_properties(${ProjectName} PROPERTIES
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
    get_filename_component(SHADER_NAME "${SHADER}" NAME)
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

add_dependencies(${ProjectName} shaders)

# <- Compile shaders