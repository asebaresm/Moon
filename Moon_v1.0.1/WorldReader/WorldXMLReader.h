
/**
 * @brief Lector de XMl para mundo
 * @file WorldXMLReader.h
 * @author Albert Soler
 * @version 0.1
 * @date 9-4-14
 */
#ifndef XML_READER_H
#define XML_READER_H

#include "../World/World.h"
#include "../TypesXML.h"

/**
 * @name STATUS world_load(char *file_name, World *world);
 * @brief Loads a world
 *
 * Creates a new world, reading it from an XML file.
 *
 * @param file_name the file's name
 * @param world pointer to the world to create
 * @return TRUE in case of no ERROR, FALSE otherwise
 **/
STATUS world_load(char *file_name, World *world);

#endif
