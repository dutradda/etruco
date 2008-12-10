#include <Ecore_Evas.h>
#include <Ecore.h>
#include <Edje.h>
#include <string>

class ETruco
{

	public:
		ETruco();
		~ETruco();
		void run();
		friend void enter_screen_create(void *data, Evas_Object *o, const char *emission, const char *source);
		friend void enter_screen_join(void *data, Evas_Object *o, const char *emission, const char *source);
		friend void enter_screen_waiting(void *data, Evas_Object *o, const char *emission, const char *source);
		friend void leave_create(void *data, Evas_Object *o, const char *emission, const char *source);
		friend void leave_join(void *data, Evas_Object *o, const char *emission, const char *source);
		friend void leave_waiting(void *data, Evas_Object *o, const char *emission, const char *source);
		friend void leave_initial(void *data, Evas_Object *o, const char *emission, const char *source);


	private:
		Ecore_Evas* ecore_evas;
		Evas* evas;
		Evas_Object* edje;
		std::string file_name;
};
