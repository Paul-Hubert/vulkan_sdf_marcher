#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Context;
class Player;

constexpr float render_distance = 1000.f;
constexpr float render_min = 0.1f;
constexpr float render_fov = 70.f;

class Camera {
public:
    Camera(Context& ctx);
    void setup();
    void update();
    ~Camera();
    
    glm::mat4& getProjection();
    glm::mat4& getView();
    glm::mat4& getViewProjection();
    
    glm::vec3 getViewPosition();
    
private:
    
    Context& ctx;
    
    float yAxis;
    float xAxis;
    bool sprinting;
    
    glm::vec3 position;
    
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 viewProjection;
    
};

#endif
