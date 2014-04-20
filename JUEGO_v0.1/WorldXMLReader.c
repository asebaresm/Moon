/**
 * WorldXMLReader.c
 */

#include <string.h>
#include "WorldXMLReader.h"

/**!Labels of the XML file*/
#define GAME			"game"
#define MAP				"map"
#define PLAYER			"player"
#define ID 				"id"
#define VALUE			"value"
#define NAME			"name"
#define INITIAL			"initial"
#define SPACE			"space"
#define SPACES			"spaces"
#define DESCR			"description"
#define DESCR_PRIMARY	"pdescription"
#define DESCR_INSPECT	"idescription"
#define DESCR_GRAPHICAL	"gdescription"
#define DESCR_MOVED		"mdescription"
#define LINKS			"links"
#define LINK			"link"
#define LINK_SPACES_1	"connection_1"
#define LINK_SPACES_2	"connection_2"
#define LINK_NORTH		"north"
#define LINK_SOUTH		"south"
#define LINK_EAST 		"east"
#define LINK_WEST		"west"
#define LINK_UP			"up"
#define LINK_DOWN		"down"
#define objS			"objects"
#define obj			"object"
#define MAX_OBJECTS		"max_objects"
#define PROPERTY		"property"
#define LIGHT 			"light"
#define OPENABLE		"openable"
#define MOVABLE			"mobile"
#define HIDDEN			"hidden"
#define OPEN			"open"
#define CONTAINER		"container"
#define LOCATION		"location"
#define COORD_X 		"x"
#define COORD_Y			"y"
#define TRUE_VALUE		"TRUE"
#define FALSE_VALUE		"FALSE"

typedef enum _xml_RETURN {
	XML_ERR = -1,
	XML_OK = 0
} xml_RETURN; /**!<Data type XML_RETURN*/


static xml_RETURN wreader_process_spaces(xmlDocPtr doc, xmlNodePtr node, World *world);
static xml_RETURN wreader_process_space(xmlDocPtr doc, xmlNodePtr node, World *world);
static xml_RETURN wreader_process_space_objs(xmlDocPtr doc, xmlNodePtr node, Space *space);

static xml_RETURN wreader_process_links(xmlDocPtr doc, xmlNodePtr node, World *world);
static xml_RETURN wreader_process_link(xmlDocPtr doc, xmlNodePtr node, World *world);

static xml_RETURN wreader_process_objects(xmlDocPtr doc, xmlNodePtr node, World *world);
static xml_RETURN wreader_process_object(xmlDocPtr doc, xmlNodePtr node, World *world);
static xml_RETURN wreader_process_obj_objs(xmlDocPtr doc, xmlNodePtr node, Object *object);

static xml_RETURN wreader_process_player(xmlDocPtr doc, xmlNodePtr node, World *world);
static xml_RETURN wreader_process_player_objs(xmlDocPtr doc, xmlNodePtr node, Player *player);

static xml_RETURN wreader_process_id(xmlDocPtr doc, xmlNodePtr node, Id *id);
static xml_RETURN wreader_process_text(xmlDocPtr doc, xmlNodePtr node, char *text);
static xml_RETURN wreader_process_bool(xmlDocPtr doc, xmlNodePtr node, BOOL *boolean);
static xml_RETURN wreader_process_bool_initial(xmlDocPtr doc, xmlNodePtr node, BOOL *boolean);

/**
 * Loads a world
 *
 * Creates a new world, reading it from an XML file.
 *
 * @param file_name the file's name
 * @param world pointer to the world to create
 * @return TRUE in case of no ERROR, FALSE otherwise
 **/
