#define _CRT_SECURE_NO_WARNINGS
#define SFML_NO_DEPRECATED_WARNINGS

#include <SFML/Graphics.hpp>
#include "list.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
using namespace sf;

FILE* file;

struct list_node* rec = NULL;

struct dot
{
    int x;
    int y;
};

enum directions {UP, RIGHT, DOWN, LEFT};

void main_menu();
void about();
void faq();
void game();
void you_lose();
void difficulty();
void game_menu();
void game_pvp();
void game_pve();
void game_pause();
void records();

const int max_snake = 3000;
int score1;

int main()
{
	file = fopen("records.txt", "a+");

    setlocale(LC_ALL, "Rus");

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
    window.setPosition(Vector2i(650,100));

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

    int menu3_pos[2] = { 400, 555 };
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

    bool work = 1;
    while (work)
    {
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
                menu1.setColor(Color::Blue);
            if (IntRect(menu2_pos[0], menu2_pos[1], 370, 50).contains(Mouse::getPosition(window)))
                menu2.setColor(Color::Blue);
            if (IntRect(menu3_pos[0], menu3_pos[1], 650, 50).contains(Mouse::getPosition(window)))
                menu3.setColor(Color::Blue);
            if (IntRect(menu4_pos[0], menu4_pos[1], 430, 50).contains(Mouse::getPosition(window)))
                menu4.setColor(Color::Blue);
            if (IntRect(menu5_pos[0], menu5_pos[1], 280, 50).contains(Mouse::getPosition(window)))
                menu5.setColor(Color::Blue);
            if (IntRect(menu6_pos[0], menu6_pos[1], 220, 50).contains(Mouse::getPosition(window)))
                menu6.setColor(Color::Blue);

            Event event;
            while (window.pollEvent(event))
            {
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
                {
                    window.close();
                    work = 0;
                }

                if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
                {
                    window.close();
                    work = 0;
                }

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    work = 0;
                }
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
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture menuTexture[4];
    menuTexture[0].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\1player.png");
    menuTexture[0].setSmooth(true);

    menuTexture[1].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\PVP.png");
    menuTexture[1].setSmooth(true);

    menuTexture[2].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\PVE.png");
    menuTexture[2].setSmooth(true);

    menuTexture[3].loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Back.png");
    menuTexture[3].setSmooth(true);

    Sprite menu1(menuTexture[0]), \
        menu2(menuTexture[1]), \
        menu3(menuTexture[2]), \
        menu4(menuTexture[3]);

    int menu1_pos[2] = { 550, 420 };
    menu1.setPosition(menu1_pos[0], menu1_pos[1]);
    menu1.setScale(0.7f, 0.7f);

    int menu2_pos[2] = { 530, 500 };
    menu2.setPosition(menu2_pos[0], menu2_pos[1]);
    menu2.setScale(0.7f, 0.7f);

    int menu3_pos[2] = { 360, 600 };
    menu3.setPosition(menu3_pos[0], menu3_pos[1]);
    menu3.setScale(0.7f, 0.7f);

    int menu4_pos[2] = { 580, 700 };
    menu4.setPosition(menu4_pos[0], menu4_pos[1]);
    menu4.setScale(0.7f, 0.7f);

    bool work = 1;
    while (work)
    {
        window.clear(sf::Color::White);

        while (window.isOpen())
        {
            menu1.setColor(Color::Black);
            menu2.setColor(Color::Black);
            menu3.setColor(Color::Black);
            menu4.setColor(Color::Black);

            if (IntRect(menu1_pos[0], menu1_pos[1], 280, 50).contains(Mouse::getPosition(window)))
                menu1.setColor(Color::Blue);
            if (IntRect(menu2_pos[0], menu2_pos[1], 330, 50).contains(Mouse::getPosition(window)))
                menu2.setColor(Color::Blue);
            if (IntRect(menu3_pos[0], menu3_pos[1], 670, 50).contains(Mouse::getPosition(window)))
                menu3.setColor(Color::Blue);
            if (IntRect(menu4_pos[0], menu4_pos[1], 220, 50).contains(Mouse::getPosition(window)))
                menu4.setColor(Color::Blue);

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu1_pos[0], menu1_pos[1], 280, 50).contains(Mouse::getPosition(window)))
                    game();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu2_pos[0], menu2_pos[1], 330, 50).contains(Mouse::getPosition(window)))
                    game_pvp();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu3_pos[0], menu3_pos[1], 670, 50).contains(Mouse::getPosition(window)))
                    game_pve();

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu4_pos[0], menu4_pos[1], 220, 50).contains(Mouse::getPosition(window)))
                {
                    window.close();
                    work = 0;
                }

                if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
                {
                    window.close();
                    work = 0;
                }

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    work = 0;
                }
            }

            window.draw(menu1);
            window.draw(menu2);
            window.draw(menu3);
            window.draw(menu4);

            window.display();
        }
    }

    return;
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
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));
    
    Texture headerTexture;
    headerTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\About.png");
    headerTexture.setSmooth(true);

    Sprite header(headerTexture);
    int header_pos[2] = { 500, 50 };
    header.setPosition(header_pos[0], header_pos[1]);
    header.setScale(0.7f, 0.7f);
    header.setColor(Color::Black);

    Texture backTexture;
    backTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Back.png");
    backTexture.setSmooth(true);

    Sprite back_button(backTexture);
    int back_pos[2] = { 600, 900 };
    back_button.setPosition(back_pos[0], back_pos[1]);
    back_button.setScale(0.7f, 0.7f);

    window.clear(Color::White);

    Font font;
    assert(font.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Fonts\\Segoe Print\\segoeprint.ttf"));

    Text text("", font, 40);
    text.setColor(Color::Black);
    text.setString(L"Игра змейка TM\nРазработчики Данилов Денис и Багров Егор,\nгруппа 4851003\\00002, Политех, ИКиЗИ\n2021 год\n");
    text.setPosition(50, 200);

    bool work = 1;
    while (work)
    {
        back_button.setColor(Color::Black);

        if (IntRect(back_pos[0], back_pos[1], 300, 50).contains(Mouse::getPosition(window)))
            back_button.setColor(Color::Blue);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
            {
                window.close();
                work = 0;
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                IntRect(back_pos[0], back_pos[1], 300, 50).contains(Mouse::getPosition(window)))
            {
                window.close();
                work = 0;
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
                work = 0;
            }
        }
        window.draw(header);
        window.draw(text);
        window.draw(back_button);

        window.display();
    }
     
    return;
}

