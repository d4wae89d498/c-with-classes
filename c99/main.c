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
		this->p = p;
		printf("Optional constructed!\n");
		super(4);
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
    with (Optional_construct(71) as opt,
		opt.clear();
		opt.parent.y = 6;
		opt.parent.parent.z = 3;
		opt.parent.doo();
		with (Optional_construct(4) as file,
			file.parent.y = 85;
			file.parent.doo();
		)
		opt.parent.doo();
	)
    return 0;
}
