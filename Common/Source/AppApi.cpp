/*
 * AppApi.cpp
 *
 *  Created on: Apr 25, 2011
 *      Author: void
 */

#include "pch.h"

#include "AppApi.h"

const int MAX_FILE_LIST = 8;
FILE * l_file_list[MAX_FILE_LIST] = {NULL, NULL, NULL, NULL};

void * APP_API_MALLOC(size_t size)
{
    return malloc(size);
}

void APP_API_FREE(void * p)
{
    free(p);
}

void APP_API_MEMSET(void * data, int value, size_t size)
{
    memset(data, value, size);
}

void * APP_API_MEMCPY(void * data, const void * src, size_t size)
{
    memcpy(data, src, size);
    return data;
}

int APP_API_MEMCMP(const void *data1, const void *data2, size_t sz)
{
    return memcmp(data1, data2, sz);
}

int APP_API_MEMICMP(const void *data, const void *data2, size_t sz)
{
#ifdef __GNUC__
    int result = 0;

    for (size_t i = 0; i < sz; i++)
    {
        char c1 = ((char*)data)[i];
        char c2 = ((char*)data2)[i];

        result = c1 - c2;

        if (result)
        {
            if ('A' <= c1 && c1 <= 'Z')
                c1 += 'a' - 'A';
            if ('A' <= c2 && c2 <= 'Z')
                c2 += 'a' - 'A';

            result = c1 - c2;

            if (result)
                break;
        }
    }

    return result;
#else
    return ::_memicmp(data, data2, sz);
#endif
}

void APP_API_MEMZERO(void* dist, size_t len)
{
#ifndef __GNUC__
    ZeroMemory(dist, len);
#else
    APP_API_MEMSET(dist, 0, len);
#endif
}

size_t APP_API_STRLEN(const char * string)
{
    return strlen(string);
}

int APP_API_STRCMP(const char * p1, const char * p2)
{
    return strcmp(p1, p2);
}

int APP_API_STRICMP(const char * p1, const char * p2)
{
#ifdef __GNUC__
    int result = 0;

    for (;;)
    {
        char c1 = *p1;
        char c2 = *p2;

        result = c1 - c2;

        if (result)
        {
            if ('A' <= c1 && c1 <= 'Z')
                c1 += 'a' - 'A';
            if ('A' <= c2 && c2 <= 'Z')
                c2 += 'a' - 'A';
            result = c1 - c2;
            if (result)
                break;
        }
        if (!c1)
            break;
        p1++;
        p2++;
    }

    return result;
#else
    return _stricmp(p1, p2);
#endif
}

int APP_API_STRNCMP(const char * p1, const char * p2, int size)
{
    return strncmp(p1, p2, size);
}

char * APP_API_STRNEW(const char * string)
{
    char * data = NULL;
    size_t len = APP_API_STRLEN(string);

    data = APP_API_NEW char [ len + 1 ];
    APP_API_MEMSET(data, 0, len + 1);
    APP_API_MEMCPY(data, string, len);

    return data;
}

char * APP_API_STRCPY(char * dest, const char * src)
{
    return strcpy(dest, src);
}

char * APP_API_STRNCPY(char * dest, const char * src, int count)
{
    return strncpy(dest, src, count);
}

char * APP_API_STRCAT(char * dest, const char * src)
{
    return strcat(dest, src);
}

char * APP_API_STRTRIM(char * src)
{
    size_t len = APP_API_STRLEN(src);
    int space_flag = true;
    int index = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (src[i] == ' ' && space_flag)
        {
            ;
        }
        else
        {
            space_flag = false;
            src[index++] = src[i];
        }
    }

    src[index] = 0;

    return src;
}

char * APP_API_STRSTR(const char * src, const char * substr)
{
    return (char *) strstr(src, substr);
}

char * APP_API_STRCHRFIND(char * src, const char subchar, int count)
{
    int sum = 0;
    int i = 0;

    while (src[i] != '\0' && sum < count)
    {
        if (src[i] == subchar)
        {
            sum++;
        }
        i++;
    }

    if (sum == count)
    {
        return src + i;
    }
    else
    {
        return NULL;
    }
}

char * APP_API_STRDUP(const char* s)
{
#ifndef __GNUC__
    return ::_strdup(s);
#else
    return ::strdup(s);
#endif
}

