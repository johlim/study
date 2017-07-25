#include <gst/gst.h>

int main(int argc, char *argv[]) {
  GstElement *pipeline, *source, *sink;
  GstElement *o_pipeline, *o_source, *o_filter;
  GstElement *bin;
  GstPad *pad;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Create the elements */
  o_source = gst_element_factory_make ("videotestsrc", "source");
  o_filter = gst_element_factory_make ("bayer2rgb", "filter");
  sink = gst_element_factory_make ("fakesink", "sink");
  
  bin = gst_bin_new("my_bin");
  gst_bin_add(GST_BIN(bin),sink);
  pad =gst_element_get_static_pad(sink,"sink"); //extract sink
  gst_element_add_pad(bin,gst_ghost_pad_new("sink",pad)); //link sink to bin
  gst_object_unref(GST_OBJECT(pad));
/*(
  bin = gst_bin_new("my_srcbin");
  gst_bin_add(GST_BIN(bin),src);
  pad =gst_element_get_static_pad(sink,"sink"); //extract sink
  gst_element_add_pad(bin,gst_ghost_pad_new("sink",pad)); //link sink to bin
  gst_object_unref(GST_OBJECT(pad));
*/
  /* Create the empty pipeline */
  o_pipeline = gst_pipeline_new ("src-pipeline");
  pipeline = gst_pipeline_new ("test-pipeline");

  if (!pipeline || !source || !sink) {
    g_printerr ("Not all elements could be created.\n");
    return -1;
  }

  /* Build the pipeline */
  gst_bin_add_many (GST_BIN (pipeline), o_source, o_filter, bin , NULL);
//  gst_bin_add_many (GST_BIN (pipeline), o_pipeline, sink, NULL);

  gst_element_link_many (o_source, o_filter, bin , NULL);
#if 0
  if (gst_element_link (o_filter, sink) != TRUE) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (pipeline);
    return -1;
  }
#endif
  /* Modify the source's properties */
  g_object_set (o_source, "pattern", 0, NULL);
  g_object_set (o_source, "num-buffers", 1000, NULL);

  GST_DEBUG_BIN_TO_DOT_FILE(pipeline, GST_DEBUG_GRAPH_SHOW_ALL, "testdot");
  /* Start playing */
  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    return -1;
  }

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
