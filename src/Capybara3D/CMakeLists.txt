include(${CMAKE_SOURCE_DIR}/macro.cmake)

set(LIB_NAME Capybara3D)
set(HEADER_PATH ../../inc/${LIB_NAME})

include_directories(${HEADER_PATH})
include_directories(../../inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
if(WIN32)
	#add_compile_definitions(MG_ENABLE_SSL)
	#add_compile_definitions(NOMINMAX)
	#add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	#add_compile_definitions(_SCL_SECURE_NO_WARNINGS)
	#add_compile_definitions(_CONSOLE)
	#add_compile_definitions(FD_SETSIZE=1024)
	link_directories(../../lib/glfw_vc2019)
	link_libraries(opengl32.lib glfw3.lib glfw3dll.lib glfw3_mt.lib)
	
elseif(UNIX)
	#add_compile_definitions(MG_ENABLE_SSL)
	#add_compile_definitions(NOMINMAX)
	#add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	#add_compile_definitions(_SCL_SECURE_NO_WARNINGS)
	#add_compile_definitions(_CONSOLE)
	#add_compile_definitions(FD_SETSIZE=1024)

	#link_libraries(boost_filesystem)
	#link_libraries(boost_system)
	#link_libraries(stdc++)
	#link_libraries(ssl)

endif()

ADD_EXE(${HEADER_PATH} ${LIB_NAME})

# 依赖
LINKDLL_AND_COPY(${LIB_NAME} Utility)

# 输出lib
OUT_LIB(${LIB_NAME})