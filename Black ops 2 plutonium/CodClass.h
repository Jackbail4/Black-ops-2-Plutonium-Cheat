#pragma once
#include "Vector.h"
#include <cstdint>

//0x234B808 incremented->0x808
class Entity
{
public:
	int32_t Valid; //0x0000
	char pad_0004[8]; //0x0004
	char Name[12]; //0x000C
	char pad_0010[20]; //0x0010
	int32_t Team; //0x002C
	char pad_0030[1088]; //0x0030
	Vec3 Position; //0x0470
};

//0x0x235E7E4 <-Dereferance 0x31C <-increment
class EntityInfo
{
public:
	int32_t PlayerId; //0x0000
	char pad_0004[8]; //0x0004
	int32_t Team; //0x000C
	char pad_0010[280]; //0x0010
	Vec3 HeadPos; //0x0128
	Vec3 Position; //0x0134
	char pad_0140[104]; //0x0140
	int32_t Health; //0x01A8
};

//0x1065F30
class Refdef_t
{
public:
	Vec2 Screen; //0x0000
	char pad_0008[8]; //0x0008
	Vec2 Fov; //0x0010
	char pad_0018[64]; //0x0018
	float ViewOrigX; //0x0058
	char pad_005C[12]; //0x005C
	float ViewOrigY; //0x0068
	char pad_006C[12]; //0x006C
	float ViewOrigZ; //0x0078
};

//0x1065EEC
class LocalPlayerInfo
{
public:
	Vec3 ViewAngles; //0x0000
}; //Size: 0x0138

class ClientGameStruct
{
public:
	int32_t ClientNum; //0x0000
	char pad_0004[20]; //0x0004
	int32_t isInGame; //0x0018
	char pad_001C[104]; //0x001C
	int32_t Ping; //0x0084
	char pad_0088[1088]; //0x0088
	int32_t SecondaryAmmi; //0x04C8
	int32_t PrimaryAmmo; //0x04CC
	int32_t LethalAmmo; //0x04D0
	int32_t TacticalAmmo; //0x04D4
};

static LocalPlayerInfo* LocalPlayer = (LocalPlayerInfo*)0x1065EEC;
static Refdef_t* RefDef = (Refdef_t*)0x1065F30;
static ClientGameStruct* ClientGS = *(ClientGameStruct**)0x113F18C;