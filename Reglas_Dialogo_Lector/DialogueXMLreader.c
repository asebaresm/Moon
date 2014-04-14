/**
* @brief Lector de XMl para dialogo
* @file DialogueXMLreader.c
* @author Albert Soler
* @version 0.1
* @date 9-4-14
*/



/*ejemplo de formato del .xml a leer:
<dialogue>
	<rules>
		<rule id="1">
			<patterns>
				<pattern> * </pattern>
			</patterns>
			<templates>
				<template>Buenos dias como se encuentra usted </template>
			</templates>
		</rule>
		...
	</rules>	
	<topics>
		<topic name="T_INIT_GAME">
			<topicid id="1"/>
			<rulest>
				<rulet id="1"/>
				<rulet id="2"/>
				...
			</rulest>
		</topic>
		...
	</topics>
</dialogue>		
*/


#include "DialogueXMLreader.h"

/**!Labels of the XML file*/
#define DIALOGUE "dialogue" /*Labels de topics*/
#define TOPICS "topics"
#define TOPIC "topic"
#define TOPICID "topicid"
#define RULEST "rulest"
#define RULET "rulet"
#define RULES "rules" /*labels de reglas*/
#define RULE "rule"
#define PATTERNS "patterns"
#define PATTERN "pattern"
#define TEMPLATES "templates"
#define TEMPLATE "template"




typedef enum _xml_RETURN {
	XML_ERR = -1,
	XML_OK = 0
} xml_RETURN; /**!<Data type XML_RETURN*/


/*Funciones de topics*/
static xml_RETURN wreader_process_topics(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr);
static xml_RETURN wreader_process_topic(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr);
static xml_RETURN wreader_process_rulet(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr, Id topic_id);
/*Funciones de rules*/
static xml_RETURN wreader_process_rules(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr);
static xml_RETURN wreader_process_rule(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr);
static xml_RETURN wreader_process_pattern(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr, Id rule_id);
static xml_RETURN wreader_process_template(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr, Id rule_id);


/*Funciones genericas procesar texto e ID's*/
static xml_RETURN wreader_process_id(xmlDocPtr doc, xmlNodePtr node, Id *id);
static xml_RETURN wreader_process_text(xmlDocPtr doc, xmlNodePtr node, char *text);



/**
* Carga un dialogo
* Recibe el fichero y puntero al dialogo a incilizar
* return TRUE in case of no ERROR, FALSE otherwise
*
*/

STATUS dialogue_load(char *file_name, DialogueRules *dr){

	xmlDocPtr doc;
	xmlNodePtr node;

	if(!file_name || !dr)
		return FALSE;

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
	if (xmlStrcmp(node->name, (const xmlChar*) DIALOGUE)) {
		fprintf(stderr,"Expected <%s>, instead of %s\n", DIALOGUE, node->name);
		xmlFreeDoc(doc);
		return FALSE;
	}	

	node = node->xmlChildrenNode;
		while(node != NULL) {
			if (!xmlStrcmp(node->name, (const xmlChar*) RULES)) {
				wreader_process_rules(doc, node->xmlChildrenNode, dr);
			}
			else if (!xmlStrcmp(node->name, (const xmlChar*) TOPICS)) {
				wreader_process_topics(doc, node->xmlChildrenNode, dr);
			}
			node = node->next;
		}
	xmlFreeDoc(doc);
	return TRUE;
}

/**
* Procesa topic 
* Lee los topics de un XML file
 * param doc pointer to an XML file
 * param node current XML node in the file
 * param dr pointer to a DialogueRules
 * return XML_OK in case of no ERROR, XML_ERR otherwise 
*/

static xml_RETURN wreader_process_topics(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr){

	xml_RETURN ret = XML_OK;

	if(!doc || !node || !dr)
		return ret = XML_ERR;

	while(node !=NULL){
		if(!xmlStrcmp(node->name, (const xmlChar*) TOPIC)){
			if(wreader_process_topic(doc,node,dr) == XML_ERR){
				return ret = XML_ERR;
			}	
		}
		node = node->next;
	}
	return ret;

}


