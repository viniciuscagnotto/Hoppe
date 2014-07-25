#if !defined(__UTILS_H__)
#define __UTILS_H__

struct Point{
	float x;
	float y;

	Point(float valX = 0.0f, float valY = 0.0f){
		x = valX;
		y = valY;
	};
};

//Random Functions
int RandomInt(int from, int to);
float RandomFloat(float from, float to);
float Random();


#endif //__UTILS_H__