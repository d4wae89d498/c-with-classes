#include "class.h"

class (Foo,, {
		int	z;
	},
	((int x),
		printf("Foo constructed! (%i)\n", x);
		this->z = x;
	),
	(void, dumpZ, (),
		printf("this->z %i\n", this->z);
	)
)

class (Base extends Foo,
	{
		int y;
	},
	((int x),
		printf("Base constructed with %i %p!\n", x, this);
		this->y = x;
		super(2 * x);
	),
	(void, dumpY, (),
		printf("this->y %i\n", this->y);
	)
)

class (Optional extends Base,
	{
		int x;
	},
	((int x),
		printf("Base constructed with %i %p!\n", x, this);
		this->x = x;
		super(2 * x);
	),
	(void, dumpX, (),
		printf("this->x %i\n", this->x);
	)
)


int main() {
	auto x = Optional_construct(8);

	x->dumpX();

	x->dumpY();

	x->dumpZ();

    return 0;
}
