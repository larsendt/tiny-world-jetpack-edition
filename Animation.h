#include "Bone.h"

struct{

	uint time;
	float angle;

}Keyframe;

class BoneAnimation{
	public:
		BoneAnimation(uint l, uint n, bool loop, Keyframe * kfs){
			anim_length = l;
			num_frames = n;
			current_time = 0;
			loopable = loop;
			frames = kfs;
		};
	private:
		uint anim_length; // in milliseconds
		uint num_frames; // number of keyframes
		
		uint current_time; // mod anim_length
		bool loopable;
		
		Keyframe * frames;
};

class SkelAnimation{
	public:
		SkelAnimation(char * file, int maxBoneID);
		void animate(Bone * root);
	private:
		BoneAnimation * animations; // one for each bone
}
