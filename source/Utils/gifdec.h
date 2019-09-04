#ifndef GIFDEC_H
#define GIFDEC_H

#include <stdint.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>

#include <Utils/StandardSDL2.h>

#include <Engine/IResources.h>
#include <Engine/IStreamer.h>

struct gd_Palette {
	int size;
	uint8_t colors[0x100 * 3];
};

typedef struct gd_GCE {
	uint16_t delay;
	uint8_t tindex;
	uint8_t disposal;
	int input;
	int transparency;
} gd_GCE;

typedef struct gd_GIF {
	IResource* fd;
	off_t anim_start;
	uint16_t width, height;
	uint16_t depth;
	uint16_t loop_count;
	gd_GCE gce;
	gd_Palette *palette;
	gd_Palette lct, gct;
	void(*plain_text)(
	struct gd_GIF *gif, uint16_t tx, uint16_t ty,
		uint16_t tw, uint16_t th, uint8_t cw, uint8_t ch,
		uint8_t fg, uint8_t bg
		);
	void(*comment)(struct gd_GIF *gif);
	void(*application)(struct gd_GIF *gif, char id[8], char auth[3]);
	uint16_t fx, fy, fw, fh;
	uint8_t bgindex;
	uint8_t *canvas, *frame;
} gd_GIF;

gd_GIF *gd_open_gif(IResource* fd);//const char *fname);
gd_GIF *gd_copy_gif(gd_GIF *other);
int gd_get_frame(gd_GIF *gif);
void gd_render_frame(gd_GIF *gif, uint8_t *buffer);
void gd_rewind(gd_GIF *gif);
void gd_close_gif(gd_GIF *gif);

#endif /* GIFDEC_H */
