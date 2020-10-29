#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/OpenGL.hpp>
#include<thread>
#include<math.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<typeinfo>
#include<random>
#include<windows.h>
#include<unordered_map> 
#include <time.h>

using namespace sf;
using namespace std;

class strDic { // string tuple for store array of string.
public:
	unordered_map<string, string> map;
	string get(string keyIn) {
		return this->map[keyIn];
	}
	void set(string keyIn, string In) {
		this->map[keyIn] = In;
	}
	void append(string keyIn, string In) {
		this->map[keyIn] = In;
	}
	void remove(string keyIn) {
		this->map.erase(keyIn);
	}
	unsigned __int64 length() {
		return this->map.size();
	}
};

class fltDic { // string tuple for store array of string.
public:
	unordered_map<string, float> map;
	float get(string keyIn) {
		return this->map[keyIn];
	}
	void set(string keyIn, float In) {
		this->map[keyIn] = In;
	}
	void append(string keyIn, float In) {
		this->map[keyIn] = In;
	}
	void remove(string keyIn) {
		this->map.erase(keyIn);
	}
	void incread(string keyIn, int In) {
		this->map[keyIn] += In;
	}
	unsigned __int64 length() {
		return this->map.size();
	}
};
class Object {
private:
	string Type = "Dynamic";
	unsigned __int64 ID;
	string Name = "None";
	fltDic Stat;
	float posX = 0;
	float posY = 0;
	float Size[2];
	int imgHeight;
	int imgWidth;
	sf::Vector2f velocity;

	int time = 0, Index = 0;
	unordered_map<string, vector<Texture*>> textureArray;
	unordered_map<string, vector<int>> duration;
	string slot;
public:
	bool loop = false;
	bool passable = true;
	bool fliping = false;
	float offsetPosX = 0;
	float offsetPosY = 0;
	string tag = "None", cat = "None";
	bool usable = true;
	Sprite sprite;
	Object(unsigned __int64 ID) {
		this->ID = ID;
	}
	void useStat(Object In) {
		this->textureArray = In.textureArray;
		this->duration = In.duration;
		this->fliping = In.fliping;
		this->setImgDim(In.imgWidth, In.imgHeight);
		this->loop = In.loop;
		this->passable = In.passable;
		this->setPosX(In.posX);
		this->setPosY(In.posY);
		this->setSpriteSize(In.getSizeX(), In.getSizeY());
		this->Stat = In.Stat;
		this->Type = In.Type;
		this->sprite = In.sprite;
		this->slot = In.slot;
		this->tag = In.tag;
	}
	void setTag(string Tag) {
		this->tag = Tag;
	}
	void useStatNoPos(Object In) {
		this->textureArray = In.textureArray;
		this->duration = In.duration;
		this->fliping = In.fliping;
		this->setImgDim(In.imgWidth, In.imgHeight);
		this->loop = In.loop;
		this->passable = In.passable;
		this->setSpriteSize(In.getSizeX(), In.getSizeY());
		this->Stat = In.Stat;
		this->Type = In.Type;
		this->sprite = In.sprite;
		this->slot = In.slot;
		this->tag = In.tag;
		this->Is(In.nowIs());
	}
	vector<float> getHitBoxData() {
		return { this->PosX() - (this->getImgWigth() * this->Size[0] / 2), this->PosY(), this->PosX() + (this->getImgWigth() * this->Size[0] / 2), this->PosY() + (this->getImgHeight() * this->Size[1] * 3 / 10) , this->PosX(), this->PosY() + (this->getImgHeight() * this->Size[1]) / 2 };
	}
	void isPassable(bool In) {
		this->passable = In;
	}
	void setAnimationSeq(string Slot) {
		this->slot = Slot;
	}
	int getImgHeight() {
		return this->imgHeight;
	}
	int getImgWigth() {
		return this->imgWidth;
	}
	void setImgDim(int Width, int Height) {
		this->imgHeight = Height;
		this->imgWidth = Width;
		const float halfW = Width / 2; // setOrigin required it.
		const float halfH = Height / 2; // setOrigin required it.
		this->sprite.setOrigin({ halfW , halfH });
	}
	string type() {
		return this->Type;
	}
	void setType(string In) {
		this->Type = In;
	}
	unsigned __int64 getID() {
		return this->ID;
	}
	void addTexture(string Path, string seqName, int durt) {
		Texture* ptr = new Texture;
		if (!(*ptr).loadFromFile(Path)) {
			printf("Error");
		}
		int old_size = this->textureArray.size();
		this->textureArray[seqName].push_back(ptr);
		this->duration[seqName].push_back(durt);

	}
	void setSpriteTexture(string seqName, unsigned long long Index) {
		this->sprite.setTexture(*this->textureArray[seqName][Index]);
	}
	void setSpriteSize(float scalex, float scaley) {
		this->sprite.setScale(scalex, scaley);
		this->Size[0] = scalex;
		this->Size[1] = scaley;
	}
	float getSizeX() {
		return this->Size[0];
	}
	float getSizeY() {
		return this->Size[1];
	}
	void addStat(string KeyIn, float val) {
		Stat.append(KeyIn, val);
	}
	void incread(string KeyIn, int amount) {
		this->Stat.incread(KeyIn, amount);
	}
	float getStat(string KeyIn) {
		return Stat.get(KeyIn);
	}
	void setOffsetPosX(float offx) {
		this->offsetPosX = offx;
	}
	void setOffsetPosY(float offy) {
		this->offsetPosY = offy;
	}
	void setPosX(float x) {
		this->posX = x;
		this->sprite.setPosition(this->posX + this->offsetPosX, this->posY + this->offsetPosY);
	}
	void setPosY(float y) {
		this->posY = y;
		this->sprite.setPosition(this->posX + this->offsetPosX, this->posY + this->offsetPosY);
	}
	void moveX(float amount) {
		this->sprite.setPosition(this->posX + amount + this->offsetPosX, this->posY + this->offsetPosY);
		this->posX += amount;
	}
	void moveY(float amount) {
		this->sprite.setPosition(this->posX + this->offsetPosX, this->posY + amount + this->offsetPosY);
		this->posY += amount;
	}
	float PosX() {
		return this->posX + this->offsetPosX;
	}
	float PosY() {
		return this->posY + this->offsetPosY;
	}
	float OrigPosX() {
		return this->posX;
	}
	float OrigPosY() {
		return this->posY;
	}
	void Is(string name) {
		this->Name = name;
	}
	string nowIs() {
		return this->Name;
	}
	Sprite getSprite() {
		return this->sprite;
	}
	void UpdateAnimation(int speed) {
		this->time += speed;
		if (this->loop && this->Index >= this->textureArray[this->slot].size()) {
			this->Index = 0;
		}
		if (this->Index < this->textureArray[this->slot].size() && this->time >= duration[this->slot][this->Index]) {
			this->sprite.setTexture(*(this->textureArray[this->slot][this->Index]));
			this->Index++;
			this->time = 0;
		}
	}
	void resetTimeSeq() {
		this->time = 0;
	}
	void flipTexture(int rev) {
		this->fliping = !this->fliping;
		this->sprite.setScale(rev * this->Size[0], this->Size[1]);
	}
	void setStat(string key, float value) {
		this->Stat.set(key, value);
	}
};

