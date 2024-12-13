#ifndef CTS_ASSERT_H
#define CTS_ASSERT_H

#include "cts_types_def.h"

CTS_C_BEGIN

#define cts_return_if_fail(expr, val) \
  if ((expr)) {                       \
    return val;                       \
  }

CTS_C_END

#endif /*!CTS_ASSERT_H*/