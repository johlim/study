

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gst-app.h"

static GMainLoop *loop;

static void
seek_to_time (GstElement *pipeline,
		gint64      time_nanoseconds)
{
	if (!gst_element_seek (pipeline, 1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
				GST_SEEK_TYPE_SET, time_nanoseconds,
				GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE)) {
		g_print ("Seek failed!\n");
	}
}

static gboolean
cb_print_position (GstElement *pipeline)
{
	gint64 pos, len;

	if (gst_element_query_position (pipeline, GST_FORMAT_TIME, &pos)
			&& gst_element_query_duration (pipeline, GST_FORMAT_TIME, &len)) {
		g_print ("Time: %" GST_TIME_FORMAT " / %" GST_TIME_FORMAT "\r",
				GST_TIME_ARGS (pos), GST_TIME_ARGS (len));
	}

	/* call me again */
	return TRUE;
}

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
		//g_print ("eos: %s\n", __func__);
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
	g_print ("eos: %s\n", __func__);
	g_main_loop_quit (loop);
	return TRUE;
}

GstElement *pipeline, *source, *sink;
GstElement *demux,*decoder, *conv, *sink;	
static void cb_new_pad (GstElement *element,GstPad *pad,gpointer data)
{
	gchar *name;
	GstPad *sinkpad;
	GstElement *decoder = (GstElement *) data;
	
	name = gst_pad_get_name (pad);
	g_print ("A new pad %s was created\n", name);
	
	g_free (name);
	
	/* here, you would setup a new pad link for the newly created pad */
	
	//gst_element_link_pads (element, "src", sink, "sink");
	//gst_element_link (bin, sink);
	sinkpad = gst_element_get_static_pad (decoder, "sink");
	gst_pad_link (pad, sinkpad);
	gst_object_unref (sinkpad);
	//gst_element_sync_state_with_parent (element);
	return ;
}
int
main (int argc, char *argv[])
{


	GstBus *bus;
	guint bus_watch_id;
	/* init */
	gst_init (&argc, &argv);

	/* Check input arguments */
	if (argc != 2) {
		g_printerr ("Usage: %s <Ogg/Vorbis filename>\n", argv[0]);
		return -1;
	}	

	loop = g_main_loop_new (NULL, FALSE);

	/* create */
	pipeline = gst_pipeline_new ("audio-player");

	source   = gst_element_factory_make ("filesrc",       "file-source");
	g_object_set (source, "location", argv[1], NULL);
	demux  = gst_element_factory_make ("oggdemux",      "ogg-demuxer");
	decoder  = gst_element_factory_make ("vorbisdec",     "vorbis-decoder");
	conv     = gst_element_factory_make ("audioconvert",  "converter");
	sink     = gst_element_factory_make ("autoaudiosink", "audio-output");

	/* First add the elements to the bin */
	gst_bin_add_many (GST_BIN (pipeline), source, demux, decoder, conv, sink, NULL);
	gst_element_link_pads (source, "src", demux, "sink");
	gst_element_link_many (decoder, conv, sink, NULL);

	/* listen for newly created pads */
	g_signal_connect (demux, "pad-added", G_CALLBACK (cb_new_pad), decoder);


	/* link the elements */
	gst_element_link (source, demux);

	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	bus_watch_id = gst_bus_add_watch (bus, my_bus_callback, NULL);
	g_signal_connect (bus, "message::eos", G_CALLBACK (cb_message_eos), NULL);

	gst_object_unref (bus);

	gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);	

	g_timeout_add (200, (GSourceFunc) cb_print_position, pipeline);
	seek_to_time(pipeline, 1000*1000*1000*100);
	g_main_loop_run (loop);

	/* clean up */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);

	g_source_remove (bus_watch_id);

	g_main_loop_unref (loop);
	
	return 0;
}
