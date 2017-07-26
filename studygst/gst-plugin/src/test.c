/* GStreamer
 * Copyright (C) 2017 FIXME <fixme@example.com>
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
 * SECTION:element-gstvideofilter
 *
 * The videofilter element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! videofilter ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>
#include <string.h>

GST_DEBUG_CATEGORY_STATIC (gst_videofilter_debug_category);
#define GST_CAT_DEFAULT gst_videofilter_debug_category


typedef struct _GstVideoFilterTemplate GstVideoFilterTemplate;
typedef struct _GstVideoFilterTemplateClass GstVideoFilterTemplateClass;

/* These are boilerplate cast macros and type check macros */
#define GST_TYPE_VIDEO_FILTER_TEMPLATE   (gst_video_filter_template_get_type())
#define GST_VIDEO_FILTER_TEMPALTE(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_VIDEO_FILTER_TEMPLATE,GstVideoFilterTemplate))
#define GST_VIDEO_FILTER_TEMPALTE_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_VIDEO_FILTER_TEMPLATE,GstVideoFilterTemplateClass))
#define GST_IS_VIDEO_FILTER_TEMPLATE(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_VIDEO_FILTER_TEMPLATE))
#define GST_IS_VIDEO_FILTER_TEMPLATE_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_VIDEO_FILTER_TEMPLATE))

struct _GstVideoFilterTemplate
{
  GstVideoFilter videofilter;

  GstBuffer *previous_buffer;
  GstVideoInfo oldinfo;

  int threshold;
  int t;

};

struct _GstVideoFilterTemplateClass
{
  GstVideoFilterClass videofilter_class;
};

//GType gst_video_filter_template_get_type (void);


/* prototypes */

G_DEFINE_TYPE (GstVideoFilterTemplate, gst_video_filter_template,
    GST_TYPE_VIDEO_FILTER);

static void gst_videofilter_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_videofilter_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);
static void gst_videofilter_dispose (GObject * object);
static void gst_videofilter_finalize (GObject * object);

static gboolean gst_videofilter_start (GstBaseTransform * trans);
static gboolean gst_videofilter_stop (GstBaseTransform * trans);
static gboolean gst_videofilter_set_info (GstVideoFilter * filter, GstCaps * incaps,
    GstVideoInfo * in_info, GstCaps * outcaps, GstVideoInfo * out_info);
static GstFlowReturn gst_videofilter_transform_frame (GstVideoFilter * filter,
    GstVideoFrame * inframe, GstVideoFrame * outframe);
static GstFlowReturn gst_videofilter_transform_frame_ip (GstVideoFilter * filter,
    GstVideoFrame * frame);

enum
{
  PROP_0
};

/* pad templates */

/* FIXME: add/remove formats you can handle */
#define VIDEO_SRC_CAPS \
    GST_VIDEO_CAPS_MAKE("{ I420, Y444, Y42B, UYVY, RGBA , YUY2 }")

/* FIXME: add/remove formats you can handle */
#define VIDEO_SINK_CAPS \
    GST_VIDEO_CAPS_MAKE("{ I420, Y444, Y42B, UYVY, RGBA , YUY2 }")


/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstVideoFilterTemplate, gst_videofilter, GST_TYPE_VIDEO_FILTER,
  GST_DEBUG_CATEGORY_INIT (gst_videofilter_debug_category, "videofilter", 0,
  "debug category for videofilter element"));

static void
gst_videofilter_class_init (GstVideoFilterTemplateClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseTransformClass *base_transform_class = GST_BASE_TRANSFORM_CLASS (klass);
  GstVideoFilterClass *video_filter_class = GST_VIDEO_FILTER_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS(klass),
      gst_pad_template_new ("src", GST_PAD_SRC, GST_PAD_ALWAYS,
        gst_caps_from_string (VIDEO_SRC_CAPS)));
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS(klass),
      gst_pad_template_new ("sink", GST_PAD_SINK, GST_PAD_ALWAYS,
        gst_caps_from_string (VIDEO_SINK_CAPS)));

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS(klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "FIXME <jhlim@plk.co.kr>");

  gobject_class->set_property = gst_videofilter_set_property;
  gobject_class->get_property = gst_videofilter_get_property;
  gobject_class->dispose = gst_videofilter_dispose;
  gobject_class->finalize = gst_videofilter_finalize;
  base_transform_class->start = GST_DEBUG_FUNCPTR (gst_videofilter_start);
  base_transform_class->stop = GST_DEBUG_FUNCPTR (gst_videofilter_stop);
  video_filter_class->set_info = GST_DEBUG_FUNCPTR (gst_videofilter_set_info);
