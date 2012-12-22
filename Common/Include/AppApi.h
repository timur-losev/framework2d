/*
 * AppApi.h
 *
 *  Created on: Apr 25, 2011
 *      Author: void
 */

#ifndef APPAPI_H_
#    define APPAPI_H_

#ifndef USING_PCH
#    include "Defs.h"
#endif

#ifdef WIN32
#	 include <Winbase.h>
#else
#	 include <sys/time.h> 
#endif

#    define APP_API_NEW             new
#    define APP_API_DEL(a)           /*if (a)*/ { delete (a); a=NULL; } 
#    define APP_API_DELETE_ARRAY(a)  /*if (a)*/ { delete [] (a); a=NULL; }
#    define APP_API_DEL_ARRAY(p, n) { if (p) { for (int __i = 0; __i < n;__i++) APP_API_DELETE_ARRAY((p)[__i]); delete[] (p); p = NULL; } }

// adding a couple basic macros
#    define APP_API_MIN(a,b) (((a) < (b))?(a):(b))
#    define APP_API_MAX(a,b) (((a) > (b))?(a):(b))

#    ifndef BYTE
typedef unsigned char   BYTE;
#    endif

#    ifndef TRUE
#        define TRUE 1
#    endif

#    ifndef FALSE
#        define FALSE 0
#    endif


#    ifndef NULL
#        define NULL            0
#    endif

#    define APP_FILE_HANDLE     int

#    ifdef __cplusplus
extern "C"
{
#    endif

#    ifdef WIN32
#        ifdef USE_ASSERT
#            define USE_ASSERT          1
#        endif
#    endif

#    if USE_ASSERT==1
#        define APP_API_ASSERT(x) assert(x);
#    else
#        define APP_API_ASSERT(x)
#    endif

    /**
     * String
     */
    size_t APP_API_STRLEN( const char* string );
    char* APP_API_STRNEW( const char* string );
    int    APP_API_STRCMP( const char* p1, const char* p2 );
    int    APP_API_STRICMP( const char* p1, const char* p2 );
    int    APP_API_STRNCMP( const char* p1, const char* p2, int size );
    char* APP_API_STRCPY( char* dest, const char* src );
    char* APP_API_STRNCPY( char* dest, const char* src, int count );
    char* APP_API_STRCAT( char* dest, const char* src );
    char* APP_API_STRTRIM( char* src );
    char* APP_API_STRSTR( const char* src, const char* substr );
    char* APP_API_STRCHR( const char* src, const char subchar, int bFromLeft2Right );
    char* APP_API_STRCHRFIND( char* src, const char subchar, int count );
    char* APP_API_STRDUP(const char* s);
    char* APP_API_STRUPR(char* s);
    hash_t APP_API_STRHASH(const char* str, size_t len);
//
//#define XP_API_STRLEN(x) strlen(x)
//#define XP_API_STRCMP(x, y) strcmp( (x), (y) )
//#define XP_API_STRNCMP( x, y, z ) strncmp( (x), (y), (z) )
//#define XP_API_STRCPY( x, y ) strcpy( (x), (y) )
//#define XP_API_STRNCPY( x, y, z ) strncpy( (x), (y), (z) )
//#define XP_API_STRCAT( x, y ) strcat( (x), (y) )
//#define XP_API_STRSTR( x, y ) strstr( (x), (y) )

    /**
     * Memory
     */
    void* APP_API_MALLOC(size_t size );
    void   APP_API_FREE( void* p );
    void   APP_API_MEMSET( void* data, int value, size_t size );
    void* APP_API_MEMCPY( void* data, const void* src, size_t size );
    int    APP_API_MEMCMP(const void* data1, const void* data2, size_t sz);
    int    APP_API_MEMICMP(const void* data, const void* data2, size_t sz);
    void   APP_API_MEMZERO(void* dist, size_t len);

    int    APP_API_SPRINTF( char* data, size_t size, const char* format, ... );
    int    APP_API_ATOI( const char* data );
    char* APP_API_ITOA( int num, char* str, int radix );
    char* APP_API_FTOA( float num, char* str, int digits );
    double APP_API_ATOF(const char* str );

    /**
     * Debug information
     */
    void   APP_DEBUG_INIT();
    void   APP_DEBUG_FINALIZE();
    void   APP_DEBUG_OUT( const char* format, ... );

    void   APP_API_SLEEP( int mseconds );

    /**
     * File process
     */
    APP_FILE_HANDLE APP_API_FILE_OPEN( const char* filename, const char* flag );
    void   APP_API_FILE_CLOSE( APP_FILE_HANDLE handle );
    int    APP_API_FILE_READ( void* dest, int element_size, int count, APP_FILE_HANDLE handle );
    int    APP_API_FILE_WRITE( void* src, int element_size, int count, APP_FILE_HANDLE handle );
    int    APP_API_FILE_GET_LENGTH( APP_FILE_HANDLE handle );

    char* APP_API_GETCWD(char* Dst, int sizebytes);

    /**
     * Dara parser.
     */
    int    APP_API_PARSE_DATA( const char* src, char* dst, int pos, char seperator );
    int    APP_API_GET_RANDOM( char* name );

    int    APP_API_IP_STR2INT( char* ip );
    char* APP_API_IP_INT2STR( int ip, char* buffer );

    /**
     * Date time.
     */
    unsigned long APP_API_GET_DATE(int year, int month, int day, int hour, int minute);

    u64 APP_API_GET_TIME();

    void   APP_API_GET_FORMAT_TIME( char* buffer );

	u64 APP_API_GET_TICK_COUNT();

    /**
     * Last Error Code
     */
    int APP_API_GETLASTERR();

    const char* APP_API_GET_SIMPLE_FILE_NAME(const char* path);

#    ifdef __cplusplus
}
#    endif

#endif /* APPAPI_H_ */
