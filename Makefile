vidply: vidply.c
    $(CC) vidply.c -o vidply -lavformat -lavcodec -lz -lm -std=c11