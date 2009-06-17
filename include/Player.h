#ifndef Player_h
#define Player_h

#include "scenegraph/Transformnode.h"
#include "scenegraph/Animated_modelnode.h"
#include "scenegraph/Scenenode.h"
#include "Heightmap.h"
#include <allegro5/allegro5.h>
#include <zoidcom/zoidcom.h>

// the input class
struct Input
{
  Input() { 
    up = down = left = right = false; 
  }

  // write input to bitstream
  void pack(ZCom_BitStream &_str) {
    _str.addBool(up);
    _str.addBool(down);
    _str.addBool(left);
    _str.addBool(right);
  }

  // read input from bitstream
  void unpack(ZCom_BitStream &_str) {
    up = _str.getBool();
    down = _str.getBool();
    left = _str.getBool();
    right = _str.getBool();
  }

  bool operator==(const Input& _in) {
    return (up == _in.up && down == _in.down && left == _in.left && right == _in.right);
  }

  Input& operator=(const Input& _rhs) {
    up = _rhs.up; down = _rhs.down; left = _rhs.left; right = _rhs.right;
    return *this;
  }

  bool up;
  bool down;
  bool left;
  bool right;
};

class Net_movement: public ZCom_MoveUpdateListener<zFloat>
{
public:
	Net_movement(ZCom_Node* net_node);
	void inputUpdated(ZCom_BitStream& _inputstream, bool _inputchanged, zU32 _client_time, zU32 _estimated_time_sent);
	void inputSent(ZCom_BitStream& _inputstream);
	void correctionReceived(zFloat *_pos, zFloat* _vel, zFloat *_acc, bool _teleport, zU32 _estimated_time_sent);
	void updateReceived(ZCom_BitStream& _inputstream, zFloat *_pos, zFloat* _vel, zFloat *_acc, zU32 _estimated_time_sent) {}

	Vector3 position;
	ZCom_Replicate_Movement<zFloat, 3> *moverep;
	Input last_input_received;
	Input last_input_sent;
};

class Player: public Scenenode
{
public:
	Player();
	~Player();
	void Set_position(Vector3 p);
	Vector3 Get_position();
	void Set_texture(ALLEGRO_BITMAP* t);
	void Update(double dt, Vector3 camera_right, Vector3 camera_front, Heightmap* heightmap);
	void Event(ALLEGRO_EVENT event);
	void Damage(float d);
	void Set_health(float h);
	float Get_health();
	void Add_score(int s);
	int Get_score();
	void Drop_bomb();

	bool Deleteme();
	ZCom_Node* Register_net_node(ZCom_Control *_control, ZCom_ClassID class_id);
	ZCom_Node* Get_net_node();
	void Process_net_events();
private:
	Vector3 position;
	Vector3 interpos;
	float fallspeed;
	float angle;

	Transformnode* transform;
	Animated_modelnode* model;

	bool move_forward;
	bool move_backward;
	bool move_left;
	bool move_right;
	bool move_up;
	bool move_down;

	float health;
	int score;
	bool dropping_bomb;

	ZCom_Node* net_node;
	bool deleteme;

	Net_movement *net_movement;
};

#endif
