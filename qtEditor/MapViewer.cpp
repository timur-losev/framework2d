#include "EdPrec.h"
#include "MapViewer.h"

MapViewer::MapViewer()
    : m_SelectedFrame(0)
    , m_PreviewPos(core::position2df(0, 0))
    , m_PreviewSize(core::vector2di(0, 0))
    , m_SelectionAnchor(core::recti(-3, -3, 3, 3))
    , m_IsShowAllSelections(FALSE)
    , m_CurrentTexture(0)
{
}

MapViewer::~MapViewer(void)
{
}

void MapViewer::Init(const irr::core::position2df &previewPos, const irr::core::vector2di &previewSize)
{
    m_PreviewPos = previewPos;
    m_PreviewSize = previewSize;

    m_Frames.reset(new SpriteFramesList());
    m_Animations.reset(new SpriteAnimationsList());

    Centering();
}

void MapViewer::Update( const RenderContext& context )
{
    m_Driver = context.Driver;

    if (m_TotalTextures == 0) return;

    // Draw texture
    APP_API_ASSERT(m_CurrentTexture < m_Atlases->size());
    video::ITexture* nativeTexture = m_Atlases->get(m_CurrentTexture).texture();

    f32 curTextureWidth = static_cast<f32>(nativeTexture->getSize().Width);
    f32 curTextureHeight = static_cast<f32>(nativeTexture->getSize().Height);
    core::rectf atlasRect =  core::rectf (0, 0, curTextureWidth, curTextureHeight);

    Draw2DImage(m_Driver, nativeTexture, atlasRect, m_Position, m_RotationPoint, m_Rotation,
        m_Scale, true,  video::SColor(255, 255, 255, 255));

    // Draw restrictive rectangle
    const core::dimension2du& atlasSize = nativeTexture->getSize();
    core::recti frameRect = core::recti(
        (int) m_Position.X,
        (int) m_Position.Y,
        (int) (m_Position.X + atlasSize.Width * m_Scale.X),
        (int) (m_Position.Y + atlasSize.Height * m_Scale.Y));

    m_Driver->draw2DRectangleOutline( frameRect,
        video::SColor(255, 255, 255, 255) );

    if (m_IsShowAllSelections)
    {
        for (size_t i = 0; i < m_TotalFrames; ++i)
        {
            const FrameDef& frame = m_Frames->get(i);

            if (frame.textureNum != m_CurrentTexture)
            {
                continue;
            }

            frameRect =  core::recti((int) (m_Position.X + frame.left   * atlasSize.Width  * m_Scale.X),
                (int) (m_Position.Y + frame.top    * atlasSize.Height * m_Scale.Y),
                (int) (m_Position.X + frame.right  * atlasSize.Width  * m_Scale.X),
                (int) (m_Position.Y + frame.bottom * atlasSize.Width  * m_Scale.X));
            m_Driver->draw2DRectangleOutline( frameRect, video::SColor(255, 255, 255, 255) );
        }
    }
    // Draw selected frame rect and anchors
    if (m_SelectedFrame >= 0 && m_SelectedFrame < (int) m_TotalFrames)
    {
        const FrameDef& frame = m_Frames->get(m_SelectedFrame);

        if (frame.textureNum != m_CurrentTexture)
        {
            m_SelectedFrame = -1;
            return;
        }

        frameRect =  core::recti((int) (m_Position.X + frame.left   * atlasSize.Width  * m_Scale.X),
            (int) (m_Position.Y + frame.top    * atlasSize.Height * m_Scale.Y),
            (int) (m_Position.X + frame.right  * atlasSize.Width  * m_Scale.X),
            (int) (m_Position.Y + frame.bottom * atlasSize.Width  * m_Scale.X));
        m_Driver->draw2DRectangle(video::SColor(127, 255, 255, 255), frameRect);
        // Draw anchors, not optimized
        for (int i = TOP_LEFT_CORNER; i < NONE_INTERSECT; ++i)
        {
            m_Driver->draw2DRectangle(video::SColor(200, 0, 255, 0), GetSelectedFrameAnchorRect( (IntersectSelection)i ));
        }
    }
}

