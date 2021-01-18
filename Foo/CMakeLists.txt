file(GLOB _HDRS "include/foo/*.hpp")
file(GLOB _SRCS "src/*.[hc]pp")

add_library(Foo "")
target_sources(Foo PRIVATE ${_HDRS} ${_SRCS})
target_include_directories(Foo PUBLIC
	$<BUILD_INTERFACE:include>
	$<INSTALL_INTERFACE:include>
	)
target_compile_features(Foo PUBLIC cxx_std_11)
set_target_properties(Foo PROPERTIES
	PUBLIC_HEADER ${_HDRS}
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(Foo PRIVATE ortools::glop)
add_library(${PROJECT_NAMESPACE}::Foo ALIAS Foo)

# Install
install(TARGETS	Foo
	EXPORT ${PROJECT_NAME}Targets
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/foo
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
