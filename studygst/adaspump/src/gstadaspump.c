/* GStreamer
 * Copyright (C) 2017 lim jonghoan <johlim@daum.net>
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
 * Free Software Foundation, Inc., 51 Franklin Street, Suite 500,
 * Boston, MA 02110-1335, USA.
 */
/**
 * SECTION:element-gstadaspump
 *
 * The adaspump element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! adaspump ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>
#include "gstadaspump.h"

GST_DEBUG_CATEGORY_STATIC (gst_adaspump_debug_category);
#define GST_CAT_DEFAULT gst_adaspump_debug_category

/* prototypes */


static void gst_adaspump_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_adaspump_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);
static void gst_adaspump_dispose (GObject * object);
static void gst_adaspump_finalize (GObject * object);

static GstCaps *gst_adaspump_transform_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, GstCaps * filter);
static GstCaps *gst_adaspump_fixate_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps);
static gboolean gst_adaspump_accept_caps (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps);
static gboolean gst_adaspump_set_caps (GstBaseTransform * trans,
    GstCaps * incaps, GstCaps * outcaps);
static gboolean gst_adaspump_query (GstBaseTransform * trans,
    GstPadDirection direction, GstQuery * query);
static gboolean gst_adaspump_decide_allocation (GstBaseTransform * trans,
    GstQuery * query);
static gboolean gst_adaspump_filter_meta (GstBaseTransform * trans,
    GstQuery * query, GType api, const GstStructure * params);
static gboolean gst_adaspump_propose_allocation (GstBaseTransform * trans,
    GstQuery * decide_query, GstQuery * query);
static gboolean gst_adaspump_transform_size (GstBaseTransform * trans,
    GstPadDirection direction, GstCaps * caps, gsize size, GstCaps * othercaps,
    gsize * othersize);
static gboolean gst_adaspump_get_unit_size (GstBaseTransform * trans,
    GstCaps * caps, gsize * size);
static gboolean gst_adaspump_start (GstBaseTransform * trans);
static gboolean gst_adaspump_stop (GstBaseTransform * trans);
static gboolean gst_adaspump_sink_event (GstBaseTransform * trans,
    GstEvent * event);
static gboolean gst_adaspump_src_event (GstBaseTransform * trans,
    GstEvent * event);
static GstFlowReturn gst_adaspump_prepare_output_buffer (GstBaseTransform *
    trans, GstBuffer * input, GstBuffer ** outbuf);
static gboolean gst_adaspump_copy_metadata (GstBaseTransform * trans,
    GstBuffer * input, GstBuffer * outbuf);
static gboolean gst_adaspump_transform_meta (GstBaseTransform * trans,
    GstBuffer * outbuf, GstMeta * meta, GstBuffer * inbuf);
static void gst_adaspump_before_transform (GstBaseTransform * trans,
    GstBuffer * buffer);
static GstFlowReturn gst_adaspump_transform (GstBaseTransform * trans,
    GstBuffer * inbuf, GstBuffer * outbuf);
static GstFlowReturn gst_adaspump_transform_ip (GstBaseTransform * trans,
    GstBuffer * buf);

enum
{
  PROP_0
};

/* pad templates */

static GstStaticPadTemplate gst_adaspump_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

static GstStaticPadTemplate gst_adaspump_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );


/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstAdaspump, gst_adaspump, GST_TYPE_BASE_TRANSFORM,
  GST_DEBUG_CATEGORY_INIT (gst_adaspump_debug_category, "adaspump", 0,
  "debug category for adaspump element"));

