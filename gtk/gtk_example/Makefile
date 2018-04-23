
SUBDIRS = comm_test_app
DUMMYHEADER = 

all:
	./rev_check.sh
	@for dir in $(SUBDIRS) ; do \
		test -s $$dir/Makefile || continue; \
		$(MAKE) -C $$dir || exit 1; \
	 done

clean:
	@for dir in $(SUBDIRS) ; do \
		test -s $$dir/Makefile || continue; \
		$(MAKE) -C $$dir clean; \
	 done
cleanall:
	@for dir in $(SUBDIRS) ; do \
		test -s $$dir/Makefile || continue; \
		$(MAKE) -C $$dir clean; \
	 done
	@for hfile in  $(DUMMYHEADER) ; do \
		test -s $$hfile || continue; \
		rm $$hfile; \
	 done
