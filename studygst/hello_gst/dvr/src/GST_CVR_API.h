#ifndef __GST_CVR_API_H__
#define __GST_CVR_API_H__

#include "GST_COMMON.h"

/* 
=================================================================================================================
 Struct Definition.
================================================================================================================= 
*/
typedef struct GST_CVR_Struct
{
    GstBus 		*m_bus;
    GMainLoop   *m_loop;
    GstElement 	*m_bin;
    GstElement 	*m_pipeline;
    GstElement  *video_filter_bin;
    GstElement *video_balance;
    GstElement *camera_tee, *effects_tee;
    GstElement *main_valve, *effects_valve;
    gchar *current_effect_desc;

    GstElement *effects_preview_bin;
    GstElement *effect_filter, *effects_capsfilter;

    GstElement 	*m_vsource, *m_vidconvert, *m_filter, *m_parser, *m_colcon,
                *m_tee, *m_queue_disp, *m_queue_save, *m_queue_aud1, *m_queue_aud2, *m_scale,
                *m_imagesink, *m_video_enc, *m_mux, *m_queue_mux, *m_file,
                *m_asource, *m_audconvert, *m_audio_enc;

    GstElement  *video_file_sink; 

    GstCaps 	*m_scale_caps, *m_video_in_caps,  *m_audio_in_caps, *m_audio_out_caps;
    gboolean     (*m_buscb)(GstBus *bus, GstMessage *msg, gpointer data);
    gboolean    is_recording;
    gboolean    pipeline_is_playing;
    gboolean    effect_pipeline_is_playing;
    char        m_filename[256];
		///
		GstElement *catchPipeline;
    GstElement *binRec1;
    GstElement *binRec2;
    GstElement *queue_1;
    GstElement *queue_2;
    GstElement *identity1;
    GstElement *identity2;
    GstElement *file_sink1;
    GstElement *file_sink2;
    GstElement *ph264_1;
    GstElement *ph264_2;
    GstElement *mp4mux1;
    GstElement *mp4mux2;
    GstElement *fakesrc;
    GstElement *fakesink;
    GstElement *queue_catch;
    GstElement *mainFakesink;

		char        byteHeader[57];
    guint       filecount;
}
GST_CVR_Struct;

typedef void *GST_CVR_Handle;
GST_CVR_Handle hGST_CVR;


/* 
=================================================================================================================
 Function Lists.
================================================================================================================= 
*/

#ifdef __cplusplus
extern "C" {
#endif

// GStreamer CVR Main
void GST_CVR_Main(gpointer data);


// Create Destroy
GST_CVR_Struct* GST_CVR_Create(void);
void GST_CVR_Destroy(GST_CVR_Handle hHandle);


// Set Parameter
void GST_CVR_SetMP4Param(GST_CVR_Handle hHandle);
void GST_CVR_SetH264Param(GST_CVR_Handle hHandle);
void GST_CVR_SetJPEGParam(GST_CVR_Handle hHandle);
void GST_CVR_SetAODParam(GST_CVR_Handle hHandle);
void GST_CVR_SetDisplayRegion(GST_CVR_Handle hHandle, int top, int bottom, int left, int right);


// Preview Control
void GST_CVR_PreviewStart(GST_CVR_Handle hHandle);
void GST_CVR_PreviewStop(GST_CVR_Handle hHandle);


// Control
void GST_CVR_AODRecord(GST_CVR_Handle hHandle);
void GST_CVR_Record(GST_CVR_Handle hHandle);
void GST_CVR_Stop(GST_CVR_Handle hHandle);
void GST_CVR_Pause(GST_CVR_Handle hHandle);
void GST_CVR_Resume(GST_CVR_Handle hHandle);
void GST_CVR_Capture(GST_CVR_Handle hHandle);
#ifdef __cplusplus
}
#endif
















#endif // __GST_CVR_API_H__
