#ifndef SPRITES_H
#define SPRITES_H

typedef struct {
    sprite_t*   image;
    const char* path;
    Vector2     position;
    float       rotation;
    Vector2     scale;
} Sprite;

void sprite_setMode();
void sprite_init(Sprite *sprites, int count);
void sprite_draw(Sprite *sprites, int count);

#endif