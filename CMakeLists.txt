cmake_minimum_required(VERSION 3.0.0)

project("inVLC")

set(CMAKE_CXX_FLAGS "-std=c++11")

CMAKE_POLICY(SET CMP0020 OLD)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED Core Widgets Xml Sql WebKit WebKitWidgets)
find_package(LIBVLC REQUIRED libvlc)

file(STRINGS ${LIBVLC_INCLUDE_DIR}/vlc/libvlc_version.h VERSIONVLC REGEX "^[ \t]*#[ \t]*define[ \t]+LIBVLC_VERSION_[A-Z]+[ \t]*[(][0-9]+[)].*$")

aux_source_directory(${CMAKE_SOURCE_DIR} SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/core SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/bridge SRC_LIST)
aux_source_directory(${CMAKE_SOURCE_DIR}/library SRC_LIST)

#aux_source_directory(ui UIS)

#QT5_WRAP_UI(UI_HEADERS ${UIS})



INCLUDE_DIRECTORIES(${LIBVLC_INCLUDE_DIR})

qt5_add_resources(RES ${CMAKE_SOURCE_DIR}/res.qrc)

add_executable(${PROJECT_NAME} WIN32 ${SRC_LIST} ${RES})

target_link_libraries(${PROJECT_NAME} ${LIBVLC_LIBRARY} Qt5::Core Qt5::Widgets Qt5::Xml Qt5::Sql Qt5::WebKit Qt5::WebKitWidgets)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/html" DESTINATION bin/html)
file(COPY "${CMAKE_SOURCE_DIR}/html" DESTINATION ${CMAKE_BINARY_DIR})
 set(CPACK_PACKAGE_NAME "inVLC")
 set(CPACK_PACKAGE_VENDOR "r@f924")
 set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "inVLC - VLC but not VLC")
 set(CPACK_PACKAGE_VERSION "0.1.0")
 set(CPACK_PACKAGE_VERSION_MAJOR "0")
 set(CPACK_PACKAGE_VERSION_MINOR "1")
 set(CPACK_PACKAGE_VERSION_PATCH "0")
 set(CPACK_PACKAGE_INSTALL_DIRECTORY "inVLC")
set(CPACK_GENERATOR NSIS)

include(cpack)
