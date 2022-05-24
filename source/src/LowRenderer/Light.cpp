#include "../include/LowRenderer/Light.h"

void LowRenderer::SpotLight::sendToShader(Resources::Shader* shader)
{
	shader->setVec3f("spotLight.position", this->position);
	shader->setVec3f("spotLight.direction", this->direction);
	shader->setVec3f("spotLight.ambient", this->ambientColor);
	shader->setVec3f("spotLight.diffuse", this->diffuseColor);
	shader->setVec3f("spotLight.specular", this->specularColor);
	shader->setFloat("spotLight.constant", this->constant);
	shader->setFloat("spotLight.linear", this->linear);
	shader->setFloat("spotLight.quadratic", this->quadratic);
	shader->setFloat("spotLight.cutOff", static_cast<float>(cos(degreesToRadians(this->cutOff))));
	shader->setFloat("spotLight.outerCutOff", static_cast<float>(cos(degreesToRadians(this->outerCutOff))));
}

LowRenderer::SpotLight::SpotLight(lm::vec3 position, lm::vec3 direction, lm::vec3 diffuseColor, lm::vec3 ambientColor,
	lm::vec3 specularColor, float constant, float linear, float quadratic, float cutOff, float outerCutOff)

{
	this->position = position;
	this->direction = direction;
	this->diffuseColor = diffuseColor;
	this->ambientColor = ambientColor;
	this->specularColor = specularColor;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}

void LowRenderer::SpotLight::updateVec(Camera& cam)
{
	this->position = cam.getPosition();
	this->direction = cam.getFront();
}

LowRenderer::PointLight::PointLight(int nbrLight, lm::vec3 position, lm::vec3 diffuseColor, lm::vec3 ambientColor,
	lm::vec3 specularColor, float constant, float linear, float quadratic)

{
	this->nbrLight = nbrLight;
	this->diffuseColor = diffuseColor;
	this->ambientColor = ambientColor;
	this->specularColor = specularColor;
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void LowRenderer::PointLight::sendToShader(Resources::Shader* shader)
{
	// point light 1
	std::string str = "pointLights[" + std::to_string(this->nbrLight) + "]";
	std::string temp = str;
	shader->setVec3f((str.append(".position")).c_str(), this->position);
	str = temp;
	shader->setVec3f((str.append(".ambient")).c_str(), this->ambientColor);
	str = temp;
	shader->setVec3f((str.append(".diffuse")).c_str(), this->diffuseColor);
	str = temp;
	shader->setVec3f((str.append(".specular")).c_str(), this->specularColor);
	str = temp;
	shader->setFloat(str.append(".constant"), this->constant);
	str = temp;
	shader->setFloat(str.append(".linear"), this->linear);
	str = temp;
	shader->setFloat(str.append(".quadratic"), this->quadratic);
}

LowRenderer::DirectionLight::DirectionLight(lm::vec3 direction, lm::vec3 diffuseColor, lm::vec3 ambientColor,
	lm::vec3 specularColor)
{
	this->direction = direction;
	this->ambientColor = ambientColor;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
}

void LowRenderer::DirectionLight::sendToShader(Resources::Shader* shader)
{
	shader->setVec3f("dirLight.direction", this->direction);
	shader->setVec3f("dirLight.ambient", this->ambientColor);
	shader->setVec3f("dirLight.diffuse", this->diffuseColor);
	shader->setVec3f("dirLight.specular", this->specularColor);
}