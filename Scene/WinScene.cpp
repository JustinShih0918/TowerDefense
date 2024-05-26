#include <functional>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "PlayScene.hpp"
using namespace std;
void WinScene::Initialize() {
	ticks = 0;
	playerName.clear();
	nowDrawing.clear();
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH + 50, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 40, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");

	AddNewObject(new Engine::Image("win/textInput.png", halfW, halfH / 4 + 80, 800, 100,0.5,0.5));
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	ofstream ofin;
	ofin.open("./Resource/scoreboard.txt",ios::app);
	ofin << "\n";
	int len = playerName.size();
	for(int i = 0;i<len;i++){
		ofin << playerName[i];
	}
	ofin << " " << dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->score << "\n";
	ofin.close();
	ofin.open("./build/Resource/scoreboard.txt",ios::app);
	ofin << "\n";
	for(int i = 0;i<len;i++){
		ofin << playerName[i];
	}
	ofin << " " << dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->score << "\n";
	ofin.close();
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

char WinScene::parseKeyCode(int keyCode,int mode){
	if(mode == 0){
		if(keyCode <= 26 && keyCode >= 1) return keyCode + 96;
	}
	else if(mode == 1){
		if(keyCode <= 26 && keyCode >= 1) return keyCode + 64; // upper
	}
	else return 0;
}

void WinScene::DrawName(){
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	Engine::Label *draw = new Engine::Label(string(1,playerName.back()),"OpenSans-Regular.ttf", 36, halfW - 350 + startIndex*20, halfH / 4 + 80, 255, 0, 0, 255 , 0.5, 0.5);
	AddNewObject(draw);
	nowDrawing.push_back(draw);
}

void WinScene::RemoveChar(){
	RemoveObject(nowDrawing.back()->GetObjectIterator());
	nowDrawing.pop_back();
}

void WinScene::OnKeyDown(int keyCode){
	IScene::OnKeyDown(keyCode);
	char del;
	if(keyCode == ALLEGRO_KEY_BACKSPACE){
		del = playerName.back();
		playerName.pop_back();
		startIndex--;
		RemoveChar();
	}
	else if(keyCode >= 1 && keyCode <= 26){
		if(playerName.empty()){
			playerName.push_back(parseKeyCode(keyCode,1));
			startIndex = 0;
		}
		else{
			playerName.push_back(parseKeyCode(keyCode,0));
			startIndex++;
		}
		DrawName();
	}
}
