#include "GST_CVR_API.h"



/*
=================================================================================================================
Function Name: GST_CVR_Main
Description:
=================================================================================================================
*/
void GST_CVR_Main(gpointer data)
{
    GST_CVR_Struct* hCamcorder = 0;
    char cCommand[3];
    int iIndex = 0;
    int bExit = 0;

    while(!bExit)
    {
        fprintf(stderr, "=============================================\n");
        fprintf(stderr, "  01> GST CVR Create \n");
        fprintf(stderr, "  02> GST CVR Destroy \n");
        fprintf(stderr, "  03> GST CVR Preview Start \n");
        fprintf(stderr, "  04> GST CVR Preview Stop\n");
        fprintf(stderr, "  05> GST CVR Set MPEG4Param \n");
        fprintf(stderr, "  06> GST CVR Set H264Param \n");
        fprintf(stderr, "  07> GST_CVR Set JPEGParam \n");
        fprintf(stderr, "  08> GST_CVR Set AODParam \n");
        fprintf(stderr, "  09> GST CVR Record \n");
        fprintf(stderr, "  10> GST CVR Stop \n");
        fprintf(stderr, "  11> GST CVR Pause \n");
        fprintf(stderr, "  12> GST CVR Resume \n");
        fprintf(stderr, "  13> GST CVR Capture \n");
        fprintf(stderr, "  14> GST CVR Debug \n");
        fprintf(stderr, " X,x> GST CVR Exit \n");
        fprintf(stderr, " INPUT : ");

        scanf("%s", cCommand);
        iIndex = atoi(cCommand);
        if(cCommand[0] == 'x' || cCommand[0] == 'X')
            bExit = 1;
        else
            fprintf(stderr, " [%d] =========================================\n", iIndex);


        switch(iIndex)
        {
            case 1:
                hGST_CVR = GST_CVR_Create();
                hCamcorder = (GST_CVR_Struct*)hGST_CVR;
                hCamcorder->m_loop = (GMainLoop*)data;
                break;

            case 2:
                GST_CVR_Destroy(hGST_CVR);
                break;

            case 3:
                GST_CVR_PreviewStart(hGST_CVR);
                break;

            case 4:
                GST_CVR_PreviewStop(hGST_CVR);
                break;

            case 5:
                GST_CVR_SetMP4Param(hGST_CVR);
                break;

            case 6:
                GST_CVR_SetH264Param(hGST_CVR);
                break;

            case 7:
                GST_CVR_SetJPEGParam(hGST_CVR);
                break;

            case 8:
                GST_CVR_SetAODParam(hGST_CVR);
                break;

            case 9:
                GST_CVR_Record(hGST_CVR);
                break;

            case 10:
                GST_CVR_Stop(hGST_CVR);
                break;

            case 11:
                GST_CVR_Pause(hGST_CVR);
                break;

            case 12:
                GST_CVR_Resume(hGST_CVR);
                break;

            case 13:
                GST_CVR_Capture(hGST_CVR);
                break;

            case 14:
                hCamcorder = (GST_CVR_Struct*)hGST_CVR;
                GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(hCamcorder->m_pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "GST_CVR");
                break;

            default:
                break;
        }
    }

}

/*
=================================================================================================================
Function Name: GST_CVR_BusCallBack
Description:
=================================================================================================================
*/
static gboolean GST_CVR_CallBack (GstBus *bus, GstMessage *msg, gpointer data)
{
    GST_CVR_Struct * pPointer;
    pPointer = (GST_CVR_Struct*)data;

    fprintf(stderr, "\n");
    switch (GST_MESSAGE_TYPE (msg))
    {
        case GST_MESSAGE_EOS:
        {
            fprintf(stderr, "[GST_CVR:EOS]	End-of-stream\n");
            fprintf(stderr, "[GST_CVR:EOS]	End-of-stream\n");
            fprintf(stderr, "[GST_CVR:EOS]	End-of-stream\n");
            fprintf(stderr, "[GST_CVR:EOS]	End-of-stream\n");
            break;
        }
        case GST_MESSAGE_ERROR:
        {
            gchar *debug;
            GError *err;
            gst_message_parse_error (msg, &err, &debug);
            fprintf(stderr, "[GST_CVR:ERR]	Error : %s\n", err->message);
            g_free (debug);
            g_error_free (err);
            break;
        }
        case GST_MESSAGE_SEGMENT_START:
        {
            fprintf(stderr, "[GST_CVR:SGS]	GST_MESSAGE_SEGMENT_START");
            break;
        }

        default:
	    {
            fprintf(stderr, "[CVR_BUS_CB:DEF]	Some Message : %s\n", GST_MESSAGE_TYPE_NAME(msg));
            break;
        }
    }
    return TRUE;
}

