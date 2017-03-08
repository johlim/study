#include <stdbool.h>
#include <glib.h>

/* Header file include --------------------------------------------------*/
#include "list_if.h"

/* Define  --------------------------------------------------------------*/
ListInterface ListIF = {0};

/* Define extern variable & function  -----------------------------------*/
static ListHandle list_create(int link_only);
static ListNode* list_add(ListHandle handle, void *data, int size);
static ListNode* list_insert(ListHandle handle, void *data, int size, int index);
static int list_get_index(ListHandle handle, void *data);
static void* list_get_data_nth(ListHandle handle, int index);
static void* list_get_data_head(ListHandle handle);
static void* list_get_data_tail(ListHandle handle);
static ListNode* list_get_node(ListHandle handle, void *data);
static ListNode* list_get_node_nth(ListHandle handle, int index);
static ListNode* list_get_node_head(ListHandle handle);
static ListNode* list_get_node_tail(ListHandle handle);
static int list_count(ListHandle handle);
static void list_swap_index(ListHandle handle, int index0, int index1);
static void list_swap_data(ListHandle handle, void *data0, void *data1);
static void list_swap_node(ListHandle handle, ListNode *node0, ListNode *node1);
static void list_sort(ListHandle handle, SortingMode mode);
static void list_remove(ListHandle handle, void *data);
static void list_remove_nth(ListHandle handle, int index);
static void list_remove_all(ListHandle handle);
static void list_destroy(ListHandle handle);

static int compare_ascii(const char *data0, const char *data1, void *mode_ptr);
static int compare_unicode(const char *data0, const char *data1, void *mode_ptr);
static int compare_constant(void *data0, void *data1, void *mode_ptr);
void ui_copy_text_w(unsigned char *dst_w, unsigned char *src_s);
/* Function implementation  ---------------------------------------------*/