STATUS world_load(char *file_name, World *world)
{
	xmlDocPtr doc;
	xmlNodePtr node;
 
	if (!file_name) {
		return FALSE;
	}

	if ((doc = xmlParseFile(file_name))== NULL) {
		fprintf(stderr,"File %s has not XML format.\n", file_name);
		
		return FALSE;
	}
 
	node = xmlDocGetRootElement(doc);
	if (node == NULL) {
		fprintf(stderr, "Empty document\n");
		xmlFreeDoc(doc);
		return FALSE;
	}

	if (xmlStrcmp(node->name, (const xmlChar*) GAME)) {
		fprintf(stderr,"Expected <%s>, instead of %s\n", GAME, node->name);
		xmlFreeDoc(doc);
		return FALSE;
	}
 
	node = node->xmlChildrenNode;
	while(node != NULL) {
		if (!xmlStrcmp(node->name, (const xmlChar*) SPACES)) {
			wreader_process_spaces(doc, node->xmlChildrenNode, world);
		}
		else if (!xmlStrcmp(node->name, (const xmlChar*) LINKS)) {
			wreader_process_links(doc, node->xmlChildrenNode, world);
		}
		else if (!xmlStrcmp(node->name, (const xmlChar*) objS)) {
			wreader_process_objects(doc, node->xmlChildrenNode, world);
		}
		else if (!xmlStrcmp(node->name, (const xmlChar*) PLAYER)) {
			wreader_process_player(doc, node->xmlChildrenNode, world);
		}

		node = node->next;
	}
 
	xmlFreeDoc(doc);
	return TRUE;
}

/**
 * @brief Processes spaces
 *
 * Reads a number of spaces from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param world pointer to a world
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
static xml_RETURN wreader_process_spaces(xmlDocPtr doc, xmlNodePtr node, World *world) {
 
	xml_RETURN ret = XML_OK;
 
	if ((!doc) || (!node))
		return ret = XML_ERR;
 
	while (node != NULL) { 
		if (!xmlStrcmp(node->name, (const xmlChar *) SPACE)){ 
			if (wreader_process_space (doc, node, world) == XML_ERR){ 
				return ret = XML_ERR;
			}
		} 
		node = node->next;
	}
 
	return ret;
}

static xml_RETURN wreader_process_space(xmlDocPtr doc, xmlNodePtr node, World *world) {
 
	xmlChar *id = NULL; 
	xml_RETURN ret = XML_OK;
 
	Id new_id;
	char aux[WORD_SIZE+1];
	BOOL boolean;
	Space *space = NULL;
 
	if ((!doc) || (!node))
		return ret = XML_ERR;
 
	/**
	 * Obtains the node's attribute
	 */
	id = xmlGetProp(node, (const xmlChar *) ID);
	if (id == NULL) {
		return XML_ERR;
	}
	sscanf((char *) id, "%ld", &(new_id));
	xmlFree(id);
	space = (Space *) world_add_space(world, new_id);
	
	/**
	 * Visits nested nodes
	 */ 
	node = node->xmlChildrenNode; /* First node */
	while (node != NULL) {
		if (!xmlStrcmp(node->name, (const xmlChar *) DESCR)) {
		if ( wreader_process_text(doc, node, aux) != ret || space_set_description(space, aux) == ERROR)
			return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) DESCR_INSPECT)) {
			if ( wreader_process_text(doc, node, aux) != ret || space_set_description_inspect(space, aux) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) MAP)) {
			if ( wreader_process_text(doc, node, aux) != ret || space_set_description_graphical(space, aux) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_NORTH)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || space_add_link_north(space, new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_SOUTH)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || space_add_link_south(space, new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_EAST)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || space_add_link_east(space, new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_WEST)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || space_add_link_west(space, new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_UP)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || space_add_link_up(space, new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_DOWN)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || space_add_link_down(space, new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LIGHT)) {
			if ( wreader_process_bool(doc, node, &boolean) != ret || space_set_light(space, boolean) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) objS)) {
			if ( wreader_process_space_objs(doc, node, space) != ret)
				return ret = XML_ERR;
		}
		node = node->next;
	}
	
	return ret;
}

