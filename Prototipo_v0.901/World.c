#include "world.h"

struct _World 
{ 
 Space *spaces[MAX_SPACES + 1]; 
 Object *objects[MAX_OBJECTS + 1]; 
 Link *links[MAX_LINKS + 1]; 
 Player *player;
 int n_spaces; /*Numero de espacios de un mundo*/
 int n_objects; /*Numero de espacios de un mundo*/
 int n_links; /*Numero de uniones de un mundo*/
};

/**
 *@name: World *create_world();
 *@brief: function to create the world.
 
 *@return: the world you have create.
 */
 World *create_world(){
 	World * w;

 	w = (World*)malloc(sizeof(World));
 	
 	w->n_links = 0;
 	w->n_spaces = 0;
 	w->n_objects = 0;

 	return w;
}

/**
 *@name: void destroy_world(World *w);
 *@brief: function to destroy the world.
 
 *@param: the world that you want destroy.
 
 *@return: NULL si hay algun errror.
 */
void destroy_world(World *w){
	if(w == NULL)
		return NULL;

	free(w);
}

/**
 *@name: Space *world_add_space(World *w, Id id); 
 *@brief: añade un espacio a menudo
 
 *@param: mundo al que añadir el espacio
 *@param: id del espacio que se quiere añadir.
 
 *@return: el espacio que se ha añadido, o NULL en caso de error.
 */
Space *world_add_space(World *w, Id id){
	if(w == NULL || id<0)
		return NULL;

	w->spaces[w->n_spaces] = create_space(id);
	
	if ((w->spaces[w->n_spaces]) == NULL)
		return NULL;

	w->n_spaces++;
	return w->spaces[w->n_spaces-1];
}

/**
 *@name: Object *world_add_obj(World *w, Id id);
 *@brief: añade un objeto a mundo.
 
 *@param: mundo al que añadir el objeto.
 *@param: id del objeto que se quiere añadir.
 
 *@return: el objeto que se ha añadido, o NULL en caso de error.
 */
Object *world_add_obj(World *w, Id id){
	if(w == NULL || id<0)
		return NULL;

	w->objects[w->n_objects] = obj_create(id);

	if((w->objects[w->n_objects]) == NULL)
		return NULL;
	
	w->n_objects++;
	return w->objects[w->n_objects-1];
} 

/**
 *@name: Link *world_add_link(World *w, Id id);
 *@brief: añade un link al mundo.
 
 *@param: mundo al que añadir el link.
 *@param: id del link que se quiere añadir.
 
 *@return: el link que se ha añadido, o NULL en caso de error.
 */
Link *world_add_link(World *w, Id id){
	if(w == NULL || id<0 || w->n_links<MAX_LINKS)
		return NULL;

	w->links[w->n_links] = create_link(id);

	if((w->links[w->n_links]) == NULL)
		return NULL;
	
	w->n_links++;
	return w->links[w->n_links-1];
}

/**
 *@name: Player *world_set_player(World *w);
 *@brief: inicializa un jugador en mundo.
 
 *@param: mundo al que añadir el jugador.
 
 *@return: el jugador que se ha añadido, o NULL en caso de error.
 */
Player *world_set_player(World *w){
	if(w == NULL)
		return NULL;
	w->player = create_player();

	if(W->player==NULL)
		return NULL;
	return w->player;
/*Solo queda esta que no se que quiere que haga la funcion.*/

}

/**
 *@name: Space *world_get_space(World *w, Id id);
 *@brief: obtienes un espacio a partir de su id y del mundo en el que se encuentra. 
 
 *@param: mundo donde esta el esapcio.
 *@param: id del espacio
 
 *@return: el espacio que se queria obtener, o NULL en caso de error. 
 */
Space *world_get_space(World *w, Id id){
	if(w == NULL || id<0)
		return NULL;

	int idAux=0;

	for(idAux=0; idAux<n_spaces; idAux++){
		if(space_get_id(w->spaces[idAux]) == id)
			return w->spaces[idAux];
	}/*Añadir funcion Id space_get_id(Space *s);, a space.h/.c*/

	printf("Espacio no encontrado.\n");
	return NULL;

}

/* Returns a reference to the corresponding element given an ID. Returns NULL if there is an error or if the element is not found. */

