aux_source_directory(. DIR_MYNET_SRC)

message(${PROJET_SOURCE_DIR}/utility)
include_directories(
	/usr/include
	/usr/local/include
	${SRC_DIR}/utility
	)

link_directories(
	/usr/include
	/usr/local/include
	)

add_library(MyNet SHARED ${DIR_MYNET_SRC})
