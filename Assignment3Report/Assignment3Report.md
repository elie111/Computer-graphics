Assignment 3 

# part 1: 
# basically the function initopenGlRendering divides the screen to two 2D triangles the first one is at indecies (-1, -1),  (1, -1), (-1,  1) which is the upper left side of the screen and the second one is the down right side of the screen  , same for the tex coordinates , the texture and vertices coordinates are forwarded to the fragment shader and by using the function textureLod the color of the fragment is assigned , which will be the color of all the screen , as written in the hint at the  initopenGlRendering The texture is drawn over two triangles that stretch over the screen.
# practicly the function initopenGlRendering generates the VAO (gl_screen_vtc) and texture array object (gl_screen_tex) . next the function bind the VAO which is gl_screen_vtc, after that the function generate a single buffer , then define a vertex array which is the whole screen containing the two triangles described first and a texture array which is also two triangles , we bind the buffer and finally we allocate room for data and pass it. then we initiate the shaders, and activate these shaders. next we find the arrays we passed earlier, both vertex and texture, and send them to the shaders. finally we pass the texture to the shaders, and they will draw the screen.

# part 2: we updated the meshmodel class so now the models are loaded in to the GPU


# part 3:
```
#version 330 core

in  vec2 vTexCoord;
in  vec2 vPosition;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

out vec2 texCoord;

void main()
{



    // Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader
	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec3(model * vec4(pos, 1.0f));
	fragNormal = mat3(model) * normal;

	// Pass the vertex texture coordinates property as it is. Its interpolated value
	// will be avilable for us in the fragment shader
	fragTexCoords = texCoords;

	// This is an internal OpenGL variable, we must set a value to this variable
	gl_Position = projection * view *  model * vec4(pos, 1.0f);

    ////////////////
   // gl_Position.xy = vPosition;
   // gl_Position.z=0;
   // gl_Position.w=1;
    texCoord = vTexCoord;
}

```

# part 4

```

#version 330 core

struct Material
{
	sampler2D textureMap;

};

uniform Material material;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 frag_color;

void main()
{
	vec3 textureColor = vec3(texture(material.textureMap, fragTexCoords));

	frag_color = vec4(0,0,1,1); // the constant color is blue
}



```
