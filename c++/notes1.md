# Notes (Part 1)

## C++
  * Originally C++ was invented by Soustroup, who worked at Bell Labs
  * Originally compiled down to C, now no longer does—directly compiled to assembly
  * Mostly a superset of C that adds classes and a few other things

## Syntax
  * Normally don't use the `.h` for imports in C++ for std library, unless it's a file we're directly including.
  * `iostream` is the way you interact with I/O streams, such as terminal interaction (but not like random access files)
  * STDOUT => `std::cout`
    * `cout` is like a global variable in the `std` namespace. Holds an `iostream` object that corresponds to the output device (file, terminal, etc.)
  * C++ has namespacing for function names.
  * `std::count << "String";`
    * << sends a string to `cout`.
  * Iostream called `cin`.
  * To write a line from stdin to a string, use `std::getline(cin, name);`
  * You can elide namespaces by prefixing file with `using namespace *namespacename*;`
  * Operator overloading exists in C++, though not in C.
  * `int&` is like a pointer, except people can use it like the actual value (so people can use it without dereferencing)
  * `atoi` is the C-version of string conversion to `int`, whereas `stoi` is the C++ version.
  * Can namespace methods within a file using `namespace *namespace_name* { do stuff }`
  * `new` instantiates an object and calls constructor allocating to the heap, to allocate space on the stack and call constructor you just declare it.

## Types
  * The String class has a constructor from a `char*`. When you try to check equality with two strings, they will call the constructor to create a string from a char*.
  * This is not typecasting, this is **implicit conversion**.
  * When declaring a vector, you have to specify the template argument (usually a class) like so:
    * `vector<string> strings;`
  * `auto` says: infer the type

## Iteration
  * `iter = names.begin()` => gives an iterator object
  * `for (vector<string>::iterator iter = names.begin(); iter != names.end(); iter++) {
    string name = *iter;
    cout << name;
  }`
  * `for (auto iter = names.begin(); iter != names.end(); iter++) {
    string name = *iter;
    cout << name;
  }`
  * `for (string name : names)`
  * `for (string& name : names)`

## Classes
  * `class HVector`
  * class is almost synonymous with `struct` in C++.
  * If you say `struct`, the default is public, whereas with a class the default is `protected`. A.K.A. plain-old-data (POD).
  * Classes are declared and defined separately; declare in header file, then declare separately.
  * You use `new` instead of `malloc` to allocate space for a new object and run the constructor as well.

## Destructors
  * When names go out of scope, the destructor function will be called. These are designed to free/destroy each of the individual items, as well as deallocating the space.
  * You declare the destructor using `~ClassName();`
  * `delete` instead of `free`
  * Use `delete[]` to recursively delete elements within another element.
  * Pointers will not be freed, but objects that have their own destructors will be freed (like a string—even though it's a pointer, it'll be correctly de-allocated).
  * Automatically inserts destructor calls when a variable goes out of scope.

## Templates
  * Java—Type erasure: type constraints are only enforced at compile-time for generics
  * In C++, you declare a template like so:
  * `template<typename T>
    T max(T i T j) {
      return i > j ? i : j;
    }`
  * Have to declare the template immediately before the function you're defining for the template.
  * Declares a **templated function**.
  * Every time you use the template with a certain type, it will in the background generate a new `maxInt` macro for that particular type that you use.
  * If you never instantiate the template it is compiled out, so rename it to a `.tpp` file and then require it directly in the header.

## References
  * T& to refer to a reference
  * `push_back(3)` => this matches an argument for `int&`
  * A literal on the stack is known as an `rvalue`
  * An `lvalue` is a value that can be on the left side of an assignment.
  * `x = 3;`
    * `x` is an `lvalue`.
    * `3` is an `rvalue`.
  * `rvalue` references by default become `const references`.
  * Literals go onto the data segment
  * For literals to be accepted by a function, it must be a `const reference`.

## Include guards
  * In a header file, to avoid defining the same thing twice you can use an **include guard** like so:
    * `#ifndef HVEC_H`
    * `#define HVEC_H`
    * ...
    * `#endif`

## Built-in object operators
  * Copy constructor is called by:
    * `Hvec hvec2 = hvec1;`
    * `Hvec hvec2(hvec1);`
  * Copy constructor: `HVec(Hvec& hvec2) {
    _count = hvec2.count;
    _store = hvec2.store;
    etc.
  }`
  * Assignment operator is called by:
    * `Hvec hvec2`;
    * `hvec2 = hvec1;`
  * `Operator=(Hvec& hvec2) {
    same thing
  }`
