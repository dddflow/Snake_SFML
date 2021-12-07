#define _CRT_SECURE_NO_WARNINGS
#include "wincon.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// sfml in visual studio

FILE* file;

struct list_node* rec = NULL;

void print_list(struct list_node* start_ptr_list)
{
	while (start_ptr_list != NULL)
	{
		fprintf(file, "%d ", start_ptr_list->value);
		fputs(start_ptr_list->name, file);
		fputs("\n", file);
		start_ptr_list = start_ptr_list->ptr_next;
	}
}

const int max_snake = 1e4;
int score = 0, score1 = 0, score2 = 0;
int speed = 70;

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
	con_init(100, 25);
	show_cursor(0);

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
	const char* menu_items[] = { "Игра", "Сложность", "Таблица рекордов", "О программе", "Справка", "Выход" };
	int menu_active_idx = 0;
	int menu_items_count = sizeof(menu_items) / sizeof(menu_items[0]);

	short clr_bg = CON_CLR_WHITE_LIGHT;
	short clr_bg_active = CON_CLR_BLUE_LIGHT;
	short clr_font = CON_CLR_BLACK;

	while (1)
	{
		int left = 48;
		int top = 3;
		int b;

		con_draw_lock();

		con_set_color(clr_font, clr_bg);
		clrscr();

		for (b = 0; b < menu_items_count; b++)
		{
			short btn_bg = clr_bg;
			if (b == menu_active_idx)
				btn_bg = clr_bg_active;

			gotoxy(left, top);
			con_set_color(clr_font, btn_bg);

			printf("********************");
			top++;
			gotoxy(left, top);
			printf("*                   ");

			gotoxy(left + 10 - strlen(menu_items[b]) / 2, top);
			printf("%s", menu_items[b]);

			con_set_color(clr_font, btn_bg);
			gotoxy(left + 19, top);
			printf("*");
			top++;
			gotoxy(left, top);
			printf("********************");
			top += 2;
		}

		con_draw_release();

		while (!key_is_pressed())
		{
			int code = key_pressed_code();
			if (code == KEY_UP)
			{
				if (menu_active_idx > 0)
				{
					menu_active_idx--;
					break;
				}
			}
			else if (code == KEY_DOWN)
			{
				if (menu_active_idx + 1 < menu_items_count)
				{
					menu_active_idx++;
					break;
				}
			}
			else if (code == KEY_ESC || code == 'q' || code == 'Q' ||
				code == (unsigned char)'й' || code == (unsigned char)'Й')
			{
				return;
			}
			else if (code == KEY_ENTER)
			{
				if (menu_active_idx == 5)
					return;

				if (menu_active_idx == 0)
					game_menu();

				if (menu_active_idx == 1)
					difficulty();

				if (menu_active_idx == 2)
					records();

				if (menu_active_idx == 3)
					about();

				if (menu_active_idx == 4)
					faq();

				break;
			}


			pause(40);
		}


		while (key_is_pressed())
			key_pressed_code();

	}
}

void faq()
{
	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	clrscr();

	gotoxy(1, 0);
	printf("Справка:");

	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	gotoxy(1, 2);
	printf("Цель игры: \n Собирать еду, избегая столкновения с собственным хвостом и  краями игрового поля\n\
 Управление в игре: \n Нажмите Q / ESC для выхода \n Нажмите P для паузы \n Перемещение для 1 игрока:\
 стрелки вверх/вниз/влево/вправо\n Перемещение для 2 игрока: клаивиши W/A/S/D\n Обозначения:\n # -- еда\n *** -- 1 змейка\n \
+++ -- 2 змейка\n @ -- препятсвия");

	gotoxy(1, 16);
	printf("Для продолжения нажмите любую клавишу...");

	key_pressed_code();
	return;
}

void about()
{
	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	clrscr();

	gotoxy(1, 0);
	printf("О программе:");

	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	gotoxy(1, 2);
	printf("Игра змейка TM\n Разработчики Данилов Денис и Багров Егор, группа 4851003\\00002, Политех, ИКиЗИ\n 2021 год\n");

	gotoxy(1, 7);
	printf("Для продолжения нажмите любую клавишу...");

	key_pressed_code();
	return;
}

