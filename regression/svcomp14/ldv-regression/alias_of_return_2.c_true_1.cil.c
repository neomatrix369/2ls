/* Generated by CIL v. 1.3.7 */
/* print_CIL_Input is true */

#line 13 "files/alias_of_return_2.c"
void err(void) 
{ 

  {
  ERROR: 
#line 14
  assert(0);
}
}
#line 16
extern int __VERIFIER_nondet_int() ;
#line 18 "files/alias_of_return_2.c"
int *return_self(int *p ) 
{ int tmp ;

  {
  {
#line 20
  tmp = __VERIFIER_nondet_int();
  }
#line 20
  if (tmp) {
#line 21
    return (p);
  } else {
#line 23
    return (p);
  }
}
}
#line 27 "files/alias_of_return_2.c"
int main(void) 
{ int a ;
  int *q ;

  {
#line 31
  a = 1;
#line 33
  q = & a;
#line 38
  *q = 2;
#line 40
  if (a != 2) {
    {
#line 40
    err();
    }
  } else {

  }
#line 41
  return (0);
}
}
