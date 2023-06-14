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

    if(fileType != "h264" && fileType != "aac"){
        fprintf(stdout, "usage: %s <file name> <fileType(h264/aac)>\n", argv[0]);
        return 1;
    }
    std::string mode = fileType.c_str();
    RTSP rtspServer(argv[1],mode);
    Tookit tookit(argv[1]);
    int fps = 0;
    if(fileType == "h264"){
        fprintf(stdout,"input file type: h264\n");
        fps = tookit.getFPSVideo();
    }else{
        fprintf(stdout,"input file type: aac\n");
        fps = tookit.getFPSAudio();
    }
    std::cout << "fps: " << fps << std::endl;
    rtspServer.Start(19990825, "wadegao", 600, fps);
    // rtspServer.Start(19990825, "wadegao", 600, double(fps));

    return 0;
}
