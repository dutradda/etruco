#include "ETruco.h"
using namespace std;

void enter_screen_create(void *data, Evas_Object *o, const char *emission, const char *source)
{
	ETruco* etruco = (ETruco*) data;
	edje_object_file_set(etruco->edje, etruco->file_name.c_str(), "screen-waiting");
}

void enter_screen_join(void *data, Evas_Object *o, const char *emission, const char *source)
{
	ETruco* etruco = (ETruco*) data;
	edje_object_file_set(etruco->edje, etruco->file_name.c_str(), "screen-join");
}

void enter_screen_waiting(void *data, Evas_Object *o, const char *emission, const char *source)
{
	ETruco* etruco = (ETruco*) data;
	edje_object_file_set(etruco->edje, etruco->file_name.c_str(), "screen-waiting");
}

void leave_create(void *data, Evas_Object *o, const char *emission, const char *source)
{
	ETruco* etruco = (ETruco*) data;
	edje_object_file_set(etruco->edje, etruco->file_name.c_str(), "screen-initial");
}

void leave_join(void *data, Evas_Object *o, const char *emission, const char *source)
{
	ETruco* etruco = (ETruco*) data;
	edje_object_file_set(etruco->edje, etruco->file_name.c_str(), "screen-initial");
}

void leave_waiting(void *data, Evas_Object *o, const char *emission, const char *source)
{
	ETruco* etruco = (ETruco*) data;
	edje_object_file_set(etruco->edje, etruco->file_name.c_str(), "screen-join");
}

void leave_initial(void *data, Evas_Object *o, const char *emission, const char *source)
{
	ecore_main_loop_quit();
}

ETruco::ETruco()
{
	ecore_init();
	ecore_evas_init();
	edje_init();

	file_name = string("../data/themes/default/default.edj");

	ecore_evas = ecore_evas_software_x11_new( NULL, 0,  0, 0, 0, 0 );
	ecore_evas_title_set( ecore_evas, "ETruco" );
	ecore_evas_size_min_set( ecore_evas, 800, 600 );
	ecore_evas_size_max_set( ecore_evas, 800, 600 );
	ecore_evas_resize(ecore_evas, 800, 600);

	evas = ecore_evas_get( ecore_evas );
	evas_font_path_append( evas, NULL );

	edje = edje_object_add(evas);
	edje_object_file_set(edje, file_name.c_str(), "screen-initial");
	evas_object_resize(edje, 800, 600);

	evas_object_show(edje);
	ecore_evas_show(ecore_evas);

	edje_object_signal_callback_add(edje, "enter_screen_create", "", enter_screen_create, this);
	edje_object_signal_callback_add(edje, "enter_screen_join", "", enter_screen_join, this);
	edje_object_signal_callback_add(edje, "enter_screen_waiting", "", enter_screen_waiting, this);
	edje_object_signal_callback_add(edje, "leave_create", "", leave_create, this);
	edje_object_signal_callback_add(edje, "leave_join", "", leave_join, this);
	edje_object_signal_callback_add(edje, "leave_waiting", "", leave_waiting, this);
	edje_object_signal_callback_add(edje, "leave_initial", "", leave_initial, this);
}

ETruco::~ETruco()
{
	edje_shutdown();
	ecore_evas_shutdown();
	ecore_shutdown();
}

void ETruco::run()
{
	ecore_main_loop_begin();
}
