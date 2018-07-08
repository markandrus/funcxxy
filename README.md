funcxxy
=======

_**<u>Fun</u>**ctional C++ (**<u>CXX</u>**) Librar**<u>y</u>** (pronounced "funky")_

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
* Either
* Validation

### Operators

* `%` (map)
* `*` (apply)
* `|` (or)

### Miscellaneous

* `curry`

Motivation
----------

Why would you ever want to use this library? Well, if you've used libraries like
[optparse-applicative](http://hackage.haskell.org/package/optparse-applicative)
or [aeson](http://hackage.haskell.org/package/aeson) in Haskell or
[circe](https://circe.github.io/circe) in Scala, then you may be familiar with
the Applicative and Alternative type classes. These type classes can be really
useful for writing concise parsers and validators. In fact, this library was
extracted from [node-webrtc](https://github.com/js-platform/node-webrtc) where
it was used to marshall data between C++ and JavaScript. To see an example of
what I mean, check out the [example](example) project.
