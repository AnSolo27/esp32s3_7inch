#include "images.h"

const ext_img_desc_t images[6] = {
    { "pressure", &img_pressure },
    { "plus", &img_plus },
    { "minus", &img_minus },
    { "minus_pressed", &img_minus_pressed },
    { "plus_pressed", &img_plus_pressed },
    { "temp", &img_temp },
};
