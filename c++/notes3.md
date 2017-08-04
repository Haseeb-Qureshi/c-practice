# Notes (part 3)

## Destructors
* Are automatically called (recursively on instance variables) when an object goes out of scope.
* Tricky cases: pointers, mutexes.
* Mutex:
  * `std::mutex m;
     void f() {
       std::lock.guardlk(m);
       // do stuff
     }

     void f() {
       m.lock();
       // do stuff
       m.unlock();
     }
  `
    * Mutex lock is a system call which basically says: "don't wake me up until the lock is now available."
    * RAIT — resource acquisition is initialization
      * This means when you acquire a resource, that should correspond to initializing some object. That object, when it goes out of scope (even during an exception), it will call the destructor which will release the resource.
* Has to call the parent destructor as well when it runs the destructor.

## Unique Pointers
* `unique_ptr<Dog> dp(&dog);`
* As part of destruction, the object is deleted.
* Only use unique pointers, not regular pointers.
* `shared_ptr<x>` <= contains a reference count.
* Don't do this.
* `move` is used to force a variable to be treated as an rvalue reference, this can be used to turn off the effective child-lock that C++ puts on pointers.

## Libraries
* Boost—the stuff the standard library left out, slowly incorporated into the standard library.

## Lambdas
* want to do :
* `int sum;
   each(is, [](int amt) { sum += amt });
   vector.map();`
* `[=](int amt) { sum += amt };` => captures by value
* `[&](int amt) { sum += amt };` => captures by pointer
* `[&sum](int amt) { sum += amt };` => captures `sum` by pointer
* `auto f = [&sum](int amt) { sum += amt };` => only way to create a reference to a lambda.

## Threads
* `std::thread t(func, ...args);`
* `t.join()` to join it back (and not immediately exit on program termination)

## Futures vs Promises
* In JS you create a new promise as `f(resolve, error) => do stuff, resolve() or error()`
