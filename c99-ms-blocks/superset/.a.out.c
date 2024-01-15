
#include "module.h"

int main()
{

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
		union
		{
			typeof (std1);
			typeof (std1) module;
		};
		//typeof (std)
	}) {.module = std1};
});

#include "std.c"

printf("ok : %i %i\n", std.x, std.y);
printf("ok : %i %i\n", x, y);
printf("%i", __COUNTER__);
printf("%i", __COUNTER__);
}

