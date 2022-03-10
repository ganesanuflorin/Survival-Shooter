#include "lab_m1/Tema1/tema1.h"

#include <vector>
#include <iostream>
#include <time.h>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema1::tema1()
{
}


tema1::~tema1()
{
}


void tema1::Init()
{
#if 1
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
#endif

    obstacles.push_back(Wall(-97.f, -78.f, 194.f, 1.f));
    obstacles.push_back(Wall(-97.f, 77.f, 194.f, 1.f));
    obstacles.push_back(Wall(-97.f, -78.f, 1.f, 156.f));
    obstacles.push_back(Wall( 97.f, -78.f, 1.f, 156.f));
    obstacles.push_back(Wall( 17.5f, 17.5f, 10.f, 5.f));
    obstacles.push_back(Wall(-3.f, 2.5f, 8.f, 8.f));
    obstacles.push_back(Wall(-2.5f, -5.f, 9.f, 9.f));
    obstacles.push_back(Wall( 20.f, 22.f, 13.f, 16.f));
    obstacles.push_back(Wall(-30.f, -33.f, 15.f, 5.f));
    obstacles.push_back(Wall(-30.f, -33.f, 5.f, 15.f));
    obstacles.push_back(Wall(-67.f, -33.f, 15.f, 15.f));
    obstacles.push_back(Wall( 50.f, -33.f, 12.f, 25.f));
    obstacles.push_back(Wall( 70.f, 60.f, 7.f, 13.f));
    obstacles.push_back(Wall( 40.f, -50.f, 12.f, 5.f));
    obstacles.push_back(Wall( 50.f, -33.f, 16.f, 6.f));
    obstacles.push_back(Wall( 55.f, -60.f, 4.f, 9.f));
    
    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 60;   // logic width
    logicSpace.height = 30;  // logic height

    //circleX = logicSpace.width / 2;
   // circleY = logicSpace.height / 2;

    bodyEnemySide = 4.f;
    handEnemySide = 1.f;
   
    score = 0;
    healthBarLength = 10.f;
    healthBarHeigth = 2.5f;
        
    side1 = 1.f;

    radius = 2.5f;
    radius1 = 1.f;

    length = 200.f;
    width = 160.f;

    length2 = 1.f;
    width2 = 1.f;

    borderLengthO = 194.f;
    borderWidthO = 1.f;

    borderLengthV = 1.f;
    borderWidthV = 154.f;

    // Initialize tx and ty (the translation steps)
    translateX = logicSpace.width / 2;
    translateY = logicSpace.height / 2;

    
    bulletX = 0;
    bulletY = 0;

    srand(time(NULL));
    float r = rand() % 75;

    enemyX = r;
    enemyY = r;

    Mesh* bodyEnemy = object2D::CreateRectangle(
        "bodyEnemy", glm::vec3(0 , 0, 0), bodyEnemySide, bodyEnemySide, glm::vec3(0.5f, 0.14f, 0.20f), true);

    AddMeshToList(bodyEnemy);

    Mesh* handEnemy = object2D::CreateRectangle(
        "handEnemy", glm::vec3(0 , 0 , 0), handEnemySide, handEnemySide, glm::vec3(0.5f, 0.14f, 0.20f), true);

    AddMeshToList(handEnemy);

    Mesh* healthBar = object2D::CreateRectangle(
        "healthBar", glm::vec3(0, 0, 0), length2, healthBarHeigth, glm::vec3(1.f, 0.f, 0.f), true);

    AddMeshToList(healthBar);

    Mesh* healthBar1 = object2D::CreateRectangle(
        "healthBar1", glm::vec3(0, 0, 0), healthBarLength, healthBarHeigth, glm::vec3(0.1f, 0.1f, 0.1f), false);

    AddMeshToList(healthBar1);

    Mesh* bullet = object2D::CreateRectangle(
        "bullet", glm::vec3(-side1 / 2, -side1 / 2, 0), side1, side1, glm::vec3(0.1f, 0.1f, 0.1f), true);

    AddMeshToList(bullet);

    // Center in (0, 0, 0)
    Mesh* rectangle1 = object2D::CreateRectangle(
        "rectangle1", glm::vec3(-length / 2, -width / 2, 0), length, width, glm::vec3(0.65f, 0.45f, 0.19f), true);

    AddMeshToList(rectangle1);

    Mesh* rectangle3 = object2D::CreateRectangle(
        "rectangle3", glm::vec3(0, 0, 0), length2, width2, glm::vec3(0.2f, 0.4f, 0.12f), true);

    AddMeshToList(rectangle3);

    // Center in (0, 0, 0)
    Mesh* circle = object2D::CreateCircle(
        "circle", glm::vec3(0, 0, 0), radius, glm::vec3(0.41f, 0.85f, 0.85f), true);

    AddMeshToList(circle);

    // Center in (0, 0, 0)
    Mesh* hand = object2D::CreateCircle(
        "hand", glm::vec3(0, 0, 0), radius1, glm::vec3(0.9f, 0.94f, 0.07f), true);

    AddMeshToList(hand);

}

