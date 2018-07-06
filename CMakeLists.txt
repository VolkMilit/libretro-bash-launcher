cmake_minimum_required(VERSION 3.0)
project(libretro-sh-launcher)

option(SPLASH "compile optional splash programm" ON)

if (SPLASH)
	# compile ra_splash
	find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
	include(${QT_USE_FILE})
	set(SOURCES apps/splash/main.cpp)
	qt4_wrap_cpp(GENERATED_SOURCES ${MOCS})
	add_executable(ra_splash ${SOURCES} ${GENERATED_SOURCES} ${MOCS})
	target_link_libraries(ra_splash ${QT_LIBRARIES})
endif()

# compile library itself
file(GLOB_RECURSE sources	
	src/third-party/crc/crc.cpp 
	src/third-party/crc/crc.h 
	src/third-party/ftlip/ftlip.cpp 
	src/third-party/ftlip/ftlip.h 
	src/third-party/https-downloader/HTTPDownloader.cpp 
	src/third-party/https-downloader/HTTPDownloader.h 
	src/utils.cpp 
	src/utils.h 
	src/art.cpp 
	src/art.h 
	src/playlist_generator.cpp 
	src/playlist_generator.h 
	src/libretro-sh-launcher.cpp 
	src/libretro.h 
	src/link.T
	)

unset(CMAKE_LINK_LIBRARY_SUFFIX)
add_library(sh_launcher_libretro SHARED ${sources})

target_compile_options(sh_launcher_libretro PUBLIC -O2)
set_target_properties(sh_launcher_libretro PROPERTIES PREFIX "") #disable lib* prefix
target_link_libraries(sh_launcher_libretro stdc++fs curl Imlib2)

# install
include(GNUInstallDirs)

if (SPLASH)
	install_files(/bin FILES ra_splash)
endif()
install_files(/lib/x86_64-linux-gnu/libretro FILES sh_launcher_libretro.so)
install_files(/lib/x86_64-linux-gnu/libretro FILES lib/sh-launcher.shlib)
#install_files(/share/libretro/assets/xmb/monochrome/png FILES "assets/xmb/monochrome/png/Bash - Sh Launcher - PC.png")
#install_files(/share/libretro/assets/xmb/monochrome/png FILES "assets/xmb/monochrome/png/Bash - Sh Launcher - PC-content.png")
install_files(/share/libretro/assets/xmb/monochrome/png FILES "assets/generic_art.png")
install(FILES etc/999-retroarch.sh etc/999-run-retroarch.rules DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/udev/rules.d)
install_files(/share/libretro/info FILES assets/info/sh_launcher_libretro.info)
