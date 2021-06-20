#ifndef CONSTANTS_H
#define CONSTANTS_H
// Includes
#include <GL/glew.h>
#include <glm.hpp>

// Namespaces
using namespace std;
using namespace glm;

// Class
namespace Constants {
	// Transforms
	const vec3 DEF_POSITION = vec3(0.0f);
	const vec3 DEF_SCALING = vec3(1.0f);
	const float DEF_SCALE_FACTOR = 1.0f;
	const float DEF_ROTATION_ANGLE = 0.0f;

	// Camera
	const vec3 DEF_CAMERA_POSITION = vec3(0.0f, 1.0f, 5.0f);
	const vec3 DEF_CAMERA_LOOKAT = vec3(0.0f, 0.0f, -1.0f);
	const float DEF_HORIZONTAL_ANGLE = 90.0f;
	const float DEF_VERTICAL_ANGLE = 0.0f;
	const float DEF_CAMERA_SPEED = 10.0f;
	const float DEF_CAMERA_ROTATION_SPEED = 10.0f;

	// Rotation Axis
	const vec3 AXIS_X = vec3(1.0f, 0.0f, 0.0f);
	const vec3 AXIS_Y = vec3(0.0f, 1.0f, 0.0f);
	const vec3 AXIS_Z = vec3(0.0f, 0.0f, 1.0f);

	// Normals
	const vec3 NORMAL_X = vec3(1.0f, 0.0f, 0.0f);
	const vec3 NORMAL_Y = vec3(0.0f, 1.0f, 0.0f);
	const vec3 NORMAL_Z = vec3(0.0f, 0.0f, 1.0f);

	// Colours
	const vec3 COLOUR_BLK = vec3(0.0f, 0.0f, 0.0f);
	const vec3 COLOUR_RED = vec3(1.0f, 0.0f, 0.0f);
	const vec3 COLOUR_GRN = vec3(0.0f, 1.0f, 0.0f);
	const vec3 COLOUR_BLU = vec3(0.0f, 0.0f, 1.0f);
	const vec3 COLOUR_YLW = vec3(1.0f, 1.0f, 0.0f);
	const vec3 COLOUR_PRP = vec3(1.0f, 0.0f, 1.0f);
	const vec3 COLOUR_CYN = vec3(0.0f, 1.0f, 1.0f);
	const vec3 COLOUR_WHT = vec3(1.0f, 1.0f, 1.0f);

	// Cube
	const vec3 CUBE_RGT_TOP_FRT = vec3(0.5f, 0.5f, 0.5f);
	const vec3 CUBE_RGT_TOP_BCK = vec3(0.5f, 0.5f, -0.5f);
	const vec3 CUBE_RGT_BOT_FRT = vec3(0.5f, -0.5f, 0.5f);
	const vec3 CUBE_RGT_BOT_BCK = vec3(0.5f, -0.5f, -0.5f);
	const vec3 CUBE_LFT_TOP_FRT = vec3(-0.5f, 0.5f, 0.5f);
	const vec3 CUBE_LFT_TOP_BCK = vec3(-0.5f, 0.5f, -0.5f);
	const vec3 CUBE_LFT_BOT_FRT = vec3(-0.5f, -0.5f, 0.5f);
	const vec3 CUBE_LFT_BOT_BCK = vec3(-0.5f, -0.5f, -0.5f);

	// Particle
	const float P_SPAWN_TIME = 1.0f;
	const vec3 P_SCALE_INITIAL = vec3(0.0f);
	const vec3 P_SCALE_FINAL = vec3(1.0f);
	const float P_OPACITY_INITIAL = 1.0f;
	const float P_OPACITY_FINAL = 0.0f;
	const float P_LIFETIME = 5.0f;
}
#endif // !CONSTANTS_H