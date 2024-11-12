#include "Colitions.h"

Colitions::Colitions()
{
    OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("CREATED :: Colitions",OkasoEngine_Utilities::Info_L);
}

Colitions::~Colitions()
{
    OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETED :: Colitions",OkasoEngine_Utilities::Info_L);
}

bool Colitions::CheckCollitions(Entity2D a, Entity2D b, bool isUpdatePos)
{
    float aRight = a.GetPosition().x + abs(a.GetScale().x) / 2;
    float bLeftSide = b.GetPosition().x - abs(b.GetScale().x) / 2;
    float aLeftSide = a.GetPosition().x - abs(a.GetScale().x) / 2;
    float bRightSide = b.GetPosition().x + abs(b.GetScale().x) / 2;

    bool collisionX = aRight >= bLeftSide &&
        bRightSide >= aLeftSide;
    
    float aUpSide = a.GetPosition().y + abs(a.GetScale().y) / 2;
    float bDownSide = b.GetPosition().y - abs(b.GetScale().y) / 2;
    float bUpSide = b.GetPosition().y + abs(b.GetScale().y) / 2;
    float aDownSide = a.GetPosition().y - abs(a.GetScale().y) / 2;

    bool collisionY = aUpSide >= bDownSide &&
        bUpSide >= aDownSide;


    if (collisionX && collisionY)
    {
        if (!isUpdatePos)
        {
            a.SetPreviousPosition();

            b.SetPreviousPosition();
        }
        return true;
    }
    return false;
}

bool Colitions::CheckCollitions(Entity2D* a, Entity2D* b, bool isUpdatePos)
{
    float aRight = a->GetPosition().x + abs(a->GetScale().x) / 2;
    float bLeftSide = b->GetPosition().x - abs(b->GetScale().x) / 2;
    float aLeftSide = a->GetPosition().x - abs(a->GetScale().x) / 2;
    float bRightSide = b->GetPosition().x + abs(b->GetScale().x) / 2;

    bool collisionX = aRight >= bLeftSide &&
        bRightSide >= aLeftSide;
    
    float aUpSide = a->GetPosition().y + abs(a->GetScale().y) / 2;
    float bDownSide = b->GetPosition().y - abs(b->GetScale().y) / 2;
    float bUpSide = b->GetPosition().y + abs(b->GetScale().y) / 2;
    float aDownSide = a->GetPosition().y - abs(a->GetScale().y) / 2;

    bool collisionY = aUpSide >= bDownSide &&
        bUpSide >= aDownSide;



    if (collisionX && collisionY)
    {
        if (!isUpdatePos)
        {
            a->SetPreviousPosition();

            b->SetPreviousPosition();
        }
        return true;
    }
    return false;
}
