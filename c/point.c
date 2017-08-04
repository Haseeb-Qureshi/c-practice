#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x;
  double y;
} Point;

Point createPoint(double x, double y) {
  Point p;
  p.x = x;
  p.y = y;
  return p;
}

Point* allocPoint() {
  Point* p = malloc(sizeof(Point));
  return p;
}

void initializePoint(Point* p, double x, double y) {
  p->x = x;
  p->y = y;
}

Point* newPoint(double x, double y) {
  Point* p = allocPoint();
  initializePoint(p, x, y);
  return p;
}

Point addPoints(Point p1, Point p2) {
  return {
    .x = p1.x + p2.x,
    .y = p1.y + p2.y
  };
}

void addPointsInto(Point* p1, Point* p2, Point* p3) {
  *p3 = addPoints(&p1, &p2);
}

int main() {
  Point p;
  initializePoint(&p, 3.0, 4.0);
  Point p1 = { .x = 3, .y = 4 };
}