/*
=================================================================================================================
Function Name: GST_CVR_Create
Description:
=================================================================================================================
*/
GST_CVR_Struct* GST_CVR_Create(void)
{
    GST_CVR_Struct* pRecorder;
    const gchar *nano_str;
    guint major, minor, micro, nano;
    fprintf(stderr, "[GST_CVR]  Create  ++\n");
    pRecorder = (GST_CVR_Struct*)g_malloc(sizeof(GST_CVR_Struct));
    memset(pRecorder, 0x00, sizeof(GST_CVR_Struct));

    if (!pRecorder)
    {
        GST_DEBUG("### [GST_CVR] Create Recorder Handle Failed. Not enough memory\n");
        return NULL;
    }

    // Pipeline' Creation
    pRecorder->m_pipeline = gst_pipeline_new("pipeline");

    // Get Bus
    pRecorder->m_bus = gst_element_get_bus(pRecorder->m_pipeline);
    if (!pRecorder->m_bus) GST_DEBUG("### [GST_CVR] get_element_get_bus fails\n");
    pRecorder->m_buscb = GST_CVR_CallBack;

    // Make Main Binary
    pRecorder->m_bin = gst_bin_new ("src_bin");
    gst_bin_add(GST_BIN(pRecorder->m_pipeline), pRecorder->m_bin);


    g_set_prgname("GST_CVR");
    gst_version(&major, &minor, &micro, &nano);

    if (nano == 1)
        nano_str = "(CVS)";
    else if (nano == 2)
        nano_str = "(Prerelease)";
    else
        nano_str = "";

    GST_DEBUG("This program is linked against GStreamer %d.%d.%d %s\n", major, minor, micro, nano_str);

    fprintf(stderr, "[GST_CVR]  Create  --\n");
    return pRecorder;
}


/*
=================================================================================================================
Function Name: GST_CVR_Destroy
Description:
=================================================================================================================
*/
void GST_CVR_Destroy(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;
    fprintf(stderr, "[GST_CVR]  Destroy ++\n");

    gst_element_set_state (hCamcorder->m_pipeline, GST_STATE_NULL);

    /* Free the allocated memory for this listening when it isn'[CVR] used anymore */
    g_print ("[GST_CVR]  Deleting Bus\n");
    gst_object_unref(hCamcorder->m_bus);

    /* Delete the pipeline */
    fprintf(stderr, "[GST_CVR]  Deleting Pipeline\n");
    gst_object_unref (GST_OBJECT (hCamcorder->m_pipeline));

    if (hCamcorder)
    {
        g_free(hCamcorder);
        hCamcorder = NULL;
    }


    fprintf(stderr, "[GST_CVR]  Destroy --\n");

}




