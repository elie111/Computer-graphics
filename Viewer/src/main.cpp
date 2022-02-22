#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"
#include <glm/ext/matrix_transform.hpp>



/**
 * Fields
 */
static int bmode = 0;

bool show_demo_window = false;
bool local_controller = false;
bool world_controller = false;
bool light_controller = false;
bool camera_controller = false;
bool show_another_window = false;
static int grscale = 20;
int grscalearr[100];
static float scalex = 70;
static float translatex = 0;
static float translatey = 0;
static float translatez = 0;
static float rotatex = 0;
static float rotatey = 0;
static float rotatez = 0;
static bool norm = false;
static bool facenorm = false;
static int isperspective = 0;
static int lightmode = 0;
static int effectmode = 0;

static bool bounding = false;
static bool boundingrec = false;
float scale[10];
static float scalexworld = 1;
static float translatexworld = 0;
static float translateyworld = 0;
static float rotatexworld = 0;
static float rotateyworld = 0;
static float rotatezworld = 0;
static float fovy = 45.f;
static float lightx = 1;
static float lighty = 0;
static float lightz = 0;

//static float l = -17.77777f;
//static float r = 17.77777f;

static float leftcam = -1.f;
static float rightcam = 1.f;
static float bottomcam = -1.f;
static float topcam = 1.f;
static float nearcam = -1.f;
static float farcam = 45.f;

int lightnum = 1;
int currentlightnum = 0;


//static float l = -80;
//static float r = 80;
//static float b = -45;
//static float t = 45;


float  scalear[100] ;
int  translatexarr[100];
int  translateyarr[100];
int  translatezarr[100];
int  rotatexarr[100];
int  rotateyarr[100];
int  rotatezarr[100];

int bmodearr[100];
float  scalearworld[100];
int  translatexarrworld[100];
int  translateyarrworld[100];
int  rotatexarrworld[100];
int  rotateyarrworld[100];
int  rotatezarrworld[100];


int  movexlight[100];
int  moveylight[100];
int  movezlight[100];

float cameraleft[100];
float cameraright[100];
float cameraup[100];
float cameradown[100];
float cameranear[100];
float camerafar[100];
float camerafovy[100];
bool camerapers[100];
std::shared_ptr<Camera> camarray[100];

static int currentModel = 0;
static int cam_num = 1;
glm::vec4 clear_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec4 clear_color2 = glm::vec4(1.f, 0.f, 0.0f, 0.f);

/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);

/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}

// debug tool
void printmat(glm::mat4 s)
{
	s = glm::transpose(s);
	cout << s[0][0] << s[0][1] << s[0][2] << s[0][3] << endl <<
		s[1][0] << s[1][1] << s[1][2] << s[1][3] << endl <<
		s[2][0] << s[2][1] << s[2][2] << s[2][3] << endl <<
		s[3][0] << s[3][1] << s[3][2] << s[3][3] << endl;
}

