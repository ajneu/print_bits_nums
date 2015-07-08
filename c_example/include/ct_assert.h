/* Compile-time "assert" -- force a compilation-error if CONDITION is false
                            (the size of array must be greater than zero)

   USAGE:   CT_ASSERT1(CONDITION, unique_tag)

   EXAMPLE: 
            int arr[] = {1, 2, 3, 4, 5};
            CT_ASSERT1((sizeof(arr)/sizeof(arr[0])) == 5, num_arr_items_is_5); // force compilation-error is arr does not have 5 elements
*/

#ifndef CT_ASSERT_H
#define CT_ASSERT_H

#define GEN_ASSERT_NAME2(NAME, LINE, MSG) NAME##LINE##MSG
#define GEN_ASSERT_NAME1(NAME, LINE, MSG) GEN_ASSERT_NAME2(NAME, LINE, MSG)

#if 0

// may produce the warning: variably modified ‘static_assert_Line54_CheckMsg_checkmax’ at file scope [enabled by default]
// when using e.g. CT_ASSERT1(TYPE_MAXIMUM(unsigned long long, checkmax);
//
// can be avoided by using the other CT_ASSERT1 (after #else)
#define CT_ASSERT1(CONDITION, MSG) typedef char (GEN_ASSERT_NAME1(static_assert ## _Line, __LINE__, _CheckMsg_ ## MSG)) [1 - (2*(!(CONDITION)))]

#else

#define CT_ASSERT1(CONDITION, MSG)                                                            enum {GEN_ASSERT_NAME1(enum_zzzz ## _Line, __LINE__, _CheckMsg_ ## MSG)=(CONDITION) }; \
    typedef char (GEN_ASSERT_NAME1(static_assert ## _Line, __LINE__, _CheckMsg_ ## MSG)) [1 - (2*(!(GEN_ASSERT_NAME1(enum_zzzz ## _Line, __LINE__, _CheckMsg_ ## MSG))))]

#endif

#endif /* CT_ASSERT_H */
