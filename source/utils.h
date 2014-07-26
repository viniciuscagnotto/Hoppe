#if !defined(__UTILS_H__)
#define __UTILS_H__

struct PointFloat{
	float x;
	float y;

	PointFloat(float valX = 0.0f, float valY = 0.0f){
		x = valX;
		y = valY;
	};
};

struct PointInt{
	int x;
	int y;

	PointInt(int valX = 0, int valY = 0){
		x = valX;
		y = valY;
	};
};

//Random Functions
int RandomInt(int from, int to);
float RandomFloat(float from, float to);
float Random();


#endif //__UTILS_H__