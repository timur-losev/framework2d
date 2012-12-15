#include "EdPrec.h"

#include "AssetsManager.h"
#include "MappingFile.h"

SINGLETON_SETUP(AssetsManager);

AssetsManager::AssetsManager()
{
    SINGLETON_ENABLE_THIS;
}

AssetsManager::~AssetsManager()
{

}

bool_t AssetsManager::GetMapping( const std::string& path, SpriteFramesListPtr& sels, SpriteAnimationsListPtr& anims, SpriteTexturesListPtr& textures )
{
    hash_t key = APP_API_STRHASH(path.c_str(), path.size());

    MappingTable_t::iterator n = m_MappingTable.find(key);

    if (n != m_MappingTable.end())
    {
        sels		= n->second->frames;
        textures	= n->second->textures;
        anims		= n->second->animations;

        return TRUE;
    }

    SpriteFramesListPtr			_sels(new SpriteFramesList());
    SpriteTexturesListPtr		_textures(new SpriteTexturesList());
    SpriteAnimationsListPtr		_anims(new SpriteAnimationsList());

    if (!MappingFile::Load(path, _sels, _anims, _textures))
        return FALSE;

    SpriteTablePtr stp(new SpriteTable(_sels, _anims, _textures));

    m_MappingTable[key] = stp;

#ifdef DBGMODE
    MappingFileTexturesTable_t::iterator pn = m_MappingFilesCache.find(key);
    APP_API_ASSERT(m_MappingFilesCache.end() == pn && "Detected collisions. Hash functions works incorrect.")
#endif

        m_MappingFilesCache[key] = APP_API_GET_SIMPLE_FILE_NAME(path.c_str());

    //clone
    sels		= _sels;
    textures	= _textures;
    anims		= _anims;

    return TRUE;
}

void AssetsManager::ClearMappingTable()
{
    m_MappingTable.clear();
    m_MappingFilesCache.clear();
}

void AssetsManager::ClearAll()
{
    ClearMappingTable();
}

void AssetsManager::Clear(const std::string& path)
{
    hash_t key = APP_API_STRHASH(path.c_str(), path.size());

    m_MappingTable.erase(key);
    m_MappingFilesCache.erase(key);
}

const std::string& AssetsManager::GetOrigin( hash_t frameUid ) const
{
    MappingFileTexturesTable_t::const_iterator n = m_MappingFilesCache.find(frameUid);
    APP_API_ASSERT(n != m_MappingFilesCache.end()  && "Files cache is not contain that element.");

    return n->second;
}

FrameDef* AssetsManager::GetFrame( const std::string& origin, const std::string& framename)
{
    FrameDef* ret = NULL;

    /*SpriteFramesListPtr sels_in(new SpriteFramesList());
    SpriteAnimationsListPtr animations_in(new SpriteAnimationsList());
    SpriteTexturesListPtr textures_in(new SpriteTexturesList());

    if (AssetsManager::GetMapping( MEDIA_PATH + origin, sels_in, animations_in, textures_in))
    {
        for (size_t i = 0 ; i < sels_in->size(); ++i)
        {
            if (sels_in->get(i).name == framename)
            {
                ret = &sels_in->get(i);
                break;
            }
        }
    }*/

    return ret;
}