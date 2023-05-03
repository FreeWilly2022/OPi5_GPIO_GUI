# OPi5_GPIO_GUI
Crude GUI for testing GPIO pins on Orange Pi 5

Toggle on and off GPIO pins on the Orange Pi 5 by clilcking on buttons
in a window on the screen.
This program uses the wiringOP and GTK libraries, download and install per the
the instructions on the websites:

https://github.com/orangepi-xunlong/wiringOP

https://www.gtk.org/docs/installations/linux

To change GPIO pins you only need to edit the "define" section of the program.  Change the number after each of the GPIO_PIN_A, B, etc to select which pins you want to toggle, and edit the buttons to read whatever makes sense to you.

```
To compile, from a terminal in the same directory as this file enter -
gcc $( pkg-config --cflags gtk4 ) -o GUItest2 GUItest2.c $( pkg-config --libs gtk4 ) -lwiringPi

to run, from a terminal enter -
sudo ./GUItest2

to confirm GPIO state, from a separate terminal enter -
gpio readall
```
