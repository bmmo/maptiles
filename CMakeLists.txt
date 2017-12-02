cmake_minimum_required ( VERSION 3.1 )

project ( maptiles )

### Parameters
# CMake
set ( CMAKE_MODULE_PATH  ${PROJECT_SOURCE_DIR}/cmake )
set ( CMAKE_CXX_STANDARD 11 )

## CMake
include ( BuildLocation )


### Packages
# Qt
find_package ( Qt5Core        REQUIRED )
find_package ( Qt5Gui         REQUIRED )
find_package ( Qt5Widgets     REQUIRED )
find_package ( Qt5OpenGL      REQUIRED )
find_package ( Qt5Xml         REQUIRED )
# OpenSceneGraph
find_package ( OpenSceneGraph REQUIRED 
	             osgViewer osgGA osgDB 
							 osg osgText )
# System
find_package ( OpenGL         REQUIRED )
find_package ( Threads        REQUIRED )


### Qt Stuff
# See for https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html
set ( CMAKE_AUTORCC             ON   )
set ( CMAKE_INCLUDE_CURRENT_DIR ON   )
set ( QT_USE_QTOPENGL           TRUE )
# Neccessary for Linux and so on, for -fPIC
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})
add_definitions(${Qt5Xml_DEFINITIONS})

### Lib
file ( GLOB maptiles_src
	src/*.cpp
	src/coords/*.cpp
	)

add_library (
	maptiles
	STATIC
	${maptiles_src}
	)

target_include_directories(
	maptiles
	PUBLIC 
	include/
	${OSG_INCLUDE_DIR}
	)


### Tests
add_subdirectory ( test )