void ui_copy_text_w(unsigned char *dst_w, unsigned char *src_s)
{
	do {
		*dst_w++ = *src_s++;
	}
	while(*src_s);
	*dst_w = *src_s;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
void InitListIF(ListInterface *if_ptr)
{
	if(if_ptr) {
		if_ptr->create = list_create;
		if_ptr->add = list_add;
		if_ptr->insert = list_insert;
		if_ptr->get_index = list_get_index;
		if_ptr->get_data_nth = list_get_data_nth;
		if_ptr->get_data_head = list_get_data_head;
		if_ptr->get_data_tail = list_get_data_tail;
		if_ptr->get_node = list_get_node;
		if_ptr->get_node_nth = list_get_node_nth;
		if_ptr->get_node_head = list_get_node_head;
		if_ptr->get_node_tail = list_get_node_tail;
		if_ptr->count = list_count;
		if_ptr->swap = list_swap_index;
		if_ptr->swap_data = list_swap_data;
		if_ptr->swap_node = list_swap_node;
		if_ptr->sort = list_sort;
		if_ptr->remove = list_remove;
		if_ptr->remove_nth = list_remove_nth;
		if_ptr->remove_all = list_remove_all;
		if_ptr->destroy = list_destroy;
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static ListHandle list_create(int link_only)
{
	ListHandle handle;

	handle = (ListHandle)g_malloc0(sizeof(ListStruct));
	handle->link_only = link_only;
	return handle;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static ListNode* list_add(ListHandle handle, void *data, int size)
{
	gpointer ptr;

	if(!handle->link_only) {
		ptr = g_memdup(data, size);
	}
	else {
		ptr = data;
	}
	handle->list = g_list_append(handle->list, ptr);
	return g_list_last(handle->list);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static ListNode* list_insert(ListHandle handle, void *data, int size, int index)
{
	gpointer ptr;

	if(!handle->link_only) {
		ptr = g_memdup(data, size);
	}
	else {
		ptr = data;
	}
	handle->list = g_list_insert(handle->list, ptr, index);
	return g_list_nth(handle->list, index);
}

/******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int list_get_index(ListHandle handle, void *data)
{
	return g_list_index(handle->list, data);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void* list_get_data_nth(ListHandle handle, int index)
{
	return g_list_nth_data(handle->list, index);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void* list_get_data_head(ListHandle handle)
{
	GList *node;

	node = g_list_first(handle->list);
	if(node) {
		return node->data;
	}
	return NULL;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void* list_get_data_tail(ListHandle handle)
{
	GList *node;

	node = g_list_last(handle->list);
	if(node) {
		return node->data;
	}
	return NULL;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static ListNode* list_get_node(ListHandle handle, void *data)
{
	return g_list_find(handle->list, data);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static ListNode* list_get_node_nth(ListHandle handle, int index)
{
	return g_list_nth(handle->list, index);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static ListNode* list_get_node_head(ListHandle handle)
{
	return g_list_first(handle->list);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static ListNode* list_get_node_tail(ListHandle handle)
{
	return g_list_last(handle->list);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int list_count(ListHandle handle)
{
	return g_list_length(handle->list);
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_swap_index(ListHandle handle, int index0, int index1)
{
	GList *node0, *node1;
	gpointer temp;

	node0 = g_list_nth(handle->list, index0);
	node1 = g_list_nth(handle->list, index1);
	if(node0 && node1) {
		temp = node0->data;
		node0->data = node1->data;
		node1->data = temp;
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_swap_data(ListHandle handle, void *data0, void *data1)
{
	GList *node0, *node1;
	gpointer temp;

	node0 = g_list_find(handle->list, data0);
	node1 = g_list_find(handle->list, data1);
	if(node0 && node1) {
		temp = node0->data;
		node0->data = node1->data;
		node1->data = temp;
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_swap_node(ListHandle handle, ListNode *node0, ListNode *node1)
{
	gpointer temp;

	temp = node0->data;
	node0->data = node1->data;
	node1->data = temp;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_sort(ListHandle handle, SortingMode mode)
{
	if(mode & SORT_ASCII) {
		handle->list = g_list_sort_with_data(handle->list, (GCompareDataFunc)compare_ascii, &mode);
	}
	else if(mode & SORT_UNICODE) {
		handle->list = g_list_sort_with_data(handle->list, (GCompareDataFunc)compare_unicode, &mode);
	}
	else {
		handle->list = g_list_sort_with_data(handle->list, (GCompareDataFunc)compare_constant, &mode);
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_remove(ListHandle handle, void *data)
{
	handle->list = g_list_remove(handle->list, data);
	if(!handle->link_only) {
		g_free(data);
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_remove_nth(ListHandle handle, int index)
{
	gpointer data;

	data = g_list_nth_data(handle->list, index);
	handle->list = g_list_remove(handle->list, data);
	if(!handle->link_only) {
		g_free(data);
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_remove_all(ListHandle handle)
{
	if(!handle->link_only) {
#if defined(_ARM_)
		g_list_free_full(handle->list, g_free); //( g_list_free_full > glib2.28 )
#else
		g_list_free(handle->list);
#endif
	}
	else {
		g_list_free(handle->list);
	}
	handle->list = NULL;
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static void list_destroy(ListHandle handle)
{
	if(handle) {
		if(handle->list) {
			list_remove_all(handle);
		}
		handle->link_only = 0;
		g_free(handle);
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int compare_ascii(const char *data0, const char *data1, void *mode_ptr)
{
	const char *ptr0, *ptr1;
	SortingMode mode = *((SortingMode*)mode_ptr);

	ptr0 = g_strrstr(data0, "/\0");
	ptr1 = g_strrstr(data1, "/\0");
	ptr0 = ptr0 ? ptr0 + 1 : data0;
	ptr1 = ptr1 ? ptr1 + 1 : data1;
	if(mode & SORT_ASCEND) {
		return g_strcmp0(ptr0, ptr1);
	}
	else {
		return g_strcmp0(ptr1, ptr0);
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int compare_unicode(const char *data0, const char *data1, void *mode_ptr)
{
	const char *ptr0, *ptr1;
	SortingMode mode = *((SortingMode*)mode_ptr);

	ptr0 = g_utf8_strrchr(data0, -1, 0x002F);
	ptr1 = g_utf8_strrchr(data1, -1, 0x002F);
	ptr0 = ptr0 ? ptr0 + 1 : data0;
	ptr1 = ptr1 ? ptr1 + 1 : data1;
	if(mode & SORT_ASCEND) {
		return g_utf8_collate(ptr0, ptr1);
	}
	else {
		return g_utf8_collate(ptr1, ptr0);
	}
}

/*******************************************************************************
*	Description		:
*	Argurments		:
*	Return value	:
*	Modify			:
*	warning			:
*******************************************************************************/
static int compare_constant(void *data0, void *data1, void *mode_ptr)
{
	int n0 = *((int*)data0);
	int n1 = *((int*)data1);
	SortingMode mode = *((SortingMode*)mode_ptr);

	if(n0 != n1) {
		if(mode & SORT_ASCEND) {
			return n0 < n1 ? -1 : 1;
		}
		else {
			return n0 < n1 ? 1 : -1;
		}
	}
	return 0;
}


