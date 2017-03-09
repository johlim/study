#include <stddef.h> // NULL
#include <app_file_glib.h>

////////////////////////////////////////////////////////////////////////////
//
GList*
g_list_first (GList *list)
{
  if (list)
    {
      while (list->prev)
	list = list->prev;
    }
  
  return list;
}

GList*
g_list_last (GList *list)
{
  if (list)
    {
      while (list->next)
	list = list->next;
    }
  
  return list;
}

GList*
g_list_prepend (GList	 *list,
		gpointer  data)
{
  GList *new_list;
  
  new_list = _g_list_alloc ();
  new_list->data = data;
  new_list->next = list;
  
  if (list)
    {
      new_list->prev = list->prev;
      if (list->prev)
	list->prev->next = new_list;
      list->prev = new_list;
    }
  else
    new_list->prev = NULL;
  
  return new_list;
}

GList*
g_list_append (GList	*list,
	       gpointer	 data)
{
  GList *new_list;
  GList *last;
  
  new_list = _g_list_alloc ();
  new_list->data = data;
  new_list->next = NULL;
  
  if (list)
    {
      last = g_list_last (list);
      /* g_assert (last != NULL); */
      last->next = new_list;
      new_list->prev = last;

      return list;
    }
  else
    {
      new_list->prev = NULL;
      return new_list;
    }
}

static GList*
_g_list_remove_link (GList *list,
		     GList *link)
{
  if (link == NULL)
    return list;

  if (link->prev)
    {
      if (link->prev->next == link)
        link->prev->next = link->next;
      else
        g_warning ("corrupted double-linked list detected");
    }
  if (link->next)
    {
      if (link->next->prev == link)
        link->next->prev = link->prev;
      else
        g_warning ("corrupted double-linked list detected");
    }

  if (link == list)
    list = list->next;

  link->next = NULL;
  link->prev = NULL;

  return list;
}

GList*
g_list_remove (GList	     *list,
	       gconstpointer  data)
{
  GList *tmp;

  tmp = list;
  while (tmp)
    {
      if (tmp->data != data)
	tmp = tmp->next;
      else
	{
          list = _g_list_remove_link (list, tmp);
	  _g_list_free1 (tmp);

	  break;
	}
    }
  return list;
}

unsigned int g_list_length (GList *list)
{
  unsigned int length;
  
  length = 0;
  while (list)
    {
      length++;
      list = list->next;
    }
  
  return length;
}

gpointer
g_list_nth_data (GList     *list,
		 unsigned int      n)
{
  while ((n-- > 0) && list)
    list = list->next;
  
  return list ? list->data : NULL;
}


GList*
g_list_nth (GList *list,
	    unsigned int  n)
{
  while ((n-- > 0) && list)
    list = list->next;
  
  return list;
}

void g_list_foreach (GList	 *list,	GFunc	  func,	gpointer  user_data)
{
  while (list)
    {
      GList *next = list->next;
      (*func) (list->data, user_data);
      list = next;
    }
}

GList*
g_list_find (GList         *list,
	     gconstpointer  data)
{
  while (list)
    {
      if (list->data == data)
	break;
      list = list->next;
    }
  
  return list;
}
GList*
g_list_delete_link (GList *list,
		    GList *link_)
{
  list = _g_list_remove_link (list, link_);
  _g_list_free1 (link_);

  return list;
}

GList*
g_list_nth_prev (GList *list,
		 guint  n)
{
  while ((n-- > 0) && list)
    list = list->prev;
  
  return list;
}

/**
 * g_list_position:
 * @list: a #GList
 * @llink: an element in the #GList
 *
 * Gets the position of the given element 
 * in the #GList (starting from 0).
 *
 * Returns: the position of the element in the #GList, 
 *     or -1 if the element is not found
 */
gint
g_list_position (GList *list,
		 GList *llink)
{
  gint i;

  i = 0;
  while (list)
    {
      if (list == llink)
	return i;
      i++;
      list = list->next;
    }

  return -1;
}

/**
 * g_list_index:
 * @list: a #GList
 * @data: the data to find
 *
 * Gets the position of the element containing 
 * the given data (starting from 0).
 *
 * Returns: the index of the element containing the data, 
 *     or -1 if the data is not found
 */
gint
g_list_index (GList         *list,
	      gconstpointer  data)
{
  gint i;

  i = 0;
  while (list)
    {
      if (list->data == data)
	return i;
      i++;
      list = list->next;
    }

  return -1;
}

static GList *
g_list_sort_merge (GList     *l1, 
		   GList     *l2,
		   GFunc     compare_func,
		   gpointer  user_data)
{
  GList list, *l, *lprev;
  gint cmp;

  l = &list; 
  lprev = NULL;

  while (l1 && l2)
    {
      cmp = ((GCompareDataFunc) compare_func) (l1->data, l2->data, user_data);

      if (cmp <= 0)
        {
	  l->next = l1;
	  l1 = l1->next;
        } 
      else 
	{
	  l->next = l2;
	  l2 = l2->next;
        }
      l = l->next;
      l->prev = lprev; 
      lprev = l;
    }
  l->next = l1 ? l1 : l2;
  l->next->prev = l;

  return list.next;
}

static GList* 
g_list_sort_real (GList    *list,
		  GFunc     compare_func,
		  gpointer  user_data)
{
  GList *l1, *l2;
  
  if (!list) 
    return NULL;
  if (!list->next) 
    return list;
  
  l1 = list; 
  l2 = list->next;

  while ((l2 = l2->next) != NULL)
    {
      if ((l2 = l2->next) == NULL) 
	break;
      l1 = l1->next;
    }
  l2 = l1->next; 
  l1->next = NULL; 

  return g_list_sort_merge (g_list_sort_real (list, compare_func, user_data),
			    g_list_sort_real (l2, compare_func, user_data),
			    compare_func,
			    user_data);
}

GList *
g_list_sort (GList        *list,
	     GCompareFunc  compare_func)
{
  return g_list_sort_real (list, (GFunc) compare_func, NULL);
			    
}
//
////////////////////////////////////////////////////////////////////////////

void * g_memdup(void *data, int size)
{ 
	void * ptr = malloc(size);
	memcpy(ptr, data, size);
	return ptr;
}