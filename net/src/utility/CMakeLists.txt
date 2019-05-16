aux_source_directory(. DIR_UTILITY_SRC)

include_directories(
	/usr/include
	/usr/local/include
	${SRC_DIR}/utility
	)

link_directories(
	/usr/include
	/usr/local/include
	)

add_library(Utility SHARED ${DIR_UTILITY_SRC})
