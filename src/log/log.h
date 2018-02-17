#ifndef _OPENEFT_LOG_H
#define _OPENEFT_LOG_H

#include <stdio.h>
#include <stdlib.h>

#define LOG_EMERG  0
#define LOG_ALERT  1
#define LOG_CRIT   2 
#define LOG_ERR    3
#define LOG_WARNING  4
#define LOG_NOTICE   5
#define LOG_INFO     6
#define LOG_DEBUG    7
#define LOG_DEFAULT  d
#define LOG_CONT     c

extern int log_run_level;
extern int log_fp;

/* Keep things simple for sakes */
#define log(level, fmt, ...) \
        do { if (level <= log_run_level) dprintf(log_fp, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

#endif
