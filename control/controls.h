#ifndef CONTROLS_H
#define CONTROLS_H



typedef struct {

    joypad_buttons_t pressed;
    joypad_buttons_t held;
    joypad_inputs_t input;

} ControllerData;


void controllerData_getInputs(ControllerData* data);


void controllerData_getInputs(ControllerData* data)
{
    joypad_poll();
    data->pressed = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    data->held = joypad_get_buttons_held(JOYPAD_PORT_1);
    data->input = joypad_get_inputs(JOYPAD_PORT_1); 
}

#endif