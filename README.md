Limitations :

- pas d'héritage multiple
- pas de public / private
- manually reset 'this' pointer using _(instance)
- rely on cc -fms-extensions flag (or 'parent' will have to be explicit)

Tested under both GCC and Clang.
