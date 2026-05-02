project(shader_support_lib)

# Tell the parent CMake file that this library exists
# PARENT_SCOPE means the list is updated in the CMake file above this one
set(SUB_LIB_LIST "${SUB_LIB_LIST}" ${PROJECT_NAME} PARENT_SCOPE)

file(GLOB SRC_FILES *.cpp)
file(GLOB HDR_FILES *.hpp)
set(ProjectType STATIC)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES} PUBLIC ${HDR_FILES})
target_compile_definitions(${PROJECT_NAME} PUBLIC)

