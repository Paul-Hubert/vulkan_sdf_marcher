#include "camera.h"

#include "context.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(Context& ctx) : ctx(ctx) {
    setup();
}

void Camera::setup() {
    
    projection = glm::perspective(render_fov, (float) ctx.swap.extent.width/ctx.swap.extent.height, render_min, render_distance);
    
}

void Camera::update() {
    
    if(ctx.input.mouseFree) return;
    
    constexpr float base_speed = 60.f/60;
    
    if(ctx.input.on[Action::SPRINT]) {
        sprinting = true;
    }
    
    float speed = sprinting ? base_speed * 10. : base_speed;
    
    bool moving = false;
    if(ctx.input.on[Action::FORWARD]) {
        position.x -= speed * std::sin(yAxis);//*dt;
        position.z -= speed * std::cos(yAxis);//*dt;
        moving = true;
    } if(ctx.input.on[Action::BACKWARD]) {
        position.x += speed * std::sin(yAxis);//*dt;
        position.z += speed * std::cos(yAxis);//*dt;
        moving = true;
    } if(ctx.input.on[Action::LEFT]) {
        position.x -= speed * std::sin(M_PI/2.0 + yAxis);//*dt;
        position.z -= speed * std::cos(M_PI/2.0 + yAxis);//*dt;
        moving = true;
    } if(ctx.input.on[Action::RIGHT]) {
        position.x += speed * std::sin(M_PI/2.0 + yAxis);//*dt;
        position.z += speed * std::cos(M_PI/2.0 + yAxis);//*dt;
        moving = true;
    } if(ctx.input.on[Action::UP]) {
        position.y += speed;
        moving = true;
    } if(ctx.input.on[Action::DOWN]) {
        position.y -= speed;
        moving = true;
    }
    
    if(!moving) {
        sprinting = false;
    }
    
    yAxis -= (ctx.input.mouseDiff.x) * (M_PI*0.1/180.);
    xAxis = std::max(std::min(xAxis - (ctx.input.mouseDiff.y) * (M_PI*0.1/180.), M_PI/2.), -M_PI/2.);
    
    
    view = glm::mat4(1.0);
    view = glm::translate(view, position);
    view = glm::rotate(view, (float) yAxis, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, (float) xAxis, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::inverse(view);
    
    viewProjection = projection * view;
    
}

glm::mat4 & Camera::getProjection() {
    return projection;
}

glm::mat4 & Camera::getView() {
    return view;
}

glm::mat4 & Camera::getViewProjection() {
    return viewProjection;
}

glm::vec3 Camera::getViewPosition() {
    return position;
}

Camera::~Camera() {
    
}
