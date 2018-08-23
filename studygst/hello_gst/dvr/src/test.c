#include <gst/gst.h>

int
main(int argc, char * argv[])
{
    GMainLoop * loop;
    GstElement * bin;
    GstElement * pipeline;
    GstElement * source;
    GstElement * sink;
    GstElement * queue_1;
//    GstElement * fakesink;
//    GstElement * fakesrc;
    GstPad * pad;

    gst_init(&argc, &argv);

    pipeline =gst_pipeline_new("mainpipeline");

    bin = gst_bin_new("recbin");

    source = gst_element_factory_make("fakesrc", "source");
    sink = gst_element_factory_make("fakesink", "sink");
    queue_1 = gst_element_factory_make("queue", "queue_1");

    gst_bin_add_many(GST_BIN(bin), queue_1, sink, NULL);
    gst_element_link(queue_1,sink);
    pad = gst_element_get_static_pad (queue_1, "sink"); 
    gst_element_add_pad (bin, gst_ghost_pad_new ("sink", pad)); 
    gst_object_unref (GST_OBJECT (pad));

    gst_bin_add_many(GST_BIN(pipeline), source, bin, NULL);
    
    gst_element_link(source, bin);

    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
    
    GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "m_pipeline");

    loop = g_main_loop_new(NULL, FALSE);

    g_main_loop_run(loop);

}
