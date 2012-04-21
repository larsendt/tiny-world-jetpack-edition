#include "Bone.h"

Bone *addBoneChild(Bone * root, vec2 pos, float a, float minangle, float maxangle, float l, float depth, uint ID){

	Bone *t;
	
	if (root == NULL){
	
		if (!(root = new Bone)){
			return NULL;
		}
		root->parent = NULL;
		t = root;
	}
	else if (root->children < MAX_CHILDREN){
		if(!(t = new Bone)){
			return NULL;
		}
		t->parent = root;
		root->child[root->children] = t;
		root->children ++;
		
	}
	else return NULL;
	
	t->minangle = minangle;
	t->maxangle = maxangle;
	t->level = 0;
	t->depth = depth;
	t->p = pos;
	t->a = a;
	t->defaulta = a;
	t->l = l;
	t->children = 0;
	t->ID = ID;
	t->num_frames = 0;
	t->anim_length = 0;

	for (int i = 0; i<MAX_CHILDREN; i++){
		t->child[i] = NULL;
	}
	return t;
}

void freeBoneTree(Bone * root){
	
	if (root == NULL) return;
	
	for (int i = 0; i< root->children; i++){
		freeBoneTree(root->child[i]);
	}
	
	delete root;
	
	return;
}

void printBoneTree(Bone * root, uint level)
{
	if (root == NULL) return;
	
	printf("Bone data for %i ", root->ID);
	for (int i = 0; i<level;i++){
		printf("#");
	}
	
	printf(" %4.2f %4.2f %4.2f %4.2f %u", root->p.x, root->p.y, root->a, root->l, root->children);
	/* Now print animation info */
 	for (int i = 0; i < root->num_frames; i++){
 		printf(" Frame data: %d %4.4f", root->animation[i].time, root->animation[i].angle);
 	}
 	printf("\n");
	
	for (int i = 0; i< root->children; i++){
		printBoneTree(root->child[i], level + 1);
	}
}

void drawBoneTree(Bone * root){
	glPushMatrix();
	
	glTranslatef(root->p.x, root->p.y, 0.0);
	glRotatef(RAD2DEG(root->a), 0.0,0.0,1.0);
	
	glBegin(GL_QUADS);
	glColor3f((root->depth+ 1 )/2.0, (root->depth + 1)/2.0, 1.0);
	glVertex3f(0,-.5, root->depth);
	glVertex3f(0,.5, root->depth);
	glVertex3f(root->l,.5, root->depth);
	glVertex3f(root->l,-.5, root->depth);
	
	glEnd();
	
	glTranslatef(root->l, 0.0,0.0);
	
	for(int i = 0; i<root->children; i++){
		drawBoneTree(root->child[i]);
	}
	
	glPopMatrix();
	
}

Bone *boneLoadStructure(char *path)
{
 	Bone *root,
 		 *temp;
 
 	FILE *file;
 
 	float x,
 		  y,
 		  angle,
 		  minangle,
 		  maxangle,
 		  dlevel,
 		  length;
 
 	int depth,
 		actualLevel;
 
 	uint name;

 	char depthStr[20],
 		 buffer[1024];
 
 	if (!(file = fopen(path, "r")))
 	{
 		fprintf(stderr, "Can't open file %s for reading\n", path);
 		return NULL;
 	}
 
 	root = NULL;
 	temp = NULL;
 	actualLevel = 0;
	int i;
 	while (!feof(file))
 	{
 		strcpy(buffer, "/\n");
 		fgets(buffer, 1024, file);

 		i++;

 		sscanf(buffer, "%s %f %f %f %f %f %f %f %u", depthStr, &x, &y,
                       &angle, &minangle, &maxangle, &length, &dlevel, &name);

 		/* Avoid empty strings */
 		if (strlen(buffer) < 3)
 			continue;
 		if (buffer[0] == '/') continue;
 		/* Calculate the depth */
 		depth = strlen(depthStr) - 1;
 		if (depth < 0 || depth > MAX_CHILDREN)
 		{
 			fprintf(stderr, "Wrong bone depth (%s)\n", depthStr);
 			return NULL;
 		}
 
 		for (; actualLevel > depth; actualLevel--)
 			temp = temp->parent;
 
 		if (!root && !depth)
 		{
 			root = addBoneChild(NULL, vec2(x,y), angle, minangle, maxangle, length, dlevel, name);
 			temp = root;
 		}
 		else
 			temp = addBoneChild(temp, vec2(x, y), angle, minangle, maxangle, length, dlevel,  name);
 		/* Now check for animation data */

 		actualLevel++;
 	}
 	fclose(file);
 	return root;
}

Bone * getBoneByID(Bone * bones, unsigned int id){

	if (bones->ID == id) return bones;
	Bone * b = NULL;
	for (int i = 0; i< bones->children; i++){
	
		if ((b = getBoneByID(bones->child[i], id)) != NULL){
			return b;
		}
	
	}
	return b;

}

void boneLoadAnimation(Bone * bone, char * path){

	FILE * file;
	char buffer[1024];
	char frames[1024];
	if (!(file = fopen(path, "r")))
 	{
 		fprintf(stderr, "Can't open file %s for reading\n", path);
 		return;
 	}
 	
 	int numframes;
 	int id;
 	int time;
 	uint animlength;
 	float angle;
 	
 	char * token;
 	char * ptr;
 	
 	Bone * b;
 	int i = 0;
 	while (!feof(file)){
		strcpy(buffer, "/\n");
 		fgets(buffer, 1024, file);
 		i++;
 		
 		sscanf(buffer, "%i %i %u %[^\n]", &id, &numframes, &animlength, frames);
 		
 		if (buffer[0] == '/') continue;
 		
 		b = getBoneByID(bone, id);
 		
 		if (b == NULL){
 			printf("Invalid ID\n");
 			return;
 		}
 		
 		b->anim_length = animlength;
 		
 		if (numframes == 0) continue;
		
		ptr = frames;
		
		while ((token = strtok(ptr, " "))){
			ptr = NULL;
			time = atoi(token);
			
			token = strtok(ptr, " ");
			angle = atof(token);
			
			b->animation[b->num_frames].time = time;
			b->animation[b->num_frames].angle = angle;
			
			b->num_frames ++;
			
		}
 		
 		
 	}
 	
 	fclose(file);

}

void boneAnimate(Bone *root, int time, float multiplier)
{
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
	
 	KeyFrame * k;
 	KeyFrame * k2;
	
	
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