bool_t MapViewer::IntersectWithPreview(int x, int y)
{
    if (x >= m_PreviewPos.X && y >= m_PreviewPos.Y &&
        x <= m_PreviewPos.X + m_PreviewSize.X && y <= m_PreviewPos.Y + m_PreviewSize.Y)
    {
        return true;
    }

    return false;
}

MapViewer::IntersectSelection MapViewer::IntersectWithSelectedFrame(int x, int y)
{
    if (m_SelectedFrame >= 0 && m_SelectedFrame < (int) m_TotalFrames && m_TotalTextures > 0)
    {
        for (int i = TOP_LEFT_CORNER; i < NONE_INTERSECT; ++i)	 // tmp
        {
            core::recti frameRect = GetSelectedFrameAnchorRect((IntersectSelection) i);

            if (i == BODY_INTERSECT)
            {
                const FrameDef& frame = m_Frames->get(m_SelectedFrame);
                const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

                frameRect = core::recti((int) (m_Position.X + frame.left   * atlasSize.Width  * m_Scale.X),
                    (int) (m_Position.Y + frame.top    * atlasSize.Height * m_Scale.Y),
                    (int) (m_Position.X + frame.right  * atlasSize.Width  * m_Scale.X),
                    (int) (m_Position.Y + frame.bottom * atlasSize.Width  * m_Scale.X));
            }

            if (frameRect.isPointInside(core::vector2d<s32 > (x, y)))
            {
                return (IntersectSelection) i;
            }
        }
    }

    return NONE_INTERSECT;
}

int MapViewer::IntersectWithShowedFrame(int x, int y)
{
    if (m_IsShowAllSelections && m_TotalTextures)
    {
        for (size_t i = 0; i < m_TotalFrames; ++i)
        {
            const FrameDef& frame = m_Frames->get(i);
            const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

            core::recti frameRect = core::recti((int) (m_Position.X + frame.left   * atlasSize.Width  * m_Scale.X),
                (int) (m_Position.Y + frame.top    * atlasSize.Height * m_Scale.Y),
                (int) (m_Position.X + frame.right  * atlasSize.Width  * m_Scale.X),
                (int) (m_Position.Y + frame.bottom * atlasSize.Width  * m_Scale.X));

			if (frame.textureNum == m_CurrentTexture &&
				frameRect.isPointInside(core::vector2d<s32 > (x, y)))
            {
                return i;
            }
        }
    }

    return -1;
}

void MapViewer::AddFrame(const FrameDef& frame)
{
    m_Frames->push_back(frame);
    m_TotalFrames = m_Frames->size();
}

bool MapViewer::AddFrame(const core::recti& frameRect, FrameDef& out)
{
    if (m_TotalTextures == 0)
    {
        return false;
    }

    std::string name = std::to_string((long long)m_Frames->size());
    out = FrameDef(name, (float)frameRect.UpperLeftCorner.X, (float)frameRect.UpperLeftCorner.Y);
    const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

    out.left = (frameRect.UpperLeftCorner.X - m_Position.X) / (atlasSize.Width * m_Scale.X);
    out.top = (frameRect.UpperLeftCorner.Y - m_Position.Y) / (atlasSize.Height * m_Scale.Y);
    out.right = (frameRect.LowerRightCorner.X - m_Position.X) / (atlasSize.Width * m_Scale.X);
    out.bottom = (frameRect.LowerRightCorner.Y - m_Position.Y) / (atlasSize.Height * m_Scale.Y);
    out.textureNum = m_CurrentTexture;

	m_Frames->push_back(out);
	m_TotalFrames = m_Frames->size();

    return true;
}

void MapViewer::SelectFrame(u32 index, bool isNeedSwitchTexture)
{
    m_SelectedFrame = -1;
    if (index >= 0 && index < m_Frames->size())
    {
        m_SelectedFrame = index;

		u32 textureIndx = m_Frames->get(index).textureNum;

		if (isNeedSwitchTexture && m_CurrentTexture != textureIndx)
		{
			SetCurrentTexture(textureIndx);
			Centering();
		}
    }
}

