#version 460 core
in vec2 aTexturePos_;
uniform sampler2D textureUnit1;
uniform sampler2D textureUnit2;
out vec4 fragColor;
void main()
{
    fragColor= mix(texture(textureUnit1,aTexturePos_),texture(textureUnit2,aTexturePos_),0.5);
}