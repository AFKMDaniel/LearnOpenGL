cmake_minimum_required (VERSION 3.28)

project ("LearnOpenGL" LANGUAGES CXX C)

option(PRODUCTION_BUILD "Make this a production build" OFF)

include(FetchContent)
FetchContent_Declare(
  GLFW
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)
FetchContent_MakeAvailable(GLFW)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable (LearnOpenGL ${MY_SOURCES})
target_compile_features(LearnOpenGL PUBLIC cxx_std_20)
target_link_libraries(LearnOpenGL PUBLIC glad glfw stb_image ${OPENGL_LIBRARIES})

include_directories("${CMAKE_SOURCE_DIR}/include")

if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions(LearnOpenGL PUBLIC RESOURCES_PATH="./resources/") 

	target_compile_definitions(LearnOpenGL PUBLIC PRODUCTION_BUILD=1) 

else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions(LearnOpenGL PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions(LearnOpenGL PUBLIC PRODUCTION_BUILD=0) 

endif()

add_subdirectory(lib)
