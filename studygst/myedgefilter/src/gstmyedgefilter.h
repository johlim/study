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
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_MYEDGEFILTER_H_
#define _GST_MYEDGEFILTER_H_

#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>

G_BEGIN_DECLS

#define GST_TYPE_MYEDGEFILTER   (gst_myedgefilter_get_type())
#define GST_MYEDGEFILTER(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_MYEDGEFILTER,GstMyedgefilter))
#define GST_MYEDGEFILTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_MYEDGEFILTER,GstMyedgefilterClass))
#define GST_IS_MYEDGEFILTER(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_MYEDGEFILTER))
#define GST_IS_MYEDGEFILTER_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_MYEDGEFILTER))

typedef struct _GstMyedgefilter GstMyedgefilter;
typedef struct _GstMyedgefilterClass GstMyedgefilterClass;

struct _GstMyedgefilter
{
  GstVideoFilter base_myedgefilter;

};

struct _GstMyedgefilterClass
{
  GstVideoFilterClass base_myedgefilter_class;
};

GType gst_myedgefilter_get_type (void);

G_END_DECLS

#endif
