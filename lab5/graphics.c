#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include "graphics.h"

int (set_graphic_mode)(uint16_t submode) {
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86)); //! Zero the structure (make sure it's clean)
  
  reg86.intno = 0x10;
  reg86.ah = 0x4F;
  reg86.al = 0x02;
  reg86.bx = submode | BIT(14);

  if(sys_int86(&reg86) != OK) return 1;
  return 0;
}

int (set_text_mode)() {
  reg86_t reg86;
  memset(&reg86, 0, sizeof(reg86));

  reg86.intno = 0x10;
  reg86.ah = 0x00;
  reg86.al = 0x03;
  reg86.bx = 0x0000;  //! Para que é que serve cada um?!

  if(sys_int86(&reg86) != OK) return 1;
  return 0;
}

void *(vg_init)(uint16_t mode) {
  vbe_mode_info_t vbe_info;

  // 1. Retrieve information about the requested graphics mode (screen resolution, bites per pixel, physical addres of VRAM)
  if(vbe_get_mode_info(mode, &vbe_info) != OK) return NULL;

  reg86_t reg86;

  // 2. Clear the structure to ensure there is no garbage data
  memset(&reg86, 0, sizeof(reg86)); //! Zero the structure (make sure it's clean)

  // 3. Set up the registers for the BIOS interrupt call (INT 0x10)
  reg86.intno = 0x10; // BIOS video interrupt
  reg86.ah = 0x4F;  // VBE call 
  reg86.al = 0x02;  // Set VBE mode function
  reg86.bx = mode | BIT(14);  // Mode number + request linear framebuffer (bit 14)

  // 4. Perform the BIOS interrupt to change the video mode
  if (sys_int86(&reg86) != OK) return NULL;

  // 5. Retrieve the physical address of the video memory (framebuffer)
  phys_bytes phys_addr = vbe_info.PhysBasePtr;

  // 6. Calculate the size of the framebuffer (width * height * bytes per pixel)
  unsigned int framebuffer_size = vbe_info.XResolution * vbe_info.YResolution * (vbe_info.BitsPerPixel / 8);

  struct minix_mem_range mr;
  mr.mr_base = phys_addr;
  mr.mr_limit = mr.mr_base + framebuffer_size;

  // 7. Request permission to map the video memory into the process address space
  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) return NULL;

  // 8. Map the physical video memory into the process virtual memory space
  void *framebuffer = vm_map_phys(SELF, (void *)phys_addr, framebuffer_size);
  if(framebuffer == MAP_FAILED) return NULL;

  // 9. Return the mapped virtual address to access the video memory
  return framebuffer;
}
