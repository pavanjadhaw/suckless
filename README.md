![scrot0](https://raw.githubusercontent.com/pavanjadhaw/suckless/master/scrot.png)

## tools

**dwm**

dwm is a dynamic window manager for X.
It manages windows in tiled, monocle and floating layouts. All of the layouts can be applied dynamically, optimising the environment for the application in use and the task performed.

**dmenu**

dmenu is a dynamic menu for X, originally designed for dwm. It manages large numbers of user-defined menu items efficiently.

**slock**

Simple X display locker. This is the simplest X screen locker we are aware of. It is stable and quite a lot of people in our community are using it every day when they are out with friends or fetching some food from the local pub.

**slstatus**

slstatus is a status monitor for window managers that use WM_NAME or stdin to fill the status bar.

## configuration

dwm and suckless tools are configured at compile-time by editing some of its source files, specifically `config.h`.
For detailed information on these settings see the included, well-commented `config.def.h` as well as the [customisation section](https://dwm.suckless.org/customisation/) on the dwm website.

The official website has a number of patches that can add extra functionality to dwm. These patches primarily make changes to the dwm.c file but also make changes to the config.h file where appropriate. For information on applying patches, see the Patching packages article.

## resources

* [dwm tutorial - official](https://dwm.suckless.org/tutorial/)
* [dwm - archwiki](https://wiki.archlinux.org/index.php/dwm)
* [dwm customisation](https://www.linuxjournal.com/content/going-fast-dwm)
* [dwm visual guide !important](http://ratfactor.com/dwm.html)
