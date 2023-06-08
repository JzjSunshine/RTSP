/*
 * @Author: your name
 * @Date: 2021-06-07 16:46:34
 * @LastEditTime: 2021-06-11 13:55:11
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /rtsp/src/main.cc
 */
#include "../include/rtsp.h"
#include "../include/Utils.h"
#include <iostream>
#include <cstdlib>
#include <string>


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stdout, "usage: %s <file name> <fileType(video/audio)\n", argv[0]);
        return 1;
    }
    std::string fileType = argv[2];

    if(fileType != "video" && fileType != "audio"){
        fprintf(stdout, "usage: %s <file name> <fileType(video/audio)>\n", argv[0]);
        return 1;
    }
    RTSP rtspServer(argv[1]);
    Tookit tookit(argv[1]);
    int fps = 0;
    if(fileType == "video"){
        fps = tookit.getFPSVideo();
    }else{
        fps = tookit.getFPSAudio();
    }
    std::cout << "fps: " << fps << std::endl;
    rtspServer.Start(19990825, "wadegao", 600, 25);
    // rtspServer.Start(19990825, "wadegao", 600, double(fps));

    return 0;
}
