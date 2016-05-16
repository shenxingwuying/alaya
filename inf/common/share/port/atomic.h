/**
 *  Atomic operations (ported from Windows version)
 */
#ifndef ALAYA_PORT_ATOMIC_H_
#define ALAYA_PORT_ATOMIC_H_

#include "extypes.h"

#if !defined(__i386__) && !defined(__x86_64__) && !defined(__arm__)
#error "Arch not supprot!"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __arm__
// return old value
static inline int atomic_add(volatile int *count, int add) {
     register int __res;
     __res = __sync_fetch_and_add(count, add);
     return __res;
}
// return old value
static inline int atomic_swap(volatile void *lockword, int value) {
    unsigned long tmp;
    int result;

    __asm__ __volatile__ ("dmb" : : : "memory");

    __asm__ __volatile__("@ atomic_swap\n"
"1: ldrex   %0, [%2]\n"
"   strex   %1, %3, [%2]\n"
"   teq %1, #0\n"
"   bne 1b"
    : "=&r" (result), "=&r" (tmp)
    : "r" (lockword), "Ir" (value)
    : "cc");

    __asm__ __volatile__ ("dmb" : : : "memory");

    return result;
}

static inline int atomic_comp_swap(volatile void *lockword, int exchange, int comperand) {
     register int __res;
     __res = __sync_val_compare_and_swap((int *)lockword, comperand, exchange);
     return __res;
}

static inline int64 atomic_comp_swap64(volatile void *lockword, int64 exchange, int64 comperand) {
     register int64 __res;
     __res = __sync_val_compare_and_swap((int64 *)lockword, comperand, exchange);
     return __res;
}
#else
static inline int atomic_add(volatile int *count, int add) {
#ifdef __linux__
    __asm__ __volatile__(
        "lock xadd %0, (%1);"
        : "=a"(add)
        : "r"(count), "a"(add)
        : "memory"
    );
#else
#error "not done yet "
#endif
	return add;
}

static inline int atomic_swap(volatile void *lockword, int value) {
#ifdef __linux__
    __asm__ __volatile__(
        "xchg %0, (%1);"
        : "=a"(value)
        : "r"(lockword), "a"(value)
        : "memory"
        );
#else
#error "not done yet "
#endif
    return value;
}

static inline int atomic_comp_swap(volatile void *lockword, int exchange, int comperand) {
#ifdef __linux__
    __asm__ __volatile__(
        "lock cmpxchg %1, (%2)"
        :"=a"(comperand)
        :"d"(exchange), "r"(lockword), "a"(comperand)
        );
#else
    __asm {
        mov eax, comperand
        mov edx, exchange
        mov ecx, lockword
        lock cmpxchg [ecx], edx
        mov comperand, eax
    }
#endif /* #ifdef __linux__ */
    return comperand;
}

static inline int atomic_comp_swap64(volatile void *lockword, int64 exchange, int64 comperand) {
#ifdef __linux__
    __asm__ __volatile__(
        "lock cmpxchg %1, (%2)"
        :"=a"(comperand)
        :"d"(exchange), "r"(lockword), "a"(comperand)
        );
#else
#error "not done yet!"
#endif /* #ifdef __linux__ */
    return comperand;
}

#endif //#ifdef __arm__


#ifdef __arm__
#define nop() 						   __asm__ __volatile__("mov\tr0,r0\t@ nop\n\t");
#else
#define nop()						    __asm__ ("pause" )
#endif

#ifdef __linux__
#define mfence_c()					    __asm__ __volatile__ ("": : :"memory")
#else
#define mfence_c()                      _ReadWriteBarrier()
#endif

#ifndef __arm__
#define mfence_x86()                    __asm__ __volatile__ ("mfence": : :"memory")
#endif

#define AtomicGetValue(x)			    (atomic_comp_swap(&(x), 0, 0))
#define AtomicSetValue(x, v)		    (atomic_swap(&(x), (v)))
#define AtomicSetValueIf(x, v, ifn)		(atomic_comp_swap(&(x), (v), ifn))

