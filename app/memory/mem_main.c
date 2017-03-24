int main(int argc, char * arg[])
{
	RAII_VARIABLE(char *, name, (char *)malloc(32), free)
		strcpy(name, "RAII example");
	printf("%s\n", name);

	return 0;
}