const core::recti MapViewer::GetSelectedFrameAnchorRect(IntersectSelection anchor)
{
    core::recti frameRect = core::recti(0, 0, 0, 0);

    if (m_SelectedFrame >= 0 && m_SelectedFrame < (int) m_TotalFrames && m_TotalTextures)
    {
        const FrameDef& frame = m_Frames->get(m_SelectedFrame);
        const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

        core::recti normalized = core::recti((int) (m_Position.X + frame.left   * atlasSize.Width  * m_Scale.X),
            (int) (m_Position.Y + frame.top    * atlasSize.Height * m_Scale.Y),
            (int) (m_Position.X + frame.right  * atlasSize.Width  * m_Scale.X),
            (int) (m_Position.Y + frame.bottom * atlasSize.Width  * m_Scale.X));
        switch (anchor)
        {
        case TOP_LEFT_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case TOP_CENTER_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + normalized.getWidth() / 2 + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X + normalized.getWidth() / 2 + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case TOP_RIGHT_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + normalized.getWidth() + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X + normalized.getWidth() + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case RIGHT_CENTER_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + normalized.getWidth() + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() / 2 + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X + normalized.getWidth() + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() / 2 + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case BOTTOM_RIGHT_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + normalized.getWidth() + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X + normalized.getWidth() + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case BOTTOM_CENTER_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + normalized.getWidth() / 2 + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X  + normalized.getWidth() / 2 + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case BOTTOM_LEFT_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case LEFT_CENTER_CORNER:
            frameRect = core::recti(normalized.UpperLeftCorner.X + m_SelectionAnchor.UpperLeftCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() / 2 + m_SelectionAnchor.UpperLeftCorner.Y,
                normalized.UpperLeftCorner.X + m_SelectionAnchor.LowerRightCorner.X,
                normalized.UpperLeftCorner.Y + normalized.getHeight() / 2 + m_SelectionAnchor.LowerRightCorner.Y );
            break;

        case BODY_INTERSECT:
        case NONE_INTERSECT:
            break;
        };
    }

    return frameRect;
}

void MapViewer::UpdateSelectedPosition(int dx, int dy)
{
    if (m_SelectedFrame >= 0 && m_SelectedFrame < (int) m_TotalFrames && m_TotalTextures)
    {
		FrameDef& frame = m_Frames->get(m_SelectedFrame);
        const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

        frame.left += dx / (m_Scale.X * atlasSize.Width);
        frame.top += dy / (m_Scale.Y * atlasSize.Height);
		// restrictions
		if (frame.left > frame.right) frame.left = frame.right;
		if (frame.top > frame.bottom) frame.top = frame.bottom;
		if (frame.left < 0.f) frame.left = 0.f;
		if (frame.top < 0.f) frame.top = 0.f;
    }
}

void MapViewer::UpdateSelectedSize(int dw, int dh)
{
    if (m_SelectedFrame >= 0 && m_SelectedFrame < (int) m_TotalFrames && m_TotalTextures)
    {
        FrameDef& frame = m_Frames->get(m_SelectedFrame);
        const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

        frame.right += (float) (dw / (m_Scale.X * atlasSize.Width));
        frame.bottom += (float) (dh / (m_Scale.Y * atlasSize.Height));
		// restrictions
        if (frame.right < frame.left) frame.right = frame.left;
        if (frame.bottom < frame.top) frame.bottom = frame.top;
		if (frame.right > 1.f) frame.right = 1.f;
		if (frame.bottom > 1.f) frame.bottom = 1.f;
    }
}

void MapViewer::SetCurrentTexture(int index)
{
    if (index >= 0 && index < (int) m_TotalTextures)
    {
        m_CurrentTexture = index;
    }
}

