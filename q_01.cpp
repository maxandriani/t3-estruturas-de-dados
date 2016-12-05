#import <iostream>
#import <stdlib.h>

struct Ticket {
	int number;
	struct Ticket next;
}

Ticket* generate_ticket( int number );
Ticket* push_ticket( Ticket* ticket, Ticket *head );
Ticket* shift_ticket( Ticket* ticket, Ticket *head );
void 		print_ticket_queue( Ticket* head );
void 		print_ticket( Ticket* ticket );
void		print_header();
void		print_menu( Ticket *queue, int last_number );
void 		ui_home( Ticket *queue, int last_number );
void 		ui_queue_in( Ticket *queue, int last_number );
void 		ui_queue_out( Ticket *queue. int last_number );

int main (){
	Ticket *queue = NULL;
	int last_number = 0;

	ui_home( queue, last_number );

	return 0;
}

Ticket* generate_ticket( int number ){
	Ticket *t = (Ticket*) malloc(sizeof(Ticket));
	t->number = number;
	t->next = NULL;
}

Ticket* push_ticket( Ticket *ticket, Ticket *head ){
	Ticket *node;

	if (head == NULL){
		head = ticket;
	} else {
		node = head;
		
		while(node->next != NULL){
			node = node->next;
		}

		node->next = ticket;
	}

	return head;
}

Ticket* shift_ticket( Ticket* head ){
	Ticket *node = NULL;
	
	if (head != NULL){
		node = head->next;
		free(head);
	}
	
	return node;
}

void 		print_ticket_queue( Ticket* head ){
	Ticket *node;

	node = head;
	while(node != NULL){
		print_ticket(node);
		cout << " ";
		node = node->next;
	}
	cout << endl;
}

void 		print_ticket( Ticket* ticket ){
	cout << "["
			 << ticket->number
			 << "]";
}

void		print_header(){
	system("cls");
	cout << "SODINHEIRO BANK" << endl
			 << "Queue system" << endl << endl;
}

void		print_menu( Ticket *queue, int last_number ){
	char k;

	cout << "Escolha uma funcao: " << endl;
			 << "(G) Gerar uma senha de atendimento" << endl
			 << "(P) Proximo atendimento" << endl
			 << "(S) Sair" << endl;

	cin >> k;
	switch(k){
		case 'g':
		case 'G':
			ui_queue_in( queue, last_number );
			break;
		
		case 'p':
		case 'P':
			ui_queue_out( queue, last_number );
			break;

		case 's':
		case 'S':
			break;

		default:
			ui_home( queue, last_number );
	}
}

void 		ui_home( Ticket *queue, int last_number ){
	print_header();

	cout << "Fila atual: ";
	print_ticket_queue(queue);
	cout << endl; << endl;

	print_menu( queue, last_number );
}

void 		ui_queue_in( Ticket *queue, int last_number ){
	Ticket *node;
	
	print_header();

	last_number++;
	node = generate_ticket(last_number);
	queue = push_ticket(node, queue);

	cout << "Sua senha para atendimento e: ";
	print_ticket(node);
	cout << endl;
	system('pause');

	ui_home( queue, last_number );
}
void 		ui_queue_out( Ticket *queue, int last_number ){
	int current;

	print_header();

	if (queue == NULL){
		cout << "A fila esta vazia. Pode ir tomar um cafe." << endl;
	} else {
		cout << "O proximo atendimento e: ";
		print_ticket(queue);
		queue = shift_ticket(queue);
		cout << endl << endl;
	}

	system("pause");

	ui_home(queue, last_number);
}