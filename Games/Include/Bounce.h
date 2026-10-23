#pragma once

#include "Types/BounceTypes.h"
#include <vector>

namespace Bounce
{
    class Game : public Scene
    {
    private:
        Paddle paddle;
        std::vector<Ball> balls;
        Cooldown ballSpawnCooldown;
        Stats stats;
        sf::RectangleShape background;
        sf::Sound bounceSound;
        sf::Music music;

        /* Initialize */
        void InitPaddle();
        void InitStats();
        void InitBounceSound();
        void InitMusic();
        void InitBackground();

        /* Reset */
        void BindInputs();
        void StartPaddle();
        void StartStats();
        void StartMusic();

        /* Frame Updates */
        void UpdatePaddle();
        void UpdateBalls();
        void UpdateBall(Ball& ball);

        /* Conditional Updates */
        void EventBallSpawn();
        void EventBallsMissed(int ballsMissed);
        
        /* Collision Handling */
        void HandleCollisions();
        void HandleCollisionsPaddleBalls();
        void ResolveCollisionsPaddleBalls();
        void ResolveCollisionPaddleBall(Ball& ball);
        void HandleCollisionsBallsMap();
    public:
        Game(EngineContext&);

        void Start();
        void Update();
        void Render() const;
        void OnPause(bool);
        void OnCleanup();
    };
}