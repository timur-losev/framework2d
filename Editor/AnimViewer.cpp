#include "AnimViewer.h"
#include <math.h>

AnimViewer::AnimViewer ()
	: m_SelectedFrame(0)
	, m_FrameScrollPos(0)
	, m_PreviewPos(core::position2df(0, 0))
	, m_PreviewSize(core::vector2di(0, 0))
	, m_FramesPos(core::position2df(0, 0))
	, m_FramesSize(core::vector2di(0, 0))
{
}

AnimViewer::~AnimViewer(void)
{
}

void AnimViewer::Init (	const core::position2df& previewPos, 
						const core::vector2di& previewSize, 
						const core::position2df& framesPos, 
						const core::vector2di& framesSize )
{
	m_PreviewPos = previewPos;
	m_PreviewSize = previewSize;
	m_FramesPos = framesPos;
	m_FramesSize = framesSize;

    //APP_API_ASSERT(m_FramesSize.X > 0 && m_FramesSize.Y > 0);

    if (m_FramesSize.X & m_FramesSize.Y > 0)
    {
        m_MaxFramesVisible = (int)(m_FramesSize.X / m_FramesSize.Y);
        // Offsets between frames
        m_FramesOffset = (m_FramesSize.X - m_MaxFramesVisible * m_FramesSize.Y) / m_MaxFramesVisible;
    }
    else
    {
        m_MaxFramesVisible = 0;
        m_FramesOffset = 0;
    }

	Centering();
}

void AnimViewer::Update()
{
	DrawAxes();

	if (m_TotalTextures == 0) return;

	DriverPtr driver = GVideoDriver;

	if (m_CurrentAnimation >= m_AnimationCount)
    {
        m_CurrentAnimation = 0;
		if (m_CurrentAnimation < m_Animations->size())
		{
			m_FramesCount = m_Animations->get(m_CurrentAnimation).frames.size();
		}
    }
	if (m_CurrentFrame >= m_FramesCount)
    {
        m_CurrentFrame = 0;
    }

	core::rectf frameRect;
	//float fW = 0;
	//float fH = 0;
	u32 textureNumber = 0;
	if (m_FramesCount > 0 && m_CurrentFrame < m_FramesCount)
    {
		const FrameDef& frame = m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame]);
		core::recti rectangle = core::recti((int)(m_Position.X + frame.offsetX * m_Scale.X),
											(int)(m_Position.Y + frame.offsetY * m_Scale.Y),
											(int)(m_Position.X + (frame.offsetX + frame.width) * m_Scale.X),
											(int)(m_Position.Y + (frame.offsetY + frame.height) * m_Scale.Y));

		// Draw frame image
		CSprite::Update();
		// Draw restrictive rectangle
		driver->draw2DRectangleOutline( rectangle, video::SColor(255, 255, 255, 255) );
    }

	// Draw frames
	uint count = ((uint)m_MaxFramesVisible < m_TotalFrames) ? m_MaxFramesVisible : m_TotalFrames;
	for (uint i = 0; i < count; ++i)
	{
		DrawFrame(m_FrameScrollPos + i);
	}
}

void AnimViewer::DrawAxes()
{
	DriverPtr driver = GVideoDriver;
	// x axis
	core::vector2di start = core::vector2di((int)m_PreviewPos.X, (int)m_Position.Y);
	core::vector2di end = core::vector2di((int)(m_PreviewPos.X + m_PreviewSize.X), (int)m_Position.Y);
	driver->draw2DLine(start, end, video::SColor(255, 255, 0, 0));

	// y axis
	start = core::vector2di((int)m_Position.X, (int)m_PreviewPos.Y);
	end = core::vector2di((int)m_Position.X, (int)(m_PreviewPos.Y + m_PreviewSize.Y));
	driver->draw2DLine(start, end, video::SColor(255, 0, 255, 0));
}

