
#include "EdPrec.h"

#include "EditablePagedLevel.h"
#include "Page.h"

float	EditablePagedLevel::DefaultBacklash = 10.f;
float	EditablePagedLevel::StepValue		= 0.15f;
size_t	EditablePagedLevel::MaxPagesInView	= 3;


EditablePagedLevel::EditablePagedLevel(const std::string& name)
    : ILevel(name)
    , m_Locked(FALSE)
    , m_ActivePageIndx(0)
#ifdef EDITOR
    , m_SelectedObject(NULL)
    , m_State(LEVEL_STATE_IDLE)
    , m_PreviousState(LEVEL_STATE_IDLE)
#endif
{
}

EditablePagedLevel::~EditablePagedLevel()
{
}

void EditablePagedLevel::Update( float dt, const RenderContext& context )
{
#ifdef USE_INVOKER
    // update invoker first
    UpdateInvoker();
#endif

    DriverPtr driver = context.Driver;

    if (m_Locked) return;

    for (size_t i = 0; i < MaxPagesInView; ++i)
    {
#ifdef EDITOR
        DebugFontPtr font   = context.DebugFont;

        core::stringw					text		= core::stringw("Page ") + core::stringw(m_PagesInView[i]->GetIndex());
        const core::dimension2d<u32>	scrSize		= driver->getScreenSize();

        core::recti rectangle = core::recti((int)m_PagesInView[i]->GetPosition().X,
            (int)m_PagesInView[i]->GetPosition().Y,
            (int)(m_PagesInView[i]->GetPosition().X + m_PagesInView[i]->GetBound().getWidth()),
            (int)(m_PagesInView[i]->GetPosition().Y + m_PagesInView[i]->GetBound().getHeight()));

        // Fill active page
        //if (m_PagesInView[i]->HitTest(core::position2df((f32)scrSize.Width / 2.f, (f32)scrSize.Height / 2.f)))
        if (i + m_PagesInView[0]->GetIndex() == m_ActivePageIndx)
        {
            driver->draw2DRectangle( video::SColor(128, 206, 206, 206), rectangle );
        }
#endif

        // Update all pages
        m_PagesInView[i]->Update(dt, context);

#ifdef EDITOR
        // Draw restrictive rectangle
        driver->draw2DRectangleOutline( rectangle, video::SColor(255, 0, 255, 0) );

        // Draw page text info
        if (font)
        {
            core::dimension2d<u32> textSize = font->getDimension(text.c_str());
            if (rectangle.UpperLeftCorner.X >= 0 && rectangle.UpperLeftCorner.X + textSize.Width < scrSize.Width &&
                rectangle.UpperLeftCorner.Y >= 0 && rectangle.UpperLeftCorner.Y + textSize.Height < scrSize.Height)
            {
                core::recti textRect = core::recti(rectangle.UpperLeftCorner, textSize);

                font->draw( text, textRect, video::SColor(255, 0, 255, 0) );
            }
        }
#endif
    }
}

bool_t EditablePagedLevel::Create()
{
    return TRUE;
}

void EditablePagedLevel::Init()
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::Init, this));
    }
    else
#endif
    {
        m_PageList.clear();
        m_PagesInView.clear();
        m_SelectedObject = NULL;

        for (size_t i = 0; i < MaxPagesInView; ++i)
        {
            PageInstance* page = new PageInstance();
            APP_API_ASSERT(page->Init(i));

            //Add clear page
            AddPage(page);

            m_PagesInView.push_back(page);
        }
    }
}

void EditablePagedLevel::Destroy()
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::Destroy, this));
    }
    else
#endif
    {
        m_PagesInView.clear();
        m_SelectedObject = NULL;

        for (size_t i = 0; i < m_PageList.size(); ++i)
        {
            PageInstance* page = m_PageList[i];

            page->Destroy();

            APP_API_DEL(page);
        }

        m_PageList.clear();
    }
}

void EditablePagedLevel::AddPage( PageInstance* page )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::AddPage, this, page));
    }
    else
#endif
    {
        if (page->GetIndex() == PE_UINT_MAX)
        {
            page->Init(m_PageList.size());
        }

        m_PageList.push_back(page);
    }
}

