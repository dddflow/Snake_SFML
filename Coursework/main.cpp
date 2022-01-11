#define _CRT_SECURE_NO_WARNINGS
#define SFML_NO_DEPRECATED_WARNINGS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <vector>
#include <windows.h>
#include <set>
#include <fstream>


using namespace std;
using namespace sf;

struct dot
{
    int x;
    int y;
};

enum directions {UP, RIGHT, DOWN, LEFT};

enum fails {LOSE, WIN, DRAW, WIN1, WIN2, DRAW1};

enum diff {EASY = 99, MID = 66, HARD = 33};

void main_menu();
void about();
void faq();
void game();
void you_lose(fails f);
void difficulty();
void game_menu();
void game_pvp();
void game_pve();
void records();

int score1, score2, m = MID;
string player_name;

multiset <pair <int, string>, greater < pair <int, string >>> rec;

clock_t start, stop;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream fin("records.txt");

    string name = "";
    int sc = 0;
    while (fin >> sc >> name)
        rec.insert({sc, name});

    cout << "Представьтесь на английском :)\n";
    cin >> player_name;

	main_menu();

	return 0;
}

void main_menu()
{
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650,100));

    Texture menuTexture[6];
    menuTexture[0].loadFromFile("Pics\\NewGame.png");
    menuTexture[0].setSmooth(true);

    menuTexture[1].loadFromFile("Pics\\Difficulty.png");
    menuTexture[1].setSmooth(true);

    menuTexture[2].loadFromFile("Pics\\Records.png");
    menuTexture[2].setSmooth(true);

    menuTexture[3].loadFromFile("Pics\\About.png");
    menuTexture[3].setSmooth(true);

    menuTexture[4].loadFromFile("Pics\\FAQ.png");
    menuTexture[4].setSmooth(true);

    menuTexture[5].loadFromFile("Pics\\Exit.png");
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
    menuTexture[0].loadFromFile("Pics\\1player.png");
    menuTexture[0].setSmooth(true);

    menuTexture[1].loadFromFile("Pics\\PVP.png");
    menuTexture[1].setSmooth(true);

    menuTexture[2].loadFromFile("Pics\\PVE.png");
    menuTexture[2].setSmooth(true);

    menuTexture[3].loadFromFile("Pics\\Back.png");
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
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture menuTexture[4];
    menuTexture[0].loadFromFile("Pics\\Easy.png");
    menuTexture[0].setSmooth(true);

    menuTexture[1].loadFromFile("Pics\\Medium.png");
    menuTexture[1].setSmooth(true);

    menuTexture[2].loadFromFile("Pics\\Hard.png");
    menuTexture[2].setSmooth(true);

    menuTexture[3].loadFromFile("Pics\\Back.png");
    menuTexture[3].setSmooth(true);

    Sprite menu1(menuTexture[0]), \
        menu2(menuTexture[1]), \
        menu3(menuTexture[2]), \
        menu4(menuTexture[3]);

    int menu1_pos[2] = { 550, 420 };
    menu1.setPosition(menu1_pos[0], menu1_pos[1]);
    menu1.setScale(0.7f, 0.7f);

    int menu2_pos[2] = { 550, 500 };
    menu2.setPosition(menu2_pos[0], menu2_pos[1]);
    menu2.setScale(0.7f, 0.7f);

    int menu3_pos[2] = { 540, 600 };
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

            switch (m)
            {
            case HARD:
            {
                menu3.setColor(Color::Blue);
                break;
            }
            case MID:
            {
                menu2.setColor(Color::Blue);
                break;
            }
            case EASY:
            {
                menu1.setColor(Color::Blue);
                break;
            }
            }

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
                    m = EASY;

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu2_pos[0], menu2_pos[1], 330, 50).contains(Mouse::getPosition(window)))
                    m = MID;

                if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left && \
                    IntRect(menu3_pos[0], menu3_pos[1], 670, 50).contains(Mouse::getPosition(window)))
                    m = HARD;

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

void records()
{
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture headerTexture;
    headerTexture.loadFromFile("Pics\\Records.png");
    headerTexture.setSmooth(true);

    Sprite header(headerTexture);
    int header_pos[2] = { 400, 50 };
    header.setPosition(header_pos[0], header_pos[1]);
    header.setScale(0.7f, 0.7f);
    header.setColor(Color::Black);

    Texture backTexture;
    backTexture.loadFromFile("Pics\\Back.png");
    backTexture.setSmooth(true);

    Sprite back_button(backTexture);
    int back_pos[2] = { 600, 1200 };
    back_button.setPosition(back_pos[0], back_pos[1]);
    back_button.setScale(0.7f, 0.7f);

    window.clear(Color::White);

    Font font;
    assert(font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf"));
    font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf");


    Text text[2][10];
    for (int i = 0; i < 10; i++)
    {
        text[0][i].setFont(font);
        text[1][i].setFont(font);
        text[0][i].setCharacterSize(40);
        text[1][i].setCharacterSize(40);
        text[0][i].setPosition(200, 50 + 100 * (i + 1));
        text[1][i].setPosition(1000, 50 + 100 * (i + 1));
        text[0][i].setColor(Color::Black);
        text[1][i].setColor(Color::Black);
    }

    int cnt = 0;
    for (auto p : rec)
    {
        text[0][cnt].setString(p.second);
        text[1][cnt].setString(to_string(p.first));
        cnt++;
        if (cnt == 10) break;
    }

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
        window.draw(back_button);
        for (int i = 0; i < 10; i++)
        {
            window.draw(text[0][i]);
            window.draw(text[1][i]);
        }

        window.display();
    }

    return;
}

