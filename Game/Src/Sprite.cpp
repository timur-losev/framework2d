#include "EdPrec.h"

#include "Sprite.h"
#include "AssetsManager.h"

SpriteInstance::SpriteInstance(void)
    : m_CurrentFrame(0)
    , m_CurrentAnimation(0)
    , m_EndAnimationTime(APP_API_GET_TICK_COUNT())
    , m_AnimationCount(0)
    , m_FramesCount(0)
    , m_TotalFrames(0)
    , m_TotalTextures(0)
    , m_Position(core::position2df(0.f, 0.f))
    , m_Scale(core::vector2df(1.f, 1.f))
    , m_RotationPoint(core::position2df(0.f, 0.f))
    , m_Rotation(0.f)
    , m_IsVisible(TRUE)
    , m_IsAnimated(FALSE)
    , m_Frames(new SpriteFramesList())
    , m_Animations(new SpriteAnimationsList())
    , m_Atlases(new SpriteTexturesList())
    , m_Driver(nullptr)
{ }

SpriteInstance::~SpriteInstance(void)
{
    m_Frames->clear();
    m_Animations->clear();
    m_Atlases->clear();
}

void SpriteInstance::Load(const std::string& resName)
{
    m_CurrentAnimation  = 0;
    m_CurrentFrame      = 0;
    m_AnimationCount    = 0;
    m_FramesCount       = 0;
    m_TotalFrames       = 0;
    m_TotalTextures     = 0;

    m_Frames->clear();
    m_Animations->clear();
    m_Atlases->clear();

    {
        SpriteFramesListPtr frames(new SpriteFramesList());
        SpriteAnimationsListPtr anims(new SpriteAnimationsList());
        SpriteTexturesListPtr textures(new SpriteTexturesList());

        if (!AssetsManager::getRef().GetMapping(resName, frames, anims, textures))
        {
            APP_API_ASSERT("Error when loading mapping file." && FALSE);
            LogMessage(LOG_ERR, "Error when loading mapping file " << resName.c_str());
            return;
        }

        //Silent copy
        *m_Frames = *frames;
        *m_Animations = *anims;
        *m_Atlases = *textures;
    }

    // Load textures
    const size_t atlasesSize = m_Atlases->size();
    for (size_t i = 0; i < atlasesSize; ++i)
    {
        if (!m_Atlases->get(i).texture())
        {
            std::string textureFile	= MEDIA_PATH + m_Atlases->get(i).name; //PVR
            video::ITexture* texture = m_Driver->getTexture(textureFile.c_str());
            APP_API_ASSERT(texture);

            m_Atlases->get(i).texture(texture);
        }
    }

    m_TotalTextures = m_Atlases->size();
    m_TotalFrames = m_Frames->size();
    m_AnimationCount = m_Animations->size();
    if (m_CurrentAnimation < m_AnimationCount)
    {
        m_FramesCount = m_Animations->get(m_CurrentAnimation).frames.size();
    }
}

