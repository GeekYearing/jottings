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

#ifndef NULL
#define NULL ((void*)0)
#endif /*!NULL*/

typedef uint8_t bool_t;
#define TRUE 1
#define FALSE 0

struct _cts_value_t;
typedef struct _cts_value_t cts_value_t;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#include "cts_assert.h"
#include "cts_err.h"

#endif /*!CTS_TYPES_DEF_H*/