
https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system

## Components / Data

```c++
struct TransformData
{
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

struct MeshData
{
	Mesh* pMesh;
	Material* pMaterial;
};
```

## Registry

```c++
entt::registry m_ECSRegistry
```

## Create an Entity

```c++
entt::entity entityID = m_ECSRegistry.create();
```

## Add a Component

```c++
m_ECSRegistry.emplace<TransformData>( entityID, vec3(0), vec3(0), vec3(1) );
```

## Get Data from an Entity

```c++
TransformData* pTransformData = m_ECSRegistry.try_get<TransformData>( id );
```

## Get All Entities With a Set of Components

```c++
auto view = m_ECSRegistry.view<TransformData, MeshData>();
```

## Get Multiple Components From Entity

```c++
for( auto entity : view )
{
    auto& [transform, mesh] = group.get<TransformData, MeshData>( entity );
}
```

## Destroy an Entity

```c++
m_ECSRegistry.destroy( entityID )
```