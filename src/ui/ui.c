#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/ui/ui.h"
#include "../../include/ui/menu.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"
#include "../../include/graphics/lighting.h"
#include "../../include/viewport/camera.h"
#include "../../include/viewport/viewport.h"
#include "../../include/scene/scenery.h"
#include "../../include/game/game.h"
#include "../../include/player/player.h"

UI ui;

void ui_init()
{
    ui.font = rdpq_font_load("rom:/fonts/DroidSans.font64");
    rdpq_text_register_font(DROID_SANS, ui.font);
}

void ui_printDebugData()
{
    //rdpq_text_printf(NULL, DROID_SANS, 10, 15, "menu index %f", player[0]->armature.animation.footing_blending_ratio);
    //rdpq_text_printf(NULL, DROID_SANS, 10, 15, "menu index %f", player[0]->armature.animation.settings.action_idle_max_blending_ratio);
}
