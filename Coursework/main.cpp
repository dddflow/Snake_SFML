#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include "list.h"
#include <iostream>

using namespace std;
using namespace sf;

FILE* file;

struct list_node* rec = NULL;

void main_menu();
void about();
void faq();
void game();
void you_lose(int c);
void difficulty();
void game_menu();
void game_pvp();
void game_pve();
void game_pause();
void records();

int main()
{
	file = fopen("records.txt", "a+");

	while (!feof(file))
	{
		int sc;
		char na[256] = { 0 };
		fscanf(file, "%d", &sc);
		if (!feof(file))
			fgets(na, 256, file);
		if (na[0] != 0)
			insert(&rec, na, sc);
		else
			break;
	}

	fclose(file);

	main_menu();

	return 0;
}

void main_menu()
{
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");

    Texture menuTexture[6];
    menuTexture[0].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\NewGame.png");
    menuTexture[0].setSmooth(true);

    menuTexture[1].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Difficulty.png");
    menuTexture[1].setSmooth(true);

    menuTexture[2].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Records.png");
    menuTexture[2].setSmooth(true);

    menuTexture[3].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\About.png");
    menuTexture[3].setSmooth(true);

    menuTexture[4].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\FAQ.png");
    menuTexture[4].setSmooth(true);

    menuTexture[5].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Exit.png");
    menuTexture[5].setSmooth(true);

    Sprite menu1(menuTexture[0]), \
        menu2(menuTexture[1]), \
        menu3(menuTexture[2]), \
        menu4(menuTexture[3]), \
        menu5(menuTexture[4]), \
        menu6(menuTexture[5]); \

    int menu1_pos[2] = { 500, 350 };
    menu1.setPosition(menu1_pos[0], menu1_pos[1]);
    menu1.setScale(0.7f, 0.7f);

    int menu2_pos[2] = { 520, 450 };
    menu2.setPosition(menu2_pos[0], menu2_pos[1]);
    menu2.setScale(0.7f, 0.7f);

    int menu3_pos[2] = { 400, 550 };
    menu3.setPosition(menu3_pos[0], menu3_pos[1]);
    menu3.setScale(0.7f, 0.7f);

    int menu4_pos[2] = { 475, 650 };
    menu4.setPosition(menu4_pos[0], menu4_pos[1]);
    menu4.setScale(0.7f, 0.7f);

    int menu5_pos[2] = { 540, 750 };
    menu5.setPosition(menu5_pos[0], menu5_pos[1]);
    menu5.setScale(0.7f, 0.7f);

    int menu6_pos[2] = { 570, 850 };
    menu6.setPosition(menu6_pos[0], menu6_pos[1]);
    menu6.setScale(0.7f, 0.7f);

    bool isMenu = 1;
    int menu_num = 0;

    while (isMenu)
    {
        int menuNum = 0;

        window.clear(sf::Color::White);

        while (window.isOpen())
        {
            menu1.setColor(Color::Black);
            menu2.setColor(Color::Black);
            menu3.setColor(Color::Black);
            menu4.setColor(Color::Black);
            menu5.setColor(Color::Black);
            menu6.setColor(Color::Black);

            if (IntRect(menu1_pos[0], menu1_pos[1], 400, 50).contains(Mouse::getPosition(window))) 
            { 
                menu1.setColor(Color::Blue);
                menuNum = 1; 
            }
            if (IntRect(menu2_pos[0], menu2_pos[1], 370, 50).contains(Mouse::getPosition(window)))
            {
                menu2.setColor(Color::Blue);
                menuNum = 2; 
            }
            if (IntRect(menu3_pos[0], menu3_pos[1], 650, 50).contains(Mouse::getPosition(window)))
            {
                menu3.setColor(Color::Blue);
                menuNum = 3;
            }
            if (IntRect(menu4_pos[0], menu4_pos[1], 430, 50).contains(Mouse::getPosition(window)))
            {
                menu4.setColor(Color::Blue);
                menuNum = 4;
            }
            if (IntRect(menu5_pos[0], menu5_pos[1], 280, 50).contains(Mouse::getPosition(window)))
            {
                menu5.setColor(Color::Blue);
                menuNum = 5;
            }
            if (IntRect(menu6_pos[0], menu6_pos[1], 220, 50).contains(Mouse::getPosition(window)))
            {
                menu6.setColor(Color::Blue);
                menuNum = 6;
            }


            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu1_pos[0], menu1_pos[1], 400, 50).contains(Mouse::getPosition(window)))
                    game_menu();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu2_pos[0], menu2_pos[1], 370, 50).contains(Mouse::getPosition(window)))
                    difficulty();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu3_pos[0], menu3_pos[1], 660, 50).contains(Mouse::getPosition(window)))
                    records();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu4_pos[0], menu4_pos[1], 430, 50).contains(Mouse::getPosition(window)))
                    about();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu5_pos[0], menu5_pos[1], 280, 50).contains(Mouse::getPosition(window)))
                    faq();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu6_pos[0], menu6_pos[1], 220, 50).contains(Mouse::getPosition(window))) 
                        return;

                if (Keyboard::isKeyPressed(Keyboard::Escape)) 
                    return;
            }

            window.draw(menu1);
            window.draw(menu2);
            window.draw(menu3);
            window.draw(menu4);
            window.draw(menu5);
            window.draw(menu6);

            window.display();
        }
    }

    return;
}

void game_menu()
{
    cout << "NOT READY!\n";
}

void difficulty()
{
    cout << "NOT READY!\n";
}

void records()
{
    cout << "NOT READY!\n";
}

void about()
{
    cout << "NOT READY!\n";
}

void faq()
{
    cout << "NOT READY!\n";
}
