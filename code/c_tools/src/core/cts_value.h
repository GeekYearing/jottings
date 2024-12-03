#ifndef CTS_VALUE_H
#define CTS_VALUE_H

#include "cts_types_def.h"

CTS_C_BEGIN

#define CTS_VALUE_COMMON \
  value_t value;         \
  uint16_t type : 8;     \
  uint16_t mark : 8;

/**
 * @enums cts_value_type_t
 * 泛值对象类型
 */
#define CTS_VALUE_TYPE_NULL 0
#define CTS_VALUE_TYPE_NUMBER 1
#define CTS_VALUE_TYPE_STRING 2
#define CTS_VALUE_TYPE_POINTER 3

typedef double cts_number_t;
typedef struct _cts_string_t cts_string_t;
typedef struct _cts_pointer_t cts_pointer_t;

typedef union value_t {
  cts_number_t number;
  cts_string_t string;
  cts_pointer_t pointer;
} value_t;

/**
 * @class cts_value_t
 * 泛值对象
 */
typedef struct _cts_value_t {
  CTS_VALUE_COMMON
} cts_value_t;

typedef struct _cts_string_t {
  const char* str;
  bool_t is_need_free;
} cts_string_t;

typedef struct _cts_pointer_t {
  void* ptr;
  void (*free_handler_t)(void* ptr);
} cts_pointer_t;

/**
 * @methods cts_value_type
 * 泛值对象类型宏函数
 */
#define cts_value_type(value) ((value)->type)
#define cts_value_type_is_null(value) (cts_value_type(value) == CTS_VALUE_TYPE_NULL)
#define cts_value_type_is_number(value) (cts_value_type(value) == CTS_VALUE_TYPE_NUMBER)
#define cts_value_type_is_string(value) (cts_value_type(value) == CTS_VALUE_TYPE_STRING)
#define cts_value_type_is_pointer(value) (cts_value_type(value) == CTS_VALUE_TYPE_POINTER)

CTS_C_END

#endif /*!CTS_VALUE_H*/