// not tested
//#define AtomicGetValue64(c)			(atomic_comp_swap64(&(c), 0, 0))
//#define AtomicSetValue64(c, n)		(atomic_swap64(&(c), (n), (c)))

// return new value
#define AtomicDec(c)				    (atomic_add(&(c), -1) - 1)
#define AtomicInc(c)				    (atomic_add(&(c), 1) + 1)

// for int64
#ifdef __linux__
//return: the incremented value;
/// 原子地做 64位的++i的操作
/// 该操作虽然参数和返回值都是无符号型整数，但是一样可以
/// 对有符号型整数做操作，只需要做适当的参数转换即可
/// @param pv 指向操作数的指针
/// @return 操作数加1以后的数值
static inline int64 atomic_inc(volatile int64 * pv) {
     register unsigned long __res;
     __asm__ __volatile__ (
          "movq $1,%0;"
          "lock xaddq %0,(%1);"
          "incq %0"
          :"=a" (__res), "=q" (pv): "1" (pv));
     return __res;
}

//return: the decremented value;
/// 原子地做 64位的--i的操作
/// 该操作虽然参数和返回值都是无符号型整数，但是一样可以
/// 对有符号型整数做操作，只需要做适当的参数转换即可
/// @param pv 指向操作数的指针
/// @return 操作数减1后的数值
static inline int64 atomic_dec(volatile int64 * pv) {
     register unsigned long __res;
     __asm__ __volatile__ (
          "movq $0xffffffffffffffff,%0;"
          "lock xaddq %0,(%1);"
          "decq %0"
          : "=a" (__res), "=q" (pv): "1" (pv));
     return __res;

}

//return: the initial value of *pv
/// 原子地做 8位，16位，32位，64位的加法的操作
/// 该操作虽然参数和返回值都是无符号型整数，但是一样可以
/// 对有符号型整数做操作，只需要做适当的参数转换即可
/// @param pv 指向操作数的指针
/// @return 操作数加法之前的数值
static inline int64 atomic_add_int64(volatile int64 * pv, const int64 av) {
     //:"=a" (__res), "=q" (pv): "m"(av), "1" (pv));
     register unsigned long __res;
     __asm__ __volatile__ (
          "movq %2,%0;"
          "lock xaddq %0,(%1);"
          :"=a" (__res), "=q" (pv): "mr"(av), "1" (pv));
     return __res;
}

//function: set *pv to nv
//return: the initial value of *pv
/// 原子地把nv赋值给pv指向的整数，支持64位操作
/// @param pv 待赋值的整数（目的操作数）
/// @param nv 向pv赋的整数
/// @return pv指向的赋值前的数值
static inline int64 atomic_exchange(volatile int64 * pv, const int64 nv) {
     register unsigned long __res;
     __asm__ __volatile__ (
          "1:"
          "lock cmpxchgq %3,(%1);"                \
          "jne 1b":
          "=a" (__res), "=q" (pv): "1" (pv), "q" (nv), "0" (*pv));
     return __res;
}

//function: compare *pv to cv, if equal, set *pv to nv, otherwise do nothing.
//return: the initial value of *pv
/// 比较pv和cv，如果两者相等，则返回pv原有数值并且把nv赋值给pv
/// 否则什么也不作，返回pv原有数值
/// @param pv 待赋值的整数（目的操作数）
/// @param nv 向pv赋的整数
/// @param cv 和pv比较的整数
/// @return pv指向的操作前的数值
static inline int64 atomic_compare_exchange(volatile int64 * pv,
       const int64 nv, const int64 cv) {
     register unsigned long __res;
     __asm__ __volatile__ (
          "lock cmpxchgq %3,(%1)"
          : "=a" (__res), "=q" (pv) : "1" (pv), "q" (nv), "0" (cv));
     return __res;
}
#endif // ifdef __linux__

#ifdef __cplusplus
}
#endif

#endif
