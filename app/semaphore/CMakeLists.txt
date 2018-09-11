PROJECT(proc_sema)
ADD_EXECUTABLE(hello proc_sema.c)
target_link_libraries (hello pthread)
