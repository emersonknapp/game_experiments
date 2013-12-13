#pragma once

#include <vector>
#include <string>

class Animation
{
public:
	Animation(int tex, std::string pixenFrameDataXMLFile);
	~Animation();

	void flipX(bool val);
	void flipY(bool val);

	void update(double dt);
	void draw(); //transform must be set by calling entity, this will draw a textured rect

private:
	int m_tex;
	int m_numFrames;
	std::vector<double> m_frameEndTimes;
	int m_currentFrame;
	double m_timeElapsed;
	double m_totalDuration;
	bool m_xFlipped;
	bool m_yFlipped;
	int m_frameSize; //Assuming all frames are square for now
};