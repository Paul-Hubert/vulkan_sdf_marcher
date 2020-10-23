#version 450

layout(location = 0) out vec3 v_position;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    v_position = vec3(vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2) * 2.0f - 1.0f, 0.0f);
    gl_Position = vec4(v_position, 1.0f);
}
