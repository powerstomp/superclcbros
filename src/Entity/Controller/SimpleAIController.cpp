#include "SimpleAIController.h"

#include "../Entity.h"

void SimpleAIController::Update(Entity& entity) {
	entity.MoveHorizontal(GetOppositeDirection(entity.GetFacing()));
}
