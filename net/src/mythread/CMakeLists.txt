aux_source_directory(. DIR_MYTHREAD_SRC)

message(${PROJET_SOURCE_DIR}/utility)
include_directories(
	/usr/include
	/usr/local/include
	${SRC_DIR}/utility
	)

link_directories(
	/usr/lib
	/usr/local/lib
	)

add_library(MyThread SHARED ${DIR_MYTHREAD_SRC})