Object *world_get_obj_by_name(World *w, char * name){
	int i=0;
	if(!w || !name)
		return NULL;

	for(i=0;i<MAX_OBJECTS+1;i++){
		if(strcmp(w->objects[i]->name,name))
			return w->objects[i];

	}
	return NULL;
}
Object *world_get_obj(World *w, Id id){
	int i=0;
	if(!w)
		return NULL;

	for(i=0;i<MAX_OBJECTS+1;i++){
		if(w->objects[i]->id==id)
			return w->objects[i];

	}
	return NULL;
}

/* Returns the current location of the player */
 Id world_get_player_location(World *w){
	if(!w)
		return -1;
	return w->player->location;
 }
/* Given a space ID returns the space located north. Returns NULL if there is none or if the link between them is closed. */
 Space *world_get_space_north(World *w, Id space){
 	int i;
 	if(!w)
 		return NULL;
 	for(i=0;i<MAX_SPACES+1;i++){
		if(w->spaces[i]->id==id){
			if(w->spaces[i]->north==0)
				return NULL;
			/*Falta comproabr link entre ellos*/
			return w->spaces[i]->north;
		}

	}
 }
/* Given the name of an object checks if it is located in a given space. Returns the object or NULL if it does not exist. */
 Object *world_get_obj_from_space(World *w, char *name, Id space){
 	int i;
 	if(!w || !name)
 		return NULL;
	for(i=0;i<MAX_OBJECTS+1;i++){
		if(strcmp(w->objects[i]->name,name))
			return w->objects[i];

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

 /* Inspect spaces. Example: 
 -> if there is light 
 -> inspect the room 
The description is returned in the parameter desc which must be allocated by the client */ 
STATUS world_inspect_space(World *w, Space *space, char *desc, int max_len){
	int i;

	if (!w || !space)
		return ERROR;
	/*bucle para localizar el espacio del player*/
	for(i=0;i<MAX_SPACES+1;i++){
		/*comprobacion de coincidencia*/
		if(where_is_player(m) == w->spaces[i]->id){
			/*el espacio está iluminado*/
			if(m->spaces[i]->light==TRUE){
				strcpy(desc,descInspect);
				return OK;
			}
			/*si no esta ilumninado: devuelve la descripcion base*/
			else{
				strcpy(desc,description);
				return OK;
			}
		}
	}
	/*no ha encontrado al player*/
	return ERROR;
} 


/* Inspect Objects. Example: 
 -> if there is light 
 -> inspect object from the inventory or in the current room (if 
hidden, the object is no longer hidden). The description is returned 
in the parameter desc which must be allocated by the client. ***************__allocated by the client__*****/ 
STATUS world_inspect_obj(World * m, Object *obj, char *desc, int max_len){ /*int max_len?*******************/
	int i;
	BOOL hidden=FALSE;

	if(!m || !obj)
		return ERROR;
	/*bucle para localizar el espacio del player*/
	for(i=0;i<MAX_SPACES+1;i++){
		/*comprobacion de coincidencia*/
		if(where_is_player(m) == space_get_id(m->spaces[i])){
			/*el espacio está iluminado*/
			if(is_space_lighted(m->spaces[i])==TRUE){
				/*entonces busca el objeto*/
				for(i=0;i<get_space_set_size(m->spaces[i]);i++){
					/*si coinciden las IDs, lo ha encontrado*/
					if(get_id_from_space_set_index(m->spaces[i], i) == get_object_id(obj)){
						/*devuelve por *desc la descripcion de inspección*/
						if(obj_is_hidden(obj)==TRUE)
							obj_set_not_hidden (obj, hidden);
						strcpy(desc,obj_get_descInspect(obj));
						return OK;
					}
				}
				/*si no encuentra el objeto en el espacio, lo busca en el inv*/
				for(i=0;i<player_inv_size(m->player);i++){
					/*si coinciden las IDs, lo ha encontrado*/
					if(get_id_from_player_inv_set_index(m->player, i) == get_object_id(obj)){
						/*devuelve por *desc la descripcion de inspección*/
						if(obj_is_hidden(obj)==TRUE)
							obj_set_not_hidden (obj, hidden);
						strcpy(desc,obj_get_descInspect(obj));
						return OK;
					}
				}
				/*para light=TRUE, no lo ha encontrado ni en espacio ni en inv*/
				return ERROR;
			}
			/*si el espacio no esta iluminado:*/
			else{
				/*entonces busca el objeto en el espacio*/
				for(i=0;i<m->get_space_set_size(m->spaces);i++){
					/*si coinciden las IDs, lo ha encontrado*/
					if( get_id_from_space_set_index(m->spaces[i], i) == get_object_id(obj)){
						/*devuelve por *desc la descripcion sin mas al no haber luz*/
						/*obj->hidden se mantiene TRUE***************************************/
						strcpy(desc,obj_get_description(obj));
						return OK;
					}
				}
				/*si no encuentra el objeto en el espacio, lo busca en el inv*/
				for(i=0;i<player_inv_size(m->player);i++){
					/*si coinciden las IDs, lo ha encontrado*/
					if(get_id_from_player_inv_set_index(m->player, i) == get_object_id(obj)){
						/*devuelve por *desc la descripcion del objeto sin más*/
						/*obj->hidden se mantiene TRUE*/
						strcpy(desc,obj_get_description(obj));
						return OK;
					}
				}
				/*para light=FALSE, no lo ha encontrado ni en espacio ni en inv*/
				return ERROR;
			}		
		}
		/*no se ha encontrado el espacio donde esta el player*/
		return ERROR;
	}/*fin del for de busqueda de espacios*/
}

/*REVISAR: si X objeto que tiene que hacer Y, no puede hacerlo?***********************/
/* Pick up an object 
 -> the object must not be hidden in the current space 
 -> the object must be movable 
 -> The inventory of the player has to have enough free space for the 
object */ 
STATUS world_pick_up_obj(World *w, Object *obj){
	if(!w || !obj)
		return ERROR;
	if(obj_is_hidden(obj)==TRUE || obj_is_movable(obj)==TRUE)
		return ERROR;
	/*caso que no quepan mas objetos*/
	if(w->player->inventory->max_objects == w->player->inventory->objects->card)
		return ERROR;
	/*entonces pickeamos el objeto***************************************/
	/*1.alloc objeto*/
	/*2.introducir al set de inventario, incrementar num objetos inv/set*/
	/*3.eliminar objeto del array del espacio en el que se encuentra el player*/
} 


/* Drop an object 
 -> the object must be in the inventory */ 
STATUS world_drop_obj(World *w, Object *obj){
	if(!w || !obj)
		return ERROR;
	/*¿esta el objeto en el inventario?*/
	for(i=0;i<w->player->inventory->objects->card;i++){
		/*¿ID objeto recibido misma que ID objeto de inventario?*/
		if(obj->id == w->player->inventory->objects->v[i]){
			/*entonces dropeamos el objeto*********************************/
			/*1.quitar del inventario*/
			/*2.añadir al set del espacio en el que esta el player*/
		}
	}
}

/* Light object 
 -> object in the current room or the inventory 
 -> The object must be lightable 
*/ 
STATUS world_turn_light_on_obj(World *w, Object *obj){
	int i;
	BOOL lighted;

	if(!w || !obj)
		return ERROR;
	/*se puede encender?*/
	if(obj_is_lightable(obj)==TRUE){
		/*¿esta el objeto en el inventario?*/
		for(i=0;i<player_inv_size(w->player);i++){
			/*¿ID objeto recibido misma que ID objeto de inventario?*/
			if(obj->id == get_id_from_player_inv_set_index(w->player, i)){
				if(obj_is_lighted(obj)==TRUE)
					return OK;
				else{
					lighted=TRUE;
					obj_set_lighted (obj,lighted);
					return OK;
				}
			}
		}
		/*¿esta el objeto en ese espacio?*/
		for(i=0;i<get_space_set_size(w->space);i++){
			/*¿ID objeto recibido misma que ID objeto de inventario?*/
			if(get_object_id(obj) == get_id_from_player_inv_set_index(w->player, i)){
				if(obj_is_lighted(obj)==TRUE)
					return OK;
				else{
					lighted=TRUE;
					obj_set_lighted (obj,lighted);
					return OK;
				}
			}
		}
	}
	if(obj_is_lightable(obj)==FALSE)
		return OK;
	return ERROR;
} 


/* Unlight object 
 -> object in the current room or the inventory 
 -> The object must be lightable */ 
STATUS world_turn_light_off_obj(World *w, Object *obj){
	int i;
	BOOL lighted;

	if(!w || !obj)
		return ERROR;
	/*se puede encender?*/
	if(obj_is_lightable(obj)==TRUE){
		/*¿esta el objeto en el inventario?*/

		for(i=0;i<player_inv_size(w->player);i++){
			/*¿ID objeto recibido misma que ID objeto de inventario?*/
			if(get_object_id(obj)== get_id_from_player_inv_set_index(w->player, i)){
				if(obj_is_lighted(obj)==FALSE)
					return OK;
				else{
					lighted=FALSE;
					obj_set_lighted (obj,lighted);
					return OK;
				}
			}
		}
		/*¿esta el objeto en ese espacio?*/
		for(i=0;i<get_space_set_size(w->space);i++){
			/*¿ID objeto recibido misma que ID objeto de inventario?*/								
			if(get_object_id(obj) == get_id_from_player_inv_set_index(w->player, i)){
				if(obj_is_lighted(obj)==FALSE)
					return OK;
				else{
					lighted=FALSE;
					obj_set_lighted (obj,lighted);
					return OK;
				}
			}
		}
	}
	if(obj_is_lightable(obj)==FALSE)
		return OK;
	return ERROR;
} 



/* Illuminates a space if the following conditions are met: 
 -> object is in the space and it is lighten 
 -> object is in the inventory and it is lighten */ 
STATUS world_illuminate_space(World * m, Space *space){
	int i;
	BOOL light;

	if(!m || !space)
		return ERROR;

	/*si hay objetos en el espacio:*/
	if(is_space_set_empty(space)==FALSE){
		/*si alguno de los objetos esta encendido:*/
		if(is_space_lighten_by_object(m,space)==TRUE){
			light=TRUE;
			return space_set_light(space, light);
	    }
	    /*hay objetos pero ninguno encendido:*/
	    else{
	    	light=FALSE;
			return space_set_light(space, light);
	    }
	}
	/*si no hay objetos en el espacio:*/
	if(is_space_set_empty(space)==TRUE){
		/*si tampoco lleva objetos el player:*/
		if(player_inv_size(m->player)==0){
			light=FALSE;
			return space_set_light(space, light);
		}
		/*si lleva objetos y alguno encendido:*/

		if(get_player_inv(m->player)==NULL)
			return ERROR;										
		else if (is_object_inventory_lighted(m, get_player_inv(m->player))==TRUE){
			light=TRUE;
			return space_set_light(space, light);
	   }
	   /*si lleva objetos pero ninguno encendido:*/
	   else{
	   		light=FALSE;
	   		return space_set_light(space, light); 
	   } 
	}
	/*no entra ningun caso*/	
	return ERROR;
} 

/*__________FUNCIONES AUX_________*/

/*AUX_world_1*/
/*busca si algun objeto encendido del mundo m esta en el espacio space*/
BOOL is_space_lighten_by_object(World *m, Space *space){
	int i;

	for(i=0;i<get_space_set_size(space);i++){
		/*Antiguo:
		if(m->objects[i]->lighted==TRUE && m->objects[i]->id == space->space_objects->v[i])
			return TRUE;*/

		/*objeto encendido y coincide la ID del objeto del mundo con ID del objeto del espacio recibido*/
		if(obj_is_lighted(m->objects[i])==TRUE && (get_object_id(m->objects[i]) == get_id_from_space_set_index(space, i)))
			return TRUE;
	}
	return FALSE;
}

/*AUX_world_2*/
/*busca si algun objeto encendido del mundo m esta en el inventario inv*/
BOOL is_object_inventory_lighted(World *m, Inventory *inv){
	int i;
	
	if(get_inventory_set_size(inv)==NO_TAM)
		return FALSE;
	for(i=0;i<get_inventory_set_size(inv);i++){
		/*antiguo: 
		if(m->objects[i]->lighted==TRUE && m->objects[i]->id == inv->objects->v[i])
			return TRUE;*/

		/*objeto encendido y coincide la ID del objeto del mundo con ID del objeto del inventario recibido*/											
		if(obj_is_lighted(m->objects[i]) == TRUE && (get_object_id(m->objects[i]) == get_id_from_inv_index(inv, i)))
			return TRUE;
	}
	return FALSE;
}

/*AUX_world_3*/
Id where_is_player(World *w){
	if(!w)
		return NO_ID;
	return player_get_location(w->player);
}
/*REVISAR: MAX_SPACES+1*******************************************************/

