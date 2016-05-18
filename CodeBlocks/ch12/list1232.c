//#include <gtk/gtk.h>
#include <glade/glade.h>

#define GLADE_FILE "greeting.glade"
#define ROOT_WIDGET "window1"


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


int main(int argc, char * argv[])
{
    GladeXML* xml;

    gtk_init(&argc, &argv);


    if (xml = glade_xml_new(GLADE_FILE, ROOT_WIDGET, NULL)) == NULL)
    {
        g_error("Can not load");
        exit(1);

    }

    glade_xml_signal_autoconnect(xml);
    gtk_widget_show_all(glade_xml_get_widget(xml, ROOT_WIDGET));



    gtk_main();

    return 0;
}

