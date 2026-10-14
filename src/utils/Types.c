#include "Types.h"
#include "math.h"

// Vector3D
Vector3D VectorAdd(Vector3D v1, Vector3D v2){
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}
Vector3D VectorSub(Vector3D v1, Vector3D v2){
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}
Vector3D VectorMul(Vector3D v, float value){
    v.x *= value;
    v.y *= value;
    v.z *= value;
    return v;
}
Vector3D VectorDiv(Vector3D v, float value){
    v.x /= value;
    v.y /= value;
    v.z /= value;
    return v;
}
float VectorMagnitude(Vector3D v){
    return sqrt(pow(v.x,2)+ pow(v.y,2) + pow(v.z,2));
}
Vector3D VectorNormalize(Vector3D v){
    return VectorDiv(v, VectorMagnitude(v));   
}
float VectorDot(Vector3D v1, Vector3D v2){
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
Vector3D VectorCross(Vector3D v1, Vector3D v2){
    Vector3D ret ={
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
        };
    return ret;
}


