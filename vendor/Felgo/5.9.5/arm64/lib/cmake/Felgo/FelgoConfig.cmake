
get_filename_component(_felgo_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

if(NOT TARGET Felgo)
    add_library(Felgo STATIC IMPORTED)

    # Dependencies

    find_package(Qt5 COMPONENTS Core Qml Quick Widgets Network Multimedia Sql OpenGL REQUIRED)

    if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "QNX" AND NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "QNX700")
        find_package(OpenGL REQUIRED)
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        find_package(zlib REQUIRED)
    endif()

    set_property(
        TARGET Felgo
        PROPERTY INTERFACE_LINK_LIBRARIES
        Qt5::Core Qt5::Qml Qt5::Quick Qt5::Widgets Qt5::Network Qt5::Multimedia Qt5::Sql Qt5::OpenGL
        )

    if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        set_property(TARGET Felgo APPEND PROPERTY INTERFACE_LINK_LIBRARIES z)
    endif()

    if(NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "QNX" AND NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "QNX700")
        set_property(TARGET Felgo APPEND PROPERTY INTERFACE_LINK_LIBRARIES OpenGL::GL)
    endif()

    # Include paths

    set_property(TARGET Felgo PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_felgo_install_prefix}/include/Felgo)

    # Libraries

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set_property(TARGET Felgo PROPERTY IMPORTED_LOCATION ${_felgo_install_prefix}/lib/Felgod.lib)
        else()
            set_property(TARGET Felgo PROPERTY IMPORTED_LOCATION ${_felgo_install_prefix}/lib/Felgo.lib)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        # NO debug libs
        set_property(TARGET Felgo PROPERTY IMPORTED_LOCATION ${_felgo_install_prefix}/lib/libFelgo.a)
    elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "QNX" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "QNX700")
        # NO debug libs
        set_property(TARGET Felgo PROPERTY IMPORTED_LOCATION ${_felgo_install_prefix}/lib/libFelgo.a)
    endif()
endif()

set(Felgo_LIBRARIES Felgo)
set(Felgo_INCLUDE_DIRS ${_felgo_install_prefix}/include/Felgo)
