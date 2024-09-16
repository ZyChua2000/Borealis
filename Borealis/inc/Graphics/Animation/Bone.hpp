#ifndef BONE_HPP
#define BONE_HPP

#include <glm/glm.hpp>
#include <string>

namespace Borealis 
{
	struct Bone 
	{
		std::string name;
		int id;
		glm::mat4 offsetMatrix; // xform matrix for the bone
	};
}
#endif