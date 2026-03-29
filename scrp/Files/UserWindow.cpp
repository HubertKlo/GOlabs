    #include "UserWindow.h"
    double UserWindow::WindowPlacementY(double y)
    {
        return (y - camY) * zoom + cy;
    }
    double UserWindow::WindowPlacementX(double x)
    {
        return (x - camX) * zoom + cx;
    }
    void UserWindow::CamxSetter(double x)
    {
        camX += x / zoom;
    }
    void UserWindow::CamySetter(double x)
    {
        camY += x / zoom;
    }
    void UserWindow::ZoomSetter(double x)
    {
        zoom *= x;
    }