#include "ext_flythings/switch_image.h"


//�л�ͼƬ�ؼ���ͼƬ
void image_set_img(image_t *img, const uint16_t imgid) {
	img->bg.imgid = imgid;
	widget_invalidate((widget_t *) img, NULL);
}
