*lead* provides hot-corners for your desktop, notably for openbox, awesome, i3 and other window managers.

![Screenshot of lead](https://github.com/mlde/lead/blob/master/screenshot.png)
> Despite the screenshot, the sensors are only 1px in size and invisible.


### Features
- hot corners: sensors in the corners of the screen
- hot sides: sensors on center/middle edge of the screen
- freely configurable action for each sensor
- each screen is individually configurable


# Get it

- clone the repository with `$ git clone https://github.com/mlde/lead`

**or**

- download as zip and extract it


# Build it

*lead* uses [clang](http://clang.llvm.org/) as compiler, [g++](https://gcc.gnu.org/) as linker and [make](https://www.gnu.org/software/make/) as build-tool. 

To build *lead* open a terminal in the root folder of the repository and:

    $ make

### Dependencies
- Qt5Widgets 
- Qt5Gui 
- Qt5Core

### Build

A build `lead` is provided in `data/usr/bin/`. It was build on my arch64 system.


# Install it

To install *lead* open a terminal in the root folder of the repository and:

    $ sudo make install


# Configure it

On the first run lead will look into these dirs for a conf-file. The first one found will be used.

    ~/.config/lead/lead.conf
    /etc/xdg/lead/lead.conf

If none of these exists, it will create `~/.config/lead/lead.conf` with default values for each screen, ie:

    [eDP1]
    bottom=
    bottomLeft=
    bottomRight=
    left=
    right=
    top=
    topLeft=
    topRight=

To enable a action for a sensor, simply add a command to the corner or side:

    [eDP1]
    bottom=
    bottomLeft=chromium
    bottomRight=thunar
    left=
    right=
    top=
    topLeft=californium toggle
    topRight=skippy-xd

Used config-files and theme-files are monitored and changes are applied automatically.


# Use it

*lead* provides the binary `lead` which creates sensors for each configured corner or side.

Start *lead* as background process:

    $ lead &

# Uninstall it

To uninstall *lead* open a terminal in the root folder of the repository and:

    $ sudo make uninstall

# Drawbacks

I didnt want to poll the mouse, so i created sensors which works with events. The sensors are transparent, but need a running compositor like compton for that. Without a compositor, they are black.
