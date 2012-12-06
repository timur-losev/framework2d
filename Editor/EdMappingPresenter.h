#ifndef EdMappingPresenter_h__
#    define EdMappingPresenter_h__

#    include "IEdMappingToolWndView.h"
#    include "MappingToolLevel.h"
#    include "LevelManager.h"

class EdMappingPresenter
{
private:
    IEdMappingToolWndView::Ptr    m_View;
    MappingToolLevel*             m_Level;
    CLevelManager*                m_LevelMgr;
	SpriteFramesListPtr           m_FramesList;
	SpriteAnimationsListPtr       m_AnimationsList;
	SpriteTexturesNamesListPtr    m_TexturesList;

    //*******************************************************************************
    //
    //
    //*******************************************************************************
    void                    OnViewShowed();
    void                    OnOpenImage(const io::path&);
    void                    OnSaveMappingFile(const io::path&);
    void                    OnOpenMappingFile(const io::path&);
    void                    OnClearSelections();
    void                    OnSelectionAdded(const FrameDef& frame);
    void                    OnShowSetNameDialog();
    void                    OnShowSetNameDialogOkPressed(const core::stringc& name);
    void					OnZoomScrolled(f32 value, int x, int y);
    void					OnPreviewMouseWheel(int delta, int direction, int x, int y);
    void					OnFrameSelecting();
    void					OnShowHideSelections();
    void					OnChangeCursor(int cursor);
    void					OnFrameChanged(int index, const FrameDef& frame);
    void					OnResize(const core::position2df& previewPos, const core::vector2di& previewSize);
    void					OnChangeCurrentTexture(int index);
    void					OnRemoveFrame(int index);
    void					OnRemoveTexture(int index);
    void					OnChangeSelectedFrame(int index);

    //*******************************************************************************
    //
    //
    //*******************************************************************************
    void                    UpdateView();
    void                    AttachViewSlots();
    void                    AttachModelSlots();
public:

    typedef boost::shared_ptr<EdMappingPresenter> Ptr;

    EdMappingPresenter();
    ~EdMappingPresenter();
} ;

#endif // EdMappingPresenter_h__

