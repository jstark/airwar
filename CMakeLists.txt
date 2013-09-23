project(airwar)
cmake_minimum_required(VERSION 2.8)

# enable C++11 features for gcc and clang
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

    # use libc++ in Mac OS X
    if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()

# use FindSFML.cmake to load SFML support
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMake")
find_package(SFML 2 COMPONENTS audio graphics window system network REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# game executable
set(GAME ${PROJECT_NAME})
set(HEADERS 
	entity.hxx
	aircraft.hxx
	scene.hxx
	resource_holder.hxx
	texture_holder.hxx
	world.hxx
	game.hxx)
set(SOURCES
	entity.cxx
	aircraft.cxx
	scene.cxx
	world.cxx
	game.cxx
	airwar.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	add_executable(${GAME} WIN32 ${HEADERS} ${SOURCES})
elseif(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    add_executable(${GAME} MACOSX_BUNDLE ${HEADERS} ${SOURCES})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	set(MAIN_LINK_LIBRARY
		optimized ${SFML_ROOT}/lib/sfml-main.lib
		debug ${SFML_ROOT}/lib/sfml-main-d.lib)
	target_link_libraries(${GAME} ${SFML_LIBRARIES} ${MAIN_LINK_LIBRARY})
elseif(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    target_link_libraries(${GAME} ${SFML_LIBRARIES})
endif()

# installation
if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
endif()

# c++ runtime
include(InstallRequiredSystemLibraries)

if (${CMAKE_SYSTEM_NAME} MATCHES Windows)
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Media DESTINATION bin)
	install(FILES
		${SFML_ROOT}/bin/openal32.dll
		${SFML_ROOT}/bin/libsndfile-1.dll
		${SFML_ROOT}/bin/sfml-network-2.dll
		${SFML_ROOT}/bin/sfml-audio-2.dll
		${SFML_ROOT}/bin/sfml-graphics-2.dll
		${SFML_ROOT}/bin/sfml-window-2.dll
		${SFML_ROOT}/bin/sfml-system-2.dll
		DESTINATION bin
		CONFIGURATIONS Release;RelWithDebInfo;MinSizeRel)

	install(FILES
		${SFML_ROOT}/bin/openal32.dll
		${SFML_ROOT}/bin/libsndfile-1.dll
		${SFML_ROOT}/bin/sfml-network-d-2.dll
		${SFML_ROOT}/bin/sfml-audio-d-2.dll
		${SFML_ROOT}/bin/sfml-graphics-d-2.dll
		${SFML_ROOT}/bin/sfml-window-d-2.dll
		${SFML_ROOT}/bin/sfml-system-d-2.dll
		DESTINATION bin
		CONFIGURATIONS Debug)
endif()

