#ifndef __APP_FM_GLIB_H__
#define __APP_FM_GLIB_H__

typedef struct _GList GList;
struct _GList
{  
	void * data;  
	GList *next;  
	GList *prev;
};
/*
////////////////////////////////////////////////////////////////////////////
//  from glib 
//  20140930
//	g_slist_last
//	g_slist_remove
//	g_slist_append
//	g_slist_length
//	g_slist_nth_data
//	g_slist_sort_with_data
//	g_slist_nth
// #define pool_alloc(size)  \
    // malloc((u_long)(size))
// #define pool_free(addr)  \
    // free((caddr_t)(addr))
*/
#define _g_list_alloc()  \
    listalloc()
#define _g_list_free1(addr)  \
    listfree((char *)(addr))
#define guint	unsigned int
#define gint	int
#define gpointer	void *
#define gconstpointer	const void *
#define g_warning	printf
//void    (*GFunc)    (gpointer data, gpointer user_data);
typedef void (*GFunc)(void*,void*); // fname sync
typedef void	(*GDestroyNotify) ();
typedef int	(*GCompareFunc)	(gconstpointer a, gconstpointer b);
typedef int (*GCompareDataFunc) (gconstpointer a, gconstpointer b, gpointer user_data);

#define g_list_previous(list)	        ((list) ? (((GList *)(list))->prev) : NULL)
#define g_list_next(list)	        ((list) ? (((GList *)(list))->next) : NULL)


#endif