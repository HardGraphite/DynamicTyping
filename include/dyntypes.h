#pragma once

#if defined __GNUC__
# ifdef _GHL_BUILD_DL
#   define HGL_DT_API __attribute__((visibility("default")))
# else
#   define HGL_DT_API
# endif
#elif defined _MSC_VER
# ifdef _GHL_BUILD_DL
#   define HGL_DT_API __declspec(dllexport)
# else
#   define HGL_DT_API __declspec(dllimport)
# endif
#else
#   define HGL_DT_API
#endif

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
# include <type_traits>
#else
// # include <stdbool.h>
# define bool  _Bool
# define true  1
# define false 0
// # include <assert.h>
# define static_assert _Static_assert
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* --- --- --- --- --- types --- --- --- --- --- */

typedef size_t      Dt_Size;   ///< size type
typedef bool        Dt_Bool;   ///< bool type
typedef int64_t     Dt_Int;    ///< integral type
typedef double      Dt_Float;  ///< floating-point type
typedef const char *Dt_Str;    ///< c-style string type

/// general method names (enum)
typedef enum _Dt_Method
{
    __Dt_M_0__    = 0,
    Dt_M_ToBool   = 1,  ///< [0] convert to bool (-> bool)
    Dt_M_ToInt    = 2,  ///< [0] convert to int (-> int)
    Dt_M_ToFloat  = 3,  ///< [0] convert to float (-> float)
    Dt_M_ToStr    = 4,  ///< [0] convert to str (-> str)
    Dt_M_Length   = 5,  ///< [0] get length (-> int)
    Dt_M_Hash     = 6,  ///< [0] get hash (-> int)
    Dt_M_Clone    = 7,  ///< [0] clone (-> old type)
    Dt_M_DClone   = 8,  ///< [0] deep clone (-> old type)
    Dt_M_IncRef   = 9,  ///< [0] inc-ref (-> old type)
    Dt_M_DecRef   = 10, ///< [0] dec-ref (-> nil)
    Dt_M_Delete   = 11, ///< [0] delete (-> nil)
    __Dt_M_0E__   = 12,

    __Dt_M_1__    = 32,
    Dt_M_Add      = 33, ///< [1] `+`
    Dt_M_Sub      = 34, ///< [1] `-`
    Dt_M_Mul      = 35, ///< [1] `*`
    Dt_M_Div      = 36, ///< [1] `/`
    Dt_M_Pow      = 37, ///< [1] `**`
    Dt_M_Rem      = 38, ///< [1] `%`
    Dt_M_Shl      = 39, ///< [1] `<<`
    Dt_M_Shr      = 40, ///< [1] `>>`
    Dt_M_BitAnd   = 41, ///< [1] `&`
    Dt_M_BitOr    = 42, ///< [1] `|`
    __Dt_M_1E__   = 43,

    __Dt_M_2__    = 64,
    __Dt_M_2E__   = 64,
} Dt_Method;

struct _Dt_Value;
typedef struct _Dt_Value * (*_Dt_MethodFn0_)(struct _Dt_Value *);
typedef struct _Dt_Value * (*_Dt_MethodFn1_)(struct _Dt_Value *, struct _Dt_Value *);
typedef struct _Dt_Value * (*_Dt_MethodFn2_)(struct _Dt_Value *, struct _Dt_Value *, struct _Dt_Value *);

/// type meta
typedef struct _Dt_Type
{
    const char *    name;
    _Dt_MethodFn0_  _m0[__Dt_M_0E__ - __Dt_M_0__];
    _Dt_MethodFn1_  _m1[__Dt_M_1E__ - __Dt_M_1__];
    _Dt_MethodFn2_  _m2[__Dt_M_2E__ - __Dt_M_2__];
} Dt_Type;

/// value
typedef struct _Dt_Value
{

/**
 * @brief common head of values
 * @details
 *  _rc: reference count,
 *  _tm: type meta.
 */
#define __DT_VALUE_HEAD__ \
    Dt_Size   _rc; \
    Dt_Type * _tm; \
// __DT_VALUE_HEAD__

    __DT_VALUE_HEAD__
} Dt_Value, * Dt_ValuePtr;

/* --- --- --- --- value creating, using and deleting --- --- --- --- */

