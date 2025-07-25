#include <ffmpeg/swscale.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

#include <stdlib.h>
#include <stdio.h>

#include "saveFrame.c"

int main(int argc, char *argv[]) {
    av_register_all(); // Register all aval file format/codcs
    //struct w/ info
    AVFormatContext *pFormatCtx = NULL;

    //open file
    if(avformat_open_input(&pFormatCtx, argv[1], NULL, 0, NULL) != 0){
        perror("FL1: Could not open file");
        return -1; // call function and stop if open fails
    }
    // fun hat populates pformatctx->streams    
    if(avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        perror("FL2: Could not find stream info");
        return -1; // cant find stream info
    }

    //Dump info abt file into std error
    // pformat-> streams is an arr of ptrs
    av_dump_format(pFormatCtx, 0, argv[1], 0);
        
    //************ Look for a vid stream */
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
        perror("FL3: No video stream found");
        return -1;
    } // No video find

    // pointer to codec for vid streams
    pCodecCtx = pFormatCtx->streams[vidStream]->codec; 

    //*** Find Codec & open it */
    // We oughta not use the AVCodeContext from the vid stream directly
    // copy it to use it by allocating memory
    AVCodec *pCodec = NULL;
    //find decoder
    pCodec = avcodec_find_decoder(pCodeCtx->codec_id); 
    if(pCodec == NULL ){
        perror("CD 1: Unsupported codec!!");
        return -1; // codec not identified or unsupported
    }
    //Copy context
    pCodecCts = avcodec_alloc_context3(pCoded);
    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
        perror("CD 2: Could not copy codec context! ");
        return -1; // Error w/ copying cotext codec
    }
    // open codec
    if(avcodec_open2(pCodeCtx, pCodec)  < 0) {
        perror("CD 3: Could not open codec");
        return -1;
    }

    // *** Store each frame */
    AVFrame *pFram = NULL, *pFrameRGB = NULL;
    pFrame = av_frame_alloc(); // allocate vid frame
    pFrameRGB = av_frame_alloc(); // allocate and AV Frame structure
    if(pFrameRGB == NUL) { 
        perror("VF 1: Error allocating frame");
        return -1;
    }
    // get size required
    unint8_t *buffer = NULL;
    int numBytes = avpicture_get_size(PIC_FMT_RGB24, pCodecCtx->width, pCodecCtx->height); // size of pciture
    buffer = (unint8_t *) av_malloc(numBytes * sizeof(unint8_t)); // malloc wrapper
    /* asign parts of buffer to image planes in pFramRGB*/
    // AVFrame is a superset of AVPicture
    avpicture_fill((AVPicture *) pFrameRGB, buffer,  PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
    

    /* READING VIDEO Stream*/
    struct SwsContext *sws_ctx = NULL;
    int frameFinished;
    AVPacket packet; // AV PACKETS
    // initializing
    sws_ctx = sws_getContext(pCodecCtx->width, 
        pCodecCtx->height,
        pCodecCtx->pix_fmt,
        pCodecCtx->width, 
        pCodecCtx->height,
        PIX_FMT_RGB24,
        SWS_BILINEAR,
        NULL, NULL, NULL);
    int i = 0;
    // readeing frames  & STORE IT in &packet struc
    while(av_read_frame(pFormatCtx, &packet) >= 0) {
        // is packet from vid stream?
        if(packet.stream_index == vidStream) {
            avcodec_decode_video2(pCodeCtx, pFrame, &frameFinished, &packet);//Decode frame aka convert packet to frame

            // Got the vid frame?
            if(frameFinished) {
                // convert to rgb type
                sws_scale(sws_ctx, (unint8_t cont * const *) pFrame->data,
                    pFrame->linesize, 0, pCodecCtx->height, pFrameRGb->data, pFrameRGB->linesize);
                // save frame to disk
                if(++i<=5) 
                    SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height, i); // from saveframe.c
            }

        }
        av_free_packet(&packet); // free packet allocated
    }

    /* Done from READING and clean all up*/
    av_free(buffer);
    av_free(pFrameRGB);

    // free yuv frame
    av_free(pFrame);

    //close codecs
    avcodec_close(pCodecCtx);
    avcodec_close(pCodecCtxOrig);

    //close file video
    avformat_close_input(&pFormatCtx);

    return 0;
}
