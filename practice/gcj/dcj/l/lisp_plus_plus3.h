// Sample input 2, in CPP.

#include <cassert>

long long GetLength() {
  return 7LL;
}

char GetCharacter(long long index) {
  switch ((int)index) {
    case 0: return '(';
    case 1: return '(';
    case 2: return '(';
    case 3: return '(';
    case 4: return ')';
    case 5: return ')';
    case 6: return ')';
    default: assert(0);
  }
}
