#include <raylib.h>
#include <stdio.h>

#include "../RenderAPI.h"

// Data structure's Provisional implementations
// TODO: hacer una pool
Camera cameras_array[5];
ID last_camera = 1;

enum ShapeType{
    SPHERE,
    PLANE,
};
typedef struct Shape{
    enum ShapeType type;
    union{
        struct {
            float radius;
        }sphere;
        struct{
            Vector2 lenght;
        }plane;
    };
}Shape;

Shape shapes_array[100];
ID last_shape = 1;

bool drawing = false;
bool mode3D = false;

// Conversions
static Vector3 vector3D_to_vector3(Vector3D v){
    Vector3 ret = {v.x, v.y, v.z};
    return ret;
}
static Vector3D vector3_to_vector3D(Vector3 v){
    Vector3D ret = {v.x, v.y, v.z};
    return ret;
}
static Vector2D vector2_to_vector2D(Vector2 v){
    Vector2D ret = {v.x, v.y};
    return ret;
}
static Vector2 vector2D_to_vector2(Vector2D v){
    Vector2 ret = {v.x, v.y};
    return ret;
}
static Color ColorRGBA_to_Color(ColorRGBA color){
    Color ret = {color.r, color.g, color.b, color.a};
    return ret;
}
static ColorRGBA Color_to_ColorRGBA(Color color){
    ColorRGBA ret = {color.r, color.g, color.b, color.a};
    return ret;
}
static Camera3D Camera3DAPI_to_Camera3D(Camera3DAPI camera){
    Camera3D ret = cameras_array[camera.id];
    return ret;
}
static Quaternion Quaternion3D_to_Quaternion(Quaternion3D quaternion){
    Quaternion ret ={quaternion.x, quaternion.y, quaternion.z};
    return ret;
}
static Quaternion3D Quaternion_to_Quaternion3D(Quaternion quaternion){
    Quaternion3D ret = {quaternion.x, quaternion.y, quaternion.z};
    return ret;
}
static Transform Transform3D_to_Transform(Transform3D transform){
    Transform ret = {
        vector3D_to_vector3(transform.p),
        Quaternion3D_to_Quaternion(transform.q),
        vector3D_to_vector3(transform.scale),
    };
    return ret;
}
static Transform3D Transform_to_Transform3D(Transform transform){
    Transform3D ret = {
        Quaternion_to_Quaternion3D(transform.rotation),
        vector3_to_vector3D(transform.translation),
        vector3_to_vector3D(transform.scale),
    };
    return ret;
}

// Error handling
RenderError last_error;
static void SetError(char* error){
    last_error.error = error;
}
RenderError GetRenderError(){
    return last_error;
}

// Functions implementations
void StartRendering(void){
    BeginDrawing();  
    drawing = true;
}
void StopRendering(void){
    EndDrawing();
    drawing = false;
}
void ClearRenderingBackground(ColorRGBA color){
    ClearBackground(ColorRGBA_to_Color(color));
}
void StartMode3D(Camera3DAPI camera){
    mode3D = true;
    BeginMode3D(cameras_array[camera.id]);
}
void StopMode3D(void){
    mode3D = false;
    EndMode3D();
}
Camera3DAPI CreateCamera3D(Vector3D position, Vector3D look, Vector3D up, float fov, int projection){ //FIXME: este projection es peligroso
    Camera c = {
        vector3D_to_vector3(position), 
        vector3D_to_vector3(look), 
        vector3D_to_vector3(up), 
        fov, 
        projection};
    cameras_array[last_camera] = c;
    Camera3DAPI ret = {last_camera, false};
    last_camera++;
    return ret;
}
Camera3DAPI UpdateCamera3D(Vector3D position, Vector3D look, Vector3D up){

}


ShapeAPI CreateSphereShape(float radius){
    if (radius <= 0){
        ShapeAPI ret = {0, true};
        return ret;
    }
    Shape shape;
    shape.type = SPHERE;
    shape.sphere.radius = radius;
    shapes_array[last_shape] = shape;
    ShapeAPI ret = {last_shape, false};
    last_shape++;
    return ret;
}
ShapeAPI CreatePlaneShape(Vector2D lenght){
    Shape shape;
    shape.type = PLANE;
    shape.plane.lenght = vector2D_to_vector2(lenght);
    ShapeAPI ret = {last_shape, false};
    shapes_array[last_shape] = shape;
    last_shape++;
    return ret;
}
void RenderShape(ShapeAPI shape, Transform3D transform, float scale){
    if (!drawing){
        SetError("Trying to render a shape without enable rendering first");
        return;
    }
    if (!mode3D){
        SetError("Trying to render a shape without enable mode3D");
        return;
    }

    Shape s = shapes_array[shape.id];
    Color default_color = {0xFF,0xFF,0xFF,0xFF};
    switch (s.type) {
        case PLANE:{
            DrawPlane(vector3D_to_vector3(transform.p), s.plane.lenght, default_color);
        }
        case SPHERE:{
            DrawSphere(vector3D_to_vector3(transform.p),s.sphere.radius, default_color);
        }
    }
}
void RenderMaterialShape(ShapeAPI shape, Transform3D transform, float scale, MaterialAPI material){
    //TODO
}
void StartWindow(int width, int height, const char* name){
    InitWindow(width, height, name);
    if (!IsWindowReady()){
        SetError("Error initializing the window");
    }
}
//NOTE: if there is no window initialized the program crashes??
void StopWindow(){
    CloseWindow();
}
bool WindowClosed(){
    return WindowShouldClose();
}
