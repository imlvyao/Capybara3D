include(${CMAKE_SOURCE_DIR}/macro.cmake)

set(LIB_NAME ToppleTheTowerDraw)
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
	# 查找Boost库
	find_package(Boost REQUIRED COMPONENTS system thread)
	if(Boost_FOUND)
		# 设置头文件路径
		include_directories(${Boost_INCLUDE_DIRS})
		message(STATUS "Boost found: ${Boost_VERSION}")
	else()
		message(FATAL_ERROR "Boost not found.")
endif()
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

# 查找Boost库
if(Boost_FOUND)
    target_link_libraries(${LIB_NAME} ${Boost_LIBRARIES})
endif()

# 输出lib
OUT_LIB(${LIB_NAME})