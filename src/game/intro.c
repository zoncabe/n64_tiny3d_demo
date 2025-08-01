#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>

#define SPINSPEED 0.9f


// Easing function for quadratic ease-out
//  t = current time
//  b = start value
//  c = change in value
//  d = duration
static float ease_out_quad(float t, float b, float c, float d)
{
    t /= d;
    if (t>1) t = 1;
    return -c * t*(t-2) + b;
}

void n64brew_logo(void)
{
    const color_t BACKGROUND_COLOR = RGBA32(0, 0, 0, 1);

    T3DModel *brew = t3d_model_load("rom:/brew_logo.t3dm");
    sprite_t *logo = sprite_load("rom:/brew_logo.sprite");

    T3DViewport viewport = t3d_viewport_create();
    T3DVec3 camPos = {{0, 0.0f, 50.0f}};
    T3DVec3 camTarget = {{0, 0.0f, 0}};
    uint8_t colorAmbient[4] = {0xff, 0xff, 0xff, 0xFF};
    float scale = 0.08f;

    T3DMat4FP *mtx = malloc_uncached(sizeof(T3DMat4FP));
    rspq_syncpoint_t sync = 0;

    float mt0 = get_ticks_ms();
    float angle = T3D_DEG_TO_RAD(-90.0f);
    float fade_white = 1.0f;
    int anim_part = 0;

    
    while (1)
    {
        float tt = get_ticks_ms() - mt0;
        if (tt < 1500) {
            anim_part = 0;
            angle += SPINSPEED*display_get_delta_time();
        } else if (tt < 3500) {
            anim_part = 1;
            tt -= 1500;
            camTarget.v[0] = ease_out_quad(tt, 0.0f, -125.0f, 2000.0f);
            camTarget.v[1] = ease_out_quad(tt, 0.0f, -5.0f, 2000.0f);
            camPos.v[1] = ease_out_quad(tt, 0.0f, -5.0f, 2000.0f);
            camPos.v[2] = ease_out_quad(tt, 50.0f, 110.0f, 2000.0f);
            angle += SPINSPEED*display_get_delta_time();
        } else if (tt < 3800) {
            anim_part = 2;
            fade_white = (tt-3500) / 300.0f;
            if (fade_white > 1.0f) fade_white = 1.0f;
            angle += SPINSPEED*display_get_delta_time();
        } else if (tt < 6500) {
            anim_part = 3;
            fade_white = 1.0f - (tt-3800) / 300.0f;
            if (fade_white < 0.0f) fade_white = 0.0f;
        } else if (tt < 7500) {
            anim_part = 4;
            fade_white = (tt-6500) / 1000.0f;
        } else {
            break;
        }
        
        rdpq_attach(display_get(), display_get_zbuf());
        rdpq_clear(BACKGROUND_COLOR);
        rdpq_clear_z(ZBUF_MAX);

        if (anim_part >= 3) {
            rdpq_set_mode_copy(true);
            rdpq_sprite_blit(logo, 28, 78, NULL);
        }

        if (anim_part < 3) {
            t3d_frame_start();
            t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(85.0f), 20.0f, 160.0f);
            t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,1,0}});
            t3d_viewport_attach(&viewport);
            t3d_light_set_ambient(colorAmbient);
            t3d_light_set_count(0);
            
            if (sync) rspq_syncpoint_wait(sync);
            t3d_mat4fp_from_srt_euler(mtx,
                (float[3]){scale, scale, scale},
                (float[3]){0.0f, angle*0.8f, 0},
                (float[3]){0, 0, 0}
            );
            t3d_matrix_push(mtx);
            t3d_model_draw(brew);
            t3d_matrix_pop(1);
            sync = rspq_syncpoint_new();
            rdpq_sync_pipe();
        }
        
        if (anim_part >= 2 && fade_white > 0.0f) {
            rdpq_set_mode_standard();
            if (anim_part == 4)
                rdpq_set_prim_color(RGBA32(0,0,0,255*fade_white));
            else
                rdpq_set_prim_color(RGBA32(255,255,255,255*fade_white));
            rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
            rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
            rdpq_fill_rectangle(0, 0, 320, 240);
        }
        
        /*
        */
        if (anim_part < 2 && fade_white > 0.0f) {

            fade_white = 1.0f - (tt / 300.0f);
            if (fade_white < 0.0f) fade_white = 0.0f;  
            
            rdpq_set_prim_color(RGBA32(0,0,0,255*fade_white));
            rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
            rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
            rdpq_fill_rectangle(0, 0, 320, 240);

        }

        rdpq_detach_show();
    }

    wait_ms(1000);
    rspq_wait();
    sprite_free(logo);
    t3d_model_free(brew);
}