void game_menu()
{
	const char* game_items[] = { "1 игрок", "2 игрока", "С компьютером", "Назад" };
	int game_active_idx = 0;
	int game_items_count = sizeof(game_items) / sizeof(game_items[0]);

	short clr_bg = CON_CLR_WHITE_LIGHT;
	short clr_bg_active = CON_CLR_BLUE_LIGHT;
	short clr_font = CON_CLR_BLACK;

	while (1)
	{
		int left = 48;
		int top = 7;
		int b;

		con_draw_lock();

		con_set_color(clr_font, clr_bg);
		clrscr();

		for (b = 0; b < game_items_count; b++)
		{
			short btn_bg = clr_bg;
			if (b == game_active_idx)
				btn_bg = clr_bg_active;

			gotoxy(left, top);
			con_set_color(clr_font, btn_bg);

			printf("********************");
			top++;
			gotoxy(left, top);
			printf("*                   ");

			gotoxy(left + 10 - strlen(game_items[b]) / 2, top);
			printf("%s", game_items[b]);

			con_set_color(clr_font, btn_bg);
			gotoxy(left + 19, top);
			printf("*");
			top++;
			gotoxy(left, top);
			printf("********************");
			top += 2;
		}

		con_draw_release();

		while (!key_is_pressed())
		{
			int code = key_pressed_code();
			if (code == KEY_UP)
			{
				if (game_active_idx > 0)
				{
					game_active_idx--;
					break;
				}
			}
			else if (code == KEY_DOWN)
			{
				if (game_active_idx + 1 < game_items_count)
				{
					game_active_idx++;
					break;
				}
			}
			else if (code == KEY_ESC || code == 'q' || code == 'Q' ||
				code == (unsigned char)'й' || code == (unsigned char)'Й')
			{
				return;
			}
			else if (code == KEY_ENTER)
			{
				if (game_active_idx == 3)
					return;

				if (game_active_idx == 0)
					game();

				if (game_active_idx == 1)
					game_pvp();

				if (game_active_idx == 2)
					game_pve();

				break;
			}


			pause(40);
		}


		while (key_is_pressed())
			key_pressed_code();

	}
}

void game()
{
	int x = 34, y = 1; // начальные значения 
	int size_x = 50, size_y = 25;
	score1 = 0;
	score2 = 0;

	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	clrscr();

	for (int i = y - 1; i <= y + 1 + size_y; i++)
	{
		gotoxy(x - 1, i);
		printf("@");
	}
	for (int i = y - 1; i <= y + 1 + size_y; i++)
	{
		gotoxy(x + 1 + size_x, i);
		printf("@");
	}
	for (int i = x; i <= x + size_x; i++)
	{
		gotoxy(i, y - 1);
		printf("@");
	}
	for (int i = x; i <= x + size_x; i++)
	{
		gotoxy(i, y + 1 + size_y);
		printf("@");
	}

	enum lines direction = RIGHT_MOVE;

	int* snake_x = (int*)malloc(max_snake * sizeof(int));
	int* snake_y = (int*)malloc(max_snake * sizeof(int));
	snake_x[0] = x;
	snake_x[1] = x + 1;
	snake_x[2] = x + 2;
	snake_y[0] = y;
	snake_y[1] = y;
	snake_y[2] = y;

	gotoxy(x, y);
	printf("***");
	x += 2;

	int len_snake = 3; // длина змеи

	int eat_x = 0, eat_y = 0;
	int eaten = 1; // 1 - нет еды

	gotoxy(10, 3);
	printf("Очки: %d", score);

	while (1)
	{
		int i = 0;
		int new_y = y, new_x = x;

		gotoxy(snake_x[len_snake - 1], snake_y[len_snake - 1]);
		printf("*");

		if (eaten)
		{
			srand(time(NULL));

			int find = 0;
			while (!find)
			{
				eat_x = rand() % 50 + 34;
				eat_y = rand() % 25 + 1;
				find = 1;
				for (int i = 0; i < len_snake; i++)
					if (eat_x == snake_x[i] && eat_y == snake_y[i]) find = 0;
			}

			gotoxy(eat_x, eat_y);
			printf("#");

			eaten = 0;
		}

		if (snake_x[len_snake - 1] == eat_x && snake_y[len_snake - 1] == eat_y)
		{
			eaten = 1;
			score += 7;
			if (speed > 1) speed--;
			gotoxy(10, 3);
			printf("Очки: %d", score);
		}

		int pressed = 0;

		for (i = 0; i < 5; i++)
		{
			if (key_is_pressed())
			{
				int c = key_pressed_code();
				if (c == 'q' || c == 'Q' || c == KEY_ESC)
					return;

				if (c == 'p' || c == 'P') game_pause();

				if (c == KEY_UP)
				{
					if (direction == RIGHT_MOVE || direction == LEFT_MOVE)
					{
						new_y--;
						direction = UP_MOVE;
						pressed = 1;
						break;
					}
				}
				if (c == KEY_DOWN)
				{
					if (direction == RIGHT_MOVE || direction == LEFT_MOVE)
					{
						new_y++;
						direction = DOWN_MOVE;
						pressed = 1;
						break;
					}
				}
				if (c == KEY_RIGHT)
				{
					if (direction == UP_MOVE || direction == DOWN_MOVE)
					{
						new_x++;
						direction = RIGHT_MOVE;
						pressed = 1;
						break;
					}
				}
				if (c == KEY_LEFT)
				{
					if (direction == UP_MOVE || direction == DOWN_MOVE)
					{
						new_x--;
						direction = LEFT_MOVE;
						pressed = 1;
						break;
					}
				}
			}
			pause(speed);
		}

		if (!eaten)
		{
			gotoxy(snake_x[0], snake_y[0]);
			printf(" ");
		}

		if (direction == UP_MOVE && !pressed)
			new_y--;
		if (direction == DOWN_MOVE && !pressed)
			new_y++;
		if (direction == RIGHT_MOVE && !pressed)
			new_x++;
		if (direction == LEFT_MOVE && !pressed)
			new_x--;

		if (!eaten)
		{
			for (int i = 0; i < len_snake - 1; i++)
			{
				snake_x[i] = snake_x[i + 1];
				snake_y[i] = snake_y[i + 1];
			}
		}
		else len_snake++;

		snake_x[len_snake - 1] = new_x;
		snake_y[len_snake - 1] = new_y;

		x = new_x;
		y = new_y;

		if (x == 85 || x == 33)
		{
			you_lose(0);
			free(snake_x);
			free(snake_y);
			return;
		}
		if (y == 27 || y == 0)
		{
			you_lose(0);
			free(snake_x);
			free(snake_y);
			return;
		}
		for (int i = 0; i < len_snake - 1; i++)
			if (x == snake_x[i] && y == snake_y[i])
			{
				you_lose(0);
				free(snake_x);
				free(snake_y);
				return;
			}
	}
}

