#ifndef LevelFile_h__
#define LevelFile_h__

class LevelFile
{
public:
    static bool_t           Save(const std::string& path, ILevel* level);
    static bool_t           Load(const std::string& path, ILevel* level);
};

#endif // LevelFile_h__
