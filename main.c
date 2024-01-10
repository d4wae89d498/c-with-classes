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
		printf("%i\n", this->y);
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

// Example usage
int main() {
    Optional opt = Optional_construct(71);

	_(&opt)->setData(42);


    printf("Data: %d, Empty: %d\n", opt.data, opt.empty);
    opt.clear();
    printf("Data: %d, Empty: %d\n", opt.data, opt.empty);
	opt.y = 6;
	opt.z = 3;
	opt.doo();


	printf("%i", opt.p);
	//opt.dopo();

    return 0;
}
