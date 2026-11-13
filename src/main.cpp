#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "attractors/vec3.hpp"
#include "attractors/lorenz.hpp"
#include "attractors/aizawa.hpp"
#include "attractors/rossler.hpp"
#include "attractors/halvorson.hpp"
#include "attractors/sprott-linz.hpp"
#include "attractors/chua.hpp"
#include <vector>

float jitter()
{
    return GetRandomValue(-1000, 1000) / 1000.0f * 0.5f;
}

void drawParticles(const std::vector<Vec3> &particles, const Camera3D &camera,
                   Texture2D glow, float size)
{
    // Camera-facing axes, computed once per frame (not per particle)
    Vector3 view  = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(view, camera.up));
    Vector3 up    = Vector3Normalize(Vector3CrossProduct(right, view));

    Vector3 h = Vector3Scale(right, size * 0.5f);
    Vector3 v = Vector3Scale(up,    size * 0.5f);

    rlDisableDepthMask();
    BeginBlendMode(BLEND_ADDITIVE);
    rlSetTexture(glow.id);
    rlBegin(RL_QUADS);
    rlColor4ub(135, 206, 235, 100);

    for (const Vec3 &p : particles)
    {
        rlCheckRenderBatchLimit(4);   // flushes if the batch is full

        rlTexCoord2f(0.0f, 1.0f); rlVertex3f(p.x - h.x - v.x, p.y - h.y - v.y, p.z - h.z - v.z);
        rlTexCoord2f(1.0f, 1.0f); rlVertex3f(p.x + h.x - v.x, p.y + h.y - v.y, p.z + h.z - v.z);
        rlTexCoord2f(1.0f, 0.0f); rlVertex3f(p.x + h.x + v.x, p.y + h.y + v.y, p.z + h.z + v.z);
        rlTexCoord2f(0.0f, 0.0f); rlVertex3f(p.x - h.x + v.x, p.y - h.y + v.y, p.z - h.z + v.z);
    }

    rlEnd();
    rlSetTexture(0);
    EndBlendMode();
    rlEnableDepthMask();
}

int main()
{
    const size_t MAX_PARTICLES = 10000;
    const int STEPS_PER_FRAME = 1;
    const float TIMESTEP = 0.005f;

    std::vector<unique_ptr<Attractor>> attractors;
    attractors.reserve(4);

    attractors.push_back(make_unique<Lorenz>());
    attractors.push_back(make_unique<Rossler>());
    attractors.push_back(make_unique<Aizawa>());
    attractors.push_back(make_unique<Halvorson>());
    attractors.push_back(make_unique<SprottLinz>());
    attractors.push_back(make_unique<Chua>());
    
    cout << "Successfully Loaded Chaotic Systems" <<endl;


    std::vector<Vec3> particles;
    particles.reserve(MAX_PARTICLES);

    InitWindow(1800, 1800, "Strange Attractor Sim");
    SetTargetFPS(60);
    Camera3D camera = {0};
    Image billBoardImage = GenImageGradientRadial(128, 128, 0.75f, WHITE, BLANK);
    Texture2D glow = LoadTextureFromImage(billBoardImage);
    UnloadImage(billBoardImage);
    SetTextureFilter(glow, TEXTURE_FILTER_POINT);

    auto select = [&](size_t index)
    {
        cout << "Selecting attractor at: " << index << endl;
        Attractor &a = *attractors[index];
        particles.clear();
        Vec3 updatedOrigin = a.initialState();
        Vec3 updatedCameraPosition = a.getCameraPosition();
        Vec3 updatedCameraTarget = a.getCameraTarget();
        camera.up = {0.0f, 0.0f, 1.0f};
        camera.position = {updatedCameraPosition.x, updatedCameraPosition.y, updatedCameraPosition.z};
        camera.target = {updatedCameraTarget.x, updatedCameraTarget.y, updatedCameraTarget.z};
        cout << "Cleared particle meshes, respawning now" << endl;
        for (size_t i = 0; i < MAX_PARTICLES; i++)
        {
            particles.push_back(Vec3(updatedOrigin.x + jitter(), updatedOrigin.y + jitter(), updatedOrigin.z + jitter()));
        }
        return &a;
    };

    Attractor &currentAttractor = *attractors[0];
    Vec3 origin = currentAttractor.initialState();
    Vec3 positionPreset = currentAttractor.getCameraPosition();
    Vec3 targetPreset = currentAttractor.getCameraTarget();
    camera.position = {positionPreset.x, positionPreset.y, positionPreset.z};
    camera.up = { 0.0f, 0.0f, 1.0f };
    camera.target = {targetPreset.x, targetPreset.y, targetPreset.z};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    for (size_t i = 0; i < MAX_PARTICLES; i++)
    {
        particles.push_back(Vec3(origin.x + jitter(), origin.y + jitter(), origin.z + jitter()));
    }

    size_t currentIndex = 0;

    while (!WindowShouldClose())
    {
        Attractor &currentAttractor = *attractors[currentIndex];

        // We calculate this many updates per frame

        if (IsKeyPressed(KEY_RIGHT))
        {
            currentIndex++;
            currentAttractor = *select(currentIndex);
        }
        
        for (size_t i = 0; i < STEPS_PER_FRAME; ++i)
        {
            for (Vec3 &particle : particles)
            {
                particle = currentAttractor.getNextStep(particle, TIMESTEP);
            }   
        }

        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangle(
                0, 0,
                GetScreenWidth(),
                GetScreenHeight(),
                Fade(BLACK, 0.08f)
            );

            BeginMode3D(camera);
                drawParticles(particles, camera, glow, currentAttractor.getParticleSize());
            EndMode3D();

            DrawText("Current Attractor:", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    UnloadTexture(glow);
    CloseWindow();


    return 0;
}
