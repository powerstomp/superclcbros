#include "SimpleAIController.h"

#include "../Entity.h"

void SimpleAIController::Update(Entity& entity) {
	entity.MoveHorizontal(
		std::abs(entity.GetVelocity().x) > 0.1 ? entity.GetFacing()
											   : GetOppositeDirection(entity.GetFacing())
	);
}
