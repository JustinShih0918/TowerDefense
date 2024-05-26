#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <list>
#include <iostream>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreBoard.hpp"
using namespace std;
void ScoreBoard::Initialize(){
    startIndex = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoard::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoard::PrevOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev", "pirulen.ttf", 48, halfW - 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 300, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoard::NextOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next", "pirulen.ttf", 48, halfW + 500, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));
    
    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 48, halfW - 25, halfH / 2 - 150, 255, 0, 0, 255 , 0.5, 0.5));
    ReadPlayerScore();
    DrawPlayerScore();
}

void ScoreBoard::Terminate(){
    IScene::Terminate();
}

void ScoreBoard::BackOnClick(int stage){
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreBoard::PrevOnClick(int stage){
    if(startIndex - 5 >= 0){
            startIndex -= 5;
        }
    else startIndex = 0;
    RemoveScore();
    DrawPlayerScore();
}

void ScoreBoard::NextOnClick(int stage){
    if(startIndex < PlayerList.size()){
        if(startIndex + 5 < PlayerList.size()){
            startIndex += 5;
        }
        else{
            startIndex += PlayerList.size()%5;
        }
    }
    if(startIndex < PlayerList.size()){
        RemoveScore();
        DrawPlayerScore();
    }
}

void ScoreBoard::ReadPlayerScore() {
    std::string filename = std::string("Resource/scoreboard") + ".txt";
	// Read enemy file.
	std::string name;
    float point;
	PlayerList.clear();
	std::ifstream fin(filename);
	while (fin >> name && fin >> point) {
		PlayerList.emplace_back(name,point);
	}
	fin.close();
}

void ScoreBoard::DrawPlayerScore(){
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    int len = PlayerList.size();
    int index;
    int nowY = halfH / 2 - 50;
    int edge = 80;
    list<pair<std::string, int>> myList;
    list<pair<string, int>>::iterator it = PlayerList.begin();
    for(int i = 0;i < startIndex && i < len;i++) it = next(it);
    for(int i = 0;i<5 && i + startIndex < PlayerList.size();i++){
        Engine::Label* name = new Engine::Label(it->first, "pirulen.ttf", 36, halfW - 150, nowY + edge*i, 255, 255, 255, 255 , 0.5, 0.5);
        Engine::Label* score = new Engine::Label(to_string(it->second), "pirulen.ttf", 36, halfW - 25 + 200, nowY + edge*i, 255, 255, 255, 255 , 0.5, 0.5);
        AddNewObject(name);
        AddNewObject(score);
        nowDrawing.push_back(pair<Engine::IObject*,Engine::IObject*>(name,score));
        it = next(it);
    }
}

void ScoreBoard::RemoveScore(){
    for(int i = 0;i<nowDrawing.size();i++){
        RemoveObject(nowDrawing[i].first->GetObjectIterator());
        RemoveObject(nowDrawing[i].second->GetObjectIterator());
    }
    nowDrawing.clear();
}



