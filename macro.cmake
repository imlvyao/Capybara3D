macro(INSTALL_NUGET target id version)
	if (CMAKE_GENERATOR MATCHES "Visual Studio.*")
		unset(nuget_cmd)
		set(nuget_cmd "${CMAKE_BINARY_DIR}/NuGet.exe install ${id} -Version ${version} -OutputDirectory ${CMAKE_BINARY_DIR}/packages")
		message(STATUS "excute nuget install: ${nuget_cmd}")
		execute_process(COMMAND ${CMAKE_BINARY_DIR}/NuGet.exe install ${id} -Version ${version} -OutputDirectory ${CMAKE_BINARY_DIR}/packages ENCODING AUTO
  			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  			RESULT_VARIABLE git_result
  			OUTPUT_VARIABLE git_ver)
		#execute_process(COMMAND ./NuGet.exe install ${id} -Version ${version} ENCODING AUTO)
		target_link_libraries(${target} ${CMAKE_BINARY_DIR}/packages/${id}.${version}/build/native/${id}.targets)
		target_link_libraries(${target} ${CMAKE_BINARY_DIR}/packages/${id}.${version}/build/${id}.targets)
	else()
		message(FATAL_ERROR "INSTALL_NUGET noly use in Visual Studio")
	endif()
endmacro()

macro(INSTALL_CONAN)
	execute_process(COMMAND conan install . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
	include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
	conan_basic_setup()
endmacro()

macro(OUT_LIB target)
    if(WIN32)
        set_property(TARGET ${target} PROPERTY IMPORTED_IMPLIB_RELEASE "${SDL_ROOT_PATH}/lib/${target}.lib")
        set_property(TARGET ${target} PROPERTY IMPORTED_LOCATION_RELEASE "${SDL_ROOT_PATH}/bin/${target}.dll")
        set_property(TARGET ${target} PROPERTY IMPORTED_IMPLIB_DEBUG "${SDL_ROOT_PATH}/lib/${target}d.lib")
        set_property(TARGET ${target} PROPERTY IMPORTED_LOCATION_DEBUG "${SDL_ROOT_PATH}/bin/${target}d.dll")
    endif(WIN32)
endmacro()

macro(ADD_LIB headerPath target)
    #aux_source_directory(. SRCS)
    file(GLOB ALL_SOURCES "*.cpp" "*.c" "${headerPath}/*.cpp" "${headerPath}/*.c")
    file(GLOB ALL_INCLUDES "*.hpp" "*.h" "${headerPath}/*.hpp" "${headerPath}/*.h")
    message(NOTICE "HEADER_PATH: ${headerPath}")
    set(SRCS 
        ${ALL_SOURCES}
        ${ALL_INCLUDES}
    )
    add_library(${target} SHARED ${SRCS})
endmacro()

macro(ADD_STATIC_LIB headerPath target)
    #aux_source_directory(. SRCS)
    file(GLOB ALL_SOURCES "*.cpp" "*.c" "${headerPath}/*.cpp" "${headerPath}/*.c")
    file(GLOB ALL_INCLUDES "*.hpp" "*.h" "${headerPath}/*.hpp" "${headerPath}/*.h")
    message(NOTICE "HEADER_PATH: ${headerPath}")
    set(SRCS 
        ${ALL_SOURCES}
        ${ALL_INCLUDES}
    )
    add_library(${target} STATIC ${SRCS})
endmacro()

macro(ADD_EXE headerPath target)
    #aux_source_directory(. SRCS)
    file(GLOB ALL_SOURCES "*.cpp" "*.c" "${headerPath}/*.cpp" "${headerPath}/*.c")
    file(GLOB ALL_INCLUDES "*.hpp" "*.h" "${headerPath}/*.hpp" "${headerPath}/*.h")
    message(NOTICE "HEADER_PATH: ${headerPath}")
    set(SRCS 
        ${ALL_SOURCES}
        ${ALL_INCLUDES}
    )
    add_executable(${target} ${SRCS})
endmacro()