#include "animation.h"
#include "openglheaders.h"
#include <tinyxml2.h>

#include <iostream>
#include <assert.h>


Animation::Animation(int tex, std::string pixenFrameDataXMLFile)
	: m_tex(tex)
	, m_numFrames(1)
	, m_currentFrame(0)
	, m_timeElapsed(0)
	, m_totalDuration(0)
	, m_xFlipped(false)
	, m_yFlipped(false)
{
	glBindTexture(GL_TEXTURE_2D, m_tex);
	int texWidth;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
	int texHeight;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);
	std::cout << texWidth << " by " << texHeight << std::endl;

	m_frameSize = texHeight*2;


	if (texWidth == texHeight) return;
	//Read xml data
	m_numFrames = 0;
	tinyxml2::XMLDocument aniDataDoc;
	tinyxml2::XMLError err = aniDataDoc.LoadFile(pixenFrameDataXMLFile.c_str());
	assert(err == tinyxml2::XML_NO_ERROR);
	tinyxml2::XMLElement* array = aniDataDoc.FirstChildElement("plist")->FirstChildElement("array");
	for (tinyxml2::XMLElement* e = array->FirstChildElement("dict"); e != NULL; e = e->NextSiblingElement("dict")) //TODO
	{
		tinyxml2::XMLElement* keynode = e->FirstChildElement("key");
		const char* key = keynode->GetText();
		float duration;
		if (strcmp(key, "duration") == 0)
		{
			tinyxml2::XMLElement* realnode = keynode->NextSiblingElement("real");
			assert(realnode);
			err = realnode->QueryFloatText(&duration);
			assert(err == tinyxml2::XML_NO_ERROR);

			m_totalDuration += duration;
			m_frameEndTimes.push_back(m_totalDuration);
			m_numFrames += 1;
		}
	}
		std::cout << "Made animation with " << m_numFrames << " frames." << std::endl;


	for (int i=0; i<m_frameEndTimes.size(); i++)
	{
		std::cout << "Start: " << m_frameEndTimes[i] << std::endl;
	}
	std::cout << "Total duration: " << m_totalDuration << std::endl;


}

Animation::~Animation()
{
}

void Animation::flipX(bool val)
{
	m_xFlipped = val;
}

void Animation::flipY(bool val)
{
	m_yFlipped = val;
}

void Animation::update(double dt)
{
	if (m_numFrames == 1) return;

	m_timeElapsed += dt;
	if (m_timeElapsed > m_totalDuration) 
		m_timeElapsed -= m_totalDuration;

	//std::cout << "Time Elapsed " << m_timeElapsed << std::endl;
	for (int i=0; i<m_numFrames; i++)
	{
		if (m_timeElapsed < m_frameEndTimes[i])
		{
			m_currentFrame = i;
			break;
		}
	}
}

void Animation::draw()
{
	float uvTop = 1.0f;
	float uvBottom = 0.0f;
	float uvLeft = m_currentFrame/(float)m_numFrames;
	float uvRight = (m_currentFrame+1)/(float)m_numFrames;
	if (m_xFlipped)
	{
		float tmp = uvLeft;
		uvLeft = uvRight;
		uvRight = tmp;
	}

	float xyTop = m_frameSize;
	float xyBottom = 0.0f;
	float xyLeft = 0.0f;
	float xyRight = m_frameSize;

	//std::cout << "UVs: (" << uvLeft << ", " << uvBottom << ") (" << uvRight << ", " << uvTop << ")" << std::endl;
	//std::cout << "Position: (" << xyLeft << ", " << xyBottom << ") (" << xyRight << ", " << xyTop << ")" << std::endl;
	//std::cout << "Current Frame " << m_currentFrame << std::endl;

	glBindTexture(GL_TEXTURE_2D, m_tex);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(uvLeft, uvBottom); glVertex3f(xyLeft, xyBottom, 0.0f);
    glTexCoord2f(uvRight, uvBottom); glVertex3f(xyRight, xyBottom, 0.0f);
    glTexCoord2f(uvRight, uvTop); glVertex3f(xyRight, xyTop, 0.0f);
    glTexCoord2f(uvLeft, uvTop); glVertex3f(xyLeft, xyTop, 0.0f);

	glEnd();
}


