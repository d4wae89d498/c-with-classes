#!./crun "-O3 "

auto std = ({
	#include "test.c"
});

//#include "std/_print"

std.g();
std.g();
std.g();
std.g();

printf("%s\n", argv[0]);
printf("-> %i\n", *std.x);
