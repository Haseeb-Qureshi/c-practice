#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct animalVTable;
typedef struct animalVTable AnimalVTable;

typedef struct {
  const AnimalVTable* vtable;
} Animal;

struct animalVTable {
  void (*age)(Animal*, int);
  void (*speak)(Animal*);
  void (*destroy)(Animal*);
};

typedef struct {
  const AnimalVTable* vtable;
  char* name;
  int age;
} Dog;

void dogAge(Dog* dog, int increment) {
  dog->age += increment;
}

void dogSpeak(Dog* dog) {
  printf("%s: %d\n", dog->name, dog->age);
}

void dogDestroy(Dog* dog) {
  free(dog->name);
  printf("Dog name is freed\n");
  free(dog);
}

const AnimalVTable dogVTable = {
  .age = (void (*)(Animal*, int)) dogAge,
  .speak = (void (*)(Animal*)) dogSpeak,
  .destroy = (void (*)(Animal*)) dogDestroy
};

Dog* dogNew(char* name) {
  Dog* dog = malloc(sizeof(Dog));
  *dog = (Dog) {
    .vtable = &dogVTable,
    .name = name
  };

  return dog;
}

void animalAge(Animal* animal, int increment) {
  animal->vtable->age(animal, increment);
}

void animalSpeak(Animal* animal) {
  animal->vtable->speak(animal);
}

void animalDestroy(Animal* animal) {
  animal->vtable->destroy(animal);
}

// Cat

typedef struct {
  const AnimalVTable* vtable;
  char* name;
  int age;
  char* skill;
} Cat;

void catAge(Cat* cat, int increment) {
  cat->age += increment;
}

void catSpeak(Cat* cat) {
  printf("%s: %d, %s\n", cat->name, cat->age, cat->skill);
}

void catDestroy(Cat* cat) {
  free(cat->name);
  printf("Cat name is freed\n");
  free(cat->skill);
  free(cat);
}

const AnimalVTable catVTable = {
  .age = (void (*)(Animal*, int)) catAge,
  .speak = (void (*)(Animal*)) catSpeak,
  .destroy = (void (*)(Animal*)) catDestroy
};

Cat* catNew(char* name, char* skill) {
  Cat* cat = malloc(sizeof(Cat));
  *cat = (Cat) {
    .vtable = &catVTable,
    .name = name,
    .skill = skill
  };

  return cat;
}

int main() {
  char* name = malloc(255);
  strcpy(name, "Fido");
  Dog* d = dogNew(name);

  char* catName = malloc(255);
  strcpy(catName, "Mr. Cat");
  char* skill = malloc(255);
  strcpy(skill, "Purring");
  Cat* c = catNew(catName, skill);

  // Animal* animals[2];
  // animals[0] = (Animal*) d;
  // animals[1] = (Animal*) c;
  //
  // for (int i = 0; i < 2; i++) {
  //   animalAge(animals[i], 2);
  //   animalSpeak(animals[i]);
  //   animalDestroy(animals[i]);
  // }

  Animal animals[2];
  animals[0] = *((Animal*) d);
  animals[1] = *((Animal*) c);

  for (int i = 0; i < 2; i++) {
    animalAge(&animals[i], 2);
    animalSpeak(&animals[i]);
    animalDestroy(&animals[i]);
  }

}