void you_lose(int c)
{
	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	clrscr();

	file = fopen("records.txt", "a");

	if (c == 0)
	{
		gotoxy(45, 10);
		printf("Вы проиграли!\n");

		gotoxy(45, 11);
		printf("Очки: % d", score);

		gotoxy(40, 15);
		printf("Введите имя: ");

		gotoxy(53, 15);
		char name[256] = { 0 };
		gets(name);
		insert(&rec, name, score);

		fprintf(file, "%d ", score);
		fputs(name, file);
		fputs("\n", file);

		//print_list(rec);
	}
	if (c == 1)
	{
		gotoxy(45, 10);
		printf("1 игрок проиграл!\n");

		gotoxy(45, 11);
		printf("Очки 1 игрока: %d", score1);
		gotoxy(45, 12);
		printf("Очки 2 игрока: %d", score2);

		gotoxy(40, 15);
		printf("1 игрок, введите имя: ");

		gotoxy(62, 15);
		char name1[256] = { 0 };
		gets(name1);
		insert(&rec, name1, score1);

		fprintf(file, "%d ", score1);
		fputs(name1, file);
		fputs("\n", file);

		gotoxy(40, 17);
		printf("2 игрок, введите имя: ");

		gotoxy(62, 17);
		char name2[256] = { 0 };
		gets(name2);
		insert(&rec, name2, score2);

		fprintf(file, "%d ", score2);
		fputs(name2, file);
		fputs("\n", file);

		//print_list(rec);
	}
	if (c == 2)
	{
		gotoxy(45, 10);
		printf("2 игрок проиграл!\n");

		gotoxy(45, 11);
		printf("Очки 1 игрока: %d", score1);
		gotoxy(45, 12);
		printf("Очки 2 игрока: %d", score2);

		gotoxy(40, 15);
		printf("1 игрок, введите имя: ");

		gotoxy(62, 15);
		char name1[256] = { 0 };
		gets(name1);
		insert(&rec, name1, score1);

		fprintf(file, "%d ", score1);
		fputs(name1, file);
		fputs("\n", file);

		gotoxy(40, 17);
		printf("2 игрок, введите имя: ");

		gotoxy(62, 17);
		char name2[256] = { 0 };
		gets(name2);
		insert(&rec, name2, score2);

		fprintf(file, "%d ", score2);
		fputs(name2, file);
		fputs("\n", file);

		//print_list(rec);
	}
	if (c == 3)
	{
		gotoxy(45, 10);
		printf("Оба проиграли!\n");

		gotoxy(45, 11);
		printf("Очки 1 игрока: %d", score1);
		gotoxy(45, 12);
		printf("Очки 2 игрока: %d", score2);

		gotoxy(40, 15);
		printf("1 игрок, введите имя: ");

		gotoxy(62, 15);
		char name1[256] = { 0 };
		gets(name1);
		insert(&rec, name1, score1);

		fprintf(file, "%d ", score1);
		fputs(name1, file);
		fputs("\n", file);

		gotoxy(40, 17);
		printf("2 игрок, введите имя: ");

		gotoxy(62, 17);
		char name2[256] = { 0 };
		gets(name2);
		insert(&rec, name2, score2);

		fprintf(file, "%d ", score2);
		fputs(name2, file);
		fputs("\n", file);

		//print_list(rec);
	}
	if (c == 4)
	{
		gotoxy(45, 10);
		printf("Вы проиграли!\n");

		gotoxy(45, 11);
		printf("Очки 1 игрока: %d", score1);
		gotoxy(45, 12);
		printf("Очки 2 игрока: %d", score2);

		gotoxy(40, 15);
		printf("Введите имя: ");

		gotoxy(53, 15);
		char name1[256] = { 0 };
		gets(name1);
		insert(&rec, name1, score1);

		fprintf(file, "%d ", score1);
		fputs(name1, file);
		fputs("\n", file);

		insert(&rec, "Компьютер", score2);

		//print_list(rec);
	}
	if (c == 5)
	{
		gotoxy(45, 10);
		printf("Компьютер проиграл!\n");

		gotoxy(45, 11);
		printf("Очки 1 игрока: %d", score1);
		gotoxy(45, 12);
		printf("Очки 2 игрока: %d", score2);

		gotoxy(40, 15);
		printf("Введите имя: ");

		gotoxy(53, 15);
		char name1[256] = { 0 };
		gets(name1);
		insert(&rec, name1, score1);

		fprintf(file, "%d ", score1);
		fputs(name1, file);
		fputs("\n", file);

		insert(&rec, "Компьютер", score2);

		//print_list(rec);
	}
	if (c == 6)
	{
		gotoxy(45, 10);
		printf("Оба проиграли!\n");

		gotoxy(45, 11);
		printf("Очки 1 игрока: %d", score1);
		gotoxy(45, 12);
		printf("Очки 2 игрока: %d", score2);

		gotoxy(40, 15);
		printf("Введите имя: ");

		gotoxy(62, 15);
		char name1[256] = { 0 };
		gets(name1);
		insert(&rec, name1, score1);

		fprintf(file, "%d ", score1);
		fputs(name1, file);
		fputs("\n", file);

		insert(&rec, "Компьютер", score2);

		//print_list(rec);
	}

	fclose(file);
	gotoxy(35, 22);
	printf("Для продолжения нажмите любую клавишу...");

	key_pressed_code();
	return;
}

