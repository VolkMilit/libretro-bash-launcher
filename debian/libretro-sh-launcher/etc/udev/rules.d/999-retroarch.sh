#!/bin/sh

export HOME=/home/user
export DISPLAY=:0 

/usr/bin/retroarch -L /usr/lib/x86_64-linux-gnu/libretro/sh_launcher_libretro.so >> /dev/null 2>&1 &
