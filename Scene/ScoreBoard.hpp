#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include <string>
using namespace std;
class ScoreBoard final : public Engine::IScene{
    private:
        std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    public:
        int startIndex;
	    std::list<std::pair<std::string, int>> PlayerList;
        vector<std::pair<Engine::IObject*,Engine::IObject*>> nowDrawing;
        explicit ScoreBoard() = default;
        void Initialize() override;
        void Terminate() override;
        //void ScoreboardOnClick();
        // void PrevOnClick();
        // void NextOnClick();
        void BackOnClick(int stage);
        void ReadPlayerScore();
        void DrawPlayerScore();
        void RemoveScore();
        void Update(float deltaTime) override;
};

#endif