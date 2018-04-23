#include <gtk/gtk.h>

static GdkPixbuf * create_pixbuf(const gchar * filename)
{
    GdkPixbuf * pixbuf=NULL;
    GError * error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);

    if (!pixbuf) {
        fprintf(stderr, "%s\n",error->message);
        g_error_free(error);
    }

    return pixbuf;
}

static void button_print_msg(void) 
{
    fprintf(stdout,"[%s::%s::%d]%s", __FILE__, __func__, __LINE__ \
    ,"hi \n" \
    );
    return;
}
int main(int argc , char * argv[])
{
    GtkWidget * window;
    GtkWidget * button;
    GtkWidget * halign;

    GdkPixbuf * icon;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), "Center");
    gtk_window_set_default_size(GTK_WINDOW(window),480,320);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER );
 
    //
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);
    button = gtk_button_new_with_label("Button");
    g_signal_connect(button, "clicked", G_CALLBACK(button_print_msg), NULL);
    halign = gtk_alignment_new(10,10,1,1.0);
    gtk_container_add(GTK_CONTAINER(halign), button);
    gtk_container_add(GTK_CONTAINER(window), halign);
    
    //
    icon = create_pixbuf("comm_test.png");
    gtk_window_set_icon(GTK_WINDOW(window), icon);
    //gtk_widget_show(window);
    gtk_widget_show_all(window);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_object_unref(icon);
    gtk_main();

    return 0;
}

