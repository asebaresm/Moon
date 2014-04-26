/**
 *@file Action.h
 *@brief contiene las implementaciones de las funciones de Action
 *@author Pablo Yus
 *@version 0.01
 *@date 24-03-2014
 */

#ifndef _ACTION
#define _ACTION


#include "World.h"

/**
 * @brief enumeracion de acciones
 */
typedef enum {
    A_GO,
    A_PICK_UP,
    A_DROP,
    A_INSPECT,
    A_TURN_LIGHT_ON,
    A_TURN_LIGHT_OFF,
    A_SPEAK,
    A_ABRIR
} ActionType;

/**
 * @brief Estrucura accion 
 */
typedef struct _Action Action;

/**
 *@name: action_execute
 *@brief: ejecuta una accione en particular en mundo (excepto A_PICK_UP)
 *@param: World *w: mundo sobre el que se ejecuta la accion
 *@param: Action *a: accion que se va a ejecutar
 *@return: devuelve OK si todo ha ido bien o ERROR si algo ha fallado

Executes a particular action on the world (except A_PICK_UP). The 
action includes the type of action and the direct object the action is 
performed over. Returns OK if everything goes well or ERROR if there 
is an error. */
STATUS action_execute(World *w, Action *a);

/**
 *@name: action_execute_inspect
 *@brief: reserva memeoria para la cadena que almacenara la descripicion del objeto inspeccionado.
 *@param: World *w: mundo que contine aquello que se va a inspeccionar.
 *@param: Action *a: accion a realizar
 *@param: char *inspected: cadena de caracteres que guarda la descripcion de lo inspeccionado.
 *@param: Size max_len: tamño maximo de la cadena inspected.
 *@return: devuelve Ok si todo ha ido bien o ERROR si ha habido algun error.

Executes the inspect action. The description is returned in the 
“inspected“ parameter, which must be allocated by the client. 
Returns OK if everything goes well and ERROR otherwise. 
 */
STATUS action_execute_inspect(World *w, Action *a, char *inspected, Size max_len);

/**
 *@name: topic_is_valid
 *@brief: permite comprobar si el tema es valido para ese momento del juego. 
 *@param: World *w: mundo actual
 *@param: Topic t: tema a comprobar
 *@return: devuelve TRUE si es valido el tema, o FALSE en caso contrario.

Allows to check if a given conversation topic is valid for the 
current state of the game. Returns TRUE if so and FALSE otherwise.
 */
/*BOOL topic_is_valid (World *w, Topic t);*/

/*----------------Auxiliares---------------*/

/**
 * @name Action* new_action(const char* do_act, ActionType id);
 * @brief crea una nueva accion
 * @param do_act
 * @param id
 * @return la accion si se ha creado correctamente o NULL en caso contrario
 */
Action* new_action(const char* do_act, ActionType id);

/**
 * @name void destroy_action(Action *a);
 * @brief destruye una accion liberando memoria que habia sido reservada previamente
 * @param a
 */
void destroy_action(Action *a);


STATUS set_action(Action *a, const char *do_act, ActionType id);

#endif /*_ACTION*/
