#include "class.h"

class (Foo,, {
		int	z;
	},
	((),
		printf("Foo constructed!\n");
	),
	(void, dopo, (),
		printf("%d\n", this->z);
	)
)

class (Base extends Foo,
	{
		int y;
	},
	((int x),
		printf("Base constructed with %i!\n", x);
		this->y = x;
		super();
	),
	(void, doo, (),
		printf("doo() %i\n", this->y);
	)
)

class (Optional extends Base,
    {
        int 	data;
        bool 	empty;
		int 	p;
    },
	((int p),
	//	this->p = p;
		printf("Optional constructed!\n");
		auto x = super(4);
		printf("parent_y = %i\n", x->y);
	),
    (void, setData, (int data),
        this->data = data;
        this->empty = false;
    ),
    (void, clear, (),
        this->data = 0;
        this->empty = true;
    )
)

int main() {

	auto x = Optional_construct(8);

	x->doo();
	auto y = Foo_construct();

	auto z = Base_construct(2);
    return 0;
}
