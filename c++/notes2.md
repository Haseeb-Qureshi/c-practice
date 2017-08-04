# Notes (Part 2)

## Inheritance in C++
  * `virtual void age(int) = 0;`
  * `virtual string speak() = 0;`
  * This makes methods virtual.
  * For child:
  * `class Dog : public Animal {
      public:
        void age() override;
        string speak() override;
    }`
  * `Animal* a = new Dog("fido")`
  * `a->speak();`
  * A **pure virtual** function is one that points to 0.