/**
 * @brief Processes the objects of a given space
 *
 * Reads a number of object ids from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param space pontiner to the space
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_space_objs(xmlDocPtr doc, xmlNodePtr node, Space *space) {
	xml_RETURN ret = XML_OK;
	xmlChar *id = NULL;
	Id new_id;
 
	if ((!doc) || (!node))
		return XML_ERR;
 
	node = node->xmlChildrenNode;
	while (node != NULL) {
		if (!xmlStrcmp(node->name, (const xmlChar *) obj)) {
			id = xmlGetProp(node, (const xmlChar *) ID);
			if (id == NULL)
				return ret = XML_ERR;
			sscanf((char *) id, "%ld", &(new_id));
			space_add_obj(space, new_id);
			xmlFree(id);
		}
		node = node->next;
	}
	return ret;
}

/**
 * @brief Processes links
 *
 * Reads the links from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param world pointer to the world to update
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_links(xmlDocPtr doc, xmlNodePtr node, World *world) {
 
	xml_RETURN ret = XML_OK;
 	
	if ((!doc) || (!node))
		return ret = XML_ERR;
 
	while (node != NULL) { 
		if (!xmlStrcmp(node->name, (const xmlChar *) LINK)){
			if (wreader_process_link (doc, node, world) != ret) { 
				return ret = XML_ERR;
			}
		} 
		node = node->next;
	}
 
	return ret;
}

/**
 * @brief Processes a link
 *
 * Reads a link from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param world pointer to the world to update
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_link(xmlDocPtr doc, xmlNodePtr node, World *world) {
 
	xmlChar *id = NULL;
	Link *link = NULL;
	xml_RETURN ret = XML_OK;
 
	Id new_id, space_1, space_2;
	BOOL boolean;

	if ((!doc) || (!node))
		return ret = XML_ERR;
 
	/**
	 * Obtains the node's attribute
	 */
	id = xmlGetProp(node, (const xmlChar *) ID);
	if (id == NULL) {
		return XML_ERR;
	}
	sscanf((char *) id, "%ld", &(new_id));
	xmlFree(id);
	link = world_add_link(world, new_id);
	space_1 = space_2 = -1; 

	/**
	 * Visits nested nodes
	 */ 
	node = node->xmlChildrenNode; /** First node */
	while (node != NULL) {
 
		if (!xmlStrcmp(node->name, (const xmlChar *) OPENABLE)) { 
			if (wreader_process_bool(doc, node, &boolean) != ret)
				return ret = XML_ERR;
			link_set_openable(link, boolean);
	 
			if (boolean == TRUE) {
				/** Openable space */	
				if (wreader_process_bool_initial(doc, node, &boolean) != ret)
					return ret = XML_ERR;
	 	 		
				/** Source space */
				if (boolean == TRUE) {
					if (link_open(link) == ERROR) 
						return ret = XML_ERR; 
				}
				else {
					if (link_close(link) == ERROR)
						return ret = XML_ERR;
				}
			}
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_SPACES_1)) {
			if ( wreader_process_id(doc, node, &space_1) != ret)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LINK_SPACES_2)) {
			if ( wreader_process_id(doc, node, &space_2) != ret)
				return ret = XML_ERR;
		}
		node = node->next;
	}

	if (link_join_spaces(link, space_1, space_2)==ERROR)
		return ret = XML_ERR; 
	return ret;
}

