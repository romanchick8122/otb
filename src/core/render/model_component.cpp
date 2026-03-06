#include "model_component.h"

namespace otb
{
ModelComponent::ModelComponent(const char* file_path)
    : model(LoadModel(file_path))
{
}

ModelComponent::~ModelComponent()
{
    UnloadModel(model);
}
}