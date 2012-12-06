#ifndef MAPVIEWER_H
#    define MAPVIEWER_H

#    include "Sprite.h"
class MapViewer : public CSprite
{
private:
    int                     m_SelectedFrame;
    core::position2df       m_PreviewPos;
    core::vector2di         m_PreviewSize;
    core::recti             m_SelectionAnchor;
    bool_t                  m_IsShowAllSelections;
    u32                     m_CurrentTexture;
public:

    enum IntersectSelection
    {
        TOP_LEFT_CORNER = 0,
        TOP_CENTER_CORNER,
        TOP_RIGHT_CORNER,
        RIGHT_CENTER_CORNER,
        BOTTOM_RIGHT_CORNER,
        BOTTOM_CENTER_CORNER,
        BOTTOM_LEFT_CORNER,
        LEFT_CENTER_CORNER,
        BODY_INTERSECT,
        NONE_INTERSECT
    } ;
private:
    const core::recti		GetSelectedFrameAnchorRect(IntersectSelection anchor);
public:

    MapViewer();
    virtual ~MapViewer(void);

    void					Init (const core::position2df& previewPos,
                                                const core::vector2di& previewSize);
    virtual void			Update(DriverPtr driver);

    bool_t					IntersectWithPreview(int x, int y);
    IntersectSelection		IntersectWithSelectedFrame(int x, int y);
    int						IntersectWithShowedFrame(int x, int y);

    INL const SpriteFramesListPtr& GetFramesList() const
    {
        return m_Frames;
    }

    void					AddFrame(const FrameDef& frame);
	bool					AddFrame(const core::recti& frameRect, FrameDef& out);
    void					SelectFrame(u32 index);

    INL int					GetSelectedFrameIndex()
    {
        return m_SelectedFrame;
    }

    INL void				ShowHideSelections()
    {
        m_IsShowAllSelections = !m_IsShowAllSelections;
    }

    INL bool_t				IsShowAllSelection()
    {
        return m_IsShowAllSelections;
    }
    void					UpdateSelectedPosition(int dx, int dy);
    void					UpdateSelectedSize(int dw, int dh);
    void					SetCurrentTexture(int index);
    void					Centering();

    INL int					GetCurrentTexture()
    {
        return m_CurrentTexture;
    }
    void					RemoveFrame(int index);
    void					RemoveTexture(int index);
    void					SetScaleByPoint(float scale, int x, int y);
} ;


#endif