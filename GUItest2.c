/* crude program to toggle on and off GPIO pins on the Orange Pi 5
this program uses the wiringOP and GTK libraries, download per the
the instructions on the websites:

https://github.com/orangepi-xunlong/wiringOP
https://www.gtk.org/docs/installations/linux

to compile, from a terminal in the sme directory as this file (delete line breaks in terminal) -
gcc $( pkg-config --cflags gtk4 ) -o GUItest2 GUItest2.c $( pkg-config --libs
gtk4 ) -lwiringPi

to run, from a terminal -
sudo ./GUItest2

to confirm GPIO state, from a separate terminal enter -
gpio readall

to format enter from a terminal -
clang-format -i GUItest3.c

 */

#include <gtk/gtk.h>

#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define G_APPLICATION_DEFAULT_FLAGS 0

// Define four pins to be able to test, these are the numbers in
// the wPi column from gpio readall, button labels can be whatever
// make sense to you
#define GPIO_PIN_A 16
#define BUTTON_A "GPIO 16"
#define GPIO_PIN_B 2
#define BUTTON_B "GPIO 2"
#define GPIO_PIN_C 3
#define BUTTON_C "GPIO 3"
#define GPIO_PIN_D 4
#define BUTTON_D "GPIO 4"


static void print_GPIOA(GtkWidget *widget, gpointer data)

{
  int GPIO_on;
  GPIO_on = digitalRead(GPIO_PIN_A);
  if (GPIO_on == 0) {
    g_print("GPIO %d On\n",GPIO_PIN_A);
    digitalWrite(GPIO_PIN_A, 1);
  } else {
    g_print("GPIO %d Off\n",GPIO_PIN_A);
    digitalWrite(GPIO_PIN_A, 0);
  }
}

static void print_GPIOB(GtkWidget *widget, gpointer data)

{
  int GPIO_on;
  GPIO_on = digitalRead(GPIO_PIN_B);
  if (GPIO_on == 0) {
    g_print("GPIO %d On\n",GPIO_PIN_B);
    digitalWrite(GPIO_PIN_B, 1);
  } else {
    g_print("GPIO %d Off\n",GPIO_PIN_B);
    digitalWrite(GPIO_PIN_B, 0);
  }
}

static void print_GPIOC(GtkWidget *widget, gpointer data)

{
  int GPIO_on;
  GPIO_on = digitalRead(GPIO_PIN_C);
  if (GPIO_on == 0) {
    g_print("GPIO %d On\n",GPIO_PIN_C);
    digitalWrite(GPIO_PIN_C, 1);
  } else {
    g_print("GPIO %d Off\n",GPIO_PIN_C);
    digitalWrite(GPIO_PIN_C, 0);
  }
}

static void print_GPIOD(GtkWidget *widget, gpointer data)

{
  int GPIO_on;
  GPIO_on = digitalRead(GPIO_PIN_D);
  if (GPIO_on == 0) {
    g_print("GPIO %d On\n",GPIO_PIN_D);
    digitalWrite(GPIO_PIN_D, 1);
  } else {
    g_print("GPIO %d Off\n",GPIO_PIN_D);
    digitalWrite(GPIO_PIN_D, 0);
  }
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "GPIO Tester");

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new();

  /* Pack the container in the window */
  gtk_window_set_child(GTK_WINDOW(window), grid);

  button = gtk_button_new_with_label(BUTTON_A);
  g_signal_connect(button, "clicked", G_CALLBACK(print_GPIOA), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label(BUTTON_B);
  g_signal_connect(button, "clicked", G_CALLBACK(print_GPIOB), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label(BUTTON_C);
  g_signal_connect(button, "clicked", G_CALLBACK(print_GPIOC), NULL);

  /* Place the first button in the grid cell (0, 1), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

  button = gtk_button_new_with_label(BUTTON_D);
  g_signal_connect(button, "clicked", G_CALLBACK(print_GPIOD), NULL);

  /* Place the second button in the grid cell (1, 1), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach(GTK_GRID(grid), button, 1, 1, 1, 1);

  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy),
                           window);

  /* Place the Quit button in the grid cell (0, 2), and make it
   * span 2 columns.
   */
  gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);

  gtk_widget_show(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  if (wiringPiSetup() == -1) {
    printf("wiringPiSetup failed\n");
    return 1;
  }

  pinMode(GPIO_PIN_A, OUTPUT);
  pinMode(GPIO_PIN_B, OUTPUT);
  pinMode(GPIO_PIN_C, OUTPUT);
  pinMode(GPIO_PIN_D, OUTPUT);

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
