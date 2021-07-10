#ifndef __GL_UTILS_H__
#define __GL_UTILS_H__

#include <signal.h>

#define glCall(f) glPurgeErrors();\
    f;\
    if (glRetrieveErrors(__FILE__, __LINE__)) raise(SIGTRAP)

void glPurgeErrors(void);
bool glRetrieveErrors(const char* file, int line_number);

#endif // __GL_UTILS_H__