//  video_filter_class->transform_frame = GST_DEBUG_FUNCPTR (gst_videofilter_transform_frame);
  video_filter_class->transform_frame_ip = GST_DEBUG_FUNCPTR (gst_videofilter_transform_frame_ip);

}

static void
gst_videofilter_init (GstVideoFilterTemplate *videofilter)
{
    videofilter->threshold = 10;
}

void
gst_videofilter_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (object);

  GST_DEBUG_OBJECT (videofilter, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_videofilter_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (object);

  GST_DEBUG_OBJECT (videofilter, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_videofilter_dispose (GObject * object)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (object);

  GST_DEBUG_OBJECT (videofilter, "dispose");

  /* clean up as possible.  may be called multiple times */

  G_OBJECT_CLASS (gst_videofilter_parent_class)->dispose (object);
}

void
gst_videofilter_finalize (GObject * object)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (object);

  GST_DEBUG_OBJECT (videofilter, "finalize");

  /* clean up object here */

  G_OBJECT_CLASS (gst_videofilter_parent_class)->finalize (object);
}

static gboolean
gst_videofilter_start (GstBaseTransform * trans)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (trans);

  GST_DEBUG_OBJECT (videofilter, "start");

  return TRUE;
}

static gboolean
gst_videofilter_stop (GstBaseTransform * trans)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (trans);

  GST_DEBUG_OBJECT (videofilter, "stop");

  return TRUE;
}

static gboolean
gst_videofilter_set_info (GstVideoFilter * filter, GstCaps * incaps,
    GstVideoInfo * in_info, GstCaps * outcaps, GstVideoInfo * out_info)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (filter);

  GST_DEBUG_OBJECT (videofilter, "set_info");

  return TRUE;
}

/* transform */
static GstFlowReturn
gst_videofilter_transform_frame (GstVideoFilter * filter, GstVideoFrame * inframe,
    GstVideoFrame * outframe)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (filter);

  GST_DEBUG_OBJECT (videofilter, "transform_frame");

  return GST_FLOW_OK;
}
int VANISH_POINT=180;

void PrewittEdgeDetection(unsigned char *Img_Raw, unsigned char *Img_Sobel, int threshold)
{
        int k, j;
        int     centerValue1=0, centerValue2=0;
        int     sum=0;
        int W=320, H=240;
        int ImageSize = W*H;

        for (k=239-VANISH_POINT; k<238; k++)
        {
                for (j=0; j<W; j++)
                {
                        centerValue1 += (-1*Img_Raw[W*k + j] +          1*Img_Raw[W*k + (j+2)]) +
                                                        (-1*Img_Raw[W*(k+1) + j] +      1*Img_Raw[W*(k+1) + (j+2)]) +
                                                        (-1*Img_Raw[W*(k+2) + j] +      1*Img_Raw[W*(k+2) + (j+2)]);

                        centerValue2 += ( 1*Img_Raw[W*k + j] +          1*Img_Raw[W*k + (j+1)] +                1*Img_Raw[W*k + (j+2)]) +
                                                        (-1*Img_Raw[W*(k+2) + j] -      1*Img_Raw[W*(k+2) + (j+1)] -    Img_Raw[W*(k+2) + (j+2)]);

                        sum = abs(centerValue1) + abs(centerValue2);

                        if (sum>255)    sum = 255;
                        if (sum < threshold)    sum = 0;
                        Img_Sobel[W*(k+1)+(j+1)] = (unsigned char)sum;
                        centerValue1 = 0;
                        centerValue2 = 0;
                        sum = 0;
                }
        }
}

