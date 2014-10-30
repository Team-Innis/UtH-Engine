#ifndef PHYSICSWORLD_H_UTH
#define PHYSICSWORLD_H_UTH

#include <Box2D/Box2D.h>
#include <UtH/Engine/Physics/PhysicsContactListener.hpp>
#include <pmath/Vector.hpp>
#include <UtH/Engine/Component.hpp>
#include <memory>

namespace uth
{
    // Conversion from pixels to meters
    const float PIXELS_PER_METER = 50.f;

    struct PhysicsSettings
    {
        float timeStep;
        unsigned int velocityIterations;
        unsigned int positionIterations;

        PhysicsSettings()
        {
            // 60 fps
            timeStep = 1.f / 60.f;

            // Box2d testbed defaults
            velocityIterations = 8;
            positionIterations = 3;
        }
    };

    class PhysicsWorld
    {
    public:
        PhysicsWorld(const float gravityX, const float gravityY, 
            const PhysicsSettings& settings = PhysicsSettings());
        PhysicsWorld(const pmath::Vec2& gravity,
            const PhysicsSettings& settings = PhysicsSettings());

        void SetGravity(const float x, const float y);
        void SetGravity(const pmath::Vec2& gravity);
        const pmath::Vec2 GetGravity() const;

        void SetContactListener(PhysicsContactListener* contactListener);

        void Update(float dt);

        void SetSettings(const PhysicsSettings& settings);
        PhysicsSettings& GetSettings();

        // Get the raw box2d world object
        std::shared_ptr<b2World> GetBox2dWorldObject();

    private:

        PhysicsWorld();

        std::shared_ptr<b2World> m_world;
        //b2World m_world;
        PhysicsSettings m_settings;

        float m_timer;
    };
}

#endif