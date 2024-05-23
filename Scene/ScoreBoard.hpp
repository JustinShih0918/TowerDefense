#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class ScoreBoard final : public Engine::IScene{
    private:
        std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    public:
        explicit ScoreBoard() = default;
        void Initialize() override;
        void Terminate() override;
        //void ScoreboardOnClick();
        // void PrevOnClick();
        // void NextOnClick();
        void BackOnClick(int stage);
};

#endif