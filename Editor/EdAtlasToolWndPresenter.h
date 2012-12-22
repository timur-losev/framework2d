#ifndef EdAtlasToolWndPresenter_h__
#    define EdAtlasToolWndPresenter_h__

#    include "IEdAtlasToolWndView.h"
#    include "Sprite.h"

#    include "AtlasToolLevel.h"
#    include "LevelManager.h"

class EdAtlasToolWndPresenter
{
private:
    IEdAtlasToolWndView::Ptr                    m_View;
    CLevelManager*				m_LevelMgr;

    SpriteAnimationsListPtr		m_AnimationsList;
    SpriteFramesListPtr			m_FramesList;
	SpriteTexturesNamesListPtr	m_TexturesList;
    u32							m_SelectedAnimation;
    u32							m_SelectedFrame;
    boost::signals::connection  m_SetNameDlgConnection;

    void                                        OnViewShowed();

    void                                        UpdateView();
    void                                        AttachViewSlots();
    void					AttachModelSlots();
    void					OnButtonNew();
    void					OnZoomScrolled(f32 value, int x, int y);
    void					OnOpenFile(const io::path& fname);
    void					OnPlayStopAnim();
    void					OnScrollFrames(bool_t toRight);
    void					OnFrameBarSelected(u32 frame);
    void					OnAnimationLoaded(SpriteAnimationsListPtr animations, SpriteFramesListPtr frames, SpriteTexturesNamesListPtr textures);
    void					OnAnimationSelected(u32 animation);
    void					OnFrameSelected(u32 frame);
    void					OnShowSetNameDialogOkPressed( const core::stringc& name );
    void					OnAddFrameToAnimation(u32 frameNum);
    void					OnButtonRemoveAnimation(u32 animation);
    void					OnButtonRemoveFrame(u32 frame);
    void					OnChangeAnimationDuration(u32 frame, u32 duration);
    void					OnPreviewMouseWheel(int delta, int direction, int x, int y);
    void					OnFrameBarMouseWheel(int delta, int direction, int x, int y);
    void					OnSaveFile(const core::stringc& fname);
    void					OnResize(	const core::position2df& previewPos,
                                                        const core::vector2di& previewSize,
                                                        const core::position2df& framesPos,
                                                        const core::vector2di& framesSize);
    void					OnChangeFrameOffset(u32 frameIndx, int offsetX, int offsetY);
    void					OnFrameChanged(int index, const FrameDef& frame);
    void					OnChangeCursor(int cursor);
public:

    typedef boost::shared_ptr<EdAtlasToolWndPresenter> Ptr;

    EdAtlasToolWndPresenter();
    ~EdAtlasToolWndPresenter();
} ;

#endif // EdAtlasToolWndPresenter_h__
