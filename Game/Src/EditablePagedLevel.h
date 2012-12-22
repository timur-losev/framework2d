#ifndef __PAGEDLEVEL_H__
#    define __PAGEDLEVEL_H__

#    include "ILevel.h"
#    include "GameObject.h"

enum LevelStates
{
    LEVEL_STATE_IDLE = 0,
    LEVEL_STATE_MOVE_OBJECT,
    LEVEL_STATE_MOVE_LEVEL
} ;

class EditablePagedLevel : public ILevel
{
public:
    typedef core::array<PageInstance*>      PageList_t;

    static float                DefaultBacklash;
    static size_t               MaxPagesInView;
    static float                StepValue;
private:

    void                        Rebuild(bool_t forward);

protected:
    PageList_t                  m_PageList;
    PageList_t                  m_PagesInView;
    bool_t                      m_Locked;
    size_t                      m_ActivePageIndx;
public:

    EditablePagedLevel(const std::string& name);
    virtual ~EditablePagedLevel();

    virtual void                Update(float dt, const RenderContext& driver);
    virtual bool_t              Create();
    virtual void                Init();
    virtual void                Destroy();

    void                        AddPage(PageInstance* page);

    void                        Scroll(float deltaX, float deltaY);

    size_t                      GetPageIndexByPoint(const core::position2df& point);
    PageInstance*               GetPageByIndex(size_t i);

    size_t                      GetPagesCount() const;

    void                        SelectPageByPoint(const core::position2df& point);

    virtual void                Serialize(DynamicMemoryStream& dms);
    virtual size_t              Deserialize(MemoryStream& ms);

#    ifdef EDITOR
public:
    //typedef boost::signal<void (GameObjectPtr) > OnGameObjectSelectedSignal;

    //OnGameObjectSelectedSignal	m_OnGameObjectSelectedSignal;

    void                        OnMouseDown(int btn, int x, int y);
    void                        OnMouseUp(int btn, int x, int y);
    void                        OnMouseMove(int x, int y);
    void                        OnKeyDown(irr::EKEY_CODE kc);
    PageInstance*               GetEditablePage();
    //boost::signals::connection	AttachOnGameObjectSelectedSignal(const OnGameObjectSelectedSignal::slot_type& slot);

    void                        ChangeState(LevelStates state);
    void                        RestoreState();
    void                        AddEmptyObject(std::string* outName);
private:
    GameObjectPtr               m_SelectedObject;

    core::position2di           m_MouseEvtPos, m_MouseMovePos;
    int                         m_BtnId;

    LevelStates                 m_State;
    LevelStates                 m_PreviousState;
#    endif

} ;

#endif // __PAGEDLEVEL_H__
