#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "attractors/vec3.hpp"
#include "attractors/lorenz.hpp"
#include "attractors/aizawa.hpp"
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
    BeginBlendMode(BLEND_ALPHA);
    rlSetTexture(glow.id);
    rlBegin(RL_QUADS);
    rlColor4ub(135, 206, 235, 60);

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

    InitWindow(1800, 1800, "Strange Attractor Sim");
    SetTargetFPS(60);

    Image billBoardImage = GenImageGradientRadial(128, 128, 0.0f, WHITE, BLANK);
    Texture2D glow = LoadTextureFromImage(billBoardImage);
    UnloadImage(billBoardImage);
    GenTextureMipmaps(&glow);
    SetTextureFilter(glow, TEXTURE_FILTER_TRILINEAR);

    Aizawa currentAttractor;

    Vec3 origin = currentAttractor.initialState();

    std::vector<Vec3> particles;
    particles.reserve(MAX_PARTICLES);

    for (size_t i = 0; i < MAX_PARTICLES; i++)
    {
        particles.push_back(Vec3(origin.x + jitter(), origin.y + jitter(), origin.z + jitter()));
    }

    
    Vec3 positionPreset = currentAttractor.getCameraPosition();
    Vec3 targetPreset = currentAttractor.getCameraTarget();

    Camera3D camera = {0};
    camera.position = {positionPreset.x, positionPreset.y, positionPreset.z};
    camera.up = { 0.0f, 0.0f, 1.0f };
    camera.target = {targetPreset.x, targetPreset.y, targetPreset.z};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;



    while (!WindowShouldClose())
    {

        // We calculate this many updates per frame
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

        DrawText(TextFormat("n=%d  p0=%.2f %.2f %.2f", (int)particles.size(),
                particles[0].x, particles[0].y, particles[0].z), 10, 40, 20, WHITE);

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
