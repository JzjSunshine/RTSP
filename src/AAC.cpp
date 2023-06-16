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
    this->frame = (uint8_t*)malloc(5000);
}

int AACParser::parseAdtsHeader(uint8_t* in){
    memset(adtdHeader, 0, sizeof(*adtdHeader));

    if ((in[0] == 0xFF) && ((in[1] & 0xF0) == 0xF0))
    {
        adtdHeader->id = ((uint8_t)in[1] & 0x08) >> 3;//第二个字节与0x08与运算之后，获得第13位bit对应的值
        adtdHeader->layer = ((uint8_t)in[1] & 0x06) >> 1;//第二个字节与0x06与运算之后，右移1位，获得第14,15位两个bit对应的值
        adtdHeader->protectionAbsent = (uint8_t)in[1] & 0x01;
        adtdHeader->profile = ((uint8_t)in[2] & 0xc0) >> 6;
        adtdHeader->samplingFreqIndex = ((uint8_t)in[2] & 0x3c) >> 2;
        adtdHeader->privateBit = ((uint8_t)in[2] & 0x02) >> 1;
        adtdHeader->channelCfg = ((((uint8_t)in[2] & 0x01) << 2) | (((unsigned int)in[3] & 0xc0) >> 6));
        adtdHeader->originalCopy = ((uint8_t)in[3] & 0x20) >> 5;
        adtdHeader->home = ((uint8_t)in[3] & 0x10) >> 4;
        adtdHeader->copyrightIdentificationBit = ((uint8_t)in[3] & 0x08) >> 3;
        adtdHeader->copyrightIdentificationStart = (uint8_t)in[3] & 0x04 >> 2;
        
        adtdHeader->aacFrameLength = (((((unsigned int)in[3]) & 0x03) << 11) |
            (((unsigned int)in[4] & 0xFF) << 3) |
            ((unsigned int)in[5] & 0xE0) >> 5);

        adtdHeader->adtsBufferFullness = (((unsigned int)in[5] & 0x1f) << 6 |
            ((unsigned int)in[6] & 0xfc) >> 2);
        adtdHeader->numberOfRawDataBlockInFrame = ((uint8_t)in[6] & 0x03);

        return 0;
    }
    else
    {
        printf("failed to parse adts header\n");
        return -1;
    }
}
