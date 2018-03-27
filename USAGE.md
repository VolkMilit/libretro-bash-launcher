# Libretro Sh Launcher usage

## Core usage

1. Scan Bash-scripts in RetroArch (never actually works for me, but, whatever)

2. Launch the script directly from the RetroArch menu

3. Alternatively, you can run games through the command line
  ``` bash
  retroarch -L sh_launcher_libretro.so script.sh
  ```

## sh-launcher.shlib usage

This lib is simple sh library that you can use in your own scripts. You can put it whatever place you want, but in Debian package, by default, it will be in /usr/lib/x86_64-linux-gnu/libretro/ .

List of function that you can use:

- pademu [profile_name] - launch antimicro with right profile. Profile must be named as script, without .sh tho. Profiles must be in $HOME/.config/antimicro . After game is exit, antimicro will terminated.
- wine_run_local [game_exe_full_path] - launch wine using [my scripts](https://github.com/VolkMilit/wine-helper-script).
- wine_run_steam [game_id] - launch wine steam using [my scripts](https://github.com/VolkMilit/wine-helper-script). Still WIP.
- run_local [game_exe_full_path] - launch local game, gog, for example.
- run_steam [game_id] - run native steam game.
- run_dosbox [game_exe_full_path] - run dosbox.

Also, you can utilize NAME and ART varibles to have some fancy playlist in menu. See [#playlist](#playlist).

So for example simple simple script will look like this:

  ``` bash
  #!/bin/sh
  
  NAME="This thing"
  ART="/path/to/art"
  
  . /usr/lib/x86_64-linux-gnu/libretro/sh-launcher.shlib
  
  pademu $0
  wine_run $HOME/games/somegame/thing.exe
  ```
  
If you're using bash:

  ``` bash
  #!/usr/bin/env bash
  
  NAME="This thing"
  ART="/path/to/art"
  
  source /usr/lib/x86_64-linux-gnu/libretro/sh-launcher.shlib
  
  pademu $0
  wine_run $HOME/games/somegame/thing.exe
  ```
  
## Install udev module

Preambule:

So, uhh... It's real pain, but I think I fugure it out. Still launch script twice for no reason, and the second copy is not seen gamepad. Wtf?

Note: Debian users (using package) must not copy any files, just edit it.

1. Find your gamepad vendor code
  ``` bash
  udevadm monitor
  ```
  
  Connect your gamepad and search for string like this:
  
  UDEV  [11315.399848] add      /devices/pci0000:00/0000:00:1d.3/usb5/5-2/5-2:1.0/0003:1A34:0802.0002/input/input14/js0 (input)
  
  1A34 is your vendor id
  
  0802 is product id
  
  Change that numbers in etc/999-run-retroarch.rules.
  
  
  Alternatively you can search for code in dmesg.
  
  ``` bash
  sudo dmesg
  ```
  
  String like:
  
  [11315.334038] input: USB GAMEPAD 8116 as /devices/pci0000:00/0000:00:1d.3/usb5/5-2/5-2:1.0/0003:1A34:0802.0002/input/input14
  
  Same steps as above.
 
2. User setup

  Change third string in etc/999-retroarch.sh to your user home dir.
  
3. Copy both files from etc
  ``` bash
  sudo cp etc/* /etc/udev/rules.d/
  ```
  
  You're done. Next time you connect the gamepad, retroarch will be launched.
  
## Playlist

This module can automatically generate fancy playlist thing for retroarch! According to [retroarch docs](https://docs.libretro.com/guides/roms-playlists-thumbnails/#retroarch-playlist-scanner) for have an auto-generated playlist, core need to be in database. Since our core is not in database, even if it be, there is too many games, we create our own "local database". All we need to add in *.sh file two entry:

``` bash
NAME="Name of the game to display"
ART="Full path to art" or "game_steam_id"
```

Both varibles is optional. If you're too lazy, playlist-geneator will be used generic art (can be disabled in config) and, as a name - name of the file.

Config must be in your $HOME/.config/retroarch and named sh-laucher.cfg. If there is no such file, core create new one with default settings. It's a plaing text file inpired by ini. There is no need to section, well... it's a simple file, anyway, and it's support commentary in bash style.

Fields you can use:

``` bash
#by now commentary support only that way to comment, it may be changet in future

#path to your library with sh's
path=/home/user/games/emu/sh
#you can disable playlist generate, default true
generate_playlist=true 
#display or not generic art, if there is no art given, default true
display_generic_art=true

#there will be cached field DO NOT IT MANNUALY unless you're realy know what 
#you're doing. This filed is autogenerated.
```