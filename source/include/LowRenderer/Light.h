#pragma once
#include "LibMaths/Vec4/Vec4.h"
#include "../include/Resources/Shader.h"

#include "../include/LowRenderer/Camera.h"
namespace LowRenderer
{
	class Light
	{
	public:
		lm::vec3 diffuseColor;
		lm::vec3 ambientColor;
		lm::vec3 specularColor;
		~Light() = default;
	};

	class PointLight : Light
	{
		lm::vec3 position;
		int nbrLight;
		float constant;
		float linear;
		float quadratic;
	public:
		PointLight(int nbrLight, lm::vec3 position, lm::vec3 diffuseColor = lm::vec3(1.f), lm::vec3 ambientColor = lm::vec3(1.f),
			lm::vec3 specularColor = lm::vec3(1.f), float constant = 1.f, float linear = 0.045f, float quadratic = 0.0075f);

		void sendToShader(Resources::Shader* shader);
	};
	class DirectionLight : Light
	{
		lm::vec3 direction;
	public:
		DirectionLight(lm::vec3 direction, lm::vec3 diffuseColor = lm::vec3(1.f), lm::vec3 ambientColor = lm::vec3(1.f),
			lm::vec3 specularColor = lm::vec3(1.f));
		void sendToShader(Resources::Shader* shader);
	};

	class SpotLight : Light
	{
		lm::vec3 position;
		lm::vec3 direction;
		int nbrLight;
		float constant;
		float linear;
		float quadratic;
		float cutOff;
		float outerCutOff;
	public:
		SpotLight(lm::vec3 position, lm::vec3 direction, lm::vec3 diffuseColor = lm::vec3(1.f), lm::vec3 ambientColor = lm::vec3(1.f),
			lm::vec3 specularColor = lm::vec3(1.f), float constant = 1.f, float linear = 0.045f, float quadratic = 0.0075f, float cutOff = 12.5f, float outerCutOff = 15.0f);

		void updateVec(Camera& cam);

		void sendToShader(Resources::Shader* shader);
	};
}
