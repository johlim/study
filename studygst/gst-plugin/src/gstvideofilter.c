/* GStreamer video filter example class
 * Copyright (C) <1999> Erik Walthinsen <omega@cse.ogi.edu>
 * Copyright (C) <2003> David Schleef <ds@schleef.org>
 * Copyright (C) YEAR AUTHOR_NAME AUTHOR_EMAIL
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
 * SECTION:element-plugin
 *
 * FIXME:Describe plugin here.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m videotestsrc ! plugin ! autovideosink
 * ]|
 * </refsect2>
 */
 
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>
#include <string.h>

GST_DEBUG_CATEGORY_STATIC (videofiltertemplate_debug);
#define GST_CAT_DEFAULT videofiltertemplate_debug

typedef struct _GstVideoFilterTemplate GstVideoFilterTemplate;
typedef struct _GstVideoFilterTemplateClass GstVideoFilterTemplateClass;

/* These are boilerplate cast macros and type check macros */
#define GST_TYPE_VIDEO_FILTER_TEMPLATE \
  (gst_video_filter_template_get_type())
#define GST_VIDEO_FILTER_TEMPLATE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_VIDEO_FILTER_TEMPLATE,GstVideoFilterTemplate))
#define GST_VIDEO_FILTER_TEMPLATE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_VIDEO_FILTER_TEMPLATE,GstVideoFilterTemplateClass))
#define GST_IS_VIDEO_FILTER_TEMPLATE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_VIDEO_FILTER_TEMPLATE))
#define GST_IS_VIDEO_FILTER_TEMPLATE_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_VIDEO_FILTER_TEMPLATE))

struct _GstVideoFilterTemplate
{
  GstVideoFilter videofilter;

  /* here you can add additional per-instance
   * data such as properties */
};

struct _GstVideoFilterTemplateClass
{
  GstVideoFilterClass videofilter_class;
};


enum
{
  /* FILL ME */
  LAST_SIGNAL
};

enum
{
  ARG_0
  /* FILL ME */
};

G_DEFINE_TYPE (GstVideoFilterTemplate, gst_video_filter_template,
    GST_TYPE_VIDEO_FILTER);

static void gst_video_filter_template_set_property (GObject * object,
    guint prop_id, const GValue * value, GParamSpec * pspec);
static void gst_video_filter_template_get_property (GObject * object,
    guint prop_id, GValue * value, GParamSpec * pspec);

static GstFlowReturn gst_video_filter_template_filter (GstBaseTransform * bt,
    GstBuffer * outbuf, GstBuffer * inbuf);
static GstFlowReturn
gst_video_filter_template_filter_inplace (GstBaseTransform * base_transform,
    GstBuffer * buf);

#if 0
/* This means we support signed 16-bit pcm and signed 32-bit pcm in native
 * endianness */
#define SUPPORTED_CAPS_STRING \
    GST_VIDEO_CAPS_MAKE("{ " GST_VIDEO_NE(S16) ", " GST_VIDEO_NE(S32) " }")
#endif

/* FIXME: add/remove formats you can handle */
#define VIDEO_SRC_CAPS \
    GST_VIDEO_CAPS_MAKE("{ I420, Y444, Y42B, UYVY, RGBA , YUY2 }")

/* FIXME: add/remove formats you can handle */
#define VIDEO_SINK_CAPS \
    GST_VIDEO_CAPS_MAKE("{ I420, Y444, Y42B, UYVY, RGBA , YUY2 }")

/* GObject vmethod implementations */
static void
gst_video_filter_template_class_init (GstVideoFilterTemplateClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *element_class;
  GstBaseTransformClass *btrans_class;
  GstVideoFilterClass *video_filter_class;
  GstCaps *caps;

  gobject_class = (GObjectClass *) klass;
  element_class = (GstElementClass *) klass;
  btrans_class = (GstBaseTransformClass *) klass;
  video_filter_class = (GstVideoFilterClass *) klass;

#if 0
  g_object_class_install_property (gobject_class, ARG_METHOD,
      g_param_spec_enum ("method", "method", "method",
          GST_TYPE_VIDEOTEMPLATE_METHOD, GST_VIDEOTEMPLATE_METHOD_1,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
#endif

  gobject_class->set_property = gst_video_filter_template_set_property;
  gobject_class->get_property = gst_video_filter_template_get_property;


  /* here you set up functions to process data (either in place, or from
   * one input buffer to another output buffer); only one is required */
  btrans_class->transform = gst_video_filter_template_filter;
 // btrans_class->transform_ip = gst_video_filter_template_filter_inplace;
  /* Set some basic metadata about your new element */
  gst_element_class_set_details_simple (element_class,
    "Video Filter Template", /* FIXME: short name */
    "Filter/Effect/Video",
    "Filters video", /* FIXME: short description*/
    "Name <mail@example.com>"); /* FIXME: author */
  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS(klass),
      gst_pad_template_new ("src", GST_PAD_SRC, GST_PAD_ALWAYS,
        gst_caps_from_string (VIDEO_SRC_CAPS)));
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS(klass),
      gst_pad_template_new ("sink", GST_PAD_SINK, GST_PAD_ALWAYS,
        gst_caps_from_string (VIDEO_SINK_CAPS)));

}

