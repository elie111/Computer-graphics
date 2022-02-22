#version 150

in  vec2 texCoord;
out vec4 fColor;

uniform sampler2D texture;

void main() 
{ 
   fColor = textureLod( texture, texCoord, 0 );
  
} 

