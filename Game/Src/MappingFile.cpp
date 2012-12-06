#ifdef EDITOR
#include "EdPrec.h"
#else
#include "Prec.h"
#endif

#include "MappingFile.h"

MappingFile::MappingFile()
{

}

MappingFile::~MappingFile()
{

}

bool_t MappingFile::Save(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr textures, bool_t IsBinary)
{
#ifdef USE_LOADING_FROM_XML
	if (FALSE == IsBinary)
	{
		return MappingFile::SaveXML(path, frames, animations, textures);
	}
#endif

    FileStream fileStream;
    if (fileStream.FromFile(path, WRITE_BINARY) != TRUE)
        return FALSE;

    size_t frameCount		= frames->size();
	size_t animationCount	= animations->size();
	size_t textureCount		= textures->size();

    fileStream.write(&textureCount);
	for (size_t i = 0; i < textureCount; ++i)
	{
		fileStream.writeUTF8(textures->get(i).name);
	}

	fileStream.write(&frameCount);
    for (size_t i = 0; i < frameCount; ++i)
    {
        fileStream.writeUTF8(frames->get(i).name);
		fileStream.write(&frames->get(i).textureNum);
		fileStream.write(&frames->get(i).left);
		fileStream.write(&frames->get(i).top);
		fileStream.write(&frames->get(i).right);
		fileStream.write(&frames->get(i).bottom);
		fileStream.write(&frames->get(i).offsetX);
		fileStream.write(&frames->get(i).offsetY);
		fileStream.write(&frames->get(i).originalWidth);
		fileStream.write(&frames->get(i).originalHeight);
		fileStream.write(&frames->get(i).animDuration);
    }

	fileStream.write(&animationCount);
    for (size_t i = 0; i < animationCount; ++i)
    {
		fileStream.writeUTF8(animations->get(i).name);

		size_t frameCount = animations->get(i).frames.size();
		fileStream.write(&frameCount);
		for (size_t j = 0; j < frameCount; ++j)
		{
			fileStream.write(&animations->get(i).frames[j]);
		}
    }

    fileStream.Flush();

    return TRUE;
}

bool_t MappingFile::Load(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr textures)
{
#ifdef USE_LOADING_FROM_XML
	if (FALSE == MappingFile::LoadXML(path, frames, animations, textures))
	{
		frames->clear();
		animations->clear();
		textures->clear();
	}
	else
	{
		return TRUE;
	}
#endif

	FileStream fileStream;
    if (fileStream.FromFile(path, READ_BINARY) != TRUE)
        return FALSE;

    size_t frameCount		= 0;
	size_t animationsCount	= 0;
	size_t textureCount		= 0;

    hash_t uid = APP_API_STRHASH(path.c_str(), path.size());

    fileStream.read(&textureCount);
	for (size_t i = 0; i < textureCount; ++i)
	{
		std::string textureName;
		fileStream.readUTF8(textureName);

		TextureDef texture = TextureDef(textureName);
        textures->push_back(textureName);
	}

	fileStream.read(&frameCount);
    for (size_t i = 0; i < frameCount; ++i)
    {
        FrameDef frame = FrameDef();

        fileStream.readUTF8(frame.name);

        fileStream.read(&frame.textureNum);
        fileStream.read(&frame.left);
		fileStream.read(&frame.top);
		fileStream.read(&frame.right);
		fileStream.read(&frame.bottom);
		fileStream.read(&frame.offsetX);
		fileStream.read(&frame.offsetY);
		fileStream.read(&frame.originalWidth);
		fileStream.read(&frame.originalHeight);
		fileStream.read(&frame.animDuration);
        frame.uid = uid;

        frames->push_back(frame);
    }

	fileStream.read(&animationsCount);
    for (size_t i = 0; i < animationsCount; ++i)
    {
		AnimationDef animation = AnimationDef();
		int aframesCount;

		fileStream.readUTF8(animation.name);

		fileStream.read(&aframesCount);
		for (int j = 0; j < aframesCount; ++j)
		{
			int frameIndx;
			fileStream.read(&frameIndx);
			animation.frames.push_back(frameIndx);
		}

		animations->push_back(animation);
	}

    return TRUE;
}

