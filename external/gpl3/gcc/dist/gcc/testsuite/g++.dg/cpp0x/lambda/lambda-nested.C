// { dg-do "run" }
// { dg-options "-std=c++0x" }

#include <cassert>

struct A {
  int i;
  A(): i(42) { }
  int f() {
    return [this]{
      return [=]{ return i; }();
    }();
  }
};

int main() {
  int i = 1;

  [] (int& i) -> void {
    [&] () -> void {
      i = 2;
    } ();
  } (i);

  assert(i == 2);

  [&] () -> void {
    [&i] () -> void {
      i = 3;
    } ();
  } ();

  assert(i == 3);

  [&] () -> void {
    [&] () -> void {
      i = 4;
    } ();
  } ();

  assert(i == 4);
  i = 4;

  [&] () -> void {
    [=] () mutable -> void {
      i = 5;
    } ();
  } ();

  assert(i == 4);

  [=] () mutable -> void {
    [&] () -> void {
      i = 6;
    } ();
  } ();

  assert(i == 4);

  assert (A().f() == 42);

  return 0;
}
