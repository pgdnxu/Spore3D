#version 330 core

uniform sampler1D   colorRamp;
in float tc_width;
out vec4 fColor;

void main(void) {
    
    fColor = vec4(0.0, 1.0, 0.0, 1.0);
//    fColor = texture(colorRamp, tc_width);
}

