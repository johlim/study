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
    char        m_filename[256];
    GMainLoop   *m_loop;
    GstElement 	*m_pipeline;
    GstBus 		*m_bus;
    GstElement 	*m_bin;

    GstElement 	*m_vsource, *m_vidconvert, *m_filter, *m_parser, *m_colcon,
                *m_tee, *m_queue_disp, *m_queue_save, *m_queue_aud1, *m_queue_aud2, *m_scale,
                *m_imagesink, *m_video_enc, *m_mux, *m_queue_mux, *m_file,
                *m_asource, *m_audconvert, *m_audio_enc;
            
    GstCaps 	*m_scale_caps, *m_video_in_caps,  *m_audio_in_caps, *m_audio_out_caps;
    gboolean     (*m_buscb)(GstBus *bus, GstMessage *msg, gpointer data);
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
