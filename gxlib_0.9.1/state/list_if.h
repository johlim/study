#ifndef __LIST_IF_H__
#define __LIST_IF_H__

/* Header file include --------------------------------------------------*/
//#include "obj_common.h"

/* Define  --------------------------------------------------------------*/
typedef GList ListNode, *ListNodePtr;
typedef void* NodeData;

typedef struct {
	ListNodePtr list;
	int link_only;	// whether use shallow copying or not (default 0)
} ListStruct, *ListHandle;

typedef enum _sorting_mode {
	SORT_NOTHING,					// nothing to sort (keep current sorting)
/*--- order --------------------*/
	SORT_ASCEND,
	SORT_DESCEND,
	SORT_MAX,
/*------------------------------*/
/*--- data type (experimental) -*/
	SORT_ASCII			= 0x1000,	// string (ascii)
	SORT_UNICODE		= 0x2000,	// experimental : string (utf-8)
	SORT_CONSTANT		= 0x4000,	// experimental : integer
/*------------------------------*/
}SortingMode;


typedef struct {
	/**
	 * create
	 *	Create linked list handle.
	 *	param0	: list property (0 = deep copy (default), 1 = shallow copy)
	 *	return	: handle
	 */
	ListHandle (*create)(int);

	/**
	 * add
	 *	Add (append) item into the list.
	 *	param0	: handle
	 *	parma1	: data to be added
	 *	param2	: size of data
	 *	return	: list node of the added data
	 */
	ListNodePtr (*add)(ListHandle, void*, int);

	/**
	 * insert
	 *	Insert item into specific position of the list.
	 *	param0	: handle
	 *	parma1	: data to be added
	 *	param2	: size of data
	 *	param3	: position (index) to insert
	 *	return	: list node of the inserted data
	 */
	ListNodePtr (*insert)(ListHandle, void*, int, int);

	/**
	 * get_index
	 *	Get position (index) of data from list.
	 *	param0	: handle
	 *	parma1	: data
	 *	return	: index of given data
	 */
	int (*get_index)(ListHandle, void*);

	/**
	 * get_data_nth
	 *	Get data from list using index.
	 *	param0	: handle
	 *	parma1	: index
	 *	return	: data of given index
	 */
	NodeData (*get_data_nth)(ListHandle, int);

	/**
	 * get_data_head
	 *	Get first data from list.
	 *	param0	: handle
	 *	return	: first data
	 */
	NodeData (*get_data_head)(ListHandle);

	/**
	 * get_data_tail
	 *	Get last data from list.
	 *	param0	: handle
	 *	return	: last data
	 */
	NodeData (*get_data_tail)(ListHandle);

	/**
	 * get_node
	 *	Get data node.
	 *	param0	: handle
	 *	param1	: data
	 *	return	: list node of given data
	 */
	ListNodePtr (*get_node)(ListHandle, void*);

	/**
	 * get_node_nth
	 *	Get data node using index.
	 *	param0	: handle
	 *	param1	: index
	 *	return	: list node of given index
	 */
	ListNodePtr (*get_node_nth)(ListHandle, int);

	/**
	 * get_node_head
	 *	Get first data node.
	 *	param0	: handle
	 *	return	: first list node
	 */
	ListNodePtr (*get_node_head)(ListHandle);

	/**
	 * get_node_tail
	 *	Get last data node.
	 *	param0	: handle
	 *	return	: last list node
	 */
	ListNodePtr (*get_node_tail)(ListHandle);

	/**
	 * count
	 *	Get item count of the list.
	 *	param0	: handle
	 *	return	: item count
	 */
	int (*count)(ListHandle);

	/**
	 * swap
	 *	Swap item node using index.
	 *	param0	: handle
	 *	param1	: first index
	 *	param2	: second index
	 *	return	: none
	 */
	void (*swap)(ListHandle, int, int);

	/**
	 * swap_data
	 *	Swap item node using data.
	 *	param0	: handle
	 *	param1	: first data
	 *	param2	: second data
	 *	return	: none
	 */
	void (*swap_data)(ListHandle, void*, void*);

	/**
	 * swap_node
	 *	Swap item node using node.
	 *	param0	: handle
	 *	param1	: first node
	 *	param2	: second node
	 *	return	: none
	 */
	void (*swap_node)(ListHandle, ListNode*, ListNode*);

	/**
	 * sort
	 *	Sort item list using specific option.
	 *	param0	: handle
	 *	param1	: sorting option (ref. SortingMode)
	 *	return	: none
	 */
	void (*sort)(ListHandle, SortingMode);

	/**
	 * remove
	 *	Remove specific node using data.
	 *	param0	: handle
	 *	param1	: data to be removed
	 *	return	: none
	 */
	void (*remove)(ListHandle, void*);

	/**
	 * remove_nt
	 *	Remove specific node using index.
	 *	param0	: handle
	 *	param1	: node index to be removed
	 *	return	: none
	 */
	void (*remove_nth)(ListHandle, int);

	/**
	 * remove_all
	 *	Remove all node from the list.
	 *	param0	: handle
	 *	return	: none
	 */
	void (*remove_all)(ListHandle);

	/**
	 * destroy
	 *	Destroy list handle.
	 *	param0	: handle
	 *	return	: none
	 */
	void (*destroy)(ListHandle);
} ListInterface;

/* Define extern variable & function  -----------------------------------*/
extern ListInterface ListIF;
void InitListIF(ListInterface *interface);
void ui_copy_text_w(unsigned char *dst_w, unsigned char *src_s);
#endif // __LIST_IF_H__
