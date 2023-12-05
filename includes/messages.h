/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:00:08 by alexandm          #+#    #+#             */
/*   Updated: 2023/12/05 19:10:09 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

// help screen msg
# define MSG_HELP_SETTINGS_0 "To change a setting value press\
 the corresponding key"
# define MSG_HELP_SETTINGS_1 "and scroll up (increase) or down (decrease) or"
# define MSG_HELP_SETTINGS_2 "click mouse wheel button (reset default):"
# define MSG_HELP_SETTINGS_PRINT "- Left click or %s: To interact with objects,\
 characters, or open doors."
# define MSG_HELP_INTRO_0 "Greetings, player! Below you'll find the fundamental"
# define MSG_HELP_INTRO_1 "commands to navigate through this virtual world."
# define MSG_HELP_ROTATION_KEYS "\tROTATION_KEYS: left [ %s ]\
 and right [ %s ]\n\n"
# define MSG_HELP_INTERACTION_PRINT "\t- Left click or %s: To interact with \
objects, characters, or open doors.\n"
# define MSG_HELP_WALK_SPEED_PRINT "\t-WALK SPEED:\t\t[ %s ] + \
[ Mouse wheel ]\n"
# define MSG_HELP_SPEED_ROT_KEY_PRINT "\t-SPEED_ROTATION KEYS:\t[ %s ] + \
[ Mouse wheel ]\n"
# define MSG_HELP_SPEED_ROT_MOUSE_PRNT "\t-SPEED_ROTATION_MOUSE:\t[ %s ] \
+ [ Mouse wheel ]\n"
# define MSG_HELP_FOV "\t-FOV:\t\t\t[ %s ] + [ Mouse wheel ]\n"
# define MSG_HELP_ZOOM_MINIMAP "\t-ZOOM_MINIMAP:\t\t[ %s ] + \
[ Mouse wheel ]\n\n"

# define MSG_SETTINGS_DIMENSION "Screen dimension settings are invalid"
# define MSG_SETTINGS_WALK_SPEED "invalid DEFAULT_WALK_SPEED"
# define MSG_SETTINGS_ROTATE_SPEED "invalid DEFAULT_ROTATE_SPEED_KEY"
# define MSG_SETTINGS_DIST_WALL_MIN "invalid DIST_WALL_MIN"
# define MSG_SETTINGS_FOV_RANGE "settings FOV MIN > FOV MAX"

# define MSG_MAP_OPEN_FAIL "Map: cannot open the given map file"
# define MSG_MAP_FILE_FORMAT "Map: format incorrect, requieres a .cub file"

//map parameters (textures) error messages
# define MSG_WRONG_LINE_FORMAT "Map: wrong number of parameters in a texture \
definition"
# define MSG_WRONG_ACRONYME "Map: wrong acronym for a texture definition or \
wrong character in the top line of the map content"
# define MSG_FILE_EOF "Incomplete file"
# define MSG_OPENDIR_FORBIDDEN "Map: cannot open folder in the mandatory part"
# define MSG_OPENDIR_FAIL "Map: fail to open a texture directory"
# define MSG_NO_XPM_IN_FOLDER "Map: no .xpm file in a texture folder"
# define MSG_ACCEPT_ONLY_XPM "Map: to avoid mlx leaks this program can only \
handle .xpm images as textures, sorry"
# define MSG_TEXTURE_DONT_EXIST "MAP: texture file/directory doesn't exist"
# define MSG_ERR_OPEN_TEXTURE "Map: texture file not reachable/readable"
# define MSG_ERR_OPEN_TEXTURE_DATA "Map: texture data file not \
reachable/readable"
# define MSG_TEXTURE_MISSING_WALL_N "Map: missing texture for the walls' north \
face"
# define MSG_TEXTURE_MISSING_WALL_E "Map: missing texture for the walls' east \
face"
# define MSG_TEXTURE_MISSING_WALL_S "Map: missing texture for the walls' south \
face"
# define MSG_TEXTURE_MISSING_WALL_W "Map: missing texture for the walls' west \
face"
# define MSG_TEXTURE_MISSING_DOOR_F "Map: missing texture for the doors' front"
# define MSG_TEXTURE_MISSING_DOOR_S "Map: missing texture for the doors' sides"
# define MSG_TEXTURE_MISSING_LEAKS "Map: missing texture for the leaks' sides"
# define MSG_TEXTURE_MISSING_CRASHES "Map: missing texture for the crashes' \
sides"
# define MSG_TEXTURE_MISSING_HOLOGRAM "Map: missing texture holograms"
# define MSG_TEXTURE_MULTIPLE_DEF "Map: Multiple definition of texture"
# define MSG_WRONG_COLOR_FORMAT "Map: wrong color format"
# define MSG_COLOR_MISSING_CEIL "Map: missing color for the ceilling"
# define MSG_COLOR_MISSING_FLOOR "Map: missing color for the floor"
# define MSG_COLOR_MULTIPLE_DEF "Map: Multiple definition of flor/ceil color"
# define MSG_WRONG_TIME "Map: wrong time argument in texture definition"

//map content error messages
# define MSG_NO_MAP_CONTENT "Map: map content under all the textures"
# define MSG_MAP_NOT_CLOSED "Map: not surrounded by walls"
# define MSG_INVALID_CHAR "Map: contains an invalid character"
# define MSG_MULTIPLE_PLAYER "Map: multiple player's position"
# define MSG_NO_PLAYER "Map: does not contain a player position"
# define MSG_DOOR_ISOLATED "Map: door not surrounded by at least two opposit\
 walls"
# define MSG_EMPTY_LINE "Map: empty line in the map content"

//big map warning
# define MSG_WARNING_BIG_MAP "display: map dimensions bigger than the window. \
You will not be abble to display a big global map"
# define MSG_WARNING_TEXTURE_DATA_MISSING "map: one texture subdirectory \
contains *.xpm files but the file \"frames_data.txt\" is missing/unreadable. \
This textures subdirectory hasn't been imported."

#endif