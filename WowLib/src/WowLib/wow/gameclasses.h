// Generated using ReClass 2015


class EntityListPtr;
class EntityList;
class Entity;
class LocalPlayerPtr;
class EntityDescriptors;
class Object;
class ObjectDescriptors;
class MovementInfo;

class EntityListPtr
{
public:
	EntityList* entityList; //0x0000 

};//Size=0x0004

class EntityList
{
public:
	char pad_0x0000[0xC]; //0x0000
	Entity* firstEntity; //0x000C 
	char pad_0x0010[0xBC]; //0x0010
	Object* firstObject; //0x00CC 

};//Size=0x00D0

class Entity
{
public:
	char pad_0x0000[0x4]; //0x0000
	EntityDescriptors* desc; //0x0004 
	char pad_0x0008[0x4]; //0x0008
	DWORD type; //0x000C 
	char pad_0x0010[0x24]; //0x0010
	Entity* nextEnttiy; //0x0034 
	char pad_0x0038[0xB4]; //0x0038
	MovementInfo* movementInfo; //0x00EC 

};//Size=0x00F0

class LocalPlayerPtr
{
public:
	Entity* localPlayer; //0x0000 

};//Size=0x0004

class EntityDescriptors
{
public:
	DWORD guid; //0x0000 
	char pad_0x0004[0x80]; //0x0004
	__int32 curHealth; //0x0084 
	__int32 curMana; //0x0088 
	__int32 curPower; //0x008C 
	char pad_0x0090[0xC]; //0x0090
	__int32 maxHealth; //0x009C 
	__int32 maxMana; //0x00A0 
	__int32 maxPower; //0x00A4 

};//Size=0x00A8

class Object
{
public:
	char pad_0x0000[0x4]; //0x0000
	ObjectDescriptors* desc; //0x0004 
	char pad_0x0008[0x4]; //0x0008
	DWORD type; //0x000C 
	char pad_0x0010[0x24]; //0x0010
	Object* nextObject; //0x0034 

};//Size=0x0038

class ObjectDescriptors
{
public:
	DWORD guid; //0x0000 

};//Size=0x0004

class MovementInfo
{
public:
	char pad_0x0000[0x10]; //0x0000
	D3DXVECTOR3 position; //0x0010 
	char pad_0x001C[0x4]; //0x001C
	float rotation1; //0x0020 
	float rotation2; //0x0024 
	char pad_0x0028[0x1C]; //0x0028

};//Size=0x0044