char* APP_API_STRUPR(char* s)
{
#ifndef __GNUC__
    return _strupr(s);
#else
    char* out = s;
    for(;*s;++s) *s = toupper(*s);
    return out;
#endif
}

char * APP_API_STRCHR(const char * src, const char subchar, int bFromLeft2Right)
{
    //char* ccsrc = const_cast<char*>(src);
    if (bFromLeft2Right == 1)
    {

#ifdef WIN32
        return (char *) strchr(src, subchar);
#else
        return (char *) strchr(src, subchar);
#endif

    }
    else
    {
#ifdef WIN32
        return (char *) strrchr(src, subchar);
#else
        return (char *) strrchr(src, subchar);
#endif
    }
}

int APP_API_SPRINTF(char * data, size_t size, const char * format, ...)
{
#if defined(WIN32) || defined(__unix__)
    va_list args;
    va_start(args, format);
    int rtn = vsnprintf(data, size, format, args);
    va_end(args);
    return rtn;
#else //for MAC
    va_list args;
    //int num = 0;
    int len = 0;
    int idx = 0;

    va_start(args, format);
    len = APP_API_STRLEN((char *) format);

    for (int i = 0; i < len; i++)
    {
        if ('%' == format[i])
        {
            switch (format[i + 1])
            {
            case 'd':
            {
                int value = va_arg(args, int);
                char temp[ 12 ] = {0};
                APP_API_ITOA(value, temp, 10);
                int length = APP_API_STRLEN(temp);
                APP_API_MEMCPY(data + idx, temp, length);
                idx += length;
                i++;
            }
                break;
            case 'f':
            {
                float value = va_arg(args, float);

                char temp[ 32 ] = {0};
                APP_API_FTOA(value, temp, 10);
                int length = APP_API_STRLEN(temp);
                APP_API_MEMCPY(data + idx, temp, length);
                idx += length;
                i++;
            }
                break;
            case 's':
            {
                char * value = va_arg(args, char *);
                if (NULL != value)
                {
                    int length = APP_API_STRLEN(value);
                    APP_API_MEMCPY(data + idx, value, length);
                    idx += length;
                }
                i++;
            }
                break;
            case 'c':
            {
                char value = va_arg(args, int);
                data[idx] = value;
                idx += 1;
                i++;
            }
                break;
            default:
                break;
            }
        }
        else
        {
            data[ idx++ ] = format[i];
        }
    }

    va_end(args);

    return idx;
#endif
}

void APP_API_SLEEP(int mseconds)
{
#if defined(WIN32) || defined(MAC)
    Sleep(mseconds);
#else // for linux
    timespec ts;
    ts.tv_sec = (mseconds / 1000);
    ts.tv_nsec = (mseconds % 1000) * 1000 * 1000; // mseconds to nanosec
    int rv = 0;

    // if interrupted by a signal handler, sleep remain time.
    while (((rv = nanosleep(&ts, &ts)) != 0) && (errno == EINTR));
#endif
}

void APP_DEBUG_INIT()
{
#ifdef WIN32
    AllocConsole();
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((intptr_t) handle, _O_TEXT);
    FILE * hf = _fdopen(hCrt, "w");
    *stdout = *hf;
#endif
}

void APP_DEBUG_FINALIZE()
{
#ifdef WIN32
    FreeConsole();
#endif
}

void APP_DEBUG_OUT(const char * format, ...)
{
    va_list args;
    //int num = 0;
    size_t len = 0;
    size_t idx = 0;
    char data[4096];

    APP_API_MEMSET(data, 0, 4096);

    time_t lt;

    lt = time(NULL);
    APP_API_SPRINTF(data, sizeof (data) - 1, "%s", asctime(gmtime(&lt)));
    idx += APP_API_STRLEN(data);
    data[idx - 1] = ' ';

    va_start(args, format);
    len = APP_API_STRLEN((char *) format);

    for (size_t i = 0; i < len; i++)
    {
        if ('%' == format[i])
        {
            switch (format[i + 1])
            {
            case 'd':
            {
                int value = va_arg(args, int);
                char temp[ 12 ] = {0};
                APP_API_ITOA(value, temp, 10);
                size_t length = APP_API_STRLEN(temp);
                APP_API_MEMCPY(data + idx, temp, length);
                idx += length;
                i++;
            }
                break;
            case 's':
            {
                char * value = va_arg(args, char *);
                if (NULL != value)
                {
                    size_t length = APP_API_STRLEN(value);
                    APP_API_MEMCPY(data + idx, value, length);
                    idx += length;
                }
                i++;
            }
                break;
            default:
                break;
            }
        }
        else
        {
            data[ idx++ ] = format[i];
        }
    }

    va_end(args);
    printf("%s",data);
    //std::cout << data; // << std::endl;
}

