#ifndef AIRWAR_CATEGORY_HXX_INCLUDED
#define AIRWAR_CATEGORY_HXX_INCLUDED

namespace airwar
{
	// game object categories
	enum class Category
	{
		None,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft  = 1 << 3
	};
}

#endif // AIRWAR_CATEGORY_HXX_INCLUDED