void about()
{
    RenderWindow window(sf::VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));
    
    Texture headerTexture;
    headerTexture.loadFromFile("Pics\\About.png");
    headerTexture.setSmooth(true);

    Sprite header(headerTexture);
    int header_pos[2] = { 500, 50 };
    header.setPosition(header_pos[0], header_pos[1]);
    header.setScale(0.7f, 0.7f);
    header.setColor(Color::Black);

    Texture backTexture;
    backTexture.loadFromFile("Pics\\Back.png");
    backTexture.setSmooth(true);

    Sprite back_button(backTexture);
    int back_pos[2] = { 600, 900 };
    back_button.setPosition(back_pos[0], back_pos[1]);
    back_button.setScale(0.7f, 0.7f);

    window.clear(Color::White);

    Font font;
    assert(font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf"));
    font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf");


    Text text("", font, 40);
    text.setColor(Color::Black);
    text.setString(L"Игра змейка TM\nРазработчики Данилов Денис и Багров Егор,\nгруппа 4851003\\00002, Политех, ИКиЗИ\n2021/22 год\n");
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
    headerTexture.loadFromFile("Pics\\About.png");
    headerTexture.setSmooth(true);

    Sprite header(headerTexture);
    int header_pos[2] = { 500, 50 };
    header.setPosition(header_pos[0], header_pos[1]);
    header.setScale(0.7f, 0.7f);
    header.setColor(Color::Black);

    Texture backTexture;
    backTexture.loadFromFile("Pics\\Back.png");
    backTexture.setSmooth(true);

    Sprite back_button(backTexture);
    int back_pos[2] = { 600, 1250 };
    back_button.setPosition(back_pos[0], back_pos[1]);
    back_button.setScale(0.7f, 0.7f);

    window.clear(Color::White);

    Font font;
    assert(font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf"));
    font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf");

    Text text("", font, 40);
    text.setColor(Color::Black);
    text.setString(L"-Цель игры: \n Собирать еду, избегая столкновения с собственным\n хвостом и  краями игрового поля.\n\
-Управление в игре: \n Нажмите ESC для выхода. \n Нажмите P для паузы. \n-Перемещение для зелёной змеи:\n \
Cтрелки вверх / вниз / влево / вправо.\n-Перемещение для красной змеи:\n Kлавиши W / A / S / D.\n");
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
    int min_pos = 10;
    int step = 30;
    int max_pos = 1400 - step - min_pos;
    dot food_pos;
    bool eaten = 1;
    score1 = 0;

    RenderWindow window(VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture headUPTexture;
    headUPTexture.loadFromFile("Pics\\Green_head_UP.png");
    headUPTexture.setSmooth(true);
    Texture headRIGHTTexture;
    headRIGHTTexture.loadFromFile("Pics\\Green_head_RIGHT.png");
    headRIGHTTexture.setSmooth(true);
    Texture headDOWNTexture;
    headDOWNTexture.loadFromFile("Pics\\Green_head_DOWN.png");
    headDOWNTexture.setSmooth(true);
    Texture headLEFTTexture;
    headLEFTTexture.loadFromFile("Pics\\Green_head_LEFT.png");
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
    foodTexture.loadFromFile("Pics\\Food.png");
    Sprite food(foodTexture);
    food.setScale(0.03, 0.03);

    Texture pauseTexture;
    pauseTexture.loadFromFile("Pics\\Pause.png");
    Sprite pauseButton(pauseTexture);
    pauseButton.setScale(0.05, 0.05);
    pauseButton.setPosition(max_pos - 2*step, min_pos + 1.5*step);

    Font font;
    assert(font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf"));
    font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf");


    Text score1_value("", font, 60);
    score1_value.setPosition(min_pos + 1.5 * step, min_pos + step);
    score1_value.setColor(Color(0, 0, 0, 100));


    int snake_len = 3;
    vector <dot> snake(snake_len);
   
    snake[0].x = min_pos + 3 * step;
    snake[1].x = min_pos + 2*step;
    snake[2].x = min_pos + step;
    snake[0].y = min_pos + step;
    snake[1].y = min_pos + step;
    snake[2].y = min_pos + step;

    vector <CircleShape> snake_item (snake_len);

    directions direction = RIGHT;

    Sprite head = headRIGHT;

    dot tail;

    bool end_game = 0, pause_game = 0;

    bool first = 1, work = 1, dir_changed = 0;
    int cnt = 0;

   
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
                
                bool find = true;
                while (find)
                {
                    food_pos.x = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;
                    food_pos.y = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;

                    find = false;
                    for (int i = 0; i < snake_len; i++)
                        if (snake[i].x == food_pos.x && snake[i].y == food_pos.y)
                            find = true;
                }

                if (!first)
                {
                    snake.push_back(tail);
                    snake_item.push_back(snake_item[snake_len - 1]);
                    snake_len++;
                }
                first = false;
                eaten = false;
            }
            food.setPosition(food_pos.x, food_pos.y);

            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, min_pos);
                border.setFillColor(Color::Black);
                window.draw(border);

            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, max_pos);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(min_pos, i);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(max_pos, i);
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
                {
                    __asm
                    {
                        mov ah, eaten
                        mov ah, 1
                        mov eaten, ah

                        mov eax, score1
                        add eax, 7
                        mov score1, eax
                    }
                }

                if (snake[0].x == min_pos || snake[0].x == max_pos || snake[0].y == min_pos || snake[0].y == max_pos)
                {
                    you_lose(LOSE);
                    end_game = 1;
                }

                for (int i = 1; i < snake_len; i++)
                    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                    {
                        you_lose(LOSE);
                        end_game = 1;
                    }
            }

            cnt = (cnt + 1) % m;
           
        }
 
        pauseButton.setColor(Color(0, 0, 0, 100));
        if (IntRect(max_pos - 2 * step, min_pos + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)))
            pauseButton.setColor(Color::Blue);
        window.draw(pauseButton);

        score1_value.setString(to_string(score1));
        window.draw(score1_value);

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
                IntRect(max_pos - 2 * step, min_pos + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)) || \
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
                if (Keyboard::isKeyPressed(Keyboard::Right) && direction != LEFT)
                {
                    direction = RIGHT;
                    head = headRIGHT;
                    dir_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up) && direction != DOWN)
                {
                    direction = UP;
                    head = headUP;
                    dir_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Left) && direction != RIGHT)
                {
                    direction = LEFT;
                    head = headLEFT;
                    dir_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down) && direction != UP)
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
    int min_pos = 10;
    int step = 30;
    int max_pos = 1400 - step - min_pos;
    dot food_pos;
    bool eaten1 = 1, eaten2 = 1;
    score1 = 0;
    score2 = 0;

    RenderWindow window(VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture head1UPTexture;
    head1UPTexture.loadFromFile("Pics\\Green_head_UP.png");
    head1UPTexture.setSmooth(true);
    Texture head1RIGHTTexture;
    head1RIGHTTexture.loadFromFile("Pics\\Green_head_RIGHT.png");
    head1RIGHTTexture.setSmooth(true);
    Texture head1DOWNTexture;
    head1DOWNTexture.loadFromFile("Pics\\Green_head_DOWN.png");
    head1DOWNTexture.setSmooth(true);
    Texture head1LEFTTexture;
    head1LEFTTexture.loadFromFile("Pics\\Green_head_LEFT.png");
    head1LEFTTexture.setSmooth(true);

    Sprite head1UP(head1UPTexture);
    head1UP.setScale(0.09, 0.09);
    head1UP.setOrigin(90, 180);
    Sprite head1RIGHT(head1RIGHTTexture);
    head1RIGHT.setScale(0.09, 0.09);
    head1RIGHT.setOrigin(0, 100);
    Sprite head1LEFT(head1LEFTTexture);
    head1LEFT.setScale(0.09, 0.09);
    head1LEFT.setOrigin(180, 70);
    Sprite head1DOWN(head1DOWNTexture);
    head1DOWN.setScale(0.09, 0.09);
    head1DOWN.setOrigin(90, 0);

    Texture head2UPTexture;
    head2UPTexture.loadFromFile("Pics\\Red_head_UP.png");
    head2UPTexture.setSmooth(true);
    Texture head2RIGHTTexture;
    head2RIGHTTexture.loadFromFile("Pics\\Red_head_RIGHT.png");
    head2RIGHTTexture.setSmooth(true);
    Texture head2DOWNTexture;
    head2DOWNTexture.loadFromFile("Pics\\Red_head_DOWN.png");
    head2DOWNTexture.setSmooth(true);
    Texture head2LEFTTexture;
    head2LEFTTexture.loadFromFile("Pics\\Red_head_LEFT.png");
    head2LEFTTexture.setSmooth(true);

    Sprite head2UP(head2UPTexture);
    head2UP.setScale(0.09, 0.09);
    head2UP.setOrigin(90, 180);
    Sprite head2RIGHT(head2RIGHTTexture);
    head2RIGHT.setScale(0.09, 0.09);
    head2RIGHT.setOrigin(0, 100);
    Sprite head2LEFT(head2LEFTTexture);
    head2LEFT.setScale(0.09, 0.09);
    head2LEFT.setOrigin(180, 70);
    Sprite head2DOWN(head2DOWNTexture);
    head2DOWN.setScale(0.09, 0.09);
    head2DOWN.setOrigin(90, 0);

    Texture foodTexture;
    foodTexture.loadFromFile("Pics\\Food.png");
    Sprite food(foodTexture);
    food.setScale(0.03, 0.03);

    Texture pauseTexture;
    pauseTexture.loadFromFile("Pics\\Pause.png");
    Sprite pauseButton(pauseTexture);
    pauseButton.setScale(0.05, 0.05);
    pauseButton.setPosition(max_pos - 2 * step, min_pos + 1.5 * step);

    Font font;
    assert(font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf"));
    font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf");

    Text score1_value("", font, 60);
    score1_value.setPosition(min_pos + 1.5 * step, min_pos + step);
    score1_value.setColor(Color(0, 0, 0, 100));

    Text score2_value("", font, 60);
    score2_value.setPosition(min_pos + 1.5 * step, min_pos + 3*step);
    score2_value.setColor(Color(0, 0, 0, 100));

    int snake1_len = 3;
    vector <dot> snake1(snake1_len);
    snake1[0].x = min_pos + 3 * step;
    snake1[1].x = min_pos + 2 * step;
    snake1[2].x = min_pos + step;
    snake1[0].y = min_pos + step;
    snake1[1].y = min_pos + step;
    snake1[2].y = min_pos + step;

    int snake2_len = 3;
    vector <dot> snake2(snake2_len);
    snake2[0].x = min_pos + 3 * step;
    snake2[1].x = min_pos + 2 * step;
    snake2[2].x = min_pos + step;
    snake2[0].y = max_pos - step;
    snake2[1].y = max_pos - step;
    snake2[2].y = max_pos - step;

    vector <CircleShape> snake1_item (snake1_len);
    vector <CircleShape> snake2_item (snake2_len);


    directions direction1 = RIGHT, direction2 = RIGHT;

    Sprite head1 = head1RIGHT;
    Sprite head2 = head2RIGHT;

    dot tail1, tail2;

    bool end_game = 0, pause_game = 0;

    bool first1 = 1, first2 = 1, work = 1, dir1_changed = 0, dir2_changed = 0;
    int cnt = 0;

    while (work)
    {
        if (!end_game && !pause_game)
        {
            window.clear(Color::White);

            for (int i = 1; i < snake1_len; i++)
            {
                snake1_item[i].setRadius(step / 2);
                snake1_item[i].setPosition(snake1[i].x, snake1[i].y);
                snake1_item[i].setFillColor(Color::Green);
            }
            for (int i = 1; i < snake2_len; i++)
            {
                snake2_item[i].setRadius(step / 2);
                snake2_item[i].setPosition(snake2[i].x, snake2[i].y);
                snake2_item[i].setFillColor(Color::Red);
            }

            if (eaten1)
            {
                srand(time(0));

                bool find = true;
                while (find)
                {
                    food_pos.x = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;
                    food_pos.y = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;

                    find = false;
                    for (int i = 0; i < snake1_len; i++)
                        if (snake1[i].x == food_pos.x && snake1[i].y == food_pos.y) find = true;
                    for (int i = 0; i < snake2_len; i++)
                        if (snake2[i].x == food_pos.x && snake2[i].y == food_pos.y) find = true;
                }
                if (!first1)
                {
                    snake1.push_back(tail1);
                    snake1_item.push_back(snake1_item[snake1_len-1]);
                    snake1_len++;
                }
                first1 = false;
                eaten1 = false;
            }
            if(eaten2)
            {
                srand(time(0));

                bool find = true;
                while (find)
                {
                    food_pos.x = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;
                    food_pos.y = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;

                    find = false;
                    for (int i = 0; i < snake1_len; i++) 
                        if (snake1[i].x == food_pos.x && snake1[i].y == food_pos.y) find = true;
                    for (int i = 0; i < snake2_len; i++)
                        if (snake2[i].x == food_pos.x && snake2[i].y == food_pos.y) find = true;
                }
                if (!first2)
                {
                    snake2.push_back(tail2);
                    snake2_item.push_back(snake2_item[snake2_len - 1]);
                    snake2_len++;
                }
                first2 = false;
                eaten2 = false;
            }
            food.setPosition(food_pos.x, food_pos.y);

            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, min_pos);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, max_pos);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(min_pos, i);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(max_pos, i);
                border.setFillColor(Color::Black);
                window.draw(border);
            }

            window.draw(food);

            head1.setPosition(snake1[0].x, snake1[0].y);
            window.draw(head1);
            for (int i = 1; i < snake1_len; i++)
            {
                window.draw(snake1_item[i]);
            }

            head2.setPosition(snake2[0].x, snake2[0].y);
            window.draw(head2);
            for (int i = 1; i < snake2_len; i++)
            {
                window.draw(snake2_item[i]);
            }

            if (cnt == m - 1)
            {
                dir1_changed = 0;
                dir2_changed = 0;

                tail1 = snake1[snake1_len - 1];
                for (int i = snake1_len - 1; i > 0; i--)
                {
                    snake1[i].x = snake1[i - 1].x;
                    snake1[i].y = snake1[i - 1].y;
                }

                tail2 = snake2[snake2_len - 1];
                for (int i = snake2_len - 1; i > 0; i--)
                {
                    snake2[i].x = snake2[i - 1].x;
                    snake2[i].y = snake2[i - 1].y;
                }

                switch (direction1)
                {
                case UP:
                {
                    snake1[0].y -= step;
                    break;
                }
                case RIGHT:
                {
                    snake1[0].x += step;
                    break;
                }
                case DOWN:
                {
                    snake1[0].y += step;
                    break;
                }
                case LEFT:
                {
                    snake1[0].x -= step;
                    break;
                }
                }

                switch (direction2)
                {
                case UP:
                {
                    snake2[0].y -= step;
                    break;
                }
                case RIGHT:
                {
                    snake2[0].x += step;
                    break;
                }
                case DOWN:
                {
                    snake2[0].y += step;
                    break;
                }
                case LEFT:
                {
                    snake2[0].x -= step;
                    break;
                }
                }

                if (snake1[0].x == food_pos.x && snake1[0].y == food_pos.y)
                {
                    eaten1 = true;
                    score1 += 7;
                }

                if (snake2[0].x == food_pos.x && snake2[0].y == food_pos.y)
                {
                    eaten2 = true;
                    score2 += 7;
                }

                bool lose1 = false, lose2 = false;

                if (snake1[0].x == min_pos || snake1[0].x == max_pos || snake1[0].y == min_pos || snake1[0].y == max_pos)
                {
                    lose1 = true;
                    end_game = 1;
                }
                if (snake2[0].x == min_pos || snake2[0].x == max_pos || snake2[0].y == min_pos || snake2[0].y == max_pos)
                {
                    lose2 = true;
                    end_game = 1;
                }
                for (int i = 1; i < snake1_len; i++)
                    if (snake1[0].x == snake1[i].x && snake1[0].y == snake1[i].y)
                    {
                        lose1 = true;
                        end_game = 1;
                    }
                for (int i = 1; i < snake2_len; i++)
                    if (snake2[0].x == snake2[i].x && snake2[0].y == snake2[i].y)
                    {
                        lose2 = true;
                        end_game = 1;
                    }
                for (int i = 0; i < snake1_len; i++)
                    if (snake2[0].x == snake1[i].x && snake2[0].y == snake1[i].y)
                    {
                        lose2 = true;
                        end_game = 1;
                    }
                for (int i = 0; i < snake2_len; i++)
                    if (snake1[0].x == snake2[i].x && snake1[0].y == snake2[i].y)
                    {
                        lose1 = true;
                        end_game = 1;
                    }

                if (lose1 && lose2) you_lose(DRAW);
                else if (lose1) you_lose(WIN1);
                else if (lose2) you_lose(WIN2);
            }
            cnt = (cnt + 1) % m;
        }

        pauseButton.setColor(Color(0, 0, 0, 100));
        if (IntRect(max_pos - 2 * step, min_pos + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)))
            pauseButton.setColor(Color::Blue);
        window.draw(pauseButton);

        score1_value.setString(to_string(score1));
        window.draw(score1_value);

        score2_value.setString(to_string(score2));
        window.draw(score2_value);

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
                IntRect(max_pos - 2 * step, min_pos + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)) || \
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

            if (!dir1_changed)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right) && direction1 != LEFT)
                {
                    direction1 = RIGHT;
                    head1 = head1RIGHT;
                    dir1_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up) && direction1 != DOWN)
                {
                    direction1 = UP;
                    head1 = head1UP;
                    dir1_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Left) && direction1 != RIGHT)
                {
                    direction1 = LEFT;
                    head1 = head1LEFT;
                    dir1_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down) && direction1 != UP)
                {
                    direction1 = DOWN;
                    head1 = head1DOWN;
                    dir1_changed = 1;
                }
            }

            if (!dir2_changed)
            {
                if (Keyboard::isKeyPressed(Keyboard::D) && direction2 != LEFT)
                {
                    direction2 = RIGHT;
                    head2 = head2RIGHT;
                    dir2_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::W) && direction2 != DOWN)
                {
                    direction2 = UP;
                    head2 = head2UP;
                    dir2_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::A) && direction2 != RIGHT)
                {
                    direction2 = LEFT;
                    head2 = head2LEFT;
                    dir2_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::S) && direction2 != UP)
                {
                    direction2 = DOWN;
                    head2 = head2DOWN;
                    dir2_changed = 1;
                }
            }
        }

        window.display();
    }

}

