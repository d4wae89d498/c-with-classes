all:
#	cc main.c
	cc -g -fsanitize=address -fms-extensions -Wno-microsoft-anon-tag main.c
