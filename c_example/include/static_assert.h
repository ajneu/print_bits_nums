/* for compilers that don't have a least C11 and are thus missing _Static_assert */
/* see http://www.pixelbeat.org/programming/gcc/static_assert.html */


/* Compile-time "assert" -- force a compilation-error if CONDITION is false
                            (the size of array must be greater than zero)

   USAGE:   STATIC_ASSERT(CONDITION, unique_tag)

   EXAMPLE: 
            int arr[] = {1, 2, 3, 4, 5};
            STATIC_ASSERT((sizeof(arr)/sizeof(arr[0])) == 5, num_arr_items_is_5); // force compilation-error is arr does not have 5 elements
*/

#ifndef STATIC_ASSERT_H
#define STATIC_ASSERT_H


#define STATIC_ASSERT_VARIANT1
/* #define STATIC_ASSERT_VARIANT2 */





#ifdef STATIC_ASSERT_VARIANT1
/***************************************************************************/

#define GEN_ASSERT_NAME2(NAME, LINE, MSG) NAME##LINE##MSG
#define GEN_ASSERT_NAME1(NAME, LINE, MSG) GEN_ASSERT_NAME2(NAME, LINE, MSG)

#if 0

/*
// may produce the warning: variably modified ‘static_assert_Line54_CheckMsg_checkmax’ at file scope [enabled by default]
// when using e.g. STATIC_ASSERT(TYPE_MAXIMUM(unsigned long long, checkmax);
//
// can be avoided by using the other STATIC_ASSERT (after #else)
*/
#define STATIC_ASSERT(CONDITION, MSG) typedef char (GEN_ASSERT_NAME1(static_assert ## _Line, __LINE__, _CheckMsg_ ## MSG)) [1 - (2*(!(CONDITION)))]

#else

#define STATIC_ASSERT(CONDITION, MSG)                                                         enum {GEN_ASSERT_NAME1(enum_zzzz ## _Line, __LINE__, _CheckMsg_ ## MSG)=(CONDITION) }; \
    typedef char (GEN_ASSERT_NAME1(static_assert ## _Line, __LINE__, _CheckMsg_ ## MSG)) [1 - (2*(!(GEN_ASSERT_NAME1(enum_zzzz ## _Line, __LINE__, _CheckMsg_ ## MSG))))]

#endif



#elif defined STATIC_ASSERT_VARIANT2
/***************************************************************************/

/* http://www.pixelbeat.org/programming/gcc/static_assert.html */

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
/* These can't be used after statements in c89. */
#ifdef __COUNTER__
#define STATIC_ASSERT(e,m) \
  ;enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(!!(e)) }
#else
/* This can't be used twice on the same line so ensure if using in headers
 * that the headers are not included twice (by wrapping in #ifndef...#endif)
 * Note it doesn't cause an issue when used on same line of separate modules
 * compiled with gcc -combine -fwhole-program.  */
#define STATIC_ASSERT(e,m) \
  ;enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }
#endif


#else
/***************************************************************************/

#error **** Warning:Neiter STATIC_ASSERT_VARIANT1 nor STATIC_ASSERT_VARIANT2 defined *****

#endif



#endif /* STATIC_ASSERT_H */
