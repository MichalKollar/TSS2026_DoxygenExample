cmake_minimum_required(VERSION 3.16.0)

# Tu nastav verziu Qt 6.
set(Qt6_Version 6.12.0)

PROJECT(DoxygenExample VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(MSVC)
	set(Qt6_CMakeDir "C:/Qt/${Qt6_Version}/msvc2022_64/lib/cmake")
	foreach(Qt6_Package IN ITEMS Qt6 Qt6Core Qt6Gui Qt6Widgets Qt6CoreTools Qt6GuiTools Qt6WidgetsTools)
		set(${Qt6_Package}_DIR "${Qt6_CMakeDir}/${Qt6_Package}")
	endforeach()
endif()

find_package(Qt6 ${Qt6_Version} EXACT CONFIG REQUIRED COMPONENTS Widgets)

file(GLOB UI_FILES src/*.ui)
file(GLOB H_FILES src/*.h)
file(GLOB CPP_FILES src/*.cpp)
file(GLOB QRC_FILES src/*.qrc)

set(SOURCE_LIST ${CPP_FILES} ${UI_FILES} ${H_FILES} ${QRC_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})

if(WIN32 AND TARGET Qt6::windeployqt)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND "$<TARGET_FILE:Qt6::windeployqt>" "$<TARGET_FILE:${PROJECT_NAME}>"
		COMMENT "Deploying Qt runtime libraries"
		VERBATIM)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
