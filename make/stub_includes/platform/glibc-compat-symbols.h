#ifndef __GLIBC_COMPAT_SYMBOLS_H__
#define __GLIBC_COMPAT_SYMBOLS_H__ 1

/**
 *
 * Note: Patching a specific glibc symbol version is only required if *not* statically linking glibc,
 *       which should be preferred.
 *
 * Note: JogAmp's minimum GLIBC is 2.4 due to '__stack_chk_fail' (stack overflow checking)
 *
 *   GLIBC 2.4 - March 2006  - Standard for LSB 4.0, Used in SLES 10
 *
 * We could add compile/link option '-fno-stack-protector', however stack protection seems reasonable
 * and a pre 2006 distribution a bit too 'far fetched' for our multimedia bindings anyway.
 *
 * Check build-in macro definitions via 'gcc -dM -E - < /dev/null'
 */
#if defined(__linux__) /* Actually we like to test whether we link against GLIBC .. */
    #if defined(__GNUC__)
        #define GLIBC_NOVERSION_SYMBOL(FFF) __asm__(".symver " #FFF "," #FFF "@");
        #if defined(__aarch64__)
           /* glibc 2.17 is the first glibc version that support aarch64
              however memcpy is not versioned for aarch64 */
           #define GLIBC_COMPAT_SYMBOL(FFF) __asm__(".symver " #FFF "," #FFF "@");
        #elif defined(__arm__)
           #define GLIBC_COMPAT_SYMBOL(FFF) __asm__(".symver " #FFF "," #FFF "@");
        #elif defined(__PPC64__)
	   /* PPC64 has multiple versions of memcpy from glibc 2.3 and onwards
	    * while PPC64LE only has one (introduced in glibc 2.17). PPC64LE is
	    * the more common of the two now so skip versioning. */
           #define GLIBC_COMPAT_SYMBOL(FFF) __asm__(".symver " #FFF "," #FFF "@");
        #elif defined(__amd64__)
           #define GLIBC_COMPAT_SYMBOL(FFF) __asm__(".symver " #FFF "," #FFF "@GLIBC_2.2.5");
        #else
           #define GLIBC_COMPAT_SYMBOL(FFF) __asm__(".symver " #FFF "," #FFF "@GLIBC_2.0");
        #endif /*__amd64__*/
    #elif defined(__clang__)
        #define GLIBC_NOVERSION_SYMBOL(FFF) asm(".symver " #FFF "," #FFF "@");
        #if defined(__aarch64__)
           /* glibc 2.17 is the first glibc version that support aarch64
              however memcpy is not versioned for aarch64 */
           #define GLIBC_COMPAT_SYMBOL(FFF) asm(".symver " #FFF "," #FFF "@");
        #elif defined(__arm__)
           /** On recent toolchain memcpy is no more versioned for arm
           #define GLIBC_COMPAT_SYMBOL(FFF) __asm__(".symver " #FFF "," #FFF "@GLIBC_2.4");
            */
           #define GLIBC_COMPAT_SYMBOL(FFF) asm(".symver " #FFF "," #FFF "@");
        #elif defined(__PPC64__)
	   /* PPC64 has multiple versions of memcpy from glibc 2.3 and onwards
	    * while PPC64LE only has one (introduced in glibc 2.17). PPC64LE is
	    * the more common of the two now so skip versioning. */
           #define GLIBC_COMPAT_SYMBOL(FFF) asm(".symver " #FFF "," #FFF "@");
        #elif defined(__amd64__)
           #define GLIBC_COMPAT_SYMBOL(FFF) asm(".symver " #FFF "," #FFF "@GLIBC_2.2.5");
        #else
           #define GLIBC_COMPAT_SYMBOL(FFF) asm(".symver " #FFF "," #FFF "@GLIBC_2.0");
        #endif /*__amd64__*/
    #else
        #warning GLIBC_COMPAT_SYMBOL not supported with current compiler on GNU/Linux
        #define GLIBC_COMPAT_SYMBOL(FFF)
    #endif
#else
    #warning GLIBC_COMPAT_SYMBOL not supported with target OS
    #define GLIBC_COMPAT_SYMBOL(FFF)
#endif

// Build on Debian 12 hardlinked against GLIBC_2.34, e.g. `U dlsym@GLIBC_2.34`
GLIBC_COMPAT_SYMBOL(memcpy)

GLIBC_NOVERSION_SYMBOL(dladdr)
GLIBC_NOVERSION_SYMBOL(dlclose)
GLIBC_NOVERSION_SYMBOL(dlerror)
GLIBC_NOVERSION_SYMBOL(dlopen)
GLIBC_NOVERSION_SYMBOL(dlsym)

#endif /*__GLIBC_COMPAT_SYMBOLS_H__*/
