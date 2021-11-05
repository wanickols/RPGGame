#pragma once
//Basic Types
typedef unsigned int	Uint32;
typedef Uint32			GAME_INT;

enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_KINEMATIC, GAME_DYNAMIC };

typedef struct GAME_PHYSICS
{
	float spinSpeed;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE objectShape;
	float density;
	float friction;
	float restitution;
	float angularDamping;
	float linearDamping;
	float force;
	float angle;
	bool bullet;
	bool physicsOn;
}GAME_PHYSICS;

//Constants
const float PI = 3.14159f;
const float fPRV = 10.0f;

//Sprite ID Update Constants
const int ANIM_LAG = 5;
const int ANIM_SIZE = 3;
const int ANIMATION[] = { 27, 51, 75 };

//Sprite Sheet Constants
const int NUM_SPRITES = 96;
const int SPRITE_HEIGHT = 60;
const int SPRITE_WIDTH = 47;
const int SPRITE_SHEET_NCOLS = 24;
const int SPRITE_SHEET_NROWS = 4;

inline float PW2RW(float x) { return x * fPRV; };

inline float RW2PW(float x) { return x / fPRV; };

inline float RW2PW(int x) { return (float)x / fPRV; };

inline float RW2PWAngle(float x) { return((float)x * (2.0f * 3.14159f) / 360.0f); }; //degrees to radians

inline float PW2RWAngle(float x) { return((float)x * 360.0f / (2.0f * 3.14159f)); }; //radians to degrees