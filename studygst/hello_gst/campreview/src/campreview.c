/*
 ============================================================================
 Name        : campreview.c
 Author      : 
 Version     :
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
int main (int
		argc, char *argv[])
{
	GMainLoop *loop;
	GstBus *bus;
	guint bus_watch_id;
	GstElement *source;
	GstElement *filter;
	GstElement *sink;
	GstElement *pipeline;
	gst_init (&argc, &argv);
	loop = g_main_loop_new (NULL, FALSE);

	pipeline=gst_pipeline_new ("cam preview");
	//v4l2src ! queue ! autovideosink
	source=gst_element_factory_make ("v4l2src", "video input");
	filter=gst_element_factory_make ("queue", "generic queue");
	sink=gst_element_factory_make ("autovideosink", "display output");
	//sink=gst_element_factory_make ("v4l2sink", "ALSA output");


	//g_object_set (G_OBJECT (source), "location", "music.mp3", NULL);
	gst_bin_add_many (GST_BIN (pipeline), source, filter, sink, NULL);
	gst_element_link_many (source, filter, sink, NULL);
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	// case 1
	// bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);

	// case 2
	gst_bus_add_signal_watch (bus);
	g_signal_connect (bus, "message::error", G_CALLBACK (cb_message_error), NULL);
	g_signal_connect (bus, "message::eos", G_CALLBACK (cb_message_eos), NULL);

	gst_object_unref (bus);

	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	g_main_loop_run (loop);

	/* clean up */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	// case 1
	//g_source_remove (bus_watch_id);
	g_main_loop_unref (loop);

	return EXIT_SUCCESS;
}
