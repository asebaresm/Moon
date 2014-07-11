/**
* @brief Lector de XMl para dialogo
* @file DialogueXMLreader.h
* @author Albert Soler
* @version 0.1
* @date 9-4-14
*/

#ifndef XML_READER_H
#define XML_READER_H

#include "../Dialogue/Reglas_dialogo.h"


#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/*#include <libxml/parser.h>*/
/*#define WORD_SIZE 1024*/

/**
 * @name STATUS dialogue_load(char *file_name, DialogueRules *dr);
 * @brief carga un dialogo desde un fichero XML
 * @param file_name
 * @param dr
 * @return OK/ERROR
 */
STATUS dialogue_load(char *file_name, DialogueRules *dr);

#endif
