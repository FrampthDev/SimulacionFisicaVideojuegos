//TODO: Poner la licencia y demas

#ifndef RENDER_API_H
#define RENDER_API_H

#include "../../utils/Types.h"

#define ID long unsigned int

typedef struct RenderError{
    char* error;
} RenderError;

typedef ID SceneAPI;
typedef ID ModelAPI;
typedef ID Camera3DAPI;


// NOTE: should we have multiple windows??
void StartWindow(int width, int height, const char* name);
void StopWindow(void);
bool WindowClosed();

void StartRendering(void);
void StopRendering(void);
void ClearRenderingBackground(ColorRGBA color);

void StartMode3D(Camera3DAPI camera);
void StopMode3D(void);

ModelAPI CreateSphereModel(float radius, int slices, int rings, Transform3D transform, ColorRGBA tint);
ModelAPI CreatePlaneModel(float length, Transform3D transform, ColorRGBA tint);
ModelAPI CreateModel(); //TODO

bool UpdateID(Transform3D transform, ColorRGBA tint);

SceneAPI CreateScene(void);
void SelectScene(SceneAPI);

// Change fov too
Camera3DAPI CreateCamera3D(Vector3D position, Vector3D look, Vector3D up, float fov, int projection);
bool UpdateCamera3D(Vector3D position, Vector3D look, Vector3D up);
void UpdateCameraRAYLIB();

void RenderScene();

void DestroyID(ModelAPI id);

RenderError GetRenderError();

#endif //RENDER_API_H
