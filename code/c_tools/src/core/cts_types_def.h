#ifndef CTS_TYPES_DEF_H
#define CTS_TYPES_DEF_H

#ifdef __cplusplus
#define CTS_C_BEGIN extern "C" {
#define CTS_C_END }
#else
#define CTS_C_BEGIN
#define CTS_C_END
#endif /*!__cplusplus*/

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif /*!__WINDOWS__*/

#include <stdint.h>

typedef uint8_t bool_t;
#define TRUE 1
#define FALSE 0

struct _cts_value_t;
typedef struct _cts_value_t cts_value_t;

#endif /*!CTS_TYPES_DEF_H*/