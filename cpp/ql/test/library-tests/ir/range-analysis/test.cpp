#include "test_util.h"
  int f1(int x, int y) {
    if (x < 500) {
      if (x > 400) {
        range(x);  // $ range=>=401 range=<=499
        return x;
      }

      if (y - 2 == x && y > 300) { // $ overflow=-
        range(x + y);  // $ range=<=802 range=>=600
        return x + y;
      }

      if (x != y + 1) { // $ overflow=+
        range(x);  // $ range=<=400
        int sum = x + y; // $ overflow=+-
      } else {
        if (y > 300) {
          range(x); // $ range=>=302 range=<=400 range=<=y+1 MISSING: range===y+1
          range(y); // $ range=>=301 range=<=399 range===x-1
          int sum = x + y;
        }
      }

      if (x > 500) {
        range(x); // $ range=<=400 range=>=501
        return x;
      }
    }

    return 0;
  }

  int f2(int x, int y, int z) {
    if (x < 500) {
      if (x > 400) {
        range(x);  // $ range=>=401 range=<=499
        return x;
      }

      if (y == x - 1 && y > 300 && y + 2 == z && z == 350) { // $ overflow=+ overflow=-
        range(x);  // $ range===349 range===y+1 range===z-1
        range(y);  // $ range===348 range=>=x-1 range===z-2 MISSING: range===x-1 
        range(z);  // $ range===350 range=<=y+2 MISSING: range===x+1 range===y+2
        return x + y + z;
      }
    }

    return 0;
  }

