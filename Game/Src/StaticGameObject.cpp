#ifdef EDITOR
#include "EdPrec.h"
#else
#include "Prec.h"
#endif


#include "StaticGameObject.h"
#include "DynamicMemoryStream.h"
#include "AssetsManager.h"

StaticGameObject::StaticGameObject(): m_Driver(nullptr)
{

}

StaticGameObject::~StaticGameObject()
{

}

void StaticGameObject::Update(float dt, DriverPtr driver)
{
    m_Driver = driver;

    GameObject::Update(dt, driver);

    for(m_GraphicStateIterBegin = m_GraphicState.begin(), m_GraphicStateIterEnd = m_GraphicState.end();
        m_GraphicStateIterEnd != m_GraphicStateIterBegin; m_GraphicStateIterBegin++)
    {
        GraphicItem& item = *m_GraphicStateIterBegin;

        const core::matrix4& oldProjMat = driver->getTransform( video::ETS_PROJECTION);
        driver->setTransform(video::ETS_PROJECTION, core::matrix4());

        // Store and clear the view matrix
        const  core::matrix4& oldViewMat = driver->getTransform( video::ETS_VIEW);
        driver->setTransform(video::ETS_VIEW, core::matrix4());

        // Find the positions of corners
        const core::recti& source = item.m_SourceRect;
        const float scaledX = source.getWidth() * m_Scale.X;
        const float scaledY = source.getHeight() * m_Scale.Y;

        core::vector2df rect[4];
        rect[0] =  core::vector2df(m_Position.X + m_Offset.X,            m_Position.Y + m_Offset.Y);
        rect[1] =  core::vector2df(m_Position.X + scaledX + m_Offset.X , m_Position.Y + m_Offset.Y);
        rect[2] =  core::vector2df(m_Position.X + m_Offset.X,            m_Position.Y + scaledY + m_Offset.Y);
        rect[3] =  core::vector2df(m_Position.X + scaledX + m_Offset.X,  m_Position.Y + scaledY + m_Offset.Y);

        //TODO: Replace it
        item.m_DestRect.UpperLeftCorner = rect[0];
        item.m_DestRect.LowerRightCorner = rect[3];

        // Rotate corners
        if (m_Rotation != 0.0f)
            for (int x = 0; x < 4; x++)
                rect[x].rotateBy(m_Rotation, core::vector2df(m_Position.X + scaledX / 2 + m_Offset.X, m_Position.Y + scaledY / 2 + m_Offset.Y));

        // Find the uv coordinates of the sourceRect
        core::vector2df uvRect[4];
        uvRect[0] =  core::vector2df((float)source.UpperLeftCorner.X, (float)source.UpperLeftCorner.Y);
        uvRect[1] =  core::vector2df((float)source.LowerRightCorner.X, (float)source.UpperLeftCorner.Y);
        uvRect[2] =  core::vector2df((float)source.UpperLeftCorner.X, (float)source.LowerRightCorner.Y);
        uvRect[3] =  core::vector2df((float)source.LowerRightCorner.X, (float)source.LowerRightCorner.Y);

        video::ITexture* texture = (*m_GraphicStateIterBegin).m_Image;

        for (int x = 0; x < 4; ++x)
        {
            float uvX = uvRect[x].X / (float)texture->getSize().Width;
            float uvY = uvRect[x].Y / (float)texture->getSize().Height;
            uvRect[x] =  core::vector2df(uvX, uvY);
        }

        // Vertices for the image
        video::S3DVertex vertices[4];
        u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };

        // Convert pixels to world coordinates
        const float screenWidth = (float)driver->getScreenSize().Width;
        const float screenHeight = (float)driver->getScreenSize().Height;

        for (int x = 0; x < 4; ++x)
        {
            float screenPosX = ((rect[x].X / screenWidth) - 0.5f) * 2.0f;
            float screenPosY = ((rect[x].Y / screenHeight) - 0.5f) * -2.0f;
            vertices[x].Pos =  core::vector3df(screenPosX, screenPosY, 1);
            vertices[x].TCoords = uvRect[x];
            vertices[x].Color = video::SColor(255,255,255,255);
        }

        video::SMaterial material;

        material.Lighting = false;
        material.ZWriteEnable = false;
        material.TextureLayer[0].Texture = texture;
        material.MaterialType =  video::EMT_TRANSPARENT_ALPHA_CHANNEL;

        driver->setMaterial(material);
        driver->drawIndexedTriangleList(&vertices[0], 4, &indices[0], 2);

        driver->setTransform( video::ETS_PROJECTION, oldProjMat);
        driver->setTransform( video::ETS_VIEW, oldViewMat);
    }
}

