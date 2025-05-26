#include "graphics.h"
#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <string.h>

vbe_mode_info_t mode_info; // Define the global mode_info here

static void    *video_mem;
static uint16_t h_res;
static uint16_t v_res;
static uint8_t  bits_per_pixel;

int(set_graphic_mode)(uint16_t submode) {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86)); //! Zero the structure (make sure it's clean)

    reg86.intno = 0x10;
    reg86.ah    = 0x4F;
    reg86.al    = 0x02;
    reg86.bx    = submode | BIT(14);

    if (sys_int86(&reg86) != OK) return 1;
    return 0;
}

int(set_text_mode)() {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = 0x10;
    reg86.ah    = 0x00;
    reg86.al    = 0x03;
    reg86.bx    = 0x0000; //! Para que é que serve cada um?!

    if (sys_int86(&reg86) != OK) return 1;
    return 0;
}

void *(vg_init)(uint16_t mode) {
    // Use the global mode_info
    if (vbe_get_mode_info(mode, &mode_info) != OK) return NULL;

    h_res          = mode_info.XResolution;
    v_res          = mode_info.YResolution;
    bits_per_pixel = mode_info.BitsPerPixel;

    phys_bytes   phys_addr        = mode_info.PhysBasePtr;
    unsigned int framebuffer_size = mode_info.XResolution * mode_info.YResolution * (mode_info.BitsPerPixel / 8);

    struct minix_mem_range mr;
    mr.mr_base  = phys_addr;
    mr.mr_limit = mr.mr_base + framebuffer_size - 1;

    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) return NULL;

    video_mem = vm_map_phys(SELF, (void *)phys_addr, framebuffer_size);
    if (video_mem == MAP_FAILED) return NULL;

    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.intno = 0x10;
    reg86.ah    = 0x4F;
    reg86.al    = 0x02;
    reg86.bx    = mode | BIT(14);

    if (sys_int86(&reg86) != OK) return NULL;

    return video_mem;
}

uint32_t normalize_color(uint32_t color) {
    if (mode_info.MemoryModel == 4 || mode_info.BitsPerPixel == 8) {
        // Indexed color
        return color & ((1 << mode_info.BitsPerPixel) - 1);
    } else {
        // Direct color
        uint32_t r = (color >> mode_info.RedFieldPosition) & ((1 << mode_info.RedMaskSize) - 1);
        uint32_t g = (color >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize) - 1);
        uint32_t b = (color >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize) - 1);
        return (r << mode_info.RedFieldPosition) | (g << mode_info.GreenFieldPosition)
               | (b << mode_info.BlueFieldPosition);
    }
}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
    if (x >= h_res || y >= v_res) return 1;
    uint8_t  bytes_per_pixel  = (bits_per_pixel + 7) / 8;
    uint32_t index            = (y * h_res + x) * bytes_per_pixel;
    uint32_t normalized_color = normalize_color(color);
    if (memcpy((uint8_t *)video_mem + index, &normalized_color, bytes_per_pixel) == NULL) return 1;
    return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (uint16_t i = 0; i < len; i++) {
        if (vg_draw_pixel(x + i, y, color) != OK) return 1;
    }
    return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for (uint16_t i = 0; i < height; i++) {
        if (vg_draw_hline(x, y + i, width, color) != OK) return 1;
    }
    return 0;
}
