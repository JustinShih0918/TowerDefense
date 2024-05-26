#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
#include <iostream>
#include <vector>
using namespace std;
class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
public:
	vector<char> playerName;
	vector<Engine::IObject*> nowDrawing;
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	void OnKeyDown(int keyCode) override;
	char parseKeyCode(int keyCode,int mode);
	void DrawName();
	void RemoveChar();
	int startIndex;
};

#endif // WINSCENE_HPP