#ifdef USE_LOADING_FROM_XML

bool_t MappingFile::SaveXML(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr textures)
{
	TiXmlDocument xmlDoc;
	TiXmlDeclaration* xmlDecl = new TiXmlDeclaration( "1.0", "", "" );
	xmlDoc.LinkEndChild( xmlDecl );

	TiXmlElement* xmlRoot = new TiXmlElement( "MappingEntry" );

	size_t frameCount		= frames->size();
	size_t animationCount	= animations->size();
	size_t textureCount		= textures->size();

	// Textures
	TiXmlElement* xmlTextures = new TiXmlElement( "Textures" );
	for (size_t i = 0; i < textureCount; ++i)
	{
		TiXmlElement* xmlTexture = new TiXmlElement( "Texture" );
		TiXmlText* xmlTextureValue = new TiXmlText( textures->get(i).name.c_str() );
		xmlTexture->LinkEndChild(xmlTextureValue);

		xmlTextures->LinkEndChild( xmlTexture );
	}
	xmlRoot->LinkEndChild(xmlTextures);

	// Frames
	TiXmlElement* xmlFrames = new TiXmlElement( "Frames" );
	for (size_t i = 0; i < frameCount; ++i)
	{
		TiXmlElement* xmlFrame = new TiXmlElement( "Frame" );
		xmlFrame->SetAttribute("name", frames->get(i).name.c_str());
		xmlFrame->SetAttribute("textureNumber", frames->get(i).textureNum);
		xmlFrame->SetDoubleAttribute("left", frames->get(i).left);
		xmlFrame->SetDoubleAttribute("top", frames->get(i).top);
		xmlFrame->SetDoubleAttribute("right", frames->get(i).right);
		xmlFrame->SetDoubleAttribute("bottom", frames->get(i).bottom);
		xmlFrame->SetDoubleAttribute("offsetX", frames->get(i).offsetX);
		xmlFrame->SetDoubleAttribute("offsetY", frames->get(i).offsetY);
		xmlFrame->SetDoubleAttribute("originalWidth", frames->get(i).originalWidth);
		xmlFrame->SetDoubleAttribute("originalHeight", frames->get(i).originalHeight);
		xmlFrame->SetAttribute("animDuration", frames->get(i).animDuration);

		xmlFrames->LinkEndChild( xmlFrame );
	}
	xmlRoot->LinkEndChild(xmlFrames);

	// Animations
	TiXmlElement* xmlAnimations = new TiXmlElement( "Animations" );
	for (size_t i = 0; i < animationCount; ++i)
	{
		TiXmlElement* xmlAnimation = new TiXmlElement( "Animation" );

		TiXmlElement* xmlName = new TiXmlElement( "Name" );
		TiXmlText* xmlAnimationName = new TiXmlText( animations->get(i).name.c_str() );
		xmlName->LinkEndChild(xmlAnimationName);
		xmlAnimation->LinkEndChild(xmlName);

		size_t frameCount = animations->get(i).frames.size();
		TiXmlElement* xmlFrames = new TiXmlElement( "Frames" );
		for (size_t j = 0; j < frameCount; ++j)
		{
			TiXmlElement* xmlFrame = new TiXmlElement( "Frame" );
			xmlFrame->SetAttribute("frameNumber", animations->get(i).frames[j]);

			xmlFrames->LinkEndChild( xmlFrame );
		}
		xmlAnimation->LinkEndChild(xmlFrames);

		xmlAnimations->LinkEndChild( xmlAnimation );
	}
	xmlRoot->LinkEndChild(xmlAnimations);

	xmlDoc.LinkEndChild( xmlRoot );
	xmlDoc.SaveFile( path.c_str() );

    return TRUE;
}

