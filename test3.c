#include <stdbool.h>
#include <stdio.h>


/*

	TODO :
		- Remove 'Optional' // for each with 2 args or other way ... done
		- public/private --> no
		- if one args. count arg to perform replacement using macros for extends ... done

*/

void *g_this = NULL;

void	*_assign_instance(void *i)
{
	g_this = i;
	return i;
}

#define _(X) ((typeof(X)) _assign_instance(X))

#define CONCAT_IMPL(x, y) x ## y
#define CONCAT(x, y) CONCAT_IMPL(x, y)
#define CALL(NAME, ...) NAME(__VA_ARGS__)
#define EXPAND(X) X
#define UNPACK(...) __VA_ARGS__
#define IF_ONE_ARG(ARGS, ...)
#define FOR_EACH_1(what, x) what(x)
#define FOR_EACH_2(what, x, ...) what(x) EXPAND(FOR_EACH_1(what, __VA_ARGS__))
#define FOR_EACH_3(what, x, ...) EXPAND(what(x)) EXPAND(FOR_EACH_2(what, __VA_ARGS__))
#define FOR_EACH_4(what, x, ...) what(x) EXPAND(FOR_EACH_3(what, __VA_ARGS__))
#define FOR_EACH_5(what, x, ...) what(x) EXPAND(FOR_EACH_4(what, __VA_ARGS__))
#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, N, ...) N
#define FOR_EACH_RSEQ_N() 5, 4, 3, 2, 1
#define FOR_EACH_(N, what, ...) EXPAND(CONCAT(FOR_EACH_, N)(what, __VA_ARGS__))
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

#define FOR_EACH2_1(what, extra_arg, x) what(extra_arg, x)
#define FOR_EACH2_2(what, extra_arg, x, ...) what(extra_arg, x) EXPAND(FOR_EACH2_1(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_3(what, extra_arg, x, ...) EXPAND(what(extra_arg, x)) EXPAND(FOR_EACH2_2(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_4(what, extra_arg, x, ...) what(extra_arg, x) EXPAND(FOR_EACH2_3(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_5(what, extra_arg, x, ...) what(extra_arg, x) EXPAND(FOR_EACH2_4(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_(N, what, extra_arg, ...) EXPAND(CONCAT(FOR_EACH2_, N)(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2(what, extra_arg, ...) FOR_EACH2_(FOR_EACH_NARG(__VA_ARGS__), what, extra_arg, __VA_ARGS__)

#define COUNT_ARGS_HELPER(_0, _1, _2, _3, _4, _5, N, ...) N
#define COUNT_ARGS(...) COUNT_ARGS_HELPER(dummy, ##__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define IF_ARGS_1(X) X
#define IF_ARGS_0(X)
#define IF_ARGS(ARGS, EXPR) CALL(CALL(CONCAT, IF_ARGS_, CALL(COUNT_ARGS, EXPAND(UNPACK ARGS))), EXPR)

#include <string.h>

#define class(...) _class(__VA_ARGS__)
#define _class(class_name, parent_class_name, properties, ...) \
    typedef struct class_name class_name; \
	struct  class_name {\
			IF_ARGS((parent_class_name), struct parent_class_name;)\
			struct properties; \
			FOR_EACH(METHOD_PROTO, __VA_ARGS__) \
	}; \
	FOR_EACH2(METHOD_IMPL, class_name, __VA_ARGS__)\
    class_name class_name##_construct(){ \
		class_name instance;\
		IF_ARGS((parent_class_name), \
			parent_class_name parent = parent_class_name ## _construct();\
			memcpy(&instance, &parent, sizeof(parent_class_name));\
		);\
       FOR_EACH(METHOD_SET, __VA_ARGS__) \
	   /* if one args. set parent method. */ \
	   return instance;\
    }
#define METHOD_PROTO(method_def) \
    EXPAND(METHOD_PROTO_ method_def)
#define METHOD_PROTO_(ret_type, name, args, ...) \
    ret_type (*name) args;

#define METHOD_IMPL(class_name, method_def)\
	EXPAND(CALL(METHOD_IMPL_, class_name, UNPACK(EXPAND(UNPACK method_def))))\

#define METHOD_IMPL_(class_name, ret_type, name, args, ...)\
    ret_type name args\
	{\
		class_name *this = g_this;\
		__VA_ARGS__\
	}
#define METHOD_SET(method_def) \
    EXPAND(METHOD_SET_ method_def)
#define METHOD_SET_(ret_type, name, args, ...) \
    instance.name = name;



/////////////
#define public struct
#define private struct
/*

	class (Type,
		public {

		}

		private {

		}
	)

*/

#define extends ,


/////

class (Foo,, {
		int	z;
	},
	(void, dopo, (),
		printf("%d\n", this->z);
	)
)

class (Base extends Foo,
	{
		int y;
	},
	(void, doo, (),
		printf("%i\n", this->y);
	)
)

class (Optional extends Base,
    {
        int 	data;
        bool 	empty;
    },
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
    Optional opt = Optional_construct();


	_(&opt)->setData(42);
    printf("Data: %d, Empty: %d\n", opt.data, opt.empty);
    opt.clear();
    printf("Data: %d, Empty: %d\n", opt.data, opt.empty);
	opt.y = 6;
	opt.z = 3;
	opt.doo();
	opt.dopo();

    return 0;
}