int APP_API_ATOI(const char * data)
{
    return atoi(data);
}

char * APP_API_FTOA(float num, char * str, int digits)
{
#ifdef WIN32
    return _gcvt(num, digits, str);
#else
    snprintf(str, 31, "%f", num);
    return str;
#endif
}

double APP_API_ATOF(const char * str)
{
    return atof(str);
}

char * APP_API_ITOA(int num, char * str, int radix)
{
    const char table[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *ptr = str;
    bool negative = false;

    if (num == 0)
    {
        //num=0
        *ptr++ = '0';
        *ptr = '\0'; // don`t forget the end of the string is '\0'!!!!!!!!!
        return str;
    }

    if (num < 0)
    {
        //if num is negative ,the add '-'and change num to positive
        *ptr++ = '-';
        num *= -1;
        negative = true;
    }

    while (num)
    {
        *ptr++ = table[ num % radix ];
        num /= radix;
    }
    *ptr = '\0'; //if num is negative ,the add '-'and change num to positive
    // in the below, we have to converse the string
    char *start = (negative ? str + 1 : str); //now start points the head of the string
    ptr--; //now prt points the end of the string
    while (start < ptr)
    {
        char temp = *start;
        *start = *ptr;
        *ptr = temp;
        start++;
        ptr--;
    }

    return str;
}

APP_FILE_HANDLE APP_API_FILE_OPEN(const char * filename, const char * flag)
{
    int i = 0;

    while (i < MAX_FILE_LIST && l_file_list[i] != NULL)
    {
        i++;
    }

    if (i == MAX_FILE_LIST)
    {
        return 0;
    }

    FILE * file = fopen(filename, flag);

    if (NULL == file)
    {
        return 0;
    }

    l_file_list[i] = file;
    return i + 1;
}

void APP_API_FILE_CLOSE(APP_FILE_HANDLE handle)
{
    fclose(l_file_list[handle - 1]);
    l_file_list[handle - 1] = NULL;
}

int APP_API_FILE_READ(void * dest, int element_size, int count, APP_FILE_HANDLE handle)
{
    return (int)fread(dest, element_size, count, l_file_list[handle - 1]);
}

int APP_API_FILE_WRITE(void * src, int element_size, int count, APP_FILE_HANDLE handle)
{
    return (int)fwrite(src, element_size, count, l_file_list[handle - 1]);
}

int APP_API_FILE_GET_LENGTH(APP_FILE_HANDLE handle)
{
    int pos_beg = 0;
    int pos_end = 0;

    fseek(l_file_list[handle - 1], 0, SEEK_SET);
    pos_beg = ftell(l_file_list[handle - 1]);

    fseek(l_file_list[handle - 1], 0, SEEK_END);
    pos_end = ftell(l_file_list[handle - 1]);

    fseek(l_file_list[handle - 1], 0, SEEK_SET);
    return (pos_end - pos_beg);
}

/**
 * Parse one line once, and the seperator is "\n".
 *
 * @param:
 *		int pos: start from 0
 * @return
 *		int:
 */
int APP_API_PARSE_DATA(const char * src, char *dst, int pos, char seperator)
{
    dst[0] = 0;
    int idx = 0;
    int idx0 = 0;
    int idx_beg = -1;

    while (src[idx] != 0)
    {
        if (src[idx] == seperator)
        {
            idx++;
            pos--;
            continue;
        }

        if (pos == 0)
        {
            if (idx_beg < 0)
            {
                idx_beg = idx;
            }
            dst[idx0] = src[idx];
            dst[idx0 + 1] = 0;
            idx0++;
        }
        else if (pos < 0)
        {
            break;
        }

        idx++;
    }

    return idx_beg;
}

unsigned long APP_API_GET_DATE(int year, int month, int day, int hour, int minute)
{
    time_t rawtime;
    time(&rawtime);
    tm *tmp = localtime(&rawtime);
    tmp->tm_year = year - 1900;
    tmp->tm_mon = month - 1;
    tmp->tm_mday = day;
    tmp->tm_hour = hour;
    tmp->tm_min = minute;
    time_t time = mktime(tmp);

    return static_cast<unsigned long> (time);
}

u64 APP_API_GET_TIME()
{
#ifdef WIN32
    __int64 timeval;
    _time64(&timeval);

    return timeval * 1000;
#elif MAC
    return GetMSTime();
#else // linux
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); //get the current time
    return ts.tv_sec * 1000 + ts.tv_nsec / (1000 * 1000);
#endif
}

