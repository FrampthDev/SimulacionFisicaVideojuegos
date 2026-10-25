#ifndef TYPES_H
#define TYPES_H

typedef struct Vector2D {
	float x;
	float y;
}Vector2D;

typedef struct Vector3D {
	float x;
	float y;
	float z;
}Vector3D;

typedef struct Vector4D {
	float x;
	float y;
	float z;
	float w;
}Vector4D;

typedef Vector4D Quaternion3D;

typedef struct Transform3D {
	Quaternion3D q;
	Vector3D p;
        Vector3D scale;
}Transform3D; //TODO: Quitar este transform

typedef struct Matrix4 {
	float m0, m4, m8, m12;
	float m1, m5, m9, m13;
	float m2, m6, m10, m14;
	float m3, m7, m11, m15;
}Matrix4;

typedef struct ColorRGBA {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}ColorRGBA;

// Vector operations
Vector3D VectorAdd(Vector3D v1, Vector3D v2);
Vector3D VectorSub(Vector3D v1, Vector3D v2);
Vector3D VectorMul(Vector3D v, float value);
Vector3D VectorDiv(Vector3D v, float value);
float VectorMagnitude(Vector3D v);
Vector3D VectorNormalize(Vector3D v);
float VectorDot(Vector3D v1, Vector3D v2);
Vector3D VectorCross(Vector3D v1, Vector3D v2);


#endif //TYPES_H
