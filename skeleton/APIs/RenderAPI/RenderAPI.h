//TODO: Poner la licencia y demas

#ifndef RENDER_API_H
#define RENDER_API_H

#include "../../utils/Types.h"

#define IDX size_t

enum Projection {
	PERSPECTIVE,
	ORTOGONAL,
};

enum Shape {
	SPHERE,
	PLANE,
};

typedef struct Shape3D{
	Shape shape;
	union{
		struct{
			float radius;
		}sphere;
		struct {
			Vector3D p1;
			Vector3D p2;
		}Plane;
	}ShapeData;
}Shape3D;

typedef struct Shape3DIDX{
	IDX id;
}Shape3DIDX;

typedef struct RenderCamera{
	Vector3D position;
	Vector3D look;
	Vector3D up;
	float fov;
	Projection projection;
}RenderCamera;

typedef struct RenderCameraIDX {
	IDX id;
}RenderCameraIDX;

typedef struct Mesh{
	//TODO: This should be something abstract, like the path to the model
}Mesh;

typedef struct MeshIDX {
	IDX id;
}MeshIDX;

typedef struct Shader {
	char* vertex_shaer_path;
	char* fragment_shader_path;
}Shader;

typedef struct ShaderIDX{
	IDX id;
}ShaderIDX;

typedef struct Material {
	ShaderIDX shader;
	//TODO:What else does this need?
}Material;

typedef struct MaterialIDX {
	IDX id;
}MaterialIDX;

void StartRendering(void);
void StopRendering(void);

void StartMode3D(RenderCameraIDX camera);
void StopMode3D(void);

Shape3DIDX CreateSphereShape(float radius);
Shape3DIDX CreatePlaneShape(Vector3D position1, Vector3D position2);

void RenderShape(Shape3DIDX shape, Transform transform, float scale);
void RenderShape(Shape3DIDX shape, Transform transform, float scale, MaterialIDX material);


#endif //RENDER_API_H
