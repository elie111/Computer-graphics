#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);

	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4& GetViewTransformation() const;
	const glm::mat4x4& GetInvViewTransformation() const;
	void SetProjectTransformation(float l,float r,float b,float t, float fovy,float near,float far);
	void SetPerspectivestatus(bool b);
	bool GetPerspectivestatus();
private:
	glm::mat4x4 view_transformation;
	glm::mat4x4 inv_view_transformation;
	glm::mat4x4 projection_transformation;
	bool perspective=false;
};
