/*
 * GStreamer
 * Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2015 jhlim <<jhlim@plk.co.kr>>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:element-myfilter
 *
 * plugin test
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! myfilter ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gst/gst.h>

#include "gstmyfilter.h"

GST_DEBUG_CATEGORY_STATIC (gst_my_filter_debug);
#define GST_CAT_DEFAULT gst_my_filter_debug


/* Filter signals and args */
enum
{
	SIGNAL_LDWS_STATUS, 
	SIGNAL_LDWS_WARNNING_LEFT, 
	SIGNAL_LDWS_WARNNING_RIGHT, 
	SIGNAL_LDWS_CAL_TIMEOUT,	
  /* FILL ME */	
  LAST_SIGNAL_LDWS
};

enum
{
  PROP_0,
  PROP_SILENT
};

/* the capabilities of the inputs and outputs.
 *
 * describe the real formats here.
 */
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
		GST_STATIC_CAPS ("ANY")
		);
    

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

#define gst_my_filter_parent_class parent_class
G_DEFINE_TYPE (GstMyFilter, gst_my_filter, GST_TYPE_ELEMENT);

static void gst_my_filter_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_my_filter_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static gboolean gst_my_filter_set_caps(GstPad * pad, GstCaps * caps);
static gboolean gst_my_filter_sink_event (GstPad * pad, GstEvent * event);
static GstFlowReturn gst_my_filter_chain (GstPad * pad, GstBuffer * buf);

static guint gst_my_filter_signals[LAST_SIGNAL_LDWS] =
{ 0, };

/* GObject vmethod implementations */

/* initialize the myfilter's class */
static void
gst_my_filter_class_init (GstMyFilterClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_my_filter_set_property;
  gobject_class->get_property = gst_my_filter_get_property;

  g_object_class_install_property (gobject_class, PROP_SILENT,
      g_param_spec_boolean ("silent", "Silent", "Produce verbose output ?",
          FALSE, G_PARAM_READWRITE));

  gst_element_class_set_details_simple(gstelement_class,
    "ADASPlugin",
    "ADASPlugin",
    "image process and notify result",
    "jhlim <<jhlim@plk.co.kr>>");

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_factory));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_factory));

#if USE_PLUGIN_CALLBACK
    gst_my_filter_signals[SIGNAL_LDWS_STATUS] = g_signal_new(
            "adas_status", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
            G_STRUCT_OFFSET (GstMyFilterClass, adas_status), NULL, NULL,
            g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1, G_TYPE_POINTER);	
    gst_my_filter_signals[SIGNAL_LDWS_WARNNING_LEFT] = g_signal_new(
            "adas_warnning_left", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
            G_STRUCT_OFFSET (GstMyFilterClass, adas_warnning_left), NULL, NULL,
            g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1, G_TYPE_POINTER);
    gst_my_filter_signals[SIGNAL_LDWS_WARNNING_RIGHT] = g_signal_new(
            "adas_warnning_right", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
            G_STRUCT_OFFSET (GstMyFilterClass, adas_warnning_right), NULL, NULL,
            g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1, G_TYPE_POINTER);
		gst_my_filter_signals[SIGNAL_LDWS_CAL_TIMEOUT] = g_signal_new(
            "adas_calibration_timeout", G_TYPE_FROM_CLASS (klass), G_SIGNAL_RUN_LAST,
            G_STRUCT_OFFSET (GstMyFilterClass, adas_calibration_timeout), NULL, NULL,
            g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1, G_TYPE_POINTER);			
#endif
}

/* initialize the new element
 * instantiate pads and add them to element
 * set pad calback functions
 * initialize instance structure
 */
