#include <iostream>
#include <SDL.h>
#include "Vec2.h"

int main(int argc, char** argv) {
	Vec2 myVector = Vec2::One();
	myVector /= 2.0f;
	return 0;
}