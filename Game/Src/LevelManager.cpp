#include "EdPrec.h"

#include "LevelManager.h"
#include "ILevel.h"

void LevelManager::Update( float dt, const RenderContext& context )
{
    if (m_CurrentLevel)
        m_CurrentLevel->Update(dt, context);
}

void LevelManager::AttachLevel(ILevelPtr lvl)
{
#ifdef USE_INVOKER
    APP_API_ASSERT(lvl->IsInvokerCreated());
#endif

    m_Levels.push_back(lvl);
    if (m_Levels.size() == 1)
        m_CurrentLevel = lvl;
}

void LevelManager::DetatchLevel(ILevelPtr lvl)
{
    LevelsList::iterator it = m_Levels.begin();
    while(it != m_Levels.end())
    {
        if (*it == lvl)
        {
            m_Levels.erase(it);
            break;
        }

        ++it;
    }

    if (m_CurrentLevel == lvl)
    {
        if (!NextLevel())
            m_CurrentLevel.reset();
    }
}

bool_t LevelManager::NextLevel()
{
    LevelsList::const_iterator iter = m_Levels.begin();
    if (iter == m_Levels.end())
        return FALSE;

    m_CurrentLevel = *iter;

    return TRUE;
}

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{
    CleanUp();
}

bool_t LevelManager::Flush()
{
    if (m_CurrentLevel)
    {
        if (!m_CurrentLevel->Create())
            return FALSE;

        m_CurrentLevel->Init();
    }

    return TRUE;
}

void LevelManager::CleanUp()
{

}

ILevelPtr LevelManager::GetLevelByName(const std::string& lname)
{
    LevelsList::iterator i = m_Levels.begin();
    LevelsList::iterator e = m_Levels.end();

    while(i != e)
    {
        ILevelPtr lvl = *i;
        if (lvl->GetName() == lname)
        {
            return lvl;
        }
        ++i;
    }

    return 0;
}

ILevelPtr LevelManager::CurrentLevel()
{
    return m_CurrentLevel;
}