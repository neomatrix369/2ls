/* Generated by CIL v. 1.3.7 */
/* print_CIL_Input is true */

#line 9 "nested_structure_ptr-safe.c"
struct Innermost {
   int c ;
};
#line 9 "nested_structure_ptr-safe.c"
struct Inner {
   int b ;
   struct Innermost *y ;
};
#line 9 "nested_structure_ptr-safe.c"
struct Toplev {
   int a ;
   struct Inner *x ;
};
#line 71 "/usr/include/assert.h"
extern  __attribute__((__nothrow__, __noreturn__)) void __assert_fail(char const   *__assertion ,
                                                                      char const   *__file ,
                                                                      unsigned int __line ,
                                                                      char const   *__function ) ;
#line 7 "nested_structure_ptr-safe.c"

#line 19 "nested_structure_ptr-safe.c"
int main(void) 
{ struct Innermost im ;
  struct Inner inner ;
  struct Toplev good ;
  struct Toplev *ptr ;
  struct Innermost *__cil_tmp5 ;
  struct Inner *__cil_tmp6 ;
  unsigned int __cil_tmp7 ;
  struct Toplev *__cil_tmp8 ;
  unsigned int __cil_tmp9 ;
  unsigned int __cil_tmp10 ;
  unsigned int __cil_tmp11 ;
  struct Inner *__cil_tmp12 ;
  unsigned int __cil_tmp13 ;
  unsigned int __cil_tmp14 ;
  struct Innermost *__cil_tmp15 ;
  unsigned int __cil_tmp16 ;
  unsigned int __cil_tmp17 ;
  struct Inner *__cil_tmp18 ;
  unsigned int __cil_tmp19 ;
  unsigned int __cil_tmp20 ;
  struct Innermost *__cil_tmp21 ;
  int __cil_tmp22 ;

  {
#line 21
  __cil_tmp5 = & im;
#line 21
  *((int *)__cil_tmp5) = 3;
#line 22
  __cil_tmp6 = & inner;
#line 22
  *((int *)__cil_tmp6) = 2;
#line 22
  __cil_tmp7 = (unsigned int )(& inner) + 4;
#line 22
  *((struct Innermost **)__cil_tmp7) = & im;
#line 23
  __cil_tmp8 = & good;
#line 23
  *((int *)__cil_tmp8) = 1;
#line 23
  __cil_tmp9 = (unsigned int )(& good) + 4;
#line 23
  *((struct Inner **)__cil_tmp9) = & inner;
#line 24
  ptr = & good;
#line 25
  __cil_tmp10 = (unsigned int )ptr;
#line 25
  __cil_tmp11 = __cil_tmp10 + 4;
#line 25
  __cil_tmp12 = *((struct Inner **)__cil_tmp11);
#line 25
  __cil_tmp13 = (unsigned int )__cil_tmp12;
#line 25
  __cil_tmp14 = __cil_tmp13 + 4;
#line 25
  __cil_tmp15 = *((struct Innermost **)__cil_tmp14);
#line 25
  *((int *)__cil_tmp15) = 4;
  {
#line 26
  __cil_tmp16 = (unsigned int )ptr;
#line 26
  __cil_tmp17 = __cil_tmp16 + 4;
#line 26
  __cil_tmp18 = *((struct Inner **)__cil_tmp17);
#line 26
  __cil_tmp19 = (unsigned int )__cil_tmp18;
#line 26
  __cil_tmp20 = __cil_tmp19 + 4;
#line 26
  __cil_tmp21 = *((struct Innermost **)__cil_tmp20);
#line 26
  __cil_tmp22 = *((int *)__cil_tmp21);
#line 26
  if (__cil_tmp22 == 4) {

  } else {
    {
#line 26
    //__assert_fail("ptr->x->y->c == 4", "nested_structure_ptr-safe.c", 26U, "main");
    ERROR: assert(0);
    }
  }
  }
#line 27
  return (0);
}
}
