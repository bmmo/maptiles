cmake_minimum_required ( VERSION 3.0 )

### Executable
add_executable(
	test_gui
  MACOSX_BUNDLE WIN32
	gui.cpp
  )

target_link_libraries(
	test_gui
	maptiles
  ${CMAKE_THREAD_LIBS_INIT}
  ${CMAKE_DL_LIBS}
  ${OPENSCENEGRAPH_LIBRARIES}
  ${OPENGL_LIBRARIES}
	)

qt5_use_modules (
	test_gui
  Core
  Gui
  Widgets
  OpenGL
  Xml)
