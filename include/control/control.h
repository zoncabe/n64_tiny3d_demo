#ifndef CONTROLS_H
#define CONTROLS_H



typedef struct {

    joypad_buttons_t pressed;
    joypad_buttons_t held;
    joypad_inputs_t input;

} ControllerData;


void controllerData_getInputs(ControllerData*data, uint8_t port);

void controllerData_getInputs(ControllerData* data, uint8_t port)
{    
    data->pressed = joypad_get_buttons_pressed(port);
    data->held = joypad_get_buttons_held(port);
    data->input = joypad_get_inputs(port); 
}

#endif