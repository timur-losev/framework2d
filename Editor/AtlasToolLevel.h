#ifndef AtlasToolLevel_h__
#define AtlasToolLevel_h__

#include "EdPrec.h"
#include "ILevel.h"

#include "Sprite.h"
#include "AnimViewer.h"

#include "EdCommon.h"

enum AnimStates
{
	ANIM_STATE_IDLE = 0,
	ANIM_STATE_MOVE_FRAME,
	ANIM_STATE_MOVE_ATLAS
};

class AtlasToolLevel: public ILevel
{
private:
	typedef boost::signal<void (u32)> OnFrameBarSelectedSignal;
    OnFrameBarSelectedSignal     m_OnFrameBarSelectedSignal;

	typedef boost::signal<void (SpriteAnimationsListPtr, SpriteFramesListPtr, SpriteTexturesNamesListPtr)> OnAnimationLoadedSignal;
    OnAnimationLoadedSignal      m_OnAnimationLoadedSignal;

	typedef boost::signal<void (u32)> OnFrameBarAddFrameSignal;
    OnFrameBarAddFrameSignal     m_OnFrameBarAddFrameSignal;

	typedef boost::signal<void (int, int, int, int) > OnMouseWheelSignal;//delta, direction rotation, x, y
	OnMouseWheelSignal			 m_OnPreviewMouseWheelSignal;
	OnMouseWheelSignal			 m_OnFrameBarMouseWheelSignal;

	typedef boost::signal<void (int index, const FrameDef& frame)> OnFrameUpdatedSignal;
    OnFrameUpdatedSignal         m_OnFrameUpdatedSignal;

	typedef boost::signal<void (int) > OnChangeCursorSignal;
	OnChangeCursorSignal		 m_OnChangeCursorSignal;

public:
	//Model events
    boost::signals::connection AttachOnFrameBarSelectedSignal(const OnFrameBarSelectedSignal::slot_type& slot);
	boost::signals::connection AttachOnAnimationLoadedSignal(const OnAnimationLoadedSignal::slot_type& slot);
	boost::signals::connection AttachOnFrameBarAddFrameSignal(const OnFrameBarAddFrameSignal::slot_type& slot);
	boost::signals::connection AttachOnPreviewMouseWheelSignal(const OnMouseWheelSignal::slot_type& slot);
	boost::signals::connection AttachOnFrameBarMouseWheelSignal(const OnMouseWheelSignal::slot_type& slot);
	boost::signals::connection AttachOnFrameUpdatedSignal(const OnFrameUpdatedSignal::slot_type& slot);
	boost::signals::connection AttachOnChangeCursorSignal(const OnChangeCursorSignal::slot_type& slot);

protected:
	core::position2di       m_MouseEvtPos, m_MouseMovePos;
    int                     m_BtnId;

	AnimViewer*				m_AnimViewer;
	AnimStates				m_State;
	AnimStates				m_PreviousState;

public:

    AtlasToolLevel();
    virtual ~AtlasToolLevel();

	//*******************************************************************************
	//	BASE
	//
	//*******************************************************************************
    virtual void            Update(float dt);
    virtual bool_t          Create();
    virtual bool_t          Init();
    virtual void            Destroy();

	//Mouse events
    void                    OnMouseDown(int, int, int);
    void                    OnMouseUp(int, int, int);
    void                    OnMouseMove(int, int);
	void                    OnMouseDblClick(int btn, int x, int y);
	void                    OnMouseWheel(int delta, int direction, int x, int y);

	//*******************************************************************************
	//	
	//
	//*******************************************************************************
	void					SetPreviewDimesion( const core::position2df& previewPos, 
												const core::vector2di& previewSize, 
												const core::position2df& framesPos, 
												const core::vector2di& framesSize );
	void                    LoadAnimation (const io::path& path);

	void					SetAnimViewerScale(float value, int x, int y);
	void					SetPlayStopAnim();
	void					ScrollFramesTo(bool_t toRight);
	void					SelectAnimation(u32 animation);
	void					SelectFrame(u32 frame);
    void SetAnimationList(SpriteAnimationsListPtr newAnimationList);
	void					ChangeCursorByState(AnimStates state);
	void					ChangeState(AnimStates state);
	void					RestoreState();
};

#endif // AtlasToolLevel_h__