void SpriteInstance::Update( const RenderContext& context )
{
    m_Driver = context.Driver;

    if (!m_Atlases->empty())
    {
        if (m_TotalTextures == 0 || !m_IsVisible) return;

        if (m_CurrentAnimation >= m_AnimationCount)
        {
            m_CurrentAnimation = 0;
            if (m_CurrentAnimation < m_Animations->size())
            {
                m_FramesCount = m_Animations->get(m_CurrentAnimation).frames.size();
            }
        }
        if (m_CurrentFrame >= m_FramesCount)
        {
            m_CurrentFrame = 0;
        }

        core::rectf frameRect;
        u32 animDuration  = 0;
        u32 textureNumber = 0;
        core::position2df position   = m_Position;
        core::dimension2du atlasSize = m_Atlases->get(textureNumber).texture()->getSize();

        if (m_FramesCount > 0 && m_CurrentFrame < m_FramesCount)
        {
            const FrameDef& frame = m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame]);
            frameRect =  core::rectf (frame.left * atlasSize.Width,
                frame.top * atlasSize.Height,
                frame.right * atlasSize.Width,
                frame.bottom * atlasSize.Height);

            animDuration = frame.animDuration;
            textureNumber = frame.textureNum;

            position.X += (f32) frame.offsetX * m_Scale.X;
            position.Y += (f32) frame.offsetY * m_Scale.Y;
        }
    #ifdef DBGMODE
        else
        {
            frameRect =  core::rectf(core::vector2df(0.0f, 0.0f), atlasSize);
        }
    #endif

        Draw2DImage(m_Driver, m_Atlases->get(textureNumber).texture(), frameRect,
            position, m_RotationPoint, m_Rotation, m_Scale,
            true, video::SColor(255, 255, 255, 255));

        if (m_IsAnimated)
        {
            if (APP_API_GET_TICK_COUNT() < m_EndAnimationTime) return;

            m_EndAnimationTime = APP_API_GET_TICK_COUNT() + animDuration;
            m_CurrentFrame++;
        }
    }
}

void SpriteInstance::Draw2DImage(DriverPtr driver,
                                 video::ITexture* texture,
                                 const core::rectf& sourceRect, const core::position2df& position,
                                 const core::position2df& rotationPoint,  f32 rotation, const core::vector2df& scale,
                                 bool useAlphaChannel, const video::SColor& color)
{
    video::SMaterial material;

    // Store and clear the projection matrix
    const core::matrix4& oldProjMat = driver->getTransform( video::ETS_PROJECTION);
    driver->setTransform(video::ETS_PROJECTION, core::matrix4());

    // Store and clear the view matrix
    const  core::matrix4& oldViewMat = driver->getTransform( video::ETS_VIEW);
    driver->setTransform(video::ETS_VIEW, core::matrix4());

    // Find the positions of corners
    core::vector2df rect[4];
    rect[0] =  core::vector2df(position.X, position.Y);
    rect[1] =  core::vector2df(position.X + sourceRect.getWidth() * scale.X, position.Y);
    rect[2] =  core::vector2df(position.X, position.Y + sourceRect.getHeight() * scale.Y);
    rect[3] =  core::vector2df(position.X + sourceRect.getWidth() * scale.X, position.Y + sourceRect.getHeight() * scale.Y);

    // Rotate corners
    if (rotation != 0.0f)
    {
        for (int x = 0; x < 4; ++x)
        {
            rect[x].rotateBy(rotation, core::vector2df(rotationPoint.X, rotationPoint.Y));
        }
    }

    // Find the uv coordinates of the sourceRect
    core::vector2df uvRect[4];
    uvRect[0] =  core::vector2df(sourceRect.UpperLeftCorner.X, sourceRect.UpperLeftCorner.Y);
    uvRect[1] =  core::vector2df(sourceRect.LowerRightCorner.X, sourceRect.UpperLeftCorner.Y);
    uvRect[2] =  core::vector2df(sourceRect.UpperLeftCorner.X, sourceRect.LowerRightCorner.Y);
    uvRect[3] =  core::vector2df(sourceRect.LowerRightCorner.X, sourceRect.LowerRightCorner.Y);
    for (int x = 0; x < 4; ++x)
    {
        float uvX = uvRect[x].X / (float) texture->getSize().Width;
        float uvY = uvRect[x].Y / (float) texture->getSize().Height;
        uvRect[x] =  core::vector2df(uvX, uvY);
    }

    // Vertices for the image
    video::S3DVertex vertices[4];
    u16 indices[6] = { 0, 1, 2, 3 , 2 , 1 };

    // Convert pixels to world coordinates
    float screenWidth	= (float) driver->getScreenSize().Width;
    float screenHeight	= (float) driver->getScreenSize().Height;

    for (int x = 0; x < 4; ++x)
    {
        float screenPosX	= ((rect[x].X / screenWidth) - 0.5f) * 2.0f;
        float screenPosY	= ((rect[x].Y / screenHeight) - 0.5f) * -2.0f;
        vertices[x].Pos		=  core::vector3df(screenPosX, screenPosY, 1);
        vertices[x].TCoords = uvRect[x];
        vertices[x].Color	= color;
    }

    material.Lighting					= false;
    material.ZWriteEnable				= false;
    material.TextureLayer[0].Texture	= texture;

    if (useAlphaChannel)
    {
        material.MaterialType =  video::EMT_TRANSPARENT_ALPHA_CHANNEL;
    }
    else
    {
        material.MaterialType =  video::EMT_SOLID;
    }

    driver->setMaterial(material);
    driver->drawIndexedTriangleList(&vertices[0], 4, &indices[0], 2);

    // Restore projection and view matrices
    driver->setTransform( video::ETS_PROJECTION, oldProjMat);
    driver->setTransform( video::ETS_VIEW, oldViewMat);
}

