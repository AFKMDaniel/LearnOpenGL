include(FetchContent)
FetchContent_Declare(
  GLFW
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)
FetchContent_MakeAvailable(GLFW)

find_package(OpenGL REQUIRED)

add_executable (LearnOpenGL "main.cpp" "shader.cpp" "camera.cpp")
target_compile_features(LearnOpenGL PRIVATE cxx_std_20)
target_link_libraries(LearnOpenGL PRIVATE glad glfw stb_image ${OPENGL_LIBRARIES})

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	if (UNIX)
		add_custom_command(TARGET LearnOpenGL POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E create_symlink
		"${CMAKE_SOURCE_DIR}/resources"
		"${CMAKE_CURRENT_BINARY_DIR}/resources"
		COMMENT "Created symlink to resources")
	else()
		file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/resources"  _dstDir)
		file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/resources" _srcDir)
		add_custom_command(TARGET LearnOpenGL POST_BUILD
		COMMAND if NOT exist "${_dstDir}"(cmd.exe /c mklink /J "${_dstDir}" "${_srcDir}")
		COMMENT "Created symlink to resources")
	endif()
else()
	add_custom_command(TARGET LearnOpenGL POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/resources"
	"${CMAKE_CURRENT_BINARY_DIR}/resources"
	COMMENT "Resources were copied")
endif()