void EditablePagedLevel::Scroll(float stepX, float stepY)
{
    for (size_t i = 0; i < m_PageList.size(); ++i)
    {
        m_PageList[i]->Scroll(stepX, stepY);
    }

#ifndef EDITOR
    if (stepX != 0)
    {
        core::position2d<u32> hitpoint = core::position2d<u32>(GVideoDriver->getScreenSize() / 2);

        bool_t hittest = FALSE;
        if (stepX > 0)
        {
            hittest = (m_PagesInView[0]->GetPosition().X + m_PagesInView[0]->GetBound().getWidth() > hitpoint.X);
        }
        else
        {
            hittest = (m_PagesInView.getLast()->GetPosition().X < hitpoint.X);
        }

        if (hittest)
            Rebuild(stepX < 0);

#ifdef DBGMODE
        /*std::string indexes;
        for (size_t i = 0; i < MaxPagesInView; ++i)
        {
        std::string str = std::string(m_PagesInView[i]->GetIndex());
        str += " ";
        indexes += str;
        }

        LogDebug("Pages in view: " << indexes.c_str());*/
#endif // BGMODE
    }
#endif // EDITOR
}

void EditablePagedLevel::Rebuild( bool_t forward )
{
    size_t pagesSize = m_PageList.size();

    if (pagesSize > MaxPagesInView)
    {
        size_t firstIndx = 0;
        size_t halfSize = MaxPagesInView / 2;

        if (m_ActivePageIndx <= halfSize)
        {
            firstIndx = 0;
        }
        else if (m_ActivePageIndx >= pagesSize - halfSize)
        {
            firstIndx = pagesSize - MaxPagesInView;
        }
        else
        {
            firstIndx = m_ActivePageIndx - halfSize;
        }

        for (size_t i = 0; i < MaxPagesInView; ++i)
        {
            m_PagesInView[i] = m_PageList[firstIndx + i];
        }

        /*if (forward)
        {
        size_t index = m_PagesInView.getLast()->GetIndex();
        if (index >= m_PageList.size() - 1)
        {
        //LogDebug("Pages end reached");
        return;
        }

        for (size_t i = 1; i < MaxPagesInView; ++i)
        {
        m_PagesInView[i - 1] = m_PagesInView[i];
        }

        m_PagesInView[MaxPagesInView - 1] = m_PageList[index + 1];
        }
        else
        {
        size_t index = m_PagesInView[0]->GetIndex();
        if (index <= 0)
        {
        //LogDebug("Pages first reached");
        return;
        }

        for (size_t i = MaxPagesInView - 1; i != 0; --i)
        {
        m_PagesInView[i] = m_PagesInView[i - 1];
        }

        m_PagesInView[0] = m_PageList[index - 1];
        }*/
    }
}

#ifdef EDITOR

void EditablePagedLevel::OnMouseDown( int btn, int x, int y )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::OnMouseDown, this, btn, x, y));
    }
    else
#endif
    {
        m_MouseEvtPos.X = x;
        m_MouseEvtPos.Y = y;
        m_BtnId			= btn;

        if (EMB_LEFT == btn)
        {
            core::position2df onpos = core::position2df(float(x), float(y));

            SelectPageByPoint(onpos);

            GameObjectPtr obj = GetEditablePage()->GetGameObjectByPoint(onpos);
            if (obj)
            {
                ChangeState(LEVEL_STATE_MOVE_OBJECT);
                LogDebug("Selected object: " << obj->GetName().c_str());
            }

            m_SelectedObject = obj; //Can be NULL
            //m_OnGameObjectSelectedSignal(obj);
        }
        else if (EMB_RIGHT == btn)
        {
            ChangeState(LEVEL_STATE_MOVE_LEVEL);
        }
    }
}

void EditablePagedLevel::OnMouseUp( int btn, int x, int y )
{
    //int deltaX = x - m_MouseEvtPos.X;
    //int deltaY = y - m_MouseEvtPos.Y;

    if (EMB_LEFT == btn && LEVEL_STATE_MOVE_OBJECT == m_State)
    {
        RestoreState();
        m_SelectedObject = NULL;
    }
    else if (EMB_RIGHT == btn)
    {
        RestoreState();
    }

    m_MouseEvtPos.X = x;
    m_MouseEvtPos.Y = y;
    m_BtnId			= EMB_NONE;
}

void EditablePagedLevel::OnMouseMove( int x, int y )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::OnMouseMove, this, x, y));
    }
    else
#endif
    {
        int deltaX			= x - m_MouseMovePos.X;
        int deltaY			= y - m_MouseMovePos.Y;
        m_MouseMovePos.X	= x;
        m_MouseMovePos.Y	= y;

        if (LEVEL_STATE_MOVE_OBJECT == m_State)
        {
            if (EMB_LEFT == m_BtnId && m_SelectedObject)
            {
                m_SelectedObject->SetPosition(m_SelectedObject->GetPosition() + core::position2df((float)deltaX, (float)deltaY));
            }
            else
            {
                RestoreState();
                m_SelectedObject = NULL;
            }
        }
        else if (LEVEL_STATE_MOVE_LEVEL == m_State)
        {
            if (EMB_RIGHT == m_BtnId)
            {
                Scroll((float)deltaX, (float)deltaY);
            }
            else
            {
                RestoreState();
            }
        }
    }
}

