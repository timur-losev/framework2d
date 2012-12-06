/*
 * CLogger.h
 *
 *  Created on: Apr 25, 2011
 *      Author: void
 */

#pragma once

#    include "Singleton.h"
//#    include "Types.h"

namespace Common {

class Logger : public Singleton<Logger>
{
private:
    void logMsgImpl(int prior, const char* msg, va_list params) const;
    const char* priorToString(int prior) const;

private:
    std::string m_appName;
    std::string m_tag;

protected:
public:
    Logger();
    ~Logger();

    void Initialize(const std::string& appName, const std::string& tag);
    void LogMsg(int prior, const char* msg, ...) const;
    void LogMsgDebug(const char* msg, ...) const;

} ;
} //Common

#define LOGGER Common::Logger::getPtr()


#if LOG_DEBUG_MSGS==1

#define LogDebug(msg) { \
    std::stringstream ss;\
    ss << msg;\
    LOGGER->LogMsgDebug("%s", ss.str().c_str());\
}

#else
#   define LogDebug(msg) (void)0
#endif

#    define LogMessage(prio, msg) {\
    std::stringstream ss; \
    ss << msg; \
    LOGGER->LogMsg(prio, "%s", ss.str().c_str());\
}

#define MemError(msg){\
    std::stringstream ss; ss << msg;\
    LOGGER->LogMsg(LOG_ERR, "Memory: %s", ss.str().c_str()); }\

#define DSError(msg){\
    std::stringstream ss; ss << msg;\
    LOGGER->LogMsg(LOG_ERR, "Script Engine: %s", ss.str().c_str()); }\

#define DSWarning(msg){\
    std::stringstream ss; ss << msg;\
    LOGGER->LogMsg(LOG_WARNING, "Script Engine: %s", ss.str().c_str()); }\

#define DSNotice(msg){\
    std::stringstream ss; ss << msg;\
    LOGGER->LogMsg(LOG_NOTICE, "Script Engine: %s", ss.str().c_str()); }\

#define DSInfo(msg){\
    std::stringstream ss; ss << msg;\
    LOGGER->LogMsg(LOG_INFO, "Script Engine: %s", ss.str().c_str()); }\

#define Stub(msg){\
    std::stringstream ss; ss << msg;\
    LOGGER->LogMsg(LOG_INFO, "STUB!: %s. FL: %s FN: %s L: %d", ss.str().c_str(), __FILE__, __FUNCTION__, __LINE__); }\