/*
=================================================================================================================
Function Name: GST_CVR_SetMP4Param
Description:
=================================================================================================================
*/
void GST_CVR_SetMP4Param(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    fprintf(stderr, "[GST_CVR]  SetMP4Param ++ \n");


	hCamcorder->m_vidconvert = gst_element_factory_make ("videoconvert", "videoconvert");
	if(!hCamcorder->m_vidconvert) fprintf(stderr, "### m_vidconvert create error\n");

    hCamcorder->m_vsource = gst_element_factory_make ("v4l2src", "v4l2src");
    if (!hCamcorder->m_vsource) fprintf(stderr, "### v412src create error\n");
    hCamcorder->m_tee = gst_element_factory_make ("tee", "t1");
    if (!hCamcorder->m_tee) fprintf(stderr, "### tee create error\n");

    hCamcorder->m_video_in_caps = gst_caps_new_simple("video/x-raw",
//                                    "format", G_TYPE_STRING, "YUY2",
                                    "width", G_TYPE_INT, 320,
                                    "height", G_TYPE_INT, 240,
                                    NULL);

    hCamcorder->m_asource = gst_element_factory_make("alsasrc", "alsasrc");
    if(!hCamcorder->m_asource) fprintf(stderr, "### arlsasrc create error\n");

    hCamcorder->m_audio_in_caps = gst_caps_new_simple("audio/x-raw",
                                    "depth", G_TYPE_INT, 16,
                                    "rate", G_TYPE_INT, 8000,
                                    "channels", G_TYPE_INT, 1,
                                    "width", G_TYPE_INT, 16,
                                    NULL);

    hCamcorder->m_queue_disp = gst_element_factory_make("queue", "queue_disp");
    hCamcorder->m_queue_save = gst_element_factory_make("queue", "queue_save");
    hCamcorder->m_queue_aud1 = gst_element_factory_make("queue", "queue_aud1");
    hCamcorder->m_queue_aud2 = gst_element_factory_make("queue", "queue_adu2");
    hCamcorder->m_queue_mux = gst_element_factory_make("queue", "queue_mux");

    hCamcorder->m_imagesink = gst_element_factory_make("ximagesink", "sink");
    if(!hCamcorder->m_imagesink) fprintf(stderr, "### ximagesink create error\n");

    hCamcorder->m_video_enc = gst_element_factory_make ("avenc_mpeg4", "avenc_mpeg4");
    if (!hCamcorder->m_video_enc) fprintf(stderr, "### avenc_mpeg4 create error\n");

    hCamcorder->m_audio_enc = gst_element_factory_make ("avenc_aac", "avenc_aac");
    if(!hCamcorder->m_audio_enc) fprintf(stderr, "### avenc_aac create error\n");
    g_object_set(hCamcorder->m_audio_enc, "bitrate", 8000, NULL);

    hCamcorder->m_audconvert = gst_element_factory_make("audioconvert", "audioconvert");

    hCamcorder->m_mux = gst_element_factory_make ("avmux_mp4", "avmux_mp4");
    if (!hCamcorder->m_mux) fprintf(stderr, "### avmux_mp4 create error\n");

    hCamcorder->m_file = gst_element_factory_make ("filesink", "filesink");
    if (!hCamcorder->m_file) fprintf(stderr, "### filesink create error\n");
    g_object_set(G_OBJECT(hCamcorder->m_file), "location", "GST_MPEG4_avmux_mp4.3gp", NULL);
    strcpy(hCamcorder->m_filename, "GST_MPEG4_avmux_mp4.3gp");

    fprintf(stderr, "[GST_CVR]  SetMP4Param -- \n");

}


/*
=================================================================================================================
Function Name: GST_CVR_SetH264Param
Description:
=================================================================================================================
*/
void GST_CVR_SetH264Param(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    fprintf(stderr, "[GST_CVR]  SetH264Param ++ \n");

    hCamcorder->m_vsource = gst_element_factory_make ("v4l2src", "v4l2src");
    if (!hCamcorder->m_vsource) fprintf(stderr, "### v412src create error\n");
    hCamcorder->m_tee = gst_element_factory_make ("tee", "t1");
    if (!hCamcorder->m_tee) fprintf(stderr, "### tee create error\n");

    hCamcorder->m_video_in_caps = gst_caps_new_simple("video/x-raw",
                                    "format", G_TYPE_STRING, "I420",
                                    "width", G_TYPE_INT, 1280,
                                    "height", G_TYPE_INT, 720,
                                    NULL);

    hCamcorder->m_asource = gst_element_factory_make("alsasrc", "alsasrc");
    if(!hCamcorder->m_asource) fprintf(stderr, "### arlsasrc create error\n");

    hCamcorder->m_audio_in_caps = gst_caps_new_simple("audio/x-raw-int",
                                    "depth", G_TYPE_INT, 16,
                                    "rate", G_TYPE_INT, 8000,
                                    "channels", G_TYPE_INT, 1,
                                    "width", G_TYPE_INT, 16,
                                    NULL);


    hCamcorder->m_queue_disp = gst_element_factory_make("queue", "queue_disp");
    hCamcorder->m_queue_save = gst_element_factory_make("queue", "queue_save");
    hCamcorder->m_queue_aud1 = gst_element_factory_make("queue", "queue_aud1");
    hCamcorder->m_queue_aud2 = gst_element_factory_make("queue", "queue_adu2");
    hCamcorder->m_queue_mux = gst_element_factory_make("queue", "queue_mux");

    hCamcorder->m_imagesink = gst_element_factory_make("ximagesink", "sink");
    if(!hCamcorder->m_imagesink) fprintf(stderr, "### ximagesink create error\n");

    hCamcorder->m_video_enc = gst_element_factory_make ("x264enc", "x264enc");
    if (!hCamcorder->m_video_enc) fprintf(stderr, "### x264enc create error\n");

    hCamcorder->m_audio_enc = gst_element_factory_make ("avenc_aac", "avenc_aac");
    if(!hCamcorder->m_audio_enc) fprintf(stderr, "### avenc_aac create error\n");
    g_object_set(hCamcorder->m_audio_enc, "bitrate", 8000, NULL);

    hCamcorder->m_audconvert = gst_element_factory_make("audioconvert", "audioconvert");

    hCamcorder->m_mux = gst_element_factory_make ("avmux_mp4", "avmux_mp4");
    if (!hCamcorder->m_mux) fprintf(stderr, "### avmux_mp4 create error\n");

    hCamcorder->m_file = gst_element_factory_make ("filesink", "filesink");
    if (!hCamcorder->m_file) fprintf(stderr, "### filesink create error\n");
    g_object_set(G_OBJECT(hCamcorder->m_file), "location", "GST_H264_avmux_mp4.3gp", NULL);
    strcpy(hCamcorder->m_filename, "GST_H264_avmux_mp4.3gp");

    fprintf(stderr, "[GST_CVR]  SetH264Param -- \n");
}


