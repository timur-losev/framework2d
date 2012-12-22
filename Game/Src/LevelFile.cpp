#include "EdPrec.h"

#include "LevelFile.h"

#include "ILevel.h"

bool_t LevelFile::Save(const std::string& path, ILevel* level )
{
    APP_API_ASSERT(level);
    FileStream f;
    APP_API_ASSERT(f.FromFile(path, WRITE_BINARY));

    level->Serialize(f);

    return TRUE;
}

bool_t LevelFile::Load(const std::string& path, ILevel* level)
{
    APP_API_ASSERT(level);
    FileStream f;
    APP_API_ASSERT(f.FromFile(path, READ_BINARY));

#if defined(USE_INVOKER)
    Common::Invoker::PerformCrossThreadCall(std::bind(&ILevel::Deserialize_stub, level, std::ref(f)), level, TRUE);
#else
    level->Deserialize(f);
#endif

    return TRUE;
}