bool CheckCollision(float obsX, float obsY, float obsW, float obsH, float bullX, float bullY, float bullS1, float bullS2) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = obsX + obsW >= bullX &&
        bullX + bullS1 >= obsX;
    // collision y-axis?
    bool collisionY = obsY + obsH >= bullY &&
        bullY + bullS2 >= obsY;
    // collision only if on both axes
    return collisionX && collisionY;
}

// 2D visualization matrix
glm::mat3 tema1::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}

// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema1::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();

#if 1

    
    // Sets the screen area where to draw
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    // Compute the 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    DrawScene(visMatrix, deltaTimeSeconds);
    
#endif

    //LogicSpace logic_space = LogicSpace(2, 2, 3, 3);
    /*ViewportSpace view_space = ViewportSpace(0, 0, resolution.x / 5, resolution.y / 5);
    SetViewportArea(view_space, glm::vec3(0), true);
    vis_matrix = glm::mat3(1);
    vis_matrix *= VisualizationTransf2D(logicSpace, view_space);

   DrawScene(vis_matrix, deltaTimeSeconds);*/

}

void tema1::DrawScene(glm::mat3 vis_matrix, float deltaTimeSeconds)
{   
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(15, 14);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes["healthBar1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix; 
    modelMatrix *= transform2D::Translate(15, 14);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Scale(healthBarLength, width2);
    if (healthBarLength >= 0) 
    {
        RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], modelMatrix);
    }
    

    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].x < translateX) 
        {
            enemies[i].x += deltaTimeSeconds * enemies[i].speed;
        }
        else
        {
            enemies[i].x -= deltaTimeSeconds * enemies[i].speed;
        }

        if (enemies[i].y < translateY)
        {
            enemies[i].y += deltaTimeSeconds * enemies[i].speed;
        }
        else
        {
            enemies[i].y -= deltaTimeSeconds * enemies[i].speed;
        }
    }

    if (count == 3) 
    {
        enemies.push_back(Enemy(enemyX, enemyY, enemySpeed, 1));
        enemySpeed = 1 + rand() % 9;
        enemyX = -75 + rand() % 150;
        enemyY = -75 + rand() % 150;
    }
    
    count -= deltaTimeSeconds;
    if (count <= 0) 
    {
        count = 3;
    }

    int aux = 0;
 
    for (Enemy e : enemies) {

        oldEX = e.x;
        oldEY = e.y;

        if(CheckCollision(e.x, e.y, bodyEnemySide, bodyEnemySide, translateX - radius, translateY - radius, 2 * radius, 2 * radius))
        {
            e.life = 0;
            healthBarLength--;
        }

        

        if (e.life == 1) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(e.x, e.y);
            modelMatrix *= transform2D::Translate(bodyEnemySide - 1.5f, -bodyEnemySide + 3.f);
            RenderMesh2D(meshes["handEnemy"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(e.x, e.y);
            modelMatrix *= transform2D::Translate(-bodyEnemySide + 4.5f, -bodyEnemySide + 3.f);
            RenderMesh2D(meshes["handEnemy"], shaders["VertexColor"], modelMatrix);

            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(e.x, e.y);
            RenderMesh2D(meshes["bodyEnemy"], shaders["VertexColor"], modelMatrix);
        } 
        else
        {
            enemies.erase(enemies.begin() + aux);
        }

        aux++;

        if (CheckCollision(e.x, e.y, bodyEnemySide, bodyEnemySide, -97.f, -78.f, 194.f, 1.f) ||
            CheckCollision(e.x, e.y, bodyEnemySide, bodyEnemySide, -97.f, 77.f, 194.f, 1.f) ||
            CheckCollision(e.x, e.y, bodyEnemySide, bodyEnemySide, -97.f, -78.f, 1.f, 156.f) ||
            CheckCollision(e.x, e.y, bodyEnemySide, bodyEnemySide, 97.f, -78.f, 1.f, 156.f))
        {
            e.x = oldEX;
            e.y = oldEY;
        }
    }

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(mouseAngle + M_PI / 2);
    modelMatrix *= transform2D::Translate(radius * glm::cos(5 * M_PI / 4), radius * glm::sin(5 * M_PI / 4));
    RenderMesh2D(meshes["hand"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(mouseAngle + M_PI / 2);
    modelMatrix *= transform2D::Translate(radius * glm::cos(7 * M_PI / 4), radius * glm::sin(7 * M_PI / 4));
    RenderMesh2D(meshes["hand"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(mouseAngle + M_PI / 2);
    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);


    load -= deltaTimeSeconds;

    if (mouseBullet)
    {
        for (int i = 0; i < bullets.size(); i++)
        {

            for (int j = 0; j < obstacles.size(); j++) 
            {
                if (CheckCollision(obstacles[j].x, obstacles[j].y, obstacles[j].width, obstacles[j].heigth, bullets[i].x, bullets[i].y, side1, side1))
                {
                    bullets[i].life = 0;
                }
            }
            for (int j = 0; j < enemies.size(); j++)
            {
                if (CheckCollision(enemies[j].x, enemies[j].y, bodyEnemySide, bodyEnemySide, bullets[i].x, bullets[i].y, side1, side1))
                {
                    bullets[i].life = 0;
                    enemies[j].life = 0;
                    score++;
                    cout << "Score = " << score << endl;
                    if (score == 15) {
                        cout << "Felicitari! Ati terminat jocul!" << endl;
                        window->Close();
                    }
                }
            }
            if (abs(bullets[i].x - initPointX) >= 8 || abs(bullets[i].y - initPointY) >= 8 && (bullets[i].life == 1 ))
            {   
                bullets[i].life = 0;
            }
            modelMatrix = visMatrix;
            bullets[i].x += 10 * deltaTimeSeconds * cos(bullets[i].angle);
            bullets[i].y += 10 * deltaTimeSeconds * sin(bullets[i].angle);
            modelMatrix *= transform2D::Translate(bullets[i].x, bullets[i].y);
            if (bullets[i].life == 1)
            {
                RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
            }
            else {
                bullets.erase(bullets.begin() + i);
            }
        }
    }

    for (Wall w : obstacles) 
    {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(w.x, w.y);
        modelMatrix *= transform2D::Scale(w.width, w.heigth);
        RenderMesh2D(meshes["rectangle3"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = visMatrix;
    RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);
}


void tema1::FrameEnd()
{
#if 0
    DrawCoordinateSystem();
#endif
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema1::OnInputUpdate(float deltaTime, int mods)
{
    oldX = translateX;
    oldY = translateY;
    oldxLogic = logicSpace.x;
    oldyLogic = logicSpace.y;

    if (window->KeyHold(GLFW_KEY_W))
    {
        logicSpace.y += 10 * deltaTime;
        translateY += 10 * deltaTime;
        
    }

    if (window->KeyHold(GLFW_KEY_S))
    {
        logicSpace.y -= 10 * deltaTime;
        translateY -= 10 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_D))
    {
        logicSpace.x += 10 * deltaTime;
        translateX += 10 * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_A))
    {
        logicSpace.x -= 10 * deltaTime;
        translateX -= 10 * deltaTime;
    }
   
    if (window->KeyHold(GLFW_KEY_Z)) {
        logicSpace.width -= 10 * deltaTime;
        logicSpace.height -= 10 * deltaTime;
    }
    else if (window->KeyHold(GLFW_KEY_X)) {
        logicSpace.width += 10 * deltaTime;
        logicSpace.height += 10 * deltaTime;
    }


    for (int i = 0; i < obstacles.size(); i++)
    {
        if (CheckCollision(obstacles[i].x, obstacles[i].y, obstacles[i].width, obstacles[i].heigth, translateX - radius, translateY - radius, 2 * radius, 2 * radius))
        {
            translateX = oldX;
            translateY = oldY;
            logicSpace.x = oldxLogic;
            logicSpace.y = oldyLogic;
        }
    }
}


void tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float radiusMouse = atan2(viewSpace.height / 2 - mouseY, mouseX - viewSpace.width / 2);
    mouseAngle = radiusMouse;
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

    float radiusMouse1 = atan2(viewSpace.height / 2 - mouseY, mouseX - viewSpace.width / 2);
    mouseAngle1 = radiusMouse1;
    initPointX = translateX  + (radius + 0.7f) * cos(mouseAngle1);
    initPointY = translateY  + (radius + 0.7f) * sin(mouseAngle1);  

   if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT))
   {    
       if (load <= 0) {
           bullets.push_back(Bullet(initPointX, initPointY, mouseAngle1, 1));
           mouseBullet = true;
           load = 0.5f;
       } 
   }
}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema1::OnWindowResize(int width, int height)
{
}