/*
=================================================================================================================
Function Name: GST_CVR_SetJPEGParam
Description:
=================================================================================================================
*/
void GST_CVR_SetJPEGParam(GST_CVR_Handle hHandle)
{

}




/*
=================================================================================================================
Function Name: GST_CVR_SetAODParam
Description:
=================================================================================================================
*/
void GST_CVR_SetAODParam(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    fprintf(stderr, "[GST_CVR]  SetAODParam ++ \n");

    hCamcorder->m_asource = gst_element_factory_make("alsasrc", "alsasrc");
    if(!hCamcorder->m_asource) fprintf(stderr, "### arlsasrc create error\n");

    hCamcorder->m_audio_in_caps = gst_caps_new_simple("audio/x-raw-int",
                                    "depth", G_TYPE_INT, 16,
                                    "rate", G_TYPE_INT, 8000,
                                    "channels", G_TYPE_INT, 1,
                                    "width", G_TYPE_INT, 16,
                                    NULL);

    hCamcorder->m_queue_aud1 = gst_element_factory_make("queue", "queue_aud1");
    hCamcorder->m_queue_aud2 = gst_element_factory_make("queue", "queue_adu2");

    hCamcorder->m_audio_enc = gst_element_factory_make ("avenc_aac", "avenc_aac");
    if(!hCamcorder->m_audio_enc) fprintf(stderr, "### avenc_aac create error\n");
    g_object_set(hCamcorder->m_audio_enc, "bitrate", 16000, NULL);

    hCamcorder->m_mux = gst_element_factory_make ("avmux_mp4", "avmux_mp4");
    if (!hCamcorder->m_mux) fprintf(stderr, "### avmux_mp4 create error\n");


    hCamcorder->m_file = gst_element_factory_make ("filesink", "filesink");
    if (!hCamcorder->m_file) fprintf(stderr, "### filesink create error\n");
    g_object_set(G_OBJECT(hCamcorder->m_file), "location", "FromMicToAAC_20101028_1.3gp", NULL);

    fprintf(stderr, "[GST_CVR]  SetAODParam -- \n");

}







/*
=================================================================================================================
Function Name: GST_CVR_PreviewStart
Description:
=================================================================================================================
*/
void GST_CVR_PreviewStart(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;
    GstCaps * caps;

    fprintf(stderr, "[GST_CVR]  PreviewStart ++\n");
    if (hCamcorder->m_pipeline==NULL)
    	hCamcorder->m_pipeline = gst_pipeline_new("pipeline");

    gst_bin_add_many(GST_BIN(hCamcorder->m_pipeline), hCamcorder->m_vsource,
    				hCamcorder->m_vidconvert,
                     hCamcorder->m_imagesink,
                     NULL);

    /* create cap */

#if 0
    if (gst_element_link_filtered (hCamcorder->m_vsource, hCamcorder->m_imagesink,caps) != TRUE) {
      g_printerr ("Elements could not be linked.\n");
      return -1;
    }
#else
    if ( gst_element_link_filtered(hCamcorder->m_vsource, hCamcorder->m_vidconvert, hCamcorder->m_video_in_caps) != TRUE)
    {
    	g_printerr("source, convert Element could not be linked.\n");
    }

    if (gst_element_link(hCamcorder->m_vidconvert, hCamcorder->m_imagesink) != TRUE)
    {
    	g_printerr("convert, sink Element could not be linked.\n");
	}
#endif

    gst_bus_add_watch(hCamcorder->m_bus, hCamcorder->m_buscb, hCamcorder);
    gst_element_set_state (hCamcorder->m_pipeline, GST_STATE_PLAYING);


    fprintf(stderr, "[GST_CVR]  PreviewStart --\n");

}


