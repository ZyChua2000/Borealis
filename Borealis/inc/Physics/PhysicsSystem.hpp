#include <glm/glm.hpp>
#include <Scene/Components.hpp>


using namespace Borealis;
class PhysicsSystem
{
public:
	static void Init();
	static void Update(float dt);
	static void Free();

	static void PushTransform(unsigned int bodyID, TransformComponent& transform);

	static void PullTransform(unsigned int bodyID, TransformComponent& transform);

	static void addSphereBody(float radius, glm::vec3 position, glm::vec3 velocity, RigidBodyComponent& rigidbody);
};