void MapViewer::Centering()
{
    if (m_CurrentTexture < m_TotalTextures)
    {
        const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

        m_Position = core::position2df( (float) ((m_PreviewSize.X - m_PreviewPos.X) / 2.0 - atlasSize.Width * m_Scale.X / 2),
            (float) ((m_PreviewSize.Y - m_PreviewPos.Y) / 2.0 - atlasSize.Height * m_Scale.Y / 2) );
    }
}

void MapViewer::RemoveFrame(int index)
{
    if (index >= 0 && index < (int) m_TotalFrames)
    {
        m_Frames->erase(index);

        m_TotalFrames = m_Frames->size();
        m_SelectedFrame = -1;
    }
}

void MapViewer::RemoveTexture(int index)
{
    if (index >= 0 && index < (int) m_TotalTextures)
    {
        m_Driver->removeTexture(m_Atlases->get(index).texture());
        m_Atlases->erase(index);

        m_TotalTextures = m_Atlases->size();

        if (m_CurrentTexture >= m_TotalTextures && m_TotalTextures > 0)
        {
            m_CurrentTexture = m_TotalTextures - 1;
        }
    }
}

void MapViewer::SetScaleByPoint(float scale, int x, int y)
{
    if (m_CurrentTexture < m_TotalTextures)
    {
        scale *= m_Scale.X;

        const core::dimension2du& atlasSize = m_Atlases->get(m_CurrentTexture).texture()->getSize();

        core::position2df leftCorner = core::position2df(m_Position.X, m_Position.Y);
        core::position2df rightCorner = core::position2df(atlasSize.Width * m_Scale.X + m_Position.X,
            atlasSize.Height * m_Scale.Y + m_Position.Y);
        if (x >= leftCorner.X  && y >= leftCorner.Y &&
            x <= rightCorner.X && y <= rightCorner.Y)
        {
            float deltaX = x - m_Position.X;
            float deltaY = y - m_Position.Y;

            deltaX = (scale - m_Scale.X) * deltaX / m_Scale.X;
            deltaY = (scale - m_Scale.Y) * deltaY / m_Scale.Y;

            m_Position.X -= deltaX;
            m_Position.Y -= deltaY;
        }
    }

    m_Scale = core::vector2df(scale, scale);
}

int MapViewer::GetSelectedFrameIndex()
{
    return m_SelectedFrame;
}

void MapViewer::ShowHideSelections(bool isShow)
{
    m_IsShowAllSelections = isShow;
}

bool_t MapViewer::IsShowAllSelection()
{
    return m_IsShowAllSelections;
}

const SpriteFramesListPtr& MapViewer::GetFramesList() const
{
    return m_Frames;
}

bool MapViewer::ChangeFrameProperties(unsigned int index, unsigned int prop, const std::string& value)
{
	if (index > m_TotalFrames)
	{
		return false;
	}

	/* prop:
		0 - Name
		1 - left tex coord
		2 - top tex coord 
		3 - right tex coord 
		4 - bottom tex coord 
	*/

	FrameDef& editedFrame = m_Frames->get(index);

	if (0 == prop)	// name
	{
		// Checking if name already taken
		for (size_t i = 0; i < m_TotalFrames; ++i)
		{
			const FrameDef& frame = m_Frames->get(i);
			if (value == frame.name && i != index)
			{
				return false;
			}
		}

		editedFrame.name = value;
	}
	else 
	{
		float fValue = (float)atof(value.c_str());

		// check validity
		if ((0.f > fValue || 1.f < fValue) ||				// coord positions cannot be negative or greater than 1
			(1 == prop && fValue > editedFrame.right) ||	// left > right?
			(3 == prop && fValue < editedFrame.left) ||		// right < left?
			(2 == prop && fValue > editedFrame.bottom) ||	// top > bottom?
			(4 == prop && fValue < editedFrame.top))		// bottom < top?
		{
			return false;
		}

		editedFrame.left	= (1 == prop) ? fValue : editedFrame.left;
		editedFrame.top		= (2 == prop) ? fValue : editedFrame.top;
		editedFrame.right	= (3 == prop) ? fValue : editedFrame.right;
		editedFrame.bottom	= (4 == prop) ? fValue : editedFrame.bottom;
	}

	return true;
}
