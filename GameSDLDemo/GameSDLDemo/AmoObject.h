
#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "BaseObject.h"

#define WIDTH_FIREBALL 24
#define HEIGHT_FIREBALL 15

#define WIDTH_SNOWBALL 20
#define HEIGHT_SNOWBALL 20

class AmoObject : public BaseObject
{
public:
	enum AmoType
	{
		NONE = 0,
		FIREBALL = 1,
		SNOWBALL = 2,
	};

	AmoObject();
	~AmoObject();
	void HandleInputAction(SDL_Event events);
	void HandleMove(const int& x_border, const int& y_border);
	void HandleMoveRightToLeft();

	int get_type() const {return amo_type_;}
	void set_type(const int& type) {amo_type_ = type;}

	bool get_is_move() const {return is_move_;}
	void set_is_move(bool is_move) {is_move_ = is_move;}
	void SetWidthHeight(const int& widht, const int& height) {rect_.w = widht; rect_.h = height;};

	void set_x_val(const int& val)	{x_val_ = val;}
	void set_y_val(const int& val)	{y_val_ = val;}
	
	int get_x_val() const {return x_val_;}
	int get_y_val() const {return y_val_;}

private:
	int x_val_;
	int y_val_;
	bool is_move_;
	int amo_type_;
};


#endif