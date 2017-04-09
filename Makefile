SRC_DIRS=bubble

all:
	@for dir in ${SRC_DIRS};					\
		do										\
			echo "[making in $$dir]";			\
			make -C $$dir;						\
		done