void StaticGameObject::Serialize( DynamicMemoryStream& dms )
{
    GameObject::Serialize(dms);
    ushort_t statesCount = (ushort_t)m_GraphicState.size();
    dms.write(&statesCount);

    if (statesCount)
    {
        const char* p = APP_API_GET_SIMPLE_FILE_NAME((m_GraphicState.front()).m_Image->getName().getPath().c_str());
        dms.writeUTF8(p);
    }

    for (GraphicStateIter_t i = m_GraphicState.begin(), e = m_GraphicState.end(); i != e; ++i)
    {
        const FrameDef& frame = (*i).m_FrameInfo;

        dms.writeUTF8(AssetsManager::getRef().GetOrigin(frame.uid));
        dms.writeUTF8(frame.name);
    }
}

size_t StaticGameObject::Deserialize( MemoryStream& ms )
{
    size_t count  = 0;
    count += GameObject::Deserialize(ms);

    ushort_t statesCount = 0;
    count += ms.read(&statesCount);

    std::string textureName;

    count += ms.readUTF8(textureName);

    for (size_t i = 0; i < statesCount; ++i)
    {
        std::string frameOrigin, frameName;
        count += ms.readUTF8(frameOrigin);
        count += ms.readUTF8(frameName);

        FrameDef* frame = AssetsManager::getRef().GetFrame(frameOrigin, frameName);

        if (!frame)
        {
            APP_API_ASSERT(FALSE && "Expected frame is not exists.");
            LogMessage(LOG_ERR, "Expected frame is not exists. Origin ["<<frameOrigin.c_str()<<"] Frame ["<<frameName.c_str()<<"]");
        }
        else if (textureName.empty())
        {
            APP_API_ASSERT(FALSE && "Expected texture name.");
            LogMessage(LOG_ERR, "Expected texture name. Origin ["<<frameOrigin.c_str()<<"] Frame ["<<frameName.c_str()<<"]");
        }
        else
        {
            AddGraphicItem(textureName, *frame);
        }
    }

    return count;
}

void StaticGameObject::AddGraphicItem( const std::string& texture, const FrameDef& frame)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&StaticGameObject::AddGraphicItem, this, texture, frame));
    }
    else
#endif
    {
        GraphicItem item;
        std::string str = MEDIA_PATH + texture;
        item.m_Image = m_Driver->getTexture(str.c_str());

        APP_API_ASSERT(item.m_Image);
		item.m_SourceRect = core::recti(core::position2di((int)frame.left, (int)frame.top), core::dimension2di((int)frame.right, (int)frame.bottom));	// TODO: tex coord to abs value
        item.m_DestRect = core::rectf(0, 0, 0, 0);
        item.m_FrameInfo = frame;

        m_GraphicState.push_back(item);
    }
}

bool_t StaticGameObject::HitTest( const core::position2df& in ) const
{
    GraphicStateConstIter_t i = m_GraphicState.begin(), e = m_GraphicState.end();
    while(i != e)
    {
        if ((*i).m_DestRect.isPointInside(in))
            return TRUE;
        ++i;
    }

    return FALSE;
}
