extern funca(void);
extern funcb(void);
int
main(void)
{
	unsigned long long i;
	i=0;
	do
	{
if (i % 100 == 0)
	funca();
if (i % 50  == 0)
	funcb();
	i++;
	}
	while(i);
	return 0;
}
