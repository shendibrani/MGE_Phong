#ifndef INPUT_H
#define INPUT_H

class Input
{
    public:
        static void SetMouseWheelDelta(float delta);
        static float GetMouseWheelDelta();
    private:
        static float _mouseWheelDelta;
};

#endif // INPUT_H
