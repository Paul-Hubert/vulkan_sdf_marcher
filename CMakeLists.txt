cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(vulkan_sdf_marcher)

add_subdirectory(3rdparty/FastNoiseSIMD)

include_directories("./src")
include_directories("./3rdparty")
file(GLOB_RECURSE sources ./src/main.cpp ./src/*.cpp ./src/*.h)

add_executable(vulkan_sdf_marcher ${sources})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(vulkan_sdf_marcher PRIVATE -Wall -Wextra)
endif()

find_package(Vulkan REQUIRED)
target_link_libraries(vulkan_sdf_marcher PRIVATE Vulkan::Vulkan)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(vulkan_sdf_marcher PRIVATE SDL2::SDL2 SDL2::SDL2main)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(vulkan_sdf_marcher PRIVATE FastNoiseSIMD)


# Copy resources to build
file(
    COPY resources/
    DESTINATION ${PROJECT_BINARY_DIR}/resources/
)

add_custom_command(TARGET vulkan_sdf_marcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${PROJECT_BINARY_DIR}/resources"
)

### COMPILE SHADERS
set(GLSL_VALIDATOR "glslangValidator")

file(GLOB_RECURSE GLSL_SOURCE_FILES "src/renderer/shaders/*.glsl")

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_BINARY_DIR}/resources/shaders/${FILE_NAME}.spv")
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/resources/shaders/"
    COMMAND ${GLSL_VALIDATOR} -V --target-env vulkan1.1 ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    shaders
    DEPENDS ${SPIRV_BINARY_FILES}
    )

add_dependencies(vulkan_sdf_marcher shaders)