HGL_DT_API extern Dt_ValuePtr Dt_Nil;
HGL_DT_API extern Dt_ValuePtr Dt_True, Dt_False;

HGL_DT_API extern Dt_ValuePtr Dt_newBool(Dt_Bool b);
HGL_DT_API extern Dt_ValuePtr Dt_newInt(Dt_Int i);
HGL_DT_API extern Dt_ValuePtr Dt_newFloat(Dt_Float f);
HGL_DT_API extern Dt_ValuePtr Dt_newStr(Dt_Str s);
HGL_DT_API extern Dt_ValuePtr Dt_newStrN(Dt_Str s, Dt_Size len);

/**
 * @brief create a list
 * 
 * @param len length of the list
 * @param ... Dt_ValuePtr type values, ending with NULL
 * @return a list value
 */
HGL_DT_API extern Dt_ValuePtr Dt_newList(Dt_Size len, ...);

#ifndef __cplusplus

/**
 * @brief create a new Dt_Value (generic)
 * @param X value of type bool, int, float or const char *
 */
#define Dt_newValue(X) \
    _Generic((X), \
        bool    : Dt_newBool, \
        uint8_t : Dt_newInt,  \
        uint16_t: Dt_newInt,  \
        uint32_t: Dt_newInt,  \
        uint64_t: Dt_newInt,  \
        int8_t  : Dt_newInt,  \
        int16_t : Dt_newInt,  \
        int32_t : Dt_newInt,  \
        int64_t : Dt_newInt,  \
        float   : Dt_newFloat,\
        double  : Dt_newFloat,\
        Dt_Str  : Dt_newStr   \
    )(X) \
// Dt_newValue

#else // __cplusplus

}

template <typename T> inline Dt_ValuePtr Dt_newValue(T X) noexcept
{
    if constexpr (std::is_same<T, Dt_Bool>::value)
        return Dt_newBool(X);
    else if constexpr (std::is_integral<T>::value)
        return Dt_newInt(X);
    else if constexpr (std::is_floating_point<T>::value)
        return Dt_newFloat(X);
    else if constexpr (std::is_convertible<T, const char*>::value)
        return Dt_newStr(X);
    else
    {
        static_assert(std::is_same<T, Dt_ValuePtr>::value, "invalid T");
        return X;
    }
}

/// literals
namespace DtLiterals
{
    HGL_DT_API inline Dt_ValuePtr operator ""_i (unsigned long long int i)
        { return Dt_newInt(i); }

    HGL_DT_API inline Dt_ValuePtr operator ""_f (long double f)
        { return Dt_newFloat(f); }

    HGL_DT_API inline Dt_ValuePtr operator ""_s (const char * s, std::size_t n)
        { return Dt_newStrN(s, n); }
} // namespace DtLiterals

