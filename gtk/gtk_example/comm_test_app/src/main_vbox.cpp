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
    GtkWidget * vbox;
    GtkWidget * vbox2;
    GtkWidget * settings;
    GtkWidget * install;
    GtkWidget * player;

    

    GdkPixbuf * icon;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), "Center");
    gtk_window_set_default_size(GTK_WINDOW(window),480,320);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER );
 
    //
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    //vbox = gtk_vbox_new(TRUE, 1);
    vbox2 = gtk_vbox_new(TRUE, 1);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_add(GTK_CONTAINER(window), vbox2);
    settings = gtk_button_new_with_label("Setting");
    install = gtk_button_new_with_label("Install");
    player = gtk_button_new_with_label("Player");

    g_signal_connect(settings, "clicked", G_CALLBACK(button_print_msg), NULL);

    // gtk_box_pack_start(GTK_BOX(vbox), settings, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(vbox), install, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(vbox), player, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox2), settings, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), install, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), player, TRUE, TRUE, 0);

    icon = create_pixbuf("comm_test.png");
    gtk_window_set_icon(GTK_WINDOW(window), icon);
    //gtk_widget_show(window);
    gtk_widget_show_all(window);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_object_unref(icon);
    gtk_main();

    return 0;
}

