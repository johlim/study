/**
 * Copyright (c) 2007-2013 Core Logic, Inc. All Rights Reserved.
 *
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * CORE LOGIC, INC.
 *
 *
 *
*/
#include <glib.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "clbbipcapi.h"
#include "dvr_message.h"
#define DEBUG_TEST


#define DVR_SCEN_HEADER	"[CoreLogic DVR Scenario]"
guint AgingCommander_loop;
gboolean g_hascfg = FALSE;
char g_scenpath[128];
guint g_RunTime = 0;
uint  g_sizeofmsgarray;
static GArray *garray;
int CmdCount;
int g_ipcmsgkey;
int g_bQuit=TRUE;

typedef struct _cmdtype CmdType;
struct _cmdtype
{
    uint ms;
    uint cmd1;
    uint cmd2;
};
// msg to enum table
typedef struct _intmsgtype INTERNAL_MSG_T;
struct _intmsgtype
{
    char * str;
    uint num;
} ;

INTERNAL_MSG_T int_msg_map[]=
{
	{"DVR_EVENT" 			,DVR_EVENT },
	{"DVR_GSENSOR_DATA"		,DVR_GSENSOR_DATA},
	{"DVR_GPS_DATA"			,DVR_GPS_DATA},
	{"DVR_OBD_DATA"			,DVR_OBD_DATA},
	{"DVR_INF_START"		,DVR_INF_START},
	{"DVR_INF_STOP"			,DVR_INF_STOP},
	{"DVR_PARK_START"		,DVR_PARK_START},
	{"DVR_PARK_STOP"		,DVR_PARK_STOP},
	{"DVR_START"			,DVR_START},
	{"DVR_STOP"				,DVR_STOP},
	{"DVR_STOP_DIRECT"		,DVR_STOP_DIRECT},
	{"DVR_EXIT"				,DVR_EXIT},
	{"DVR_DISPLAY"			,DVR_DISPLAY},
	{"DVR_PIP_SET"			,DVR_PIP_SET},
	{"DVR_GPS_START"		,DVR_GPS_START},
	{"DVR_GSEN_START"		,DVR_GSEN_START},
	{"DVR_EXTPROC_ENABLE"	,DVR_EXTPROC_ENABLE},
	{"DVR_WRITE_DISABLE"	,DVR_WRITE_DISABLE},
	{"DVR_CFG_UPDATE"		,DVR_CFG_UPDATE},
	{"DVR_PCM_PLAY"		,DVR_PCM_PLAY},
	{"DVR_PCM_EXIT"		,DVR_PCM_EXIT},
	{"DVR_FILEMAN_ERROR"	,DVR_FILEMAN_ERROR},
	{"DVR_GSENSOR_MOVEMENT_IN",DVR_GSENSOR_MOVEMENT_IN},
	{"DVR_GSENSOR_MOVEMENT_OUT",DVR_GSENSOR_MOVEMENT_OUT},
	{"DVR_USER_REC_START",DVR_USER_REC_START},
	{"DVR_USER_REC_STOP",DVR_USER_REC_STOP}		
};

int convert_strtodvrenum(char * str, int * conv_ret)
{
	int i;

	for(i=0; i< g_sizeofmsgarray; i++)
	{
		if ( g_strcmp0(str, int_msg_map[i].str ) == 0 )
		{
			*conv_ret = int_msg_map[i].num;
			g_print (" %s is %d\n",str,*conv_ret);
			return TRUE;
		}
	}
	*conv_ret = -1;
	return FALSE;
}

int convert_strtoipcenum(char * str, int * conv_ret)
{
	*conv_ret = CLBB_ALIVE;// = 0x1004,
	return TRUE;
}

void register_event(uint ms, uint cmd1, uint cmd2)
{
    
    gint i;
    CmdType bin;
    CmdType * out;

	if (garray == NULL)
		garray = g_array_new (TRUE, FALSE, sizeof (CmdType));


	bin.ms = ms;
	bin.cmd1 = cmd1;
	bin.cmd2 = cmd2;

	g_array_append_val (garray, bin);
	g_print ("%d : %x : %d \n", bin.ms, bin.cmd1, bin.cmd2);
	
	CmdCount=CmdCount+1;
	g_print ("CmdCount (%d)\n", CmdCount);
	
    // for (i = 0; i < 10000; i++)
    // {
      // dummy.ms = i;
      // g_array_append_val (garray, dummy);
    // }

    // for (i = 0; i < 10000; i++)
    // {
        // dummy = g_array_index (garray, CmdType, i);
      // if ( dummy.ms != i)
        // g_print ("ERROR: got %d instead of %d\n",
                 // dummy.ms, i);
    // }

    // g_array_free (garray, TRUE);

}

