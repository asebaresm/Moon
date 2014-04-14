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

 #include "Reglas_dialogo.h"

struct _Topic
{
Id id; 					        /* topic identifier*/
char nombre[WORD_SIZE + 1];     /* topic name */
Set *topic_rules;               /* set of rule indexes associated with a topic */
};


struct _Rule
{
Id id; 						    /* rule identifier */
char * pattern [MAX_PATTERNS];  /* If the string matches any of these input patterns, then executes this rule */
int num_patterns;               /* number of patterns */
char * template [MAX_PATTERNS]; /* List of possible templates that can be used as a response */
int num_templates;              /* number of possible answers */
int last;                       /* Last used template*/
};

struct _DialogueRules
{
Rule l_rule[MAX_RULES];         /* vector to store rules */
int num_rules; 		            /* number of rules stored in l_rule */
Topic l_topic[MAX_TOPICS];      /* vector to store topics */
int num_topic;                  /* number of topics stored in l_topic */
};

/* Constructor of the structures that store the dialogue rules */
DialogueRules *create_dialog(){
	DialogueRules * new_dr=NULL;

	new_dr=(DialogueRules*)calloc(1,sizeof(DialogueRules));
	return new_dr;
}

/* Destructor of the structures that store the dialogue rules */
void destroy_dialog(DialogueRules *dr){
	int i,j;
    int patterns, templates;
	
	if (!dr)
		return;
    /*bucle que libera todos los patrones y plantillas para cada regla (i)*/
	for(i = 0; i < dr->num_rules ; i++){
        patterns= dr->l_rule[i].num_patterns-1;
        templates= dr->l_rule[i].num_templates-1;
        /*libera aptrones*/
        for(j=0; j < patterns; patterns--){
            free(dr->l_rule[i].pattern[patterns]);
            patterns--;
        }
        /*libera plantillas*/
        for(j=0; j < templates; templates--){
            free(dr->l_rule[i].template[templates]);
            templates--;
        }
    }
    /*bucle que libera los sets de los temas*/
    for(i=0; i< dr->num_topic; i++){
        destroy_set(dr->l_topic[i].topic_rules);
    }
    /*liberada toda la memoria dinámica contenida en los TADs, libera el TAD principal*/
    free(dr);
    dr=NULL;
}

/* Add a new topic defined by a topic name. Returns the topic ID if it 
is properly added. Otherwise a negative identifier is returned. */
/*ORG: int dialog_add_topic(DialogueRules *dr, char *topic_name);*/
int dialog_add_topic(DialogueRules *dr, char *topic_name, Id topic_id){
    if(!dr || !topic_name || topic_id == NO_ID)
        return NO_ID;
    strcpy(dr->l_topic[dr->num_topic].nombre, topic_name);
    dr->l_topic[dr->num_topic].id = topic_id;
    dr->l_topic[dr->num_topic].topic_rules=new_set();
    dr->num_topic++;
    return topic_id;
}

/* Add a new rule to a topic. The rule is defined by a pattern. 
Returns the rule ID if it is properly added. Otherwise a negative 
identifier is returned.*/
/*ORG: int dialog_add_rule(DialogueRules *dr, Id topic, char *pattern);*/
int dialog_add_rule(DialogueRules *dr, Id rule) {
    
    if(!dr || rule == NO_ID)
        return NO_ID;
    /*dr->l_rule[dr->num_rules]->pattern[dr->l_rule[dr->num_rules]->num_patterns]=(char*)calloc(1,strlen(pattern)+1);
    strcpy(dr->l_rule[dr->num_rules]->pattern[dr->l_rule[dr->num_rules]->num_patterns], pattern);*/
    dr->l_rule[dr->num_rules].id = rule;
    dr->l_rule[dr->num_rules].last = NO_ID;
    dr->num_rules++;
    return rule;
}

/* Add an input pattern to a rule, increasing the num_patterns*/
STATUS dialog_add_pattern(DialogueRules *dr, Id rule, char *pattern){
    int i;

    if(!dr || rule == NO_ID || !pattern)
        return ERROR;
    /*busqueda de la regla con esa id*/
    for(i=0; i < dr->num_rules; i++){
        /*si encuentra al regla:*/
        if(dr->l_rule[i].id == rule){
            dr->l_rule[i].pattern[dr->l_rule[i].num_patterns]=(char*)calloc(1,strlen(pattern)+1);
            strcpy(dr->l_rule[i].pattern[dr->l_rule[i].num_patterns],pattern);
            dr->l_rule[i].num_patterns++;
            return OK;
        }
    }
    return ERROR;    
}

