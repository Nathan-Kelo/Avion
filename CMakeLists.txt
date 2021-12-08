macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

cmake_minimum_required(VERSION 3.11)

project(Aeroport VERSION 1.0)

include(FetchContent)

FetchContent_Declare(
	json
	GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
	GIT_TAG v3.10.4)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(
	sfml
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG ${sfml_VERSION})

  FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
  FetchContent_Populate(sfml)
  add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(SRCS "main.cpp" "avion.cpp" "aeroport.cpp" "create_aeroport.cpp")
set(SFML_THINGS sfml-graphics sfml-window sfml-system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Aeroport ${SRCS})

target_link_libraries(Aeroport 
	PRIVATE 
		nlohmann_json::nlohmann_json
		${SFML_THINGS}
)

add_custom_command(
	TARGET Aeroport POST_BUILD       
    COMMAND ${CMAKE_COMMAND} -E copy_if_different _deps/sfml-build/lib/sfml-window-d-2.dll ${PROJECT_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different _deps/sfml-build/lib/sfml-graphics-d-2.dll ${PROJECT_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different _deps/sfml-build/lib/sfml-system-d-2.dll ${PROJECT_BINARY_DIR}
	#COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/files ${PROJECT_BINARY_DIR}
)
file(COPY ${PROJECT_SOURCE_DIR}/files DESTINATION ${PROJECT_BINARY_DIR})
message(STATUS "Project source dir (input directory): ${PROJECT_SOURCE_DIR}\n" 
		STATUS "Project binary dir (output diretory): ${PROJECT_BINARY_DIR}\n")




