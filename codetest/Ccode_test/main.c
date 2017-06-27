#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#define DEBUG_TEST
gboolean parse_scen(char * path)
{
	FILE* hscen=0;
	gchar scen[100];
	int input[20];
	gchar **param;
	gchar g_type;
	gint g_mstime;
	int count = 1;// header skip
	gboolean ret=TRUE;

#ifdef DEBUG_TEST
        g_print("[%d] %s \n", __LINE__, path);
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
        g_print("%d %s \n", __LINE__, scen);
#endif

		if(strlen(scen) == 0)
			continue;

		switch(count)
		{
		case 0:
			// script file  header check
			count++;
			break;
		case 1:
			if(scen[0] == '#')
				break;
			sscanf(scen,"%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&g_type, &g_mstime,\
          			&input[0],\
                    &input[1],\
                    &input[2],\
                    &input[3],\
                    &input[4],\
                    &input[5],\
                    &input[6],\
                    &input[7],\
                    &input[8],\
                    &input[9],\
                    &input[10],\
                    &input[11],\
                    &input[12],\
                    &input[13],\
                    &input[14],\
                    &input[15]);

			break;
		}
	}

	fclose(hscen);

	return ret;
}

int main()
{
    parse_scen("/home/jhlim/svn_app/trunk/application/adas_control/src/test_scen.txt");

    return 0;
}
