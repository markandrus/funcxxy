funcxxy
=======

_**Fun**ctional C++ (**CXX**) Librar**y** (pronounced "funky")_

Example
-------

```cpp
#include <funcxxy/funcxxy.h>

using namespace funcxxy;

static int add3(int a, int b, int c) {
  return a + b + c;
}

static void test() {
  auto result = curry(add3)
    % Just(1)
    * Just(2)
    * Just(3);
}
```

Features
--------

### Data Types

* Maybe

### Operators

* `%` (map)
* `*` (apply)
* `|` (or)

### Miscellaneous

* `curry`
