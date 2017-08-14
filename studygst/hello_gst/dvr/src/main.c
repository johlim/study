#include "GST_CVR_API.h"

enum
{
    PROP_0,
    PROP_VIDEO_TEXTURE,
    PROP_DEVICE_NODE,
    PROP_FORMAT,
    PROP_NUM_CAMERA_DEVICES,
    PROP_LAST
};

enum
{
    PHOTO_SAVED,
    PHOTO_TAKEN,
    VIDEO_SAVED,
    STATE_FLAGS_CHANGED,
    LAST_SIGNAL
};

enum
{
    CAMERA_ERROR_ELEMENT_NOT_FOUND,
    CAMERA_ERROR_LAST
};
static guint camera_signals[LAST_SIGNAL];
static GParamSpec *properties[PROP_LAST];

#define CAMERA_ERROR camera_error_quark()
/*
=================================================================================================================
Function Name: GST_CVR_Main
Description:
=================================================================================================================
*/
void GST_CVR_Main(gpointer data)
{
    GST_CVR_Struct *hCamcorder = 0;
    char cCommand[3];
    int iIndex = 0;
    int bExit = 0;

    while (!bExit)
    {
        fprintf(stderr, "=============================================\n");
        fprintf(stderr, "  01> GST CVR Create \n");
        fprintf(stderr, "  02> GST CVR Destroy \n");

        fprintf(stderr, "  05> GST CVR Set MPEG4Param \n");

        fprintf(stderr, "  09> GST CVR Record \n");
        fprintf(stderr, "  10> GST CVR Stop \n");
        fprintf(stderr, "  11> GST CVR Switch \n");
        fprintf(stderr, "  14> GST CVR Debug \n");
        fprintf(stderr, " X,x> GST CVR Exit \n");
        fprintf(stderr, " INPUT : ");

        scanf("%s", cCommand);
        iIndex = atoi(cCommand);
        if (cCommand[0] == 'x' || cCommand[0] == 'X')
            bExit = 1;
        else
            fprintf(stderr, " [%d] =========================================\n", iIndex);

        switch (iIndex)
        {
        case 1:
            hGST_CVR = GST_CVR_Create();
            hCamcorder = (GST_CVR_Struct *)hGST_CVR;
            hCamcorder->m_loop = (GMainLoop *)data;
            break;

        case 2:
            GST_CVR_Destroy(hGST_CVR);
            break;



        case 5:
            GST_CVR_SetMP4Param(hGST_CVR);
            break;

        case 9:
            GST_CVR_Record(hGST_CVR);
            break;

        case 10:
            GST_CVR_Stop(hGST_CVR);
            break;

        case 11:
            GST_CVR_Switch(hGST_CVR);
            break;

        case 14:
            hCamcorder = (GST_CVR_Struct *)hGST_CVR;
            //GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(hCamcorder->video_filter_bin), GST_DEBUG_GRAPH_SHOW_ALL, "video_filter_bin");
            //GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(hCamcorder->effects_preview_bin), GST_DEBUG_GRAPH_SHOW_ALL, "effects_preview_bin");
            GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(hCamcorder->m_pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "m_pipeline");
            GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(hCamcorder->binRec1), GST_DEBUG_GRAPH_SHOW_ALL, "binRec1");
            GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(hCamcorder->binRec2), GST_DEBUG_GRAPH_SHOW_ALL, "binRec2");
            GST_DEBUG_BIN_TO_DOT_FILE(GST_BIN(hCamcorder->catchPipeline), GST_DEBUG_GRAPH_SHOW_ALL, "catchPipeline");

            break;

        default:
            break;
        }
    }
}

