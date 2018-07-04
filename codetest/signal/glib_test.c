#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <glib.h>

void handler(int signo);

int test_1(int argc, char **argv[])
{

    GList * list = NULL;
    GList * node;

    list = g_list_append(list,"foo");
    list = g_list_append(list,"foo1");
    list = g_list_append(list,"foo2");

    g_print("%d\n", g_list_length(list)); /* 3 */
    node = g_list_nth(list, 0);
    g_print("%s\n", (char*)(node->data)); 
    node = g_list_find(list, "foo1");
    g_print("%s\n", (char*)(node->data)); 
    
    for(node=list ; node != NULL; node=node->next)
        g_printf("STRING %s \n", (char *)node->data);

}
//GINT_TO_POINTER




int main(int argc, char **argv[])
{

    GList * list = NULL;
    GList * node;
    char * newnode;

    newnode = g_malloc0(16);
    sprintf(newnode,"foo1");
    list = g_list_append(list,newnode);
    newnode = g_malloc0(16);
    sprintf(newnode,"foo2");
    list = g_list_append(list,newnode);
    newnode = g_malloc0(16);
    sprintf(newnode,"foo3");
    list = g_list_append(list,newnode);

    g_print("%d\n", g_list_length(list)); /* 3 */
    node = g_list_nth(list, 0);
    g_print("%s\n", (char*)(node->data)); 
    node = g_list_nth(list, 1);
    g_print("%s\n", (char*)(node->data)); 
    node = g_list_nth(list, 2);
    g_print("%s\n", (char*)(node->data)); 
    
    for(node=list ; node != NULL; node=node->next)
        g_printf("STRING %s \n", (char *)node->data);

    g_list_foreach(list, (GFunc)g_free, NULL);
    g_list_free(list);

}
