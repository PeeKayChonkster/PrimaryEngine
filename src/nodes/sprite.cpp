#include "sprite.hpp"
#include "primitives.hpp"
#include "renderer.hpp"
#include "gtc/matrix_transform.hpp"

namespace prim
{
    Sprite::Sprite(std::string name) : Node2D(name), planeMesh(Primitives::createSquareMesh())
    {
    }
    
    Sprite::Sprite(std::string name, std::string imagePath) : Node2D(name), planeMesh(Primitives::createSquareMesh(imagePath))
    {
    }
    
    Sprite::~Sprite()
    {
    }
    
    void Sprite::start()
    {
        Node2D::start();
    }
    
    void Sprite::update(float deltaTime)
    {
        Node2D::update(deltaTime);
    }
    
    void Sprite::draw(Renderer& renderer)
    {
        Node2D::draw(renderer);

        glm::vec2 globalPos = getGlobalPosition();
        glm::vec2 globalScale = getGlobalScale();
        glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), glm::vec3(globalPos.x, globalPos.y, 0.0f));
        modelMat = glm::rotate(modelMat, getGlobalRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMat = glm::scale(modelMat, glm::vec3(globalScale.x, globalScale.y, 1.0f));

        renderer.setModelMat(std::move(modelMat));

        renderer.drawMesh(planeMesh);
    }
}