#include "graphics.h"
#include "../utils/result.h"
#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <string.h>

// Global variable to store VBE mode information
vbe_mode_info_t mode_info;

// Pointers and variables to store video memory and resolution details
void           *video_mem;
static uint16_t h_res;
static uint16_t v_res;
static uint8_t  bits_per_pixel;
static uint32_t fb_size = 0;

Result(set_text_mode)() {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = 0x10;
    reg86.ah    = 0x00;
    reg86.al    = 0x03;
    reg86.bx    = 0x0000;

    if (sys_int86(&reg86) != RES_OK) return RES_HARDWARE_ERROR;
    return RES_OK;
}

Result(set_graphic_mode)(uint16_t submode) {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = 0x10;
    reg86.ah    = 0x4F;
    reg86.al    = 0x02;
    reg86.bx    = submode | BIT(14);

    if (sys_int86(&reg86) != RES_OK) return RES_HARDWARE_ERROR;
    return RES_OK;
}

Result(res_vg_init)(uint16_t mode, void **video_memory) {
    if (video_memory == NULL) return RES_INVALID_ARGUMENT;

    if (vbe_get_mode_info(mode, &mode_info) != RES_OK) return RES_UNSUPPORTED_MODE;

    h_res          = mode_info.XResolution;
    v_res          = mode_info.YResolution;
    bits_per_pixel = mode_info.BitsPerPixel;

    phys_bytes phys_addr = mode_info.PhysBasePtr;
    /* compute and store framebuffer size directly */
    fb_size              = mode_info.XResolution * mode_info.YResolution * (mode_info.BitsPerPixel / 8);

    struct minix_mem_range mr;
    mr.mr_base  = phys_addr;
    mr.mr_limit = mr.mr_base + fb_size - 1;

    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != RES_OK) return RES_PERMISSION_ERROR;

    void *mapped_mem = vm_map_phys(SELF, (void *)phys_addr, fb_size);
    if (mapped_mem == MAP_FAILED) return RES_MEMORY_ERROR;

    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.intno = 0x10;
    reg86.ah    = 0x4F;
    reg86.al    = 0x02;
    reg86.bx    = mode | BIT(14);

    if (sys_int86(&reg86) != RES_OK) return RES_HARDWARE_ERROR;

    *video_memory = mapped_mem;
    video_mem     = mapped_mem; // Linha bênção que fez retângulo desenhar
    return RES_OK;
}

Result(res_normalize_color)(uint32_t *color) {
    if (mode_info.MemoryModel == 4 || mode_info.BitsPerPixel == 8) {
        // Indexed color
        *color &= ((1 << mode_info.BitsPerPixel) - 1);
        return RES_OK;
    }

    // Direct color
    uint32_t color_copy = *color;
    uint32_t r          = (color_copy >> mode_info.RedFieldPosition) & ((1 << mode_info.RedMaskSize) - 1);
    uint32_t g          = (color_copy >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize) - 1);
    uint32_t b          = (color_copy >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize) - 1);
    *color
        = (r << mode_info.RedFieldPosition) | (g << mode_info.GreenFieldPosition) | (b << mode_info.BlueFieldPosition);
    return RES_OK;
}

Result(res_vg_draw_pixel)(void *buf, uint16_t x, uint16_t y, uint32_t color) {
    if (x >= h_res || y >= v_res) return RES_INVALID_ARGUMENT;
    uint8_t  bytes_per_pixel = (bits_per_pixel + 7) / 8;
    uint32_t index           = (y * h_res + x) * bytes_per_pixel;
    res_normalize_color(&color);
    if (memcpy((uint8_t *)buf + index, &color, bytes_per_pixel) == NULL) return RES_MEMORY_ERROR;
    return RES_OK;
}

Result(res_vg_draw_hline)(void *buf, uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (uint16_t i = 0; i < len; i++)
        if (res_vg_draw_pixel(buf, x + i, y, color) != RES_OK) return RES_IO_ERROR;
    return RES_OK;
}

Result(res_vg_draw_rectangle)(void *buf, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (uint16_t i = 0; i < height; i++)
        if (res_vg_draw_hline(buf, x, y + i, width, color) != RES_OK) return RES_IO_ERROR;
    return RES_OK;
}

Result(get_framebuffer_size)(uint32_t *size) {
    if (size == NULL) return RES_INVALID_ARGUMENT;
    if (fb_size == 0) return RES_UNINITIALIZED;
    *size = fb_size;
    return RES_OK;
}
