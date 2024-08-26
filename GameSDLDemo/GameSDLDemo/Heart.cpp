#include "Heart.h"

Heart::Heart()
{

}

Heart::~Heart()
{
	
}

void Heart::AddPos(const int& xpos)
{
	pos_list_.push_back(xpos);
}

void Heart::Render(SDL_Surface *des)
{
	if(number_ == pos_list_.size())
	{
		for(int i = 0; i < pos_list_.size(); i++)
		{
			rect_.x = pos_list_.at(i);
			Show(des);
		}
	}
}

void Heart::Init()
{
	LoadImg("kirby_heart.png");
	number_ = 3;
	if(pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	AddPos(20);
	AddPos(60);
	AddPos(100);
}

void Heart::Decrease()
{
	number_--;
	pos_list_.pop_back();
}