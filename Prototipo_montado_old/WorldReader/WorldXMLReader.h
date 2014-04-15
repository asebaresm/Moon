/** 
 * WorldXMLReader.h
 */

#ifndef XML_READER_H
#define XML_READER_H

#include "../Types.h"
#include "../World/World.h"
#include "../Space/Space.h"
#include "../Object/Object.h"
#include "../Player/Player.h"
#include "../Link/Link.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define WORD_SIZE 1024

STATUS world_load(char *file_name, World *world);

#endif
