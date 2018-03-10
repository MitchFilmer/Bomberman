#ifndef FIREUP_HEADER_H
#define FIREUP_HEADER_H
#include "PowerUp.h"


class FireUp : public PowerUp
{
public:
	FireUp(int image, const Math::Vector2& pos);
	~FireUp();

	void Collect(Player& _player) override;

};

#endif // !FIREUP_HEADER_H