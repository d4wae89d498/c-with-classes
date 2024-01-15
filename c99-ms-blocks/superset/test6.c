#include <stdio.h>
printf("running...\n");

auto std1 = ({
	#include "std.c"
});

auto std2 = ({
	#include "std2.c"
});

auto	std = ({
	(struct
	{
		//int x;
		//int y;
		typeof (std1);
		//typeof (std)
	}) {std1.x, std1.y};
});

#include "std.c"

printf("ok : %i %i\n", std.x, std.y);
printf("ok : %i %i\n", x, y);
printf("%i", __COUNTER__);
printf("%i", __COUNTER__);
