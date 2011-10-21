/* See LICENSE file for license and copyright information */

#ifndef GIRARA_INTERNAL_H
#define GIRARA_INTERNAL_H

#include "girara-types.h"
#include <gtk/gtk.h>

#define CLEAN(m) (m & ~(GDK_MOD2_MASK) & ~(GDK_MOD5_MASK) & ~(GDK_BUTTON1_MASK) & ~(GDK_BUTTON2_MASK) & ~(GDK_BUTTON3_MASK) & ~(GDK_BUTTON4_MASK) & ~(GDK_BUTTON5_MASK) & ~(GDK_LEAVE_NOTIFY_MASK))
#define FORMAT_COMMAND "<b>%s</b>"
#define FORMAT_DESCRIPTION "<i>%s</i>"

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

#ifdef HIDDEN
#elif defined(__GNUC__) && (__GNUC__ >= 4)
# define HIDDEN __attribute__((visibility("hidden")))
#else
# define HIDDEN
#endif

#define LENGTH(x) (sizeof(x)/sizeof((x)[0]))
#define UNTITLED_TAB_TITLE "untitled"


HIDDEN void girara_toggle_widget_visibility(GtkWidget* widget);

/**
 * Free girara_settings_t struct
 *
 * @param setting The setting to free.
 */
HIDDEN void girara_setting_free(girara_setting_t* setting);

HIDDEN void girara_config_handle_free(girara_config_handle_t* handle);

HIDDEN void girara_shortcut_mapping_free(girara_shortcut_mapping_t* mapping);

HIDDEN void girara_shortcut_free(girara_shortcut_t* shortcut);

HIDDEN void girara_inputbar_shortcut_free(girara_inputbar_shortcut_t* shortcut);

HIDDEN void girara_mode_string_free(girara_mode_string_t* mode);

HIDDEN void girara_statusbar_item_free(girara_statusbar_item_t* statusbaritem);

/**
 * Default complection function for the settings
 *
 * @param session The used girara session
 * @param input The current input
 */
HIDDEN girara_completion_t* girara_cc_set(girara_session_t* session, const char* input);

/**
 * Structure of a command
 */
struct girara_command_s
{
  char* command; /**< Name of the command */
  char* abbr; /**< Abbreviation of the command */
  girara_command_function_t function; /**< Function */
  girara_completion_function_t completion; /**< Completion function of the command */
  char* description; /**< Description of the command */
  struct girara_command_s *next; /**< Next command (linked list) */
};

/**
 * Structure of a statusbar item
 */
struct girara_statusbar_item_s
{
  GtkWidget* box; /**< Event box */
  GtkLabel *text; /**< Text label */
};

struct girara_mode_string_s
{
  girara_mode_t index; /**< Index */
  char* name; /**< Name of the mode object */
};

/**
 * Shortcut mapping
 */
struct girara_shortcut_mapping_s
{
  char* identifier; /**> Identifier string */
  girara_shortcut_function_t function; /** Shortcut function */
};

/**
 * Argument mapping
 */
struct girara_argument_mapping_s
{
  char* identifier; /**> Identifier string */
  int value; /**> Value */
  struct girara_argument_mapping_s* next; /**> Next entry */
};

/**
 * Structure of a shortcut
 */
struct girara_shortcut_s
{
  guint mask; /**< Mask */
  guint key; /**< Key */
  char* buffered_command; /**< Buffer command */
  girara_shortcut_function_t function; /**< The correspondending function */
  girara_mode_t mode; /**< Mode identifier */
  girara_argument_t argument; /**< Given argument */
};

/**
 * Structure of a inputbar shortcut
 */
struct girara_inputbar_shortcut_s
{
  guint mask; /**< Mask */
  guint key; /**< Key */
  girara_shortcut_function_t function; /**< Function */
  girara_argument_t argument; /**< Given argument */
};

/**
 * Structure of a special command
 */
struct girara_special_command_s
{
  char identifier; /**< Identifier */
  girara_inputbar_special_function_t function; /**< Function */
  bool always; /**< Evalute on every change of the input */
  girara_argument_t argument; /**< Argument */
  struct girara_special_command_s *next; /**< Next special command (linked list) */
};

/**
 * Structure of a mouse event
 */
struct girara_mouse_event_s
{
  guint mask; /**< Mask */
  guint button; /**< Button */
  girara_shortcut_function_t function; /**< Function */
  girara_mode_t mode; /**< Allowed modes */
  girara_argument_t argument; /**< Given argument */
  struct girara_mouse_event_s *next; /**< Next mouse event (linked list) */
};

/**
 * Config handle
 */
struct girara_config_handle_s
{
  char* identifier;
  girara_command_function_t handle;
};


#endif
