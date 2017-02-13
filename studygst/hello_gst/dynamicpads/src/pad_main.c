/*
 ============================================================================
 Name        : campreview.c
 Author      : 
 Version     : https://gstreamer.freedesktop.org/documentation/application-development/basics/pads.html
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <gst/gst.h>
#include <glib.h>

static gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data) {
	GMainLoop *loop = (GMainLoop *) data;

	  g_print ("Got %s message\n", GST_MESSAGE_TYPE_NAME (msg));

	switch (GST_MESSAGE_TYPE(msg)) {
	case GST_MESSAGE_EOS:
		g_print("End of stream\n");
		g_main_loop_quit(loop);
		break;
	case GST_MESSAGE_ERROR:
		g_print("Error\n");
		g_main_loop_quit(loop);
		break;
	default:
		break;
	}
}
static gboolean cb_message_error(GstBus *bus, GstMessage *msg, gpointer data) {
	GMainLoop *loop = (GMainLoop *) data;

	  g_print ("Got %s eos\n", GST_MESSAGE_TYPE_NAME (msg));

}
static gboolean cb_message_eos(GstBus *bus, GstMessage *msg, gpointer data) {
	GMainLoop *loop = (GMainLoop *) data;

	  g_print ("Got %s eos\n", GST_MESSAGE_TYPE_NAME (msg));

}

static void
cb_new_pad (GstElement *element,
        GstPad     *pad,
        gpointer    data)
{
  gchar *name;

  name = gst_pad_get_name (pad);
  g_print ("A new pad %s was created\n", name);
  g_free (name);

  /* here, you would setup a new pad link for the newly created pad */

}
int main (int
		argc, char *argv[])
{
	  GstElement *pipeline, *source, *demux;
	  GMainLoop *loop;
		GstBus *bus;
		guint bus_watch_id;
	  /* init */
	  gst_init (&argc, &argv);
	  loop = g_main_loop_new (NULL, FALSE);

	  /* create elements */
	  pipeline = gst_pipeline_new ("my_pipeline");
	  source = gst_element_factory_make ("filesrc", "source");
	  g_object_set (source, "location", argv[1], NULL);
	  demux = gst_element_factory_make ("oggdemux", "demuxer");

	  /* you would normally check that the elements were created properly */

	  /* put together a pipeline */
	  gst_bin_add_many (GST_BIN (pipeline), source, demux, NULL);
	  gst_element_link_pads (source, "src", demux, "sink");
	  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

	  /* listen for newly created pads */
	  g_signal_connect (demux, "pad-added", G_CALLBACK (cb_new_pad), NULL);

	  /* start the pipeline */
	  gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);

	  // case 1
	  bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);

	  g_main_loop_run (loop);
	/* clean up */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	// case 1
	//g_source_remove (bus_watch_id);
	g_main_loop_unref (loop);

	return EXIT_SUCCESS;
}
