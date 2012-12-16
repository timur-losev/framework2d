#ifndef LevelManager_h__
#define LevelManager_h__

#include "ILevel.h"

SHARED_PTR_FORWARD(ILevel);

class LevelManager
{
private:
    typedef std::list<ILevelPtr> LevelsList;
    LevelsList                  m_Levels;
    ILevelPtr                   m_CurrentLevel;

protected:
    void                    CleanUp();
public:
    LevelManager();
    ~LevelManager();

    void                    AttachLevel(ILevelPtr lvl);
    void                    DetatchLevel(ILevelPtr lvl);
    void                    Update(float dt, const RenderContext&);

    // Returns FALSE if next level could not be reached
    bool_t                  NextLevel();

    bool_t                  Flush();

    ILevelPtr               GetLevelByName(const std::string& name);
    ILevelPtr               CurrentLevel();
};

#endif // LevelManager_h__
