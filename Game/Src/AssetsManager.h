#ifndef AssetsManager_h__
#    define AssetsManager_h__


#    include "Singleton.h"
#    include "SpriteDefs.h"
#    include <SharedPointer.h>

class AssetsManager : public Common::Singleton<AssetsManager>
{
private:
protected:

    SHARED_PTR_FORWARD_S(SpriteTable);

    struct SpriteTable
    {

        SpriteTable(SpriteFramesListPtr _frames,
                    SpriteAnimationsListPtr _animations,
                    SpriteTexturesListPtr _textures)
        : frames(_frames)
        , animations(_animations)
        , textures(_textures)
        {
        }

        SpriteFramesListPtr		frames;
        SpriteAnimationsListPtr	animations;
        SpriteTexturesListPtr	textures;
    } ;

    typedef std::map<hash_t, SpriteTablePtr> MappingTable_t;
    typedef std::map<hash_t, SpriteAnimationsListPtr> AnimationsTable_t;
    typedef std::map<hash_t, std::string> MappingFileTexturesTable_t;

    MappingTable_t				m_MappingTable;
    AnimationsTable_t			m_AnimationsTable;
    MappingFileTexturesTable_t	m_MappingFilesCache;
public:

    AssetsManager();
    ~AssetsManager();

    bool_t                  GetMapping(const std::string& path, SpriteFramesListPtr& sels, SpriteAnimationsListPtr& anims, SpriteTexturesListPtr& textures);
    FrameDef*               GetFrame(const std::string& origin, const std::string& framename);

    //returns file name associated with their hash
    const std::string&    GetOrigin(hash_t frameUid) const ;

    void                    ClearMappingTable();
    void                    ClearAll();
    void					Clear(const std::string& path);
} ;

#endif // AssetsManager_h__
