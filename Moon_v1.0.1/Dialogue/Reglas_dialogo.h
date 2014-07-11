/** 
 * @brief Reglas de dialogo del programa. Este modulo incluye aquellas funciones relativas a la gestión de las reglas 
 * que rigen el diálogo del juego.
 * @file Reglas_dialogo.h 
 * @author Alfonso Sebares 
 * @version 0.1
 * @date 09-03-2014 
 */
#ifndef REGLAS_H_
#define REGLAS_H_

#include "../Set/Set.h"

#define NOT_FOUND -1 /*!< No econtrado*/
#define MAX_RULES 255 /*!< maximo de reglas*/
#define MAX_TOPICS 100  /*!< maximo de topics*/
#define MAX_PATTERNS 100  /*!< maximo de patrones*/

 /** @brief TAD topic*/
typedef struct _Topic Topic;

 /** @brief TAD DialogueRules*/
typedef struct _DialogueRules DialogueRules;

 /** @brief TAD Rule*/
typedef struct _Rule Rule;

/* Constructor and destructor of the structures that store the 
dialogue rules */
/**
 *@name DialogueRules *create_dialog();
 *@brief Crea un dialogo
 *@return Puntero a DialogueRules si todo ha ido bien, o NULL en caso contrario
 */
DialogueRules *create_dialog();

/**
 *@name void destroy_dialog(DialogueRules *dr);
 *@brief Destruye un dialogo
 *@param dr
 */
void destroy_dialog(DialogueRules *dr);

/**
 *@name int dialog_add_topic(DialogueRules *dr, char *topic_name, Id topic_id);
 *@brief Add a new topic defined by a topic name
 *@param dr
 *@param topic_name
 *@param topic_id
 *@return  Returns the topic ID if it is properly added. Otherwise a negative identifier is returned
 */
int dialog_add_topic(DialogueRules *dr, char *topic_name, Id topic_id);

/**
 *@name int dialog_add_rule(DialogueRules *dr, Id rule);
 *@brief Add a new rule to a topic
 *@param dr
 *@param rule
 *@return  Returns the rule ID if it is properly added. Otherwise a negative identifier is returned
 */
int dialog_add_rule(DialogueRules *dr, Id rule);

/**
 *@name STATUS dialog_add_pattern(DialogueRules *dr, Id rule, char *pattern);
 *@brief Add an input pattern to a rule, increasing the num_patterns
 *@param dr
 *@param rule
 *@param pattern
 *@return OK/ERROR
 */
STATUS dialog_add_pattern(DialogueRules *dr, Id rule, char *pattern);

/**
 *@name STATUS dialog_add_output_templ(DialogueRules *dr, Id rule, char *template);
 *@brief Add a template response and is associated with a rule, increasing by one the num_templates
 *@param dr
 *@param rule
 *@param template
 *@return OK/ERROR
 */
STATUS dialog_add_output_templ(DialogueRules *dr, Id rule, char *template);

/**
 *@name STATUS dialog_add_ruleid_to_topic(DialogueRules *dr, Id topic_id, Id rule_id);
 *@brief Añade la id de una regla al set de reglas de un topic
 *@param dr
 *@param topic_id
 *@param rule_id
 *@return OK/ERROR
 */
STATUS dialog_add_ruleid_to_topic(DialogueRules *dr, Id topic_id, Id rule_id);

/**
 *@name char * select_output_template(DialogueRules *dr, Id rule_id);
 *@brief Selecciona una plantilla de salida
 *@param dr
 *@param topic_id
 *@return Pùntero a char con la plantilla, o NULL en caso de error. 
 */
char * select_output_template(DialogueRules *dr, Id rule_id);

/**
 *@name char * select_random_output_template (DialogueRules *dr, Id rule_id);
 *@brief Selecciona una plantilla de salida aleatoria
 *@param dr
 *@param topic_id
 *@return Pùntero a char con la plantilla, o NULL en caso de error. 
 */
char * select_random_output_template (DialogueRules *dr, Id rule_id);

/**
 *@name Id search_rule_and_pattern (DialogueRules *dr, int * ind_patr, Id topic, const char * txt_ent);
 *@brief Busca una regla
 *@param dr
 *@param ind_patr
 *@param topic
 *@param txt_ent
 *@return ID de la regla o NO_ID si no la encuentra
 */
Id search_rule_and_pattern (DialogueRules *dr, int * ind_patr, Id topic, const char * txt_ent);

/**
 *@name int search_pattern_coincidence(DialogueRules *dr, int rule_index, const char *txt_ent);
 *@brief busca coincidencias entre los aptrones de una regla a partir del indice *del array que ocupa dicha regla en "DialogueRules *dr"
 *@param dr
 *@param rule_index
 *@param txt_ent
 *@return int de la coincidencia o NOT_FOUND si no lo encuentra
 */
int search_pattern_coincidence(DialogueRules *dr, int rule_index, const char *txt_ent);

/**
 *@name Id get_id_from_topic(DialogueRules *dr, const char *txt_ent);
 *@brief Devuelve la id de un topic si coincide con la cadena de entrada
 *@param dr
 *@param txt_ent
 *@return ID del topic o NO_ID si no la encuentra
 */
Id get_id_from_topic(DialogueRules *dr, const char *txt_ent);

/**
 *@name int size_rule_pattern (DialogueRules *dr,  int rule_index,int ind_patr);
 *@brief Devuelve el tamaño del patron de entrada para ese indice de regla
 *@param dr
 *@param rule_index
 *@param ind_patr
 *@return tamaño del patron o NOT_FOUND si no lo encuentra
 */
int size_rule_pattern (DialogueRules *dr,  int rule_index,int ind_patr);

/**
 *@name char *get_pattern_from_index(DialogueRules *dr, Id rule_id, int *index);
 *@brief Devuelve un patron desde un indice 
 *@param dr
 *@param rule_id
 *@param index
 *@return Puntero al patron o NULL si no lo encuentra
 */
char *get_pattern_from_index(DialogueRules *dr, Id rule_id, int *index);

 #endif /* REGLAS_H_ */