/* Add a template response and is associated with a rule, increasing 
by one the num_templates */
STATUS dialog_add_output_templ(DialogueRules *dr, Id rule, char *template){
    int i;

    if(!dr || rule == NO_ID || !template)
        return ERROR;
    /*busqueda de la regla con esa id*/
    for(i=0; i < dr->num_rules; i++){
        /*si encuentra la regla:*/
        if(dr->l_rule[i].id == rule){
            dr->l_rule[i].template[dr->l_rule[i].num_templates]=(char*)calloc(1,strlen(template)+1);
            strcpy(dr->l_rule[i].template[dr->l_rule[i].num_templates],template);
            dr->l_rule[i].num_templates++;
            return OK;
        }
    }
    return ERROR;
}

/*Añade la id de una regla al set de reglas de un topic*/
STATUS dialog_add_ruleid_to_topic(DialogueRules *dr, Id topic_id, Id rule_id){
    int i;
    
    if(!dr || rule_id == NO_ID || rule_id == NO_ID)
        return ERROR;
    /*bucle de busqueda del topic con ese topic_id*/
    for(i=0; i< dr->num_topic; i++){
        if(dr->l_topic[i].id == topic_id){
            if(add(dr->l_topic[i].topic_rules, rule_id) == OK)
                return OK;
        }
    }
    return ERROR;
}

char * select_ouput_template(DialogueRules *dr, Id rule_id){
    int i;

    /*comprobacion de que el ind_regla que recibe sea valido*/
    if (rule_id == NO_ID){
        return NULL;
    }
    for(i=0; i < dr->num_rules; i++){
        if(dr->l_rule[i].id == rule_id){
            dr->l_rule[i].last++;
            /*caso 1: iteracion normal del array*/
            if(dr->l_rule[i].last < dr->l_rule[i].num_templates)
                return dr->l_rule[i].template[dr->l_rule[i].last];
            /*caso 2: la ultima plantilla impresa es la ultima posible para esta regla. 
              Se resetea el indicador del array*/
            dr->l_rule[i].last=0;
            return dr->l_rule[i].template[dr->l_rule[i].last];
        }
    }
    return NULL;
}

char * select_random_output_template (DialogueRules *dr, Id rule_id){
    
    float r=0;
    int i, rand_capped;  
    
    for(i=0; i < dr->num_rules; i++){
        if(dr->l_rule[i].id == rule_id){
            r = rand();                
            rand_capped = (r/RAND_MAX)*(dr->l_rule[i].num_templates);
            return dr->l_rule[i].template[rand_capped];
        }
    } 
    return NULL;
}

Id search_rule_and_pattern (DialogueRules *dr, int * ind_patr, Id topic, const char * txt_ent){
    int i,j,k, located_pattern;
    Id rule_id;
    Size set_size;

    if(!ind_patr || !txt_ent)
        return NOT_FOUND;
    /*recorriendo el array de topics:*/
    for(i=0; i < dr->num_topic; i++){
        /*cuando encuentra el topic on esa id:*/
        if(dr->l_topic[i].id == topic){
            /*size del set de reglas que contiene el topic con esa id*/
            set_size = get_size(dr->l_topic[i].topic_rules);
            /*recorriendo el set de reglas:*/
            for(j=0; j < set_size; j++){
                rule_id = get_i_id(dr->l_topic[i].topic_rules, j);
                for(k=0; k < dr->num_rules; k++){
                    /*si el rule_id coincide con una regla del array de reglas:*/
                    if(rule_id == dr->l_rule[k].id){
                        located_pattern = search_pattern_coincidence(dr, k, txt_ent);
                        if(located_pattern != NOT_FOUND){
                            *ind_patr = located_pattern;
                            return rule_id;
                        }
                    }
                }
            }
        }
    }
    return NOT_FOUND;
}

int search_pattern_coincidence(DialogueRules *dr, int rule_index, const char *txt_ent){
    int l;
    char aux_ent[WORD_SIZE];

    for(l=0; l < dr->l_rule[rule_index].num_patterns; l++){
        strcpy(aux_ent, txt_ent);
        aux_ent[strlen(dr->l_rule[rule_index].pattern[l])]='\0';
        if(strcmp(aux_ent, dr->l_rule[rule_index].pattern[l]) == 0)
            return l;
    }
    return NOT_FOUND;
}

