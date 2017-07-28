# Notes 3 — Structs

* Struct
  * C programs are just functions operating on structs
  * struct Point {
    double x;
    double y;
  };
  * To declare on the stack: `struct Point p1;`
    * Sets fields to default values to 0 in both cases.
  * p1.x = 123;
  * p2.y = 456;
  * Point.x means take address of `Point`, add 0, and a double lives there. That's what the struct signifies to the C compiler.
  * After compilation time, all of the struct information in your program is lost and thrown away. Nothing more is enforced at runtime.
  * When you return a struct, you do not return the reference, you return the entire value of the struct.
  * Assuming `p` is a pointer:
  * `(*p).x = val`
  * `p -> x = 37`
  * -> is property access through a pointer for a struct
  * Can define a struct like so: `Point p = { .x = 3, .y = 4 };`
  * `*p3 = addPoints(&p1, &p2);`:
    * Can do that to directly set a struct using another struct

## `typedef`
  * An alias for a struct, or any data type
  * `typedef int ned_int;`
    * Now instead of `int` I can say `ned_int`.
    * No other difference.
      * The reason historically we do this might be:
        * `typedef double feet;`
        * `typedef double meters;`
      * Does not enforce any strong typing here unfortunately.
* Can make an anonymous struct, like so:
  * Struct {
    fields
  }
  * typedef Struct {
    double x;
    double y;
  } Point;
    * Point p1;

## void pointers
  * A void pointer is basically how you avoid the restrictive type system. A void * points to who knows what??
  * Boxing: the void pointer points to some object, which may be a primitive object.