void faq()
{
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture headerTexture;
    headerTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\About.png");
    headerTexture.setSmooth(true);

    Sprite header(headerTexture);
    int header_pos[2] = { 500, 50 };
    header.setPosition(header_pos[0], header_pos[1]);
    header.setScale(0.7f, 0.7f);
    header.setColor(Color::Black);

    Texture backTexture;
    backTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Back.png");
    backTexture.setSmooth(true);

    Sprite back_button(backTexture);
    int back_pos[2] = { 600, 1250 };
    back_button.setPosition(back_pos[0], back_pos[1]);
    back_button.setScale(0.7f, 0.7f);

    window.clear(sf::Color::White);

    Font font;
    assert(font.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Fonts\\Segoe Print\\segoeprint.ttf"));

    Text text("", font, 40);
    text.setColor(Color::Black);
    text.setString(L"-Цель игры: \n Собирать еду, избегая столкновения с собственным\n хвостом и  краями игрового поля.\n\
-Управление в игре: \n Нажмите Q / ESC для выхода. \n Нажмите P для паузы. \n-Перемещение для 1 игрока:\n \
Cтрелки вверх / вниз / влево / вправо.\n-Перемещение для 2 игрока:\n Kлавиши W / A / S / D.\n-Обозначения : \n # --еда\n * **-- 1 змейка\n \
+++ -- 2 змейка\n @ -- препятсвия");
    text.setPosition(50, 200);

    bool work = 1;
    while (work)
    {
        back_button.setColor(Color::Black);

        if (IntRect(back_pos[0], back_pos[1], 300, 50).contains(Mouse::getPosition(window)))
            back_button.setColor(Color::Blue);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
            {
                window.close();
                work = 0;
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                IntRect(back_pos[0], back_pos[1], 300, 50).contains(Mouse::getPosition(window)))
            {
                window.close();
                work = 0;
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
                work = 0;
            }
        }
        window.draw(header);
        window.draw(text);
        window.draw(back_button);

        window.display();
    }

    return;
}

