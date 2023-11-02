#version 120

attribute vec3 position;
varying vec4 vertexColor;
uniform float tintAmount;
varying float shaderTintAmount;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vertexColor = gl_Color;
    shaderTintAmount = tintAmount;

    gl_Position = projection * view * model * vec4(position, 1.0);
}