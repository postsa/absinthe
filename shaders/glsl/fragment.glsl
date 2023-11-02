#version 120

varying vec4 vertexColor;
varying float shaderTintAmount;

void main()
{
    gl_FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z + shaderTintAmount, vertexColor.w);
}