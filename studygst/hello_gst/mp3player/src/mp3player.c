/*
 ============================================================================
 Name        : mp3player.c
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
	return 0;
}

int main (int
		argc, char *argv[])
{
	GMainLoop *loop;
	GstBus *bus;
	GstElement *source;
	GstElement *filter;
	GstElement *sink;
	GstElement *pipeline;
	gst_init (&argc, &argv);
	loop = g_main_loop_new (NULL, FALSE);

	pipeline=gst_pipeline_new ("mp3 player");
	source=gst_element_factory_make ("filesrc", "file reader");
	filter=gst_element_factory_make ("mad", "MP3 decoder");
	sink=gst_element_factory_make ("alsasink", "ALSA output");

	g_object_set (G_OBJECT (source), "location", "music.mp3", NULL);
	gst_bin_add_many (GST_BIN (pipeline), source, filter, sink, NULL);
	gst_element_link_many (source, filter, sink, NULL);
	bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
	gst_bus_add_watch (bus, bus_call, loop);
	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	g_main_loop_run (loop);
	return EXIT_SUCCESS;
}
