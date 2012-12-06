/*
 * CLogger.cpp
 *
 *  Created on: Apr 25, 2011
 *      Author: void
 */

#include "pch.h"

#include "Logger.h"

namespace Common {

SINGLETON_SETUP(Logger);

#ifdef WIN32_LOG_TO_FILE
FILE *logFile;
#endif

#define WIN32_LOG_TO_FILE	0

const char *Logger::priorToString(int prior) const
{
    const char *str;
    switch (prior)
    {
    case LOG_EMERG:
        str = "EMERG";
        break;
    case LOG_ALERT:
        str = "ALERT";
        break;
    case LOG_CRIT:
        str = "CRIT";
        break;
    case LOG_ERR:
        str = "ERR";
        break;
    case LOG_WARNING:
        str = "WARN";
        break;
    case LOG_NOTICE:
        str = "NOTICE";
        break;
    case LOG_INFO:
        str = "INFO";
        break;
    case LOG_DEBUG:
        str = "DEBUG";
        break;
    default:
        str = "UNKNOWN";
        break;
    }

    return str;
}

void Logger::LogMsg(int prior, const char *msg, ...) const
{
    va_list arg;
    va_start(arg, msg);
    logMsgImpl(prior, msg, arg);
    va_end(arg);
}

void Logger::Initialize(const std::string & appName, const std::string & tag)
{
    m_appName = appName;
    m_tag = tag;
#ifdef WIN32
#if WIN32_LOG_TO_FILE==1
    logFile = fopen("winlog.txt", "a");
#endif
#elif USE_SYSLOG==1
    closelog();
    APP_DEBUG_OUT("Opening syslog with id ( %s )", m_appName.c_str());
    openlog(m_appName.c_str(), LOG_PID, LOG_LOCAL0);
#endif
}

void Logger::LogMsgDebug(const char *msg, ...) const
{
#if LOG_DEBUG_MSGS==1
    va_list arg;
    va_start(arg, msg);
    logMsgImpl(LOG_DEBUG, msg, arg);
    va_end(arg);
#endif
}

Logger::~Logger()
{
#ifdef WIN32
#if WIN32_LOG_TO_FILE==1
    fclose(logFile);
#endif

#elif USE_SYSLOG==1
    closelog();
#endif
}

Logger::Logger()
{
    SINGLETON_ENABLE_THIS;
}

void Logger::logMsgImpl(int priority, const char *msg, va_list params) const
{
    char msg_buf[1024];
    APP_API_MEMSET(msg_buf, 0, 1024);
    int msg_size;
#if !defined(NOLOG)
    msg_size = vsnprintf(msg_buf, sizeof (msg_buf) - 1, msg, params);
#ifdef WIN32
    APP_DEBUG_OUT("Prio(%s) : %s %s\n", priorToString(priority), m_tag.c_str(), msg_buf);
#if WIN32_LOG_TO_FILE==1
    fprintf(logFile, "Prio(%s) : %s %s\n", priorToString(priority), m_tag.c_str(), msg_buf);
#endif
#elif USE_SYSLOG==1
#ifndef NDEBUG
    APP_DEBUG_OUT("Prio(%s) : %s\n", priorToString(priority), msg_buf); //TODO: remove this
#endif
    syslog(priority, "%s [%s] %s", m_tag.c_str(), priorToString(priority), msg_buf);
#else
    APP_DEBUG_OUT("Prio(%s) : %s\n", priorToString(priority), msg_buf);
#endif
#endif
}

} //Common