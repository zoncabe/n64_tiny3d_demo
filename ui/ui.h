#ifndef UI_H
#define UI_H

#define DROID_SANS 1


typedef struct {

    rdpq_font_t *font;
    int box_width;
    int box_height;

} UI;



void ui_init(UI* ui)
{
    ui->font = rdpq_font_load("rom:/DroidSans.font64");
    rdpq_text_register_font(DROID_SANS, ui->font);
}

void ui_printActorState(UI* ui, Actor* actor)
{
    switch(actor->state) {
        
        case STAND_IDLE: {
           rdpq_text_printf(NULL, DROID_SANS, 10, 20, "state: idle");
            break;
        }
        case WALKING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 20, "state: walking");
            break;
        }
        case RUNNING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 20, "state: running");
            break;
        }
        case SPRINTING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 20, "state: sprinting");
            break;
        }
        case ROLLING: {
            break;
        }
        case JUMPING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 20, "state: jumping");
            break;
        }
        case FALLING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 20, "state: falling");
            break;
        }   
    }
}

void ui_printActorAnimation(UI* ui, Actor* actor)
{
    switch(actor->animation.current) {
        
        case STAND_IDLE: {
           rdpq_text_printf(NULL, DROID_SANS, 10, 30, "animation: idle");
            break;
        }
        case WALKING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 30, "animation: walking");
            break;
        }
        case RUNNING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 30, "animation: running");
            break;
        }
        case SPRINTING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 30, "animation: sprinting");
            break;
        }
        case ROLLING: {
            break;
        }
        case JUMPING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 30, "animation: jumping");
            break;
        }
        case FALLING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 30, "animation: falling");
            break;
        }   
    }
}

void ui_printActorPreviousAnimation(UI* ui, Actor* actor)
{
    switch(actor->animation.previous) {
        
        case STAND_IDLE: {
           rdpq_text_printf(NULL, DROID_SANS, 10, 40, "previous: idle");
            break;
        }
        case WALKING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 40, "previous: walking");
            break;
        }
        case RUNNING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 40, "previous: running");
            break;
        }
        case SPRINTING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 40, "previous: sprinting");
            break;
        }
        case ROLLING: {
            break;
        }
        case JUMPING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 40, "previous: jumping");
            break;
        }
        case FALLING: {
            rdpq_text_printf(NULL, DROID_SANS, 10, 40, "previous: falling");
            break;
        }   
    }
}

void ui_printDebugData(UI* ui, Actor* actor, TimeData time)
{
    //ui_printActorState(ui, actor);
    //ui_printActorAnimation(ui, actor);
    //ui_printActorPreviousAnimation(ui, actor);

	//rdpq_text_printf(NULL, DROID_SANS, 10, 15, "action blending ratio %f", actor->animation.action_blending_ratio);
	//rdpq_text_printf(NULL, DROID_SANS, 10, 25, "rolling timer %f", actor->input.roll_timer);

	rdpq_text_printf(NULL, DROID_SANS, 250, 15, "FPS %f", time.frame_rate);
	rdpq_text_printf(NULL, DROID_SANS, 224, 25, "frame time %f", time.frame_time);  
}

#endif 