/*  acconfig.h -- `autoheader' will generate config.h.in */
/*
 * This file is part of the XORP software.
 * See file `LICENSE.xorp' for copyright and license information.
 */

#ifndef __XORP_CONFIG_H__
#define __XORP_CONFIG_H__

/*
 * XXX: everything above is unconditionally copied to the generated file
 */
@TOP@

/*
 * If you don't have these types in <inttypes.h>, #define these to be
 * the types you do have.
 */
#undef int8_t
#undef int16_t
#undef int32_t
#undef int64_t
#undef uint8_t
#undef uint16_t
#undef uint32_t

/*
 * Debugging:
 * DEBUG: general debugging
 * DEBUG_MEM: debug memory allocation
 */
#undef DEBUG
#undef DEBUG_MEM

@BOTTOM@
/*
 * XXX: everything below is unconditionally copied to the generated file
 */

/*
 * XXX: Workaround a bug whereby the GNU autoconf tests will happily
 * go off and define their own fictional pid_t using the preprocessor.
 */
#ifdef pid_t
#undef pid_t
#endif

#ifndef HAVE_SIG_T
typedef RETSIGTYPE (*sig_t)(int);
#endif

#ifndef HAVE_SOCKLEN_T
typedef int socklen_t;
#endif /* HAVE_SOCKLEN_T */

/* KAME code likes to use INET6 to ifdef IPv6 code */
#if defined(HAVE_IPV6) && defined(IPV6_STACK_KAME)
#ifndef INET6
#define INET6
#endif
#endif /* HAVE_IPV6 && IPV6_STACK_KAME */

#ifndef WORDS_BIGENDIAN
#define WORDS_SMALLENDIAN
#endif

#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif

#if defined (__cplusplus) && !defined(__STL_NO_NAMESPACES)
using namespace std;
#endif

/*
 * Include sys/cdefs.h to define __BEGIN_DECLS and __END_DECLS.  Even if
 * this file exists, not all platforms define these macros.
 */
#ifdef HAVE_SYS_CDEFS_H
#include <sys/cdefs.h>
#endif

/*
 * Define C++ decls wrappers if not previously defined.
 */
#ifndef __BEGIN_DECLS
#  if defined(__cplusplus)
#    define __BEGIN_DECLS	extern "C" {
#    define __END_DECLS		};    
#  else /* __BEGIN_DECLS */
#    define __BEGIN_DECLS
#    define __END_DECLS
#  endif /* __BEGIN_DECLS */
#endif /* __BEGIN_DECLS */

#endif /* __XORP_CONFIG_H__ */