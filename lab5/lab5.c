// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "graphics.h"
#include "kbd.h"
#include <lcom/xpm.h> // Use system header
#include <lcom/pixmap.h> // Use system header

extern int count;
extern vbe_mode_info_t mode_info;
extern uint16_t scancode;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/shared/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/shared/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  // Switch video adapter to graphics mode
  if(vg_init(mode) == NULL) return 1;

  sleep(delay);

  // Switch video adapter to text mode
  if(vg_exit() != OK) return 1;

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  int ipc_sta;
  uint8_t kbd_mask;
  message msg;                 

  scancode = 0;
  // Switch video adapter to graphics mode
  if(vg_init(mode) == NULL) return 1;

  // Draw the rectangle immediately after switching to graphics mode
  if(vg_draw_rectangle(x, y, width, height, color) != OK) return 1; 

  // Subscribe keyboard interrupts
  if(kbd_subscribe_int(&kbd_mask) != OK) return 1;

  while(scancode != 0x81) {
    if(driver_receive(ANY, &msg, &ipc_sta) != OK) continue;

    if(is_ipc_notify(ipc_sta)) {
      if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
        if(msg.m_notify.interrupts & kbd_mask) {
          kbc_ih();
        }
      }
    }
  }
      
  // Unsubscribe keyboard interrupts
  if(kbd_unsubscribe_int() != OK) return 1;

  // Switch video adapter to text mode
  if(vg_exit() != OK) return 1;

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  scancode = 0;
  // Switch video adapter to graphics mode
  if(vg_init(mode) == NULL) return 1;

  uint16_t rect_width = mode_info.XResolution / no_rectangles;
  uint16_t rect_height = mode_info.YResolution / no_rectangles;

  for (uint8_t row = 0; row < no_rectangles; row++) {
    for (uint8_t col = 0; col < no_rectangles; col++) {
      uint32_t color;
      if (mode_info.MemoryModel == 4 || mode_info.BitsPerPixel == 8) { // Indexed color
        color = (first + (row * no_rectangles + col) * step) % (1 << mode_info.BitsPerPixel);
      } else { // Direct color
        uint32_t r = (first >> mode_info.RedFieldPosition) & ((1 << mode_info.RedMaskSize) - 1);
        uint32_t g = (first >> mode_info.GreenFieldPosition) & ((1 << mode_info.GreenMaskSize) - 1);
        uint32_t b = (first >> mode_info.BlueFieldPosition) & ((1 << mode_info.BlueMaskSize) - 1);
        r = (r + col * step) % (1 << mode_info.RedMaskSize);
        g = (g + row * step) % (1 << mode_info.GreenMaskSize);
        b = (b + (col + row) * step) % (1 << mode_info.BlueMaskSize);
        color = (r << mode_info.RedFieldPosition) |
                (g << mode_info.GreenFieldPosition) |
                (b << mode_info.BlueFieldPosition);
      }
      vg_draw_rectangle(col * rect_width, row * rect_height, rect_width, rect_height, color);
    }
  }

  int ipc_sta;
  uint8_t kbd_mask;
  message msg;
  if(kbd_subscribe_int(&kbd_mask) != OK) return 1;
  while(scancode != 0x81) {
    if(driver_receive(ANY, &msg, &ipc_sta) != OK) continue;
    if(is_ipc_notify(ipc_sta)) {
      if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
        if(msg.m_notify.interrupts & kbd_mask) {
          kbc_ih();
        }
      }
    }
  }
  if(kbd_unsubscribe_int() != OK) return 1;
  if(vg_exit() != OK) return 1;
  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  scancode = 0;
  if(vg_init(0x105) == NULL) return 1;

  xpm_image_t img;
  uint8_t *map = xpm_load(xpm, XPM_INDEXED, &img);
  if (map == NULL) {
    vg_exit();
    return 1;
  }

  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      vg_draw_pixel(x + j, y + i, map[i * img.width + j]);
    }
  }

  int ipc_sta;
  uint8_t kbd_mask;
  message msg;
  if(kbd_subscribe_int(&kbd_mask) != OK) { vg_exit(); return 1; }
  while(scancode != 0x81) {
    if(driver_receive(ANY, &msg, &ipc_sta) != OK) continue;
    if(is_ipc_notify(ipc_sta)) {
      if(_ENDPOINT_P(msg.m_source) == HARDWARE) {
        if(msg.m_notify.interrupts & kbd_mask) {
          kbc_ih();
        }
      }
    }
  }
  if(kbd_unsubscribe_int() != OK) return 1;
  if(vg_exit() != OK) return 1;
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  scancode = 0;
  if (vg_init(0x105) == NULL) return 1;

  xpm_image_t img;
  uint8_t *map = xpm_load(xpm, XPM_INDEXED, &img);
  if (map == NULL) {
    vg_exit();
    return 1;
  }

  int ipc_sta;
  uint8_t kbd_mask, timer_mask;
  message msg;
  int frame_counter = 0;
  int total_frames;
  int dx = 0, dy = 0;
  int x = xi, y = yi;

  // Calculate movement direction and total frames
  if (xi == xf) {
    dy = (yf > yi) ? 1 : -1;
    total_frames = abs(yf - yi) / (speed > 0 ? speed : 1);
  } else {
    dx = (xf > xi) ? 1 : -1;
    total_frames = abs(xf - xi) / (speed > 0 ? speed : 1);
  }
  if (speed < 0) total_frames = abs((xi == xf ? yf - yi : xf - xi)) / abs(speed);

  // Subscribe interrupts
  if (kbd_subscribe_int(&kbd_mask) != OK) { vg_exit(); return 1; }
  if (timer_subscribe_int(&timer_mask) != OK) { kbd_unsubscribe_int(); vg_exit(); return 1; }

  int timer_ticks = 0;
  int ticks_per_frame = sys_hz() / fr_rate;

  // Initial draw
  for (int i = 0; i < img.height; i++)
    for (int j = 0; j < img.width; j++)
      vg_draw_pixel(x + j, y + i, map[i * img.width + j]);

  while (scancode != 0x81) {
    if (driver_receive(ANY, &msg, &ipc_sta) != OK) continue;
    if (is_ipc_notify(ipc_sta)) {
      if (_ENDPOINT_P(msg.m_source) == HARDWARE) {
        if (msg.m_notify.interrupts & timer_mask) {
          timer_ticks++;
          if (timer_ticks % ticks_per_frame == 0 && frame_counter < total_frames) {
            // Erase previous
            for (int i = 0; i < img.height; i++)
              for (int j = 0; j < img.width; j++)
                vg_draw_pixel(x + j, y + i, 0); // 0 = background color
            // Move
            if (speed > 0) {
              x += dx * speed;
              y += dy * speed;
            } else if (speed < 0) {
              x += dx;
              y += dy;
            }
            // Draw new
            for (int i = 0; i < img.height; i++)
              for (int j = 0; j < img.width; j++)
                vg_draw_pixel(x + j, y + i, map[i * img.width + j]);
            frame_counter++;
          }
        }
        if (msg.m_notify.interrupts & kbd_mask) {
          kbc_ih();
        }
      }
    }
  }

  timer_unsubscribe_int();
  kbd_unsubscribe_int();
  vg_exit();
  return 0;
}

int(video_test_controller)() {
  /* This year you do not need to implement this */
  printf("%s(): under construction\n", __func__);

  return 1;
}