void game_pve()
{
    int min_pos = 10;
    int step = 30;
    int max_pos = 1400 - step - min_pos;
    dot food_pos;
    bool eaten1 = 1, eaten2 = 1;
    score1 = 0;
    score2 = 0;

    RenderWindow window(VideoMode(1400, 1400), "Snake");
    window.setPosition(Vector2i(650, 100));

    Texture head1UPTexture;
    head1UPTexture.loadFromFile("Pics\\Green_head_UP.png");
    head1UPTexture.setSmooth(true);
    Texture head1RIGHTTexture;
    head1RIGHTTexture.loadFromFile("Pics\\Green_head_RIGHT.png");
    head1RIGHTTexture.setSmooth(true);
    Texture head1DOWNTexture;
    head1DOWNTexture.loadFromFile("Pics\\Green_head_DOWN.png");
    head1DOWNTexture.setSmooth(true);
    Texture head1LEFTTexture;
    head1LEFTTexture.loadFromFile("Pics\\Green_head_LEFT.png");
    head1LEFTTexture.setSmooth(true);

    Sprite head1UP(head1UPTexture);
    head1UP.setScale(0.09, 0.09);
    head1UP.setOrigin(90, 180);
    Sprite head1RIGHT(head1RIGHTTexture);
    head1RIGHT.setScale(0.09, 0.09);
    head1RIGHT.setOrigin(0, 100);
    Sprite head1LEFT(head1LEFTTexture);
    head1LEFT.setScale(0.09, 0.09);
    head1LEFT.setOrigin(180, 70);
    Sprite head1DOWN(head1DOWNTexture);
    head1DOWN.setScale(0.09, 0.09);
    head1DOWN.setOrigin(90, 0);

    Texture head2UPTexture;
    head2UPTexture.loadFromFile("Pics\\Red_head_UP.png");
    head2UPTexture.setSmooth(true);
    Texture head2RIGHTTexture;
    head2RIGHTTexture.loadFromFile("Pics\\Red_head_RIGHT.png");
    head2RIGHTTexture.setSmooth(true);
    Texture head2DOWNTexture;
    head2DOWNTexture.loadFromFile("Pics\\Red_head_DOWN.png");
    head2DOWNTexture.setSmooth(true);
    Texture head2LEFTTexture;
    head2LEFTTexture.loadFromFile("Pics\\Red_head_LEFT.png");
    head2LEFTTexture.setSmooth(true);

    Sprite head2UP(head2UPTexture);
    head2UP.setScale(0.09, 0.09);
    head2UP.setOrigin(90, 180);
    Sprite head2RIGHT(head2RIGHTTexture);
    head2RIGHT.setScale(0.09, 0.09);
    head2RIGHT.setOrigin(0, 100);
    Sprite head2LEFT(head2LEFTTexture);
    head2LEFT.setScale(0.09, 0.09);
    head2LEFT.setOrigin(180, 70);
    Sprite head2DOWN(head2DOWNTexture);
    head2DOWN.setScale(0.09, 0.09);
    head2DOWN.setOrigin(90, 0);

    Texture foodTexture;
    foodTexture.loadFromFile("Pics\\Food.png");
    Sprite food(foodTexture);
    food.setScale(0.03, 0.03);

    Texture pauseTexture;
    pauseTexture.loadFromFile("Pics\\Pause.png");
    Sprite pauseButton(pauseTexture);
    pauseButton.setScale(0.05, 0.05);
    pauseButton.setPosition(max_pos - 2 * step, min_pos + 1.5 * step);

    Font font;
    assert(font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf"));
    font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf");

    Text score1_value("", font, 60);
    score1_value.setPosition(min_pos + 1.5 * step, min_pos + step);
    score1_value.setColor(Color(0, 0, 0, 100));

    Text score2_value("", font, 60);
    score2_value.setPosition(min_pos + 1.5 * step, min_pos + 3 * step);
    score2_value.setColor(Color(0, 0, 0, 100));

    int snake1_len = 3;
    vector <dot> snake1(snake1_len);
    snake1[0].x = min_pos + 3 * step;
    snake1[1].x = min_pos + 2 * step;
    snake1[2].x = min_pos + step;
    snake1[0].y = min_pos + step;
    snake1[1].y = min_pos + step;
    snake1[2].y = min_pos + step;

    int snake2_len = 3;
    vector <dot> snake2(snake2_len);
    snake2[0].x = min_pos + 3 * step;
    snake2[1].x = min_pos + 2 * step;
    snake2[2].x = min_pos + step;
    snake2[0].y = max_pos - step;
    snake2[1].y = max_pos - step;
    snake2[2].y = max_pos - step;

    vector <CircleShape> snake1_item(snake1_len);
    vector <CircleShape> snake2_item(snake2_len);


    directions direction1 = RIGHT, direction2 = RIGHT;

    Sprite head1 = head1RIGHT;
    Sprite head2 = head2RIGHT;

    dot tail1, tail2;

    bool end_game = 0, pause_game = 0;

    bool first1 = 1, first2 = 1, work = 1, dir1_changed = 0, dir2_changed = 0;
    int cnt = 0;

    while (work)
    {
        if (!end_game && !pause_game)
        {
            window.clear(Color::White);

            for (int i = 1; i < snake1_len; i++)
            {
                snake1_item[i].setRadius(step / 2);
                snake1_item[i].setPosition(snake1[i].x, snake1[i].y);
                snake1_item[i].setFillColor(Color::Green);
            }
            for (int i = 1; i < snake2_len; i++)
            {
                snake2_item[i].setRadius(step / 2);
                snake2_item[i].setPosition(snake2[i].x, snake2[i].y);
                snake2_item[i].setFillColor(Color::Red);
            }

            if (eaten1)
            {
                srand(time(0));

                bool find = true;
                while (find)
                {
                    food_pos.x = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;
                    food_pos.y = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;

                    find = false;
                    for (int i = 0; i < snake1_len; i++)
                        if (snake1[i].x == food_pos.x && snake1[i].y == food_pos.y) find = true;
                    for (int i = 0; i < snake2_len; i++)
                        if (snake2[i].x == food_pos.x && snake2[i].y == food_pos.y) find = true;
                }
                if (!first1)
                {
                    snake1.push_back(tail1);
                    snake1_item.push_back(snake1_item[snake1_len - 1]);
                    snake1_len++;
                }
                first1 = false;
                eaten1 = false;
            }
            if (eaten2)
            {
                srand(time(0));

                bool find = true;
                while (find)
                {
                    food_pos.x = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;
                    food_pos.y = (rand() % ((max_pos - min_pos) / step - 2)) * step + min_pos + step;

                    find = false;
                    for (int i = 0; i < snake1_len; i++)
                        if (snake1[i].x == food_pos.x && snake1[i].y == food_pos.y) find = true;
                    for (int i = 0; i < snake2_len; i++)
                        if (snake2[i].x == food_pos.x && snake2[i].y == food_pos.y) find = true;
                }
                if (!first2)
                {
                    snake2.push_back(tail2);
                    snake2_item.push_back(snake2_item[snake2_len - 1]);
                    snake2_len++;
                }
                first2 = false;
                eaten2 = false;
            }
            food.setPosition(food_pos.x, food_pos.y);

            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, min_pos);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(i, max_pos);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(min_pos, i);
                border.setFillColor(Color::Black);
                window.draw(border);
            }
            for (int i = min_pos; i <= max_pos; i += step)
            {
                RectangleShape border(Vector2f(step, step));
                border.setPosition(max_pos, i);
                border.setFillColor(Color::Black);
                window.draw(border);
            }

            window.draw(food);

            head1.setPosition(snake1[0].x, snake1[0].y);
            window.draw(head1);
            for (int i = 1; i < snake1_len; i++)
            {
                window.draw(snake1_item[i]);
            }

            head2.setPosition(snake2[0].x, snake2[0].y);
            window.draw(head2);
            for (int i = 1; i < snake2_len; i++)
            {
                window.draw(snake2_item[i]);
            }

            if (cnt == m - 1)
            {
                dir1_changed = 0;
                dir2_changed = 0;

                tail1 = snake1[snake1_len - 1];
                for (int i = snake1_len - 1; i > 0; i--)
                {
                    snake1[i].x = snake1[i - 1].x;
                    snake1[i].y = snake1[i - 1].y;
                }

                tail2 = snake2[snake2_len - 1];
                for (int i = snake2_len - 1; i > 0; i--)
                {
                    snake2[i].x = snake2[i - 1].x;
                    snake2[i].y = snake2[i - 1].y;
                }

                switch (direction1)
                {
                case UP:
                {
                    snake1[0].y -= step;
                    break;
                }
                case RIGHT:
                {
                    snake1[0].x += step;
                    break;
                }
                case DOWN:
                {
                    snake1[0].y += step;
                    break;
                }
                case LEFT:
                {
                    snake1[0].x -= step;
                    break;
                }
                }

                switch (direction2)
                {
                case UP:
                {
                    snake2[0].y -= step;
                    break;
                }
                case RIGHT:
                {
                    snake2[0].x += step;
                    break;
                }
                case DOWN:
                {
                    snake2[0].y += step;
                    break;
                }
                case LEFT:
                {
                    snake2[0].x -= step;
                    break;
                }
                }

                if (snake1[0].x == food_pos.x && snake1[0].y == food_pos.y)
                {
                    eaten1 = true;
                    score1 += 7;
                }

                if (snake2[0].x == food_pos.x && snake2[0].y == food_pos.y)
                {
                    eaten2 = true;
                    score2 += 7;
                }

                bool lose1 = false, lose2 = false;

                if (snake1[0].x == min_pos || snake1[0].x == max_pos || snake1[0].y == min_pos || snake1[0].y == max_pos)
                {
                    lose1 = true;
                    end_game = 1;
                }
                if (snake2[0].x == min_pos || snake2[0].x == max_pos || snake2[0].y == min_pos || snake2[0].y == max_pos)
                {
                    lose2 = true;
                    end_game = 1;
                }
                for (int i = 1; i < snake1_len; i++)
                    if (snake1[0].x == snake1[i].x && snake1[0].y == snake1[i].y)
                    {
                        lose1 = true;
                        end_game = 1;
                    }
                for (int i = 1; i < snake2_len; i++)
                    if (snake2[0].x == snake2[i].x && snake2[0].y == snake2[i].y)
                    {
                        lose2 = true;
                        end_game = 1;
                    }
                for (int i = 0; i < snake1_len; i++)
                    if (snake2[0].x == snake1[i].x && snake2[0].y == snake1[i].y)
                    {
                        lose2 = true;
                        end_game = 1;
                    }
                for (int i = 0; i < snake2_len; i++)
                    if (snake1[0].x == snake2[i].x && snake1[0].y == snake2[i].y)
                    {
                        lose1 = true;
                        end_game = 1;
                    }

                if (lose1 && lose2) you_lose(DRAW1);
                else if (lose1) you_lose(LOSE);
                else if (lose2) you_lose(WIN);
            }
            cnt = (cnt + 1) % m;
        }

        pauseButton.setColor(Color(0, 0, 0, 100));
        if (IntRect(max_pos - 2 * step, min_pos + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)))
            pauseButton.setColor(Color::Blue);
        window.draw(pauseButton);

        score1_value.setString(to_string(score1));
        window.draw(score1_value);

        score2_value.setString(to_string(score2));
        window.draw(score2_value);

        //////////////// AI_SNAKE
        if (!dir2_changed)
        {
            if (food_pos.x < snake2[0].x && direction2 != RIGHT)
            {
                direction2 = LEFT;
                head2 = head2LEFT;
                dir2_changed = 1;
            }
            else if (food_pos.x > snake2[0].x && direction2 != LEFT)
            {
                direction2 = RIGHT;
                head2 = head2RIGHT;
                dir2_changed = 1;
            }
            else if (food_pos.y < snake2[0].y && direction2 != DOWN)
            {
                direction2 = UP;
                head2 = head2UP;
                dir2_changed = 1;
            }
            else if (food_pos.y > snake2[0].y && direction2 != UP)
            {
                direction2 = DOWN;
                head2 = head2DOWN;
                dir2_changed = 1;
            }

            if ((snake2[0].x - step == min_pos || snake2[0].x + step == max_pos) && (direction2 == RIGHT || direction2 == LEFT))
            {
                if (snake2[0].y - step != min_pos)
                {
                    bool temp = true;
                    for (int i = 0; i < snake1_len; i++)
                        if (snake2[0].x == snake1[i].x && snake2[0].y - step == snake1[i].y) temp = false;
                    for (int i = 1; i < snake2_len; i++)
                        if (snake2[0].x == snake2[i].x && snake2[0].y - step == snake2[i].y) temp = false;
                    if (temp)
                    {
                        direction2 = UP;
                        head2 = head2UP;
                        dir2_changed = 1;
                    }
                }
                else if (snake2[0].y + step != max_pos)
                {
                    bool temp = true;
                    for (int i = 0; i < snake1_len; i++)
                        if (snake2[0].x == snake1[i].x && snake2[0].y + step == snake1[i].y) temp = false;
                    for (int i = 1; i < snake2_len; i++)
                        if (snake2[0].x == snake2[i].x && snake2[0].y + step == snake2[i].y) temp = false;
                    if (temp)
                    {
                        direction2 = DOWN;
                        head2 = head2DOWN;
                        dir2_changed = 1;
                    }
                }
            }
            else if ((snake2[0].y - step == min_pos || snake2[0].y + step == max_pos) && (direction2 == UP || direction2 == DOWN))
            {
                if (snake2[0].x - step != min_pos)
                {
                    bool temp = true;
                    for (int i = 0; i < snake1_len; i++)
                        if (snake2[0].x - step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                    for (int i = 1; i < snake2_len; i++)
                        if (snake2[0].x - step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                    if (temp)
                    {
                        direction2 = LEFT;
                        head2 = head2LEFT;
                        dir2_changed = 1;
                    }
                }
                else if (snake2[0].x + step != max_pos)
                {
                    bool temp = true;
                    for (int i = 0; i < snake1_len; i++)
                        if (snake2[0].x + step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                    for (int i = 1; i < snake2_len; i++)
                        if (snake2[0].x + step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                    if (temp)
                    {
                        direction2 = RIGHT;
                        head2 = head2RIGHT;
                        dir2_changed = 1;
                    }
                }
            }

            for (int i = 1; i < snake2_len; i++)
                if (snake2[0].x + step == snake2[i].x && snake2[0].y == snake2[i].y && direction2 == RIGHT)
                {
                    if (snake2[0].y - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y - step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y - step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = UP;
                            head2 = head2UP;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].y + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y + step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y + step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = DOWN;
                            head2 = head2DOWN;
                            dir2_changed = 1;
                        }
                    }
                }
            for (int i = 1; i < snake2_len; i++)
                if (snake2[0].x - step == snake2[i].x && snake2[0].y == snake2[i].y && direction2 == LEFT)
                {
                    if (snake2[0].y - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y - step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y - step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = UP;
                            head2 = head2UP;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].y + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y + step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y + step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = DOWN;
                            head2 = head2DOWN;
                            dir2_changed = 1;
                        }
                    }
                }
            for (int i = 1; i < snake2_len; i++)
                if (snake2[0].x == snake2[i].x && snake2[0].y - step == snake2[i].y && direction2 == UP)
                {
                    if (snake2[0].x - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x - step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x - step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != RIGHT)
                        {
                            direction2 = LEFT;
                            head2 = head2LEFT;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].x + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x + step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x + step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != LEFT)
                        {
                            direction2 = RIGHT;
                            head2 = head2RIGHT;
                            dir2_changed = 1;
                        }
                    }
                }
            for (int i = 1; i < snake2_len; i++)
                if (snake2[0].x == snake2[i].x && snake2[0].y + step == snake2[i].y && direction2 == DOWN)
                {
                    if (snake2[0].x - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x - step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x - step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != RIGHT)
                        {
                            direction2 = LEFT;
                            head2 = head2LEFT;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].x + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x + step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x + step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != LEFT)
                        {
                            direction2 = RIGHT;
                            head2 = head2RIGHT;
                            dir2_changed = 1;
                        }
                    }
                }

            for (int i = 0; i < snake1_len; i++)
                if (snake2[0].x + step == snake1[i].x && snake2[0].y == snake1[i].y && direction2 == RIGHT)
                {
                    if (snake2[0].y - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y - step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y - step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = UP;
                            head2 = head2UP;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].y + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y + step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y + step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = DOWN;
                            head2 = head2DOWN;
                            dir2_changed = 1;
                        }
                    }
                }
            for (int i = 0; i < snake1_len; i++)
                if (snake2[0].x - step == snake1[i].x && snake2[0].y == snake1[i].y && direction2 == LEFT)
                {
                    if (snake2[0].y - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y - step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y - step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = UP;
                            head2 = head2UP;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].y + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x == snake1[i].x && snake2[0].y + step == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x == snake2[i].x && snake2[0].y + step == snake2[i].y) temp = false;
                        if (temp)
                        {
                            direction2 = DOWN;
                            head2 = head2DOWN;
                            dir2_changed = 1;
                        }
                    }
                }
            for (int i = 0; i < snake1_len; i++)
                if (snake2[0].x == snake1[i].x && snake2[0].y - step == snake1[i].y && direction2 == UP)
                {
                    if (snake2[0].x - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x - step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x - step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != RIGHT)
                        {
                            direction2 = LEFT;
                            head2 = head2LEFT;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].x + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x + step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x + step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != LEFT)
                        {
                            direction2 = RIGHT;
                            head2 = head2RIGHT;
                            dir2_changed = 1;
                        }
                    }
                }
            for (int i = 0; i < snake1_len; i++)
                if (snake2[0].x == snake1[i].x && snake2[0].y + step == snake1[i].y && direction2 == DOWN)
                {
                    if (snake2[0].x - step != min_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x - step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x - step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != RIGHT)
                        {
                            direction2 = LEFT;
                            head2 = head2LEFT;
                            dir2_changed = 1;
                        }
                    }
                    else if (snake2[0].x + step != max_pos)
                    {
                        bool temp = true;
                        for (int i = 0; i < snake1_len; i++)
                            if (snake2[0].x + step == snake1[i].x && snake2[0].y == snake1[i].y) temp = false;
                        for (int i = 1; i < snake2_len; i++)
                            if (snake2[0].x + step == snake2[i].x && snake2[0].y == snake2[i].y) temp = false;
                        if (temp && direction2 != LEFT)
                        {
                            direction2 = RIGHT;
                            head2 = head2RIGHT;
                            dir2_changed = 1;
                        }
                    }
                }
        }
        ////////////////

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
                IntRect(max_pos - 2 * step, min_pos + 1.5 * step, 50, 50).contains(Mouse::getPosition(window)) || \
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

            if (!dir1_changed)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right) && direction1 != LEFT)
                {
                    direction1 = RIGHT;
                    head1 = head1RIGHT;
                    dir1_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Up) && direction1 != DOWN)
                {
                    direction1 = UP;
                    head1 = head1UP;
                    dir1_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Left) && direction1 != RIGHT)
                {
                    direction1 = LEFT;
                    head1 = head1LEFT;
                    dir1_changed = 1;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Down) && direction1 != UP)
                {
                    direction1 = DOWN;
                    head1 = head1DOWN;
                    dir1_changed = 1;
                }
            }
        }

        window.display();
    }
}

