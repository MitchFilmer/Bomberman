#ifndef BOMBUP_HEADER_H
#define BOMBUP_HEADER_H
#include "PowerUp.h"


class BombUp : public PowerUp
{
public:
	BombUp(int image, const Math::Vector2& pos);
	~BombUp();

	void Collect(Player& _player) override;

};

#endif // !BOMBUP_HEADER_H