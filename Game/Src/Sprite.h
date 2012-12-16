#ifndef _CSPRITE_H_
#    define _CSPRITE_H_

#    include "SpriteDefs.h"
#    include "Serializable.h"

class SpriteInstance : public Serializable
{
protected:
    // Animation
    u32                     m_CurrentFrame;		// Rendered frame
    u32                     m_CurrentAnimation;
    u64                     m_EndAnimationTime;
    u32                     m_AnimationCount;
    u32                     m_FramesCount;		// Frames per animation
    u32                     m_TotalFrames;
    u32                     m_TotalTextures;

    // Properties
    core::position2df       m_Position;
    core::vector2df         m_Scale;
    core::position2df       m_RotationPoint;
    f32                     m_Rotation;
    bool_t                  m_IsVisible;
    bool_t                  m_IsAnimated;

    SpriteFramesListPtr     m_Frames;
    SpriteAnimationsListPtr m_Animations;
    SpriteTexturesListPtr	m_Atlases;

    DriverPtr               m_Driver;

    static void             Draw2DImage (DriverPtr driver,
                                         video::ITexture* texture,
                                         const core::rectf& sourceRect, const core::position2df& position,
                                         const core::position2df& rotationPoint, f32 rotation, const core::vector2df& scale,
                                         bool useAlphaChannel, const video::SColor& color);
public:
    SpriteInstance(void);
    virtual ~SpriteInstance(void);

    virtual void Update(const RenderContext& context);

    void                   Load(const std::string& resName);
    bool_t                 LoadTexture(const std::string& resName, video::ITexture* out);

    INL void Stop()
    {
        m_IsAnimated = FALSE;
    }

    INL void Play()
    {
        m_IsAnimated = TRUE;
    }
    void GotoAndStop(u32 frameIndx);
    void GotoAndPlay(u32 frameIndx);

    INL	u32 GetTotalAnimations() const
    {
        return m_AnimationCount;
    }

    INL u32 GetCurrentAnimation() const
    {
        return m_CurrentAnimation;
    }
    void SetCurrentAnimation(u32 animationIndx);

    INL u32 GetAnimationFrames() const
    {
        return m_FramesCount;
    }

    INL u32 GetCurrentFrame() const
    {
        return m_CurrentFrame;
    }

    INL u32 GetTotalFrames() const
    {
        return m_TotalFrames;
    }
    // Properties

    INL void SetPosition(const core::position2df& position)
    {
        m_Position = position;
    }

    INL const core::position2df& GetPosition() const
    {
        return m_Position;
    }

    INL void SetScale(const core::vector2df& scale)
    {
        m_Scale = scale;
    }

    INL const core::vector2df& GetScale() const
    {
        return m_Scale;
    }

    INL void SetRotationPoint(const core::position2df& rotationPoint)
    {
        m_RotationPoint = rotationPoint;
    }

    INL const core::position2df& GetRotationPoint() const
    {
        return m_RotationPoint;
    }

    INL void SetRotation(f32 rotation)
    {
        m_Rotation = rotation;
    }

    INL f32 GetRotation() const
    {
        return m_Rotation;
    }

    INL void SetVisible(bool_t isVisible)
    {
        m_IsVisible = isVisible;
    }

    INL bool_t GetVisible() const
    {
        return m_IsVisible;
    }

    INL bool_t IsAnimated() const
    {
        return m_IsAnimated;
    }

    INL SpriteTexturesListConstPtr GetTexturesList() const
    {
        return m_Atlases;
    }

    INL SpriteFramesListConstPtr GetFramesList() const
    {
        return m_Frames;
    }

private:

} ;

#endif // _CSPRITE_H_