void APP_API_GET_FORMAT_TIME(char * buffer)
{
#ifdef WIN32
    time_t lt;

    lt = time(NULL);
    APP_API_SPRINTF(buffer, 64, "%s", asctime(gmtime(&lt)));
#else

#endif
}

u64 APP_API_GET_TICK_COUNT()
{
#ifdef WIN32
    return GetTickCount();
#else
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000+tv.tv_usec/1000);
#endif
} 

int APP_API_GET_RANDOM(char * name)
{
    int offset = 0;
    srand((unsigned) time(NULL));
    if (NULL != name)
    {
        size_t len = APP_API_STRLEN(name);
        for (size_t i = 0; i < len; i++)
        {
            offset += name[i];
        }
    }
    return ( rand() + offset);
}

int APP_API_IP_STR2INT(char * ip)
{
    int value = 0;
    char * last = NULL;
    char * curr = NULL;

    last = ip;

    for (int i = 0; i < 4; i++)
    {
        int len = 0;
        char ip_addr[16] = {0};

        curr = APP_API_STRSTR(last, ".");
        if (NULL == curr)
        {
            APP_API_MEMSET(ip_addr, 0, 16);
            APP_API_STRCPY(ip_addr, last);
            value |= (APP_API_ATOI(ip_addr) & 0xFF) << 8 * i;
            break;
        }
        len = static_cast<int> (curr - last);
        APP_API_MEMSET(ip_addr, 0, 16);
        APP_API_MEMCPY(ip_addr, last, len);

        value |= (APP_API_ATOI(ip_addr) & 0xFF) << 8 * i;

        last = curr + 1;
    }

    return value;
}

char * APP_API_IP_INT2STR(int ip, char * buffer)
{
    int ip1 = ip & 0x000000FF;
    int ip2 = (ip & 0x0000FF00) >> 8;
    int ip3 = (ip & 0x00FF0000) >> 16;
    int ip4 = (ip & 0xFF000000) >> 24;

    APP_API_SPRINTF(buffer, 16, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
    return buffer;
}

int APP_API_GETLASTERR()
{
#ifdef WIN32
    return GetLastError();
#else
    return errno;
#endif
}

char* APP_API_GETCWD(char* Dst, int sizebytes)
{
#ifdef WIN32
    return _getcwd(Dst, sizebytes);
#else
    return getcwd(Dst, sizebytes);
#endif
}

const char* APP_API_GET_SIMPLE_FILE_NAME( const char* path )
{
    int len = (int)APP_API_STRLEN(path);

    for (int i = len - 1; i >= 0; --i)
    {
        if (path[i] == '\\' || path[i] == '/')
            return path + i + 1;
    }

    return "";
}

hash_t APP_API_STRHASH( const char* str, size_t len )
{
    hash_t hash = 0;

    while(true)
    {
        switch(len)
        {
        case 0:
            return hash;

        case 1:
            hash *= 37;
            hash += *(uchar_t*)str;
            return hash;

        case 2:
            hash *= 37;
            hash += *(ushort_t*)str;
            return hash;

        case 3:
            hash *= 37;
            hash += (*(ushort_t*)str << 8) + ((uchar_t*)str)[2];
            return hash;

        default:
            hash *= 37;
            hash += *(uint_t*)str;
            str += 4;
            len -= 4;
            break;
        }
    }

    return hash;
}
