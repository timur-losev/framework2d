#ifndef MAPVIEWER_H
#define MAPVIEWER_H

#include "Sprite.h"

#ifdef EDITOR
#include "EdPrec.h"
#else
#include "Prec.h"
#endif

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
};

class MapViewer : public CSprite
{
public:
	MapViewer();
	~MapViewer(void);

	void					Init (const core::position2df& previewPos, 
								  const core::vector2di& previewSize);
	virtual void			Update();

	bool_t					IntersectWithPreview(int x, int y);
	IntersectSelection		IntersectWithSelectedFrame(int x, int y);
	int						IntersectWithShowedFrame(int x, int y);

	INL const SpriteFramesListPtr& GetFramesList() const {return m_Frames;}

	void					AddFrame(const FrameDef frame);
	void					SelectFrame(u32 index);
	INL int					GetSelectedFrameIndex() {return m_SelectedFrame;}
	INL void				ShowHideSelections() {m_IsShowAllSelections = !m_IsShowAllSelections;}
	INL bool_t				IsShowAllSelection() {return m_IsShowAllSelections;}
	void					UpdateSelectedPosition(int dx, int dy);
	void					UpdateSelectedSize(int dw, int dh);
	void					SetCurrentTexture(int index);
	void					Centering();
	INL int					GetCurrentTexture() {return m_CurrentTexture;}
	void					RemoveFrame(int index);
	void					RemoveTexture(int index);
	void					SetScaleByPoint(float scale, int x, int y);

private:
	const core::recti		GetSelectedFrameAnchorRect(IntersectSelection anchor);

private:
	core::position2df		m_PreviewPos;
	core::vector2di			m_PreviewSize;
	int						m_SelectedFrame;
	core::recti				m_SelectionAnchor;
	bool_t					m_IsShowAllSelections;
	u32						m_CurrentTexture;
};


#endif