static xml_RETURN wreader_process_topic(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr){

	xml_RETURN ret = XML_OK;
	xmlChar *value = NULL;
	char text[WORD_SIZE+1];
	
	if(!doc || !node || !dr)
		return ret = XML_ERR;


	/**
	 * Obtains the node's attribute
	 */	  
	value = xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
	if (value!= NULL) {
		strcpy(text, (char *)value);
		xmlFree(value);
	}

	/**
	 * Visits nested nodes
	 */ 
	 node = node->xmlChildrenNode; /* First node */

	while (node != NULL) {
		/*Añadimos el topic name para la id*/
		if  (!xmlStrcmp(node->name, (const xmlChar *) TOPICID)) {
			if ( wreader_process_id(doc, node, &new_id) != ret || dialog_add_topic(dr,text,new_id) ==  NO_ID)
				return ret = XML_ERR;
		} else if (!xmlStrcmp(node->name, (const xmlChar *) RULEST)) {
			if (wreader_process_rulet(doc,node,dr,new_id) == XML_ERROR)
				return ret = XML_ERR;
		} 
		node = node->next;
	}
	return ret;
}

static xml_RETURN wreader_process_rulet(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr, Id topic_id){


	xml_RETURN ret = XML_OK;
	if(!doc || !node || !dr || topic_id==NO_ID)
		return ret = XML_ERR;

	while(node !=NULL){
		if(!xmlStrcmp(node->name, (const xmlChar*) RULET)){
			if(wreader_process_id(doc, node, &new_id) != ret || dialog_add_ruleid_to_topic(dr,topic_id,new_id) ==  ERROR){
				return ret = XML_ERR;
			}	
		}
		node = node->next;
	}
	return ret;
}
/*Procesa las reglas de un XML*/
static xml_RETURN wreader_process_rules(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr){

	xml_RETURN ret = XML_OK;

	if(!doc || !node || !dr)
		return ret = XML_ERR;

	while(node !=NULL){
		if(!xmlStrcmp(node->name, (const xmlChar*) RULES)){
			if(wreader_process_rule(doc,node,dr) == XML_ERR){
				return ret = XML_ERR;
			}	
		}
		node = node->next;
	}
	return ret;
}

static xml_RETURN wreader_process_rule(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr){

	xmlChar *id = NULL;
	xml_RETURN ret = XML_OK;
	Id new_id;
	
	if(!doc || !node || !dr)
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

	/*Creamos una regla con la id*/
 	if(dialog_add_rule(dr,new_id)==NO_ID)
 		return ret = XML_ERR; 
	/**
	 * Visits nested nodes
	 */ 
	node = node->xmlChildrenNode; /** First node */
	while (node != NULL) {
		/*Añadimos patrones a la regla seleccioanda*/
		if (!xmlStrcmp(node->name, (const xmlChar *) PATTERNS)) {
			if ( wreader_process_pattern(doc,node,dr,new_id) == XML_ERR)
				return ret = XML_ERR;
		} 
		/*Templates*/
		else if (!xmlStrcmp(node->name, (const xmlChar *) TEMPLATES)) {
			if ( wreader_process_template(doc,node,dr,new_id) == XML_ERR)
				return ret = XML_ERR;
		} 
		node = node->next;
	}
	return ret;
}

static xml_RETURN wreader_process_pattern(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr, Id rule_id){

	xml_RETURN ret = XML_OK;
	
	if(!doc || !node || !dr || rule_id==NO_ID)
		return ret = XML_ERR;

	/**
	 * Visits nested nodes
	 */ 
	 node = node->xmlChildrenNode; /* First node */
	 while (node != NULL) {
		/*Añadimos patrones a la regla seleccioanda*/
		if (!xmlStrcmp(node->name, (const xmlChar *) PATTERN)) {
			if (wreader_process_text(doc, node, aux) != ret || dialog_add_pattern(dr,rule_id, aux) == ERROR )
				return ret = XML_ERR;
		} 
		node = node->next;
	}
	return ret;
}


static xml_RETURN wreader_process_template(xmlDocPtr doc, xmlNodePtr node,DialogueRules *dr, Id rule_id){
	
	xml_RETURN ret = XML_OK;
	
	if(!doc || !node || !dr || rule_id==NO_ID)
		return ret = XML_ERR;

	/**
	 * Visits nested nodes
	 */ 
	 node = node->xmlChildrenNode; /* First node */
	 while (node != NULL) {
		/*Añadimos templates a la regla seleccioanda*/
		if (!xmlStrcmp(node->name, (const xmlChar *) TEMPLATE)) {
			if (wreader_process_text(doc, node, aux) != ret || dialog_add_output_templ(dr,rule_id, aux) == ERROR )
				return ret = XML_ERR;
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




