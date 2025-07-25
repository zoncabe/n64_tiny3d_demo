#ifndef CONTROLS_H
#define CONTROLS_H


typedef struct {

    joypad_buttons_t pressed;
    joypad_buttons_t held;
    joypad_inputs_t input;

} ControllerData;


void controllerData_getInputs(ControllerData*data, uint8_t port);


#endif