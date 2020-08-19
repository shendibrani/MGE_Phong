#include "Input.hpp"

float Input::_mouseWheelDelta = 0;

void Input::SetMouseWheelDelta(float delta)
{
    _mouseWheelDelta = delta;
}

float Input::GetMouseWheelDelta()
{
    float temp = _mouseWheelDelta;
    _mouseWheelDelta = 0;
    return temp;
}
