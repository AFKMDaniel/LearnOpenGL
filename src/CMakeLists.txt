include(FetchContent)
FetchContent_Declare(
  GLFW
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)
FetchContent_MakeAvailable(GLFW)

find_package(OpenGL REQUIRED)

add_executable (LearnOpenGL "main.cpp" "glad.c")
target_compile_features(LearnOpenGL PRIVATE cxx_std_20)
target_link_libraries(LearnOpenGL PRIVATE "glfw" ${OPENGL_LIBRARIES})
target_include_directories(LearnOpenGL PRIVATE "${CMAKE_SOURCE_DIR}/include")