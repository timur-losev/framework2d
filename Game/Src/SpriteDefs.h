#ifndef _SPRITE_DEFS_H_
#    define _SPRITE_DEFS_H_


//*****************************************************************************
// Textures
//
//*****************************************************************************

struct TextureDef
{

    TextureDef(	const std::string& _name = "",
               video::ITexture* _texture = NULL)
    : name(_name)
    , m_texture(NULL)
    {
        texture(_texture);
    }

    ~TextureDef()
    {
        if (m_texture)
        {
            m_texture->drop();
            m_texture = 0;
        }
    }

    INL void texture(video::ITexture * texture)
    {
        if (m_texture)
        {
            m_texture->drop();
        }
        if (texture)
        {
            m_texture = texture;
            m_texture->grab();
        }
    };

    INL video::ITexture * texture() const
    {
        return m_texture;
    }

    std::string		 name;

private:
    video::ITexture* m_texture;
} ;

typedef core::array<TextureDef> SpriteTexturesList;
typedef std::shared_ptr<SpriteTexturesList> SpriteTexturesListPtr;
typedef std::shared_ptr<SpriteTexturesList const> SpriteTexturesListConstPtr;

//*****************************************************************************
// Frames
//
//*****************************************************************************

struct FrameDef
{
    FrameDef(	std::string _name = "",
             float _left = 0,
             float _top = 0,
             float _right = 0,
             float _bottom = 0,
             float _offsetX = 0,
             float _offsetY = 0,
             float _originalWidth = 0,
             float _originalHeight = 0,
             u32 _animDuration = 50 )
    : textureNum(0)
    , name(_name)
    , left(_left)
    , top(_top)
    , right(_right)
    , bottom(_bottom)
    , offsetX(_offsetX)
    , offsetY(_offsetY)
    , originalWidth(_originalWidth)
    , originalHeight(_originalHeight)
    , animDuration(_animDuration)
    , uid(PE_UINT_MAX)
    {
    }

    u32	textureNum;			// Number of texture which related with this frame
    std::string name;		// Frame name
    float left;				// Position in texture	(0..1)
    float top;				// Position in texture	(0..1)
    float right;			// Position in texture	(0..1)
    float bottom;			// Position in texture	(0..1)
    float offsetX;			// Additional offset on X axis (0..1)
    float offsetY;			// Additional offset on Y axis (0..1)
    float originalWidth;	// Frame width (in px)
    float originalHeight;	// Frame height (in px)
    u32   animDuration;		// Delay, which sprite will show, in ms #TODO: must be moved to animation def

    u32 uid;				//unique id, for service purposes
} ;

typedef core::array<FrameDef> SpriteFramesList;
typedef std::shared_ptr<SpriteFramesList> SpriteFramesListPtr;
typedef std::shared_ptr<SpriteFramesList const> SpriteFramesListConstPtr;

//*****************************************************************************
// Animations
//
//*****************************************************************************

struct AnimationDef
{
    std::string name;			// Animation name
    core::array<int> frames;	// Frames for animation
} ;

typedef core::array<AnimationDef> SpriteAnimationsList;
typedef std::shared_ptr<SpriteAnimationsList> SpriteAnimationsListPtr;
typedef std::shared_ptr<SpriteAnimationsList const> SpriteAnimationsListConstPtr;

#endif