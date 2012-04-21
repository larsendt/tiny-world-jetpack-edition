#include "Animation.h"

SkelAnimation::SkelAnimation(char * file, int maxBoneID){

	FILE * file;
	char buffer[1024];
	char frames[1024];
	if (!(file = fopen(path, "r")))
 	{
 		fprintf(stderr, "Can't open file %s for reading\n", path);
 		return;
 	}
 	int curframe = 0;
 	int numframes;
 	int id;
 	int time;
 	uint animlength;
 	float angle;
 	
 	char * token;
 	char * ptr;
 	
 	BoneAnimation * b;
 	animations = new BoneAnimation[maxBoneID];
 	
 	int i = 0;
 	while (!feof(file)){
		strcpy(buffer, "/\n");
 		fgets(buffer, 1024, file);
 		i++;
 		
 		sscanf(buffer, "%i %i %u %[^\n]", &id, &numframes, &animlength, frames);
 		
 		if (buffer[0] == '/') continue;
 		
 		if (b == NULL){
 			printf("Invalid ID\n");
 			return;
 		}
 		
 		if (numframes == 0) continue;
		
		ptr = frames;
		
		Keyframe * frames = new Keyframe[numframes];
		
		curframe = 0;
		
		while ((token = strtok(ptr, " "))){
			ptr = NULL;
			time = atoi(token);
			
			token = strtok(ptr, " ");
			angle = atof(token);
			
			frames[curframe].time = time;
			frames[curframe].angle = angle;
			
			curframe++;
			
		}
		
		b->anim_length = animlength;
		
		b = new BoneAnimation(animlength, numframes, true, frames);
 		animations[id] = b; // sets class animations to this

 	}
 	
 	fclose(file);

}

void SkelAnimation::animate(Bone * root){

	if (!root->anim_length){
	
		for (int i = 0; i< root->children; i++){
 	
 		boneAnimate(root->child[i], time, multiplier);
 		
 		}
	
		return;
	}
	
	int animtime = time%root->anim_length;
	int nextindex = 0;

	float angle;
	float ratio;
	int range;
	int delta;
	
 	Keyframe * k;
 	Keyframe * k2;
	
	
 	for (int i = 0; i< root->num_frames; i++){
 		
		
 		nextindex = (i+1)%(root->num_frames);
 		k = &root->animation[i];
		k2 = &root->animation[nextindex];
 		
 		if (k->time < animtime && k2->time > animtime){ // we're in the section
 		
 			range = k2->time - k->time;
 			delta = animtime - k->time;

 			if (range != 0)	ratio = delta/ (float) range;
 			else ratio = 1.0;
 			
 			angle = (k->angle*multiplier*(1-ratio)) + (k2->angle * multiplier * (ratio));
 			float newangle = root->defaulta + angle;
 			if (newangle < root->minangle) newangle = root->minangle;
 			if (newangle > root->maxangle) newangle = root->maxangle;
 			
 			root->a = newangle;
 			
 		}
 		else if (nextindex < i && k->time < animtime){ // Looped around
 		
 			delta = animtime - k->time;
 			range = root->anim_length - k->time;
 			if (range != 0)	ratio = delta/ (float) range;
 			else ratio = 1.0;

 			ratio = delta / (float) range;
 			angle = (k->angle * multiplier * (1-ratio)) + (k2->angle * multiplier *(ratio));
 			
 			float newangle = root->defaulta + angle;
 			if (newangle < root->minangle) newangle = root->minangle;
 			if (newangle > root->maxangle) newangle = root->maxangle;
 			
 			root->a = newangle;
 			
 			
 		}
 		
 	}
 	
 	for (int i = 0; i< root->children; i++){
 	
 		boneAnimate(root->child[i], time, multiplier);
 	
 	}

}
