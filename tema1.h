#pragma once

#include "components/simple_scene.h"




namespace m1
{
    class tema1 : public gfxc::SimpleScene
    {
    public:

        struct Enemy
        {
            Enemy() : x(0), y(0), speed(0), life(0) {}
            Enemy(float x, float y, float speed, float life)
                :x(x), y(y), speed(speed), life(life) {}
            float x;
            float y;
            float speed;
            float life;
        };

        struct Wall
        {
            Wall() : x(0), y(0), width(0), heigth(0) {}
            Wall(float x, float y, float width, float heigth)
                :x(x), y(y), width(width), heigth(heigth) {}
            float x;
            float y;
            float width;
            float heigth;
        };

        struct Bullet
        {
            Bullet(): x(0), y(0), angle(0), life(0) {}
            Bullet(float x, float y, float angle, float life)
                :x(x), y(y), angle(angle), life(life){}
            float x;
            float y;
            float angle;
            float life;
        };

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        tema1();
        ~tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 vis_matrix, float deltaTimeSeconds);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        
       // bool CheckCollision(float obsX, float obsY, float obsW, float obsH, float bullX, float bullY, float bullS1, float bullS2);

        glm::mat3 tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float bulletX, bulletY;
        //float initBulletX, initBulletY;
        float initPointX, initPointY;
        bool mouseBullet = false;
        double radius;
        double radius1;
        float healthBarLength, healthBarHeigth;
        float enemyX, enemyY, enemySpeed;
        float load = 0.5f;
        float count = 0;
        float score;
        float oldEX, oldEY;
        float bodyEnemySide, handEnemySide;
        float side, side1;
        float oldX, oldY, oldxLogic, oldyLogic;
        float length, borderLengthO, borderLengthV, length2;
        float width, borderWidthO, borderWidthV, width2;
        float squareSide = 100.f;
        float mouseAngle = 5 * M_PI / 2;
        float mouseAngle1 = 5 * M_PI / 2;
        float circleX, circleY;
        std::vector<Bullet> bullets;
        std::vector<Wall> obstacles;
        std::vector<Enemy> enemies;

        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 vis_matrix;
        glm::mat3 visMatrix;

    };
}   // namespace m1
