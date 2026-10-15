#include <raylib.h>
#include "../RenderAPI.h"
#include <stdio.h>
#include <assert.h>

#define NUM_MODELS 512
#define NUM_SCENES 3

Camera cameras_array[5];
ID last_camera = 1;

typedef struct Scene{
    Model model_array[NUM_MODELS];
    Transform transform_array[NUM_MODELS];
    Color tint_array[NUM_MODELS];
    bool valid[NUM_MODELS];
    // ...
    ID last_model;
    struct { // Esto es un stack con las ids de los últimos modelos liberados
        ID stack[NUM_MODELS];
        ID stack_pointer;
        bool empty_stack;
    }free_space;
   
}Scene;

SceneAPI current_scene = 0;
Scene scenes[NUM_SCENES]; 
SceneAPI last_scene = 0;

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
    Camera3D ret = cameras_array[camera];
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
// Finds a new empty id in the scene //TODO: si no encuentra una devuelve 0
static ModelAPI FindNewModelID(void){
    if (scenes[current_scene].free_space.empty_stack){
        return ++scenes[current_scene].last_model;
    }

    ID id = scenes[current_scene].free_space.stack[scenes[current_scene].free_space.stack_pointer];
    if (id != 0){
        scenes[current_scene].free_space.stack_pointer--;
    }
    else {
        scenes[current_scene].free_space.empty_stack = true;
    }
    return id;

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
    BeginMode3D(cameras_array[camera]);
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
    Camera3DAPI ret = last_camera;
    last_camera++;
    return ret;

}
bool UpdateCamera3D(Vector3D position, Vector3D look, Vector3D up){
    //TODO
}

ModelAPI CreateSphereModel(float radius, int slices, int rings, Transform3D transform, ColorRGBA tint){
    Mesh SphereMesh = GenMeshSphere(radius, slices, rings);

    ID id = FindNewModelID();
    scenes[current_scene].model_array[id] = LoadModelFromMesh(SphereMesh);
    scenes[current_scene].transform_array[id] = Transform3D_to_Transform(transform);
    scenes[current_scene].tint_array[id] = ColorRGBA_to_Color(tint); 
    scenes[current_scene].valid[id] = true;

    return id;
}
ModelAPI CreatePlaneModel(float length, Transform3D transform, ColorRGBA tint){
    Mesh PlaneMesh = GenMeshPoly(4, length);

    ID id = FindNewModelID();
    scenes[current_scene].model_array[id] = LoadModelFromMesh(PlaneMesh);
    scenes[current_scene].transform_array[id] = Transform3D_to_Transform(transform);
    scenes[current_scene].tint_array[id] = ColorRGBA_to_Color(tint); 
    scenes[current_scene].valid[id] = true;
    //TODO: errores

    return id;
}

SceneAPI CreateScene(){
    Scene scene;
    SceneAPI scene_id = ++last_scene;
    scene.last_model = 0;
    scene.free_space.stack_pointer = 0;
    for (ID i = 0; i < NUM_MODELS; i++){
        scene.valid[i] = false;
    }
    scenes[scene_id] = scene;
    return scene_id;
}

void SelectScene(SceneAPI scene){
    current_scene = scene;
}

void RenderScene(){
    for (ID i = 0; i < NUM_MODELS; i++){
        if (scenes[current_scene].valid[i]){
            Transform t = scenes[current_scene].transform_array[i];
            Vector3 rotation = {0,0,0}; //TODO: poner aquí lo que sería el vector 'up' del quaternion y la rotación en ese ángulo
            DrawModel( //TODO: poner esto en modo ex para poder cargar modelos más complejos
                scenes[current_scene].model_array[i],
                t.translation,
                1,
                scenes[current_scene].tint_array[i]
            );
        }
    }
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
