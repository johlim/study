SET ( SRC_FILES main.c src/module.cpp src/submodule.cpp )
SET ( INC_FILES src/common_inc.h)
ADD_EXECUTABLE( emblinux ${SRC_FILES} ${INC_FILES})