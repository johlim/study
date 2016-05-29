#include <stdlib.h>
#include <gtk/gtk.h>
#include <unicap.h>
#include <unicapgtk.h>

int
main (int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget* ugtk_display;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    ugtk_display =  unicapgtk_video_display_new_by_device(NULL);
// 실제 UVC 를 장치해야 동작할 수 있는 부분
    unicapgtk_video_display_start(UNICAPGTK_VIDEO_DISPLAY(ugtk_display));
//
    gtk_widget_show_all(window);
    gtk_main();

    return 0;

}
