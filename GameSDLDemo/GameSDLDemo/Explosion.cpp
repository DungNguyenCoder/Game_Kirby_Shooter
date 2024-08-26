
#include "Explosion.h"

ExplosionObject::ExplosionObject()
{
	frame_ = 0;
};

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIDTH;
	clip_[0].h = EXP_HEIGHT;

	clip_[1].x = EXP_WIDTH;
	clip_[1].y = 0;
	clip_[1].w = EXP_WIDTH;
	clip_[1].h = EXP_HEIGHT;

	clip_[0].x = EXP_WIDTH * 2;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIDTH;
	clip_[0].h = EXP_HEIGHT;

	clip_[0].x = EXP_WIDTH * 3;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIDTH;
	clip_[0].h = EXP_HEIGHT;
}

void ExplosionObject::ShowEx(SDL_Surface* des)
{
	if(frame_ >= 4)
		frame_ = 0;
	SDLCommonFunc::ApplySurfaceclip(this->p_object_,des,&clip_[frame_],rect_.x,rect_.y);
}