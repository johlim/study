#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void
print_node (xmlNode * start, int depth)
{
	xmlNode * node = NULL;

	for(node = start; node; node = node->next)
	{
		if (node->type == XML_ELEMENT_NODE)
		{
			int i;
			for(i=0; i < depth; i++) printf("  ");
			printf("%s\n", node->name);
		}
		print_node(node->children, depth+1);
	}
}

int main(int argc, char ** argv)
{
	xmlDoc* doc = xmlParseFile (argv[1]);
	xmlNode* root = xmlDocGetRootElement (doc);

	print_node(root,0);

	xmlFreeDoc(doc);
	xmlCleanupParser();

	return 0;
}
