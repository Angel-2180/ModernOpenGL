#pragma once
#include "../include/Resources/Model.h"
#include "../maths/LibMaths/Vec3/Vec3.h"
#include "../include/LowRenderer/Camera.h"
#include "../include/Resources/Texture.h"
namespace LowRenderer
{
	class Mesh
	{
	private:
		lm::Vec3<float> postion;
		lm::Vec3<float> rotation;
		lm::Vec3<float> scale;

	public:
		Mesh(Resources::Model* model,
			lm::Vec3<float> position = lm::Vec3(0.f),
			lm::Vec3<float> rotation = lm::Vec3(0.f),
			lm::Vec3<float> scale = lm::Vec3(1.f),
			Resources::Texture* texture = nullptr);
		lm::Mat4<float> modelMat;
		lm::Mat4<float> projectionMat;
		lm::Mat4<float> viewMat;
		lm::Mat4<float> mvp;

		void updateModelMatrix();
		void updateUniform(Resources::Shader* shader, Camera& cam);
		lm::mat4 calculateMVP(lm::Mat4<float> view);
		Resources::Model* model;
		Resources::Texture* texture = nullptr;
	};
}
