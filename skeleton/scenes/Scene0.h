#ifndef Scene0_h
#define Scene0_h

#include "../Scene.h"
#include "../Particle.h"


#include <vector>

class RenderItem;

class Scene0 : public Scene {
public:
    explicit Scene0(std::string name);
    void init() override;
    void cleanup() override;
    void update(double dt) override;

    //Particle factory TODO: hacer esto más general a todas las escenas
    void new_particle(Vector3D pos, Vector3D acc, Vector3D vel);
private:
    std::vector<RenderItem*> render_item_vector;
    std::vector<Particle*> particle_vector;
};

#endif