#include <libxml/parser.h>

int 
main(int argc, char * arv[])
{
	xmlNode * node;
	xmlDoc * doc;
	xmlChar * xmlbuff;
	int bufsize;

	doc = xmlNewDoc("1.0");

	node = xmlNewNode(NULL, "greeting");
	xmlNodeSetContent(node, " Hello World!");
	xmlDocSetRootElement(doc, node);

	xmlDocDumpFormatMemory(doc, &xmlbuff, &bufsize, 1);

	printf("%s", (char *) xmlbuff);

	xmlFree( xmlbuff);
	xmlFreeDoc( doc);

	return 0;
}
