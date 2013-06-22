project(mandriva-galaxy)
cmake_minimum_required(VERSION 2.6)

set(mandriva-galaxy_SRCS main.cpp mandrivagalaxy.cpp)
set(mandriva-galaxy_HDRS mandrivagalaxy.h)

find_package(Qt4)
find_package(KDE4 REQUIRED)

include(KDE4Defaults)
include(MacroLibrary)

#Preprocessor definition values are now escaped CMAKE 2.6
cmake_policy(SET CMP0005 NEW)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDE_DIRS} ${KDE4_INCLUDES})
set(QT_USE_QTWEBKIT 1)
QT4_WRAP_CPP(mandriva-galaxy_MOC_SRCS ${mandriva-galaxy_HDRS})
QT4_WRAP_UI(mandriva-galaxy_UI_SRCS mandrivagalaxy.ui)

include(${QT_USE_FILE})

add_subdirectory(po)

add_executable(mandriva-galaxy MACOSX_BUNDLE ${mandriva-galaxy_SRCS} ${mandriva-galaxy_MOC_SRCS} ${mandriva-galaxy_UI_SRCS})

target_link_libraries(mandriva-galaxy ${QT_LIBRARIES} ${KDE4_KDEUI_LIBS})

install(FILES mandriva-galaxy.desktop DESTINATION /etc/xdg/autostart)
install(FILES mandriva-galaxy.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons)
install(TARGETS mandriva-galaxy DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
