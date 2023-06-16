#include "AAC.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
AACParser::AACParser(const char *filename)
{
    this->fd = open(filename, O_RDONLY);
    assert(this->fd >= 0);

    struct stat st;
    fstat(this->fd, &st);

    this->fileSize = st.st_size;
    

}