void you_lose(fails f)
{
    RenderWindow window(sf::VideoMode(800, 400), "Snake");
    window.setPosition(Vector2i(950, 400));

    window.clear(sf::Color::White);

    Font font;
    assert(font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf"));
    font.loadFromFile("Fonts\\Segoe Print\\segoeprint.ttf");


    Text text("", font, 60);
    text.setColor(Color::Black);
    text.setPosition(400, 400);
    text.setScale(1, 2);

    if (f == LOSE)
    {
        text.setString(L"ВЫ ПРОИГРАЛИ!\n");
        rec.insert({ score1, player_name + "(green)"});
        ofstream fout("records.txt", ios::app);
        fout << score1 << ' ' << player_name + "(green)" << '\n';
    }
    if (f == WIN1)
    {
        text.setString(L"2 ИГРОК ПОБЕДИЛ!\n");
        text.setPosition(350, 400);
        rec.insert({ score1, player_name + "(green)"});
        rec.insert({ score2, player_name + "(red)" });
        ofstream fout("records.txt", ios::app);
        fout << score1 << ' ' << player_name + "(green)" << '\n';
        fout << score2 << ' ' << player_name + "(red)" << '\n';
    }
    if (f == WIN2)
    {
        text.setString(L"1 ИГРОК ПОБЕДИЛ!\n");
        text.setPosition(350, 400);
        rec.insert({ score1, player_name + "(green)" });
        rec.insert({ score2, player_name + "(red)" });
        ofstream fout("records.txt", ios::app);
        fout << score1 << ' ' << player_name + "(green)" << '\n';
        fout << score2 << ' ' << player_name + "(red)" << '\n';
    }
    if (f == DRAW)
    {
        text.setString(L"ОБА ПРОИГРАЛИ!\n");
        rec.insert({ score1, player_name + " (green)" });
        rec.insert({ score2, player_name + " (red)" });
        ofstream fout("records.txt", ios::app);
        fout << score1 << ' ' << player_name + " (green)" << '\n';
        fout << score2 << ' ' << player_name + " (red)" << '\n';
    }
    if (f == WIN)
    {
        text.setString(L"ВЫ ПОБЕДИЛИ!\n");
        rec.insert({ score1, player_name + "(green)" });
        ofstream fout("records.txt", ios::app);
        fout << score1 << ' ' << player_name + "(green)" << '\n';
    }
    if (f == DRAW1)
    {
        text.setString(L"ОБА ПРОИГРАЛИ!\n");
        rec.insert({ score1, player_name + "(green)" });
        ofstream fout("records.txt", ios::app);
        fout << score1 << ' ' << player_name + "(green)" << '\n';
    }
    
    bool work = 1;
    while (work)
    {
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
        }

        window.draw(text);
        window.display();
    }

    return;
}
