#include "EdPrec.h"

#include "ZwoptexParser.h"

TiXmlElement* ZwoptexParser::FindObjectByKey(TiXmlElement *dict, const char *key, const char *value)
{
	while (dict)
	{
		if (!APP_API_STRCMP(dict->Value(), "key") &&
			(key == NULL || !APP_API_STRCMP(dict->GetText(), key)) &&
			(value == NULL || !APP_API_STRCMP(dict->NextSiblingElement()->Value(), value)))
		{
			return dict->NextSiblingElement();
		}

		dict = dict->NextSiblingElement("key");
	}

	return NULL;
}

TiXmlElement* ZwoptexParser::FindDictByKey(TiXmlElement *dict, const char *key)
{
	TiXmlElement* result = FindObjectByKey(dict, key, "dict");
	if (result)
	{
		return result->FirstChildElement();
	}

	return NULL;
}

int ZwoptexParser::FindIntByKey(TiXmlElement *dict, const char *key)
{
	TiXmlElement* result = FindObjectByKey(dict, key, "integer");
	if (result)
	{
		return APP_API_ATOI(result->GetText());
	}

	return 0;
}

float ZwoptexParser::FindRealByKey(TiXmlElement *dict, const char *key)
{
	TiXmlElement* result = FindObjectByKey(dict, key, "real");
	if (result)
	{
		return (float)APP_API_ATOF(result->GetText());
	}

	return 0;
}

char* ZwoptexParser::FindStringByKey(TiXmlElement *dict, const char *key)
{
	TiXmlElement* result = FindObjectByKey(dict, key, "string");
	if (result)
	{
		return APP_API_STRNEW(result->GetText());
	}

	return NULL;
}

SpriteFramesList ZwoptexParser::Parse(const std::string& path)
{
    SpriteFramesList result;
	/*TiXmlDocument doc(path.c_str());
	TiXmlElement* elem;
	TiXmlHandle root(0);

	if (doc.LoadFile())
	{
		elem = doc.FirstChildElement();

		if (!elem) return result;
		root = TiXmlHandle(elem);

		elem=root.FirstChild( "dict" ).FirstChild("key").Element();
		// find frames block
		elem = FindDictByKey(elem, "frames");
		while (elem)// all files
		{
			if (!APP_API_STRCMP(elem->Value(), "key") &&
				elem->NextSiblingElement("dict") != NULL)
			{
				TiXmlElement* blockElement = elem->NextSiblingElement("dict")->FirstChildElement();
				// read frame data
				FrameDef frame = FrameDef();

                frame.name			= elem->GetText();
				frame.x				= (float)FindIntByKey(blockElement, "x");
				frame.y				= (float)FindIntByKey(blockElement, "y");
				frame.width			= (float)FindIntByKey(blockElement, "width");
				frame.height		= (float)FindIntByKey(blockElement, "height");
				frame.offsetX		= (float)FindIntByKey(blockElement, "offsetX");
				frame.offsetY		= (float)FindIntByKey(blockElement, "offsetY");
				frame.originalWidth = (float)FindIntByKey(blockElement, "originalWidth");
				frame.originalHeight = (float)FindIntByKey(blockElement, "originalHeight");

				result.push_back(frame);
			}

			elem = elem->NextSiblingElement("key");
		}
	}*/

	return result;
}