void game()
{
    dot min_pos = { 10, 10 };
    int step = 30;
    dot max_pos = {1400 - step - min_pos.x, 1400 - step - min_pos.y };
    dot food_pos;
    bool eaten = 1;
    score1 = 0;

    RenderWindow window(VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture headUPTexture;
    headUPTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Green_head_UP.png");
    headUPTexture.setSmooth(true);
    Texture headRIGHTTexture;
    headRIGHTTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Green_head_RIGHT.png");
    headRIGHTTexture.setSmooth(true);
    Texture headDOWNTexture;
    headDOWNTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Green_head_DOWN.png");
    headDOWNTexture.setSmooth(true);
    Texture headLEFTTexture;
    headLEFTTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Green_head_LEFT.png");
    headLEFTTexture.setSmooth(true);

    Sprite headUP(headUPTexture);
    headUP.setScale(0.09, 0.09);
    headUP.setOrigin(90, 180);
    Sprite headRIGHT(headRIGHTTexture);
    headRIGHT.setScale(0.09, 0.09);
    headRIGHT.setOrigin(0, 100);
    Sprite headLEFT(headLEFTTexture);
    headLEFT.setScale(0.09, 0.09);
    headLEFT.setOrigin(180, 70);
    Sprite headDOWN(headDOWNTexture);
    headDOWN.setScale(0.09, 0.09);
    headDOWN.setOrigin(90, 0);

    Texture foodTexture;
    foodTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Food.png");
    Sprite food(foodTexture);
    food.setScale(0.03, 0.03);

    Texture pauseTexture;
    pauseTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Pause.png");
    Sprite pauseButton(pauseTexture);
    pauseButton.setScale(0.05, 0.05);
    pauseButton.setPosition(max_pos.x - 2*step, min_pos.y + 1.5*step);

    int snake_len = 3;
    vector <dot> snake(snake_len);
   
    snake[0].x = min_pos.x + 3*step;
    snake[1].x = min_pos.x + 2*step;
    snake[2].x = min_pos.x + step;
    snake[0].y = min_pos.y + step;
    snake[1].y = min_pos.y + step;
    snake[2].y = min_pos.y + step;

    CircleShape snake_item[max_snake];

    directions direction = RIGHT;

    Sprite head = headRIGHT;

    dot tail;

    bool end_game = 0, pause_game = 0;

    bool first = 1, work = 1, dir_changed = 0;
    int cnt = 0, m = 7;
    while (work)
    { 
        if (!end_game && !pause_game)
        {
            window.clear(Color::White);

            for (int i = 1; i < snake_len; i++)
            {
                snake_item[i].setRadius(step / 2);
                snake_item[i].setPosition(snake[i].x, snake[i].y);
                snake_item[i].setFillColor(Color::Green);
            }

            if (eaten)
            {
                srand(time(0));
                food_pos.x = (rand() % ((max_pos.x - min_pos.x) / step - 2)) * step + min_pos.x + step;
                food_pos.y = (rand() % ((max_pos.x - min_pos.x) / step - 2)) * step + min_pos.y + step;
                if (!first)
                {
                    snake.push_back(tail);
                    snake_len++;
                }
                first = false;
                eaten = false;
            }
            food.setPosition(food_pos.x, food_pos.y);

            for (int i = min_pos.x; i <= max_pos.x; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, min_pos.x);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos.x; i <= max_pos.x; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, max_pos.x);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos.y; i <= max_pos.y; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(min_pos.y, i);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos.x; i <= max_pos.x; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(max_pos.y, i);
                border.setFillColor(Color::Black);
                window.draw(border);
            }

            head.setPosition(snake[0].x, snake[0].y);
            window.draw(food);
            window.draw(head);
            for (int i = 1; i < snake_len; i++)
                {
                    window.draw(snake_item[i]);
                }

            if (cnt == m - 1)
            {
                dir_changed = 0;

                tail = snake[snake_len - 1];

                for (int i = snake_len - 1; i > 0; i--)
                {
                    snake[i].x = snake[i - 1].x;
                    snake[i].y = snake[i - 1].y;
                }

                switch (direction)
                {
                    case UP:
                    {
                        snake[0].y -= step;
                        break;
                    }
                    case RIGHT:
                    {
                        snake[0].x += step;
                        break;
                    }
                    case DOWN:
                    {
                        snake[0].y += step;
                        break;
                    }
                    case LEFT:
                    {
                        snake[0].x -= step;
                        break;
                    }
                }

                if (snake[0].x == food_pos.x && snake[0].y == food_pos.y)
                    eaten = true;

                if (snake[0].x == min_pos.x || snake[0].x == max_pos.x || snake[0].y == min_pos.y || snake[0].y == max_pos.y)
                {
                    you_lose();
                    end_game = 1;
                }

                for (int i = 1; i < snake_len; i++)
                    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                    {
                        you_lose();
                        end_game = 1;
                    }
            }

            cnt = (cnt + 1) % m;
           
        }
 
        pauseButton.setColor(Color(0, 0, 0, 100));
        if (IntRect(max_pos.x - 2 * step, min_pos.y + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)))
            pauseButton.setColor(Color::Blue);

        window.draw(pauseButton);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
            {
                window.close();
                work = 0;
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
                work = 0;
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                IntRect(max_pos.x - 2 * step, min_pos.y + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)) || \
                event.type == Event::KeyReleased && event.key.code == Keyboard::P)
            {
                if (pause_game)
                {
                    pause_game = false;
                    pauseButton.setColor(Color(0, 0, 0, 128));
                }
                else
                {
                    pause_game = true;
                    pauseButton.setColor(Color::Black);
                }
            }

            if (!dir_changed)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    if (direction != LEFT)
                    {
                        direction = RIGHT;
                        head = headRIGHT;
                        dir_changed = 1;
                    }
                if (Keyboard::isKeyPressed(Keyboard::Up))
                    if (direction != DOWN)
                    {
                        direction = UP;
                        head = headUP;
                        dir_changed = 1;
                    }
                if (Keyboard::isKeyPressed(Keyboard::Left))
                    if (direction != RIGHT)
                    {
                        direction = LEFT;
                        head = headLEFT;
                        dir_changed = 1;
                    }
                if (Keyboard::isKeyPressed(Keyboard::Down))
                    if (direction != UP)
                    {
                        direction = DOWN;
                        head = headDOWN;
                        dir_changed = 1;
                    }
            }
        }

        window.display();
    }

}

