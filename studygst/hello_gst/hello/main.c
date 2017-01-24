
#include <stdio.h>
#include <unistd.h>
#include <gst/gst.h>

int
check_ver (int   argc,
      char *argv[])
{
  const gchar *nano_str;
  guint major, minor, micro, nano;

  //gst_init (&argc, &argv);

  gst_version (&major, &minor, &micro, &nano);

  if (nano == 1)
    nano_str = "(CVS)";
  else if (nano == 2)
    nano_str = "(Prerelease)";
  else
    nano_str = "";

  printf ("This program is linked against GStreamer %d.%d.%d %s\n",
          major, minor, micro, nano_str);

  return 0;
}



int
main (int   argc,
      char *argv[])
{
  GstElement *source_element;
  GstElement *fileter_element;
  GstElement *pad_element;
  GstElement *pipeline;

  /* init GStreamer */
  gst_init (&argc, &argv);

  check_ver(argc, argv);
  /* create element */
  source_element = gst_element_factory_make ("audiotestsrc", "source");
  if (!source_element) {
    g_print ("Failed to create element of type 'fakesrc'\n");
    return -1;
  }

  fileter_element = gst_element_factory_make ("audioresample", "filter");
  if (!fileter_element) {
    g_print ("Failed to create element of type 'fakesrc'\n");
    return -1;
  }

  pad_element = gst_element_factory_make ("pulsesink", "sink");
  if (!pad_element) {
    g_print ("Failed to create element of type 'fakesrc'\n");
    return -1;
  }

  /* create pipeline */
  pipeline = gst_pipeline_new ("my-pipeline");
  gst_bin_add_many (GST_BIN (pipeline), source_element, fileter_element, pad_element, NULL);
  /* link */
  if (!gst_element_link_many (source_element, fileter_element, pad_element, NULL)) {
    g_warning ("Failed to link elements!");
  }
  //audiotestsrc !  audioresample ! pulsesink

  gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);

  gst_object_unref (GST_OBJECT (pipeline));
  gst_object_unref (GST_OBJECT (pad_element));
  gst_object_unref (GST_OBJECT (fileter_element));
  gst_object_unref (GST_OBJECT (source_element));

  sleep(1);

  return 0;
}