static void
gst_my_filter_init (GstMyFilter * filter)
{
  filter->sinkpad = gst_pad_new_from_static_template (&sink_factory, "sink");
  
  gst_pad_set_event_function (filter->sinkpad,
                              GST_DEBUG_FUNCPTR(gst_my_filter_sink_event));
  gst_pad_set_chain_function (filter->sinkpad,
                              GST_DEBUG_FUNCPTR(gst_my_filter_chain));
// add 
    gst_pad_set_setcaps_function(filter->sinkpad,
            GST_DEBUG_FUNCPTR(gst_my_filter_set_caps));
			
  //GST_PAD_SET_PROXY_CAPS (filter->sinkpad);
	gst_pad_set_getcaps_function (filter->sinkpad,
                                GST_DEBUG_FUNCPTR(gst_pad_proxy_query_caps));
								
  gst_element_add_pad (GST_ELEMENT (filter), filter->sinkpad);

  filter->srcpad = gst_pad_new_from_static_template (&src_factory, "src");
  //GST_PAD_SET_PROXY_CAPS (filter->srcpad);
	gst_pad_set_getcaps_function (filter->srcpad,
                                GST_DEBUG_FUNCPTR(gst_pad_proxy_query_caps));  
  gst_element_add_pad (GST_ELEMENT (filter), filter->srcpad);

  filter->silent = FALSE;
}

static void
gst_my_filter_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstMyFilter *filter = GST_MYFILTER (object);

  switch (prop_id) {
    case PROP_SILENT:
      filter->silent = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_my_filter_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstMyFilter *filter = GST_MYFILTER (object);

  switch (prop_id) {
    case PROP_SILENT:
      g_value_set_boolean (value, filter->silent);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

/* GstElement vmethod implementations */
/* this function handles the link with other elements */
static gboolean gst_my_filter_set_caps(GstPad * pad, GstCaps * caps)
{
	GstMyFilter *filter;
	GstPad *otherpad;

	filter = GST_MYFILTER (gst_pad_get_parent (pad));
	GST_TRACE_OBJECT(filter, "set caps");

	otherpad = (pad == filter->srcpad) ? filter->sinkpad : filter->srcpad;
	gst_object_unref (filter);

	return gst_pad_set_caps (otherpad, caps);
}
/* this function handles sink events */
static gboolean
gst_my_filter_sink_event (GstPad * pad, GstEvent * event)
{
  gboolean ret;
  GstMyFilter *filter;

  filter = GST_MYFILTER (GST_OBJECT_PARENT (pad));
  switch (GST_EVENT_TYPE (event)) {

	case GST_EVENT_EOS:
		//gst_my_filter_stop_prococessing(filter);
    default:
      ret = gst_pad_event_default (pad, NULL, event);
      break;
  }
  return ret;
}

/* chain function
 * this function does the actual processing
 */
static GstFlowReturn
gst_my_filter_chain (GstPad * pad, GstBuffer * buf)
{
  GstMyFilter *filter;

  filter = GST_MYFILTER (GST_OBJECT_PARENT (pad));

  GST_TRACE_OBJECT(filter, "buf (%p)", buf);
  
  if (filter->silent == FALSE)
//    g_print ("I'm plugged, therefore I'm in.\n");
//
#if 1
{
	gint16 *raw;
	raw = (gint16 *)GST_BUFFER_DATA (buf);
	 GST_DEBUG("%08x (%d) \n", (int)raw, GST_BUFFER_SIZE (buf));
	
	
	{
		{
		GST_DEBUG_OBJECT(filter, "signal test");
		g_signal_emit(G_OBJECT (filter), gst_my_filter_signals[SIGNAL_LDWS_CAL_TIMEOUT], 0, 0/*(gpointer)&packet*/);
		}
	}
}	
#endif 
//
  /* just push out the incoming buffer without touching it */
  return gst_pad_push (filter->srcpad, buf);
}


/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean
myfilter_init (GstPlugin * myfilter)
{
  /* debug category for fltering log messages
   *
   * exchange the string 'Template myfilter' with your description
   */
  GST_DEBUG_CATEGORY_INIT (gst_my_filter_debug, "myfilter",
      0, "jhlim myfilter");

  return gst_element_register (myfilter, "myfilter", GST_RANK_NONE,
      GST_TYPE_MYFILTER);
}

/* PACKAGE: this is usually set by autotools depending on some _INIT macro
 * in configure.ac and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use autotools to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "myadaspluing"
#endif

/* gstreamer looks for this structure to register myfilters
 *
 * exchange the string 'Template myfilter' with your myfilter description
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    "myfilter",
    "jhlim myfilter",
    myfilter_init,
    VERSION,
    "LGPL",
    "GStreamer",
    "http://gstreamer.net/"
)
