

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gst-app.h"

static GMainLoop *loop;

static gboolean my_bus_callback (GstBus *bus,GstMessage *message,gpointer data)
{
	//g_print ("Got %s messagen", GST_MESSAGE_TYPE_NAME (message));
	
	switch (GST_MESSAGE_TYPE (message)) {
		case GST_MESSAGE_ERROR: {
		GError *err;
		gchar *debug;
		gst_message_parse_error (message, &err, &debug);
		g_print ("Error: %s\n", err->message);
		g_error_free (err);//!!
		g_free (debug);//!!
		g_main_loop_quit (loop);
		break;
		}
		
		case GST_MESSAGE_EOS:
		/* end-of-stream */
		g_main_loop_quit (loop);
		break;
		default:
		/* unhandled message */
		break;
	}
	
	/* we want to be notified again the next time there is a message
	* on the bus, so returning TRUE (FALSE means we want to stop watching
	* for messages on the bus and our callback should not be called again)
	*/
	return TRUE;
}
/* not call */ 
static gboolean cb_message_error(GstBus *bus,GstMessage *message,gpointer data)
{
	return TRUE;
}
/* not call */
static gboolean cb_message_eos(GstBus *bus,GstMessage *message,gpointer data)
{
	g_print ("Error: %s\n", __func__);
	g_main_loop_quit (loop);
	return TRUE;
}
int
main (int argc, char *argv[])
{
	GstElement *bin, *pipeline, *source, *sink;
	GstBus *bus;
	guint bus_watch_id;
	/* init */
	gst_init (&argc, &argv);

	/* create */
	pipeline = gst_pipeline_new ("my_pipeline");
	bin = gst_bin_new ("my_bin");
	source = gst_element_factory_make ("fakesrc", "source");
	sink = gst_element_factory_make ("fakesink", "sink");

	/* First add the elements to the bin */
	gst_bin_add_many (GST_BIN (bin), source, sink, NULL);

	/* add the bin to the pipeline */
	gst_bin_add (GST_BIN (pipeline), bin);

	/* link the elements */
	gst_element_link (source, sink);

	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	bus_watch_id = gst_bus_add_watch (bus, my_bus_callback, NULL);
	g_signal_connect (bus, "message::error", G_CALLBACK (cb_message_error), NULL);
	g_signal_connect (bus, "message::eos", G_CALLBACK (cb_message_eos), NULL);

	g_object_set (source, "num-buffers", 30, NULL);

	gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);	

	loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (loop);

	/* clean up */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	g_source_remove (bus_watch_id);
	g_main_loop_unref (loop);
	
	return 0;
}
