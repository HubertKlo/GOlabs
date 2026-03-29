#ifndef USERWIND_H
#define USERWIND_H

class UserWindow
{
private:
    float zoom = 30.0f;
    float camX = 0;
    float camY = 0;
    float cx = 320;
    float cy = 240;

public:
    double WindowPlacementY(double y);
    double WindowPlacementX(double x);
    void CamxSetter(double x);
    void CamySetter(double x);
    void ZoomSetter(double x);
};
#endif