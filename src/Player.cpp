#include "Player.h"

Player::Player()
{
	transform = new Transformnode();
	Attach_node(transform);
	model = new Modelnode;
	model->Loadmodel("media/darwinian.raw");
	transform->Attach_node(model);
}

Player::~Player()
{
	delete transform;
	delete model;
//	delete net_node;
}

void Player::Set_position(Vector3 p)
{
	transform->Set_position(p);
}

Vector3 Player::Get_position()
{
	return transform->Get_position();
}

void Player::Set_texture(ALLEGRO_BITMAP* t)
{
	model->Set_texture(t);
}
