#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ShaderProgram.h>
#include <Texture2D.h>


class Renderer
{
public:
	Renderer();
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render(const Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	int getscale();
	void setscale(int s);
	int gettranslatex();
	void settranslatex(int s);
	int gettranslatey();
	void settranslatey(int s);
	int gettranslatez();
	void settranslatez(int s);
	float getdegreex();
	void setdegreex(int s);

	float getdegreey();
	void setdegreey(int s);

	float getdegreez();
	void setdegreez(int s);

	int getCurrentModel();
	void setCurrentModel(int s);


	int getscaleworld();
	void setscaleworld(int s);
	int gettranslatexworld();
	void settranslatexworld(int s);
	int gettranslateyworld();
	void settranslateyworld(int s);
	float getdegreexworld();
	void setdegreexworld(int s);

	float getdegreeyworld();
	void setdegreeyworld(int s);

	float getdegreezworld();
	void setdegreezworld(int s);
	void setscaleat(int index, float val);
	int getscaleat(int index);


	void settranslatexat(int index, int val);
	int gettranslatexat(int index);
	void settranslateyat(int index, int val);
	int gettranslateyat(int index);
	void settranslatezat(int index, int val);
	int gettranslatezat(int index);


	void setrotatexat(int index, int val);
	float getrotatexat(int index);
	void setrotateyat(int index, int val);
	float getrotateyat(int index);
	void setrotatezat(int index, int val);
	float getrotatezat(int index);

	void setbuffermode(int index,int buffermode);
	int getbuffermode(int index);



	// //////

	void setscaleatworldat(int index, int val);
	int getscaleatworld(int index);

	void setmodelcolor(glm::vec4 clear_color);
	glm::vec4 getmodelcolor();

	void settranslatexatworld(int index, int val);
	int gettranslatexatworld(int index);
	void settranslateyatworld(int index, int val);
	int gettranslateyatworld(int index);

	void setGreyScale(int index,int gs);
	int getGreyScale(int index);

	void setlightmode(int index);
	int getlightmode();


	void setrotatexatworld(int index, int val);
	float getrotatexatworld(int index);
	void setrotateyatworld(int index, int val);
	float getrotateyatworld(int index);
	void setrotatezatworld(int index, int val);
	float getrotatezatworld(int index);
	void setdrawnormalstatus(bool b);
	void setdrawfacenormalstatus(bool b);
	void setbounding(bool b);
	void setboundingrec(bool b);
	void seteffectmode(int val);




	float min_three(float a, float b, float c);
	float max_three(float a, float b, float c);
	float AreaOfTri(float X0, float Y0, float X1, float Y1, float X2, float Y2);

	void setlightx( int val);
	int getlightx();

	void setlighty( int val);
	int getlighty();

	void setlightz( int val);
	int getlightz();
	void LoadShaders();

	
private:
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void PutPixelpoly(const int i, const int j, const glm::vec3& color,float z,int modelnum);
	void DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);

	void CreateBuffers(int w, int h);
	void CreateOpenglBuffer();
	void InitOpenglRendering();
	Texture2D texture1;
	float* color_buffer;
	float* z_buffer;
	int viewport_width;
	int viewport_height;
	float scale=1;
	bool normalstatus = false;
	bool facenormalstatus = false;
	bool bounding = false;
	bool boundingrec = false;
	int translatex=0;
	int translatey = 0;
	int translatez = 0;
	float degreex = 0;
	float degreey = 0;
	float degreez = 0;

	int scaleworld = 1;
	int translatexworld = 0;
	int translateyworld = 0;
	float degreexworld = 0;
	float degreeyworld = 0;
	float degreezworld = 0;
	float lightx = 1;
	float lighty = 0;
	float lightz = 0;
	int currentModel = 0;
	float  scalear[100] ;
	int  translatexarr[100];
	int  translateyarr[100];
	int  translatezarr[100];
	int  rotatexarr[100];
	int  rotateyarr[100];
	int  rotatezarr[100];
	int grscale[100];

	int  scalearworld[100];
	int  translatexarrworld[100];
	int  translateyarrworld[100];
	int  rotatexarrworld[100];
	int  rotateyarrworld[100];
	int  rotatezarrworld[100];
	GLuint gl_screen_tex;
	GLuint gl_screen_vtc;
	int buffermode[100] ;// 0 no buffer 1 color buffer 2 z buffer
	glm::vec4 modelcolor;
	int lightmode;
	int  lightmovex;
	int  lightmovey;
	int  lightmovez;
	int effectmode;
	ShaderProgram colorShader;
};
