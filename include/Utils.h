#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <iostream>
#include <string>

extern "C"{
    #include <libavutil/frame.h>
    #include <libavutil/mem.h>
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
}


class Tookit{

public:
    explicit Tookit(const char *filename);
    ~Tookit();
    int getFPSVideo();
    int getFPSAudio();
private:
    const char * FileName;
    AVFormatContext *format_ctx = nullptr;
    double avg_frame_duration = 0;
    int video_stream_index = -1;
    int num_frames = 0;
    double duration = 0;

};
#endif