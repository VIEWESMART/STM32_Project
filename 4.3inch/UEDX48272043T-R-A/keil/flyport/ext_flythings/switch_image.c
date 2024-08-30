#include "ext_flythings/switch_image.h"


//ÇĞ»»Í¼Æ¬¿Ø¼şµÄÍ¼Æ¬
void image_set_img(image_t *img, const uint16_t imgid) {
	img->bg.imgid = imgid;
	widget_invalidate((widget_t *) img, NULL);
}
