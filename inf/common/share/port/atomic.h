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
/// ԭ�ӵ��� 64λ��++i�Ĳ���
/// �ò�����Ȼ�����ͷ���ֵ�����޷���������������һ������
/// ���з�����������������ֻ��Ҫ���ʵ��Ĳ���ת������
/// @param pv ָ���������ָ��
/// @return ��������1�Ժ����ֵ
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
/// ԭ�ӵ��� 64λ��--i�Ĳ���
/// �ò�����Ȼ�����ͷ���ֵ�����޷���������������һ������
/// ���з�����������������ֻ��Ҫ���ʵ��Ĳ���ת������
/// @param pv ָ���������ָ��
/// @return ��������1�����ֵ
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
/// ԭ�ӵ��� 8λ��16λ��32λ��64λ�ļӷ��Ĳ���
/// �ò�����Ȼ�����ͷ���ֵ�����޷���������������һ������
/// ���з�����������������ֻ��Ҫ���ʵ��Ĳ���ת������
/// @param pv ָ���������ָ��
/// @return �������ӷ�֮ǰ����ֵ
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
/// ԭ�ӵذ�nv��ֵ��pvָ���������֧��64λ����
/// @param pv ����ֵ��������Ŀ�Ĳ�������
/// @param nv ��pv��������
/// @return pvָ��ĸ�ֵǰ����ֵ
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
/// �Ƚ�pv��cv�����������ȣ��򷵻�pvԭ����ֵ���Ұ�nv��ֵ��pv
/// ����ʲôҲ����������pvԭ����ֵ
/// @param pv ����ֵ��������Ŀ�Ĳ�������
/// @param nv ��pv��������
/// @param cv ��pv�Ƚϵ�����
/// @return pvָ��Ĳ���ǰ����ֵ
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
