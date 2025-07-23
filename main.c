#include <libavcodec/avcode.h>
#include <libavformat/avformat.h>
#include <ffmpeg/swscale.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    av_register_all(); // Register all aval file format/codcs
    //struct w/ info
    AVFormatContext *pFormatCtx = NULL;

    //open file
    if(avformat_open_input(&pFormatCtx, argv[1], NULL, 0, NULL) != 0){
        perror("Could not open file");
        return -1; // call function and stop if open fails
    }
    // fun hat populates pformatctx->streams    
    if(avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        perror("Could not find stream info");
        return -1; // cant find stream info
    }

    //Dump info abt file into std error
    // pformat-> streams is an arr of ptrs
    av_dump_format(pFormatCtx, 0, argv[1], 0);
        
    // look for a vid stream
    AVCodeContext *pCodecCtxOrig = NULL;
    AVCodeContext *pCodecCtx = NULL;
    vidStream = -1;
    for(int i = 0; i < pFormatCtx->nb_streams; i++) {
        // goes over each stream codec to see if one matches avmedia type
        if(pFormatCtx0->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            vidStream = i; // the one that finds is a video
            break;
        }
    }
    if(vidStream == -1) {
        perror("No video stream found");
        return -1;
    } // No video find

    // pointer to codec for vid streams
    pCodecCtx = pFormatCtx->streams[vidStream]->codec; 

    //*** Find Codec & open it */
    AVCodec *pCodec = NULL;
    return 0;
}
 