void AnimViewer::DrawFrame(int frameNum)
{
	if ((frameNum >= 0 && (uint)frameNum < m_TotalFrames) || m_TotalFrames > 0)
	{
		core::rectf frameRect;
        const FrameDef& frame = m_Frames->get(frameNum);
		frameRect =  core::rectf( (f32)(frame.x), 
								  (f32)(frame.y), 
								  (f32)(frame.x + frame.width), 
								  (f32)(frame.y + frame.height) );
		u32 textureNumber = frame.textureNum;

		float frameSize = (float)m_FramesSize.Y;
		float s = (float)((frame.width > frame.height) ? frameSize / frame.width : frameSize / frame.height);
		core::vector2df scale = core::vector2df(s, s);

		core::position2df framePos = core::position2df( m_FramesPos.X + (frameNum - m_FrameScrollPos) * (frameSize + m_FramesOffset), 
														m_FramesPos.Y);

		DriverPtr driver = GVideoDriver;
		// Draw restrictive rectangle
		driver->draw2DRectangleOutline( core::recti((int)framePos.X, (int)framePos.Y, (int)(framePos.X + frameSize), (int)(framePos.Y + frameSize)), 
									video::SColor(255, 255, 255, 255) );

		// Draw frame selection
		if (m_SelectedFrame >= m_FrameScrollPos + m_MaxFramesVisible) m_SelectedFrame = m_FrameScrollPos + m_MaxFramesVisible - 1;
		if (m_SelectedFrame < m_FrameScrollPos) m_SelectedFrame = m_FrameScrollPos;	
		if (frameNum == m_SelectedFrame)
		{
			driver->draw2DRectangle( video::SColor(128, 255, 255, 255),
									 core::recti((int)framePos.X, (int)framePos.Y, (int)(framePos.X + frameSize), (int)(framePos.Y + frameSize)) );
		}

		// Centering frame
		framePos.X += (frameSize - (f32)m_Frames->get(frameNum).width * s) / 2.f;
		framePos.Y += (frameSize - (f32)m_Frames->get(frameNum).height * s) / 2.f;
		// Draw frame image
		Draw2DImage(m_Atlases[textureNumber], frameRect, framePos, m_RotationPoint, m_Rotation, 
			scale, true,  video::SColor(255,255,255,255));
	}
}

void AnimViewer::ScrollFrameLeft()
{
	if (--m_FrameScrollPos < 0) m_FrameScrollPos = 0;
	// Shift selecting frame
	if (m_SelectedFrame >= m_FrameScrollPos + m_MaxFramesVisible) m_SelectedFrame = m_FrameScrollPos + m_MaxFramesVisible - 1;
}

void AnimViewer::ScrollFrameRight()
{
	if ((uint)m_MaxFramesVisible < m_TotalFrames &&
		uint(++m_FrameScrollPos + m_MaxFramesVisible) >= m_TotalFrames) 
	{
		m_FrameScrollPos = m_TotalFrames - m_MaxFramesVisible - 1;
	}
	// Shift selecting frame
	if (m_SelectedFrame < m_FrameScrollPos) m_SelectedFrame = m_FrameScrollPos;
}

int AnimViewer::CheckFrameBarCollision(int x, int y)
{
	uint count = ((uint)m_MaxFramesVisible < m_TotalFrames) ? m_MaxFramesVisible : m_TotalFrames;
	for (uint i = 0; i < count; ++i)
	{
		s32 frameSize = m_FramesSize.Y;
		core::position2df leftCorner = core::position2df(m_FramesPos.X + i * (frameSize + m_FramesOffset), m_FramesPos.Y);
		core::position2df rightCorner = core::position2df(leftCorner.X + frameSize, leftCorner.Y + frameSize);

		if (x >= leftCorner.X  && y >= leftCorner.Y &&
			x <= rightCorner.X && y <= rightCorner.Y)
		{
			m_SelectedFrame = i + m_FrameScrollPos;
			return m_SelectedFrame;
		}
	}

	return -1;
}

bool_t AnimViewer::CheckFrameViewCollision(int x, int y)
{
	if (m_CurrentAnimation < m_AnimationCount && 
		m_CurrentFrame < m_FramesCount &&
		m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame] < m_TotalFrames)
	{
		const FrameDef& frame = m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame]);

		core::position2df leftCorner = core::position2df((f32)(frame.offsetX * m_Scale.X + m_Position.X),
														 (f32)(frame.offsetY * m_Scale.Y + m_Position.Y));
		core::position2df rightCorner = core::position2df((f32)((frame.offsetX + frame.width) * m_Scale.X + m_Position.X),
														  (f32)((frame.offsetY + frame.height) * m_Scale.X + m_Position.Y));
		if (x >= leftCorner.X  && y >= leftCorner.Y &&
			x <= rightCorner.X && y <= rightCorner.Y)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void AnimViewer::SetAnimationsList(SpriteAnimationsListPtr newAnimationList)
{
	m_IsAnimated = false;
	m_Animations = newAnimationList;

	m_AnimationCount = m_Animations->size();
    m_FramesCount = 0;
	if (m_CurrentAnimation < m_AnimationCount)
	{
		m_FramesCount = m_Animations->get(m_CurrentAnimation).frames.size();
	}
	else
	{
		m_CurrentAnimation = 0;
	}
}

