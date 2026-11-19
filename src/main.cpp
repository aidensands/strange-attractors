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
#include "attractors/thomas.hpp"
#include "attractors/chenlee.hpp"
#include "attractors/arneodo.hpp"
#include <vector>

using namespace std;

const size_t MAX_PARTICLES = 10000;
const size_t TRAIL_LENGTH = 24;
const size_t TRAIL_PARTICLE_STRIDE = 4;
const int STEPS_PER_FRAME = 1;
const float TIMESTEP = 0.005f;

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

void drawTrails(const std::vector<Vec3> &trailHistory, size_t trailHead,
                size_t trailCount)
{
    if (trailCount < 2)
    {
        return;
    }

    const size_t oldestSlot = (trailHead + TRAIL_LENGTH - trailCount) % TRAIL_LENGTH;

    rlDisableDepthMask();
    BeginBlendMode(BLEND_ALPHA);
    rlSetTexture(0);
    rlBegin(RL_LINES);

    for (size_t particleIndex = 0; particleIndex < MAX_PARTICLES;
         particleIndex += TRAIL_PARTICLE_STRIDE)
    {
        const size_t particleOffset = particleIndex * TRAIL_LENGTH;

        for (size_t age = 0; age + 1 < trailCount; ++age)
        {
            const size_t firstSlot = (oldestSlot + age) % TRAIL_LENGTH;
            const size_t secondSlot = (oldestSlot + age + 1) % TRAIL_LENGTH;
            const Vec3 &first = trailHistory[particleOffset + firstSlot];
            const Vec3 &second = trailHistory[particleOffset + secondSlot];
            const unsigned char alpha = static_cast<unsigned char>(
                20 + (100 * (age + 1)) / (trailCount - 1));

            rlCheckRenderBatchLimit(2);
            rlColor4ub(135, 206, 235, alpha);
            rlVertex3f(first.x, first.y, first.z);
            rlVertex3f(second.x, second.y, second.z);
        }
    }

    rlEnd();
    EndBlendMode();
    rlEnableDepthMask();
}

void resetTrails(const std::vector<Vec3> &particles,
                 std::vector<Vec3> &trailHistory,
                 size_t &trailHead, size_t &trailCount)
{
    for (size_t particleIndex = 0; particleIndex < particles.size(); ++particleIndex)
    {
        const size_t particleOffset = particleIndex * TRAIL_LENGTH;
        for (size_t slot = 0; slot < TRAIL_LENGTH; ++slot)
        {
            trailHistory[particleOffset + slot] = particles[particleIndex];
        }
    }

    trailHead = 0;
    trailCount = 1;
}

void reset_particles(vector<Vec3> &particles, Vec3 origin)
{
    particles.clear();
    for (size_t i = 0; i < MAX_PARTICLES; ++i)
    {
        particles.push_back(Vec3(origin.x + jitter(), origin.y + jitter(), origin.z + jitter()));
    }
    cout << "Manual particle clear and respawn done" << endl;
}

int main()
{

    // Setup for loading parameters

    std::vector<unique_ptr<Attractor>> attractors;
    attractors.reserve(12); 
    attractors.push_back(make_unique<Lorenz>());
    attractors.push_back(make_unique<Rossler>());
    attractors.push_back(make_unique<Aizawa>());
    attractors.push_back(make_unique<Halvorson>());
    attractors.push_back(make_unique<SprottLinz>());
    attractors.push_back(make_unique<Chua>());
    attractors.push_back(make_unique<Thomas>());
    attractors.push_back(make_unique<Chenlee>());
    attractors.push_back(make_unique<Arneodo>());
    
    cout << "Successfully Loaded Chaotic Systems" <<endl;


    std::vector<Vec3> particles;
    particles.reserve(MAX_PARTICLES);
    std::vector<Vec3> trailHistory(MAX_PARTICLES * TRAIL_LENGTH);
    size_t trailHead = 0;
    size_t trailCount = 0;
    bool trailsEnabled = true;
    
    InitWindow(1200, 800, "Strange Attractor Sim");
    SetTargetFPS(60);
    ToggleFullscreen();
    Camera3D camera = {0};
    Image billBoardImage = GenImageGradientRadial(128, 128, 0.75f, WHITE, BLANK);
    Texture2D glow = LoadTextureFromImage(billBoardImage);
    UnloadImage(billBoardImage);
    SetTextureFilter(glow, TEXTURE_FILTER_POINT);

    auto select = [&](size_t index)
    {
        cout << "Selecting attractor at: " << index << endl;
        
        Attractor &a = *attractors.at(index);
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
        resetTrails(particles, trailHistory, trailHead, trailCount);
        return &a;
    };

    Attractor &currentAttractor = *attractors.at(0);
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
    resetTrails(particles, trailHistory, trailHead, trailCount);

    signed int currentIndex = 0;

    while (!WindowShouldClose())
    {
        Attractor &currentAttractor = *attractors[currentIndex];
        // We calculate this many updates per frame

        if (IsKeyPressed(KEY_RIGHT))
        {
            currentIndex++;
            if (currentIndex > attractors.size() - 1)
            {
                cout << "Cycling selector" << endl;
                currentIndex = 0;
            }
            currentAttractor = *select(currentIndex);
        }
        
        if (IsKeyPressed(KEY_LEFT))
        {
            currentIndex--;
            if (currentIndex < 0)
            {
                currentIndex = attractors.size() - 1;
            }
            currentAttractor = *select(currentIndex);
        }
        
        if (IsKeyPressed(KEY_R))
        {
            reset_particles(particles, currentAttractor.initialState());
            resetTrails(particles, trailHistory, trailHead, trailCount);
        }

        if (IsKeyPressed(KEY_T))
        {
            trailsEnabled = !trailsEnabled;
        }
        
        for (size_t i = 0; i < STEPS_PER_FRAME; ++i)
        {
            for (Vec3 &particle : particles)
            {
                particle = currentAttractor.getNextStep(particle, TIMESTEP);
            }   

            for (size_t particleIndex = 0; particleIndex < particles.size(); ++particleIndex)
            {
                trailHistory[particleIndex * TRAIL_LENGTH + trailHead] =
                    particles[particleIndex];
            }

            trailHead = (trailHead + 1) % TRAIL_LENGTH;
            if (trailCount < TRAIL_LENGTH)
            {
                ++trailCount;
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
                if (trailsEnabled)
                {
                    drawTrails(trailHistory, trailHead, trailCount);
                }
                drawParticles(particles, camera, glow, currentAttractor.getParticleSize());
            EndMode3D();
            
            string current = "Current System: " + currentAttractor.getName();
            DrawText(current.c_str(), 10, 10, 20, DARKGRAY);
            DrawText("T: toggle trails", 10, 35, 20, DARKGRAY);
        EndDrawing();
    }

    UnloadTexture(glow);
    CloseWindow();


    return 0;
}
