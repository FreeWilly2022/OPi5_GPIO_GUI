# OPi5_GPIO_GUI
Crude GUI for testing GPIO pins on Orange Pi 5

Toggle on and off GPIO pins on the Orange Pi 5 by clilcking on buttons
in a window on the screen.
This program uses the wiringOP and GTK libraries, download per the
the instructions on the websites:

https://github.com/orangepi-xunlong/wiringOP
https://www.gtk.org/docs/installations/linux

To compile, from a terminal in the same directory as this file enter -
gcc $( pkg-config --cflags gtk4 ) -o GUItest2 GUItest2.c $( pkg-config --libs gtk4 ) -lwiringPi

to run, from a terminal enter -
sudo ./GUItest2

to confirm GPIO state, from a separate terminal enter -
gpio readall
