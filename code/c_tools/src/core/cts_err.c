#include "cts_err.h"

#ifdef CTS_CONFIG_WITH_ERR_CODE_MESSAGE

#define CTS_ERR_MESSAGE_ITEM(err) \
  { err, #err }

typedef struct _cts_err_message_t {
  cts_err_t code;
  const char* message;
} cts_err_message_t;

static const cts_err_message_t s_cts_err_message_table[] = {

#ifdef CTS_OK
    CTS_ERR_MESSAGE_ITEM(CTS_OK),
#endif /*!CTS_OK*/

#ifdef CTS_FAIL
    CTS_ERR_MESSAGE_ITEM(CTS_FAIL),
#endif /*!CTS_FAIL*/

#ifdef CTS_BAD_PARAMS
    CTS_ERR_MESSAGE_ITEM(CTS_BAD_PARAMS),
#endif /*!CTS_BAD_PARAMS*/

#ifdef CTS_OUT_OF_MEM
    CTS_ERR_MESSAGE_ITEM(CTS_OUT_OF_MEM),
#endif /*!CTS_OUT_OF_MEM*/

};

static const cts_err_message_t* cts_err_message_find(cts_err_t code) {
  uint32_t i = 0;
  const cts_err_message_t* err_message = {0};

  for (i = 0; i < ARRAY_SIZE(s_cts_err_message_table); i++) {
    err_message = &s_cts_err_message_table[i];
    if (err_message->code == code) {
      return err_message;
    }
  }

  return NULL;
}

#endif /*!CTS_CONFIG_WITH_ERR_CODE_MESSAGE*/

static const char* s_unkonwn_err_message = "UNKNOWN ERROR";

const char* cts_err_to_name(cts_err_t code) {
#ifdef CTS_CONFIG_WITH_ERR_CODE_MESSAGE
  const cts_err_message_t* err_message = cts_err_message_find(code);
  if (err_message != NULL) {
    return err_message->message;
  }
#endif /*!CTS_CONFIG_WITH_ERR_CODE_MESSAGE*/

  return s_unkonwn_err_message;
}

const char* cts_err_to_name_with_code(cts_err_t code, char* buff, uint32_t length) {
  cts_return_if_fail(buff != NULL && length > 0, NULL);

#ifdef CTS_CONFIG_WITH_ERR_CODE_MESSAGE
  const cts_err_message_t* err_message = cts_err_message_find(code);
  if (err_message != NULL) {
    if (sprintf(buff, length, "%s 0x%x(%d)", err_message->message, err_message->code, err_message->code) > 0) {
      return buff;
    }
  }
#endif

  if (sprintf(buff, length, "%s 0x%x(%d)", err_message->message, err_message->code, err_message->code) > 0) {
    return buff;
  }
  return NULL;
}