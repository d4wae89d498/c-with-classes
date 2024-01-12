#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <Block.h>

__thread void *prev_ptr = NULL;
__thread void *g_this = NULL;
void	*_assign_instance(void *i)
{
	g_this = i;
	return i;
}

#define auto __auto_type

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2


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
#define FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__))
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

#define FOR_EACH2_1(what, extra_arg, x) what(extra_arg, x)
#define FOR_EACH2_2(what, extra_arg, x, ...) what(extra_arg, x) EXPAND(FOR_EACH2_1(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_3(what, extra_arg, x, ...) EXPAND(what(extra_arg, x)) EXPAND(FOR_EACH2_2(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_4(what, extra_arg, x, ...) what(extra_arg, x) EXPAND(FOR_EACH2_3(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_5(what, extra_arg, x, ...) what(extra_arg, x) EXPAND(FOR_EACH2_4(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2_(N, what, extra_arg, ...) EXPAND(CONCATENATE(FOR_EACH2_, N)(what, extra_arg, __VA_ARGS__))
#define FOR_EACH2(what, extra_arg, ...) FOR_EACH2_(FOR_EACH_NARG(__VA_ARGS__), what, extra_arg, __VA_ARGS__)

#define COUNT_ARGS_HELPER(_0, _1, _2, _3, _4, _5, N, ...) N
#define COUNT_ARGS(...) COUNT_ARGS_HELPER(dummy, ##__VA_ARGS__, 5, 4, 3, 2, 1, 0)
#define IF_ARGS_1(...) __VA_ARGS__
#define IF_ARGS_0(...)
#define IF_ARGS(ARGS, ...) CALL(CALL(CONCATENATE, IF_ARGS_, COUNT_ARGS ARGS), __VA_ARGS__)



#define FIRST_ARG(X, ...) X
#define REST_ARGS(X, ...) __VA_ARGS__

#define class(...) _class(__VA_ARGS__)

#define super(...)\
	(parent = __parent_constructor(__VA_ARGS__))

#define STR(X) #X

__thread void	*g_root = NULL;

// TODO : better constructors. Handle cases like useless alloc for parents, and other class construct in constructors
#define _class(class_name, parent_class_name, properties, constructor, ...) \
    typedef struct class_name class_name; \
	struct  class_name {\
			IF_ARGS((parent_class_name), struct parent_class_name;)\
			struct properties; \
			FOR_EACH(METHOD_PROTO, __VA_ARGS__) \
	}; \
    class_name *class_name##_construct CALL(FIRST_ARG, UNPACK constructor) { \
		__block class_name * this = malloc(sizeof(class_name));\
		IF_ARGS((parent_class_name), \
			typeof(parent_class_name ## _construct) * __parent_constructor = & parent_class_name ## _construct;\
			parent_class_name *parent;\
		);\
       FOR_EACH(METHOD_SET, __VA_ARGS__) \
	   CALL(REST_ARGS, UNPACK constructor)\
	   IF_ARGS((parent_class_name), \
	   		printf("parent copied from %s (%p) to %s (%p)\n", STR(parent_class_name), this, STR(class_name), parent);\
			memcpy(this, parent, sizeof(parent_class_name));\
		);\
	   return this;\
    }
#define METHOD_PROTO(method_def) \
    EXPAND(METHOD_PROTO_ method_def)
#define METHOD_PROTO_(ret_type, name, args, ...) \
    typeof(^ ret_type args { (void)4;  }) name;

// TODO : better abstraction and naming for MERGE_ARGS

#define COMMA_0
#define COMMA_1 ,
#define COMMA_2 ,
#define COMMA_3 ,
#define COMMA_4 ,
#define COMMA_5 ,
#define MERGE_ARGS(first, ...)\
	first CONCATENATE(COMMA_, COUNT_ARGS(__VA_ARGS__)) __VA_ARGS__



#define METHOD_SET(method_def) \
	EXPAND(CALL(METHOD_SET_, UNPACK(EXPAND(UNPACK method_def))))

#define METHOD_SET_(ret_type, name, args, ...) \
    this->name = Block_copy(^ ret_type args {\
		__VA_ARGS__\
	});
#define extends ,


/////