static void
gst_adaspump_class_init (GstAdaspumpClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseTransformClass *base_transform_class = GST_BASE_TRANSFORM_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS(klass),
      gst_static_pad_template_get (&gst_adaspump_src_template));
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS(klass),
      gst_static_pad_template_get (&gst_adaspump_sink_template));

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS(klass),
      "lim jong hoan", "Generic", "make filter image with yuv data and pump sink2 ",
      "jhlim <johlim@daum.net>");

  gobject_class->set_property = gst_adaspump_set_property;
  gobject_class->get_property = gst_adaspump_get_property;
  //gobject_class->dispose = gst_adaspump_dispose;
  //gobject_class->finalize = gst_adaspump_finalize;
  //base_transform_class->transform_caps = GST_DEBUG_FUNCPTR (gst_adaspump_transform_caps);
  //base_transform_class->fixate_caps = GST_DEBUG_FUNCPTR (gst_adaspump_fixate_caps);
  //base_transform_class->accept_caps = GST_DEBUG_FUNCPTR (gst_adaspump_accept_caps);
  base_transform_class->set_caps = GST_DEBUG_FUNCPTR (gst_adaspump_set_caps);
  //base_transform_class->query = GST_DEBUG_FUNCPTR (gst_adaspump_query);
  //base_transform_class->decide_allocation = GST_DEBUG_FUNCPTR (gst_adaspump_decide_allocation);
  //base_transform_class->filter_meta = GST_DEBUG_FUNCPTR (gst_adaspump_filter_meta);
  //base_transform_class->propose_allocation = GST_DEBUG_FUNCPTR (gst_adaspump_propose_allocation);
  //base_transform_class->transform_size = GST_DEBUG_FUNCPTR (gst_adaspump_transform_size);
  //base_transform_class->get_unit_size = GST_DEBUG_FUNCPTR (gst_adaspump_get_unit_size);
  //base_transform_class->start = GST_DEBUG_FUNCPTR (gst_adaspump_start);
  //base_transform_class->stop = GST_DEBUG_FUNCPTR (gst_adaspump_stop);
  //base_transform_class->sink_event = GST_DEBUG_FUNCPTR (gst_adaspump_sink_event);
  //base_transform_class->src_event = GST_DEBUG_FUNCPTR (gst_adaspump_src_event);
  //base_transform_class->prepare_output_buffer = GST_DEBUG_FUNCPTR (gst_adaspump_prepare_output_buffer);
  //base_transform_class->copy_metadata = GST_DEBUG_FUNCPTR (gst_adaspump_copy_metadata);
  //base_transform_class->transform_meta = GST_DEBUG_FUNCPTR (gst_adaspump_transform_meta);
  //base_transform_class->before_transform = GST_DEBUG_FUNCPTR (gst_adaspump_before_transform);
  //base_transform_class->transform = GST_DEBUG_FUNCPTR (gst_adaspump_transform);
  base_transform_class->transform_ip = GST_DEBUG_FUNCPTR (gst_adaspump_transform_ip);

}

static void
gst_adaspump_init (GstAdaspump *adaspump)
{
}

void
gst_adaspump_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstAdaspump *adaspump = GST_ADASPUMP (object);

  GST_DEBUG_OBJECT (adaspump, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_adaspump_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstAdaspump *adaspump = GST_ADASPUMP (object);

  GST_DEBUG_OBJECT (adaspump, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_adaspump_dispose (GObject * object)
{
  GstAdaspump *adaspump = GST_ADASPUMP (object);

  GST_DEBUG_OBJECT (adaspump, "dispose");

  /* clean up as possible.  may be called multiple times */

  G_OBJECT_CLASS (gst_adaspump_parent_class)->dispose (object);
}

void
gst_adaspump_finalize (GObject * object)
{
  GstAdaspump *adaspump = GST_ADASPUMP (object);

  GST_DEBUG_OBJECT (adaspump, "finalize");

  /* clean up object here */

  G_OBJECT_CLASS (gst_adaspump_parent_class)->finalize (object);
}

static GstCaps *
gst_adaspump_transform_caps (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps, GstCaps * filter)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);
  GstCaps *othercaps;

  GST_DEBUG_OBJECT (adaspump, "transform_caps");

  othercaps = gst_caps_copy (caps);

  /* Copy other caps and modify as appropriate */
  /* This works for the simplest cases, where the transform modifies one
   * or more fields in the caps structure.  It does not work correctly
   * if passthrough caps are preferred. */
  if (direction == GST_PAD_SRC) {
    /* transform caps going upstream */
  } else {
    /* transform caps going downstream */
  }

  if (filter) {
    GstCaps *intersect;

    intersect = gst_caps_intersect (othercaps, filter);
    gst_caps_unref (othercaps);

    return intersect;
  } else {
    return othercaps;
  }
}

static GstCaps *
gst_adaspump_fixate_caps (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps, GstCaps * othercaps)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "fixate_caps");

  return NULL;
}

static gboolean
gst_adaspump_accept_caps (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "accept_caps");

  return TRUE;
}

static gboolean
gst_adaspump_set_caps (GstBaseTransform * trans, GstCaps * incaps,
    GstCaps * outcaps)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "set_caps");

  GstStructure *structure;
  int rate, channels;
  gboolean ret;
  gchar * format;
  //GstCaps *outcaps;

  structure = gst_caps_get_structure (incaps, 0);
  ret = gst_structure_get_int (structure, "rate", &rate);
  ret = ret && gst_structure_get_int (structure, "channels", &channels);
  format = gst_structure_get_string (structure, "format");

  g_print("in format %s \n", format);

  structure = gst_caps_get_structure (outcaps, 0);
  ret = gst_structure_get_int (structure, "rate", &rate);
  ret = ret && gst_structure_get_int (structure, "channels", &channels);
  format = gst_structure_get_string (structure, "format");

  g_print("out format %s \n", format);

