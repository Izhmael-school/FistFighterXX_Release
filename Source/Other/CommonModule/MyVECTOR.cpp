#include "MyVECTOR.h"
#include "../../Definition.h"

bool MyVECTOR::CompareVECTORToSize(VECTOR v1, VECTOR v2) {

    if (v1.x > v2.x) return false;
    if (v1.y > v2.y) return false;
    if (v1.z > v2.z) return false;

    return true;
}

bool MyVECTOR::CompareVECTORToEqual(VECTOR _vec1, VECTOR _vec2) {
    if (_vec1.x != _vec2.x) return false;
    if (_vec1.y != _vec2.y) return false;
    if (_vec1.z != _vec2.z) return false;
    return true;
}

VECTOR MyVECTOR::ChangeElementXY(VECTOR& v) {
    float box = v.y;
    v.y = v.x;
    v.x = box;
    return v;
}

VECTOR MyVECTOR::ChangeElementYZ(VECTOR& v) {
    float box = v.y;
    v.y = v.z;
    v.z = box;
    return v;
}

VECTOR MyVECTOR::ChangeElementXZ(VECTOR& v) {
    float box = v.x;
    v.x = v.z;
    v.z = box;
    return v;
}

VECTOR MyVECTOR::VAddFloat(VECTOR v, float f) {
    v.x = v.x + f;
    v.y = v.y + f;
    v.z = v.z + f;
    return v;
}

VECTOR MyVECTOR::VSubFloat(VECTOR v, float f) {
    v.x = v.x - f;
    v.y = v.y - f;
    v.z = v.z - f;
    return v;
}

VECTOR MyVECTOR::VDiv(VECTOR _v1, VECTOR _v2) {
    float f1[VMax] = { _v1.x,_v1.y ,_v1.z };
    float f2[VMax] = { _v2.x,_v2.y ,_v2.z };
    float r[VMax] = { 0,0,0 };
    for (int i = 0; i < VMax; i++) {
        if (f2[i] == 0) {
            r[i] = 0;
            continue;
        }

        r[i] = f1[i] / f2[i];
    }

    return VGet(r[X], r[Y], r[Z]);
}
