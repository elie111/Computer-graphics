#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera()
{
	perspective = false;
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 1), // Camera is at (0,0,1), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin (negative z direction)
		glm::vec3(0, 1, 0)  // Head is up 
	);
	view_transformation = View;
	inv_view_transformation = glm::inverse(view_transformation);
	//projection_transformation= glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.f, 100.f);

}

Camera::~Camera()
{
	
}
void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) {
	glm::mat4 View = glm::lookAt(
		eye, // Camera is at (4,3,3), in World Space
		at, // and looks at the origin
		up  // Head is up (set to 0,-1,0 to look upside-down)
	);
	view_transformation = View;
	inv_view_transformation = glm::inverse(view_transformation);
}
void Camera::SetPerspectivestatus(bool b) {
	perspective = b;
}
bool Camera::GetPerspectivestatus() {
	return perspective;
}
const glm::mat4x4& Camera::GetProjectionTransformation() const
{
	return projection_transformation;
}

const glm::mat4x4& Camera::GetViewTransformation() const
{
	return view_transformation;
}
void Camera::SetProjectTransformation(float l, float r, float b, float t,float fovy,float near,float far) {
	if(perspective==false)
	projection_transformation = glm::ortho(l, r, b, t, near, far);
	else {
		float aspect = 1280.f / 720.f;
		projection_transformation = glm::perspective(glm::radians(fovy), aspect, near, far);

	}
		//projection_transformation = glm::frustum(l, r, b, t, 0.f, 10.f);
	//projection_transformation = Projection;
	//projection_transformation = glm::transpose(projection_transformation);
}
const glm::mat4x4& Camera::GetInvViewTransformation() const
{
	//inv_view_transformation = glm::inverse(view_transformation);
	return inv_view_transformation;
}