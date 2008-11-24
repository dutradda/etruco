#include <Messages_Handler.h>

int main(int argc, char** argv) {
	Messages_Handler message_handler = Messages_Handler(argv[1]);
	
	int* a = new int(atoi(argv[2]));
	int* b = new int(atoi(argv[3]));

	message_handler.register_messages();
	message_handler.run_message_rcv(atoi(argv[2]), a);
	message_handler.run_message_send(atoi(argv[3]), b);

	delete a;
	delete b;

	return 0;
}
