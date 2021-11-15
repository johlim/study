ADD_EXECUTABLE( app.out pthread_main.c )
SET ( CMAKE_C_FLAGS "-pthread -g" )
#ADD_COMPILE_OPTIONS( -g )