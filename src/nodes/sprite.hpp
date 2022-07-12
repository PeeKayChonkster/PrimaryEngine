#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#include "node2d.hpp"
#include "mesh.hpp"
#include "image.hpp"

namespace prim
{

    enum class ImageType;

    class Sprite : public Node2D
    {
    private:
        const float defaultSize = 100.0f;
        Mesh planeMesh;
        Image image;
        float width;
        float height;
    public:
        Sprite(std::string name);
        Sprite(std::string name, std::string imagePath);
        virtual ~Sprite();

        virtual void start() override;
        virtual void update(float deltaTime) override;
        virtual void draw(Renderer& renderer) override;

        void setCenterPivot();

        void setSize(float width, float height);
        void setWidth(float width);
        void setHeight(float height);
        void setImage(std::string path);
        inline float getWidth() const { return width; }
        inline float getHeight() const { return height; }
    };

}

#endif // __SPRITE_HPP__