void difficulty()
{
	const char* diff_items[] = { "Легкий", "Средний", "Сложный", "Экстремальный", "Назад" };
	int diff_active_idx = 0;
	int diff_items_count = sizeof(diff_items) / sizeof(diff_items[0]);

	short clr_bg = CON_CLR_WHITE_LIGHT;
	short clr_bg_active = CON_CLR_BLUE_LIGHT;
	short clr_font = CON_CLR_BLACK;

	while (1)
	{
		int left = 48;
		int top = 5;
		int b;

		con_draw_lock();

		con_set_color(clr_font, clr_bg);
		clrscr();

		for (b = 0; b < diff_items_count; b++)
		{
			short btn_bg = clr_bg;
			if (b == diff_active_idx)
				btn_bg = clr_bg_active;

			gotoxy(left, top);
			con_set_color(clr_font, btn_bg);

			printf("********************");
			top++;
			gotoxy(left, top);
			printf("*                   ");

			gotoxy(left + 10 - strlen(diff_items[b]) / 2, top);
			printf("%s", diff_items[b]);

			con_set_color(clr_font, btn_bg);
			gotoxy(left + 19, top);
			printf("*");
			top++;
			gotoxy(left, top);
			printf("********************");
			top += 2;
		}

		con_draw_release();

		while (!key_is_pressed())
		{
			int code = key_pressed_code();
			if (code == KEY_UP)
			{
				if (diff_active_idx > 0)
				{
					diff_active_idx--;
					break;
				}
			}
			else if (code == KEY_DOWN)
			{
				if (diff_active_idx + 1 < diff_items_count)
				{
					diff_active_idx++;
					break;
				}
			}
			else if (code == KEY_ESC || code == 'q' || code == 'Q' ||
				code == (unsigned char)'й' || code == (unsigned char)'Й')
			{
				return;
			}
			else if (code == KEY_ENTER)
			{
				if (diff_active_idx == 4)
					return;

				if (diff_active_idx == 0)
				{
					speed = 100;
					return;
				}

				if (diff_active_idx == 1)
				{
					speed = 70;
					return;
				}

				if (diff_active_idx == 2)
				{
					speed = 40;
					return;
				}

				if (diff_active_idx == 3)
				{
					speed = 15;
					return;
				}

				break;
			}


			pause(40);
		}


		while (key_is_pressed())
			key_pressed_code();

	}
}

