#include <string>
#include "../ECS/Actor.h"
#include<unordered_map>

enum MyEnum
{
	DAMAGE,
	RESTORE,
	STUN,
	POISON
};




typedef void(*func)(); // function pointer type
typedef std::unordered_map<short, func> script_map;

void funct() { std::printf("rr"); }
void DamageHealth(std::string damageExpression, std::string chanceExpression, Actor * source, Actor * target)
{
	int damageToDeal = 2;//would be damageExpressions value
	target->getComponent()
}
void RestoreHealth(std::string damageExpression, std::string chanceExpression, Actor * source, Actor * target) {}
void ApplyStun(std::string durationExpression, std::string chanceExpression, Actor * source, Actor * target) {}


void a()
{
	script_map m;
	m.emplace(MyEnum::DAMAGE, &funct);

	m[0]();
}

