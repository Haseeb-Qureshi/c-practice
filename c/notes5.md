# Notes (part 5)

## Dynamic dispatch
  * Can define a function like so in a struct: `void (*eat) (Animal*);`
  * This constructs a "function table".
  * Then all structs that inherit from this interface, they will include a vtable with different pointers to functions as their first field in the struct.
  * `Dog dogNew(char* name) {
      return (Dog) {
        .vtable = dogVtable (which is a const),
        .name = name
      };
    }`
  * `void animalEat(Animal* a) {
      a->vtable.eat(a);
    }`
  * This is known as type punning—casting to another type of struct and treating them as though they're the same because they're laid out in memory identically.