static void
gst_video_filter_template_init (GstVideoFilterTemplate * filter)
{
  /* This function is called when a new filter object is created. You
   * would typically do things like initialise properties to their
   * default values here if needed. */
}

static void
gst_video_filter_template_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstVideoFilterTemplate *filter = GST_VIDEO_FILTER_TEMPLATE (object);

  GST_OBJECT_LOCK (filter);
  switch (prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (filter);
}

static void
gst_video_filter_template_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstVideoFilterTemplate *filter = GST_VIDEO_FILTER_TEMPLATE (object);

  GST_OBJECT_LOCK (filter);
  switch (prop_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
  GST_OBJECT_UNLOCK (filter);
}

/* You may choose to implement either a copying filter or an
 * in-place filter (or both).  Implementing only one will give
 * full functionality, however, implementing both will cause
 * videofilter to use the optimal function in every situation,
 * with a minimum of memory copies. */

static GstFlowReturn
gst_video_filter_template_filter (GstBaseTransform * base_transform,
    GstBuffer * inbuf, GstBuffer * outbuf)
{
  GstVideoFilterTemplate *filter = GST_VIDEO_FILTER_TEMPLATE (base_transform);
  GstMapInfo map_in;
  GstMapInfo map_out;

  GST_LOG_OBJECT (filter, "transform buffer");

  /* FIXME: do something interesting here.  We simply copy the input data
   * to the output buffer for now. */
  if (gst_buffer_map (inbuf, &map_in, GST_MAP_READ)) {
    if (gst_buffer_map (outbuf, &map_out, GST_MAP_WRITE)) {
      g_assert (map_out.size == map_in.size);
      memcpy (map_out.data, map_in.data, map_out.size);
      gst_buffer_unmap (outbuf, &map_out);
    }
    gst_buffer_unmap (inbuf, &map_in);
  }

  return GST_FLOW_OK;
}

static GstFlowReturn
gst_video_filter_template_filter_inplace (GstBaseTransform * base_transform,
    GstBuffer * buf)
{
  GstVideoFilterTemplate *filter = GST_VIDEO_FILTER_TEMPLATE (base_transform);
  GstFlowReturn flow = GST_FLOW_OK;
  GstMapInfo map;

  GST_LOG_OBJECT (filter, "transform buffer in place");

  /* FIXME: do something interesting here.  Doing nothing means the input
   * buffer is simply pushed out as is without any modification */
  if (gst_buffer_map (buf, &map, GST_MAP_READWRITE)) {
#if 0
    switch (GST_VIDEO_FILTER_FORMAT (filter)) {
      case GST_VIDEO_FORMAT_S16LE:
      case GST_VIDEO_FORMAT_S16BE: {
        gint16 *samples = map.data;
        guint n_samples = map.size / sizeof (gint16);
        guint i;

        for (i = 0; i < n; ++n) {
          samples[i] = samples[i];
        }
        break;
      }
      default:
        g_warning ("Unexpected video format %s!",
            GST_VIDEO_INFO_NAME (GST_VIDEO_FILTER_INFO(filter)));
        flow = GST_FLOW_ERROR;
        break;
    }
#endif
    gst_buffer_unmap (buf, &map);
  }

  return flow;
}

static gboolean
plugin_init (GstPlugin * plugin)
{
  /* Register debug category for filtering log messages
   * FIXME:exchange the string 'Template plugin' with your description */
  GST_DEBUG_CATEGORY_INIT (videofiltertemplate_debug, "videofiltertemplate", 0,
      "Video filter template example");

  /* This is the name used in gst-launch-1.0 and gst_element_factory_make() */
  return gst_element_register (plugin, "videofiltertemplate", GST_RANK_NONE,
      GST_TYPE_VIDEO_FILTER_TEMPLATE);
}

/* gstreamer looks for this structure to register plugins
 *
 * FIXME:exchange the string 'Template plugin' with you plugin description
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    videofiltertemplateplugin,
    "Video filter template plugin",
    plugin_init,
    VERSION, "LGPL",
    "GStreamer",
    "http://gstreamer.freedesktop.org"
);