class Map {
public:
	unordered_map<string, Object*> Tuple;
	unordered_map<string, Object*> Templ;
	unordered_map<unsigned __int64, string> Tuplekey, Templkey;
	void clear() {
		this->Templ.clear();
		this->Tuple.clear();
	}
	void createTemplate(string name) {
		Object* p = new Object(this->Templ.size());
		p->Is(name);
		this->Templ[name] = p;
		Templkey[this->Templ.size()] = name;
	}
	void registerObject(string Name, string Template, string Cat) {
		Object* p = new Object(this->Tuple.size());
		(*p).useStat(*this->Template(Template));
		(*p).Is(Name);
		p->cat = Cat;
		this->Tuple[Name] = p;
		this->Tuplekey[this->Tuple.size() - 1] = Name;
	}
	Object* object(string keyIn) {
		return Tuple[keyIn];
	}
	Object* Template(string keyIn) {
		return Templ[keyIn];
	}
	Object* objectAt(unsigned __int64 Index) {
		return this->Tuple[Tuplekey[Index]];
	}
	void remove(string keyIn) {
		this->Tuple.erase(keyIn);
	}
	void removeObjAt(unsigned __int64 Index) {
		cout << this->Tuplekey[Index] << endl;
		this->Tuple.erase(this->Tuplekey[Index]);
	}
	unsigned __int64 entityNumber() {
		return this->Tuple.size();
	}
	string objectTypeAt(unsigned __int64 Index) {
		return this->objectAt(Index)->nowIs();
	}
	unordered_map<string, Object*> getTuple() {
		return this->Tuple;
	}

};

class strMap {
public:
	unordered_map<string, Font> font;
	unordered_map<string, Text*> Tuple;
	unordered_map<string, string> Tag;
	unordered_map<unsigned __int64, string> Tuplekey;
	void registerObject(string Name, string tag) {
		Text* p = new Text;
		this->Tuple[Name] = p;
		this->Tag[Name] = tag;
		this->Tuplekey[this->Tuple.size() - 1] = Name;
	}
	void addFont(string name, string path) {
		font[name].loadFromFile(path);
	}
	Font Font(string name) {
		return this->font[name];
	}
	Text* object(string keyIn) {
		return this->Tuple[keyIn];
	}
	Text* objectAt(unsigned __int64 Index) {
		return this->Tuple[this->Tuplekey[Index]];
	}
	void remove(string keyIn) {
		this->Tuple.erase(keyIn);
	}
	string tag(string keyIn) {
		return this->Tag[keyIn];
	}
	void removeObjAt(unsigned __int64 Index) {
		cout << this->Tuplekey[Index] << endl;
		this->Tuple.erase(this->Tuplekey[Index]);
	}
	unsigned __int64 entityNumber() {
		return this->Tuple.size();
	}
	unordered_map<string, Text*> getTuple() {
		return this->Tuple;
	}

};