///////////////////////////////////////////////////////////////////////////////////////
//  Function Name : AveragingSmoothing
//  Abstract : ������ ���ſ��� ��
//  Arguments : Img_Raw �Է�Y���� (320x240), Img_Out ���������ſ��� (320x240)
///////////////////////////////////////////////////////////////////////////////////////
void AveragingSmoothing (unsigned char *Img_Raw, unsigned char *Img_Out)
{
	int k, j;
	int	centerValue1=0;
	int	sum=0;
	int left_val, right_val, center_val;
	int prevprev_right_val, prev_right_val;

	for (k=239-VANISH_POINT; k<238; k++)
	{
		for (j=2; j<318; j++)
		{
			left_val  = Img_Raw[320*(k-1) + (j-0)] + Img_Raw[320*(k+1) + (j-0)];
			center_val = 2*Img_Raw[320*k + j];
			right_val = Img_Raw[320*(k-0) + (j-1)] + Img_Raw[320*(k+0) + (j+1)];
			sum = (left_val + center_val + right_val)/6;

			if (sum>255)	sum = 255;
			Img_Out[320*k+j] = (unsigned char)sum;
		}
	}
}

static GstFlowReturn
gst_videofilter_diff_transform_frame_ip_planarY (GstVideoFilterTemplate * videodiff,
    GstVideoFrame * outframe, GstVideoFrame * inframe, GstVideoFrame * oldframe)
{
  int width = inframe->info.width;
  int height = inframe->info.height;
  int i, j;
  int threshold = videodiff->threshold;
  int t = videodiff->t;

  for (j = 0; j < height; j++) {
    guint8 *d = (guint8 *) outframe->data[0] + outframe->info.stride[0] * j;
    guint8 *s1 = (guint8 *) oldframe->data[0] + oldframe->info.stride[0] * j;
    guint8 *s2 = (guint8 *) inframe->data[0] + inframe->info.stride[0] * j;
    for (i = 0; i < width; i++) {
      if ((s2[i] < s1[i] - threshold) || (s2[i] > s1[i] + threshold)) {
        if ((i + j + t) & 0x4) {
          d[i] = 16;
        } else {
          d[i] = 240;
        }
      } else {
        d[i] = s2[i];
      }
    }
  }
  for (j = 0; j < GST_VIDEO_FRAME_COMP_HEIGHT (inframe, 1); j++) {
    guint8 *d = (guint8 *) outframe->data[1] + outframe->info.stride[1] * j;
    guint8 *s = (guint8 *) inframe->data[1] + inframe->info.stride[1] * j;
    memcpy (d, s, GST_VIDEO_FRAME_COMP_WIDTH (inframe, 1));
  }
  for (j = 0; j < GST_VIDEO_FRAME_COMP_HEIGHT (inframe, 2); j++) {
    guint8 *d = (guint8 *) outframe->data[2] + outframe->info.stride[2] * j;
    guint8 *s = (guint8 *) inframe->data[2] + inframe->info.stride[2] * j;
    memcpy (d, s, GST_VIDEO_FRAME_COMP_WIDTH (inframe, 2));
  }
  return GST_FLOW_OK;
}

static GstFlowReturn
gst_videofilter_transform_frame_ip (GstVideoFilter * filter, GstVideoFrame * frame)
{
  GstVideoFilterTemplate *videofilter = GST_VIDEO_FILTER_TEMPALTE (filter);

  GST_DEBUG_OBJECT (videofilter, "transform_frame_ip");

  int i= gst_buffer_n_memory(frame->buffer);
  GstMapInfo info={0,};
  GstMapFlags flags=GST_MAP_WRITE;

  for(int j=0; j<i; j++)
  {
	  GstMemory * tmpMemory = gst_buffer_peek_memory(frame->buffer, j);
	  if (gst_memory_map(tmpMemory, &info, flags ))
	  {
		  char * sobelbuffer = malloc(info.size);
		  //
		  //AveragingSmoothing(info.data , sobelbuffer);
		  PrewittEdgeDetection(info.data , sobelbuffer, 10);

		  memcpy(info.data, sobelbuffer, info.size);
		  free(sobelbuffer);
		  gst_memory_unmap(tmpMemory, &info);
	  }
  }

  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "videofilter", GST_RANK_NONE,
      GST_TYPE_VIDEO_FILTER_TEMPLATE);
}

/* FIXME: these are normally defined by the GStreamer build system.
   If you are creating an element to be included in gst-plugins-*,
   remove these, as they're always defined.  Otherwise, edit as
   appropriate for your external plugin package. */
#ifndef VERSION
#define VERSION "0.0.FIXME"
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
    videofiltertemplateplugin,
    "Video filter template plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN
);

