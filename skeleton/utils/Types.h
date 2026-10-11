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

typedef Vector4D Quaternion;

typedef struct Transform {
	Quaternion q;
	Vector3D p;
}Transform;

typedef struct Matrix {
	float m0, m4, m8, m12;
	float m1, m5, m9, m13;
	float m2, m6, m10, m14;
	float m3, m7, m11, m15;
}Matrix;

typedef struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}Color;

#endif //TYPES_H