bool_t MappingFile::LoadXML(const std::string& path, SpriteFramesListPtr frames, SpriteAnimationsListPtr animations, SpriteTexturesListPtr textures)
{
	TiXmlDocument xmlDoc(path.c_str());

	if (!xmlDoc.LoadFile())
	{
		return FALSE;
	}

	const TiXmlElement* xmlRoot = xmlDoc.FirstChildElement("MappingEntry");
	if (xmlRoot == NULL) return FALSE;

	// Load textures names
	const TiXmlElement* xmlTextures = xmlRoot->FirstChildElement("Textures");
	if (xmlTextures == NULL) return FALSE;

	const TiXmlElement* xmlTexture = xmlTextures->FirstChildElement("Texture");
	while(xmlTexture)
	{
		const char* textureName = xmlTexture->GetText();
		if (textureName != NULL)
		{
			TextureDef texture = TextureDef(textureName);
			textures->push_back(texture);
		}

		xmlTexture = xmlTexture->NextSiblingElement("Texture");
	}

	// Load frames
	const TiXmlElement* xmlFrames = xmlRoot->FirstChildElement("Frames");
	if (xmlFrames == NULL) return FALSE;

    hash_t uid = APP_API_STRHASH(path.c_str(), path.size());

	const TiXmlElement* xmlFrame = xmlFrames->FirstChildElement("Frame");
	while(xmlFrame)
	{
		bool_t corrupted = FALSE;
		FrameDef frame = FrameDef();

		if (xmlFrame->Attribute("name") == NULL)
		{
			corrupted = TRUE;
		}
		else
		{
			frame.name = xmlFrame->Attribute("name");
		}
		if (xmlFrame->Attribute("textureNumber", (int *)(&frame.textureNum)) == NULL) corrupted = TRUE;
		if (xmlFrame->Attribute("left", &frame.left) == NULL) corrupted = TRUE;
		if (xmlFrame->Attribute("top", &frame.top) == NULL)	corrupted = TRUE;
		if (xmlFrame->Attribute("right", &frame.right) == NULL)	corrupted = TRUE;
		if (xmlFrame->Attribute("bottom", &frame.bottom) == NULL) corrupted = TRUE;
		if (xmlFrame->Attribute("offsetX", &frame.offsetX) == NULL)	corrupted = TRUE;
		if (xmlFrame->Attribute("offsetY", &frame.offsetY) == NULL)	corrupted = TRUE;
		if (xmlFrame->Attribute("originalWidth", &frame.originalWidth) == NULL) corrupted = TRUE;
		if (xmlFrame->Attribute("originalHeight", &frame.originalHeight) == NULL) corrupted = TRUE;
		if (xmlFrame->Attribute("animDuration", (int *)(&frame.animDuration)) == NULL) corrupted = TRUE;

        frame.uid = uid;

		if (FALSE == corrupted)
		{
			frames->push_back(frame);
		}

		xmlFrame = xmlFrame->NextSiblingElement("Frame");
	}

	// Load animations
	const TiXmlElement* xmlAnimations = xmlRoot->FirstChildElement("Animations");
	if (xmlAnimations == NULL) return FALSE;

	const TiXmlElement* xmlAnimation = xmlAnimations->FirstChildElement("Animation");
	while(xmlAnimation)
	{
		AnimationDef animation = AnimationDef();

		const TiXmlElement* animationName = xmlAnimation->FirstChildElement("Name");
		if (animationName != NULL)
		{
			animation.name = animationName->GetText();
		}

		// Load frames
		const TiXmlElement* xmlFrames = xmlAnimation->FirstChildElement("Frames");
		if (xmlFrames != NULL)
		{
			const TiXmlElement* xmlFrame = xmlFrames->FirstChildElement("Frame");
			while(xmlFrame)
			{
				int frameIndx;
				if (xmlFrame->Attribute("frameNumber", (int *)(&frameIndx)) != NULL)
				{
					animation.frames.push_back(frameIndx);
				}

				xmlFrame = xmlFrame->NextSiblingElement("Frame");
			}
		}

		if (animation.name != "")
		{
			animations->push_back(animation);
		}

		xmlAnimation = xmlAnimation->NextSiblingElement("Animation");
	}

    return TRUE;
}
#endif