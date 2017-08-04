#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Animal {
public:
  virtual ~Animal() {};
  virtual void age(int) = 0;
  virtual string speak() = 0;
};

class Dog : public Animal {
protected:
  int _age;
  string _name;
public:
  Dog(int, string);
  ~Dog();
  void age(int) override;
  string speak() override;
};

class PuppyDog : public Dog {
public:
  PuppyDog(int, string);
  ~PuppyDog();
  string speak() override;
};

Dog::Dog(int age, string name) : _age(age), _name(name) {}

PuppyDog::PuppyDog(int age, string name) : Dog(age, name) {}

void Dog::age(int amt) {
  _age += amt;
}

string Dog::speak() {
  ostringstream stream;
  stream << "Hello I am " << _name << " and I am "<< _age << " days old.";
  return stream.str();
}

Dog::~Dog() {
  cout << "Dog is being destroyed!" << this << endl;
}

PuppyDog::~PuppyDog() {
  cout << "PuppyDog is being destroyed!" << this << endl;
}

string PuppyDog::speak() {
  ostringstream stream;
  stream << "bark bark bark " << _name << " bark "<< _age << " bark.";
  return stream.str();
}

int main() {
  Dog d(25, "Fido");
  PuppyDog pd(5, "Fido Jr.");
  Animal* dogp = &d;
  Animal& pdref = pd;
  Dog& pdref2 = pd;
  cout << dogp->speak() << "\n" << pdref.speak() << "\n" << pdref2.speak() << endl;
  
  vector<Animal*> animals;
  animals.push_back(dogp);
  animals.push_back(&pdref);
  animals.push_back(&pdref2);

  for (auto animal : animals) {
    cout << animal->speak();
  }
  cout << endl;

  Dog* dogPointer = new PuppyDog(25, "JJ");
  delete dogPointer;
  return 0;
}
