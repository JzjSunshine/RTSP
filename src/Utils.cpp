#include "Utils.h"

Tookit::Tookit(const char *filename){
    FileName = filename;

    av_register_all();
    format_ctx = avformat_alloc_context();
    avg_frame_duration = 0;
    video_stream_index = -1;
}

int Tookit::getFPSVideo()
{
    if (avformat_open_input(&format_ctx, FileName, NULL, NULL) != 0) {
        std::cout << "Failed to open file " << FileName << std::endl;
        return -1;
    }
    if(avformat_find_stream_info(format_ctx, NULL) < 0){
        std::cout << "Failed to find stream information" << std::endl;
        return -1;
    }
    for (int i = 0; i < format_ctx->nb_streams; i++) {
        AVStream* stream = format_ctx->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index = i;
            avg_frame_duration = av_q2d(stream->avg_frame_rate);
            break;
        }
    }
    if(video_stream_index == -1){
        std::cout << "No video stream found in the input file " << std::endl;
        return -1;
    }
    num_frames = format_ctx->streams[video_stream_index]->nb_frames;
    duration = (double)format_ctx->streams[video_stream_index]->duration / AV_TIME_BASE;

    double fps = 1/avg_frame_duration;
    return fps;
}
int Tookit::getFPSAudio()
{
    if (avformat_open_input(&format_ctx, FileName, NULL, NULL) != 0) {
        std::cout << "Failed to open file " << FileName << std::endl;
        return -1;
    }
    if(avformat_find_stream_info(format_ctx, NULL) < 0){
        std::cout << "Failed to find stream information" << std::endl;
        return -1;
    }
    int audio_stream_index = -1;
    for (int i = 0; i < format_ctx->nb_streams; i++) {
        AVStream* stream = format_ctx->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_index = i;
            avg_frame_duration = av_q2d(stream->avg_frame_rate);
            break;
        }
    }
    if(video_stream_index == -1){
        std::cout << "No audio stream found in the input file " << std::endl;
        return -1;
    }
    // num_frames = format_ctx->streams[video_stream_index]->nb_frames;
    // duration = (double)format_ctx->streams[video_stream_index]->durtion / AV_TIME_BASE;
    int sample_rate = format_ctx->streams[audio_stream_index]->codecpar->sample_rate;

    int fps = sample_rate;
    return fps;
}

Tookit::~Tookit(){
    if(format_ctx != nullptr)
    {
        avformat_close_input(&format_ctx);
        avformat_free_context(format_ctx);
    }

}