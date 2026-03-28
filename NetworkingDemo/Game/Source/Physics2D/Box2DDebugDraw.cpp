#include "Framework.h"

#include "DataTypes.h"

#include "Box2DDebugDraw.h"

Box2DDebugDraw::Box2DDebugDraw(fw::Material* pMaterial, CameraObject* pCamera)
{
    m_pMaterial = pMaterial;
    m_pCamera = pCamera;

    m_DisplayOnXZ = true;
}

Box2DDebugDraw::~Box2DDebugDraw()
{
}

void Box2DDebugDraw::Draw(const b2Vec2* vertices, int32 vertexCount, const b2Color& color, unsigned char alpha, int primitivetype)
{
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
}

void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
}

void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
{
}

void Box2DDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
}
