#version 330 core
struct Material {
  sampler2D texture_diffuse1;
  sampler2D texture_specular1;
};
uniform Material material;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

void main() {
  FragColor = texture(material.texture_diffuse1,TexCoords);
}