/*
=================================================================================================================
Function Name: GST_CVR_PreviewStop
Description:
=================================================================================================================
*/
void GST_CVR_PreviewStop(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    fprintf(stderr, "[GST_CVR]	PreviewStop ++\n");


    gst_element_set_state (hCamcorder->m_pipeline, GST_STATE_NULL);

    gst_element_unlink_many (hCamcorder->m_vsource,
    						hCamcorder->m_vidconvert,
                            hCamcorder->m_imagesink,
                            NULL);

    gst_object_unref(hCamcorder->m_pipeline);
    hCamcorder->m_pipeline=NULL;

    fprintf(stderr, "[GST_CVR]	PreviewStop --\n");
}


/*
=================================================================================================================
Function Name: GST_CVR_AODRecord
Description:
=================================================================================================================
*/
void GST_CVR_AODRecord(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    gst_bin_add_many(GST_BIN(hCamcorder->m_bin), hCamcorder->m_asource,
                     hCamcorder->m_queue_aud1, hCamcorder->m_queue_aud2,
                     hCamcorder->m_audio_enc, hCamcorder->m_mux, hCamcorder->m_file,
                     NULL);

    // insert video caps information
    gst_element_link_pads_filtered(hCamcorder->m_asource, "src", hCamcorder->m_audio_enc, "sink",
                                    hCamcorder->m_audio_in_caps);

    gst_element_link(hCamcorder->m_audio_enc, hCamcorder->m_queue_aud1);

    gst_element_link(hCamcorder->m_queue_aud1,  hCamcorder->m_mux);
    gst_element_link(hCamcorder->m_mux, hCamcorder->m_queue_aud2);
    gst_element_link(hCamcorder->m_queue_aud2, hCamcorder->m_file);

    /* Set the pipeline to "playing" state*/
    g_print ("[GST_CVR]  AODRecord ++ \n");
    gst_bus_add_watch(hCamcorder->m_bus, hCamcorder->m_buscb, hCamcorder);
    gst_element_set_state (hCamcorder->m_pipeline, GST_STATE_PLAYING);
    g_print ("[GST_CVR]  AODRecord -- \n");


}



/*
=================================================================================================================
Function Name: GST_CVR_Record
Description:
=================================================================================================================
*/
void GST_CVR_Record(GST_CVR_Handle hHandle)
{
    gboolean bRet;
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    gst_bin_add_many(GST_BIN(hCamcorder->m_bin), hCamcorder->m_vsource, hCamcorder->m_asource,
                     hCamcorder->m_tee,
                     //hCamcorder->m_queue_save,
                     //hCamcorder->m_queue_disp,
                     hCamcorder->m_queue_aud1,
                     //hCamcorder->m_queue_aud2,
                     hCamcorder->m_queue_mux,
                     hCamcorder->m_imagesink,
                     hCamcorder->m_video_enc, hCamcorder->m_mux, hCamcorder->m_file,
                     hCamcorder->m_audio_enc,
                     hCamcorder->m_audconvert, NULL);

    // insert video caps information
    gst_element_link_pads_filtered(hCamcorder->m_vsource, "src", hCamcorder->m_tee, "sink",
                                    hCamcorder->m_video_in_caps);

    gst_element_link(hCamcorder->m_tee, /* hCamcorder->m_queue_disp);
    gst_element_link(hCamcorder->m_queue_disp,*/ hCamcorder->m_imagesink);

    gst_element_link(hCamcorder->m_tee, /* hCamcorder->m_queue_save);
    gst_element_link(hCamcorder->m_queue_save,*/ hCamcorder->m_video_enc);
    gst_element_link(hCamcorder->m_video_enc, hCamcorder->m_mux);

    // insert audio caps information
    bRet = gst_element_link_pads_filtered(hCamcorder->m_asource, "src", hCamcorder->m_audconvert, "sink",
                                    hCamcorder->m_audio_in_caps);
    if(!bRet)
        g_print("[CVR]  audio source capability set error\n");\

    gst_element_link(hCamcorder->m_audconvert,  hCamcorder->m_audio_enc);
    gst_element_link(hCamcorder->m_audio_enc,   hCamcorder->m_queue_aud1);
    gst_element_link(hCamcorder->m_queue_aud1,  hCamcorder->m_mux);

    gst_element_link(hCamcorder->m_mux, hCamcorder->m_queue_mux);
    gst_element_link(hCamcorder->m_queue_mux, hCamcorder->m_file);

    /* Set the pipeline to "playing" state*/
    g_print ("[GST_CVR]  Record ++ \n");

    //[2010.11.29] Wired Problem. Within QT, gst_bus_add_watch function is not matched.
    gst_bus_add_watch(hCamcorder->m_bus, hCamcorder->m_buscb, hCamcorder);
    //gst_bus_set_sync_handler(   hCamcorder->m_bus,(GstBusSyncHandler)hCamcorder->m_buscb,(gpointer*)hCamcorder);
    gst_element_set_state (hCamcorder->m_pipeline, GST_STATE_PLAYING);
    g_print ("[GST_CVR]  Record -- \n");

}



