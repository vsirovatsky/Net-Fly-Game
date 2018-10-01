#include "GameObject.h"

void GameObject::setPos( vector2d & _pos )
{
	pos.x = _pos.x;
	pos.y = _pos.y;
}

vector2d & GameObject::getPos()
{
	return pos;
}

void GameObject::movePos( vector2d & _moveBy )
{
	pos.x += _moveBy.x;
	pos.y += _moveBy.y;
}

LivingObject::LivingObject( BE_ID _id ) : GameObject(_id), hp(0)
{
	sprite=new hgeSprite( SYSTEM->getTexture("mediab/particles.png"), 96, 64, 32, 32);
	sprite->SetColor(0xFFFFA000);
	sprite->SetHotSpot(16,16);
}

LivingObject::~LivingObject()
{
	delete sprite;
}

void LivingObject::render()
{
	sprite->Render( getPos().x, getPos().y );
}

void LivingObject::iterate()
{
}

FoodObject::FoodObject( BE_ID _id, BE_INT _amount ) : NonLivingObject( _id ), amount(_amount), rotation(0)
{
	sprite=new hgeSprite( SYSTEM->getTexture("mediab/particles.png"), 64, 64, 32, 32);
	sprite->SetColor(0xFFFFA000);
	sprite->SetHotSpot(16,16);
}

FoodObject::~FoodObject()
{
}

void FoodObject::render()
{
	rotation += 0.01f;
	BE_FLOAT scale = 0.5f;
	if ( amount > 1000 ) {
		scale = 5;
	} else if ( amount > 100 ) {
		scale = amount / 200.0f;
	}
	sprite->RenderEx( getPos().x, getPos().y, rotation, scale );
}