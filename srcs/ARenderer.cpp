#include "ARenderer.hpp"

ARenderer::ARenderer(std::shared_ptr<GameObject> obj) : AComponent(obj), _shader(nullptr) {}
ARenderer::ARenderer(std::shared_ptr<GameObject> obj, std::shared_ptr<Shader>  shader) : AComponent(obj), _shader(shader) {}
ARenderer::ARenderer(std::shared_ptr<GameObject> obj, std::shared_ptr<Shader>  shader, Transform trans) : AComponent(obj), _shader(shader) 
{
    transform = trans;
    UpdateMatrix();
}

void    ARenderer::UpdateMatrix()
{
    _modelMatrix = glm::mat4(1.0f);
    _modelMatrix = glm::translate(_modelMatrix, transform.position);
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    _modelMatrix = glm::rotate(_modelMatrix, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    _modelMatrix = glm::scale(_modelMatrix, transform.scale);
};

glm::mat4       ARenderer::GetModelMatrix(void) const  {return _modelMatrix;}
void            ARenderer::SetModelMatrix(glm::mat4 matrix) {_modelMatrix = matrix;}
std::shared_ptr<Shader> ARenderer::GetShader(void) const { return _shader;}
void                    ARenderer::SetShader(std::shared_ptr<Shader>  shader) {_shader = shader;}