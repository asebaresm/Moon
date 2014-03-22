/*Funciones de Albert wiiiiii*/

/*Return a referenece to the corresponding element given a NAME. Returns NULL if there is an error or if the element is not found. */
Object *world_get_obj_by_name(World *w, char * name){
	int i=0;
	if(!w || !name)
		return NULL;

	for(i=0;i<MAX_OBJECTS+1;i++){
		if(strcmp(obj_get_name(w->objects[i]),name))
			return w->objects[i];
	}
	return NULL;
}
/* Returns a reference to the corresponding element given an ID. Returns NULL if there is an error or if the element is not found. */
Object *world_get_obj(World *w, Id id){
	int i=0;
	if(!w || id==-1)
		return NULL;

	for(i=0;i<MAX_OBJECTS+1;i++){
		if(obj_get_id(w->objects[i])==id)
			return w->objects[i];
	}
	return NULL;
}

/* Returns the current location of the player */
 Id world_get_player_location(World *w){
	if(!w)
		return -1;

	return player_get_location(w->player);
 }
/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
 Space *world_get_space_north(World *w, Id space){
 	int i,j;
 	id norte;
 	if(!w || space==-1)
 		return NULL;
 	for(i=0;i<MAX_SPACES+1;i++){

 		if(space_get_id(w->spaces[i])==space){
 			/*Almacenar id espacio al norte*/
 			norte=space_get_north(w->spaces[i])
 			/*Comprobar el espacio con la id*/
 			for(j=0;j<MAX_SPACES+1;j++){
 				if(space_get_id(w->spaces[j])==norte){
 					/*Comprobar si el link existe entre ellos y esta abierto*/
 					for(k=0;k<MAX_LINKS;k++){
 						if(link_ask_linked(w->link[k], space, norte)==TRUE){
 							return w->spaces[j];
 						}
 					}
 				}
 			}
 		}
	}
	return NULL;
 }
/* Given the name of an object checks if it is located in a given space. Returns the object or NULL if it does not exist. */
 Object *world_get_obj_from_space(World *w, char *name, Id space){
 	int i;
 	if(!w || !name || space==NO_ID)
 		return NULL;
 	for (i = 0; i < MAX_SPACES; ++i)
 	{
 		
 	}

	return NULL;


 }
/* Shows the description of the space and its visible objects. Hidden objects are not shown. The client must reserve enough memory for desc. */ 
 STATUS world_get_space_description(World *w, Id space, char * desc, Size max_len){
 	if(!w || !desc)
 		return ERROR;
 	int i;
 	desc=(char*)malloc (max_len*sizeof(char));
 	for(i=0;i<MAX_SPACES;i++){
 		if(w->spaces[i]->id==space){

 			strcpy(desc,w->spaces[i]->description);
 			return OK;
 		}
 	}
 	return ERROR;
 }

 /* Changes the location of the player. The current place must be connected to the destination. */ 
 STATUS world_move_player(World *w, DIRECTION dir){
 	if(!w)
 		return ERROR;
 	w->player->location=dir;
 	return OK;

 }
 /*************************08948438578357987897897848e397894***********************************/







