/* crude program to toggle on and off GPIO pins on the Orange Pi 5
this program uses the wiringOP and GTK libraries, download per the
the instructions on the websites:

https://github.com/orangepi-xunlong/wiringOP
https://www.gtk.org/docs/installations/linux

to compile, from a terminal in the sme directory as this file -
gcc $( pkg-config --cflags gtk4 ) -o GUItest2 GUItest2.c $( pkg-config --libs gtk4 ) -lwiringPi

to run, from a terminal -
sudo ./GUItest2

to confirm GPIO state, from a separate terminal enter -
gpio readall

 */

#include <gtk/gtk.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

#define G_APPLICATION_DEFAULT_FLAGS 0

// Define a few pins to be able to test, these are the numbers in
// the wPi column from gpio readall
#define FAN_PIN_16 16
#define FAN_PIN_2 2
#define FAN_PIN_3 3
#define FAN_PIN_4 4

static void
print_GPIO16 (GtkWidget *widget,
             gpointer   data)
            
{   int GPIO_on ;
GPIO_on = digitalRead(FAN_PIN_16);
    if (  GPIO_on == 0) {
  g_print ("GPIO 16 On\n");
              digitalWrite(FAN_PIN_16, 1);
} 
              else {g_print ("GPIO 16 Off\n");
              digitalWrite(FAN_PIN_16,0);
              }
}

static void
print_GPIO2 (GtkWidget *widget,
             gpointer   data)
            
{   int GPIO_on ;
GPIO_on = digitalRead(FAN_PIN_2);
    if (  GPIO_on == 0) {
  g_print ("GPIO 2 On\n");
              digitalWrite(FAN_PIN_2, 1);
} 
              else {g_print ("GPIO 2 Off\n");
              digitalWrite(FAN_PIN_2,0);
              }
}

static void
print_GPIO3 (GtkWidget *widget,
             gpointer   data)
            
{   int GPIO_on ;
GPIO_on = digitalRead(FAN_PIN_3);
    if (  GPIO_on == 0) {
  g_print ("GPIO 3 On\n");
              digitalWrite(FAN_PIN_3, 1);
} 
              else {g_print ("GPIO 3 Off\n");
              digitalWrite(FAN_PIN_3,0);
              }
}

static void
print_GPIO4 (GtkWidget *widget,
             gpointer   data)
            
{   int GPIO_on ;
GPIO_on = digitalRead(FAN_PIN_4);
    if (  GPIO_on == 0) {
  g_print ("GPIO 4 On\n");
              digitalWrite(FAN_PIN_4, 1);
} 
              else {g_print ("GPIO 4 Off\n");
              digitalWrite(FAN_PIN_4,0);
              }
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "GPIO Tester");

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_window_set_child (GTK_WINDOW (window), grid);

  button = gtk_button_new_with_label ("GPIO 16");
  g_signal_connect (button, "clicked", G_CALLBACK (print_GPIO16), NULL);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("GPIO 2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_GPIO2), NULL);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

  button = gtk_button_new_with_label ("GPIO 3");
  g_signal_connect (button, "clicked", G_CALLBACK (print_GPIO3), NULL);

  /* Place the first button in the grid cell (0, 1), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);

  button = gtk_button_new_with_label ("GPIO 4");
  g_signal_connect (button, "clicked", G_CALLBACK (print_GPIO4), NULL);

  /* Place the second button in the grid cell (1, 1), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button, 1, 1, 1, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);

  /* Place the Quit button in the grid cell (0, 2), and make it
   * span 2 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 2, 1);

  gtk_widget_show (window);

}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;


      if (wiringPiSetup() == -1) {
        printf("wiringPiSetup failed\n");
        return 1;
    }
    
    pinMode(FAN_PIN_16, OUTPUT);
     pinMode(FAN_PIN_2, OUTPUT);
         pinMode(FAN_PIN_3, OUTPUT);
     pinMode(FAN_PIN_4, OUTPUT);

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
