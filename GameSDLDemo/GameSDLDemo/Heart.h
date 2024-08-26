
#ifndef HEART_H_
#define HEART_H_

#include "BaseObject.h"
#include <vector>

class Heart : public BaseObject
{
public:
	Heart();
	~Heart();
	void SetNumber(const int &num) {number_ = num;}
	void AddPos(const int& xpos);
	void Render(SDL_Surface *des);
	void Init();
	void Decrease();
private:
	int number_;
	std::vector <int> pos_list_;

};


#endif