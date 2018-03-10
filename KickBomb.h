#ifndef KICKBOMB_HEADER_H
#define KICKBOMB_HEADER_H
#include "PowerUp.h"

class KickBomb : public PowerUp
{
public:
	KickBomb(int image, const Math::Vector2& pos);
	~KickBomb();

	void Collect(Player& _player) override;

};

#endif // !KICKBOMB_HEADER_H