void game_pvp()
{
    cout << "NOT READY!\n";
}

void game_pve()
{
    cout << "NOT READY!\n";
}

void you_lose()
{
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture backTexture;
    backTexture.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Pics\\Back.png");
    backTexture.setSmooth(true);

    Sprite back_button(backTexture);
    int back_pos[2] = { 600, 1250 };
    back_button.setPosition(back_pos[0], back_pos[1]);
    back_button.setScale(0.7f, 0.7f);

    window.clear(sf::Color::White);

    Font font;
    assert(font.loadFromFile("\\\\Mac\\Home\\Desktop\\University\\3 SEM\\Programming languages\\Coursework\\Fonts\\Segoe Print\\segoeprint.ttf"));

    Text text("", font, 60);
    text.setColor(Color::Black);
    text.setString(L"ВЫ ПРОИГРАЛИ!");
    text.setPosition(200, 200);

    bool work = 1;
    while (work)
    {
        back_button.setColor(Color::Black);

        if (IntRect(back_pos[0], back_pos[1], 300, 50).contains(Mouse::getPosition(window)))
            back_button.setColor(Color::Blue);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
            {
                window.close();
                work = 0;
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                IntRect(back_pos[0], back_pos[1], 300, 50).contains(Mouse::getPosition(window)))
            {
                window.close();
                work = 0;
            }

            if (event.type == sf::Event::Closed)
            {
                window.close();
                work = 0;
            }
        }

        window.draw(text);
        window.draw(back_button);

        window.display();
    }

    return;
}
