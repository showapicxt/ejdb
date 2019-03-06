#pragma once
#ifndef JQL_H
#define JQL_H

#include "jbl.h"
#include <iowow/iwlog.h>

IW_EXTERN_C_START

struct _JQL;
typedef struct _JQL *JQL;

typedef enum {
  _JQL_ERROR_START = (IW_ERROR_START + 10000UL + 1000),
  JQL_ERROR_QUERY_PARSE,          /**< Query parsing error (JQL_ERROR_QUERY_PARSE) */
  JQL_ERROR_INVALID_PLACEHOLDER,  /**< Invalid placeholder position (JQL_ERROR_INVALID_PLACEHOLDER) */
  JQL_ERROR_UNSET_PLACEHOLDER,    /**< Found unset placeholder (JQL_ERROR_UNSET_PLACEHOLDER) */
  JQL_ERROR_REGEXP_INVALID,       /**< Invalid regular expression (JQL_ERROR_REGEXP_INVALID) */
  JQL_ERROR_REGEXP_CHARSET,       /**< Invalid regular expression: expected ']' at end of character set (JQL_ERROR_REGEXP_CHARSET) */
  JQL_ERROR_REGEXP_SUBEXP,        /**< Invalid regular expression: expected ')' at end of subexpression (JQL_ERROR_REGEXP_SUBEXP) */
  JQL_ERROR_REGEXP_SUBMATCH,      /**< Invalid regular expression: expected '}' at end of submatch (JQL_ERROR_REGEXP_SUBMATCH) */
  JQL_ERROR_REGEXP_ENGINE,        /**< Illegal instruction in compiled regular expression (please report this bug) (JQL_ERROR_REGEXP_ENGINE) */
  JQL_ERROR_SKIP_ALREADY_SET,     /**< Skip clause already specified (JQL_ERROR_SKIP_ALREADY_SET) */
  JQL_ERROR_LIMIT_ALREADY_SET,    /**< Limit clause already specified (JQL_ERROR_SKIP_ALREADY_SET) */
  JQL_ERROR_ORDERBY_MAX_LIMIT,    /**< Reached max number of asc/desc order clauses: 64 (JQL_ERROR_ORDERBY_MAX_LIMIT) */
  _JQL_ERROR_END,
  _JQL_ERROR_UNMATCHED
} jq_ecode;

/**
 * @brief Create query object from specified text query.
 * @param pq Pointer to resulting query object
 * @param query Query text
 */
IW_EXPORT WUR iwrc jql_create(JQL *qptr, const char *coll, const char *query);

IW_EXPORT const char* jql_collection(JQL q);

IW_EXPORT WUR iwrc jql_set_json(JQL q, const char *placeholder, int index, JBL_NODE val);

IW_EXPORT WUR iwrc jql_set_i64(JQL q, const char *placeholder, int index, int64_t val);

IW_EXPORT WUR iwrc jql_set_f64(JQL q, const char *placeholder, int index, double val);

IW_EXPORT WUR iwrc jql_set_str(JQL q, const char *placeholder, int index, const char *val);

IW_EXPORT WUR iwrc jql_set_bool(JQL q, const char *placeholder, int index, bool val);

IW_EXPORT WUR iwrc jql_set_regexp(JQL q, const char *placeholder, int index, const char* expr);

IW_EXPORT WUR iwrc jql_set_null(JQL q, const char *placeholder, int index);

IW_EXPORT WUR iwrc jql_matched(JQL q, JBL jbl, bool *out);

IW_EXPORT bool jql_has_apply(JQL q);

IW_EXPORT bool jql_has_projection(JQL q);

IW_EXPORT bool jql_has_orderby(JQL q);

IW_EXPORT iwrc jql_get_skip(JQL q, int64_t *out);

IW_EXPORT iwrc jql_get_limit(JQL q, int64_t *out);

IW_EXPORT WUR iwrc jql_apply(JQL q, JBL jbl, JBL_NODE *out, IWPOOL *pool);

IW_EXPORT void jql_reset(JQL q, bool reset_match_cache, bool reset_placeholders);

IW_EXPORT void jql_destroy(JQL *qptr);

IW_EXPORT WUR iwrc jql_init(void);

IW_EXTERN_C_END
#endif
