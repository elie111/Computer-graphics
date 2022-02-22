#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"

//#include <glm/gtx/transform.hpp>
#include "Renderer.h"
#include "Utils.h"
#include "InitShader.h"
#include <math.h>       /* sin */
#include <iostream>

#define PI 3.14159265
#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))
#define infinity 10000000000

Renderer::Renderer() :
	viewport_width(1280),
	viewport_height(720)
{
	InitOpenglRendering();
	CreateBuffers(viewport_width, viewport_height);
	//glewExperimental = GL_TRUE;
	//InitOpenGLRendering();
	//SwapBuffers();
	//CreateBuffers(viewport_width_, viewport_height_);

}
Renderer::Renderer(int viewport_width, int viewport_height) :
	viewport_width(viewport_width),
	viewport_height(viewport_height)
{
	InitOpenglRendering();
	CreateBuffers(viewport_width, viewport_height);
	for (int i = 0; i < 100; i++)
	{
		scalear[i] = 70;
		scalearworld[i] = 1;
	}

	for (int i = 0; i < 100; i++)
	{
		translatexarr[i] = 0;
		translatexarrworld[i] = 0;
	}
	for (int i = 0; i < 100; i++)
	{
		translateyarr[i] = 0;
		translateyarrworld[i] = 0;
	}
	for (int i = 0; i < 100; i++)
	{
		rotatexarr[i] = 0;
		rotatexarrworld[i] = 0;
	}
	for (int i = 0; i < 100; i++)
	{
		rotateyarr[i] = 0;
		rotateyarrworld[i] = 0;
	}
	for (int i = 0; i < 100; i++)
	{
		rotatezarr[i] = 0;
		rotatezarrworld[i] = 0;
	}
}