void game_pvp()
{
	int x = 34, y = 1; // начальные значения 
	int size_x = 50, size_y = 25;
	score1 = 0;
	score2 = 0;

	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	clrscr();

	for (int i = y - 1; i <= y + 1 + size_y; i++)
	{
		gotoxy(x - 1, i);
		printf("@");
	}
	for (int i = y - 1; i <= y + 1 + size_y; i++)
	{
		gotoxy(x + 1 + size_x, i);
		printf("@");
	}
	for (int i = x; i <= x + size_x; i++)
	{
		gotoxy(i, y - 1);
		printf("@");
	}
	for (int i = x; i <= x + size_x; i++)
	{
		gotoxy(i, y + 1 + size_y);
		printf("@");
	}

	enum lines direction1 = RIGHT_MOVE;
	enum lines direction2 = RIGHT_MOVE;

	int x1 = x, y1 = y;

	int* snake1_x = (int*)malloc(max_snake * sizeof(int));
	int* snake1_y = (int*)malloc(max_snake * sizeof(int));
	snake1_x[0] = x;
	snake1_x[1] = x + 1;
	snake1_x[2] = x + 2;
	snake1_y[0] = y;
	snake1_y[1] = y;
	snake1_y[2] = y;

	gotoxy(x, y);
	printf("***");
	x1 += 2;

	int x2 = x, y2 = y + size_y;

	int* snake2_x = (int*)malloc(max_snake * sizeof(int));
	int* snake2_y = (int*)malloc(max_snake * sizeof(int));
	snake2_x[0] = x;
	snake2_x[1] = x + 1;
	snake2_x[2] = x + 2;
	snake2_y[0] = y + size_y;
	snake2_y[1] = y + size_y;
	snake2_y[2] = y + size_y;

	gotoxy(x2, y2);
	printf("+++");
	x2 += 2;

	int len_snake1 = 3, len_snake2 = 3; // длина змеи

	int eat_x = 0, eat_y = 0;
	int eaten1 = 1, eaten2 = 1; // 1 - нет еды

	gotoxy(10, 3);
	printf("Очки 1 игрока: %d", score1);
	gotoxy(10, 5);
	printf("Очки 2 игрока: %d", score2);

	while (1)
	{
		int i = 0;
		int new_y1 = y1, new_x1 = x1;
		int new_y2 = y2, new_x2 = x2;

		gotoxy(snake1_x[len_snake1 - 1], snake1_y[len_snake1 - 1]);
		printf("*");
		gotoxy(snake2_x[len_snake2 - 1], snake2_y[len_snake2 - 1]);
		printf("+");

		if (eaten1 || eaten2)
		{
			srand(time(NULL));

			int find = 0;
			while (!find)
			{
				eat_x = rand() % 50 + 34;
				eat_y = rand() % 25 + 1;
				find = 1;
				for (int i = 0; i < len_snake1; i++)
					if (eat_x == snake1_x[i] && eat_y == snake1_y[i]) find = 0;
				for (int i = 0; i < len_snake2; i++)
					if (eat_x == snake2_x[i] && eat_y == snake2_y[i]) find = 0;
			}

			gotoxy(eat_x, eat_y);
			printf("#");

			eaten1 = 0;
			eaten2 = 0;
		}

		if (snake1_x[len_snake1 - 1] == eat_x && snake1_y[len_snake1 - 1] == eat_y)
		{
			eaten1 = 1;
			score1 += 7;
			if (speed > 1) speed--;
			gotoxy(10, 3);
			printf("Очки 1 игрока: %d", score1);
		}

		if (snake2_x[len_snake2 - 1] == eat_x && snake2_y[len_snake2 - 1] == eat_y)
		{
			eaten2 = 1;
			score2 += 7;
			if (speed > 1) speed--;
			gotoxy(10, 5);
			printf("Очки 2 игрока: %d", score2);
		}

		int pressed1 = 0;
		int pressed2 = 0;

		for (i = 0; i < 5; i++)
		{
			if (key_is_pressed())
			{
				int c = key_pressed_code();
				if (c == 'q' || c == 'Q' || c == KEY_ESC)
					return;

				if (c == 'p' || c == 'P') game_pause();

				if (c == KEY_UP)
				{
					if (direction1 == RIGHT_MOVE || direction1 == LEFT_MOVE)
					{
						new_y1--;
						direction1 = UP_MOVE;
						pressed1 = 1;
						break;
					}
				}
				if (c == KEY_DOWN)
				{
					if (direction1 == RIGHT_MOVE || direction1 == LEFT_MOVE)
					{
						new_y1++;
						direction1 = DOWN_MOVE;
						pressed1 = 1;
						break;
					}
				}
				if (c == KEY_RIGHT)
				{
					if (direction1 == UP_MOVE || direction1 == DOWN_MOVE)
					{
						new_x1++;
						direction1 = RIGHT_MOVE;
						pressed1 = 1;
						break;
					}
				}
				if (c == KEY_LEFT)
				{
					if (direction1 == UP_MOVE || direction1 == DOWN_MOVE)
					{
						new_x1--;
						direction1 = LEFT_MOVE;
						pressed1 = 1;
						break;
					}
				}

				if (c == KEY_W)
				{
					if (direction2 == RIGHT_MOVE || direction2 == LEFT_MOVE)
					{
						new_y2--;
						direction2 = UP_MOVE;
						pressed2 = 1;
						break;
					}
				}
				if (c == KEY_S)
				{
					if (direction2 == RIGHT_MOVE || direction2 == LEFT_MOVE)
					{
						new_y2++;
						direction2 = DOWN_MOVE;
						pressed2 = 1;
						break;
					}
				}
				if (c == KEY_D)
				{
					if (direction2 == UP_MOVE || direction2 == DOWN_MOVE)
					{
						new_x2++;
						direction2 = RIGHT_MOVE;
						pressed2 = 1;
						break;
					}
				}
				if (c == KEY_A)
				{
					if (direction2 == UP_MOVE || direction2 == DOWN_MOVE)
					{
						new_x2--;
						direction2 = LEFT_MOVE;
						pressed2 = 1;
						break;
					}
				}
			}
			pause(speed);
		}

		if (!eaten1)
		{
			gotoxy(snake1_x[0], snake1_y[0]);
			printf(" ");
		}
		if (!eaten2)
		{
			gotoxy(snake2_x[0], snake2_y[0]);
			printf(" ");
		}

		if (direction1 == UP_MOVE && !pressed1)
			new_y1--;
		if (direction1 == DOWN_MOVE && !pressed1)
			new_y1++;
		if (direction1 == RIGHT_MOVE && !pressed1)
			new_x1++;
		if (direction1 == LEFT_MOVE && !pressed1)
			new_x1--;

		if (direction2 == UP_MOVE && !pressed2)
			new_y2--;
		if (direction2 == DOWN_MOVE && !pressed2)
			new_y2++;
		if (direction2 == RIGHT_MOVE && !pressed2)
			new_x2++;
		if (direction2 == LEFT_MOVE && !pressed2)
			new_x2--;

		if (!eaten1)
		{
			for (int i = 0; i < len_snake1 - 1; i++)
			{
				snake1_x[i] = snake1_x[i + 1];
				snake1_y[i] = snake1_y[i + 1];
			}
		}
		else len_snake1++;

		snake1_x[len_snake1 - 1] = new_x1;
		snake1_y[len_snake1 - 1] = new_y1;

		x1 = new_x1;
		y1 = new_y1;

		if (!eaten2)
		{
			for (int i = 0; i < len_snake2 - 1; i++)
			{
				snake2_x[i] = snake2_x[i + 1];
				snake2_y[i] = snake2_y[i + 1];
			}
		}
		else len_snake2++;

		snake2_x[len_snake2 - 1] = new_x2;
		snake2_y[len_snake2 - 1] = new_y2;

		x2 = new_x2;
		y2 = new_y2;

		if (x1 == 85 || x1 == 33)
		{
			you_lose(1);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}
		if (y1 == 27 || y1 == 0)
		{
			you_lose(1);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}

		if (x2 == 85 || x2 == 33)
		{
			you_lose(2);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}
		if (y2 == 27 || y2 == 0)
		{
			you_lose(2);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}

		for (int i = 0; i < len_snake1 - 1; i++)
			if (x1 == snake1_x[i] && y1 == snake1_y[i])
			{
				you_lose(1);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}
		for (int i = 0; i < len_snake2 - 1; i++)
			if (x2 == snake2_x[i] && y2 == snake2_y[i])
			{
				you_lose(2);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}

		if (x1 == x2 && y1 == y2)
		{
			you_lose(3);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}

		for (int i = 0; i < len_snake1 - 1; i++)
			if (x2 == snake1_x[i] && y2 == snake1_y[i])
			{
				you_lose(2);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}
		for (int i = 0; i < len_snake2 - 1; i++)
			if (x1 == snake2_x[i] && y1 == snake2_y[i])
			{
				you_lose(1);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}
	}
}