static GstPadProbeReturn 
checkForKeyFrames(GstPad * pad, GstPadProbeInfo *info, gpointer user_data)
{
    GstBuffer * buffer;


    buffer = GST_PAD_PROBE_INFO_BUFFER(info);
    buffer = gst_buffer_make_writable(buffer);

    if (buffer == NULL)
        return GST_PAD_PROBE_OK;

    if  (!GST_BUFFER_FLAG_IS_SET(buffer, GST_BUFFER_FLAG_DELTA_UNIT))
    {
        char * dummyheader[57];
        GstMapInfo map;
        GstMemory * mem = gst_allocator_alloc(NULL, 56, NULL);

        if ( gst_memory_map(mem, &map, GST_MAP_WRITE))
        {
            memcpy((gchar*)map.data, dummyheader, 56);
            gst_memory_unmap(mem,&map);
            gst_buffer_prepend_memory(buffer, mem);
            fprintf(stderr,"%s %d\n", __func__, __LINE__);
        }

        GST_PAD_PROBE_INFO_DATA(info) = buffer;

    } 
    return GST_PAD_PROBE_OK;
}
/*
=================================================================================================================
Function Name: GST_CVR_BusCallBack
Description:
=================================================================================================================
*/
static gboolean GST_CVR_CallBack(GstBus *bus, GstMessage *msg, gpointer data)
{
    GST_CVR_Struct *pPointer;
    pPointer = (GST_CVR_Struct *)data;

    fprintf(stderr, "\n");
    switch (GST_MESSAGE_TYPE(msg))
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
        gst_message_parse_error(msg, &err, &debug);
        fprintf(stderr, "[GST_CVR:ERR]	Error : %s\n", err->message);
        g_free(debug);
        g_error_free(err);
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
GQuark camera_error_quark(void);

GQuark
camera_error_quark(void)
{
    return g_quark_from_static_string("camera-error-quark");
}
static void
camera_set_error_element_not_found(GError **error, const gchar *factoryname)
{
    g_return_if_fail(error == NULL || *error == NULL);
}

static gboolean
camera_create_effects_preview_bin(GST_CVR_Handle hHandle, GError **error)
{
    GST_CVR_Struct *priv = hHandle;

    gboolean ok = TRUE;
    GstElement *scale;
    GstPad *pad;

    g_return_val_if_fail(error == NULL || *error == NULL, FALSE);

    priv->effects_preview_bin = gst_bin_new("effects_preview_bin");

    if ((priv->effects_valve = gst_element_factory_make("valve", "effects_valve")) == NULL)
    {
        camera_set_error_element_not_found(error, "effects_valve");
        return FALSE;
    }
    g_object_set(G_OBJECT(priv->effects_valve), "drop", TRUE, NULL);
    if ((scale = gst_element_factory_make("videoscale", "effects_scale")) == NULL)
    {
        camera_set_error_element_not_found(error, "videoscale");
        return FALSE;
    }
    if ((priv->effects_capsfilter = gst_element_factory_make("capsfilter", "effects_capsfilter")) == NULL)
    {
        camera_set_error_element_not_found(error, "capsfilter");
        return FALSE;
    }
    if ((priv->effects_tee = gst_element_factory_make("tee", "effects_tee")) == NULL)
    {
        camera_set_error_element_not_found(error, "tee");
        return FALSE;
    }

    gst_bin_add_many(GST_BIN(priv->effects_preview_bin), priv->effects_valve,
                     scale, priv->effects_capsfilter, priv->effects_tee, NULL);

    ok &= gst_element_link_many(priv->effects_valve, scale,
                                priv->effects_capsfilter, priv->effects_tee, NULL);

    /* add ghostpads */

    pad = gst_element_get_static_pad(priv->effects_valve, "sink");
    gst_element_add_pad(priv->effects_preview_bin, gst_ghost_pad_new("sink", pad));
    gst_object_unref(GST_OBJECT(pad));

    if (!ok)
        g_error("Unable to create effects preview bin");

    return TRUE;
}

static gboolean
camera_create_video_filter_bin(GST_CVR_Handle hHandle, GError **error)
{
    GST_CVR_Struct *priv = (GST_CVR_Struct *)hHandle;
    gboolean ok = TRUE;
    GstPad *pad;

    camera_create_effects_preview_bin(hHandle, error);

    priv->video_filter_bin = gst_bin_new("video_filter_bin");
    if ((priv->camera_tee = gst_element_factory_make("tee", "camera_tee")) == NULL)
    {
        camera_set_error_element_not_found(error, "tee");
        return FALSE;
    }
    if ((priv->main_valve = gst_element_factory_make("valve", "main_valve")) == NULL)
    {
        camera_set_error_element_not_found(error, "main_valve");
        return FALSE;
    }
    if ((priv->effect_filter = gst_element_factory_make("identity", "effect")) == NULL)
    {
        camera_set_error_element_not_found(error, "identity");
        return FALSE;
    }
    priv->current_effect_desc = g_strdup("identity");
    if ((priv->video_balance = gst_element_factory_make("videobalance", "video_balance")) == NULL)
    {
        camera_set_error_element_not_found(error, "videobalance");
        return FALSE;
    }

    gst_bin_add_many(GST_BIN(priv->video_filter_bin), priv->camera_tee,
                     priv->main_valve, priv->effect_filter,
                     priv->video_balance, priv->effects_preview_bin, NULL);

    ok &= gst_element_link_many(priv->camera_tee, priv->main_valve,
                                priv->effect_filter, priv->video_balance, NULL);

    gst_pad_link (gst_element_get_request_pad (priv->camera_tee, "src_%u"),
                gst_element_get_static_pad (priv->effects_preview_bin, "sink"));
    /* add ghostpads */

    pad = gst_element_get_static_pad(priv->video_balance, "src");
    gst_element_add_pad(priv->video_filter_bin, gst_ghost_pad_new("src", pad));
    gst_object_unref(GST_OBJECT(pad));

    pad = gst_element_get_static_pad(priv->camera_tee, "sink");
    gst_element_add_pad(priv->video_filter_bin, gst_ghost_pad_new("sink", pad));
    gst_object_unref(GST_OBJECT(pad));

    if (!ok)
        g_error("Unable to create filter bin");

    return TRUE;
}

/*
=================================================================================================================
Function Name: GST_CVR_Create
Description:
=================================================================================================================
*/
GST_CVR_Struct *GST_CVR_Create(void)
{
    GST_CVR_Struct *pRecorder;
    GError *tmp_error = NULL;
    const gchar *nano_str;
    guint major, minor, micro, nano;
    GstBus 		*bus;
    fprintf(stderr, "[GST_CVR]  Create  ++\n");
    pRecorder = (GST_CVR_Struct *)g_malloc(sizeof(GST_CVR_Struct));
    memset(pRecorder, 0x00, sizeof(GST_CVR_Struct));

    if (!pRecorder)
    {
        GST_DEBUG("### [GST_CVR] Create Recorder Handle Failed. Not enough memory\n");
        return NULL;
    }

    // Pipeline' Creation
    pRecorder->m_pipeline = gst_pipeline_new("pipeline");
    pRecorder->catchPipeline = gst_pipeline_new("catchPipeline");

    // Get Bus
    pRecorder->m_bus = gst_element_get_bus(pRecorder->m_pipeline);
    if (!pRecorder->m_bus)
        GST_DEBUG("### [GST_CVR] get_element_get_bus fails\n");
    bus = gst_element_get_bus (pRecorder->catchPipeline);
    

    pRecorder->m_buscb = GST_CVR_CallBack;

    gst_bus_add_signal_watch(pRecorder->m_bus);
    g_signal_connect(G_OBJECT(pRecorder->m_bus), "message",
                     G_CALLBACK(pRecorder->m_buscb), pRecorder);

    gst_bus_add_signal_watch(bus);
    g_signal_connect(G_OBJECT(bus), "message",
                     G_CALLBACK(pRecorder->m_buscb), pRecorder);

    // Make Rec1,2 Binary
    pRecorder->binRec1 = gst_bin_new("rec1 bin");
    pRecorder->binRec2 = gst_bin_new("rec2 bin");
    //  gst_bin_add(GST_BIN(pRecorder->m_pipeline), pRecorder->m_bin);

    // Makefile Filter bin / Effect bin
    camera_create_video_filter_bin(pRecorder, &tmp_error);

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
    GST_CVR_Struct *hCamcorder = (GST_CVR_Struct *)hHandle;
    fprintf(stderr, "[GST_CVR]  Destroy ++\n");

    gst_element_set_state(hCamcorder->m_pipeline, GST_STATE_NULL);

    /* Free the allocated memory for this listening when it isn'[CVR] used anymore */
    g_print("[GST_CVR]  Deleting Bus\n");
    gst_object_unref(hCamcorder->m_bus);

    /* Delete the pipeline */
    fprintf(stderr, "[GST_CVR]  Deleting Pipeline\n");
    gst_object_unref(GST_OBJECT(hCamcorder->m_pipeline));

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
    GST_CVR_Struct *hCamcorder = (GST_CVR_Struct *)hHandle;
    GST_CVR_Struct *this = (GST_CVR_Struct *)hHandle;

    fprintf(stderr, "[GST_CVR]  SetMP4Param ++ \n");

    hCamcorder->m_vidconvert = gst_element_factory_make("videoconvert", "videoconvert");
    if (!hCamcorder->m_vidconvert)
        fprintf(stderr, "### m_vidconvert create error\n");

    hCamcorder->m_vsource = gst_element_factory_make("v4l2src", "v4l2src");
    if (!hCamcorder->m_vsource)
        fprintf(stderr, "### v412src create error\n");
    hCamcorder->m_tee = gst_element_factory_make("tee", "t1");
    if (!hCamcorder->m_tee)
        fprintf(stderr, "### tee create error\n");
/*    
    hCamcorder->m_video_in_caps = gst_caps_new_simple("video/x-raw",
                                    "format", G_TYPE_STRING, "YUY2",
                                    "width", G_TYPE_INT, 320,
                                    "height", G_TYPE_INT, 240,
                                    NULL);
*/
/*
 gst-launch-1.0 alsasrc ! audioconvert ! audioresample ! audiorate 
 ! "audio/x-raw, rate=48000, channels=1" ! queue ! voaacenc ! queue ! filesink location="test.aac"
 */

    hCamcorder->m_asource = gst_element_factory_make("alsasrc", "alsasrc");
    if (!hCamcorder->m_asource)
        fprintf(stderr, "### arlsasrc create error\n");
    

    hCamcorder->m_queue_disp = gst_element_factory_make("queue", "queue_disp");
    hCamcorder->m_queue_save = gst_element_factory_make("queue", "queue_save");
    hCamcorder->m_queue_aud1 = gst_element_factory_make("queue", "queue_aud1");
    // hCamcorder->m_queue_aud2 = gst_element_factory_make("queue", "queue_adu2");

    hCamcorder->m_queue_mux = gst_element_factory_make("queue", "queue_mux");
    {
        GstPad * pad = gst_element_get_static_pad(hCamcorder->m_queue_save, "src");
        gst_pad_add_probe(pad, GST_PAD_PROBE_TYPE_BUFFER, (GstPadProbeCallback) checkForKeyFrames, NULL, NULL);
        gst_object_unref(pad);
    }
		
    hCamcorder->m_imagesink = gst_element_factory_make("ximagesink", "sink");
    ///////////////////////////////////////////////////////////////////////////
    //hCamcorder->m_imagesink = gst_element_factory_make("vaapisink", "sink");
    if (!hCamcorder->m_imagesink)
        fprintf(stderr, "### ximagesink create error\n");
    g_object_set(hCamcorder->m_imagesink, "async", FALSE, NULL);

    hCamcorder->m_video_enc = gst_element_factory_make("avenc_mpeg4", "avenc_mpeg4");
    if (!hCamcorder->m_video_enc)
        fprintf(stderr, "### avenc_mpeg4 create error\n");

    hCamcorder->m_audio_enc = gst_element_factory_make("voaacenc", "voaacenc");
    if (!hCamcorder->m_audio_enc)
        fprintf(stderr, "### voaacenc create error\n");
    g_object_set(hCamcorder->m_audio_enc, "bitrate", 8000, NULL);

    hCamcorder->m_audconvert = gst_element_factory_make("audioconvert", "audioconvert");

    hCamcorder->m_mux = gst_element_factory_make("avimux", "avimux");
    if (!hCamcorder->m_mux)
        fprintf(stderr, "### avimux create error\n");
#if 0
    hCamcorder->m_file = gst_element_factory_make("filesink", "filesink");
    if (!hCamcorder->m_file)
        fprintf(stderr, "### filesink create error\n");
    g_object_set(G_OBJECT(hCamcorder->m_file), "location", "avenc_mpeg4.mp4", NULL);
    strcpy(hCamcorder->m_filename, "avenc_mpeg4.mp4");
#endif
/////////////////////////////////////
    this->mp4mux1 = gst_element_factory_make ( "mp4mux", "mux_1");
    this->mp4mux2 = gst_element_factory_make( "mp4mux", "mux_2");
    this->ph264_1 = gst_element_factory_make ("h264parse", "ph264_1");
    this->ph264_2 = gst_element_factory_make( "h264parse", "ph264_2");
    this->identity1 = gst_element_factory_make("identity", "identity_1");
    this->identity2 = gst_element_factory_make( "identity", "identity_2");
    this->queue_1 = gst_element_factory_make( "queue", "queue_1");
    this->queue_2 = gst_element_factory_make( "queue", "queue_2");
    this->file_sink1 = gst_element_factory_make( "filesink", "file_sink1");
    this->file_sink2 = gst_element_factory_make( "filesink", "file_sink2");

    hCamcorder->fakesrc = gst_element_factory_make( "fakesrc", "fakesrc");
    hCamcorder->fakesink = gst_element_factory_make( "fakesink", "fakesink");
    hCamcorder->queue_catch = gst_element_factory_make( "queue", "queue_catch");
    hCamcorder->mainFakesink = gst_element_factory_make( "fakesink", "mainFakesink");

    sprintf(hCamcorder->m_filename, "inf%03.mp4",hCamcorder->filecount++);
    g_object_set(this->file_sink1, "sync", FALSE, "async", FALSE, "location", this->m_filename, NULL);
    sprintf(hCamcorder->m_filename, "inf%03.mp4",hCamcorder->filecount++);
    g_object_set(this->file_sink2, "sync", FALSE, "async", FALSE, "location", this->m_filename, NULL);

    fprintf(stderr, "[GST_CVR]  SetMP4Param -- \n");
}

/*
=================================================================================================================
Function Name: GST_CVR_Record
Description:
=================================================================================================================
*/
// gst-launch-1.0 v4l2src ! 'video/x-raw, format=(string)I420, width=(int)640, height=(int)480' 
//! x264enc ! avmux_mp4 ! filesink location=test.mp4 -e
// gst-launch-1.0 v4l2src ! 'video/x-raw, format=(string)I420, width=(int)640, height=(int)480' ! tee name=t1 ! x264enc ! avmux_mp4 ! filesink location=test.mp4 t1. ! videoconvert ! ximagesink ! "async=false"
//  gst-launch-1.0 alsasrc ! audioconvert ! audioresample ! audiorate 
//  ! "audio/x-raw, rate=48000, channels=1" ! queue ! voaacenc ! queue ! filesink location="test.aac"
void GST_CVR_Record(GST_CVR_Handle hHandle)
{
    gboolean bRet;
    GST_CVR_Struct *hCamcorder = (GST_CVR_Struct *)hHandle;
    GST_CVR_Struct *this = (GST_CVR_Struct *)hHandle;
    GstCaps *caps;

    /* Set the pipeline to "playing" state*/
    g_print("[GST_CVR]  Record ++ \n");

    if (hCamcorder->m_pipeline == NULL)
    {
        fprintf(stderr, "[GST_CVR]  pipeline not ready --\n");
        return;
    }

    gst_element_set_state (hCamcorder->m_pipeline, GST_STATE_PAUSED);
    
    if (hCamcorder->pipeline_is_playing == FALSE)
    {
        gst_bin_add_many(GST_BIN(hCamcorder->m_pipeline), hCamcorder->m_vsource,                                 
                        hCamcorder->m_tee,                        
                        hCamcorder->m_vidconvert,
                        hCamcorder->m_queue_disp,
                        hCamcorder->m_imagesink,
                        hCamcorder->m_video_enc, 
                        hCamcorder->m_queue_save,
                        hCamcorder->m_mux, 
                        hCamcorder->m_queue_mux, 
                        //hCamcorder->m_file,
                        NULL);

        //gst_pad_link ( gst_element_get_static_pad (hCamcorder->m_vsource, "src"),
        //               gst_element_get_request_pad (hCamcorder->video_filter_bin, "src"));
        caps = gst_caps_new_simple("video/x-raw",
                                                      "format", G_TYPE_STRING, "I420",
                                                      "width", G_TYPE_INT, 640,
                                                      "height", G_TYPE_INT, 480,
                                                      NULL);

        if (gst_element_link_pads_filtered(hCamcorder->m_vsource, "src",  hCamcorder->m_tee, "sink", caps) != TRUE)
        {
            g_printerr("m_vsource, m_tee Element could not be linked.\n");
        }
        //gst_object_unref(caps);

         //gst_element_link(hCamcorder->m_tee, hCamcorder->video_filter_bin);
         gst_element_link(hCamcorder->m_tee, hCamcorder->m_video_enc);//encoding
         gst_element_link(hCamcorder->m_tee, hCamcorder->m_vidconvert);//display

        
        gst_element_link(hCamcorder->m_video_enc, hCamcorder->m_queue_save);
        gst_element_link(hCamcorder->m_queue_save, hCamcorder->m_mux);
        gst_element_link(hCamcorder->m_mux, hCamcorder->m_queue_mux);
        //gst_element_link(hCamcorder->m_queue_mux, hCamcorder->m_file);///-<---------------------

        gst_element_link(hCamcorder->m_vidconvert, hCamcorder->m_queue_disp);
        gst_element_link(hCamcorder->m_queue_disp, hCamcorder->m_imagesink);
        
        gst_element_link(hCamcorder->m_video_enc, hCamcorder->m_mux);



// add
        gst_bin_add_many(GST_BIN(hCamcorder->catchPipeline), hCamcorder->fakesrc, hCamcorder->queue_catch/*, hCamcorder->fakesink*/, NULL);
        gst_bin_add_many(GST_BIN(hCamcorder->binRec1), hCamcorder->queue_1, hCamcorder->ph264_1, hCamcorder->mp4mux1, hCamcorder->identity1, hCamcorder->file_sink1, NULL);
        gst_bin_add_many(GST_BIN(hCamcorder->binRec2), hCamcorder->queue_2, hCamcorder->ph264_2, hCamcorder->mp4mux2, hCamcorder->identity2, hCamcorder->file_sink2, NULL);
// link
        gst_element_link_many(this->fakesrc, this->queue_catch/*, this->fakesink*/, NULL);

        gst_element_link_many(this->queue_1, this->ph264_1, this->mp4mux1, this->identity1, this->file_sink1, NULL);
        gst_element_link_many(this->queue_2, this->ph264_2, this->mp4mux2, this->identity2, this->file_sink2, NULL);

        /* add ghost pads to rec bins */
        GstPad* pad = gst_element_get_static_pad (this->queue_1, "sink");
        gst_element_add_pad (this->binRec1, gst_ghost_pad_new ("sink", pad));
        gst_object_unref (GST_OBJECT (pad));

        pad = gst_element_get_static_pad (this->queue_2, "sink");
        gst_element_add_pad (this->binRec2, gst_ghost_pad_new ("sink", pad));
        gst_object_unref (GST_OBJECT (pad));

        fprintf(stdout," link m_queue_mux , binRec1");
        /* connect the first recording bin to main pipeline */
        gst_bin_add(GST_BIN(this->m_pipeline), this->binRec1);        
        gst_element_link(hCamcorder->m_queue_mux, hCamcorder->binRec1);///-<---------------------

        fprintf(stdout," link queue_catch , binRec2");
        /* connect passive recording bin to catch pipeline */
        gst_bin_add(GST_BIN(this->catchPipeline), this->binRec2);
        gst_element_link(this->queue_catch, this->binRec2);
        

        hCamcorder->pipeline_is_playing = TRUE;
    }
    gst_element_set_state(hCamcorder->m_pipeline, GST_STATE_PLAYING);

    g_print("[GST_CVR]  Record -- \n");
}

/*
=================================================================================================================
Function Name: GST_CVR_Stop
Description:
=================================================================================================================
*/
void GST_CVR_Stop(GST_CVR_Handle hHandle)
{
    GST_CVR_Struct *hCamcorder = (GST_CVR_Struct *)hHandle;

    fprintf(stderr, "[GST_CVR]	Stop ++\n");

    if (hCamcorder->m_vsource)
        gst_element_send_event(hCamcorder->m_vsource, gst_event_new_eos());

    if (hCamcorder->m_asource)
        gst_element_send_event(hCamcorder->m_asource, gst_event_new_eos());

    fprintf(stderr, "[GST_CVR]	Stop --\n");
}

/*
=================================================================================================================
Function Name: GST_CVR_Pause
Description:
=================================================================================================================
*/
void GST_CVR_Switch(GST_CVR_Handle hHandle)
{
    GstStateChangeReturn bRet;
    GST_CVR_Struct *hCamcorder = (GST_CVR_Struct *)hHandle;

    fprintf(stderr, "[GST_CVR]	Pause ++\n");

    bRet = gst_element_set_state(hCamcorder->m_pipeline, GST_STATE_PAUSED);
    if (bRet != GST_STATE_CHANGE_SUCCESS)
        fprintf(stderr, "[GST_CVR]	Pause Error\n");

    fprintf(stderr, "[GST_CVR]	Pause --\n");
}

typedef struct _CustomData
{
    gboolean is_live;
    GstElement *pipeline;
    GMainLoop *loop;
} CustomData;

static void cb_message(GstBus *bus, GstMessage *msg, CustomData *data)
{

    return;
}

int main(int argc, char *argv[])
{
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;
    GMainLoop *main_loop;
    CustomData data;
    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    main_loop = g_main_loop_new(NULL, FALSE);
    data.loop = main_loop;

    GST_CVR_Main(main_loop);

    //    g_main_loop_run (main_loop);

    /* Free resources */
    g_main_loop_unref(main_loop);
    return 0;
}
