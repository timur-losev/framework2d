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
    core::position2df       m_AbsolutePosition;
    core::vector2df         m_Scale;
    core::position2df       m_RotationPoint;
    f32                     m_Rotation;
    bool_t                  m_IsVisible;
    bool_t                  m_IsAnimated;

    SpriteFramesListPtr     m_Frames;
    SpriteAnimationsListPtr m_Animations;
    SpriteTexturesListPtr	m_Atlases;

    DriverPtr               m_Driver;

    void                    Draw2DImage (DriverPtr driver,
                                         video::ITexture* texture,
                                         const core::rectf& sourceRect, const core::position2df& position,
                                         const core::position2df& rotationPoint, f32 rotation, const core::vector2df& scale,
                                         bool useAlphaChannel, const video::SColor& color);
public:

    SpriteInstance(void);
    virtual ~SpriteInstance(void);

    virtual void           Update(float dt, const RenderContext& context);

    void                   Load(const std::string& resName);
    bool_t                 LoadTexture(const std::string& resName, video::ITexture* out);

    void                   Stop();
    void                   Play();
    void                   GotoAndStop(u32 frameIndx);
    void                   GotoAndPlay(u32 frameIndx);

    u32                    GetTotalAnimations() const;
    u32                    GetCurrentAnimation() const;

    void                   SetCurrentAnimation(u32 animationIndx);
    u32                    GetAnimationFrames() const;

    u32                    GetCurrentFrame() const;

    u32                    GetTotalFrames() const;
    // Properties

    void                   SetPosition(const core::position2df& position, EPosRelation r = RELATIVE_POS);
    const core::position2df& GetPosition(EPosRelation r = RELATIVE_POS) const;

    void                   SetScale(const core::vector2df& scale);
    const core::vector2df& GetScale() const;

    void                   SetRotationPoint(const core::position2df& rotationPoint);
    const core::position2df& GetRotationPoint() const;

    void                   SetRotation(f32 rotation);
    f32                    GetRotation() const;

    void                   SetVisible(bool_t isVisible);
    bool_t                 GetVisible() const;

    void                   SetOffset(const core::position2df& off);
    const core::position2df& GetOffset() const;

    bool_t                 IsAnimated() const;
    bool_t                 IsEmpty() const;

    SpriteTexturesListConstPtr GetTexturesList() const;
    SpriteFramesListConstPtr GetFramesList() const;

    bool_t                  HitTest(const core::position2df& in) const;

} ;

#endif // _CSPRITE_H_
