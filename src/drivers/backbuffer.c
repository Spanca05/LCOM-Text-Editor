#include "backbuffer.h"
#include "../utils/result.h"
#include "graphics.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Result(init_backbuffer)(void **buffer) {
    if (buffer == NULL) return RES_INVALID_ARGUMENT;

    uint32_t size;
    Result   res = get_framebuffer_size(&size);
    if (res != RES_OK) return res;

    void *buf = malloc(size);
    if (buf == NULL) return RES_MEMORY_ERROR;

    *buffer = buf;
    fprintf(stderr, "INITIALIZATION OF BACK BUFFER DONE!");
    return RES_OK;
}

Result(free_backbuffer)(void *buffer) {
    if (buffer == NULL) return RES_INVALID_ARGUMENT;

    free(buffer);
    return RES_OK;
}

Result(swap_buffers)(void *buffer) {
    if (buffer == NULL) return RES_INVALID_ARGUMENT;

    uint32_t size;
    Result   res = get_framebuffer_size(&size);
    if (res != RES_OK) return res;

    extern void *video_mem;
    if (video_mem == NULL) return RES_UNINITIALIZED;
    memcpy(video_mem, buffer, size);
    return RES_OK;
}
