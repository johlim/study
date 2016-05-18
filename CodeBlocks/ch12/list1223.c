#include <gtk/gtk.h>

#define BTN_WIDTH 200
#define BTN_HEIGHT 50

static void
morning()
{
    printf("Good morning!");
}

static void
afternoon()
{
    printf("Good afternoon!");
}

static void
evening()
{
    printf("Good evening!");
}

static void
pack_button(GtkWidget* hbox, const char * label, GCallback func)
{
    GtkWidget* button = gtk_button_new_with_label(label);

    gtk_widget_set_size_request(button, BTN_WIDTH, BTN_HEIGHT);
    gtk_container_add(GTK_CONTAINER(hbox), button);
    //gtk_widget_show_all(window);
    g_signal_connect(G_OBJECT(button), "clicked" , G_CALLBACK(func), NULL);
}
int main(int argc, char * argv[])
{
    GtkWidget* window;
    GtkWidget* hbox;
    GtkWidget* button1;
    GtkWidget* button2;
    GtkWidget* button3;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy" , G_CALLBACK(gtk_main_quit), NULL);

#if 0
    gtk_widget_show(window);
#else
    hbox = gtk_hbox_new(TRUE, 0);
    pack_button(hbox, "10:00" , morning);
    pack_button(hbox, "13:00" , afternoon);
    pack_button(hbox, "18:00" , evening);

    gtk_container_add(GTK_CONTAINER(window), hbox);
    gtk_widget_show_all(window);
#endif


    gtk_main();

    return 0;
}