void libdragon_logo(void)
{
    const color_t RED = RGBA32(221, 46, 26, 255);
    const color_t WHITE = RGBA32(255, 255, 255, 255);

    sprite_t *d1 = sprite_load("rom:/dragon1.sprite");
    sprite_t *d2 = sprite_load("rom:/dragon2.sprite");
    sprite_t *d3 = sprite_load("rom:/dragon3.sprite");
    sprite_t *d4 = sprite_load("rom:/dragon4.sprite");
    //wav64_t music;
    //wav64_open(&music, "rom:/dragon.wav64");
    //mixer_ch_set_limits(0, 0, 48000, 0);

    float angle1=0, angle2=0, angle3=0;
    float scale1=0, scale2=0, scale3=0, scroll4=0;
    uint32_t ms0=0;
    int anim_part=0;
    const int X0 = 5, Y0 = 15; // translation offset of the animation (simplify centering)

    void reset() {
        ms0 = get_ticks_ms();
        anim_part = 0;

        angle1 = 3.2f;
        angle2 = 1.9f;
        angle3 = 0.9f;
        scale1 = 0.0f;
        scale2 = 0.4f;
        scale3 = 0.8f;
        scroll4 = 200;
        //wav64_play(&music, 0);
    }

    reset();
    
    while (1) {
        //mixer_try_play();
        
        // Calculate animation part:
        // 0: rotate dragon head
        // 1: rotate dragon body and tail, scale up
        // 2: scroll dragon logo
        // 3: fade out 
        uint32_t tt = get_ticks_ms() - ms0;
        if (tt < 1000) anim_part = 0;
        else if (tt < 1500) anim_part = 1;
        else if (tt < 4000) anim_part = 2;
        else if (tt < 5000) anim_part = 3;
        else break;

        // Update animation parameters using quadratic ease-out
        angle1 -= angle1 * 0.04f; if (angle1 < 0.010f) angle1 = 0;
        if (anim_part >= 1) {
            angle2 -= angle2 * 0.06f; if (angle2 < 0.01f) angle2 = 0;
            angle3 -= angle3 * 0.06f; if (angle3 < 0.01f) angle3 = 0;
            scale2 -= scale2 * 0.06f; if (scale2 < 0.01f) scale2 = 0;
            scale3 -= scale3 * 0.06f; if (scale3 < 0.01f) scale3 = 0;
        }
        if (anim_part >= 2) {
            scroll4 -= scroll4 * 0.08f;
        }

        // Update colors for fade out effect
        color_t red = RED;
        color_t white = WHITE;
        if (anim_part >= 3) {
            red.a = 255 - (tt-4000) * 255 / 1000;
            white.a = 255 - (tt-4000) * 255 / 1000;
        }

        #if 0
        #endif
        // Debug: re-run logo animation on button press
        joypad_poll();
        joypad_buttons_t btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);
        if (btn.a) reset();

        surface_t *fb = display_get();
        rdpq_attach_clear(fb, NULL);

        // To simulate the dragon jumping out, we scissor the head so that
        // it appears as it moves.
        if (angle1 > 1.0f) {
            // Initially, also scissor horizontally, 
            // so that the head tail is not visible on the right.
            rdpq_set_scissor(0, 0, X0+150, Y0+120);    
        } else {
            rdpq_set_scissor(0, 0, 320, Y0+120);
        }

        // Draw dragon head
        rdpq_set_mode_standard();
        rdpq_mode_alphacompare(1);
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
        rdpq_mode_combiner(RDPQ_COMBINER1((0,0,0,PRIM),(TEX0,0,PRIM,0)));
        rdpq_set_prim_color(red);
        rdpq_sprite_blit(d1, X0+108, Y0+102, &(rdpq_blitparms_t){ 
            .theta = angle1, .scale_x = scale1+1, .scale_y = scale1+1,
            .cx = 88, .cy = 85,
        });

        // Restore scissor to standard
        rdpq_set_scissor(0, 0, 320, 240);

        // Draw a black rectangle with alpha gradient, to cover the head tail
        rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
        rdpq_mode_dithering(DITHER_NOISE_NOISE);
        float vtx[4][6] = {
            //  x,      y,    r,g,b,a
            { X0+0,   Y0+90, 0,0,0,0 },
            { X0+100, Y0+90, 0,0,0,0 },
            { X0+100, Y0+120, 0,0,0,1 },
            { X0+0,   Y0+120, 0,0,0,1 },
        };
        rdpq_triangle(&TRIFMT_SHADE, vtx[0], vtx[1], vtx[2]);
        rdpq_triangle(&TRIFMT_SHADE, vtx[0], vtx[2], vtx[3]);

        if (anim_part >= 1) {
            // Draw dragon body and tail
            rdpq_set_mode_standard();
            rdpq_mode_alphacompare(1);
            rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
            rdpq_mode_combiner(RDPQ_COMBINER1((0,0,0,PRIM),(TEX0,0,PRIM,0)));

            // Fade them in
            color_t color = red;
            color.r *= 1-scale3; color.g *= 1-scale3; color.b *= 1-scale3;
            rdpq_set_prim_color(color);

            rdpq_sprite_blit(d2, X0+123, Y0+115, &(rdpq_blitparms_t){ 
                .theta = angle2, .scale_x = 1-scale2, .scale_y = 1-scale2,
                .cx = 72, .cy = 56,
            });

            rdpq_sprite_blit(d3, X0+133, Y0+128, &(rdpq_blitparms_t){ 
                .theta = -angle3, .scale_x = 1-scale3, .scale_y = 1-scale3,
                .cx = 45, .cy = 12,
            });
        }

        // Draw scrolling logo
        if (anim_part >= 2) {
            rdpq_set_prim_color(white);
            rdpq_sprite_blit(d4, X0 + 80 + (int)scroll4, Y0 + 91, NULL);
        }

        rdpq_detach_show();
    }

    wait_ms(500); // avoid immediate switch to next screen
    rspq_wait();
    sprite_free(d1);
    sprite_free(d2);
    sprite_free(d3);
    sprite_free(d4);
    //wav64_close(&music);
    return;
}
