# Consume
**consume** takes another program to execute and hides the current active window, until that program finishes execution.  
It is same in functionality to [devour](https://github.com/salman-abedin/devour/), which relies on [xdo](https://github.com/baskerville/xdo).  
This is a standalone program, with the same functionality.

# Use
```
consume PROGRAM ...
```

## Requirements
Development libraries:
- libxcb
- libxcb-util
- libxcb-ewmh

## Installation
By default it will be placed into /usr/local.
If you prefer to put it somewhere else, look at the install.sh script.
```
compile.sh
sudo install.sh
```

## Uninstallation
If you used the unmodified install.sh script for installation, you can run uninstall.sh.
Otherwise look into the uninstall.sh script.
```
sudo uninstall.sh
```

## Examples
Launching an image viewer on image.png.
```
consume xdg-open image.png
```
Or using a specific image viewer.
```
consume sxiv image.png
```

To add support for aliases you can put something like this in your .bashrc file.
```
eat() {
    consume $SHELL -i -c "$*"
}
```
Then you would call.
```
eat CMD/ALIAS ...
```