class gameEngine { //this a main class of this game. resposibility for render object, recieve input event, draw graphic.
private:
	Sprite Marco;
	Texture texture;
	RenderWindow* window;
	unordered_map<string, Map> Field;
	Event ev;
	Map map;
	

	void initWindow()
	{
		VideoMode mode;
		mode.height = 720;
		mode.width = 1080;
		window = new RenderWindow(mode, "GUN SLUG", Style::Titlebar | Style::Close);

	}
	void initobject()
	{
		this->Field["Dynamic"].createTemplate("Blank");

		this->Field["Dynamic"].registerObject("Marco", "Blank", "Marco");
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\win\\win1.png", "win", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\win\\win2.png", "win", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\win\\win3.png", "win", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\win\\win4.png", "win", 8);

		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\stand\\stand1.png", "stand", 100);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\stand\\stand2.png", "stand", 100);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\stand\\stand3.png", "stand", 100);

		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\shoot\\shoot1.png", "shoot", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\shoot\\shoot2.png", "shoot", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\shoot\\shoot3.png", "shoot", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\shoot\\shoot4.png", "shoot", 8);

		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run1.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run2.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run3.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run4.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run5.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run6.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run7.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run8.png", "run", 50);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\run\\run9.png", "run", 50);

		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload1.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload2.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload3.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload4.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload5.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload6.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload7.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload8.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload9.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload10.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload11.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload12.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload13.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload14.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload15.png", "reload", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\reload\\reload16.png", "reload", 8);
		
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump1.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump2.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump3.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump4.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump5.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump6.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump7.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump8.png", "jump", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\jump\\jump9.png", "jump", 8);

		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink1.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink2.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink3.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink4.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink5.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink6.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink7.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink8.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink9.png", "drink", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\drink\\drink10.png", "drink", 8);

		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die1.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die2.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die3.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die4.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die5.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die6.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die7.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die8.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die9.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die10.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die11.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die12.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die13.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die14.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die15.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die16.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die17.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die18.png", "die", 8);
		this->Field["Dynamic"].object("Marco")->addTexture("sprite\\die\\die19.png", "die", 8);

		this->Field["Dynamic"].object("Marco")->setImgDim(37, 40);
		this->Field["Dynamic"].object("Marco")->setPosX(500);
		this->Field["Dynamic"].object("Marco")->setPosY(500);
		this->Field["Dynamic"].object("Marco")->setAnimationSeq("stand");
		this->Field["Dynamic"].object("Marco")->loop = true;
		this->Field["Dynamic"].object("Marco")->setSpriteSize(2.5, 2.5);

		this->Field["Dynamic"].registerObject("Bom", "Blank", "Bom");
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom1.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom2.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom3.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom4.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom5.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom6.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom7.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom8.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom9.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom10.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom11.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom12.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom13.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom14.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom15.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom16.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom17.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom18.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom19.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom20.png", "bom", 8);
		this->Field["Dynamic"].object("Bom")->addTexture("sprite\\bom\\bom21.png", "bom", 8);

		
		texture.loadFromFile("sprite\\stand\\stand1.png");
		Marco.setScale(5, 5);
		Marco.setTexture(texture);
	}
public:

	float move_speed = 3;
	bool is_Running() {
		return window->isOpen();
	}
	
	void pollevent() {
		while (this->window->pollEvent(this->ev)) {

			if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Escape) {
				this->window->close();
			}
			if (ev.type == Event::KeyPressed && (ev.key.code == Keyboard::Left || ev.key.code == Keyboard::Right)) {
				if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Left) {
					this->Field["Dynamic"].object("Marco")->flipTexture(-1);
					this->Field["Dynamic"].object("Marco")->moveX(-5*5);
					this->Field["Dynamic"].object("Marco")->setAnimationSeq("run");
					
				}
				if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Right) {
					this->Field["Dynamic"].object("Marco")->flipTexture(1);
					this->Field["Dynamic"].object("Marco")->moveX(5*5);
					this->Field["Dynamic"].object("Marco")->setAnimationSeq("run");
				}
			}
			else {
				this->Field["Dynamic"].object("Marco")->setAnimationSeq("stand");
			}

		}

	}

	gameEngine()
	{
		initWindow();
		initobject();
	}
	void update(){
		this->Field["Dynamic"].object("Marco")->UpdateAnimation(1);
		pollevent();
	}

	void render() {
		this->window->clear();
		this->window->draw(this->Field["Dynamic"].object("Marco")->getSprite());
		
		window->display();
	}
};

gameEngine GUN_SLUG;

int main()
{
	while (GUN_SLUG.is_Running())
	{
		GUN_SLUG.update();
		GUN_SLUG.render();
		Sleep(1);
	}
	return 0;
}