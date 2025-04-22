#include "CollisionDetection.h"
#include <limits>

bool CollisionDetection::IsColliding(Body* a, Body* b, std::vector<Contact>& contacts) {
    bool aIsCircle = a->shape->GetType() == CIRCLE;
    bool bIsCircle = b->shape->GetType() == CIRCLE;
    bool aIsPolygon = a->shape->GetType() == POLYGON || a->shape->GetType() == RECTANGLE;
    bool bIsPolygon = b->shape->GetType() == POLYGON || b->shape->GetType() == RECTANGLE;

    if (aIsCircle && bIsCircle) {
        return IsCollidingCircleCircle(a, b, contacts);
    }
    if (aIsPolygon && bIsPolygon) {
        return IsCollidingPolygonPolygon(a, b, contacts);
    }
    if (aIsPolygon && bIsCircle) {
        return IsCollidingPolygonCircle(a, b, contacts);
    }
    if (aIsCircle && bIsPolygon) {
        return IsCollidingPolygonCircle(b, a, contacts);
    }
     return false;
}

bool CollisionDetection::IsCollidingCircleCircle(Body* a, Body* b, std::vector<Contact>& contacts) {
    CircleShape* aCircleShape = (CircleShape*)a->shape;
    CircleShape* bCircleShape = (CircleShape*)b->shape;

    const Vec2 ab = b->position - a->position;
    const float radiusSum = aCircleShape->radius + bCircleShape->radius;

    bool isColliding = ab.MagnitudeSquared() <= (radiusSum * radiusSum);

    if (!IsColliding)
        return false;

    Contact contact;
    contact.a = a;
    contact.b = b;
    contact.normal = ab;
    contact.normal.Normalize();

    contact.start = b->position - contact.normal * bCircleShape->radius;
    contact.end = a->position + contact.normal * aCircleShape->radius;

    contact.depth = (contact.end - contact.start).Magnitude();

    contacts.push_back(contact);
    return isColliding;
}

bool CollisionDetection::IsCollidingPolygonPolygon(Body* a, Body* b, std::vector<Contact>& contacts) {
    PolygonShape* aPolygonShape = (PolygonShape*)a->shape;
    PolygonShape* bPolygonShape = (PolygonShape*)b->shape;
    int aIndexReferenceEdge, bIndexReferenceEdge;
    Vec2 aSupportPoint, bSupportPoint;
    float abSeparation = aPolygonShape->FindMinimumSeparation(bPolygonShape, aIndexReferenceEdge, aSupportPoint);
    if (abSeparation >= 0) {
        return false;
    }
    float baSeparation = bPolygonShape->FindMinimumSeparation(aPolygonShape, bIndexReferenceEdge, bSupportPoint);
    if (baSeparation >= 0) {
        return false;
    }

    PolygonShape* referenceShape;
    PolygonShape* incidentShape;
    int indexReferenceEdge;
    if (abSeparation > baSeparation) {
        referenceShape = aPolygonShape;
        incidentShape = bPolygonShape;
        indexReferenceEdge = aIndexReferenceEdge;
    }
    else {
        referenceShape = bPolygonShape;
        incidentShape = aPolygonShape;
        indexReferenceEdge = bIndexReferenceEdge;
    }

    Vec2 referenceEdge = referenceShape->EdgeAt(indexReferenceEdge);

    int incidentIndex = incidentShape->FindIncidentEdge(referenceEdge.Normal());
    int incidentNextIndex = (incidentIndex + 1) % incidentShape->worldVertices.size();
    Vec2 v0 = incidentShape->worldVertices[incidentIndex];
    Vec2 v1 = incidentShape->worldVertices[incidentNextIndex];

    std::vector<Vec2> contactPoints = { v0, v1 };
    std::vector<Vec2> clippedPoints = contactPoints;
    for (int i = 0; i < referenceShape->worldVertices.size(); i++) {
        if (i == indexReferenceEdge)
            continue;
        Vec2 c0 = referenceShape->worldVertices[i];
        Vec2 c1 = referenceShape->worldVertices[(i + 1) % referenceShape->worldVertices.size()];
        int numClipped = referenceShape->ClipSegmentToLine(contactPoints, clippedPoints, c0, c1);
        if (numClipped < 2) {
            break;
        }

        contactPoints = clippedPoints;
    }

    auto vref = referenceShape->worldVertices[indexReferenceEdge];

    for (auto& vclip : clippedPoints) {
        float separation = (vclip - vref).Dot(referenceEdge.Normal());
        if (separation <= 0) {
            Contact contact;
            contact.a = a;
            contact.b = b;
            contact.normal = referenceEdge.Normal();
            contact.start = vclip;
            contact.end = vclip + contact.normal * -separation;
            if (baSeparation >= abSeparation) {
                std::swap(contact.start, contact.end);
                contact.normal *= -1.0;
            }

            contacts.push_back(contact);
        }
    }
    return true;
}

