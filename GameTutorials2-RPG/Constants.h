#pragma once
//Basic Types
typedef unsigned int	Uint32;
typedef Uint32			GAME_INT;

enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_KINEMATIC, GAME_DYNAMIC };



// 0000000000000001 in binary
static short CATEGORY_PLAYER = 1;

// 0000000000000010 in binary
static short CATEGORY_BULLET = 2;

// 0000000000000100 in binary
static short CATEGORY_ENEMY = 4;

// 0000000000001000 in binary
static short CATEGORY_WALL = 8;

static short MASK_PLAYER = CATEGORY_WALL | CATEGORY_ENEMY;
static short MASK_BULLET = CATEGORY_WALL | CATEGORY_ENEMY;
static short MASK_ENEMY = CATEGORY_PLAYER | CATEGORY_WALL | CATEGORY_BULLET | CATEGORY_ENEMY;
static short MASK_WALL = CATEGORY_PLAYER | CATEGORY_WALL | CATEGORY_BULLET | CATEGORY_ENEMY;

typedef struct GAME_PHYSICS
{
	GAME_PHYSICS() {};

	GAME_PHYSICS(
	GAME_BODY_TYPE bodyType, GAME_OBJECT_SHAPE objectShape,
		float width, float height,
	float density, float friction, float restitution,
	float angularDamping, float linearDamping,
	float force, float angle, float spinSpeed,
		short category, short mask,
	bool bullet = false, bool physicsOn = true
	) 
		: bodyType(bodyType), objectShape(objectShape),
		width(width), height(height),
		density(density), friction(friction), restitution(restitution),
		angularDamping(angularDamping), linearDamping(linearDamping),
		force(force), angle(angle), spinSpeed(spinSpeed),
		category(category), mask(mask),
		bullet(bullet), physicsOn(physicsOn)
	{};

	GAME_BODY_TYPE bodyType = GAME_BODY_TYPE::GAME_STATIC;
	GAME_OBJECT_SHAPE objectShape = GAME_OBJECT_SHAPE::GAME_RECTANGLE;
	float width = 0.f;
	float height = 0.f;
	float offSetX = 0.f;
	float offSetY = 0.f;
	float density = 0.f;
	float friction = 0.f;
	float restitution = 0.f;
	float angularDamping = 0.f;
	float linearDamping = 0.f;
	float force = 0.f;
	float angle = 0.f;
	float spinSpeed = 1.f;
	bool bullet = false;
	bool physicsOn = true;
	short category = CATEGORY_PLAYER;
	short mask = CATEGORY_PLAYER;
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


