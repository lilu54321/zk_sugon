/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ZK_LOG_H_
#define ZK_LOG_H_

#include <zookeeper.h>

#ifdef __cplusplus
extern "C" {
#endif

// 下面这段从ofs_debug.h拷过来的。
typedef struct zoo_debug_limits {
    long long   timestamp_next; /* Next time when to print log at the same place */
    int         suppress_delay; /* delay to recalcuate timestamp_next */
    int         suppress_count;
} zoo_debug_limits_t;

int zoo_debug_write_limit(struct zoo_debug_limits * dbg_limits);

extern ZOOAPI ZooLogLevel logLevel;
#define LOGSTREAM getLogStream()

#define LOG_ERROR(x) if(logLevel>=ZOO_LOG_LEVEL_ERROR) \
    log_message(ZOO_LOG_LEVEL_ERROR,__LINE__,__func__,format_log_message x)
#define LOG_WARN(x) if(logLevel>=ZOO_LOG_LEVEL_WARN) \
    log_message(ZOO_LOG_LEVEL_WARN,__LINE__,__func__,format_log_message x)
#define LOG_INFO(x) if(logLevel>=ZOO_LOG_LEVEL_INFO) \
    log_message(ZOO_LOG_LEVEL_INFO,__LINE__,__func__,format_log_message x)
#define LOG_DEBUG(x) if(logLevel==ZOO_LOG_LEVEL_DEBUG) \
    log_message(ZOO_LOG_LEVEL_DEBUG,__LINE__,__func__,format_log_message x)


#define LOG_ERROR_LIMIT(x) if(logLevel>=ZOO_LOG_LEVEL_ERROR) {                  \
    static zoo_debug_limits_t dbg_limits = { 0, 0, 0 };                         \
                                                                                \
    if (zoo_debug_write_limit(&dbg_limits) == 0)                                \
    {                                                                           \
        log_message(ZOO_LOG_LEVEL_ERROR,__LINE__,__func__,format_log_message x);\
    }                                                                           \
}

#define LOG_WARN_LIMIT(x) if(logLevel>=ZOO_LOG_LEVEL_WARN) {                    \
    static zoo_debug_limits_t dbg_limits = { 0, 0, 0 };                         \
                                                                                \
    if (zoo_debug_write_limit(&dbg_limits) == 0)                                \
    {                                                                           \
        log_message(ZOO_LOG_LEVEL_WARN,__LINE__,__func__,format_log_message x); \
    }                                                                           \
}

#define LOG_INFO_LIMIT(x) if(logLevel>=ZOO_LOG_LEVEL_INFO) {                    \
    static zoo_debug_limits_t dbg_limits = { 0, 0, 0 };                         \
                                                                                \
    if (zoo_debug_write_limit(&dbg_limits) == 0)                                \
    {                                                                           \
        log_message(ZOO_LOG_LEVEL_INFO,__LINE__,__func__,format_log_message x); \
    }                                                                           \
}

#define LOG_DEBUG_LIMIT(x) if(logLevel>=ZOO_LOG_LEVEL_DEBUG) {                  \
    static zoo_debug_limits_t dbg_limits = { 0, 0, 0 };                         \
                                                                                \
    if (zoo_debug_write_limit(&dbg_limits) == 0)                                \
    {                                                                           \
        log_message(ZOO_LOG_LEVEL_DEBUG,__LINE__,__func__,format_log_message x);\
    }                                                                           \
}


ZOOAPI void log_message(ZooLogLevel curLevel, int line,const char* funcName,
    const char* message);

ZOOAPI const char* format_log_message(const char* format,...);

FILE* getLogStream();

#ifdef __cplusplus
}
#endif

#endif /*ZK_LOG_H_*/
