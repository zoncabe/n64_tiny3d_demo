
#include "../../include/control/control.h"



void controllerData_getInputs(ControllerData* data, uint8_t port)
{    
    data->pressed = joypad_get_buttons_pressed(port);
    data->held = joypad_get_buttons_held(port);
    data->input = joypad_get_inputs(port); 
}
