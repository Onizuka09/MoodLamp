#include <lvgl.h>
#include <TFT_eSPI.h>
#include "ui/ui.h"


#define LVGL_TICK_PERIOD 20



// Set the screen resolution
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10]; 

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

//declare the function to create a group and input device for the rotary encoder
lv_group_t *group1 = NULL;
lv_indev_t *encoder_indev = NULL;

//configure the resolution
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void DHTtimer(lv_timer_t * timer) { //Create timer for sensor

 
   
}

void setup() {
    Serial.begin(115200);

    lv_init();
    
    tft.begin();
    tft.setRotation(1);

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

    //Initialize the display.
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_init();

    lv_timer_t* timer = lv_timer_create(DHTtimer,2000,NULL); //Update sensor value after 2 second

    Serial.println("Setup done");
}

void loop() {
    lv_timer_handler();
    delay(5);
    
}