#if 0
  if (g_strcmp0(format, "S16LE")==0)
	  return TRUE;
  else
	  return FALSE;
#endif
  return TRUE;
}

static gboolean
gst_adaspump_query (GstBaseTransform * trans, GstPadDirection direction,
    GstQuery * query)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "query");

  return TRUE;
}

/* decide allocation query for output buffers */
static gboolean
gst_adaspump_decide_allocation (GstBaseTransform * trans, GstQuery * query)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "decide_allocation");

  return TRUE;
}

static gboolean
gst_adaspump_filter_meta (GstBaseTransform * trans, GstQuery * query, GType api,
    const GstStructure * params)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "filter_meta");

  return TRUE;
}

/* propose allocation query parameters for input buffers */
static gboolean
gst_adaspump_propose_allocation (GstBaseTransform * trans,
    GstQuery * decide_query, GstQuery * query)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "propose_allocation");

  return TRUE;
}

/* transform size */
static gboolean
gst_adaspump_transform_size (GstBaseTransform * trans, GstPadDirection direction,
    GstCaps * caps, gsize size, GstCaps * othercaps, gsize * othersize)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "transform_size");

  return TRUE;
}

static gboolean
gst_adaspump_get_unit_size (GstBaseTransform * trans, GstCaps * caps,
    gsize * size)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "get_unit_size");

  return TRUE;
}

/* states */
static gboolean
gst_adaspump_start (GstBaseTransform * trans)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "start");

  return TRUE;
}

static gboolean
gst_adaspump_stop (GstBaseTransform * trans)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "stop");

  return TRUE;
}

/* sink and src pad event handlers */
static gboolean
gst_adaspump_sink_event (GstBaseTransform * trans, GstEvent * event)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "sink_event");

  return GST_BASE_TRANSFORM_CLASS (gst_adaspump_parent_class)->sink_event (
      trans, event);
}

static gboolean
gst_adaspump_src_event (GstBaseTransform * trans, GstEvent * event)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "src_event");

  return GST_BASE_TRANSFORM_CLASS (gst_adaspump_parent_class)->src_event (
      trans, event);
}

static GstFlowReturn
gst_adaspump_prepare_output_buffer (GstBaseTransform * trans, GstBuffer * input,
    GstBuffer ** outbuf)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "prepare_output_buffer");

  return GST_FLOW_OK;
}

/* metadata */
static gboolean
gst_adaspump_copy_metadata (GstBaseTransform * trans, GstBuffer * input,
    GstBuffer * outbuf)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "copy_metadata");

  return TRUE;
}

static gboolean
gst_adaspump_transform_meta (GstBaseTransform * trans, GstBuffer * outbuf,
    GstMeta * meta, GstBuffer * inbuf)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "transform_meta");

  return TRUE;
}

static void
gst_adaspump_before_transform (GstBaseTransform * trans, GstBuffer * buffer)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "before_transform");

}

/* transform */
static GstFlowReturn
gst_adaspump_transform (GstBaseTransform * trans, GstBuffer * inbuf,
    GstBuffer * outbuf)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "transform");

  g_print ("I'm plugged, tranform\n");

 // memcpy(adaspump->src, inbuf);
  return GST_FLOW_OK;
}

static GstFlowReturn
gst_adaspump_transform_ip (GstBaseTransform * trans, GstBuffer * buf)
{
  GstAdaspump *adaspump = GST_ADASPUMP (trans);

  GST_DEBUG_OBJECT (adaspump, "transform_ip");

  if (adaspump->process_count++ == 0)
	  g_print ("I'm plugged, 3000 th buf \n");

  //memset(buf,0x00,100);
  /* just push out the incoming buffer without touching it */
  //gst_pad_push (adaspump->src, buf);
  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "adaspump", GST_RANK_NONE,
      GST_TYPE_ADASPUMP);
}

/* FIXME: these are normally defined by the GStreamer build system.
   If you are creating an element to be included in gst-plugins-*,
   remove these, as they're always defined.  Otherwise, edit as
   appropriate for your external plugin package. */
#ifndef VERSION
#define VERSION "0.1.FIXME"
#endif
#ifndef PACKAGE
#define PACKAGE "FIXME_package"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "FIXME_package_name"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN "http://FIXME.org/"
#endif

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    adaspump,
    "FIXME plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)