//!------------------------------------------------------------------------------
//! Function Implemetation
//!
//! ----------------------------------------------------------------------------
static char * MsgString(int cmd)
{
	char * strptr;
	strptr="what msg?";
	switch(cmd)
	{
		case 	DVR_EVENT  : 					  strptr="DVR_EVENT  : "; break;
		case 	DVR_GSENSOR_DATA :                strptr="DVR_GSENSOR_DATA : "; break;
		case 	DVR_GPS_DATA :                    strptr="DVR_GPS_DATA : "; break;
		case 	DVR_INF_START :                   strptr="DVR_INF_START : "; break;
		case 	DVR_INF_STOP :                    strptr="DVR_INF_STOP : "; break;
		case 	DVR_PARK_START :                  strptr="DVR_PARK_START : "; break;
		case 	DVR_PARK_STOP :                   strptr="DVR_PARK_STOP : "; break;
		case 	DVR_START :                       strptr="DVR_START : "; break;
		case 	DVR_STOP :                        strptr="DVR_STOP : "; break;
		case 	DVR_STOP_DIRECT :                 strptr="DVR_STOP_DIRECT : "; break;
		case 	DVR_EXIT :                        strptr="DVR_EXIT : "; break;
		case 	DVR_DISPLAY :                     strptr="DVR_DISPLAY : "; break;
		case 	DVR_PIP_SET :                     strptr="DVR_PIP_SET : "; break;
		case 	DVR_GPS_START :                   strptr="DVR_GPS_START : "; break;
		case 	DVR_GSEN_START :                  strptr="DVR_GSEN_START : "; break;
		case 	DVR_EXTPROC_ENABLE :              strptr="DVR_EXTPROC_ENABLE : "; break;
		case 	DVR_WRITE_DISABLE :               strptr="DVR_WRITE_DISABLE : "; break;
		case 	DVR_CFG_UPDATE :                  strptr="DVR_CFG_UPDATE : "; break;
		case 	DVR_PCM_PLAY :                    strptr="DVR_PCM_PLAY : "; break;
		case 	DVR_PCM_EXIT :                    strptr="DVR_PCM_EXIT : "; break;
		case 	DVR_FILEMAN_ERROR :               strptr="DVR_FILEMAN_ERROR : "; break;
		case 	DVR_GSENSOR_MOVEMENT_IN :         strptr="DVR_GSENSOR_MOVEMENT_IN : "; break;
		case 	DVR_GSENSOR_MOVEMENT_OUT :        strptr="DVR_GSENSOR_MOVEMENT_OUT : "; break;
		case 	DVR_STATE_RESERVED1 :             strptr="DVR_STATE_RESERVED1 : "; break;
		case 	DVR_STATE_RESERVED2 :             strptr="DVR_STATE_RESERVED2 : "; break;
		case 	DVR_STATE_RESERVED3 :             strptr="DVR_STATE_RESERVED3 : "; break;
		case 	DVR_BUTTON_1_DOWN :               strptr="DVR_BUTTON_1_DOWN : "; break;
		case 	DVR_BUTTON_1_UP :                 strptr="DVR_BUTTON_1_UP : "; break;
		case 	DVR_BUTTON_2_DOWN :               strptr="DVR_BUTTON_2_DOWN : "; break;
		case 	DVR_BUTTON_2_UP :                 strptr="DVR_BUTTON_2_UP : "; break;
		case 	DVR_BUTTON_3_DOWN :               strptr="DVR_BUTTON_3_DOWN : "; break;
		case 	DVR_BUTTON_3_UP : 	            strptr="DVR_BUTTON_3_UP : "; break;
		case 	DVR_BUTTON_1_LONG_DOWN :          strptr="DVR_BUTTON_1_LONG_DOWN : "; break;
		case 	DVR_BUTTON_2_LONG_DOWN :          strptr="DVR_BUTTON_2_LONG_DOWN : "; break;
		case 	DVR_BUTTON_3_LONG_DOWN :          strptr="DVR_BUTTON_3_LONG_DOWN : "; break;
		case 	DVR_PCM_WARNING_SD_REMOVED :      strptr="DVR_PCM_WARNING_SD_REMOVED : "; break;
		case 	DVR_TVOUT_DETECTED :              strptr="DVR_TVOUT_DETECTED : "; break;
		case 	DVR_TVOUT_REMOVED : 	            strptr="DVR_TVOUT_REMOVED : "; break;
		case 	DVR_USER_REC_START :              strptr="DVR_USER_REC_START : "; break;
		case 	DVR_USER_REC_STOP : 	            strptr="DVR_USER_REC_STOP : "; break;		
	}
	return strptr;
}

