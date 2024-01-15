#ifndef MODULE_H
# define MODULE_H
# include "../class.h"

#define inst(X)		X,
#define redecl(X)	typeof(X) X;

#define export(...)\
	(struct {\
		FOR_EACH(redecl, __VA_ARGS__)\
	}) {\
		FOR_EACH(inst, __VA_ARGS__)\
	};\
/*
#define export(...)\
	struct {\
		FOR_EACH(redecl, __VA_ARGS__)\
	}	CONCATENATE(output_module, __COUNTER__) = {\
		FOR_EACH(inst, __VA_ARGS__)\
	};\
*/
#endif
