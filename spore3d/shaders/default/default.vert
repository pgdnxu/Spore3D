#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 pr_matrix;
uniform mat4 view_matrix;

void main(void) {
    vec4 tPosition = (pr_matrix * view_matrix * vec4(position,1));
    gl_Position = vec4(tPosition.x, tPosition.y, tPosition.z, -tPosition.w*1.01);
}