void EditablePagedLevel::OnKeyDown( irr::EKEY_CODE kc )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::OnKeyDown, this, kc));
    }
    else
#endif
    {
        if (kc == KEY_KEY_D)
            Scroll(StepValue, 0);
        else if (kc == KEY_KEY_A)
            Scroll(-StepValue, 0);
        else if (kc == KEY_KEY_W)
            Scroll(0, StepValue);
        else if (kc == KEY_KEY_S)
            Scroll(0, -StepValue);
    }
}
#endif

size_t EditablePagedLevel::GetPageIndexByPoint( const core::position2df& point )
{
    for (size_t i = 0; i < m_PagesInView.size(); i++)
    {
        if (m_PagesInView[i]->HitTest(point))
            return m_PagesInView[i]->GetIndex();
    }

    return PE_UINT_MAX;
}

PageInstance* EditablePagedLevel::GetPageByIndex( size_t i )
{
    if (i < m_PageList.size())
    {
        return m_PageList[i];
    }

    return NULL;
}

PageInstance* EditablePagedLevel::GetEditablePage()
{
    /*size_t i = GetPageIndexByPoint(core::position2df((f32)GVideoDriver->getScreenSize().Width / 2.f, (f32)GVideoDriver->getScreenSize().Height / 2.f));
    if (i == PE_UINT_MAX) return NULL;*/

    return GetPageByIndex(m_ActivePageIndx);
}

void EditablePagedLevel::SelectPageByPoint( const core::position2df& point )
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::SelectPageByPoint, this, point));
    }
    else
#endif
    {
        size_t index = GetPageIndexByPoint( point );

        if (index != m_ActivePageIndx && index < m_PageList.size())
        {
            m_ActivePageIndx = index;

            Rebuild(false);
        }
    }
}

/*boost::signals::connection EditablePagedLevel::AttachOnGameObjectSelectedSignal( const OnGameObjectSelectedSignal::slot_type& slot )
{
return m_OnGameObjectSelectedSignal.connect(slot);
}*/

void EditablePagedLevel::Serialize( DynamicMemoryStream& dms )
{
#ifdef USE_INVOKER
    /*if (NeedInvoke())
    {
    BeginInvoke(std::bind(&EditablePagedLevel::Serialize, this, dms));
    }
    else*/
#endif
    {
        dms.writeUTF8(m_StringID);
        ushort_t count = (ushort_t)m_PageList.size();
        dms.write(&count);

        for (ushort_t i = 0; i < count; ++i)
        {
            m_PageList[i]->Serialize(dms);
        }
    }
}

size_t EditablePagedLevel::Deserialize( MemoryStream& ms )
{
    size_t count		= 0;
    ushort_t pagesCount	= 0;

    ms.readUTF8(m_StringID);
    ms.read(&pagesCount);

    for(ushort_t i = 0; i < pagesCount; ++i)
    {
        PageInstance* page = APP_API_NEW PageInstance();
        AddPage(page);

        count += page->Deserialize(ms);

        if (i < 3)
        {
            m_PagesInView.push_back(page);
        }
    }

    return count;
}

void EditablePagedLevel::LockUnlock( bool_t lock )
{
    m_Locked = lock;
}

#ifdef EDITOR
void EditablePagedLevel::ChangeState(LevelStates state)
{
    if (state != m_PreviousState && state != m_State)
    {
        m_PreviousState = m_State;
    }
    m_State = state;
    //ChangeCursorByState(m_State);
}

void EditablePagedLevel::RestoreState()
{
    m_State = m_PreviousState;
    //ChangeCursorByState(m_State);
}

void EditablePagedLevel::AddEmptyObject(std::string* outName)
{
#ifdef USE_INVOKER
    if (NeedInvoke())
    {
        BeginInvoke(std::bind(&EditablePagedLevel::AddEmptyObject, this, outName));
    }
    else
#endif
    {
        PageInstance* page = GetEditablePage();
        std::ostringstream ss;
        int iter = 0;

        do
        {
            ss.str("");
            ss << "EmptyObject" << iter;
            iter++;
        }
        while(page->GetGameObjectByName(ss.str()) != nullptr);

        page->AddGameObject(ss.str());
        if (outName)
            *outName = ss.str();
    }
}

#endif