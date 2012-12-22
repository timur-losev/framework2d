#pragma once

#include "SpriteDefs.h"

class ZwoptexParser
{
public:
    static SpriteFramesList		 Parse(const std::string& path);
private:
	static TiXmlElement*         FindObjectByKey(TiXmlElement *dict, const char *key = NULL, const char *value = NULL);
	static TiXmlElement*         FindDictByKey(TiXmlElement *dict, const char *key = NULL);
	static int                   FindIntByKey(TiXmlElement *dict, const char *key = NULL);
	static float                 FindRealByKey(TiXmlElement *dict, const char *key = NULL);
	static char*                 FindStringByKey(TiXmlElement *dict, const char *key = NULL);
};
