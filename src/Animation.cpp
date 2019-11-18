#include "Animation.hpp"


Animation::Animation() : frames(0), currentFrameIndex(0), currentFrameTime(0.f), releaseFirstFrame(true), isLooped(true) { }

void Animation::AddFrame(int textureID, int x, int y, int width, int height, float frameTime, bool looped)
{
    FrameData data;
    data.id = textureID;
    data.x = x;
    data.y = y;
    data.width = width;
    data.height = height;
    data.displayTimeSeconds = frameTime;
    
    frames.push_back(data);

	isLooped = looped;
}

const FrameData* Animation::GetCurrentFrame() const
{
    if(frames.size() > 0)
    {
        return &frames[currentFrameIndex];
    }
    
    return nullptr;
}

bool Animation::UpdateFrame(float deltaTime)
{
	if (releaseFirstFrame)
	{
		RunActionForCurrentFrame();
		releaseFirstFrame = false;
		return true;
	}

    if(frames.size() > 1 && (isLooped || currentFrameIndex < frames.size() - 1))
    {
        currentFrameTime += deltaTime;
        
        if(currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds)
        {
            currentFrameTime = 0.f;
            IncrementFrame();
			RunActionForCurrentFrame();
            return true;
        }
    }
    
    return false;
}

void Animation::IncrementFrame()
{
    // check if we reached the last frame
    if (currentFrameIndex == (frames.size() - 1))
    {
        currentFrameIndex = 0;
    }
    else
    {
        currentFrameIndex++;
    }
}

void Animation::Reset()
{
    currentFrameIndex = 0;
    currentFrameTime = 0.f;
	releaseFirstFrame = true;
}

void Animation::AddFrameAction(unsigned int frame, AnimationAction action)
{
	if (frame < frames.size())
	{
		auto actionKey = actions.find(frame);

		if (actionKey == actions.end())
		{
			framesWithActions.SetBit(frame);
			actions.insert(std::make_pair(frame, std::vector<AnimationAction>{action}));
		}
		else
		{
			actionKey->second.emplace_back(action);
		}
	}
}

void Animation::RunActionForCurrentFrame()
{
	if (actions.size() > 0)
	{
		if (framesWithActions.GetBit(currentFrameIndex))
		{
			auto actionsToRun = actions.at(currentFrameIndex);

			for (auto f : actionsToRun)
			{
				f();
			}
		}
	}
}

void Animation::SetLooped(bool looped)
{
	isLooped = looped;
}

bool Animation::IsLooped()
{
	return isLooped;
}



