cmake_minimum_required(VERSION 3.14.7)

if(POLICY CMP0022)
	cmake_policy(SET CMP0022 NEW)
endif()

# option() honors normal variables.
if(POLICY CMP0077)
	cmake_policy(SET CMP0077 NEW)
endif()

# Set default build type to Release if empty.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING
	"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.")

project(CMakeGlop VERSION 1.0 LANGUAGES CXX)
set(PROJECT_NAMESPACE cg)

include(CTest)
include(GNUInstallDirs)

if(UNIX)
  option(BUILD_SHARED_LIBS "Build shared libraries(.so)." ON)
else()
	# only support for static build on Windows.
 set(BUILD_SHARED_LIBS OFF)
endif()

if(BUILD_SHARED_LIBS)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

include(FetchContent)
FetchContent_Declare(
  ortools
  GIT_REPOSITORY https://github.com/google/or-tools.git
  GIT_TAG        main
)

set(BUILD_CXX OFF)
set(BUILD_DEPS ON)
set(BUILD_GLOP ON)
FetchContent_MakeAvailable(ortools)

add_subdirectory(Foo)
add_subdirectory(FooApp)

# Install
install(EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ${PROJECT_NAMESPACE}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
	COMPONENT Devel)
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/${PROJECT_NAME}Config.cmake.in
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
	NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	COMPATIBILITY SameMajorVersion)
install(
	FILES
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
	COMPONENT Devel)
