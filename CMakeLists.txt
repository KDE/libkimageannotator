cmake_minimum_required(VERSION 3.5)
project(kImageAnnotator LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(BUILD_TESTS "Build Unit Tests" OFF)
option(BUILD_EXAMPLE "Build Example Application" ON)

set(QT_MIN_VERSION "5.6.1")
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Test)

if (UNIX)
	find_package(X11 REQUIRED)
endif ()

include(GNUInstallDirs)
include(FeatureSummary)

set(KCOLORPICKER_MIN_VERSION "0.0.1")
find_package(kColorPicker ${KCOLORPICKER_MIN_VERSION} REQUIRED)

set(BASEPATH "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${BASEPATH}")

add_subdirectory(src)

if (BUILD_EXAMPLE)
	add_subdirectory(example)
endif (BUILD_EXAMPLE)

if (BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif (BUILD_TESTS)

include(CMakePackageConfigHelpers)

add_library(kImageAnnotator
			${KIMAGEANNOTATOR_SRCS}
			${CMAKE_CURRENT_SOURCE_DIR}/include/kImageAnnotator/KImageAnnotator.h
			${CMAKE_CURRENT_SOURCE_DIR}/icons/kImageAnnotator_icons.qrc
			)

add_library(kImageAnnotator::kImageAnnotator ALIAS kImageAnnotator)

target_include_directories(kImageAnnotator
						   PUBLIC
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
						   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
						   )

if (UNIX)
	target_link_libraries(kImageAnnotator PUBLIC Qt5::Widgets kColorPicker X11)
else ()
	target_link_libraries(kImageAnnotator PUBLIC Qt5::Widgets kColorPicker)
endif ()

target_compile_definitions(kImageAnnotator PRIVATE KIMAGEANNOTATOR_LIB)

set_target_properties(kImageAnnotator
					  PROPERTIES
					  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
					  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
					  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
					  SOVERSION ${PROJECT_VERSION}
					  )

install(TARGETS kImageAnnotator
		EXPORT kImageAnnotator-targets
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/kImageAnnotator
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		)

configure_package_config_file(
		${CMAKE_CURRENT_SOURCE_DIR}/cmake/kImageAnnotatorConfig.cmake.in
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotatorConfig.cmake
		INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
)

write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotatorConfig-version.cmake
		VERSION ${PROJECT_VERSION}
		COMPATIBILITY AnyNewerVersion
)

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotatorConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotatorConfig-version.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
		)

export(
		EXPORT kImageAnnotator-targets
		FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotator-targets.cmake
		NAMESPACE kImageAnnotator::
)

install(
		EXPORT kImageAnnotator-targets
		FILE kImageAnnotator-targets.cmake
		NAMESPACE kImageAnnotator::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
