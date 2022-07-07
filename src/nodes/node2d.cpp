#include "node2d.hpp"
#include "renderer.hpp"

namespace prim
{
    Node2D::Node2D(std::string name) : Node(name)
    {
    }

    Node2D::~Node2D()
    {
    }
    
    void Node2D::start()
    {
        Node::start();
    }
    
    void Node2D::update(float deltaTime)
    {
        Node::update(deltaTime);
    }
    
    void Node2D::draw(Renderer& renderer)
    {
        Node::draw(renderer);
    }

    void Node2D::move(glm::vec2 v)
    {
        transform.position += v;
    }

    void Node2D::rotate(float angle)
    {
        transform.rotation += angle;
    }

    void Node2D::scale(float s)
    {
        transform.scale *= glm::vec2(s);
    }

    void Node2D::scale(glm::vec2 s)
    {
        transform.scale *= s;
    }

    glm::vec2 Node2D::getPosition()
    {
        return transform.position;
    }

    float Node2D::getRotation()
    {
        return transform.rotation;
    }

    glm::vec2 Node2D::getScale()
    {
        return transform.scale;
    }

    glm::vec2 Node2D::getGlobalPosition()
    {
        if (!parent) return transform.position;
        Node2D* parent2d = dynamic_cast<Node2D*>(parent);
        if (parent2d)
        {
            return parent2d->getGlobalPosition() + transform.position;
        }
        else
        {
            return transform.position;
        }
    }

    float Node2D::getGlobalRotation()
    {
        if (!parent) return transform.rotation;
        Node2D* parent2d = dynamic_cast<Node2D*>(parent);
        if (parent2d)
        {
            return parent2d->getGlobalRotation() + transform.rotation;
        }
        else
        {
            return transform.rotation;
        }
    }

    glm::vec2 Node2D::getGlobalScale()
    {
        if (!parent) return transform.scale;
        Node2D* parent2d = dynamic_cast<Node2D*>(parent);
        if (parent2d)
        {
            return parent2d->getGlobalScale() * transform.scale;
        }
        else
        {
            return transform.scale;
        }
    }

    void Node2D::setPosition(glm::vec2 v)
    {
        transform.position = v;
    }

    void Node2D::setRotation(float angle)
    {
        transform.rotation = angle;
    }

    void Node2D::setScale(float s)
    {
        transform.scale = glm::vec2(s);
    }

    void Node2D::setScale(glm::vec2 s)
    {
        transform.scale = s;
    }

    void Node2D::setGlobalPosition(glm::vec2 v)
    {
        if (!parent) transform.position = v;
        Node2D* parent2d = dynamic_cast<Node2D*>(parent);
        if (parent2d)
        {
            transform.position = v - parent2d->getGlobalPosition();
        }
        else
        {
            transform.position = v;
        }
    }

    void Node2D::setGlobalRotation(float angle)
    {
        if (!parent) transform.rotation = angle;
        Node2D* parent2d = dynamic_cast<Node2D*>(parent);
        if (parent2d)
        {
            transform.rotation = angle - parent2d->getGlobalRotation();
        }
        else
        {
            transform.rotation = angle;
        }
    }

    void Node2D::setGlobalScale(glm::vec2 s)
    {
        if (!parent) transform.scale = s;
        Node2D* parent2d = dynamic_cast<Node2D*>(parent);
        if (parent2d)
        {
            transform.scale = s / parent2d->getGlobalScale();
        }
        else
        {
            transform.scale = s;
        }
    }
}