/*
=================================================================================================================
Function Name: GST_CVR_Stop
Description:
=================================================================================================================
*/
void GST_CVR_Stop(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    fprintf(stderr, "[GST_CVR]	Stop ++\n");

    /* 泥섏쓬�쓽 source 媛� �릺�뒗 element�뿉�떎媛� end-of-stream event瑜� �궇�젮以��떎.  */
    if(hCamcorder->m_vsource)
        gst_element_send_event(hCamcorder->m_vsource, gst_event_new_eos());

    if(hCamcorder->m_asource)
        gst_element_send_event(hCamcorder->m_asource, gst_event_new_eos());

    /*
            泥섏쓬�쓽 mux�쓽 sink pad�뿉�떎媛� end-of-stream event瑜� �궇�젮以섎몢 �맂�떎.
            Mux�뿉�떎 �뜕�졇�몢 �븞�맂�떦.. �뀪�뀪.
       */
    //pad = gst_element_get_pad (hCamcorder->m_mux, "sink");
    //gst_element_add_pad (pad, gst_event_new_eos());

    /* BUS�뿉�떎 end-of-stream event瑜� 蹂대궡吏� �븡�룄濡� �븳�떎. */

    fprintf(stderr, "[GST_CVR]	Stop --\n");

}






/*
=================================================================================================================
Function Name: GST_CVR_Pause
Description:
=================================================================================================================
*/
void GST_CVR_Pause(GST_CVR_Handle hHandle)
{
    GstStateChangeReturn bRet;
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

	fprintf(stderr,"[GST_CVR]	Pause ++\n");

    bRet = gst_element_set_state (hCamcorder->m_pipeline, GST_STATE_PAUSED);
    if(bRet != GST_STATE_CHANGE_SUCCESS)
    	fprintf(stderr,"[GST_CVR]	Pause Error\n");


	fprintf(stderr,"[GST_CVR]	Pause --\n");

}




/*
=================================================================================================================
Function Name: GST_CVR_Resume
Description:
=================================================================================================================
*/
void GST_CVR_Resume(GST_CVR_Handle hHandle)
{
    GstStateChangeReturn bRet;
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

	fprintf(stderr,"[GST_CVR]	Resume ++\n");

    bRet = gst_element_set_state(hCamcorder->m_pipeline, GST_STATE_PLAYING);
    if(bRet != GST_STATE_CHANGE_SUCCESS)
        fprintf(stderr, "[GST_CVR]  Resume Error\n");

	fprintf(stderr,"[GST_CVR]	Resume --\n");

}




/*
=================================================================================================================
Function Name: GST_CVR_Capture
Description:
=================================================================================================================
*/
void GST_CVR_Capture(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct* hCamcorder = (GST_CVR_Struct*)hHandle;

    fprintf(stderr, "[GST_CVR]  Capture ++\n");

    if(hCamcorder)
    {

    }
    fprintf(stderr, "[GST_CVR]  Capture --\n");

}
typedef struct _CustomData {
    gboolean is_live;
    GstElement *pipeline;
    GMainLoop *loop;
} CustomData;

static void cb_message (GstBus *bus, GstMessage *msg, CustomData *data) {

    return;
}

int main(int argc, char *argv[]) {
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;
    GMainLoop *main_loop;
    CustomData data;
    /* Initialize GStreamer */
    gst_init (&argc, &argv);

    main_loop = g_main_loop_new (NULL, FALSE);
    data.loop = main_loop;

    GST_CVR_Main(main_loop);

//    g_main_loop_run (main_loop);

    /* Free resources */
    g_main_loop_unref (main_loop);
    return 0;
}

