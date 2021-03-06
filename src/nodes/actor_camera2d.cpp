#include "actor_camera2d.hpp"
#include "gtx/rotate_vector.hpp"
#include "utils.hpp"
#include "globals.hpp"
#include "node_utils.hpp"

namespace prim
{
    ActorCamera2D::ActorCamera2D(std::string name, const NodePath& target)
        : ActorCamera2D(name, -1.0f, 1.0f, target)
    {
    }

    ActorCamera2D::ActorCamera2D(std::string name, float zNear, float zFar, const NodePath& target)
        : Camera2D(name, zNear, zFar), targetPath(target)
    {
    }
    
    ActorCamera2D::ActorCamera2D(std::unordered_map<std::string, std::string>& fieldValues) 
        : Camera2D(fieldValues), stiffness(std::stof(fieldValues[NodeFields::stiffness])),
        targetPath(fieldValues[NodeFields::targetPath])
    {
    }

    ActorCamera2D::~ActorCamera2D()
    {
    }

    void ActorCamera2D::start()
    {
        START_CHILDREN

        target = dynamic_cast<Node2D*>(Globals::app->getNode(targetPath));
        initialOffset = getGlobalPosition() - target->getGlobalPosition();
        //setAsCurrent();
    }

    void ActorCamera2D::update(float deltaTime)
    {
        UPDATE_CHILDREN

            auto followTargetFunction = [this]() {
            glm::vec2 position;
            if (rotateWithTarget)
            {
                float targetAngle = target->getGlobalRotation();
                position = glm::mix(getGlobalPosition(), target->getGlobalPosition() + glm::rotate(initialOffset, targetAngle), stiffness);
                setGlobalRotation(Utils::lerpAngle(getGlobalRotation(), targetAngle, stiffness));
            }
            else
                position = glm::mix(getGlobalPosition(), target->getGlobalPosition() + initialOffset, stiffness);

            setGlobalPosition(position);
        };

        Globals::app->deferFunctionExecution(followTargetFunction);
    }

    void ActorCamera2D::draw(Renderer& renderer)
    {
        DRAW_CHILDREN
    }

    void ActorCamera2D::setTarget(const NodePath& target)
    {
        targetPath = target;
        this->target = dynamic_cast<Node2D*>(Globals::app->getNode(targetPath));
    }

    void ActorCamera2D::setStiffness(float value)
    {
        stiffness = Utils::clamp(value, 0.0f, 1.0f);
    }

    std::string ActorCamera2D::serialize() const
    {
        std::stringstream ss;
        ss << createKeyValuePair(NodeFields::type, getNodeTypeName<ActorCamera2D>()) << std::endl;
        ss << createKeyValuePair(NodeFields::name, name) << std::endl;
        ss << createKeyValuePair(NodeFields::position, serializeVec2(getPosition())) << std::endl;
        ss << createKeyValuePair(NodeFields::rotation, std::to_string(getRotation())) << std::endl;
        ss << createKeyValuePair(NodeFields::scale, serializeVec2(getScale())) << std::endl;
        ss << createKeyValuePair(NodeFields::pivot, serializeVec2(getPivot())) << std::endl;
        ss << createKeyValuePair(NodeFields::zNear, std::to_string(zNear)) << std::endl;
        ss << createKeyValuePair(NodeFields::zFar, std::to_string(zFar)) << std::endl;
        ss << createKeyValuePair(NodeFields::zoom, std::to_string(zoom)) << std::endl;
        ss << createKeyValuePair(NodeFields::targetPath, targetPath.string()) << std::endl;
        ss << createKeyValuePair(NodeFields::initialOffset, serializeVec2(initialOffset)) << std::endl;
        ss << createKeyValuePair(NodeFields::stiffness, std::to_string(stiffness)) << std::endl;
        ss << createKeyValuePair(NodeFields::rotateWithTarget, std::to_string((int)rotateWithTarget)) << std::endl;
        ss << NodeFields::childrenStart << std::endl;
        for (Node* child : children)
            ss << child->serialize() << std::endl;
        ss << NodeFields::childrenEnd << std::endl;
        return ss.str();
    }
}