bool CollisionDetection::IsCollidingPolygonCircle(Body* polygon, Body* circle, std::vector<Contact>& contacts) {
    const PolygonShape* polygonShape = (PolygonShape*) polygon->shape;
    const CircleShape* circleShape = (CircleShape*) circle->shape;
    const std::vector<Vec2>& polygonVertices = polygonShape->worldVertices;

    bool isOutside = false;
    Vec2 minCurrVertex;
    Vec2 minNextVertex;
    float distanceCircleEdge = std::numeric_limits<float>::lowest();

    for (int i = 0; i < polygonVertices.size(); i++) {
        int currVertex = i;
        int nextvertex = (i + 1) % polygonVertices.size();
        Vec2 edge = polygonShape->EdgeAt(currVertex);
        Vec2 normal = edge.Normal();

        Vec2 vertexToCircleCenter = circle->position - polygonVertices[currVertex];
        float projection = vertexToCircleCenter.Dot(normal);

        if (projection > 0) {
            distanceCircleEdge = projection;
            minCurrVertex = polygonShape->worldVertices[currVertex];
            minNextVertex = polygonShape->worldVertices[nextvertex];
            isOutside = true;
            break;
        }
        else {
            if (projection > distanceCircleEdge) {
                distanceCircleEdge = projection;
                minCurrVertex = polygonShape->worldVertices[currVertex];
                minNextVertex = polygonShape->worldVertices[nextvertex];
            }
        }
    }

    Contact contact;

    if (isOutside) {
        Vec2 v1 = circle->position - minCurrVertex;
        Vec2 v2 = minNextVertex - minCurrVertex;
        if (v1.Dot(v2) < 0) {
            if (v1.Magnitude() > circleShape->radius) {
                return false;
            }
            else {
                contact.a = polygon;
                contact.b = circle;
                contact.depth = circleShape->radius - v1.Magnitude();
                contact.normal = v1.Normalize();
                contact.start = circle->position + (contact.normal * -circleShape->radius);
                contact.end = contact.start + (contact.normal * contact.depth);
            }
        }
        else {
            v1 = circle->position - minNextVertex;
            v2 = minCurrVertex - minNextVertex;
            if (v1.Dot(v2) < 0) {
                if (v1.Magnitude() > circleShape->radius) {
                    return false;
                }
                else {
                    contact.a = polygon;
                    contact.b = circle;
                    contact.depth = circleShape->radius - v1.Magnitude();
                    contact.normal = v1.Normalize();
                    contact.start = circle->position + (contact.normal * -circleShape->radius);
                    contact.end = contact.start + (contact.normal * contact.depth);
                }
            }
            else {
                if (distanceCircleEdge > circleShape->radius) {
                    return false;
                }
                else {
                    contact.a = polygon;
                    contact.b = circle;
                    contact.depth = circleShape->radius - distanceCircleEdge;
                    contact.normal = (minNextVertex - minCurrVertex).Normal();
                    contact.start = circle->position - (contact.normal * circleShape->radius);
                    contact.end = contact.start + (contact.normal * contact.depth);
                }
            }
        }
    }
    else {
        contact.a = polygon;
        contact.b = circle;
        contact.depth = circleShape->radius - distanceCircleEdge;
        contact.normal = (minNextVertex - minCurrVertex).Normal();
        contact.start = circle->position - (contact.normal * circleShape->radius);
        contact.end = contact.start + (contact.normal * contact.depth);
    }

    contacts.push_back(contact);
    return true;
}