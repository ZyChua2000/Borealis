#include <glm/glm.hpp>
#include <Scene/Components.hpp>


using namespace Borealis;
class PhysicsSystem
{
public:
	static void Init();
	static void Update(float dt, RigidBodyComponent& rigidbody);
	static void Free();

	static void createSphere(float radius, glm::vec3 position, glm::vec3 velocity, RigidBodyComponent& rigidbody);
};