void SpriteInstance::GotoAndStop( u32 frameIndx )
{
    if (frameIndx < m_FramesCount)
    {
        m_CurrentFrame = frameIndx;
    }
    m_IsAnimated = FALSE;
}

void SpriteInstance::GotoAndPlay( u32 frameIndx )
{
    if (frameIndx < m_FramesCount)
    {
        m_CurrentFrame = frameIndx;
    }
    m_IsAnimated = TRUE;
}

void SpriteInstance::SetCurrentAnimation( u32 animationIndx )
{
    if (animationIndx < m_AnimationCount)
    {
        m_CurrentAnimation	= animationIndx;
        m_CurrentFrame		= 0;
        m_FramesCount		= m_Animations->get(m_CurrentAnimation).frames.size();
    }
}

void SpriteInstance::Stop()
{
    m_IsAnimated = FALSE;
}

void SpriteInstance::Play()
{
    m_IsAnimated = TRUE;
}

u32 SpriteInstance::GetTotalAnimations() const
{
    return m_AnimationCount;
}

u32 SpriteInstance::GetCurrentAnimation() const
{
    return m_CurrentAnimation;
}

u32 SpriteInstance::GetAnimationFrames() const
{
    return m_FramesCount;
}

u32 SpriteInstance::GetCurrentFrame() const
{
    return m_CurrentFrame;
}

u32 SpriteInstance::GetTotalFrames() const
{
    return m_TotalFrames;
}

void SpriteInstance::SetPosition( const core::position2df& position )
{
    m_Position = position;
}

const core::position2df& SpriteInstance::GetPosition() const
{
    return m_Position;
}

void SpriteInstance::SetScale( const core::vector2df& scale )
{
    m_Scale = scale;
}

const core::vector2df& SpriteInstance::GetScale() const
{
    return m_Scale;
}

void SpriteInstance::SetRotationPoint( const core::position2df& rotationPoint )
{
    m_RotationPoint = rotationPoint;
}

const core::position2df& SpriteInstance::GetRotationPoint() const
{
    return m_RotationPoint;
}

void SpriteInstance::SetRotation( f32 rotation )
{
    m_Rotation = rotation;
}

f32 SpriteInstance::GetRotation() const
{
    return m_Rotation;
}

void SpriteInstance::SetVisible( bool_t isVisible )
{
    m_IsVisible = isVisible;
}

bool_t SpriteInstance::GetVisible() const
{
    return m_IsVisible;
}

bool_t SpriteInstance::IsAnimated() const
{
    return m_IsAnimated;
}

SpriteTexturesListConstPtr SpriteInstance::GetTexturesList() const
{
    return m_Atlases;
}

SpriteFramesListConstPtr SpriteInstance::GetFramesList() const
{
    return m_Frames;
}

bool_t SpriteInstance::HitTest( const core::position2df& in ) const
{
    for(size_t i = 0; i < m_FramesCount; ++i)
    {
        const FrameDef& frame = m_Frames->get(i);

        if (frame.originalWidth >= in.X && frame.originalHeight >= in.Y)
            return TRUE;
    }

    return FALSE;
}
