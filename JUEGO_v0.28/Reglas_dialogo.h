/** 
 * @brief Reglas de dialogo del programa
 *
 * Este modulo incluye aquellas funciones relativas a la gestión de las reglas 
 * que rigen el diálogo del juego.
 * @file Reglas.c 
 * @author Alfonso Sebares 
 * @version 0.p 
 * @date 09-03-2014 
 */
#ifndef REGLAS_H_
#define REGLAS_H_

#include "Set.h"
#include "Types.h"

#define NOT_FOUND -1
#define MAX_RULES 255
#define MAX_TOPICS 100 
#define MAX_PATTERNS 100 

typedef struct _Topic Topic;

typedef struct _DialogueRules DialogueRules;

typedef struct _Rule Rule;

/* Constructor and destructor of the structures that store the 
dialogue rules */
DialogueRules *create_dialog();

void destroy_dialog(DialogueRules *dr);

/* Add a new topic defined by a topic name. Returns the topic ID if it 
is properly added. Otherwise a negative identifier is returned. */
int dialog_add_topic(DialogueRules *dr, char *topic_name, Id topic_id);

/* Add a new rule to a topic. The rule is defined by a pattern. 
Returns the rule ID if it is properly added. Otherwise a negative 
identifier is returned.*/
int dialog_add_rule(DialogueRules *dr, Id rule);

/* Add an input pattern to a rule, increasing the num_patterns*/
STATUS dialog_add_pattern(DialogueRules *dr, Id rule, char *pattern);

/* Add a template response and is associated with a rule, increasing 
by one the num_templates */
STATUS dialog_add_output_templ(DialogueRules *dr, Id rule, char *template);

/*Añade la id de una regla al set de reglas de un topic*/
STATUS dialog_add_ruleid_to_topic(DialogueRules *dr, Id topic_id, Id rule_id);

char * select_output_template(DialogueRules *dr, Id rule_id);

char * select_random_output_template (DialogueRules *dr, Id rule_id);

Id search_rule_and_pattern (DialogueRules *dr, int * ind_patr, Id topic, const char * txt_ent);

/*aux de search_rule_and_pattern: busca coincidencias entre los aptrones de una regla a partir del indice
 *del array que ocupa dicha regla en "DialogueRules *dr" */
int search_pattern_coincidence(DialogueRules *dr, int rule_index, const char *txt_ent);

Id get_id_from_topic(DialogueRules *dr, const char *txt_ent);

 #endif /* REGLAS_H_ */
