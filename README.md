### Note: this is only mirror. The project is now [here](https://gitlab.com/VolkMilit/libretro-sh-launcher)

# libretro-sh-launcher
Based on [libretro-dolphin-launcher](https://github.com/RobLoach/libretro-dolphin-launcher) and [libretro-bash-launcher](https://github.com/SwedishGojira/libretro-bash-launcher), see full list of changes below.

Launch (ba)sh-scripts directly from [RetroArch](http://www.libretro.com/) to launch your Linux games.

![Sh Launcher Screenshot](screenshot.png)

## Changes from the original bash-launcher

- Use cmake instead of make. Two reasons - cmake code is more simplier, and I can't sort thing out of original make file.
- Add sh library to easy create your own sh launchers. For example, for wine.
- Add udev module for autolaunch Retroarch. Well, somebody say it's useless feature, but I want just plug in my controller and start playing.
- Playlists and thumbnails auto generation.
- Debian package.
- Rewrite on C++ (WIP)

## Installation

#### Depends

- libcurl
- imlib2
- compiller with c++14 support
- retroarch

Optional:

- Qt4

#### Manual

1. Compile the core

  ``` bash
  git clone --recurse-submodules https://github.com/VolkMilit/libretro-sh-launcher.git
  cd libretro-sh-launcher
  mkdir build && cd build
  cmake ..
  # optional use -DSPLASH=OFF option to disable compile splash programm, see USAGE.md#splash
  make -j$(nproc)
  ```

2. Copy assets and core in right directoryes

  ``` bash
  mkdir $HOME/.config/retroarch/xmb/monochrome/png
  cp ../assets/xmb/monochrome/png/* $HOME/.config/retroarch/xmb/monochrome/png
  cp sh_launcher_libretro.so /any/place/you/like
  ```
  Then just launch core with
  
  ``` bash
  retroarch -L /any/place/you/like/sh_launcher_libretro.so
  ```
  Alternatively you can perform this way, but read the caution bottom first:

  ``` bash
  make install
  ```
  
  But actually I dare you to NOT do *make install* in /usr unless you realy want to. 
  Better using package system or launch it locally, because you can forget what you're install.
  
#### Debian package

1. Clone repo and Install necessary packages
  ``` bash
  mkdir libretro-sh-launcher && cd libretro-sh-launcher
  git clone --recurse-submodules https://github.com/VolkMilit/libretro-sh-launcher.git
  sudo apt install devsripts fakeroot libcurl4-gnutls-dev libimlib2-dev
  ```

2. Build the package
  ``` bash
  cd libretro-sh-launcher
  debuild -i -us -uc -b
  ```

3. Install package
  ``` bash
  cd ..
  sudo dpkg -i libretro_sh_launcher_1.0.0-1+stretch_amd64.deb
  ```

## Usage

See [usage](USAGE.md)

## Contributors

- [SwedishGojira](http://github.com/swedishgojira)
- [Rob Loach](http://github.com/robloach)
- [Alcaro](https://github.com/Alcaro)

## License

- Libretro Sh Launcher (c) Volk_Milit, GPL v3.0.
- Splash (c) Volk_Milit, GPL v3.0.
- HTTPDownloader.cpp (c) Uli Köhler, CC0 1.0 Universal (public domain).
- libretro.h (c) The RetroArch team, MIT.

