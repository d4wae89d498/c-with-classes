all:
	make -C c99
	make -C c99-ms
	make -C c99-ms-blocks

clean:
	make clean -C c99
	make clean -C c99-ms
	make clean -C c99-ms-blocks

