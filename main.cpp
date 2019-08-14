#include <SFML/Graphics.hpp>
using namespace sf;

#include <SFML/Audio.hpp>

#include <iostream>
using namespace std;

#include <string>

#include <fstream>

#include <cmath>

#include <sstream>

#include <vector>

#include "Animation.h"

#include "Player.h"

#include "Enemy.h"

#include "Explosion.h"

#include "Bullet.h"

#include "Coin.h"

//Creat random Number for game loop
int getRandomNumber(int a, int b, char ch);

string getRandomImage();

//Measures distance between any two points in the vertices
float getDistance(float, float, int, int);

//regenerate enemy
void setEnemNewPosition(Enemy& enem, int num, int speed);

//respawn coin
void setCoinNewPosition(Coin& , int );

// DISTANCE BETWEEN COIN AND PLAYER
int getCPdistance(Coin& , Player& );

int main() {
	//In Game variables for game loop
	string lineFile;
	string currentHighScore;
	float maxSpeed = 5.0f;
	float speed = 0;
	float bgAcc = 0.01f;
	float bgDcc = 0.03f;
	float BackgroundY1 = 0;
	float BackgroundY2 = -1080.0f;
	float BackgroundY3 = -2160.0f;
	float BackgroundY4 = -3240.0f;
	float borderRight = 0;
	float borderLeft = 705.0f;
	float score = 0;
	
	//Enemy max lim
	int oppMaxSpeed = 5;
	//player Collision stats
	bool collided = false;
	//Bullet stats
	bool fire = false;
	//Enemy collision stat
	bool bulletCollide = false;

	//Explosion vector
	vector<Explosion> explode;
	//Bullet Vector
	vector<Bullet> bullet;
	//EnemyExplode Vector
	vector<Explosion> enemyExplode;
	//Coin vector
	vector<Coin> coinVect;



	///////Sound Buffer
	SoundBuffer fireBuffer, coinPick;
	//Sound 
	Sound fireSound, coinSound;
	/// Testing Sound
	if (!fireBuffer.loadFromFile("sounds/bulletShot.wav")) {
		cout << "Error Loading Sound" << endl;
	}
	if (!coinPick.loadFromFile("sounds/Pickup_Coin.wav")) {
		cout << "Error Loading Sound" << endl;
	}
	//Setting Sounds
	fireSound.setBuffer(fireBuffer);
	coinSound.setBuffer(coinPick);

	/////////Fonts
	Font scoreFont, highScoreFont;
	if (!scoreFont.loadFromFile("fonts/PaladinsCondensed-rB77.otf")) {
		cout << "Error loading Score Font";
	}
	if (!highScoreFont.loadFromFile("fonts/PaladinsCondensed-rB77.otf")) {
		cout << "Error Loading High Score font";
	}


	//Text
	Text scoreText, scoreTitleText, highScoreText, highScoreTitleText, titleText;
	scoreText.setFont(scoreFont);
	highScoreText.setFont(highScoreFont);

	scoreText.setPosition(Vector2f(1250.0f, 100.0f));
	scoreText.setFillColor(Color::Black);
	highScoreText.setPosition(Vector2f(640.0f, 100.0f));
	highScoreText.setFillColor(Color::Black);

	//stringstream scores;
	ifstream file;
	file.open("highScore.txt");
	if (!file) {
		cout << "Error loading Record";
	}

	///////////Texture
	Texture bg1, bg2, bg3, bg4, bgCover, bombTxt, bulletTxt, scoreBoardTxt, coinTexture;

	if (bg1.loadFromFile("images/new1.png"))
	{
		cout << "File 1 Loaded Successfully" << endl;
		bg1.setSmooth(true);
	}
	else {
		cout << "Error Loading File 1" << endl;
	}

	if (bg2.loadFromFile("images/new2.png"))
	{
		cout << "File 2 Loaded Successfully" << endl;
		bg2.setSmooth(true);
	}
	else {
		cout << "Error Loading File 2" << endl;
	}
	if (bg3.loadFromFile("images/new3.png"))
	{
		cout << "File 3 Loaded Successfully" << endl;
		bg3.setSmooth(true);
	}
	else {
		cout << "Error Loading File 3" << endl;
	}
	if (bg4.loadFromFile("images/new4.png"))
	{
		cout << "File 4 Loaded Successfully" << endl;
		bg4.setSmooth(true);
	}
	else {
		cout << "Error Loading File 3" << endl;
	}

	if (bgCover.loadFromFile("images/backupBG.png"))
	{
		cout << "Files Cover loaded Successfully" << endl;
		bgCover.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (bombTxt.loadFromFile("images/type_C.png"))
	{
		cout << "Bomb Cover loaded Successfully" <<endl;
		bombTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (bulletTxt.loadFromFile("images/fire_red.png"))
	{
		cout << "Gun Fire loaded Successfully" <<endl;
		bulletTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}
	if (scoreBoardTxt.loadFromFile("images/scoreBoard.png"))
	{
		cout << "Score Board Loaded Successfully" << endl;
		bulletTxt.setSmooth(true);
	}
	else {
		cout << "Error loading Cover";
	}

	if (coinTexture.loadFromFile("images/coins.png"))
	{
		cout << "Coins Loaded Successfully" << endl;
		coinTexture.setSmooth(true);
	}
	else {
		cout << "Error loading Coiin";
	}

	//Setting up a sprite
	Sprite mainBG, mainBG2, mainBG3, mainBG4, mainCover, scoreBoard;
	mainBG.setTexture(bg1);
	mainBG2.setTexture(bg2);
	mainBG3.setTexture(bg3);
	mainBG4.setTexture(bg4);
	mainCover.setTexture(bgCover);
	scoreBoard.setTexture(scoreBoardTxt);

	//bombSpr.setTexture(bombTxt);

	//Player Object
	Player racer("images/Car.png", 985.0f, 900.0f);

	//Coin Objects
	coinVect.push_back(Coin(coinTexture, getRandomNumber(705, 805, 'c'), getRandomNumber(-1500, -1700, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(855, 955, 'c'), getRandomNumber(-2700, -2900, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(1005, 1055, 'c'), getRandomNumber(-3900, -4100, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(1105, 1155, 'c'), getRandomNumber(-5100, -5300, 'c'), 60, 60, 10, 0.1));
	coinVect.push_back(Coin(coinTexture, getRandomNumber(1205, 1255, 'c'), getRandomNumber(-6300, -6500, 'c'), 60, 60, 10, 0.1));
	
	Coin cc(coinTexture, 0, 0, 60, 60, 10, 0.1);
	//ScoreBoard
	scoreBoard.setPosition(Vector2f(501.0f,0));

	//Enemies Objects
	Enemy en1(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1500, -1700, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en2(getRandomImage(), getRandomNumber(855, 955, 'e'), getRandomNumber(-1800, -2000, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en3(getRandomImage(), getRandomNumber(1005, 1055, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en4(getRandomImage(), getRandomNumber(1105, 1155, 'e'), getRandomNumber(-2500, -2700, 'e'), getRandomNumber(3, 8, 's'));
	Enemy en5(getRandomImage(), getRandomNumber(1205, 1255, 'e'), getRandomNumber(-2800, -3000, 'e'), getRandomNumber(3, 8, 's'));
	/*
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(705, 805, 'e'), getRandomNumber(-1500, -1700, 'e'), getRandomNumber(3, 8, 's')));
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(815, 915, 'e'), getRandomNumber(-1800, -2000, 'e'), getRandomNumber(3, 8, 's')));
	enemVect.push_back(Enemy(getRandomImage(), getRandomNumber(925, 1025, 'e'), getRandomNumber(-2200, -2400, 'e'), getRandomNumber(3, 8, 's')));
	*/


	RenderWindow window(VideoMode(1920, 1080), "Drift Race", sf::Style::Close | sf::Style::Titlebar);
	//window.setFramerateLimit(90);

	//Loading Window  main Game LOOP
	while (window.isOpen()) {
		Event evnt;

		while (window.pollEvent(evnt)) {

			switch (evnt.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (evnt.key.code == Keyboard::Space) 
				{
					//cout << "Fired";
					fire = true;
					bullet.push_back(Bullet(bulletTxt, (int)racer.getPosX(), (int)racer.getPosY(), 32, 64, 16, 0.25));
					fireSound.play();
				}
				break;
			}

			
		}
		//Showing High Score from file
		while (file >> lineFile) {
			highScoreText.setString(lineFile);

			//Store score from file
			currentHighScore = lineFile;
			//cout << lineFile << endl;
		}
//		file.close();

		scoreText.setString(to_string((int)score));

		if (!collided) {
			//player movement
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				racer.movePlayer('u');
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				racer.movePlayer('r');
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				racer.movePlayer('d');
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				racer.movePlayer('l');
			}
		}

		//Create scrolling background
		mainBG.setPosition(Vector2f(0, BackgroundY1));
		mainBG2.setPosition(Vector2f(0, BackgroundY2));
		mainBG3.setPosition(Vector2f(0, BackgroundY3));
		mainBG4.setPosition(Vector2f(0, BackgroundY4));
		//Cover up
		mainCover.setPosition(Vector2f(0, 0));

		if (mainBG.getPosition().y >= 1080)
		{
			BackgroundY1 = -3240.0f;
		}
		if (mainBG2.getPosition().y >= 1080) {
			BackgroundY2 = -3240.0f;
		}
		if (mainBG3.getPosition().y >= 1080) {
			BackgroundY3 = -3240.0f;
		}
		if (mainBG4.getPosition().y >= 1080) {
			BackgroundY4 = -3240.0f;
		}

		//If not collided
		if (!collided) {
			// Slow start simulation
			if (speed <= maxSpeed) {
				//cout << "True";
				speed += bgAcc;
			}

			BackgroundY1 += speed;
			BackgroundY2 += speed;
			BackgroundY3 += speed;
			BackgroundY4 += speed;
		}


		// Regeneration of Enemy
		//cout << en1.getPosY() << endl;

		if (en1.getPosY() > 1080) {
			setEnemNewPosition(en1, 1, oppMaxSpeed);
//			score++;
		}
		if (en2.getPosY() > 1080) {
			setEnemNewPosition(en2, 2, oppMaxSpeed);
//			score++;
		}
		if (en3.getPosY() > 1080) {
			setEnemNewPosition(en3, 3, oppMaxSpeed);
//			score++;
		}
		if (en4.getPosY() > 1080) {
			setEnemNewPosition(en4, 4, oppMaxSpeed);
//			score++;
		}
		if (en5.getPosY() > 1080) {
			setEnemNewPosition(en5, 5, oppMaxSpeed);
//			score++;
		}

		// Game Level
		if (score > 25 && score < 150) { maxSpeed = 7; oppMaxSpeed = 7; };
		if (score > 150 && score < 200) { maxSpeed = 9; oppMaxSpeed = 9; };
		if (score > 200 && score < 250) { maxSpeed = 11; oppMaxSpeed = 11; };


		//Check collission of player and enemy
		if (!collided) {
			if (getDistance(racer.getPosX(), racer.getPosY(), en1.getPosX(), en1.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en2.getPosX(), en2.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en3.getPosX(), en3.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en4.getPosX(), en4.getPosY()) < 60 ||
				getDistance(racer.getPosX(), racer.getPosY(), en5.getPosX(), en5.getPosY()) < 60)
			{
				collided = true;
				//cout << "Collided";
				explode.push_back(Explosion(bombTxt, (int)racer.getPosX() - 170, (int)racer.getPosY() - 150, 256, 256, 48, 0.25));
				racer.setLife(racer.getLife() - 1);
			}
		}

		/////////////////////////////////////////////////
		///////////////// BULLET COLLISION /////////////
		// Check collission of bullet and enemy
		if (fire) {
			for (int i = 0; i < bullet.size(); i++) {
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en1.getPosX(), en1.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en1.getPosX() - 170, (int)en1.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en1, 1, oppMaxSpeed);
					score += 1;
				}
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en2.getPosX(), en2.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en2.getPosX() - 170, (int)en2.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en2, 2, oppMaxSpeed);
					score += 1;
				}
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en3.getPosX(), en3.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en3.getPosX() - 170, (int)en3.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en3, 3, oppMaxSpeed);
					score += 1;
				}
				if(getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en4.getPosX(), en4.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en4.getPosX() - 170, (int)en4.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en4, 4, oppMaxSpeed);
					score += 1;
				}
				if (getDistance((float)bullet[i].getPosX(), (float)bullet[i].getPosY(), en5.getPosX(), en5.getPosY()) < 60) {
					bulletCollide = true;
					enemyExplode.push_back(Explosion(bombTxt, (int)en5.getPosX() - 170, (int)en5.getPosY() - 150, 256, 256, 48, 0.25));
					
					setEnemNewPosition(en5, 5, oppMaxSpeed);
					score += 1;
				}
			}
		}

		/////////////////////////////////////////////////
		///////////////// PLAYER COLLISION /////////////
		/// Player Collided
		if (collided) {
			// Slow start simulation
			if (maxSpeed <= 5) {
				if (speed > 0) {
					speed -= 0.05f;
				}
			}else if (maxSpeed > 5 && maxSpeed <= 7) {
				if (speed > 0) {
					speed -= 0.05f;
				}
			}
			else if (maxSpeed > 7 && maxSpeed <= 9) {
				if (speed > 0) {
					speed -= 0.07f;
				}
			}
			else if (maxSpeed > 9 && maxSpeed <= 11) {
				if (speed > 0) {
					speed -= 0.09f;
				}
			}

			BackgroundY1 += speed;
			BackgroundY2 += speed;
			BackgroundY3 += speed;
			BackgroundY4 += speed;
		}

		
		///////////////////////////////////////////////
		///////////////////////////////////////////////
		/////////////// COIN COLLISION ///////////////
		///////////////////////////////////////////////
		///////////////////////////////////////////////
		for (int i = 0; i < coinVect.size(); i++)
		{
			if (getCPdistance(coinVect[i], racer) < 60) {
				coinSound.play();
				setCoinNewPosition(coinVect[i], i);
				score += 2;
			}
		}



		
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		//////////////////////////// Drawing Session ////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		
		//Clearing and creating windows
		window.clear();

		window.draw(mainCover);
		window.draw(mainBG);
		window.draw(mainBG2);
		window.draw(mainBG3);
		window.draw(mainBG4);

		//Render Player Object
		racer.drawPlayer(window);

		//Render Enemies
		en1.drawEnemy(window);
		en2.drawEnemy(window);
		en3.drawEnemy(window);
		en4.drawEnemy(window);
		en5.drawEnemy(window);
		//en6.drawEnemy(window);


		//Render Coin
		for (int i = 0; i < coinVect.size(); i++) {
			coinVect[i].update();
			window.draw(coinVect[i].sprite);
			coinVect[i].updateCoin();
		}
		
		cc.update();
		window.draw(cc.sprite);

		//Explosion
		if (collided) {

			for (int i = 0; i < explode.size(); i++) {
				explode[i].update();
				window.draw(explode[i].sprite);
				if (explode[i].isEnd()) {
					/*if (explode.size() > 1) {
						swap(explode.front(), explode.end());
					}*/
					explode.pop_back(); collided = false;
				};
			}
		}

		if (fire) {
			for (int i = 0; i < bullet.size(); i++) {
				bullet[i].update();
				window.draw(bullet[i].sprite);
				bullet[i].updateBullet();

				if (bullet[i].getPosY() < 0) {
					bullet.erase(bullet.begin() + 0);
				}
			}

			if (bullet.empty()) {
				fire = false;
			}
		}

		if (bulletCollide) {
			for (int i = 0; i < enemyExplode.size(); i++) {
				enemyExplode[i].update();
				window.draw(enemyExplode[i].sprite);

				if (enemyExplode[i].isEnd()) {
					enemyExplode.erase(enemyExplode.begin() + 0);
				}
			}
			if (enemyExplode.empty()) {
				bulletCollide = false;
			}
		}


		///////////////////////////
		//Render ScoreBoard
		window.draw(scoreBoard);

		//Render Score
		window.draw(highScoreText);
		window.draw(scoreText);

		//////////////////////////

		// Checking Player LifeSpan 
		if (racer.getLife() <= 0) {
			cout << "You Died !";

			if (score > stoi(currentHighScore)) {
				//Storing HIGH SCORE
				ofstream storeFile;
				storeFile.open("highScore.txt");

				storeFile << score;
				storeFile.close();
			}

			window.close();
		}


		window.display();
	}
}

//// e = enemy
//// i = image
//// s = speed
//// c = coin
int getRandomNumber(int a, int b, char ch)
{
	static bool first = true; if (first) { srand(time(NULL)); first = false; }
	int result = a + rand() % ((b + 1) - a);
	if (ch == 'e') {
		result = (result / 10) * 10;
		return result;
	}
	else if (ch == 'i' || ch == 's' || ch == 'c') {
		return result;
	}
	return result;
}

string getRandomImage() {
	stringstream ss;
	ss << getRandomNumber(1, 4, 'i');
	string imgTag = ss.str();

	string imgDir = "images/obs" + imgTag + ".png";
	//cout << imgDir;

	return imgDir;
}

float getDistance(float x1, float y1, int x2, int y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void setEnemNewPosition(Enemy &enem, int num, int speed) {
	if (num == 1) {
		enem.setPosY(getRandomNumber(-1500, -1700, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 2) {
		enem.setPosY(getRandomNumber(-1800, -2000, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 3) {
		enem.setPosY(getRandomNumber(-2100, -2300, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 4) {
		enem.setPosY(getRandomNumber(-2400, -2600, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}
	else if (num == 5) {
		enem.setPosY(getRandomNumber(-2700, -2900, 'e'));
		enem.setNewTexture(getRandomImage());
		enem.setSpeed(getRandomNumber(3, speed, 's'));
	}

}

int getCPdistance(Coin& c, Player& p) {
	return sqrt(pow((p.getPosX() - c.getPosX()),2) + pow((p.getPosY() - c.getPosY()),2));
}

void setCoinNewPosition(Coin& coin, int num) {
	if (num == 0) {
		coin.setNewPos(getRandomNumber(705, 805, 'c'), getRandomNumber(-1500, -1700, 'c'));
	}
	else if (num == 1) {
		coin.setNewPos(getRandomNumber(855, 955, 'c'), getRandomNumber(-2700, -2900, 'c'));
	}
	else if (num == 2) {
		coin.setNewPos(getRandomNumber(1005, 1055, 'c'), getRandomNumber(-3900, -4100, 'c'));
	}
	else if (num == 3) {
		coin.setNewPos(getRandomNumber(1105, 1155, 'c'), getRandomNumber(-5100, -5300, 'c'));
	}
	else if (num == 4) {
		coin.setNewPos(getRandomNumber(1205, 1255, 'c'), getRandomNumber(-6300, -6500, 'c'));
	}
}