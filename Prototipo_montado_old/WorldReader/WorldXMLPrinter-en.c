/** 
  *  WorldXMLPrinter.c
  *  
  * This program tests the WorldXMLReader library. All functions needed for the test
  * are included in the program. In a real case, these functions would be distributed
  * among several modules (World, Space, Object and player). 
  * 
  * Simplified versions of the ".h" files of these modules are included with 
  * the test program. Only function prototypes used by WorldXMLReader have been defined.  
  * Also a Makefile is included in the distribution, in order to facilitate the building of 
  * the sample program.
*/

#include <stdio.h>
#include "Consts.h"
#include "World.h"
#include "Space.h"
#include "Object.h"
#include "Player.h"
#include "WorldXMLReader.h"

/**  Space  */
Space *world_add_space(World *world, Id id)
{
	printf("New space Id:%ld\n", id);
	return NULL;
}

STATUS space_set_description(Space *space, char *s)
{
	if (s != NULL)
		printf("\tNew desc. space:%s\n", s);
	return OK; 
}

STATUS space_set_description_inspect(Space *space, char *s)
{
	if (s != NULL)
		printf("\tNew inspect desc. space:%s\n", s);
	return OK; 
}

STATUS space_set_description_graphical(Space *space, char *s) 
{
	if (s != NULL)
		printf("\tNew graphical desc. space:%s\n", s);
	return OK; 
}

STATUS space_add_link_north(Space *space, Id id)
{
	printf("\tNoth Id:%ld\n", id);
	return OK; 
}

STATUS space_add_link_south(Space *space, Id id)
{
	printf("\tSouth Id:%ld\n", id);
	return OK; 
}

STATUS space_add_link_east(Space *space, Id id)
{
	printf("\tEast Id:%ld\n", id);
	return OK; 
}

STATUS space_add_link_west(Space *space, Id id)
{
	printf("\tWest Id:%ld\n", id);
	return OK; 
}

STATUS space_add_link_up(Space *space, Id id)
{
	printf("\tUp Id:%ld\n", id);
	return OK; 
}

STATUS space_add_link_down(Space *space, Id id)
{
	printf("\tDown Id:%ld\n", id);
	return OK; 
}

STATUS space_set_light(Space *space, BOOL is_light)
{
	printf("\tLight:%s\n", is_light ? "TRUE" : "FALSE_VALUE");
	return OK; 
}

STATUS space_add_obj(Space *space, Id id) {
	printf("\tAdd obj.:%ld\n", id);
	return OK; 
}
/**  End Space  */

/**  Link  */
Link *world_add_link(World *world, Id id) {
	printf("New link Id:%ld\n", id);
	return NULL;
}

STATUS link_set_openable(Link *link, BOOL is_openable) {
	printf("\tLink is: %s\n", is_openable ? "TRUE" : "FALSE_VALUE");
	return OK;
}

STATUS link_open(Link *link) 
{
	printf("\tLink open\n");
	return OK;
}

STATUS link_close(Link *link) 
{
	printf("\tLink close\n");
	return OK;
}

STATUS link_join_spaces(Link *link, Id space_1, Id space_2) 
{
	printf("\tLink %ld-%ld\n", space_1, space_2);
	return OK; 
}
/**  End Link  */

/**  Object  */
Object *world_add_obj(World *world, Id id)
{
	printf("New obj. Id:%ld\n", id);
	return NULL; 
}

STATUS obj_set_name(Object *object, char *s)
{
	if (s != NULL)
		printf("\tNew name:%s\n", s);
	return OK;
}

STATUS obj_set_description(Object *object, char *s)
{
	if (s != NULL)
		printf("\tNew desc.:%s\n", s);
	return OK;
}

STATUS obj_set_description_moved(Object *object, char *s)
{
	if (s != NULL)
		printf("\tNew desc. moved:%s\n", s);
	return OK;
}

STATUS obj_set_description_inspect(Object *object, char *s)
{
	if (s != NULL)
		printf("\tNew inspect desc.:%s\n", s);
	return OK;
}

STATUS obj_set_description_graphical(Object *object, char *s)
{
	printf("\tNew graphical desc.:%s\n", s);
	return OK;
}

STATUS obj_set_movable(Object *object, BOOL is_moveable)
{
	printf("\tMovable:%s\n", is_moveable ? "TRUE" : "FALSE_VALUE");
	return OK; 
}

/* By default the objects are visible. Only if you specify that any is hidden,
	this function is called*/
STATUS obj_hide(Object *object) 
{
	printf("\tHidden obj.\n");
	return OK; 
}

STATUS obj_open_link(Object *object, Id id)
{
	printf("\tObj. opens link:%ld\n", id);
	return OK;
}

STATUS obj_set_lightable(Object *object, BOOL is_lightable)
{
	printf("\tLightable:%s\n", is_lightable ? "TRUE" : "FALSE_VALUE");
	return OK; 
}

STATUS obj_set_light(Object *object, BOOL is_light)
{
	printf("\tLit:%s\n", is_light ? "TRUE" : "FALSE_VALUE");
	return OK; 
}

STATUS obj_add_obj(Object *object, Id id)
{
	printf("\tObj. contains obj.:%ld\n", id);
	return OK; 
}
/**  End Object  */

/**  Player  */
Player *world_set_player(World *world)
{
	printf("New player\n");
	return NULL;
}

STATUS player_set_location(Player *player, Id id)
{
	printf("\tLocation %ld\n", id);
	return OK;
}

STATUS player_set_max_objects(Player *player, unsigned int nobj)
{
	printf("\tMax-obj. %u\n", nobj);
	return OK;
}

STATUS player_add_obj(Player *player, Id id)
{
	printf("\tPlayer takes obj.:%ld\n", id);
	return OK; 
}
/**  End Player  */

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Use: %s file_name.xml\n", argv[0]);
	}
	
	world_load(argv[1], NULL);
	
	return OK;
}
