
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "Heart.h"
#include "Text.h"

TTF_Font* g_font_text = NULL;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
	return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (g_screen == NULL)
		return false;

	if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1)
		return false;
	//read file audio
	g_sound_bullet[0] = Mix_LoadWAV("Fireball2.wav");
	g_sound_bullet[1] = Mix_LoadWAV("Snowball.wav");
	g_sound_exp[0] = Mix_LoadWAV("Explosion.wav");
	g_sound_exp[1] = Mix_LoadWAV("Explosion.wav");

	if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL)
		return false;

	if(TTF_Init() == -1)
		return false;
	g_font_text = TTF_OpenFont("Atop-R99O3.ttf",40);
	if(g_font_text == NULL)
		return false;

	return true;
}

int main(int arc, char*argv[])
{
	bool is_run_screen = true;
	int bkgn_x = 0;
	bool is_quit = false;
	if (Init() == false)
		return 0;

	g_bkground = SDLCommonFunc::LoadImage("kirby_bk.jpeg");	
	if (g_bkground == NULL)
	{
	return 0;
	}

	//make Kirby heart
	Heart kirby_heart;
	kirby_heart.Init();

	Text time;
	time.SetColor(Text::WHITE_TEXT);

	Text kirby_point;
	kirby_point.SetColor(Text::WHITE_TEXT);

	//make main_object
	MainObject kirby_object;
	kirby_object.SetRect(100, 200);
	bool ret = kirby_object.LoadImg("kirby_1.png");
	if (!ret)	return 0;

	//init exp object
	ExplosionObject exp_main;
	ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clip();
	if(!ret)	return false;


	//init exp threats
	ExplosionObject exp_threats;
	ret = exp_threats.LoadImg("exp.png");
	exp_threats.set_clip();
	if(!ret)	return false;

	//make threats_object
	ThreatsObject* p_threats = new ThreatsObject[NUM_THREATS];

	for(int t = 0; t < NUM_THREATS; t++)
	{
		ThreatsObject* p_threat = (p_threats + t);
		if(p_threat)
		{
			ret = p_threat->LoadImg("enemy.png");
			if(!ret)	return 0;

			int rand_y = rand()%750;
			if(rand_y > SCREEN_HEIGHT)
			{
				rand_y = SCREEN_HEIGHT*0.3;
			}

			p_threat->SetRect(SCREEN_WIDTH + t*50,rand_y);
			p_threat->set_x_val(1);

			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
		}
	}

// 	ThreatsObject* p_threat = new ThreatsObject();
// 	ret = p_threat->LoadImg("enemy.png");
// 	if(!ret)	return 0;
// 
// 	int rand_y = rand()%400;
// 	if(rand_y > SCREEN_HEIGHT - 200)
// 	{
// 		rand_y = SCREEN_HEIGHT*0.3;
// 	}
// 
// 	p_threat->SetRect(SCREEN_WIDTH,rand_y);
// 	p_threat->set_x_val(1);
// 
// 	AmoObject* p_amo = new AmoObject();
// 	p_threat->InitAmo(p_amo);

	unsigned int kirby_die_num = 0;
	unsigned int point_val = 0;

	int ret_menu = SDLCommonFunc::ShowMenu(g_screen,g_font_text);
	if(ret_menu == 1)
		is_quit = true;

	//run code
	while (!is_quit) 
	{
		while (SDL_PollEvent(&g_even)) 
		{
			if (g_even.type == SDL_QUIT)
			{
			is_quit = true;
			break;
			}
			kirby_object.HandleInputAction(g_even,g_sound_bullet);
		}

		//apply background

		//use one picture
 		bkgn_x -= 2;
 		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
  		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH,0);
 		if(bkgn_x <= -SCREEN_WIDTH)
 			bkgn_x = 0;

		//use long picture
// 		if(is_run_screen == true)
// 		{
// 			bkgn_x -= 2;
// 			if(bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))
// 			{
// 				is_run_screen = false;
// 			}
// 			else
// 			{
// 				SDLCommonFunc::ApplySurface(g_bkground,g_screen,bkgn_x,0);
// 			}
// 		}
// 		else
// 		{
// 			SDLCommonFunc::ApplySurface(g_bkground,g_screen,bkgn_x,0);
// 		}

		//show Kirby heart
		kirby_heart.Render(g_screen);

		//implement main object
		kirby_object.HandleMove();
		kirby_object.Show(g_screen);
		kirby_object.MakeAmo(g_screen);

		//run threat
		for(int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatsObject* p_threat = (p_threats + tt);
			if(p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);

				//collision threats bullet and main
				bool is_col1 = false;
				std::vector<AmoObject*> amo_arr = p_threat->GetAmoList();
				for(int am = 0; am < amo_arr.size(); am++)
				{
					AmoObject* p_amo = amo_arr.at(am);
					if(p_amo)
					{
						is_col1 = SDLCommonFunc::CheckCollision(p_amo->GetRect(),kirby_object.GetRect());
						if(is_col1 == true)
						{
							p_threat->ResetAmo(p_amo);
							break;
						}
					}
				}

				//check collision main and threats
				bool is_col = SDLCommonFunc::CheckCollision(kirby_object.GetRect(),p_threat->GetRect());
				if(is_col || is_col1)
				{
					for(int ex = 0; ex < 4; ex++)
					{
						int x_pos = kirby_object.GetRect().x + kirby_object.GetRect().w*0.5 - EXP_WIDTH*0.5;
						int y_pos = kirby_object.GetRect().y + kirby_object.GetRect().h*0.5 - EXP_HEIGHT*0.5;
						
						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos,y_pos);
						exp_main.ShowEx(g_screen);
						SDL_Delay(100);

						if ( SDL_Flip(g_screen) == -1)
							return 0;

					}
					Mix_PlayChannel(-1,g_sound_exp[0],0);
					kirby_die_num++;
					if(kirby_die_num > 2)
					{
						if(MessageBox(NULL,L"GAME OVER",L"INFO",MB_OK))
						{
							delete [] p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 1;
						}
					}
					else
					{
						SDL_Delay(1000);
						kirby_object.SetRect(100,100);
						kirby_heart.Decrease();
						kirby_heart.Render(g_screen);
						if(SDL_Flip(g_screen) == -1)
						{
							delete[]p_threats;
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return 0;
						}
					}
				}

				std::vector<AmoObject*> amo_list = kirby_object.GetAmoList();
				for(int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if(p_amo != NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(),p_threat->GetRect());
						if(ret_col)
						{
							++point_val;
							for(int tx = 0; tx < 4; tx++)
							{
								int x_pos = p_amo->GetRect().x - EXP_WIDTH*0.5;
								int y_pos = p_amo->GetRect().y - EXP_HEIGHT*0.5;

								exp_threats.set_frame(tx);
								exp_threats.SetRect(x_pos,y_pos);
								exp_threats.ShowEx(g_screen);

							}

							p_threat->Reset(SCREEN_WIDTH + tt*400);
							kirby_object.RemoveAmo(im);
							Mix_PlayChannel(-1,g_sound_exp[1],0);
						}
					}
				}
			}
		}

		//show time for game
		std::string str_time = "Time : ";
		UINT32 time_val = SDL_GetTicks()/1000;
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time.SetText(str_time);
		time.SetRect(SCREEN_WIDTH - 200,10);
		time.CreateGameText(g_font_text,g_screen);

		//show point
		std::string val_str_point = std::to_string(point_val);
		std::string strPoint("Point : ");
		strPoint += val_str_point;

		kirby_point.SetText(strPoint);
		kirby_point.CreateGameText(g_font_text,g_screen);
		//update screen
		if ( SDL_Flip(g_screen) == -1)
		{
			delete[] p_threats;
			SDLCommonFunc::CleanUp();
			SDL_Quit();
			return 0;
		}

	}

	delete [] p_threats;

	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 1;
}