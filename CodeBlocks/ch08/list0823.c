#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int 
main(int argc, char * argv[])
{
	sqlite3 * db;
	char * err_msg = NULL;
	int rc;
	int counter = 0;

	rc = sqlite3_open_v2(argv[1], &db, SQLITE_OPEN_READONLY, NULL);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "%s", sqlite3_errmsg(db));
		sqlite3_close(db);
		return EXIT_FAILURE;
	}

	sqlite3_close(db);

	return EXIT_SUCCESS;
}
