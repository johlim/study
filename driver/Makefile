SUBDIRS = `find ./* -maxdepth 0 -type d`


all:
	@for dir in $(SUBDIRS) ; do \
		test -s $$dir/Makefile || continue; \
		$(MAKE) -C $$dir || exit 1; \
		done

clean:
	@for dir in $(SUBDIRS) ; do \
		test -s $$dir/Makefile || continue; \
		$(MAKE) -C $$dir clean; \
		done
