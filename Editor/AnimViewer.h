#ifndef ANIMVIEWER_H
#define ANIMVIEWER_H

#include "Sprite.h"

#ifdef EDITOR
#include "EdPrec.h"
#else
#include "Prec.h"
#endif

class AnimViewer : public CSprite
{
public:
	AnimViewer ();
	~AnimViewer(void);

	void					Init (const core::position2df& previewPos, 
								  const core::vector2di& previewSize, 
								  const core::position2df& framesPos, 
								  const core::vector2di& framesSize);
	virtual void			Update();
	void					DrawAxes();
	void					DrawFrame(int frameNum);
	void					ScrollFrameLeft();
	void					ScrollFrameRight();

	int						CheckFrameBarCollision(int x, int y);
	bool_t					CheckFrameViewCollision(int x, int y);
	bool_t					IntersectWithPreview(int x, int y);
	bool_t					IntersectWithFrameBar(int x, int y);
	void					Centering();
	void					SetScaleByPoint(float scale, int x, int y);

	SpriteAnimationsListPtr GetAnimationsList() {return m_Animations;}
	void					SetAnimationsList(SpriteAnimationsListPtr newAnimationList);
	const SpriteFramesListPtr GetFramesList() {return m_Frames;}

	bool_t					SetFrameOffset(float offX, float offY, FrameDef& frame);
    core::position2df GetFrameOffset();

private:
	core::position2df	m_PreviewPos;
	core::vector2di		m_PreviewSize;
	core::position2df	m_FramesPos;
	core::vector2di		m_FramesSize;
	int					m_MaxFramesVisible;
	int					m_FramesOffset;
	int					m_FrameScrollPos;
	int					m_SelectedFrame;
};

#endif