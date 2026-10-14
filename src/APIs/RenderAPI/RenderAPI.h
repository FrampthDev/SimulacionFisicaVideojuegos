//TODO: Poner la licencia y demas

#ifndef RENDER_API_H
#define RENDER_API_H

#include "../../utils/Types.h"

#define ID long unsigned int

typedef struct IDX{
    const ID id;   
    const bool nil;
} IDX;

typedef struct RenderError{
    char* error;
} RenderError;

typedef IDX ShapeAPI;
typedef IDX Camera3DAPI;
typedef IDX ShaderAPI;
typedef IDX MaterialAPI;

// NOTE: should we have multiple windows??
void StartWindow(int width, int height, const char* name);
void StopWindow(void);
bool WindowClosed();

void StartRendering(void);
void StopRendering(void);
void ClearRenderingBackground(ColorRGBA color);

void StartMode3D(Camera3DAPI camera);
void StopMode3D(void);

ShapeAPI CreateSphereShape(float radius);
ShapeAPI CreatePlaneShape(Vector2D lenght);
ShapeAPI CreateMeshShape(); //TODO
// Change fov too
Camera3DAPI CreateCamera3D(Vector3D position, Vector3D look, Vector3D up, float fov, int projection);
Camera3DAPI UpdateCamera3D(Vector3D position, Vector3D look, Vector3D up);

//TODO: funciones de destrucción
void DestroyShape(ShapeAPI);

MaterialAPI CreateMaterial(); //TODO

void RenderShape(ShapeAPI shape, Transform3D transform, float scale);
void RenderMaterialShape(ShapeAPI shape, Transform3D transform, float scale, MaterialAPI material);

RenderError GetRenderError();

#endif //RENDER_API_H
