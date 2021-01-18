file(GLOB _SRCS "src/*.[hc]pp")

add_executable(FooApp "")
target_sources(FooApp PRIVATE ${_SRCS})
target_include_directories(FooApp PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_compile_features(FooApp PUBLIC cxx_std_17)
set_target_properties(FooApp PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(FooApp PRIVATE Foo)
add_executable(${PROJECT_NAMESPACE}::FooApp ALIAS FooApp)

# Test
if(BUILD_TESTING)
  add_test(NAME FooApp_UT COMMAND FooApp)
endif()

# Install
install(TARGETS FooApp
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
