#pragma once
#include "DxLib.h"

class MyImage {
public:

    /// <summary>
    /// 画像を座標の中心に描画するための計算
    /// </summary>
    /// <param name="gHandle"></param>
    /// <param name="pos"></param>
    /// <param name="exRateX"></param>
    /// <param name="exRateY"></param>
    /// <returns></returns>
    static VECTOR ImageCenterPos(int gHandle, VECTOR pos, float exRateX = 1, float exRateY = 1);

    /// <summary>
    /// 画像を座標の中心に描画するための計算
    /// </summary>
    /// <param name="gHandle"></param>
    /// <param name="pos"></param>
    /// <param name="exRateX"></param>
    /// <param name="exRateY"></param>
    /// <returns></returns>
    static VECTOR ExpendImageCenterPos(VECTOR pos, int exRateX, int exRateY);


    /// <summary>
    /// 画像の頂点の座標を取得
    /// </summary>
    static VECTOR ImageTopPos(int gHandle, int exRateX = 1, int exRateY = 1);

    static VECTOR BoxCenterPos(float _x, float _y, float _w, float _h);
};