int main(int argc, char **argv)
{
	int windowWidth = 1920, windowHeight = 1080;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;
	for (int i = 0; i < 100; i++)
	{
		scalear[i] = 70;
		scalearworld[i] = 1;
		translatexarr[i] = 0;
		translateyarr[i] = 0;
		translatezarr[i] = 0;
		translatexarrworld[i] = 0;
		translateyarrworld[i] = 0;

	}
	//float qq = glm::dot(glm::vec3(1, 0, 0), glm::vec3(-1, 0, 0));
	//cout << qq;

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	
	std::shared_ptr<Camera> p(new Camera());
	camarray[cam_num-1] = p;
	
	//Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);
	Renderer renderer;
	renderer.LoadShaders();
	Scene scene = Scene();
	scene.AddCamera(p);
	scene.SetActiveCameraIndex(0);
	//p->SetProjectTransformation((-windowWidth / 2), (windowWidth / 2), -(windowHeight / 2), (windowHeight / 2));
	//glm::mat4 scaleMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(50.f, 50.f, 50.f));
	p->SetProjectTransformation((-1), (1), (-1), (1),fovy,nearcam,farcam);
	//printmat(p->GetProjectionTransformation());
	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);
    while (!glfwWindowShouldClose(window))
    {
		glfwPollEvents();
		StartFrame();
		DrawImguiMenus(io, scene);
		renderer.setCurrentModel(currentModel);
		scene.SetActiveCameraIndex(cam_num - 1);
		scene.SetActiveModelIndex(currentModel);

		camarray[scene.GetActiveCameraIndex()]->SetProjectTransformation(leftcam, rightcam, bottomcam, topcam, fovy, nearcam, farcam);
		camarray[scene.GetActiveCameraIndex()]->SetPerspectivestatus((bool)isperspective);

		


	

     
		
			
		
		

		scalear[currentModel] = renderer.getscaleat(currentModel);
		translatexarr[currentModel] = translatex;
		translateyarr[currentModel] = translatey;
		translatezarr[currentModel] = translatez;
		rotatexarr[currentModel] = rotatex;
		rotateyarr[currentModel] = rotatey;
		rotatezarr[currentModel] = rotatez;
		scalearworld[currentModel] = scalexworld;
		translatexarrworld[currentModel] = translatexworld;
		translateyarrworld[currentModel] = translateyworld;
		rotatexarrworld[currentModel] = rotatexworld;
		rotateyarrworld[currentModel] = rotateyworld;
		rotatezarrworld[currentModel] = rotatezworld;
		cameraleft[cam_num-1] = leftcam;
		cameraright[cam_num-1] = rightcam;
		cameraup[cam_num-1] = topcam;
		cameradown[cam_num-1] = bottomcam;
		cameranear[cam_num-1] = nearcam;
		camerafar[cam_num-1] = farcam;
		camerafovy[cam_num-1] = fovy;
		camerapers[cam_num-1] = isperspective;
		bmodearr[currentModel] = bmode;
		grscalearr[currentModel] = grscale;
		movexlight[currentlightnum] = lightx;
		moveylight[currentlightnum] = lighty;
		movezlight[currentlightnum] = lightz;
		renderer.setscaleat(currentModel,scalex);
		renderer.settranslatexat(currentModel,translatex);
		renderer.settranslateyat(currentModel,translatey);
		renderer.settranslatezat(currentModel, translatez);
		renderer.setrotatexat(currentModel,rotatex);
		renderer.setrotateyat(currentModel,rotatey);
		renderer.setrotatezat(currentModel,rotatez);
		renderer.setscaleatworldat(currentModel, scalexworld);
		renderer.settranslatexatworld(currentModel,translatexworld);
		renderer.settranslateyatworld(currentModel,translateyworld);
		renderer.setrotatexatworld(currentModel, rotatexworld);
		renderer.setrotateyatworld(currentModel, rotateyworld);
		renderer.setrotatezatworld(currentModel, rotatezworld);
		renderer.setdrawnormalstatus(norm);
		renderer.setdrawfacenormalstatus(facenorm);
		renderer.setbounding(bounding);
		renderer.setboundingrec(boundingrec);
		renderer.setGreyScale(currentModel,grscale);
		renderer.setlightx(movexlight[currentlightnum]);
		renderer.setlighty(moveylight[currentlightnum]);
		renderer.setlightz(movezlight[currentlightnum]);
		renderer.setmodelcolor(clear_color2);
		renderer.setlightmode(lightmode);
		renderer.seteffectmode(effectmode);
		
	
		
		switch (bmode) {
		case 0:
			renderer.setbuffermode(currentModel,0);
			break;
		case 1:
			renderer.setbuffermode(currentModel,1);
			break;
		case 2:
			renderer.setbuffermode(currentModel,2);
			break;
		case 3:
			renderer.setbuffermode(currentModel,3);
			break;



		}
		RenderFrame(window, scene, renderer, io);
		
    }

	Cleanup(window);
    return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	
	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		// TODO: Set new aspect ratio
	}

	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		if (io.KeysDown[65])
		{
			// A key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
			translatexworld -= 1;
			
		}
		if (io.KeysDown[68])
		{
			// D key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
			translatexworld += 1;

		}
		if (io.KeysDown[76])
		{
			// L key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)

			translatex -= 1;

		}
		if (io.KeysDown[82])
		{
			// R key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)

			translatex += 1;

		}

		if (io.KeysDown[90])
		{
			// R key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)

			scalex += 0.1;

		}
		if (io.KeysDown[88])
		{
			// R key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)

			scalex -= 0.1;

		}
	}

	if (!io.WantCaptureMouse)
	{
		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			// Left mouse button is down
		}
	}

	renderer.ClearColorBuffer(clear_color);
	renderer.Render(scene);
	renderer.SwapBuffers();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	/**
	 * MeshViewer menu
	 */
	

	
	

	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */
	
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;
		const char* models[] = { "model1", "model2", "model3", "model4", "model5", "model6", "model7",
			"model8", "model9", "model10", "model11", "model12", "model13" };
		static const char* current_item = "----";

		ImGui::Begin("main controller");                          // Create a window called "Hello, world!" and append into it.
		
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open", "CTRL+O"))
				{
					nfdchar_t* outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
					if (result == NFD_OKAY)
					{
						
							current_item = models[scene.GetModelCount()];
							currentModel = scene.GetModelCount();
							rotatex = rotatexarr[scene.GetModelCount()];
							rotatey = rotateyarr[scene.GetModelCount()];
							rotatez = rotatezarr[scene.GetModelCount()];
							translatex = translatexarr[scene.GetModelCount()];
							translatey = translateyarr[scene.GetModelCount()];
							translatez = translatezarr[scene.GetModelCount()];
							scalex = scalear[scene.GetModelCount()];

							scalexworld = scalearworld[scene.GetModelCount()];
							translatexworld = translatexarrworld[scene.GetModelCount()];
							translateyworld = translateyarrworld[scene.GetModelCount()];
							rotatexworld = rotatexarrworld[scene.GetModelCount()];
							rotateyworld = rotateyarrworld[scene.GetModelCount()];
							rotatezworld = rotatezarrworld[scene.GetModelCount()];
							bmode = 0;
							grscale = 20;
							
						scene.AddModel(Utils::LoadMeshModel(outPath));
						free(outPath);
					}
					else if (result == NFD_CANCEL)
					{
					}
					else
					{
					}

				}
				ImGui::EndMenu();
			}

			// TODO: Add more menubar items (if you want to)
			ImGui::EndMainMenuBar();
		}
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 5.3f;
		style.FrameRounding = 2.3f;
		style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);

		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_Separator] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		style.Colors[ImGuiCol_Button] = ImVec4(1.0f, 0.0f, 0.0f, 0.83f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.9f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_ButtonActive]= ImVec4(0.9f, 0.00f, 0.00f, 0.83f);;
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
		
		ImGui::Checkbox("local controller       ", &local_controller);      // Edit bools storing our window open/close state
		ImGui::SameLine();
		ImGui::Checkbox("camera controller      ", &camera_controller);

		ImGui::Checkbox("world controller       ", &world_controller);

		ImGui::SameLine();
		ImGui::Checkbox("light controller       ", &light_controller);
		// Menu Bar


		// Controls


		// TODO: Add more controls as needed


		

		ImGuiStyle& style2 = ImGui::GetStyle();
		float w = ImGui::CalcItemWidth();
		float spacing = style.ItemInnerSpacing.x;
		float button_sz = ImGui::GetFrameHeight();
		ImGui::PushItemWidth(w - spacing * 15.0f - button_sz * 2.0f);
		

		
		if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
		{
			
			for (int n = 0; n < scene.GetModelCount(); n++)
			{
				bool is_selected = (current_item == models[n]);
				if (ImGui::Selectable(models[n], is_selected)) {
					current_item = models[n];

					currentModel = n;
					rotatex = rotatexarr[n];
					rotatey = rotateyarr[n];
					rotatez = rotatezarr[n];
					translatex = translatexarr[n];
					translatey = translateyarr[n];
					translatez = translatezarr[n];
					scalex = scalear[n];

					scalexworld = scalearworld[n];
					translatexworld = translatexarrworld[n];
					translateyworld = translateyarrworld[n];
					rotatexworld = rotatexarrworld[n];
					rotateyworld = rotateyarrworld[n];
					rotatezworld = rotatezarrworld[n];
					bmode = bmodearr[n];
					grscale = grscalearr[n];
					


					//string outPath = "C:/Users/faisal/source/repos/computer-graphics-2022-elie-faisal/Data/";
				//	string modeln = models[n];
					//	scene.AddModel(Utils::LoadMeshModel(outPath+modeln+".obj"));


					if (is_selected) {
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine();
		ImGui::Text("Model");
		ImGui::Separator();
		ImGui::RadioButton("none", &bmode, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Z-buffer grey", &bmode, 1); 
		ImGui::SameLine();
		ImGui::RadioButton("Z-buffer colors", &bmode, 2);
		ImGui::SameLine();
		ImGui::RadioButton("color buffer", &bmode ,3);
		ImGuiStyle& style3 = ImGui::GetStyle();
		float w2 = ImGui::CalcItemWidth();
		float spacing2 = style3.ItemInnerSpacing.x;
		float button_sz2 = ImGui::GetFrameHeight();
		ImGui::PushItemWidth(w - spacing * 15 - button_sz * 2.0f);
		ImGui::SliderInt("grey scale", &grscale, 1, 1000);
		ImGui::SameLine();
		if (ImGui::Button("+"))  //this button make reset values
		{
			grscale+=5;

		}
		ImGui::SameLine();
		if (ImGui::Button("-"))  //this button make reset values
		{
			grscale-=5;

		}
		ImGui::SameLine();
		if (ImGui::Button("reset"))  //this button make reset values
		{
			grscale=20;

		}
		ImGui::Separator();
	//	ImGui::Checkbox("z-buffer       ", &zbufferbox);
		//ImGui::SameLine();
		//ImGui::Checkbox("color-buffer", &colorbufferbox);
		//ImGui::Separator();
		ImGui::Checkbox("draw vertixes normals ", &norm);
		ImGui::SameLine();
		ImGui::Checkbox("draw faces normals", &facenorm);
		ImGui::Checkbox("bounding box          ", &bounding);
		ImGui::SameLine();
		ImGui::Checkbox("bounding rectangle for triangles", &boundingrec);
		ImGui::Separator();
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("background color", (float*)&clear_color); // Edit 3 floats representing a color
		ImGui::ColorEdit3("Model color", (float*)&clear_color2);

		/*if (ImGui::Button("local controller"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}*/
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (local_controller)
	{
		ImGui::Begin("local controller");
		
		

ImGui::SliderFloat("scale", &scalex, 0, 4000);
ImGui::SliderFloat("translatex", &translatex, -2000, 2000);
ImGui::SliderFloat("translatey", &translatey, -1000, 1000);
ImGui::SliderFloat("translatez", &translatez, -1000, 1000);
ImGui::SliderFloat("rotatex", &rotatex, -360, 360);
ImGui::SliderFloat("rotatey", &rotatey, -360, 360);
ImGui::SliderFloat("rotatez", &rotatez, -360, 360);


if (ImGui::Button("reset"))  //this button make reset values
{
	rotatex = 0;
	rotatey = 0;
	rotatez = 0;
	translatex = 0;
	translatey = 0;
	translatez = 0;
	scalex = 70;
	

}

ImGui::End();
	}
	if (world_controller) {
		ImGui::Begin("World controller");
		ImGui::SliderFloat("scale world", &scalexworld, 0, 100);
		ImGui::SliderFloat("translate x world", &translatexworld, -2000, 2000);
		ImGui::SliderFloat("translate y world", &translateyworld, -1000, 1000);
		ImGui::SliderFloat("rotate x world", &rotatexworld, -360, 360);
		ImGui::SliderFloat("rotate y world", &rotateyworld, -360, 360);
		ImGui::SliderFloat("rotate z world", &rotatezworld, -360, 360);
		if (ImGui::Button("reset"))  //this button make reset values
		{
			rotatexworld = 0;
			rotateyworld = 0;
			rotatezworld = 0;
			translatexworld = 0;
			translateyworld = 0;
			scalexworld = 1;

		}


		ImGui::End();
	}
	if(camera_controller){
		
		
		
		
		
		
		const char* cameras[] = { "camera1", "camera2", "camera3", "camera4", "camera5", "camera6" };
		static const char* current_camera = cameras[0];

		

		ImGui::Begin("Camera controller");
		
		
		ImGui::RadioButton("orthographic      ", &isperspective, 0);
		ImGui::SameLine();
		ImGui::RadioButton("perspective", &isperspective, 1);
		
		//float w = ImGui::CalcItemWidth();
		//ImGuiStyle& style = ImGui::GetStyle();
		//float spacing = style.ItemInnerSpacing.x;
		//float button_sz = ImGui::GetFrameHeight();
		//ImGui::PushItemWidth(w - spacing * 15.0f - button_sz * 2.0f);
		if (ImGui::BeginCombo("##combo", current_camera)) // The second parameter is the label previewed before opening the combo.
		{

			for (int n = 0; n < scene.GetCameraCount(); n++)
			{
				bool is_selected = (current_camera == cameras[n]);
				if (ImGui::Selectable(cameras[n], is_selected)) {
					current_camera = cameras[n];

					cam_num = n+1;
					leftcam = cameraleft[n];
					rightcam = cameraright[n];
					topcam = cameraup[n];
					bottomcam = cameradown[n];
					nearcam = cameranear[n];
					farcam = camerafar[n];
					fovy = camerafovy[n];
					isperspective = camerapers[n];
					scene.SetActiveCameraIndex(n);


					//string outPath = "C:/Users/faisal/source/repos/computer-graphics-2022-elie-faisal/Data/";
				//	string modeln = models[n];
					//	scene.AddModel(Utils::LoadMeshModel(outPath+modeln+".obj"));


					if (is_selected) {
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
				}
			}
			ImGui::EndCombo();

		}
		ImGui::SameLine();
		if (ImGui::Button("add camera"))  //this button make reset values
		{
			std::shared_ptr<Camera> newcam(new Camera());
			scene.AddCamera(newcam);
			camarray[scene.GetCameraCount()-1] = newcam;
			
			current_camera = cameras[scene.GetCameraCount()-1];
			scene.SetActiveCameraIndex(scene.GetCameraCount()-1);
			
			cam_num = scene.GetCameraCount();
			leftcam = -1.f;
			rightcam = 1.f;
			rightcam = 1.f;
			bottomcam = -1;
			topcam = 1;


			nearcam = -1;
			farcam = 45;
			isperspective = 0;
			fovy = 45;
			
			
			



		}
		ImGui::Separator();
		ImGui::SliderFloat("left", &leftcam, -1.f, -200.f);
		ImGui::SliderFloat("right", &rightcam, 1.f, 200.f);
		ImGui::SliderFloat("bottom", &bottomcam, -1, -100);
		ImGui::SliderFloat("top", &topcam, 1, 100);
		ImGui::SliderFloat("near", &nearcam, -1.f, -100.f);
		ImGui::SliderFloat("far", &farcam, 1, 100);
		ImGui::SliderFloat("fovy persp", &fovy, 0, 180);

		if (ImGui::Button("reset"))  //this button make reset values
		{
			leftcam = -1.f;
			rightcam = 1.f;
			bottomcam = -1;
			topcam = 1;
			
				
				nearcam = -1;
				farcam = 45;
				fovy = 45;
			
		}
		
		ImGui::End();
	}
	if (light_controller) {
		
		ImGui::Begin("light controller");
		ImGui::Text("Shadings");
		ImGui::RadioButton("Gouraud      ", &lightmode, 0);
		ImGui::SameLine();
		ImGui::RadioButton("flat shading", &lightmode, 1);
		
		ImGui::RadioButton("phong shading", &lightmode, 2);
		ImGui::SameLine();
		ImGui::RadioButton("directional light", &lightmode, 3);
		ImGui::Separator();
		ImGui::Text("Post-processing effects");
		ImGui::RadioButton("none", &effectmode, 0);
		ImGui::SameLine();
		ImGui::RadioButton("marble effect", &effectmode, 1);
		ImGui::SameLine();
		ImGui::RadioButton("blur effect", &effectmode, 2);
		ImGui::Separator();
		const char* lights[] = { "light1", "light2", "light3", "light4", "light5", "light6" };
		static const char* current_light = lights[0];
		if (ImGui::BeginCombo("##combo", current_light)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n <lightnum; n++)
			{
				bool is_selected = (current_light == lights[n]);
				if (ImGui::Selectable(lights[n], is_selected)) {
					current_light = lights[n];

					lightx = movexlight[n];
					lighty = moveylight[n];
					lightz = movezlight[n];
					currentlightnum = n;
					


					//string outPath = "C:/Users/faisal/source/repos/computer-graphics-2022-elie-faisal/Data/";
				//	string modeln = models[n];
					//	scene.AddModel(Utils::LoadMeshModel(outPath+modeln+".obj"));


					if (is_selected) {
						ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
					}
				}
			}
			
			ImGui::EndCombo();

		}
		ImGui::SameLine();
		if (ImGui::Button("add light"))  //this button make reset values
		{
			lightnum++;
			lightx = 1;
			lighty = 0;
			lightz = 0;
			
			current_light = lights[lightnum - 1];
			currentlightnum = lightnum-1;


		}
		
		ImGui::SliderFloat("lightx", &lightx, -360, 360);
		ImGui::SameLine();
		if (ImGui::Button("+##addx"))  //this button make reset values
		{
			lightx += 1;

		}
		ImGui::SameLine();
		if (ImGui::Button("-##subx"))  //this button make reset values
		{
			lightx -= 1;

		}
		ImGui::SliderFloat("lighty", &lighty, -360, 360);
		ImGui::SameLine();
		if (ImGui::Button("+##addy"))  //this button make reset values
		{
			lighty += 1;

		}
		ImGui::SameLine();
		if (ImGui::Button("-##suby"))  //this button make reset values
		{
			lighty -= 1;

		}
		ImGui::SliderFloat("lightz", &lightz, -360, 360);
		ImGui::SameLine();
		if (ImGui::Button("+##addz"))  //this button make reset values
		{
			lightz += 1;

		}
		ImGui::SameLine();
		if (ImGui::Button("-##subz"))  //this button make reset values
		{
			lightz -= 1;

		}
		if (ImGui::Button("reset"))  //this button make reset values
		{
			lightx = 1;
			lighty = 0;
			lightz = 0;
		}
		ImGui::End();
	}
	
}

