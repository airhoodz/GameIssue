#ifndef Animation_hpp
#define Animation_hpp

#include <vector>
#include <map>
#include <functional>

#include "Bitmask.hpp"


enum class FacingDirection
{
    None,
    Left,
    Right,
	Up,
	Down
};

struct FrameData
{
    int id;
    int x;
    int y;
    int width;
    int height;
    float displayTimeSeconds;
};

using AnimationAction = std::function<void(void)>;

class Animation
{
public:
	Animation();
    
    void AddFrame(int textureID, int x, int y, int width, int height, float frameTime, bool looped);
	void AddFrameAction(unsigned int frame, AnimationAction action);
    
    const FrameData* GetCurrentFrame() const;
    
    bool UpdateFrame(float deltaTime);
    
    void Reset();

	//Handle if variables loop or not - fix to never ending projectile bug
	void SetLooped(bool looped);
	bool IsLooped();
    
private:
    void IncrementFrame();
	void RunActionForCurrentFrame();
    
    std::vector<FrameData> frames;
    int currentFrameIndex;
    float currentFrameTime;

	bool releaseFirstFrame;

	std::map<int, std::vector<AnimationAction>> actions;

	Bitmask framesWithActions;
	bool isLooped;

};


#endif /* Animation_hpp */