gboolean parse_arg(int argc, char *argv[])
{
	int i;
	int slen = 0;
	char keystring[128];

	if(argc > 1)
	{
		for(i=1; i<argc; i += 2)
		{
#ifdef DEBUG_TEST
        printf("%s", argv[i]);
#endif
			if(g_strcmp0(argv[i], "-h") == 0 || g_strcmp0(argv[i], "--help") == 0)
			{
				g_print("Usage : cl_test [option] [value] ...\n");
				g_print("-cfg	set dvr configuration file path(ex:cl_test -scen test_scen.csv )\n");
				return FALSE;
			}
			else if(g_strcmp0(argv[i], "-scen") == 0)
			{
				memset(g_scenpath, 0, 128);
				strcpy(g_scenpath, (char*)argv[i+1]);
				g_hascfg = TRUE;
			}
			else if(g_strcmp0(argv[i], "-runtime") == 0)
			{
				g_RunTime = atoi(argv[i+1]);
				g_print("cl_test run time (%d) : for debugging ( auto stop at time )\n", g_RunTime);
			}
			else if(g_strcmp0(argv[i], "-key") == 0)
			{
				memset(keystring, 0, 128);
				strcpy(keystring, (gchar*)argv[i+1]);
                g_ipcmsgkey = strtol(keystring, NULL, 16);
                g_print("-key %s %08x \n", keystring, g_ipcmsgkey);
			}			
			else
			{
				g_print("Usage : cl_test [option] [value] ...\n");
				g_print("-cfg	set dvr configuration file path(ex:cl_test -cfg /usr/dvr_hd2ch_lcd.cfg)\n");
				return FALSE;
			}
		}
	}

	return TRUE;
}
guint g_mstime;;
gchar * g_cmd1;
gchar * g_cmd2;

gboolean parse_scen(char * path)
{
	FILE* hscen;
	gchar scen[100];
	gchar **param;
	int count = 0;
	int result1=0;
	int result2=0;

#ifdef DEBUG_TEST
        printf("%d %s \n", __LINE__, path);
#endif

	hscen = fopen(path, "r");
	if(!hscen)
	{
		g_print("parse_scen configuration file open failed (%s)\n", path);
		return FALSE;
	}

	while(TRUE)
	{
		memset(scen, 0, 100);
		if(!fgets(scen, 100, hscen))
			break;

		scen[strlen(scen)-1] = 0;

#ifdef DEBUG_TEST
        printf("%d %s \n", __LINE__, scen);
#endif

		if(strlen(scen) == 0)
			continue;
		switch(count)
		{
		case 0:
			if(strcmp(scen, DVR_SCEN_HEADER) != 0)
			{
				g_print("Invalid DVR Configuration File\n");
				return FALSE;
			}
			count++;
			break;
		case 1:
			if(scen[0] == '#')
				break;
			param = g_strsplit(scen, ",", 4);
			{
			    g_mstime = atoi(param[0]);
			    g_cmd1 = g_strstrip(param[1]);
			    g_cmd2 = g_strstrip(param[2]);
			}
#ifdef DEBUG_TEST
			printf("%d %s %s \n", g_mstime, g_cmd1, g_cmd2);
#endif
            // convert msg enum type
            //convert_msgtoenum();
			convert_strtoipcenum(g_cmd1, &result1);
			convert_strtodvrenum(g_cmd2, &result2);
			if ((result1 >=0) && (result2 >= 0))
			register_event(g_mstime, result1, result2);
#ifdef DEBUG_TEST
			else
			g_print("%s : %s msg error", g_cmd1, g_cmd2);
#endif			
            //
			g_strfreev(param);
			break;
		}
	}

	fclose(hscen);

	return TRUE;
}
char * testparam[]={"cl_test","-scen","/home/limjh/test_scen.csv"};

int main(int argc, char *argv[])
{
    CmdType * out;
	uint	i,j;
	guint intervalms;
	guint cmd;
	
	//if(!parse_arg(argc, argv))
	if(!parse_arg(3,testparam))
	{
		g_print("parse_arg failed\n");
		return 0;
	}

	if(!g_ipcmsgkey)
	{
		return 0;
	} 	
	
	// Init Internal variable
	g_sizeofmsgarray = sizeof(int_msg_map)/sizeof(INTERNAL_MSG_T);

	if (g_hascfg==TRUE)
	{
#ifdef DEBUG_TEST
        printf("%d %s \n", __LINE__, g_scenpath);
#endif
	    parse_scen(g_scenpath);
	}

	g_usleep (10*1000*1000);// 10 sec
	
//  main loop	
	i=AgingCommander_loop;// init 0

	while(g_bQuit)
	{
		out = &g_array_index (garray, CmdType, i % CmdCount);
		intervalms = out->ms;
		cmd = out->cmd2;

		g_print ("\t\t\t\t\t\t After %d(ms) Event(%s) will happen\n", intervalms, MsgString(cmd));
		
		for(j=0; j < intervalms; j++)
		{
			g_usleep (1000);
			if (!g_bQuit)
			goto AgingLoopOUT;
			/* Running Time Check 
			if (g_RunTime < CurTime)
			goto AgingLoopOUT;
			*/
		}
		i=++AgingCommander_loop;

		{
			g_print ("AgingCommander Event(%d) CmdCount(%d), SetCount(%d) \n", cmd, AgingCommander_loop, (AgingCommander_loop/CmdCount));			
		}
	}

	AgingLoopOUT:	
	

    g_print("OK\n");
    return 0;
}
