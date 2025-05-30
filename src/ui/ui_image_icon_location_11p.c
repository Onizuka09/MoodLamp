#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif
#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IMG_ICON_LOCATION_11P
#define LV_ATTRIBUTE_IMG_IMG_ICON_LOCATION_11P
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IMG_ICON_LOCATION_11P uint8_t img_icon_location_11p_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe5, 0x4d, 0xe5, 0xd0, 0xe5, 0xf0, 0xe5, 0xd0, 0xe5, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xe5, 0x4d, 0xe5, 0xfe, 0xe5, 0xbe, 0xe5, 0x74, 0xe5, 0xbe, 0xe5, 0xfe, 0xe5, 0x4d, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xe5, 0xd0, 0xe5, 0xd0, 0xa0, 0x03, 0x00, 0x00, 0xa0, 0x03, 0xe5, 0xd0, 0xe5, 0xd0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xe5, 0xfe, 0xe5, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe5, 0xa4, 0xe5, 0xfe, 0xa0, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xe5, 0xe3, 0xe5, 0xf0, 0xe4, 0x2a, 0x00, 0x00, 0xe5, 0x28, 0xe5, 0xf0, 0xe5, 0xe3, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xe5, 0x85, 0xe5, 0xfe, 0xe5, 0xfe, 0xe5, 0xe3, 0xe5, 0xfe, 0xe5, 0xfe, 0xe5, 0x85, 0x00, 0x00, 0x00, 0x00, 
  0x0f, 0x05, 0x33, 0x70, 0x33, 0xe5, 0xc5, 0xff, 0xe5, 0xfe, 0xe5, 0xfe, 0xe5, 0xfe, 0xc5, 0xff, 0x33, 0xe5, 0x33, 0x70, 0x0f, 0x05, 
  0x33, 0xaa, 0x33, 0xf8, 0x33, 0x8d, 0x8a, 0x4d, 0xe5, 0xf0, 0xe5, 0xfe, 0xe5, 0xf0, 0x8a, 0x4d, 0x33, 0x8d, 0x33, 0xf8, 0x33, 0xaa, 
  0x33, 0xf8, 0x33, 0xe5, 0x0f, 0x05, 0x00, 0x00, 0xe5, 0x3f, 0xe5, 0xf0, 0xe5, 0x3f, 0x00, 0x00, 0x0f, 0x05, 0x33, 0xe5, 0x33, 0xf8, 
  0x33, 0x70, 0x33, 0xf8, 0x33, 0xcf, 0x33, 0x70, 0x2f, 0x43, 0x2f, 0x43, 0x2f, 0x43, 0x33, 0x70, 0x33, 0xcf, 0x33, 0xf8, 0x33, 0x70, 
  0x00, 0x00, 0x33, 0x28, 0x33, 0x8d, 0x33, 0xcf, 0x33, 0xf8, 0x33, 0xf8, 0x33, 0xf8, 0x33, 0xcf, 0x33, 0x8d, 0x33, 0x28, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xe9, 0x4d, 0x05, 0xf1, 0xd0, 0x05, 0xf1, 0xf0, 0x05, 0xf1, 0xd0, 0x05, 0xe9, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xe9, 0x4d, 0x05, 0xf1, 0xfe, 0x04, 0xf1, 0xbe, 0x04, 0xe9, 0x74, 0x04, 0xf1, 0xbe, 0x05, 0xf1, 0xfe, 0x05, 0xe9, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xf1, 0xd0, 0x05, 0xf1, 0xd0, 0x00, 0xa8, 0x03, 0x00, 0x00, 0x00, 0x00, 0xa8, 0x03, 0x05, 0xf1, 0xd0, 0x05, 0xf1, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xf1, 0xfe, 0x05, 0xf1, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xf1, 0xa4, 0x05, 0xf1, 0xfe, 0x00, 0xa8, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xe9, 0xe3, 0x05, 0xf1, 0xf0, 0x04, 0xf1, 0x2a, 0x00, 0x00, 0x00, 0xe4, 0xf0, 0x28, 0x05, 0xf1, 0xf0, 0x05, 0xe9, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xf1, 0x85, 0x05, 0xf1, 0xfe, 0x05, 0xf1, 0xfe, 0x05, 0xe9, 0xe3, 0x05, 0xf1, 0xfe, 0x05, 0xf1, 0xfe, 0x04, 0xf1, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x5a, 0x03, 0x05, 0xdd, 0x1b, 0x70, 0xdc, 0x23, 0xe5, 0x68, 0xd1, 0xff, 0x05, 0xf1, 0xfe, 0x05, 0xf1, 0xfe, 0x05, 0xf1, 0xfe, 0x68, 0xd1, 0xff, 0xdc, 0x23, 0xe5, 0xdd, 0x1b, 0x70, 0x5a, 0x03, 0x05, 
  0xdd, 0x1b, 0xaa, 0xfd, 0x1b, 0xf8, 0xdd, 0x1b, 0x8d, 0x4f, 0x92, 0x4d, 0x05, 0xf1, 0xf0, 0x05, 0xf1, 0xfe, 0x05, 0xf1, 0xf0, 0x4f, 0x92, 0x4d, 0xdd, 0x1b, 0x8d, 0xfd, 0x1b, 0xf8, 0xdd, 0x1b, 0xaa, 
  0xfd, 0x1b, 0xf8, 0xdc, 0x23, 0xe5, 0x5a, 0x03, 0x05, 0x00, 0x00, 0x00, 0xe4, 0xe8, 0x3f, 0x05, 0xf1, 0xf0, 0xe4, 0xe8, 0x3f, 0x00, 0x00, 0x00, 0x5a, 0x03, 0x05, 0xdc, 0x23, 0xe5, 0xfd, 0x1b, 0xf8, 
  0xdd, 0x1b, 0x70, 0xfd, 0x1b, 0xf8, 0xfd, 0x1b, 0xcf, 0xdd, 0x1b, 0x70, 0x9a, 0x33, 0x43, 0x9a, 0x33, 0x43, 0x9a, 0x33, 0x43, 0xdd, 0x1b, 0x70, 0xfd, 0x1b, 0xcf, 0xfd, 0x1b, 0xf8, 0xdd, 0x1b, 0x70, 
  0x00, 0x00, 0x00, 0xdd, 0x13, 0x28, 0xdd, 0x1b, 0x8d, 0xfd, 0x1b, 0xcf, 0xfd, 0x1b, 0xf8, 0xfd, 0x1b, 0xf8, 0xfd, 0x1b, 0xf8, 0xfd, 0x1b, 0xcf, 0xdd, 0x1b, 0x8d, 0xdd, 0x13, 0x28, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0x05, 0x4d, 0xf1, 0x05, 0xd0, 0xf1, 0x05, 0xf0, 0xf1, 0x05, 0xd0, 0xe9, 0x05, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0x05, 0x4d, 0xf1, 0x05, 0xfe, 0xf1, 0x04, 0xbe, 0xe9, 0x04, 0x74, 0xf1, 0x04, 0xbe, 0xf1, 0x05, 0xfe, 0xe9, 0x05, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x05, 0xd0, 0xf1, 0x05, 0xd0, 0xa8, 0x00, 0x03, 0x00, 0x00, 0x00, 0xa8, 0x00, 0x03, 0xf1, 0x05, 0xd0, 0xf1, 0x05, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x05, 0xfe, 0xf1, 0x05, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x05, 0xa4, 0xf1, 0x05, 0xfe, 0xa8, 0x00, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe9, 0x05, 0xe3, 0xf1, 0x05, 0xf0, 0xf1, 0x04, 0x2a, 0x00, 0x00, 0x00, 0xf0, 0xe4, 0x28, 0xf1, 0x05, 0xf0, 0xe9, 0x05, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x04, 0x85, 0xf1, 0x05, 0xfe, 0xf1, 0x05, 0xfe, 0xe9, 0x05, 0xe3, 0xf1, 0x05, 0xfe, 0xf1, 0x05, 0xfe, 0xf1, 0x04, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x5a, 0x05, 0x1b, 0xdd, 0x70, 0x23, 0xdc, 0xe5, 0xd1, 0x68, 0xff, 0xf1, 0x05, 0xfe, 0xf1, 0x05, 0xfe, 0xf1, 0x05, 0xfe, 0xd1, 0x68, 0xff, 0x23, 0xdc, 0xe5, 0x1b, 0xdd, 0x70, 0x03, 0x5a, 0x05, 
  0x1b, 0xdd, 0xaa, 0x1b, 0xfd, 0xf8, 0x1b, 0xdd, 0x8d, 0x92, 0x4f, 0x4d, 0xf1, 0x05, 0xf0, 0xf1, 0x05, 0xfe, 0xf1, 0x05, 0xf0, 0x92, 0x4f, 0x4d, 0x1b, 0xdd, 0x8d, 0x1b, 0xfd, 0xf8, 0x1b, 0xdd, 0xaa, 
  0x1b, 0xfd, 0xf8, 0x23, 0xdc, 0xe5, 0x03, 0x5a, 0x05, 0x00, 0x00, 0x00, 0xe8, 0xe4, 0x3f, 0xf1, 0x05, 0xf0, 0xe8, 0xe4, 0x3f, 0x00, 0x00, 0x00, 0x03, 0x5a, 0x05, 0x23, 0xdc, 0xe5, 0x1b, 0xfd, 0xf8, 
  0x1b, 0xdd, 0x70, 0x1b, 0xfd, 0xf8, 0x1b, 0xfd, 0xcf, 0x1b, 0xdd, 0x70, 0x33, 0x9a, 0x43, 0x33, 0x9a, 0x43, 0x33, 0x9a, 0x43, 0x1b, 0xdd, 0x70, 0x1b, 0xfd, 0xcf, 0x1b, 0xfd, 0xf8, 0x1b, 0xdd, 0x70, 
  0x00, 0x00, 0x00, 0x13, 0xdd, 0x28, 0x1b, 0xdd, 0x8d, 0x1b, 0xfd, 0xcf, 0x1b, 0xfd, 0xf8, 0x1b, 0xfd, 0xf8, 0x1b, 0xfd, 0xf8, 0x1b, 0xfd, 0xcf, 0x1b, 0xdd, 0x8d, 0x13, 0xdd, 0x28, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x1e, 0xeb, 0x4d, 0x24, 0x1f, 0xed, 0xd0, 0x24, 0x20, 0xed, 0xf0, 0x24, 0x1f, 0xed, 0xd0, 0x24, 0x1e, 0xeb, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x1e, 0xeb, 0x4d, 0x24, 0x20, 0xed, 0xfe, 0x23, 0x1f, 0xee, 0xbe, 0x21, 0x21, 0xeb, 0x74, 0x23, 0x1f, 0xee, 0xbe, 0x24, 0x20, 0xed, 0xfe, 0x24, 0x1e, 0xeb, 0x4d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x1f, 0xed, 0xd0, 0x24, 0x1f, 0xed, 0xd0, 0x00, 0x00, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x03, 0x24, 0x1f, 0xed, 0xd0, 0x24, 0x1f, 0xed, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x20, 0xed, 0xfe, 0x25, 0x20, 0xed, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x21, 0xec, 0xa4, 0x24, 0x20, 0xed, 0xfe, 0x00, 0x00, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x21, 0xe9, 0xe3, 0x24, 0x20, 0xed, 0xf0, 0x1e, 0x1e, 0xed, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1a, 0xec, 0x28, 0x24, 0x20, 0xed, 0xf0, 0x28, 0x21, 0xe9, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x1f, 0xee, 0x85, 0x24, 0x20, 0xed, 0xfe, 0x24, 0x20, 0xed, 0xfe, 0x28, 0x21, 0xe9, 0xe3, 0x24, 0x20, 0xed, 0xfe, 0x24, 0x20, 0xed, 0xfe, 0x23, 0x1f, 0xee, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xcc, 0x66, 0x00, 0x05, 0xe6, 0x79, 0x19, 0x70, 0xe1, 0x78, 0x1e, 0xe5, 0x40, 0x2d, 0xcf, 0xff, 0x24, 0x20, 0xed, 0xfe, 0x24, 0x20, 0xed, 0xfe, 0x24, 0x20, 0xed, 0xfe, 0x40, 0x2d, 0xcf, 0xff, 0xe1, 0x78, 0x1e, 0xe5, 0xe6, 0x79, 0x19, 0x70, 0xcc, 0x66, 0x00, 0x05, 
  0xe5, 0x79, 0x19, 0xaa, 0xe6, 0x7a, 0x19, 0xf8, 0xe6, 0x79, 0x19, 0x8d, 0x7b, 0x49, 0x8e, 0x4d, 0x24, 0x20, 0xed, 0xf0, 0x24, 0x20, 0xed, 0xfe, 0x24, 0x20, 0xed, 0xf0, 0x7b, 0x49, 0x8e, 0x4d, 0xe6, 0x79, 0x19, 0x8d, 0xe6, 0x7a, 0x19, 0xf8, 0xe5, 0x79, 0x19, 0xaa, 
  0xe6, 0x7a, 0x19, 0xf8, 0xe1, 0x78, 0x1e, 0xe5, 0xcc, 0x66, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1c, 0xeb, 0x3f, 0x24, 0x20, 0xed, 0xf0, 0x20, 0x1c, 0xeb, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xcc, 0x66, 0x00, 0x05, 0xe1, 0x78, 0x1e, 0xe5, 0xe6, 0x7a, 0x19, 0xf8, 
  0xe6, 0x79, 0x19, 0x70, 0xe6, 0x7a, 0x19, 0xf8, 0xe6, 0x7a, 0x19, 0xcf, 0xe6, 0x79, 0x19, 0x70, 0xd1, 0x6e, 0x2e, 0x43, 0xd1, 0x6e, 0x2e, 0x43, 0xd1, 0x6e, 0x2e, 0x43, 0xe6, 0x79, 0x19, 0x70, 0xe6, 0x7a, 0x19, 0xcf, 0xe6, 0x7a, 0x19, 0xf8, 0xe6, 0x79, 0x19, 0x70, 
  0x00, 0x00, 0x00, 0x00, 0xe6, 0x79, 0x13, 0x28, 0xe6, 0x79, 0x19, 0x8d, 0xe6, 0x7a, 0x19, 0xcf, 0xe6, 0x7a, 0x19, 0xf8, 0xe6, 0x7a, 0x19, 0xf8, 0xe6, 0x7a, 0x19, 0xf8, 0xe6, 0x7a, 0x19, 0xcf, 0xe6, 0x79, 0x19, 0x8d, 0xe6, 0x79, 0x13, 0x28, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t img_icon_location_11p = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 11,
  .header.h = 11,
  .data_size = 121 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = img_icon_location_11p_map,
};
