#include "MyImage.h"

VECTOR MyImage::ImageCenterPos(int gHandle, VECTOR pos, float exRateX, float exRateY) {
    int x, y;
    GetGraphSize(gHandle, &x, &y);

    pos.x -= (int)(x * exRateX) / 2;
    pos.y -= (int)(y * exRateY) / 2;

    return pos;
}

VECTOR MyImage::ExpendImageCenterPos(VECTOR pos, int exRateX, int exRateY) {

    pos.x -= (int)(exRateX) / 2;
    pos.y -= (int)(exRateY) / 2;

    return pos;
}

VECTOR MyImage::ImageTopPos(int gHandle, int exRateX, int exRateY) {
    int x, y;
    GetGraphSize(gHandle, &x, &y);

    x = (int)(x * exRateX);
    y = (int)(y * exRateY);

    return VGet(x, y, 0);
}

VECTOR MyImage::BoxCenterPos(float _x, float _y, float _w, float _h) {
    float x, y;

    x = (_w / 2) + _x;
    y = (_h / 2) + _y;

    return VGet(x,y,0);
}
