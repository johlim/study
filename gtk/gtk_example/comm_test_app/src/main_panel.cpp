#include <gtk/gtk.h>

GtkWidget * curr_window;
GtkWidget * next_window;

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
static void button_widget_exit(void)
{
    fprintf(stdout,"[%s::%s::%d]%s", __FILE__, __func__, __LINE__ \
    ,"hi \n" \
    );
    if (curr_window)
        gtk_widget_destroy (curr_window);
    if (next_window)
    {
        curr_window = next_window;
        gtk_widget_show(curr_window);
        next_window = NULL;
    }
        
}
static void sub_menu_widget(void)
{
    GtkWidget * window;
    GtkWidget * table;
    GtkWidget * button;
    const gchar * const menu_table[2][3]={ 
        {"ADAS","DVR","PLAYER"},
        {"SETTING", "INSTALL", "BACK"},
        };
    if (curr_window)
    {
        gtk_widget_hide (curr_window);
        next_window = curr_window;
    }
    

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    curr_window = window;
    gtk_window_set_title(GTK_WINDOW(window), "Sub");
    gtk_window_set_default_size(GTK_WINDOW(window),480,320);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER );
 
    //
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    table = gtk_table_new(2,3,TRUE);
    
    gtk_table_set_row_spacings(GTK_TABLE(table), 1);
    gtk_table_set_col_spacings(GTK_TABLE(table), 1);

    for (int i=0; i < 2; i++) 
    {
        for(int j=0; j < 3; j++)
        {
            button = gtk_button_new_with_label(menu_table[i][j]);
            gtk_table_attach_defaults(GTK_TABLE(table), button, j,j+1, i, i+1);           
        }
    }
     g_signal_connect(button, "clicked", G_CALLBACK(button_widget_exit), NULL);
    gtk_container_add(GTK_CONTAINER(window), table);
    gtk_widget_show_all(window);
}
typedef void (*FUNC_PTR_TYPE)();

int main(int argc , char * argv[])
{
    GtkWidget * window;
    GtkWidget * table;
    GtkWidget * button;
    const gchar * const menu_table[2][3]={ 
        {"ADAS","DVR","PLAYER"},
        {"SETTING", "INSTALL", "BACK"},
        };
    FUNC_PTR_TYPE function_table[2][3]={ 
        {sub_menu_widget,button_print_msg,button_print_msg},
        {button_print_msg, button_print_msg, button_print_msg},
        };  

    GdkPixbuf * icon;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), "Center");
    curr_window = window;
    gtk_window_set_default_size(GTK_WINDOW(window),480,320);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER );
 
    //
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    table = gtk_table_new(2,3,TRUE);
    
    gtk_table_set_row_spacings(GTK_TABLE(table), 1);
    gtk_table_set_col_spacings(GTK_TABLE(table), 1);

    for (int i=0; i < 2; i++) 
    {
        for(int j=0; j < 3; j++)
        {
            button = gtk_button_new_with_label(menu_table[i][j]);
            gtk_table_attach_defaults(GTK_TABLE(table), button, j,j+1, i, i+1);
            g_signal_connect(button, "clicked", G_CALLBACK(function_table[i][j]), NULL);
        }
    }
    gtk_container_add(GTK_CONTAINER(window), table);

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