bool_t AnimViewer::IntersectWithPreview(int x, int y)
{
	if (x >= m_PreviewPos.X && y >= m_PreviewPos.Y &&
		x <= m_PreviewPos.X + m_PreviewSize.X && y <= m_PreviewPos.Y + m_PreviewSize.Y)
	{
		return true;
	}

	return false;
}

bool_t AnimViewer::IntersectWithFrameBar(int x, int y)
{
	if (x >= m_FramesPos.X && y >= m_FramesPos.Y &&
		x <= m_FramesPos.X + m_FramesSize.X && y <= m_FramesPos.Y + m_FramesSize.Y)
	{
		return true;
	}

	return false;
}

void AnimViewer::Centering()
{
	double maxW = 0;
	double maxH = 0;

	if (m_CurrentAnimation < m_AnimationCount && 
		m_CurrentFrame < m_FramesCount)
	{
		for (u32 i = 0; i < m_FramesCount; ++i)
		{
			const FrameDef& frame = m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[i]);

			if (maxW < frame.width)
			{
				maxW = frame.width;
			}
			if (maxH < frame.height)
			{
				maxH = frame.height;
			}
		}
	}

	m_Position = core::position2df( (float)(m_PreviewPos.X + m_PreviewSize.X / 2.0 - (maxW * m_Scale.X) / 2.0), 
		 							(float)(m_PreviewPos.Y + m_PreviewSize.Y / 2.0 - (maxH * m_Scale.Y) / 2.0) );
}

bool_t AnimViewer::SetFrameOffset(float offX, float offY, FrameDef& frame)
{
	if (m_CurrentAnimation < m_AnimationCount &&
		m_CurrentFrame < m_FramesCount &&
		m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame] < m_TotalFrames)
	{
		FrameDef& curFrame = m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame]);

		curFrame.offsetX = offX;
		curFrame.offsetY = offY;

		frame = curFrame;
		return TRUE;
	}

	return FALSE;
}

core::position2df AnimViewer::GetFrameOffset()
{
	if (m_CurrentAnimation < m_AnimationCount &&
		m_CurrentFrame < m_FramesCount &&
		m_TotalFrames > m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame])
	{
		return core::position2df(m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame]).offsetX, 
								 m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame]).offsetY);
	}

	return core::position2df(0, 0);
}

void AnimViewer::SetScaleByPoint(float scale, int x, int y)
{
	if (m_CurrentAnimation < m_AnimationCount && 
		m_CurrentFrame < m_FramesCount &&
		m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame] < m_TotalFrames)
	{
		const FrameDef& frame = m_Frames->get(m_Animations->get(m_CurrentAnimation).frames[m_CurrentFrame]);

		core::position2df leftCorner = core::position2df(frame.offsetX * m_Scale.X + m_Position.X,
														frame.offsetY * m_Scale.Y + m_Position.Y);
		core::position2df rightCorner = core::position2df((frame.offsetX + frame.width) * m_Scale.X + m_Position.X,
														  (frame.offsetY + frame.height) * m_Scale.X + m_Position.Y);
		if (x >= leftCorner.X  && y >= leftCorner.Y &&
			x <= rightCorner.X && y <= rightCorner.Y)
		{
			float deltaX = x - m_Position.X;
			float deltaY = y - m_Position.Y;

			deltaX = (scale - m_Scale.X) * deltaX / m_Scale.X;
			deltaY = (scale - m_Scale.Y) * deltaY / m_Scale.Y;

			m_Position.X -= deltaX;
			m_Position.Y -= deltaY;
		}
	}

	m_Scale = core::vector2df(scale, scale);
}