Renderer::~Renderer()
{
	delete[] color_buffer;
}
float Renderer::AreaOfTri(float X0, float Y0, float X1, float Y1, float X2, float Y2)
{
	//float dArea = ((X1 - X0) * (Y2 - Y0) - (X2 - X0) * (Y1 - dY0)) / 2.0;
	float dArea = (X0 * (Y1 - Y2) + X1 * (Y2 - Y0) + X2 * (Y0 - Y1)) / 2.0;

	return (dArea > 0.0) ? dArea : -dArea;
}
void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width) return;
	if (j < 0) return; if (j >= viewport_height) return;

	color_buffer[INDEX(viewport_width, i, j, 0)] = color.r;
	color_buffer[INDEX(viewport_width, i, j, 1)] = color.g;
	color_buffer[INDEX(viewport_width, i, j, 2)] = color.b;
}
void Renderer::PutPixelpoly(int i, int j, const glm::vec3& color, float z, int modelnum)
{
	if (i < 0) return; if (i >= viewport_width) return;
	if (j < 0) return; if (j >= viewport_height) return;
	if (color.r > 1) {
		color.r == 1;
	}
	if (color.g > 1) {
		color.g == 1;
	}
	if (color.b > 1) {
		color.b == 1;
	}
	if (z >= z_buffer[INDEX(viewport_width, i, j, 0)] && buffermode[modelnum] == 1) {
		

		color_buffer[INDEX(viewport_width, i, j, 0)] = color.r + z / getGreyScale(modelnum);
		color_buffer[INDEX(viewport_width, i, j, 1)] = color.g + z / getGreyScale(modelnum);
		color_buffer[INDEX(viewport_width, i, j, 2)] = color.b + z / getGreyScale(modelnum);
		;
		z_buffer[INDEX(viewport_width, i, j, 0)] = z;
		z_buffer[INDEX(viewport_width, i, j, 1)] = z;
		z_buffer[INDEX(viewport_width, i, j, 2)] = z;
	}
	if (z >= z_buffer[INDEX(viewport_width, i, j, 0)] && buffermode[modelnum] != 1) {
		color_buffer[INDEX(viewport_width, i, j, 0)] = color.r;
		color_buffer[INDEX(viewport_width, i, j, 1)] = color.g;
		color_buffer[INDEX(viewport_width, i, j, 2)] = color.b;
		;
		z_buffer[INDEX(viewport_width, i, j, 0)] = z;
		z_buffer[INDEX(viewport_width, i, j, 1)] = z;
		z_buffer[INDEX(viewport_width, i, j, 2)] = z;
	}



}

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// 
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

	int x, y, deltax, deltay;
	double a;

	x = p1.x;
	y = p1.y;
	deltax = p2.x - p1.x;
	deltay = p2.y - p1.y;
	if (deltax != 0) {
		a = (double)deltay / (double)deltax;
	}
	else {
		a = 1;
	}
	deltax = abs(deltax);
	deltay = abs(deltay);
	if (a >= 0 && a < 1) {
		if (x <= p2.x) {
			int e = -deltax;

			while (x <= p2.x) {
				if (e > 0) {
					y = y + 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x + 1;
				e = e + 2 * deltay;
			}
		}
		else {
			int e = -deltax;

			while (x >= p2.x) {
				if (e > 0) {
					y = y - 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x - 1;
				e = e + 2 * deltay;
			}
		}
	}

	if (a >= 1) {
		if (y <= p2.y) {
			int e = -deltay;

			while (y <= p2.y) {
				if (e > 0) {
					x = x + 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y + 1;
				e = e + 2 * deltax;
			}
		}
		else {
			int e = -deltay;

			while (y >= p2.y) {
				if (e > 0) {
					x = x - 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y - 1;
				e = e + 2 * deltax;
			}
		}
	}
	if (a < 0 && a >= -1) {
		if (x <= p2.x) {
			int e = -deltax;

			while (x <= p2.x) {
				if (e > 0) {
					y = y - 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x + 1;
				e = e + 2 * deltay;
			}
		}
		else {
			int e = -deltax;

			while (x >= p2.x) {
				if (e > 0) {
					y = y + 1;
					e = e - 2 * deltax;
				}
				PutPixel(x, y, color);
				x = x - 1;
				e = e + 2 * deltay;
			}
		}
	}
	if (a < -1) {
		if (y >= p2.y) {
			int e = -deltay;

			while (y >= p2.y) {
				if (e > 0) {
					x = x + 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y - 1;
				e = e + 2 * deltax;
			}
		}

		else {
			int e = -deltay;

			while (y <= p2.y) {
				if (e > 0) {
					x = x - 1;
					e = e - 2 * deltay;
				}
				PutPixel(x, y, color);
				y = y + 1;
				e = e + 2 * deltax;
			}
		}
	}
}


void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenglBuffer(); //Do not remove this line.
	color_buffer = new float[3 * w * h];
	z_buffer = new float[3 * w * h];
	for (int i = 0; i < 3 * w * h; i++)
	{
		z_buffer[i] = -1000000.f;
	}
	ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenglRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &gl_screen_tex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &gl_screen_vtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(gl_screen_vtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[] = {
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1 };

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc) + sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(vtc));

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"), 0);
}

void Renderer::CreateOpenglBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport_width, viewport_height, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewport_width, viewport_height);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewport_width, viewport_height, GL_RGB, GL_FLOAT, color_buffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(gl_screen_vtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewport_width; i++)
	{
		for (int j = 0; j < viewport_height; j++)
		{
			PutPixel(i, j, color);
		}
	}
	for (int i = 0; i < 3 * viewport_width * viewport_height; i++)
	{
		z_buffer[i] = -1000000.f;
	}
}

void Renderer::Render(const Scene& scene)
{

	if (scene.GetModelCount() > 0) {
		// TODO: Replace this code with real scene rendering code
		int half_width = viewport_width / 2;
		int half_height = viewport_height / 2;
		int cx, cy, r, a;

		for (int j = 0; j < scene.GetModelCount(); j++) {
			MeshModel myMesh = scene.GetModel(j);
			float minx, miny, minz, maxx, maxy, maxz;
			minx = 1000000.f;
			miny = 1000000.f;
			minz = 1000000.f;
			maxx = -1000000.f;
			maxy = -1000000.f;
			maxz = -1000000.f;
			std::vector<glm::vec3> ver = myMesh.get_vertices();
			std::vector<glm::vec3> normals = myMesh.get_normals();
			//std::cout  << mdl->GetFace(0).GetVertexIndex(0) <<"//"<< mdl->GetFace(0).GetNormalIndex(0)<<"\n";
			//print vertices
			//for (int i = 0 ;i <  ver.size();i++)
			//	std::cout << "v " <<  ver.at(i).x <<  " " << ver.at(i).y << "  " << ver.at(i).z << "\n";
			// print faces
		//	for (int i = 0 ;i <  mdl->GetFacesCount();i++)
			//	std::cout <<"f " << mdl->GetFace(i).GetVertexIndex(0) <<"//"<< mdl->GetFace(i).GetNormalIndex(0)<< "  "<< mdl->GetFace(i).GetVertexIndex(1) << "//" << mdl->GetFace(i).GetNormalIndex(1) << "  " << mdl->GetFace(i).GetVertexIndex(2) << "//" << mdl->GetFace(i).GetNormalIndex(2) << "\n";
			cx = 500;
			cy = 400;
			r = 100;
			a = 90;
			//DrawLine(glm::ivec2(5 * ver.at(mdl->GetFace(mdl->GetFacesCount()-1).GetVertexIndex(0)).x + 1, 5 * ver.at(mdl->GetFace(mdl->GetFacesCount()-1).GetVertexIndex(0)).y + 1), glm::ivec2(5 * ver.at(mdl->GetFace(mdl->GetFacesCount()-1).GetVertexIndex(1)).x + 1, 5 * ver.at(mdl->GetFace(mdl->GetFacesCount()-1).GetVertexIndex(1)).y + 1), glm::vec3(1.0f, 0.5f, 0.31f));
			//DrawLine(glm::ivec2(100,100),glm::ivec2(100,200), glm::vec3 (1.0f, 0.5f, 0.31f) );
			/*
			for (int i = 0; i < a; i++)
			{
				DrawLine(glm::ivec2(cx, cy), glm::ivec2(cx+r*cos((2*PI*i)/a), cy + r * sin((2 * PI*i) / a)), glm::vec3(1.0f, 0.5f, 0.31f));
		} //circle
		*/
			colorShader.use();
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(getscaleat(j), getscaleat(j), getscaleat(j))); //matrix used to scale points X100
			glm::mat4 mytranslateMatrix = glm::translate(glm::mat4(1.0f), { gettranslatexat(j),gettranslateyat(j),gettranslatezat(j) }); //translate matrix 500 in x units and 100 in y 
			glm::mat4 rotationMatrixx = glm::rotate(glm::mat4(1.0f), glm::radians(getrotatexat(j)), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotationMatrixy = glm::rotate(glm::mat4(1.0f), glm::radians(getrotateyat(j)), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotationMatrixz = glm::rotate(glm::mat4(1.0f), glm::radians(getrotatezat(j)), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 rotation = rotationMatrixz * rotationMatrixy * rotationMatrixx;
			glm::mat4 Tlocal = mytranslateMatrix * rotation * scaleMatrix;
			///
			glm::mat3 blurmat=glm::mat3(0.1);
			glm::mat4 scaleMatrixworld = glm::scale(glm::mat4(1.0f), glm::vec3(getscaleatworld(j), getscaleatworld(j), getscaleatworld(j))); //matrix used to scale points X100
			glm::mat4 mytranslateMatrixworld = glm::translate(glm::mat4(1.0f), { gettranslatexatworld(j),gettranslateyatworld(j),0 }); //translate matrix 500 in x units and 100 in y 
			glm::mat4 rotationMatrixxworld = glm::rotate(glm::mat4(1.0f), glm::radians(getrotatexatworld(j)), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotationMatrixyworld = glm::rotate(glm::mat4(1.0f), glm::radians(getrotateyatworld(j)), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotationMatrixzworld = glm::rotate(glm::mat4(1.0f), glm::radians(getrotatezatworld(j)), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 rotationworld = rotationMatrixzworld * rotationMatrixyworld * rotationMatrixxworld;
			glm::mat4 Tworld = mytranslateMatrixworld * rotationworld * scaleMatrixworld;
			glm::mat4 proj = scene.GetActiveCamera().GetProjectionTransformation();
			glm::mat4 invview = scene.GetActiveCamera().GetInvViewTransformation();
			//glm::mat4 tranform = proj*invview *Tworld * Tlocal;
			glm::mat4 tranform = proj * invview * Tworld * Tlocal;
			glm::vec3 pointamb, pointdiff, pointdifflat, pointspec, pointpos, finalamb, finaldiff, finalspec, finalclr;
			pointpos = { 1,0,0 }; //point light position
			pointamb = modelcolor;
			colorShader.setUniform("model", Tworld * Tlocal);
			colorShader.setUniform("view", invview);
			colorShader.setUniform("projection", proj);
			colorShader.setUniform("material.textureMap", 0);
			texture1.bind(0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(myMesh.GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, myMesh.GetModelVertices().size());
			glBindVertexArray(0);
			texture1.unbind(0);
			pointdiff = modelcolor;
			pointdifflat = {0,0,0};
			pointspec = { 0,0,0 };
			finalamb = modelcolor;
			for (int i = 0; i < myMesh.GetFacesCount(); i++)
			{
				glm::vec4 center, normal1, normal2, normal3, u, v, face_center, face_normal, top_1, top_2, top_3, top_4, bottom_1, bottom_2, bottom_3, bottom_4;

				center.x = (viewport_width / 2);
				center.y = (viewport_height / 2);
				center.z = 1;
				center.w = 1;
				glm::vec4 p1, p2, p3;
				// calculate bounding box 8 points
				//myMesh.calcmax_min();
				top_1 = glm::vec4((float)myMesh.max_x, (float)myMesh.max_y, (float)myMesh.max_z, 1.f);
				top_2 = glm::vec4((float)myMesh.min_x, (float)myMesh.max_y, myMesh.max_z, 1.f);
				top_3 = glm::vec4(myMesh.max_x, myMesh.max_y, myMesh.min_z, 1.f);
				top_4 = glm::vec4(myMesh.min_x, myMesh.max_y, myMesh.min_z, 1.f);
				bottom_1 = glm::vec4((float)myMesh.max_x, (float)myMesh.min_y, (float)myMesh.max_z, 1.f);
				bottom_2 = glm::vec4(myMesh.min_x, myMesh.min_y, myMesh.max_z, 1.f);
				bottom_3 = glm::vec4(myMesh.max_x, myMesh.min_y, myMesh.min_z, 1.f);
				bottom_4 = glm::vec4(myMesh.min_x, myMesh.min_y, myMesh.min_z, 1.f);


				// extract the points

				p1.x = (ver.at(myMesh.GetFace(i).GetVertexIndex(0) - 1)).x;
				p1.y = (ver.at(myMesh.GetFace(i).GetVertexIndex(0) - 1)).y;
				p2.x = (ver.at(myMesh.GetFace(i).GetVertexIndex(1) - 1)).x;
				p2.y = (ver.at(myMesh.GetFace(i).GetVertexIndex(1) - 1)).y;
				p3.x = (ver.at(myMesh.GetFace(i).GetVertexIndex(2) - 1)).x;
				p3.y = (ver.at(myMesh.GetFace(i).GetVertexIndex(2) - 1)).y;
				p1.z = ver.at(myMesh.GetFace(i).GetVertexIndex(0) - 1).z;
				p2.z = ver.at(myMesh.GetFace(i).GetVertexIndex(1) - 1).z;
				p3.z = ver.at(myMesh.GetFace(i).GetVertexIndex(2) - 1).z;
				p1.w = 1;
				p2.w = 1;
				p3.w = 1;
				normal1.x = (normals.at(myMesh.GetFace(i).GetNormalIndex(0) - 1)).x + p1.x;
				normal1.y = (normals.at(myMesh.GetFace(i).GetNormalIndex(0) - 1)).y + p1.y;
				normal1.z = (normals.at(myMesh.GetFace(i).GetNormalIndex(0) - 1)).z + p1.z;
				normal2.x = (normals.at(myMesh.GetFace(i).GetNormalIndex(1) - 1)).x + p2.x;
				normal2.y = (normals.at(myMesh.GetFace(i).GetNormalIndex(1) - 1)).y + p2.y;
				normal2.z = (normals.at(myMesh.GetFace(i).GetNormalIndex(1) - 1)).z + p2.z;
				normal3.x = (normals.at(myMesh.GetFace(i).GetNormalIndex(2) - 1)).x + p3.x;
				normal3.y = (normals.at(myMesh.GetFace(i).GetNormalIndex(2) - 1)).y + p3.y;
				normal3.z = (normals.at(myMesh.GetFace(i).GetNormalIndex(2) - 1)).z + p3.z;
				normal1.w = 1;
				normal2.w = 1;
				normal3.w = 1;

				// calculate face normals
				u = p2 - p1;
				v = p3 - p1;
				face_normal.x = (u.y * v.z) - (u.z * v.y);
				face_normal.y = (u.z * v.x) - (u.x * v.z);
				face_normal.z = (u.x * v.y) - (u.y * v.x);
				face_normal.w = 1;
				face_center.x = (p1.x + p2.x + p3.x) / 3;
				face_center.y = (p1.y + p2.y + p3.y) / 3;
				face_center.z = (p1.z + p2.z + p3.z) / 3;
				face_center.w = 1;
				face_normal = face_normal + face_center;
				//now we transform the points according to scale and translate matrix
				p1 = tranform * p1;
				p2 = tranform * p2;
				p3 = tranform * p3;
				normal1 = tranform * normal1;
				normal2 = tranform * normal2;
				normal3 = tranform * normal3;
				center = mytranslateMatrixworld * mytranslateMatrix * center;
				face_center = tranform * face_center;
				face_normal = tranform * face_normal;
				top_1 = tranform * top_1;
				top_2 = tranform * top_2;
				top_3 = tranform * top_3;
				top_4 = tranform * top_4;
				bottom_1 = tranform * bottom_1;
				bottom_2 = tranform * bottom_2;
				bottom_3 = tranform * bottom_3;
				bottom_4 = tranform * bottom_4;
				// viewport transformation
				p1.x = p1.x + 1 * (viewport_width / 2);
				p1.y = p1.y + 1 * (viewport_height / 2);
				p2.x = p2.x + 1 * (viewport_width / 2);
				p2.y = p2.y + 1 * (viewport_height / 2);
				p3.x = p3.x + 1 * (viewport_width / 2);
				p3.y = p3.y + 1 * (viewport_height / 2);

				normal1.x = normal1.x + 1 * (viewport_width / 2);
				normal1.y = normal1.y + 1 * (viewport_height / 2);
				normal2.x = normal2.x + 1 * (viewport_width / 2);
				normal2.y = normal2.y + 1 * (viewport_height / 2);
				normal3.x = normal3.x + 1 * (viewport_width / 2);
				normal3.y = normal3.y + 1 * (viewport_height / 2);
				face_center.x = face_center.x + 1 * (viewport_width / 2);
				face_center.y = face_center.y + 1 * (viewport_height / 2);
				face_normal.x = face_normal.x + 1 * (viewport_width / 2);
				face_normal.y = face_normal.y + 1 * (viewport_height / 2);
				top_1.x = top_1.x + 1 * (viewport_width / 2);
				top_2.x = top_2.x + 1 * (viewport_width / 2);
				top_3.x = top_3.x + 1 * (viewport_width / 2);
				top_4.x = top_4.x + 1 * (viewport_width / 2);
				top_1.y = top_1.y + 1 * (viewport_height / 2);
				top_2.y = top_2.y + 1 * (viewport_height / 2);
				top_3.y = top_3.y + 1 * (viewport_height / 2);
				top_4.y = top_4.y + 1 * (viewport_height / 2);

				bottom_1.x = bottom_1.x + 1 * (viewport_width / 2);
				bottom_2.x = bottom_2.x + 1 * (viewport_width / 2);
				bottom_3.x = bottom_3.x + 1 * (viewport_width / 2);
				bottom_4.x = bottom_4.x + 1 * (viewport_width / 2);
				bottom_1.y = bottom_1.y + 1 * (viewport_height / 2);
				bottom_2.y = bottom_2.y + 1 * (viewport_height / 2);
				bottom_3.y = bottom_3.y + 1 * (viewport_height / 2);
				bottom_4.y = bottom_4.y + 1 * (viewport_height / 2);
				glm::vec4 pos;

				if (lightmode == 3) {
					 pos = glm::vec4(infinity, 0, 0, 0)/* - temp*/;

				}
				else {
				 pos = glm::vec4(1, -1, 1, 0)/* - temp*/;
				}
				glm::vec3 clrv1;
				glm::vec3 to_lightv1 = pos;
				float cos_anglev1, divv;
				to_lightv1 = glm::normalize(to_lightv1);
				divv = sqrt(normal1[0] * normal1[0] + normal1[1] * normal1[1] + normal1[2] * normal1[2]) * sqrt(to_lightv1[0] * to_lightv1[0] + to_lightv1[1] * to_lightv1[1] + to_lightv1[2] * to_lightv1[2]);
				cos_anglev1 = (normal1[0] * to_lightv1[0] + normal1[1] * to_lightv1[1] + normal1[2] * to_lightv1[2]) / divv;
				cos_anglev1 = glm::clamp(cos_anglev1, (float)0.0, (float)1.0);
				//cout << cos_angle << endl;
				clrv1 = glm::vec3(1, 1, 1) * cos_anglev1 * glm::vec3(1.0, 1.0, 1.0);

				//////////////////////////////////
				glm::vec3 clrv2;

				glm::vec3 to_lightv2 = pos;
				float cos_anglev2;
				to_lightv2 = glm::normalize(to_lightv2);
				divv = sqrt(normal2[0] * normal2[0] + normal2[1] * normal2[1] + normal2[2] * normal2[2]) * sqrt(to_lightv2[0] * to_lightv2[0] + to_lightv2[1] * to_lightv2[1] + to_lightv2[2] * to_lightv2[2]);
				cos_anglev2 = (normal2[0] * to_lightv2[0] + normal2[1] * to_lightv2[1] + normal2[2] * to_lightv2[2]) / divv;
				cos_anglev2 = glm::clamp(cos_anglev2, (float)0.0, (float)1.0);
				//cout << cos_angle << endl;
				clrv2 = glm::vec3(1, 1, 1) * cos_anglev2 * glm::vec3(1.0, 1.0, 1.0);
				/////////////////////////////////////
				glm::vec3 clrv3;

				glm::vec3 to_lightv3 = pos;
				float cos_anglev3;
				to_lightv3 = glm::normalize(to_lightv3);
				divv = sqrt(normal3[0] * normal3[0] + normal3[1] * normal3[1] + normal3[2] * normal3[2]) * sqrt(to_lightv3[0] * to_lightv3[0] + to_lightv3[1] * to_lightv3[1] + to_lightv3[2] * to_lightv3[2]);
				cos_anglev3 = (normal3[0] * to_lightv3[0] + normal3[1] * to_lightv3[1] + normal3[2] * to_lightv3[2]) / divv;
				cos_anglev3 = glm::clamp(cos_anglev3, (float)0.0, (float)1.0);
				//cout << cos_angle << endl;
				clrv3 = glm::vec3(1, 1, 1) * cos_anglev3 * glm::vec3(1.0, 1.0, 1.0);

				/*cout << clrv1[0] << " - " << clrv1[1] << " - " << clrv1[2]<<endl;
				cout << clrv2[0] << " - " << clrv2[1] << " - " << clrv2[2] << endl;
				cout << clrv3[0] << " - " << clrv3[1] << " - " << clrv3[2] << endl;
				cout << "&&&&&&&&&&&&&&&&&&&&" << endl;*/
				int minxt = min(min(p1.x, p2.x), p3.x);
				int minyt = min(min(p1.y, p2.y), p3.y);
				int maxxt = max(max(p1.x, p2.x), p3.x);
				int maxyt = max(max(p1.y, p2.y), p3.y);
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

				/*for (float itc = minxtc; itc <= maxxtc; itc+=0.1) {
					for (float jtc = minytc; jtc <= maxytc; jtc+=0.1) {
							float c_overallface_area = AreaOfTri(clrv1.x, clrv1.y, clrv2.x, clrv2.y, clrv3.x, clrv3.y);
							float cz1 = clrv1.z;
							float cz2 = clrv2.z;
							float cz3 = clrv3.z;
							float cA1, cA2, cA3, cdepth;
							cA1 = AreaOfTri(clrv2.x, clrv2.y, clrv3.x, clrv3.y, itc, jtc);
							cA2 = AreaOfTri(clrv1.x, clrv1.y, clrv3.x, clrv3.y, itc, jtc);
							cA3 = AreaOfTri(clrv2.x, clrv2.y, clrv1.x, clrv1.y, itc, jtc);
							cdepth = (cA1 / c_overallface_area) * cz1 + (cA2 / c_overallface_area) * cz2 + (cA3 / c_overallface_area) * cz3;
							glm::vec3 finalgouroadclr = glm::vec3(itc, jtc, cdepth);
					}
				}*/
				

				for (int it = minxt; it <= maxxt; it++) {
					for (int jt = minyt; jt <= maxyt; jt++) {
						//pointamb = { sin(0.1+it ),sin(0.7 + it),sin(0.2 + it) };
					
						
						if (effectmode==1) {
							pointamb = { sin((0.3 * it * it + jt * jt)),sin((0.7 * it * it + jt * jt)),sin((0.4 * it * it + jt * jt)) };
						}

						if (((it - p1.x) * (p2.y - p1.y) - (jt - p1.y) * (p2.x - p1.x) >= 0) &&
							(it - p2.x) * (p3.y - p2.y) - (jt - p2.y) * (p3.x - p2.x) >= 0 &&
							(it - p3.x) * (p1.y - p3.y) - (jt - p3.y) * (p1.x - p3.x) >= 0) {
							float overallface_area = AreaOfTri(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
							float z1 = p1.z;
							float z2 = p2.z;
							float z3 = p3.z;
							float A1, A2, A3, depth;
							glm::vec3 vertex_normal = glm::vec3(face_normal.x, face_normal.y, face_normal.z);
							A1 = AreaOfTri(p2.x, p2.y, p3.x, p3.y, it, jt);
							A2 = AreaOfTri(p1.x, p1.y, p3.x, p3.y, it, jt);
							A3 = AreaOfTri(p2.x, p2.y, p1.x, p1.y, it, jt);
							depth = (A1 / overallface_area) * z1 + (A2 / overallface_area) * z2 + (A3 / overallface_area) * z3;

							glm::vec3 finalgouroadclr = (A1 / overallface_area) * clrv1 + (A2 / overallface_area) * clrv2 + (A3 / overallface_area) * clrv3; // gouraud diffusive color shading
							glm::vec3 interpolatednormal = (A1 / overallface_area) * glm::vec3(normal1) + (A2 / overallface_area) * glm::vec3(normal2) + (A3 / overallface_area) * glm::vec3(normal3);
							//glm::vec4 temp = glm::vec4(it,jt,depth, 1.0);


							// flat diffusive color shading
							if (lightmode == 3) {
								 pos = glm::vec4(infinity, infinity, infinity, 0)/* - temp*/;
							}
							else {
								 pos = glm::vec4(getlightx(), getlighty(), getlightz(), 0)/* - temp*/;
							}
							glm::vec3 to_light = pos;
							float cos_angle, divv;
							to_light = glm::normalize(pos);
							divv = sqrt(vertex_normal[0] * vertex_normal[0] + vertex_normal[1] * vertex_normal[1] + vertex_normal[2] * vertex_normal[2]) * sqrt(to_light[0] * to_light[0] + to_light[1] * to_light[1] + to_light[2] * to_light[2]);
							cos_angle = (vertex_normal[0] * to_light[0] + vertex_normal[1] * to_light[1] + vertex_normal[2] * to_light[2]) / divv;
							cos_angle = glm::clamp(cos_angle, (float)0.0, (float)1.0);
							//cout << cos_angle << endl;
							pointdifflat = glm::vec3(1, 1, 1) * cos_angle * glm::vec3(1.0, 1.0, 1.0);
							//if (cos_angle > 0.0) {
							//	pointdiff = pointdiff * (float)(1.0 - cos_angle);
							//}
							//{
							//	glm::vec3 to_camera, color;
							//	glm::vec4 to_light, temp, reflection;
							//	float temp_result, cos_angle;
							//	glm::vec4 to_camera = glm::vec4(1, 0, 0, 0)/* - temp*/;
							//}
							pointdifflat[0] = pointdifflat[0] > 1.f ? 1.f : pointdifflat[0];
							pointdifflat[1] = pointdifflat[1] > 1.f ? 1.f : pointdifflat[1];
							pointdifflat[2] = pointdifflat[2] > 1.f ? 1.f : pointdifflat[2];

							//phong diffusive color shaing

							to_light = glm::normalize(pos);
							divv = sqrt(interpolatednormal[0] * interpolatednormal[0] + interpolatednormal[1] * interpolatednormal[1] + interpolatednormal[2] * interpolatednormal[2]) * sqrt(to_light[0] * to_light[0] + to_light[1] * to_light[1] + to_light[2] * to_light[2]);
							cos_angle = (interpolatednormal[0] * to_light[0] + interpolatednormal[1] * to_light[1] + interpolatednormal[2] * to_light[2]) / divv;
							cos_angle = glm::clamp(cos_angle, (float)0.0, (float)1.0);
							//cout << cos_angle << endl;
							pointdiff = glm::vec3(1, 1, 1) * cos_angle * glm::vec3(1.0, 1.0, 1.0);
							//if (cos_angle > 0.0) {
							//	pointdiff = pointdiff * (float)(1.0 - cos_angle);
							//}
							//{
							//	glm::vec3 to_camera, color;
							//	glm::vec4 to_light, temp, reflection;
							//	float temp_result, cos_angle;
							//	glm::vec4 to_camera = glm::vec4(1, 0, 0, 0)/* - temp*/;
							//}
							pointdiff[0] = pointdiff[0] > 1.f ? 1.f : pointdiff[0];
							pointdiff[1] = pointdiff[1] > 1.f ? 1.f : pointdiff[1];
							pointdiff[2] = pointdiff[2] > 1.f ? 1.f : pointdiff[2];


							// phong specular shading
							interpolatednormal = glm::normalize(interpolatednormal);
							glm::vec3 lightposition = glm::normalize(pos);
							glm::vec3 reflection = lightposition - 2 * (glm::dot(lightposition, interpolatednormal)) * interpolatednormal;
							divv = sqrt(reflection[0] * reflection[0] + reflection[1] * reflection[1] + reflection[2] * reflection[2]) * 1;// sqrt(to_light[0] * to_light[0] + to_light[1] * to_light[1] + to_light[2] * to_light[2]);
							cos_angle = (reflection[0] + reflection[1] + reflection[2]) / divv;
							cos_angle = glm::clamp(cos_angle, (float)0.0, (float)1.0);
							glm::vec3 specclr = glm::vec3(1, 1, 1) * cos_angle * glm::vec3(1, 0, 0);
							//reflection = glm::vec3(10,10,10)*reflection + glm::vec3(face_center);
							//reflection = reflection + glm::vec3(1,1,1);
							//reflection = glm::normalize(reflection);
							specclr[0] = specclr[0] > 1.f ? 1.f : specclr[0];
							specclr[1] = specclr[1] > 1.f ? 1.f : specclr[1];
							specclr[2] = specclr[2] > 1.f ? 1.f : specclr[2];


							if (buffermode[j] == 1) {



								//DrawLinepoly(glm::ivec2(it, jt), glm::ivec2(it, jt), glm::vec3(0.4f, 0.4f, 0.4f), p1, p2, p3); //using Z-buffer
								PutPixelpoly(it, jt, glm::vec3(0.4f, 0.4f, 0.4f), depth, j);


							}
							if (buffermode[j] == 2) {
								if (lightmode == 0) {

									PutPixelpoly(it, jt, pointamb + pointdiff, depth, j);//goaraud
								}
								if (lightmode == 1) {

									PutPixelpoly(it, jt, pointamb + pointdifflat, depth, j);//flat
								}
								if (lightmode == 2||lightmode==3) {
									

									PutPixelpoly(it, jt, pointamb + pointdiff+specclr, depth, j);//phong
								}
								//DrawLine(glm::ivec2(face_center.x, face_center.y), glm::ivec2(reflection.x, reflection.y), glm::vec3(0.0f, 0.0f, 0.0f));
								//DrawLinepoly(glm::ivec2(it, jt), glm::ivec2(it, jt), glm::vec3(r, g, b), p1, p2, p3); //using Z-buffer colors
								//cout << pointdiff[0] << pointdiff[1] << pointdiff[2] << endl;
								
								
								if (effectmode == 2 ) {
									float new_red = 0;
									float new_green = 0;
									float new_blue = 0;
									for (int kernelx = it - 1; kernelx <= it + 1; kernelx++) {
										for (int kernely = jt - 1; kernely <= jt + 1; kernely++) {
											
												new_red +=( color_buffer[INDEX(viewport_width, kernelx, kernely, 0)] );
												new_green += (color_buffer[INDEX(viewport_width, kernelx, kernely, 1)] );
												new_blue += (color_buffer[INDEX(viewport_width, kernelx, kernely, 2)]);
												

										}
									}
									new_red /= 9;
									new_green /= 9;
									new_blue /= 9;
									pointamb = glm::vec3( new_red,new_green,new_blue );
									if (lightmode == 0) {

										PutPixelpoly(it, jt, pointamb , depth, j);//goaraud
									}
									if (lightmode == 1) {

										PutPixelpoly(it, jt, pointamb , depth, j);//flat
									}
									if (lightmode == 2 || lightmode == 3) {


										PutPixelpoly(it, jt, pointamb + pointdiff + specclr, depth, j);//phong
									}
								}
							}
							if (buffermode[j] == 3) {
								DrawLine(glm::ivec2(it, jt), glm::ivec2(it, jt), glm::vec3(1, 0, 0)); // without z buffer

							}
						}
					}
				}
				// draw the transformed object using drawline function
				if (buffermode[j] == 0) {
					DrawLine(glm::ivec2(p1.x, p1.y), glm::ivec2(p2.x, p2.y), glm::vec3(1.0f, 0.0f, 0.0f));
					DrawLine(glm::ivec2(p1.x, p1.y), glm::ivec2(p3.x, p3.y), glm::vec3(1.0f, 0.0f, 0.0f));
					DrawLine(glm::ivec2(p2.x, p2.y), glm::ivec2(p3.x, p3.y), glm::vec3(1.0f, 0.0f, 0.0f));
				}
				if (boundingrec) {
					DrawLine(glm::ivec2(p1.x, p1.y), glm::ivec2(p2.x, p2.y), glm::vec3(0.0f, 0.0f, 0.1f));
					DrawLine(glm::ivec2(p1.x, p1.y), glm::ivec2(p1.x, p3.y), glm::vec3(0.0f, 0.0f, 0.1f));
					DrawLine(glm::ivec2(p1.x, p3.y), glm::ivec2(p2.x, p3.y), glm::vec3(0.0f, 0.0f, 0.1f));
					DrawLine(glm::ivec2(p2.x, p3.y), glm::ivec2(p2.x, p2.y), glm::vec3(0.0f, 0.0f, 0.1f));
				}


				/*DrawLine(glm::ivec2(p1.x, p1.y), glm::ivec2(p2.x, p2.y), glm::vec3(r, g, b));
				DrawLine(glm::ivec2(p1.x, p1.y), glm::ivec2(p1.x, p3.y), glm::vec3(r, g, b));
				DrawLine(glm::ivec2(p1.x, p3.y), glm::ivec2(p2.x, p3.y), glm::vec3(r, g, b));
				DrawLine(glm::ivec2(p2.x, p3.y), glm::ivec2(p2.x, p2.y), glm::vec3(r, g, b));*/

				if (normalstatus) {// draw the vertexes normals
					DrawLine(glm::ivec2(p1.x, p1.y), glm::ivec2(normal1.x, normal1.y), glm::vec3(1.0f, 0.5f, 0.31f));
					DrawLine(glm::ivec2(p2.x, p2.y), glm::ivec2(normal2.x, normal2.y), glm::vec3(1.0f, 0.5f, 0.31f));
					DrawLine(glm::ivec2(p3.x, p3.y), glm::ivec2(normal3.x, normal3.y), glm::vec3(1.0f, 0.5f, 0.31f));
				}

				if (facenormalstatus)//face normal;
					DrawLine(glm::ivec2(face_center.x, face_center.y), glm::ivec2(face_normal.x, face_normal.y), glm::vec3(1.0f, 0.5f, 0.31f));
				if (bounding) {
					DrawLine(glm::ivec2(top_1.x, top_1.y), glm::ivec2(top_2.x, top_2.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(top_1.x, top_1.y), glm::ivec2(top_3.x, top_3.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(top_2.x, top_2.y), glm::ivec2(top_4.x, top_4.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(top_4.x, top_4.y), glm::ivec2(top_3.x, top_3.y), glm::vec3(0.0f, 0.f, 0.f));

					DrawLine(glm::ivec2(bottom_1.x, bottom_1.y), glm::ivec2(bottom_2.x, bottom_2.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(bottom_1.x, bottom_1.y), glm::ivec2(bottom_3.x, bottom_3.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(bottom_2.x, bottom_2.y), glm::ivec2(bottom_4.x, bottom_4.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(bottom_4.x, bottom_4.y), glm::ivec2(bottom_3.x, bottom_3.y), glm::vec3(0.0f, 0.f, 0.f));

					DrawLine(glm::ivec2(bottom_1.x, bottom_1.y), glm::ivec2(top_1.x, top_1.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(bottom_2.x, bottom_2.y), glm::ivec2(top_2.x, top_2.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(bottom_3.x, bottom_3.y), glm::ivec2(top_3.x, top_3.y), glm::vec3(0.0f, 0.f, 0.f));
					DrawLine(glm::ivec2(bottom_4.x, bottom_4.y), glm::ivec2(top_4.x, top_4.y), glm::vec3(0.0f, 0.f, 0.f));
				}
				//x local Axes
				//DrawLine(glm::ivec2(0, center.y), glm::ivec2((viewport_width), center.y), glm::vec3(1.0f, 0.2f, 0.7f));
				//y local Axes
				//DrawLine(glm::ivec2(center.x, 0), glm::ivec2(center.x, viewport_height), glm::vec3(1.0f, 0.2f, 0.7f));


			}


		}


		/*
			for (int i = 0; i < 50; i++) {
				DrawLine(glm::ivec2(355 + i, 350 + i), glm::ivec2(355 + i, 300 + i), glm::vec3(0.988, 0.808, 0.));
			}
			for (int i = 0; i< 100; i++) {
				DrawLine(glm::ivec2(130+i, 250+i), glm::ivec2(130+i, 300+i), glm::vec3(0.078, 0.761, 0.863));
			}
			for (int i = 0; i < 100; i++) {
				DrawLine(glm::ivec2(230 + i, 350- i), glm::ivec2(230 + i, 400 - i), glm::vec3(0.353, 0.741, 0.565));
			}
			for (int i = 0; i < 100; i++) {
				DrawLine(glm::ivec2(230 + i, 250 + i), glm::ivec2(230 + i, 300 + i), glm::vec3(0.914, 0.129, 0.149));
			}
			for (int i = 0; i < 100; i++) {
				DrawLine(glm::ivec2(330 + i, 350 - i), glm::ivec2(330 + i, 400 - i), glm::vec3(0.882, 0.4, 0.137));
			}
			for (int i = 0; i < 25; i++) {
				DrawLine(glm::ivec2(405 + i, 350 + i), glm::ivec2(405 + i, 400 - i), glm::vec3(0.125, 0.729, 0.875));
			}
			for (int i = 0; i < 10; i++) {
				DrawLine(glm::ivec2(500 + i, 250 ), glm::ivec2(500 + i, 400), glm::vec3(0., 0., 0.));
				DrawLine(glm::ivec2(600 + i, 250 ), glm::ivec2(600 + i, 400), glm::vec3(0., 0., 0.));
				DrawLine(glm::ivec2(650 + i, 250), glm::ivec2(650 + i, 400), glm::vec3(0., 0., 0.));
				DrawLine(glm::ivec2(750 + i, 250), glm::ivec2(750 + i, 400), glm::vec3(0., 0., 0.));
			}
			for (int i = 0; i < 110; i++) {
				DrawLine(glm::ivec2(500 + i, 315 ), glm::ivec2(500 + i, 325 ), glm::vec3(0., 0., 0.));
			}
			for (int i = 0; i < 100; i++) {
				DrawLine(glm::ivec2(650 + i, 250), glm::ivec2(650 + i, 260), glm::vec3(0., 0., 0.));
			}
			*/
	}
	//x Axes
	//DrawLine(glm::ivec2(0, (viewport_height / 2)), glm::ivec2((viewport_width ), (viewport_height / 2)), glm::vec3(0.0f, 0.0f, 0.0f));
	//y axes
	//DrawLine(glm::ivec2((viewport_width / 2), 0), glm::ivec2((viewport_width / 2), viewport_height), glm::vec3(0.0f, 0.0f, 0.0f));
}

int Renderer::GetViewportWidth() const
{
	return viewport_width;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height;
}

void Renderer::setscale(int s) {
	scale = s;
}
int Renderer::getscale()
{
	return scale;
}

void Renderer::settranslatex(int s) {
	translatex = s;
}
int Renderer::gettranslatex()
{
	return translatex;
}
void Renderer::settranslatey(int s) {
	translatey = s;
}
int Renderer::gettranslatey()
{
	return translatey;
}

void Renderer::setdegreex(int s) {
	degreex = s;
}
float Renderer::getdegreex()
{
	return degreex;
}

void Renderer::setdegreey(int s) {
	degreey = s;
}
float Renderer::getdegreey()
{
	return degreey;
}

void Renderer::setdegreez(int s) {
	degreez = s;
}
float Renderer::getdegreez()
{
	return degreez;
}

void Renderer::setCurrentModel(int s) {
	currentModel = s;
}
int Renderer::getCurrentModel()
{
	return currentModel;
}

//////////////////////////////////////////

void Renderer::setscaleworld(int s) {
	scaleworld = s;
}
int Renderer::getscaleworld()
{
	return scaleworld;
}

void Renderer::settranslatexworld(int s) {
	translatexworld = s;
}
int Renderer::gettranslatexworld()
{
	return translatexworld;
}
void Renderer::settranslateyworld(int s) {
	translateyworld = s;
}
int Renderer::gettranslateyworld()
{
	return translateyworld;
}

void Renderer::setdegreexworld(int s) {
	degreexworld = s;
}
float Renderer::getdegreexworld()
{
	return degreexworld;
}

void Renderer::setdegreeyworld(int s) {
	degreeyworld = s;
}
float Renderer::getdegreeyworld()
{
	return degreeyworld;
}

void Renderer::setdegreezworld(int s) {
	degreezworld = s;
}
float Renderer::getdegreezworld()
{
	return degreezworld;
}
/// /// /////
void Renderer::setscaleat(int index, float val) {
	scalear[index] = val;
}
int Renderer::getscaleat(int index) {
	return scalear[index];
}


void Renderer::settranslatexat(int index, int val) {
	translatexarr[index] = val;
}
int Renderer::gettranslatexat(int index) {
	return translatexarr[index];
}

void Renderer::settranslateyat(int index, int val) {
	translateyarr[index] = val;
}
int Renderer::gettranslateyat(int index) {
	return translateyarr[index];
}

void Renderer::settranslatezat(int index, int val) {
	translatezarr[index] = val;
}
int Renderer::gettranslatezat(int index) {
	return translatezarr[index];
}


void Renderer::setrotatexat(int index, int val) {
	rotatexarr[index] = val;
}
float Renderer::getrotatexat(int index) {
	return rotatexarr[index];
}


void Renderer::setrotateyat(int index, int val) {
	rotateyarr[index] = val;
}
float Renderer::getrotateyat(int index) {
	return rotateyarr[index];
}


void Renderer::setrotatezat(int index, int val) {
	rotatezarr[index] = val;
}
float Renderer::getrotatezat(int index) {
	return rotatezarr[index];
}

// ///////////////////////////////////////////////////////////


void Renderer::setscaleatworldat(int index, int val) {
	scalearworld[index] = val;
}
int Renderer::getscaleatworld(int index) {
	return scalearworld[index];
}


void Renderer::settranslatexatworld(int index, int val) {
	translatexarrworld[index] = val;
}
int Renderer::gettranslatexatworld(int index) {
	return translatexarrworld[index];
}

void Renderer::settranslateyatworld(int index, int val) {
	translateyarrworld[index] = val;
}
int Renderer::gettranslateyatworld(int index) {
	return translateyarrworld[index];
}


void Renderer::setrotatexatworld(int index, int val) {
	rotatexarrworld[index] = val;
}
float Renderer::getrotatexatworld(int index) {
	return rotatexarrworld[index];
}


void Renderer::setrotateyatworld(int index, int val) {
	rotateyarrworld[index] = val;
}
float Renderer::getrotateyatworld(int index) {
	return rotateyarrworld[index];
}


void Renderer::setrotatezatworld(int index, int val) {
	rotatezarrworld[index] = val;
}
float Renderer::getrotatezatworld(int index) {
	return rotatezarrworld[index];
}
void Renderer::setdrawnormalstatus(bool b) {
	normalstatus = b;
}
void Renderer::setdrawfacenormalstatus(bool b) {
	facenormalstatus = b;
}
void Renderer::setbounding(bool b) {
	bounding = b;
}
void Renderer::setboundingrec(bool b) {
	boundingrec = b;
}

float Renderer::min_three(float a, float b, float c) {
	if (a < b && a < c)
		return a;
	else if (b < a && b < c)
		return b;
	else
		return c;
}

float Renderer::max_three(float a, float b, float c) {
	if (a > b && a > c)
		return a;
	else if (b > a && b > c)
		return b;
	else
		return c;
}

void Renderer::setbuffermode(int index, int b) {
	buffermode[index] = b;
}

int Renderer::getbuffermode(int index) {
	return buffermode[index];
}

void Renderer::setGreyScale(int index, int gs) {
	grscale[index] = gs;
}

int Renderer::getGreyScale(int index) {
	return grscale[index];
}



void Renderer::setmodelcolor(glm::vec4 clear_color) {
	modelcolor = clear_color;

}
glm::vec4 Renderer::getmodelcolor() {
	return modelcolor;

}

void Renderer::setlightmode(int mode) {
	lightmode = mode;

}
int Renderer::getlightmode() {
	return lightmode;

}

void Renderer::setlightx(int value) {
	lightmovex = value;

}
int Renderer::getlightx() {
	return lightmovex;

}

void Renderer::setlighty(int value) {
	lightmovey = value;

}
int Renderer::getlighty() {
	return lightmovey;

}

void Renderer::setlightz(int value) {
	lightmovez = value;

}
int Renderer::getlightz() {
	return lightmovez;

}
void Renderer::seteffectmode(int val) {
	effectmode = val;
}
void Renderer::LoadShaders()
{
	colorShader.loadShaders("vshader.glsl", "fshader.glsl");
}