extern "C" {

#endif // __cplusplus

/**
 * @brief increase reference count
 * @param ValuePtr pointer to the value
 */
#define DT_incRef(ValuePtr) ((ValuePtr)->_rc++)

/**
 * @brief decrease reference count
 * @param ValuePtr pointer to the value
 */
#define DT_decRef(ValuePtr) \
    (((ValuePtr)->_rc > (Dt_Size)1) ? \
        ((ValuePtr)->_rc--, (void)0) : (DT_delValue(ValuePtr), (void)0))

/**
 * @brief delete a value
 * @param ValuePtr the value to delete
 * @warning deleting a value with its ref-cnt over 1 may lead to unexpected errors
 */
#define DT_delValue(ValuePtr) DT_invokeMethod0(ValuePtr, Dt_M_Delete)

/* --- --- --- --- --- value unwrap --- --- --- --- --- */

HGL_DT_API extern Dt_Bool  Dt_asBool(Dt_ValuePtr v);
HGL_DT_API extern Dt_Int   Dt_asInt(Dt_ValuePtr v);
HGL_DT_API extern Dt_Float Dt_asFloat(Dt_ValuePtr v);
HGL_DT_API extern Dt_Str   Dt_asStr(Dt_ValuePtr v);

/* --- --- --- --- --- type operations --- --- --- --- --- */

HGL_DT_API extern Dt_Type Dt_NilType;
HGL_DT_API extern Dt_Type Dt_BoolType;
HGL_DT_API extern Dt_Type Dt_IntType;
HGL_DT_API extern Dt_Type Dt_FloatType;
HGL_DT_API extern Dt_Type Dt_StrType;
HGL_DT_API extern Dt_Type Dt_ListType;

/// get type of a value
#define DT_TypeOf(ValuePtr)         (*(ValuePtr->_tm))
/// get type name of a value (returns name of type `const char*`)
#define DT_TypeNameOf(ValuePtr)     (ValuePtr->_tm->name)
/// check if two values have same type
#define DT_isSameType(VP1, VP2)     (&DT_TypeOf(VP1) == &DT_TypeOf(VP2))
/// check if a value is the given type
#define DT_isType(ValuePtr, Type)   (&DT_TypeOf(ValuePtr) == &Type)

/* --- --- --- --- --- methods --- --- --- --- --- */

/// invoke method with no argument (returns value of type `Dt_ValuePtr`)
#define DT_invokeMethod0(ValuePtr, Method) \
    ((ValuePtr)->_tm->_m0[(Method) - __Dt_M_0__](ValuePtr))
/// invoke method with 1 argument (returns value of type `Dt_ValuePtr`)
#define DT_invokeMethod1(ValuePtr, Method, Arg1) \
    ((ValuePtr)->_tm->_m1[(Method) - __Dt_M_1__](ValuePtr, Arg1))
/// invoke method with 2 arguments (returns value of type `Dt_ValuePtr`)
#define DT_invokeMethod2(ValuePtr, Method, Arg1, Arg2) \
    ((ValuePtr)->_tm->_m2[(Method) - __Dt_M_2__](ValuePtr, Arg1, Arg2))

#define DT_assertIsMethod0(Method) \
    static_assert(Method > __Dt_M_0__ && Method < __Dt_M_0E__, "not a method0")
#define DT_assertIsMethod1(Method) \
    static_assert(Method > __Dt_M_1__ && Method < __Dt_M_1E__, "not a method1")
#define DT_assertIsMethod2(Method) \
    static_assert(Method > __Dt_M_2__ && Method < __Dt_M_2E__, "not a method2")

/**
 * @brief invoke a method of the given value
 * 
 * @param v the value
 * @param m the method to invoke
 * @param ... argument(s); the number of args is related to the method to call
 * @return return of the call
 */
HGL_DT_API extern Dt_ValuePtr Dt_invokeMethod(Dt_ValuePtr v, Dt_Method m, ...);

#define DT_Add(A, B)    DT_invokeMethod1(A, Dt_M_Add, B)
#define DT_Sub(A, B)    DT_invokeMethod1(A, Dt_M_Sub, B)
#define DT_Mul(A, B)    DT_invokeMethod1(A, Dt_M_Mul, B)
#define DT_Div(A, B)    DT_invokeMethod1(A, Dt_M_Div, B)
#define DT_Pow(A, B)    DT_invokeMethod1(A, Dt_M_Pow, B)
#define DT_Rem(A, B)    DT_invokeMethod1(A, Dt_M_Rem, B)
#define DT_Shl(A, B)    DT_invokeMethod1(A, Dt_M_Shl, B)
#define DT_Shr(A, B)    DT_invokeMethod1(A, Dt_M_Shr, B)

/* --- --- --- --- --- derivatives --- --- --- --- --- */

/**
 * @brief string format; similar to std::sprintf, but returns a string
 * 
 * @param fmtstr format-string, which is similar to 1st argument of std::printf
 * @param ... data to format
 * @return formatted string (Dt_ValuePtr, instance of Dt_StrType)
 */
HGL_DT_API extern Dt_ValuePtr Dt_format(const char * fmtstr, ...);

/* --- --- --- --- error handling --- --- --- --- */

/// error reasons (enum)
typedef enum _Dt_Error
{
    Dt_NoError = 0,
    Dt_MethodError,
    Dt_TypeError,
    Dt_IndexError,
    Dt_KeyError,
} Dt_Error;


/**
 * @brief set error handler
 * @param handler the handler function, pass a NULL to reset
 */
HGL_DT_API extern void Dt_setErrorHandler(void (*handler)(Dt_Error, const char *));

#ifdef __cplusplus
}
#endif