/**
 * @brief Processes objs
 *
 * Reads the objects from an XML file
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param world pointer to the world to update
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_objects(xmlDocPtr doc, xmlNodePtr node, World *world) {
 
	xml_RETURN ret = XML_OK;
 
	if ((!doc) || (!node))
		return ret = XML_ERR;
 
	while (node != NULL) { 
		if (!xmlStrcmp(node->name, (const xmlChar *) obj)){
			if (wreader_process_object (doc, node, world) != ret) {
				return ret = XML_ERR;
			}
		} 
		node = node->next;
	}
	
	return ret;
}
 
/**
 * @brief Processes an object
 *
 * Reads an object from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param world pointer to the world to update
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_object(xmlDocPtr doc, xmlNodePtr node, World *world) {
 
	xmlChar *id = NULL;
	Object *object = NULL;
	xml_RETURN ret = XML_OK;
	char aux[WORD_SIZE+1];
	/**int x=-1, y=-1;*/
	Id new_id;
	BOOL boolean;
	
	if ((!doc) || (!node))
		return ret = XML_ERR;
 
	/**
	 * Obtains the node's attribute
	 */
	id = xmlGetProp(node, (const xmlChar *) ID);
	if (id == NULL) {
		return XML_ERR;	
	}
	sscanf((char *) id, "%ld", &(new_id));
	xmlFree(id);
	object = world_add_obj(world, new_id);
 
	/**
	 * Visits nested nodes
	 */ 
	node = node->xmlChildrenNode; /** First node */
	while (node != NULL) {
		if (!xmlStrcmp(node->name, (const xmlChar *) LOCATION)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || obj_set_location(object, new_id) == ERROR)
				return ret = XML_ERR;
		}else if (!xmlStrcmp(node->name, (const xmlChar *) NAME)) {
			if ( wreader_process_text(doc, node, aux) != ret || obj_set_name(object, aux) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) DESCR_PRIMARY)) {
			if ( wreader_process_text(doc, node, aux) != ret || obj_set_description(object, aux) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) DESCR_MOVED)) {
			if ( wreader_process_text(doc, node, aux) != ret || obj_set_description_moved(object, aux) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) DESCR_INSPECT)) {
			if ( wreader_process_text(doc, node, aux) != ret || obj_set_description_inspect(object, aux) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) DESCR_GRAPHICAL)) {
			if ( wreader_process_text(doc, node, aux) != ret || obj_set_description_graphical(object, aux) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) MOVABLE)) {
			if ( wreader_process_bool(doc, node, &boolean) != ret || obj_set_movable(object, boolean) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) HIDDEN)) {
			if ( wreader_process_bool(doc, node, &boolean) != ret)
				return ret = XML_ERR;
			if (boolean == TRUE)
				obj_hide(object);
		} else if (!xmlStrcmp(node->name, (const xmlChar *) OPEN)) {
			if ( wreader_process_bool(doc, node, &boolean) != ret)
				return ret = XML_ERR;
			if (boolean == TRUE) {
				id = xmlGetProp(node, (const xmlChar *) LINK);
				if (id == NULL)
					return ret = XML_ERR;
				sscanf((char *) id, "%ld", &(new_id));
				xmlFree(id);
				if (obj_open_link(object, new_id)==ERROR)
					return ret = XML_ERR;
			}
		} else if (!xmlStrcmp(node->name, (const xmlChar *) LIGHT)) {
			if (wreader_process_bool(doc, node, &boolean) != ret)
				return ret = XML_ERR;
			obj_set_lightable(object, boolean);
	 
			if (boolean == TRUE) {
				/**spaces iluminable */	
				if (wreader_process_bool_initial(doc, node, &boolean) != ret)
					return ret = XML_ERR;
				obj_set_lighted(object, boolean); 
			}
		}
		/*else if (!xmlStrcmp(node->name, (const xmlChar *) COORD_X)) {
			if ( wreader_process_id(doc, node, (Id*)&x) != ret)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) COORD_Y)) {
			if ( wreader_process_id(doc, node, (Id*)&y) != ret)
				return ret = XML_ERR;
		}*/ 
		else if (!xmlStrcmp(node->name, (const xmlChar *) CONTAINER)) {
			if ( wreader_process_bool(doc, node, &boolean) != ret)
				return ret = XML_ERR;
			if (boolean == TRUE) {
				if (wreader_process_obj_objs(doc, node, object) != ret)
					return ret = XML_ERR;
			}
		} 
		node = node->next;
	}
	
	return ret;
}
 
/**
 * @brief Processes the objects within a given object
 *
 * Reads the objects that belong to the input object.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param object pointer to the object to update
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_obj_objs(xmlDocPtr doc, xmlNodePtr node, Object *object) {

	xml_RETURN ret = XML_OK;
	xmlChar *id = NULL;
	Id new_id;
 
	if ((!doc) || (!node))
		return XML_ERR;
 
	node = node->xmlChildrenNode;
	while (node != NULL) {
		if (!xmlStrcmp(node->name, (const xmlChar *) obj)) {
			id = xmlGetProp(node, (const xmlChar *) ID);
			if (id == NULL)
				return ret = XML_ERR;
			sscanf((char *) id, "%ld", &(new_id));
			obj_add_obj(object, new_id);
			xmlFree(id);
		}
		node = node->next;
	}
	
	return ret;
}

/**
 * @brief Processes a player
 *
 * Reads a player from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param world pointer to the world to update
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_player(xmlDocPtr doc, xmlNodePtr node, World *world) {
 
	xml_RETURN ret = XML_OK;
	Id new_id;
	Player *player = NULL;
 
	if ((!doc) || (!node))
		return ret = XML_ERR;
 
	/**
	 * Obtains the node's attribute
	 */ 
	player = world_set_player(world);
 
	/**
	 * Visits nested nodes
	 */ 
	while (node != NULL) {
		if (!xmlStrcmp(node->name, (const xmlChar *) LOCATION)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || player_set_location(player, new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) MAX_OBJECTS)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || player_set_max_objects(player, (int)new_id) == ERROR)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) objS)) {
			if (wreader_process_player_objs(doc, node, player) != ret)
				return ret = XML_ERR;
		}
		node = node->next;
	}
	
	return ret;
}

