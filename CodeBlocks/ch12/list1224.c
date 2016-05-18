#include <gtk/gtk.h>

#define BTN_WIDTH 200
#define BTN_HEIGHT 50

static void
clicked(GtkWidget* button)
{
    gtk_button_set_label(GTK_BUTTON(button), "Good CLick");
}

static void
key_pressed(GtkWidget* button, GdkEventKey * key)
{
    gtk_button_set_label(GTK_BUTTON(button), "Good Key");
}
int main(int argc, char * argv[])
{
    GtkWidget* window;
    GtkWidget* hbox;
    GtkWidget* button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy" , G_CALLBACK(gtk_main_quit), NULL);

#if 0
    gtk_widget_show(window);
#else
    button = gtk_button_new_with_label("Press me,눌러죠");
    gtk_widget_set_size_request(button, BTN_WIDTH, BTN_HEIGHT);
    g_signal_connect(G_OBJECT(button), "key_press_event" , G_CALLBACK(key_pressed), NULL);
    g_signal_connect(G_OBJECT(button), "clicked" , G_CALLBACK(clicked), NULL);
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show_all(window);
#endif


    gtk_main();

    return 0;
}

