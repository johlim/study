#ifndef __PARSER_H__
#define __PARSER_H__

#include "obj_common.h"

#define SCRIPT_PATH	"script.xml"

int script_open_parsing(char *script_path);
void script_close_parsing(void);
void script_update(void);

#endif // __PARSER_H__