/**
 * @brief Processes a player's objects
 *
 * Reads the objects of a given player an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param player pointer to the player to update
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_player_objs(xmlDocPtr doc, xmlNodePtr node, Player *player) {

	xml_RETURN ret = XML_OK;
	xmlChar *id = NULL;
	Id new_id;
 
	if ((!doc) || (!node))
		return XML_ERR;
 
	node = node->xmlChildrenNode;
	while (node != NULL) {
		if (!xmlStrcmp(node->name, (const xmlChar *) obj)) {
			id = xmlGetProp(node, (const xmlChar *) ID);
			if (id == NULL)
				return ret = XML_ERR;
			sscanf((char *) id, "%ld", &(new_id));
			player_add_obj(player, new_id);
			xmlFree(id);
		}
		node = node->next;
	}
	
	return ret;
}

/**
 * @brief Processes text
 *
 * Reads a text value from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param text pointer in which store the read text
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_text(xmlDocPtr doc, xmlNodePtr node, char *text) {
	xmlChar *value = NULL;
	xml_RETURN ret = XML_OK;
 
	if ((!doc) || (!node) || (!text))
		return ret = XML_ERR;
 
	value = xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
	if (value!= NULL) {
		strcpy(text, (char *)value);
		xmlFree(value);
	}
 
	return ret;
}

/**
 * @brief Processes an id
 *
 * Reads an id from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param id pointer in which store the read id
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_id(xmlDocPtr doc, xmlNodePtr node, Id *id) {
	xmlChar *value = NULL;
	xml_RETURN ret = XML_OK;
 
	if ((!doc) || (!node) || (!id))
		return ret = XML_ERR;
 
	value = xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
 
	if (value == NULL)
		return ret = XML_ERR;
 
	sscanf((char *)value, "%ld", id);
	xmlFree(value);
 
	return ret;
}

/**
 * @brief Processes a Boolean value
 *
 * Reads a Boolean value from an XML file.
 *
 * @param doc pointer to an XML file
 * @param node current XML node in the file
 * @param boolean pointer in which store the read Boolean value
 * @return XML_OK in case of no ERROR, XML_ERR otherwise
 **/
xml_RETURN wreader_process_bool(xmlDocPtr doc, xmlNodePtr node, BOOL *boolean) {

	xmlChar *value = NULL;
	xml_RETURN ret = XML_OK;
 
	if ((!doc) || (!node) || (!boolean))
		return ret = XML_ERR;
 
	value = xmlGetProp(node, (const xmlChar *) VALUE);
 
	if (value == NULL)
		return ret = XML_ERR; 
 
	if (!strcmp(TRUE_VALUE, (char *)value)) {
		*boolean = TRUE;
	} else if (!strcmp(FALSE_VALUE, (char *)value)) {
		*boolean = FALSE;
	} else {
		ret = XML_ERR;
	}
	xmlFree(value);
 
	return ret;
}

static xml_RETURN wreader_process_bool_initial(xmlDocPtr doc, xmlNodePtr node, BOOL *boolean)
{
	xmlChar *value = NULL;
	xml_RETURN ret = XML_OK;
 
	if ((!doc) || (!node) || (!boolean))
		return ret = XML_ERR;
 
	*boolean = FALSE; 
	value = xmlGetProp(node, (const xmlChar *) INITIAL); 
	if (value == NULL)
		return ret = XML_OK; /** it may be the case that the initial parameter does not exist */ 
 
	if (!strcmp(TRUE_VALUE, (char *)value)) {
		*boolean = TRUE;
	} else if (!strcmp(FALSE_VALUE, (char *)value)) {
		*boolean = FALSE;
	} else {
		ret = XML_ERR;
	}
	xmlFree(value);
 
	return ret; 
}

