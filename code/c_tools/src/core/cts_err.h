#ifndef CTS_ERR_H
#define CTS_ERR_H

#include "cts_types_def.h"

CTS_C_BEGIN

typedef int32_t cts_err_t;

/**
 * @enum cts_err_code_t
 * 异常错误码定义
 */
#define CTS_OK (0)
#define CTS_FAIL (-1)
#define CTS_BAD_PARAMS (-2)
#define CTS_OUT_OF_MEM (0x101)

const char* cts_err_to_name(cts_err_t code);
const char* cts_err_to_name_with_code(cts_err_t code, char* buff, uint32_t length);

CTS_C_END

#endif /*!CTS_ERR_H*/