void game_pve()
{
	int x = 34, y = 1; // начальные значения 
	int size_x = 50, size_y = 25;
	score1 = 0;
	score2 = 0;

	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	clrscr();

	for (int i = y - 1; i <= y + 1 + size_y; i++)
	{
		gotoxy(x - 1, i);
		printf("@");
	}
	for (int i = y - 1; i <= y + 1 + size_y; i++)
	{
		gotoxy(x + 1 + size_x, i);
		printf("@");
	}
	for (int i = x; i <= x + size_x; i++)
	{
		gotoxy(i, y - 1);
		printf("@");
	}
	for (int i = x; i <= x + size_x; i++)
	{
		gotoxy(i, y + 1 + size_y);
		printf("@");
	}

	enum lines direction1 = RIGHT_MOVE;
	enum lines direction2 = RIGHT_MOVE;

	int x1 = x, y1 = y;

	int* snake1_x = (int*)malloc(max_snake * sizeof(int));
	int* snake1_y = (int*)malloc(max_snake * sizeof(int));
	snake1_x[0] = x;
	snake1_x[1] = x + 1;
	snake1_x[2] = x + 2;
	snake1_y[0] = y;
	snake1_y[1] = y;
	snake1_y[2] = y;

	gotoxy(x, y);
	printf("***");
	x1 += 2;

	int x2 = x, y2 = y + size_y;

	int* snake2_x = (int*)malloc(max_snake * sizeof(int));
	int* snake2_y = (int*)malloc(max_snake * sizeof(int));
	snake2_x[0] = x;
	snake2_x[1] = x + 1;
	snake2_x[2] = x + 2;
	snake2_y[0] = y + size_y;
	snake2_y[1] = y + size_y;
	snake2_y[2] = y + size_y;

	gotoxy(x2, y2);
	printf("+++");
	x2 += 2;

	int len_snake1 = 3, len_snake2 = 3; // длина змеи

	int eat_x = 0, eat_y = 0;
	int eaten1 = 1, eaten2 = 1; // 1 - нет еды

	gotoxy(10, 3);
	printf("Очки 1 игрока: %d", score1);
	gotoxy(10, 5);
	printf("Очки 2 игрока: %d", score2);

	while (1)
	{
		int i = 0;
		int new_y1 = y1, new_x1 = x1;
		int new_y2 = y2, new_x2 = x2;

		gotoxy(snake1_x[len_snake1 - 1], snake1_y[len_snake1 - 1]);
		printf("*");
		gotoxy(snake2_x[len_snake2 - 1], snake2_y[len_snake2 - 1]);
		printf("+");

		if (eaten1 || eaten2)
		{
			srand(time(NULL));

			int find = 0;
			while (!find)
			{
				eat_x = rand() % 50 + 34;
				eat_y = rand() % 25 + 1;
				find = 1;
				for (int i = 0; i < len_snake1; i++)
					if (eat_x == snake1_x[i] && eat_y == snake1_y[i]) find = 0;
				for (int i = 0; i < len_snake2; i++)
					if (eat_x == snake2_x[i] && eat_y == snake2_y[i]) find = 0;
			}

			gotoxy(eat_x, eat_y);
			printf("#");

			eaten1 = 0;
			eaten2 = 0;
		}

		if (snake1_x[len_snake1 - 1] == eat_x && snake1_y[len_snake1 - 1] == eat_y)
		{
			eaten1 = 1;
			score1 += 7;
			if (speed > 1) speed--;
			gotoxy(10, 3);
			printf("Очки 1 игрока: %d", score1);
		}

		if (snake2_x[len_snake2 - 1] == eat_x && snake2_y[len_snake2 - 1] == eat_y)
		{
			eaten2 = 1;
			score2 += 7;
			if (speed > 1) speed--;
			gotoxy(10, 5);
			printf("Очки 2 игрока: %d", score2);
		}

		int pressed1 = 0;
		int pressed2 = 0;

		for (i = 0; i < 5; i++)
		{
			if (key_is_pressed())
			{
				int c = key_pressed_code();
				if (c == 'q' || c == 'Q' || c == KEY_ESC)
					return;

				if (c == 'p' || c == 'P') game_pause();

				if (c == KEY_UP)
				{
					if (direction1 == RIGHT_MOVE || direction1 == LEFT_MOVE)
					{
						new_y1--;
						direction1 = UP_MOVE;
						pressed1 = 1;
						break;
					}
				}
				if (c == KEY_DOWN)
				{
					if (direction1 == RIGHT_MOVE || direction1 == LEFT_MOVE)
					{
						new_y1++;
						direction1 = DOWN_MOVE;
						pressed1 = 1;
						break;
					}
				}
				if (c == KEY_RIGHT)
				{
					if (direction1 == UP_MOVE || direction1 == DOWN_MOVE)
					{
						new_x1++;
						direction1 = RIGHT_MOVE;
						pressed1 = 1;
						break;
					}
				}
				if (c == KEY_LEFT)
				{
					if (direction1 == UP_MOVE || direction1 == DOWN_MOVE)
					{
						new_x1--;
						direction1 = LEFT_MOVE;
						pressed1 = 1;
						break;
					}
				}
			}
			pause(speed);
		}

		if (direction2 == UP_MOVE || direction2 == DOWN_MOVE)
		{
			if (eat_x > x2)
			{
				int find = 0;

				for (int i = 0; i < len_snake2; i++)
					if (x2 + 1 == snake2_x[i]) find = 1;
				for (int i = 0; i < len_snake1; i++)
					if (x2 + 1 == snake1_x[i]) find = 1;

				if (!find)
				{
					new_x2++;
					pressed2 = 1;
					direction2 = RIGHT_MOVE;
				}
			}
			else if (eat_x < x2)
			{
				int find = 0;

				for (int i = 0; i < len_snake2; i++)
					if (x2 - 1 == snake2_x[i]) find = 1;
				for (int i = 0; i < len_snake1; i++)
					if (x2 - 1 == snake1_x[i]) find = 1;

				if (!find)
				{
					new_x2--;
					pressed2 = 1;
					direction2 = LEFT_MOVE;
				}
			}

			if (y2 == 26 || y2 == 1)
			{
				if (x2 + 1 < 85)
				{
					new_x2++;
					direction2 = RIGHT_MOVE;
				}
				if (x2 - 1 > 33)
				{
					new_x2--;
					direction2 = LEFT_MOVE;
				}
				pressed2 = 1;
			}
		}
		else if (direction2 == RIGHT_MOVE || direction2 == LEFT_MOVE)
		{
			if (eat_y > y2)
			{
				int find = 0;

				for (int i = 0; i < len_snake2; i++)
					if (y2 + 1 == snake2_y[i]) find = 1;
				for (int i = 0; i < len_snake1; i++)
					if (y2 + 1 == snake1_y[i]) find = 1;

				if (!find)
				{
					new_y2++;
					pressed2 = 1;
					direction2 = DOWN_MOVE;
				}
			}
			else if (eat_y < y2)
			{
				int find = 0;

				for (int i = 0; i < len_snake2; i++)
					if (y2 - 1 == snake2_y[i]) find = 1;
				for (int i = 0; i < len_snake1; i++)
					if (y2 - 1 == snake1_y[i]) find = 1;

				if (!find)
				{
					new_y2--;
					pressed2 = 1;
					direction2 = UP_MOVE;
				}
			}

			if (x2 == 84 || x2 == 34)
			{
				if (y2 + 1 < 27)
				{
					new_y2++;
					direction2 = UP_MOVE;
				}
				if (y2 - 1 > 0)
				{
					new_y2--;
					direction2 = DOWN_MOVE;
				}
				pressed2 = 1;
			}
		}

		if (!eaten1)
		{
			gotoxy(snake1_x[0], snake1_y[0]);
			printf(" ");
		}
		if (!eaten2)
		{
			gotoxy(snake2_x[0], snake2_y[0]);
			printf(" ");
		}

		if (direction1 == UP_MOVE && !pressed1)
			new_y1--;
		if (direction1 == DOWN_MOVE && !pressed1)
			new_y1++;
		if (direction1 == RIGHT_MOVE && !pressed1)
			new_x1++;
		if (direction1 == LEFT_MOVE && !pressed1)
			new_x1--;

		if (direction2 == UP_MOVE && !pressed2)
			new_y2--;
		if (direction2 == DOWN_MOVE && !pressed2)
			new_y2++;
		if (direction2 == RIGHT_MOVE && !pressed2)
			new_x2++;
		if (direction2 == LEFT_MOVE && !pressed2)
			new_x2--;

		if (!eaten1)
		{
			for (int i = 0; i < len_snake1 - 1; i++)
			{
				snake1_x[i] = snake1_x[i + 1];
				snake1_y[i] = snake1_y[i + 1];
			}
		}
		else len_snake1++;

		snake1_x[len_snake1 - 1] = new_x1;
		snake1_y[len_snake1 - 1] = new_y1;

		x1 = new_x1;
		y1 = new_y1;

		if (!eaten2)
		{
			for (int i = 0; i < len_snake2 - 1; i++)
			{
				snake2_x[i] = snake2_x[i + 1];
				snake2_y[i] = snake2_y[i + 1];
			}
		}
		else len_snake2++;

		snake2_x[len_snake2 - 1] = new_x2;
		snake2_y[len_snake2 - 1] = new_y2;

		x2 = new_x2;
		y2 = new_y2;

		if (x1 == 85 || x1 == 33)
		{
			you_lose(1 + 3);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}
		if (y1 == 27 || y1 == 0)
		{
			you_lose(1 + 3);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}

		if (x2 == 85 || x2 == 33)
		{
			you_lose(2 + 3);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}
		if (y2 == 27 || y2 == 0)
		{
			you_lose(2 + 3);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}

		for (int i = 0; i < len_snake1 - 1; i++)
			if (x1 == snake1_x[i] && y1 == snake1_y[i])
			{
				you_lose(1 + 3);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}
		for (int i = 0; i < len_snake2 - 1; i++)
			if (x2 == snake2_x[i] && y2 == snake2_y[i])
			{
				you_lose(2 + 3);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}

		if (x1 == x2 && y1 == y2)
		{
			you_lose(3 + 3);
			free(snake1_x);
			free(snake1_y);
			free(snake2_x);
			free(snake2_y);
			return;
		}

		for (int i = 0; i < len_snake1 - 1; i++)
			if (x2 == snake1_x[i] && y2 == snake1_y[i])
			{
				you_lose(2 + 3);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}
		for (int i = 0; i < len_snake2 - 1; i++)
			if (x1 == snake2_x[i] && y1 == snake2_y[i])
			{
				you_lose(1 + 3);
				free(snake1_x);
				free(snake1_y);
				free(snake2_x);
				free(snake2_y);
				return;
			}
	}
}

void records()
{
	con_set_color(CON_CLR_BLACK, CON_CLR_WHITE_LIGHT);
	clrscr();

	gotoxy(1, 0);
	printf("Рекорды:");

	print_records(rec);

	gotoxy(1, 25);
	printf("Для продолжения нажмите любую клавишу...");

	key_pressed_code();
	return;
}

void game_pause()
{
	gotoxy(10, 10);
	printf("Игра на паузе");
	gotoxy(9, 12);
	printf("Для продолжения");
	gotoxy(7, 13);
	printf("нажмите любую клавишу");

	while (1)
	{
		pause(1000);
		key_pressed_code();

		gotoxy(10, 10);
		printf("             ");
		gotoxy(9, 12);
		printf("               ");
		gotoxy(7, 13);
		printf("                     ");

		return;
	}
}

