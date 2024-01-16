#ifndef MODULE_H
# define MODULE_H
# include "../c99-ms-blocks/class.h"
# include <gc.h>
# include "stdlib.h"
# define inst(X)		X,
# define redecl(X)	typeof(X) X;
# define tant
# define vide void
# define entier int
# define hérite
# define classe class
# define de extends
# define retourner return
# define que(x, ...) while (x) { __VA_ARGS__ }
# define si(cond, ...) if (cond) { __VA_ARGS__ }
# define else(...) else { __VA_ARGS__ }
# define lambda(type, args, body)\
	^ type args { body }
# define fonction(type, name, args, body)\
	auto name = ^type args { body };
# define locale(name, value)\
	auto name = value;
# define globale(name, value)\
	typeof(value) *const name = GC_MALLOC(sizeof(value));\
	if (name == NULL)\
		exit(!!printf("memory full %p.", name));\
	*name = value;
# define constante(name, value)\
	const auto name = value;
# define exporter(...)\
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
