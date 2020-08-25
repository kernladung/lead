*lead* provides hot-corners for your desktop, notably for openbox, awesome, i3 and other window managers.

This fork adds support for specifying an interval to wait before the action is triggered. There may be more improvements in the future.

![Screenshot of lead](https://github.com/almamu/lead/blob/master/screenshots/screenshot1.png)
![Screenshot of lead](https://github.com/almamu/lead/blob/master/screenshots/screenshot2.png)
> Sensors are not displayed unless the debug mode is enabled


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

Sensors have their own sections in the configuration, so if you want to add an action to a corner you can do so:

    [eDP1]
    bottomLeft=SensorName

    [SensorName]
    enterAction=chromium
    exitAction=firefox
    enterDelay=5000
    exitDelay=1000

Delays are configured in miliseconds and dictate the amount of time the mouse has to be in the sensor to trigger the specific action.
In the case of exitDelay, this delay affects how much time the mouse has to be in the sensor for it to trigger the exitAction when the mouse moves out of the sensor.

If you are not sure why a sensor isn't properly firing you can enable the debug mode to visualize what their position is, your screen names and the status they're in.
Each configured sensor will be displayed in a red color when the sensor is waiting for the mouse to enter it.
Once the mouse is in, the sensor will turn to yellow, this indicates that it is waiting for the enter delay timer to end. Once the timer ends the sensor will turn green and the program should be run.
If still your program doesn't run please check lead's output to get a better idea of what's happening.

In debug mode the screen names are shown on the top-left corner of each screen.
To enable the debug mode add the following section in the config file:

    [systemsettings]
    debug=1

The configuration file is monitored and changes are applied automatically.


# Use it

*lead* provides the binary `lead` which creates sensors for each configured corner or side.

Start *lead* as background process:

    $ lead &

# Uninstall it

To uninstall *lead* open a terminal in the root folder of the repository and:

    $ sudo make uninstall

# Drawbacks

I didnt want to poll the mouse, so i created sensors which works with events. The sensors are transparent, but need a running compositor like compton for that. Without a compositor, they are black.

# TODO

Improvements that need to be made:

- Error checking of the conf file; e.g. check that an integer was set for the interval

Possible new features:

- Custom regions
