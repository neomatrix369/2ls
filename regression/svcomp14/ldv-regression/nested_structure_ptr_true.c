void __VERIFIER_assert(int cond) {
  if (!(cond)) {
    ERROR: assert(0);
  }
  return;
}

/* Complex lvalue assignment
 */

#include <assert.h>



typedef struct Toplev {
	int a;
	struct Inner {
		int b;
		struct Innermost{
			int c;
		} *y;
	} *x;
} Stuff;

int main()
{
	struct Innermost im = {3};
	struct Inner inner = {2, &im};
	struct Toplev good = { 1, &inner};
	struct Toplev *ptr = &good;
	ptr->x->y->c = 4;
	__VERIFIER_assert (ptr->x->y->c == 4);
	return 0;
}






