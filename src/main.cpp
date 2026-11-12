#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "attractors/vec3.hpp"
#include "attractors/lorenz.hpp"
#include <vector>

int main()
{
    InitWindow(1280, 720, "Strange Attractors");
    SetTargetFPS(60);

    Lorenz attractor;

    // Spawn a small cloud around the initial state
    const int PARTICLE_COUNT = 2000;
    std::vector<Vec3> particles;
    particles.reserve(PARTICLE_COUNT);

    Vec3 origin = attractor.initialState();
    for (int i = 0; i < PARTICLE_COUNT; i++)
    {
        // GetRandomValue returns ints, so scale to a small float offset
        auto jitter = []() { return GetRandomValue(-1000, 1000) / 1000.0f * 0.5f; };
        particles.push_back(Vec3(origin.x + jitter(), origin.y + jitter(), origin.z + jitter()));
    }

    Camera3D camera = {};
    camera.position = { 50.0f, 50.0f, 40.0f };
    camera.target   = { 0.0f, 0.0f, 25.0f };
    camera.up       = { 0.0f, 0.0f, 1.0f };
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    const float dt = 0.0025f;
    const int stepsPerFrame = 3;
    const float particleSize = 1.0f;

    Image img = GenImageGradientRadial(64, 64, 0.5f, WHITE, BLANK);
    Texture2D glow = LoadTextureFromImage(img);
    UnloadImage(img);
    SetTextureFilter(glow, TEXTURE_FILTER_BILINEAR);

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        for (int s = 0; s < stepsPerFrame; s++)
            for (Vec3 &p : particles)
                p = attractor.getNextStep(p, dt);

        BeginDrawing();
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();
        const Color backgroundTop = { 7, 12, 32, 255 };
        const Color backgroundBottom = { 1, 2, 9, 255 };
        ClearBackground(backgroundBottom);
        DrawRectangleGradientV(0, 0, screenWidth, screenHeight,
                               backgroundTop, backgroundBottom);
        DrawCircleGradient({ screenWidth / 2.0f, screenHeight / 2.0f }, screenHeight * 0.7f,
                           Color{ 13, 22, 56, 90 }, Color{ 1, 2, 9, 0 });

        BeginMode3D(camera);
        Vector3 viewDirection = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
        Vector3 billboardRight = Vector3Normalize(Vector3CrossProduct(viewDirection, camera.up));
        Vector3 billboardUp = Vector3Normalize(Vector3CrossProduct(billboardRight, viewDirection));

        rlDisableDepthTest();
        rlDisableDepthMask();
        BeginBlendMode(BLEND_ADDITIVE);
        rlSetTexture(glow.id);
        rlBegin(RL_QUADS);
        rlColor4ub(SKYBLUE.r, SKYBLUE.g, SKYBLUE.b, 220);
        for (const Vec3 &p : particles)
        {
            Vector3 center = { p.x, p.y, p.z };
            Vector3 horizontal = Vector3Scale(billboardRight, particleSize * 0.5f);
            Vector3 vertical = Vector3Scale(billboardUp, particleSize * 0.5f);

            rlTexCoord2f(0.0f, 1.0f);
            rlVertex3f(center.x - horizontal.x - vertical.x,
                       center.y - horizontal.y - vertical.y,
                       center.z - horizontal.z - vertical.z);
            rlTexCoord2f(1.0f, 1.0f);
            rlVertex3f(center.x + horizontal.x - vertical.x,
                       center.y + horizontal.y - vertical.y,
                       center.z + horizontal.z - vertical.z);
            rlTexCoord2f(1.0f, 0.0f);
            rlVertex3f(center.x + horizontal.x + vertical.x,
                       center.y + horizontal.y + vertical.y,
                       center.z + horizontal.z + vertical.z);
            rlTexCoord2f(0.0f, 0.0f);
            rlVertex3f(center.x - horizontal.x + vertical.x,
                       center.y - horizontal.y + vertical.y,
                       center.z - horizontal.z + vertical.z);
        }
        rlEnd();
        rlSetTexture(0);
        EndBlendMode();
        rlEnableDepthMask();
        rlEnableDepthTest();
        EndMode3D();

        if (GetTime() < 5.0 && (int)(GetFrameTime() * 1000) % 10 == 0)
            TraceLog(LOG_INFO, "p0 = %f %f %f", particles[0].x, particles[0].y, particles[0].z);

        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(glow);
    CloseWindow();
    return 0;
}
