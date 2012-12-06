/*
 * Defs.h
 *
 *  Created on: Apr 25, 2011
 *      Author: void
 */

#ifndef DEFS_H_
#    define DEFS_H_

#include "BasicTypes.h"
#if  defined(__MINGW32__) && !defined WIN32
        #define WIN32
#endif


#define INL inline

#    define USE_ASSERT 1
#    define USE_ZLIB 0
#ifndef FD_SETSIZE
#    define FD_SETSIZE 2000 // must be defined before including <Winsock2.h>
#endif
#    define UT_NPOS     0xFFFFFFFF
#    define STATIC_ASSERT(x, n) typedef bool n[(x) ? 1 : 0];

#    if defined(DEBUG) || defined(_DEBUG)
#        define DBGMODE
#    endif

#    ifdef WIN32
#        define LOG_EMERG   0
#        define LOG_ALERT   1
#        define LOG_CRIT    2
#        define LOG_ERR     3
#        define LOG_WARNING 4
#        define LOG_NOTICE  5
#        define LOG_INFO    6
#        define LOG_DEBUG   7
#    endif

#    ifdef DBGMODE
#        define LOG_DEBUG_MSGS 1
#    endif

#   define PEG_X64

#   if defined PEG_X64 && defined WIN32
#        define PE_WIN_X86_ASM
#   endif

// define a 64 bit int type
#    ifdef WIN32
#        define u64 unsigned __int64
#        define s64 __int64
#        define l64 u64
#    elif MAC
#        define u64 unsigned long long
#        define s64 long
#    else // for linux
#        define u64 unsigned long long
#        define l64 long long
#        define s64 long long
#    endif

typedef long double float80; //compiler specific
typedef double float64;
typedef float float32;

enum FILE_ACCESSOR
{
    FAUNKNOWN       =   0,
    READ_BINARY     =   1 << 1,
    WRITE_BINARY    =   1 << 2
} ;


#    ifdef WIN32
#        include <windows.h>
//#        include <Winsock2.h>
#        ifdef min
#            undef min  // undef min define in Windef.h included by windows.h
#        endif
#        include <stdlib.h>
#        include <stdio.h>
#        include <malloc.h>
#        include <memory.h>
#        include <tchar.h>
#        include <string.h>
#        include <stdarg.h>
#        include <time.h>
#        include <io.h>
#        include <fcntl.h>
#        include <process.h>
#        include <direct.h>
//#        include <ws2tcpip.h>

#    elif MAC
#        include <sys/types.h>
#        include <sys/socket.h>
#        include <netinet/in.h>
#        include <netdb.h>
#        include <arpa/inet.h>
#        include <unistd.h>
#        include <fcntl.h>
#        include <errno.h>
#        include <sys/ioctl.h>
#        include <net/if.h>
#        include <syslog.h>
#        include <stdlib.h>
#        include <stdio.h>
#        include <memory.h>
#        include <string.h>
#        include <stdarg.h>
#        include <time.h>
#        include <fcntl.h>
#        include <unistd.h>
#        include <pthread.h>
#        include <time.h>
#        include <string.h>

#    else // for linux
#        include <sys/socket.h>
#        include <netinet/in.h>
#        include <netdb.h>
#        include <arpa/inet.h>
#        include <unistd.h>
#        include <fcntl.h>
#        include <errno.h>
#        include <sys/ioctl.h>
#        include <net/if.h>
#        include <syslog.h>
#        include <stdlib.h>
#        include <stdio.h>
#        include <memory.h>
#        include <string.h>
#        include <stdarg.h>
#        include <time.h>
#        include <fcntl.h>
#        include <errno.h>

#	 include <sys/stat.h>
#        include <sys/types.h>
#        include <sys/socket.h>
#        include <netinet/in.h>
#        include <netdb.h>
#        include <arpa/inet.h>
#        include <unistd.h>
//#include <fcntl.h>
//#include <errno.h>
#        include <sys/ioctl.h>
#        include <net/if.h>
#        include <syslog.h>
#        include <unistd.h>
#        include <pthread.h>
#        include <string.h>
#        include <stddef.h>
#    endif




#    include <assert.h>
#    include <string>
#    include <cassert>
#    include <stdexcept>
#    include <stdarg.h>
#    include <vector>
#    include <sstream>
#    include <limits>
#    include <stack>

#    include <iostream>
#    include <time.h>
#    include <fstream>
#    include <math.h>
#    include <queue>

#    include <functional>
#    include <map>
#    include <deque>
#    include <algorithm>
#    include <list>

#    include <cstdio>

#ifdef ENABLE_BOOST
#include "BoostInc.h"
#endif

#endif /* DEFS_H_ */
