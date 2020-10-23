#version 450

layout(location = 0) in vec3 v_position;

layout(location = 0) out vec4 outColor;

layout(std140, set = 0, binding = 0) uniform UBO {
    mat4 viewproj;
    vec4 viewpos;
    vec2 screensize;
};

const float e = 0.1;
const float d = 1.00001;

float sq(float a) {
    return a * a;
}

float dist(vec3 pos) {
    return length(mod(pos, 50.0f) - 25.0f) - 10.0f;
}

void main() {
    
    vec3 raypos = viewpos.xyz;
    vec3 raydir = normalize(inverse(mat3(viewproj)) * vec3(v_position.xy, 1.0));
    
    for(int i = 0; i<50; i++) {
        float distance = dist(raypos);
        if(distance<e) {
            vec3 normal = normalize(vec3(
                dist(raypos + vec3(d,0,0)) - dist(raypos - vec3(d,0,0)),
                dist(raypos + vec3(0,d,0)) - dist(raypos - vec3(0,d,0)),
                dist(raypos + vec3(0,0,d)) - dist(raypos - vec3(0,0,d))));
            outColor = vec4(1,0,0,1) * (dot(normalize(vec3(1,1,1)), normal) * 0.4 + 0.6);
            //outColor = vec4((normal+1.0f)/2.0f, 1);
            return;
        }
        raypos += raydir * (distance);
    }
    
    outColor = vec4(0.5, 0.5, 0.5, 1);
    
}
