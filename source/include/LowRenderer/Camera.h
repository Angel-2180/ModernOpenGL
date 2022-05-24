#pragma once
#include "LibMaths/Mat4/Mat4.h"
#include "LibMaths/Vec3/Vec3.h"

namespace LowRenderer
{
	const double static degreesToRadians(const double deg)
	{
		return deg * (M_PI / HALF_CIRCLE);
	}
	class Camera
	{
	private:
		//private var
		lm::Mat4<float> viewMatrix;
		lm::vec3 position, front, up, right, worldUp;

		float pitch, yawn, roll;
		float speed, sensitivity;
		//private func
		void updateCamVec();

	public:

		enum DIRECTION { FORWARD = 0, BACKWARD, LEFT, RIGHT };
		//Constructor / Destructor
		Camera(lm::vec3 position, lm::vec3 direction, lm::vec3 WorldUp);
		//public func
		const lm::mat4 createViewMatrix();

		const lm::mat4 getViewMatrix() const;

		const lm::vec3 getPosition() const;
		const lm::vec3 getFront() const;
		lm::mat4 look_at();
		void updateMouseInput(const float& delta, const double& offsetX, const double& offsetY);
		void move(const float& delta, const int direction);
		void updateInput(const float& delta, const double& offsetX, const double& offsetY);
		//public var
	};
}
