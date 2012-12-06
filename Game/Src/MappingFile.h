#ifndef MAPPINGFILE_H__
#define MAPPINGFILE_H__

#include "SpriteDefs.h"

class MappingFile
{
private:

public:
    MappingFile();
    ~MappingFile();

	static bool_t                  Save(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr textures, bool_t IsBinary = true);
    static bool_t                  Load(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr texturesNames);

	static bool_t                  SaveXML(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr textures);
	static bool_t                  LoadXML(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr texturesNames);
};

#endif // MAPPINGFILE_H__
