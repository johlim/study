#include <gst/gst.h>

int main(int argc, char *argv[]) {
  GstElement *pipeline, *source, *sink0;
  GstElement *sink1, *sink2, *sink3, *sink4;
	GstElement *bin, *filter, *tee1 , *tee2;
	GstElement *vgagoldfilter, *vgahorizontaledge, * vgathreshold, * vgaratio;
  GstPad *pad;
	GstPad *tee2_src1, *tee2_src2, *tee2_src3, *tee2_src4;
	GstPad *sinkpad1, *sinkpad2, *sinkpad3,  *sinkpad4;
	
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  GstCaps * caps;
	gchar *name;
	
  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Create the elements */
  source = gst_element_factory_make ("videotestsrc", "source");	
  filter = gst_element_factory_make ("rgbdemux", "filter");
  sink0 = gst_element_factory_make ("fakesink", "sink0");
	sink1 = gst_element_factory_make ("fakesink", "sink1");
	sink2 = gst_element_factory_make ("fakesink", "sink2");
	sink3 = gst_element_factory_make ("fakesink", "sink3");
	sink4 = gst_element_factory_make ("fakesink", "sink4");
	tee1  = gst_element_factory_make ("tee","src");
	tee2  = gst_element_factory_make ("tee","src");
	
	vgagoldfilter = gst_element_factory_make ("vgagoldfilter","vgagoldfilter");
	vgahorizontaledge = gst_element_factory_make ("vgahorizontaledge","vgahorizontaledge");
	vgathreshold = gst_element_factory_make ("vgathreshold","vgathreshold");
	vgaratio = gst_element_factory_make ("vgaratio","vgaratio");
	
#if 1  
  bin = gst_bin_new("my_bin");
  gst_bin_add_many(GST_BIN(bin),filter, tee2, vgagoldfilter, vgahorizontaledge, vgathreshold, vgaratio, sink1, sink2, sink3, sink4, NULL);
	
	///
	sinkpad1 = gst_element_get_static_pad (vgagoldfilter, "sink");
	tee2_src1 = gst_element_get_request_pad (tee2, "src_%u");
  name = gst_pad_get_name (tee2_src1);
  g_print ("A new pad %s was created\n", name);
  g_free (name);
	gst_pad_link(tee2_src1, sinkpad1);
	gst_object_unref(GST_OBJECT(sinkpad1));	
  ///
	///
	sinkpad2 = gst_element_get_static_pad (vgahorizontaledge, "sink");
	tee2_src2 = gst_element_get_request_pad (tee2, "src_%u");
  name = gst_pad_get_name (tee2_src2);
  g_print ("A new pad %s was created\n", name);
  g_free (name);
	gst_pad_link(tee2_src2, sinkpad2);
	gst_object_unref(GST_OBJECT(sinkpad2));	
  ///
	///
	sinkpad3 = gst_element_get_static_pad (vgathreshold, "sink");
	tee2_src3 = gst_element_get_request_pad (tee2, "src_%u");
  name = gst_pad_get_name (tee2_src3);
  g_print ("A new pad %s was created\n", name);
  g_free (name);
	gst_pad_link(tee2_src3, sinkpad3);
	gst_object_unref(GST_OBJECT(sinkpad3));	
  ///
	///
	sinkpad4 = gst_element_get_static_pad (vgaratio, "sink");
	tee2_src4 = gst_element_get_request_pad (tee2, "src_%u");
  name = gst_pad_get_name (tee2_src4);
  g_print ("A new pad %s was created\n", name);
  g_free (name);
	gst_pad_link(tee2_src4, sinkpad4);
	gst_object_unref(GST_OBJECT(sinkpad4));	
  ///
	
	gst_element_link (vgagoldfilter, sink1);	
	gst_element_link (vgahorizontaledge, sink2);
	gst_element_link (vgathreshold, sink3);
	gst_element_link (vgaratio, sink4);
	

  pad =gst_element_get_static_pad(filter,"sink"); //extract sink
  gst_element_add_pad(bin,gst_ghost_pad_new("sink",pad)); //link sink to bin
  gst_object_unref(GST_OBJECT(pad));
	
	gst_element_link (filter, tee2);	

#endif

  /* Create the empty pipeline */
  pipeline = gst_pipeline_new ("test-pipeline");

  if (!pipeline || !source || !sink0 || !filter) {
    g_printerr ("Not all elements could be created.\n");
    return -1;
  }

  /* Build the pipeline */
  gst_bin_add_many (GST_BIN (pipeline), source, bin , NULL);


  /* create cap */

  caps = gst_caps_new_simple("video/x-bayer",
          "format",G_TYPE_STRING,"bggr",
          "width",G_TYPE_INT,320,
          "height",G_TYPE_INT,240,
          "framerate",GST_TYPE_FRACTION,25,1, NULL);

  if (gst_element_link_filtered (source,bin,caps) != TRUE) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (pipeline);
    return -1;
  }
  /* Modify the source's properties */
  g_object_set (source, "pattern", 0, NULL);
  g_object_set (source, "num-buffers", 300, NULL);

  GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "testdot");
  /* Start playing */
	
  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    return -1;
  }

	ret = gst_element_set_state (source, GST_STATE_PLAYING);
  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);
  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  /* Parse message */
  if (msg != NULL) {
    GError *err;
    gchar *debug_info;

    switch (GST_MESSAGE_TYPE (msg)) {
      case GST_MESSAGE_ERROR:
        gst_message_parse_error (msg, &err, &debug_info);
        g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
        g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
        g_clear_error (&err);
        g_free (debug_info);
        break;
      case GST_MESSAGE_EOS:
        g_print ("End-Of-Stream reached.\n");
        break;
      default:
        /* We should not reach here because we only asked for ERRORs and EOS */
        g_printerr ("Unexpected message received.\n");
        break;
    }
    gst_message_unref (msg);
  }

  /* Free resources */
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0;
}
