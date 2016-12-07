#include <iostream>
#include <stdlib.h>
#include <string>

#define SLOTS 10;

struct Car {
	string plate;
	int attempts;
};

struct CarQueue {
	Car car;
	struct CarQueue *next;
	struct CarQueue *prev;
};

CarQueue  *car_queue_build( string plate );
CarQueue 	*car_queue_push( CarQueue *head, CarQueue slot );
CarQueue 	*car_queue_pop( CarQueue *head );
int				car_queue_sizeof( CarQueue *head );
void			car_queue_print( CarQueue *head );

void			ui_head();
bool			ui_menu( CarQueue **parking, CarQueue **street );
bool			ui_start( CarQueue **parking, CarQueue **street );
bool			ui_add_car( CarQueue **parking, CarQueue **street );
bool			ui_remove_car( CarQueue **parking, CarQueue **street ); 

int main(){
	CarQueue *parking = NULL;
	CarQueue *street  = NULL;
	bool t = true;
	while(t = true){
		t = ui_start( &parking, &street );
	}

	return 0;
}

CarQueue  *car_queue_build( string plate ) {
	CarQueue *node = NULL;
	CarQueue *q = (CarQueue*) malloc(sizeof(CarQueue));
	q->next = NULL;
	q->pref = NULL;
	q->car.plate
	q->car.attempts = 0;
	return q;
}

CarQueue 	*car_queue_push( CarQueue *head, CarQueue slot ) {
	if (head != NULL){
		node = head;
		while(node->next != NULL){
			node = node->next;
		}
		node->next = slot;
		slot->prev = node;
		slot->next = NULL;
	} else {
		head = slot;
		head->prev = NULL;
		head->next = NULL;
	}

	return head;
}

CarQueue 	*car_queue_pop( CarQueue *head ){
	CarQueue *node = head;
	
	if (node != NULL){
		while(node->next != NULL){
			node = node->next;
		}

		if (node != head){
			node->prev->next = NULL;
		}
		
		node->next = NULL;
		node->prev = NULL;
	}

	return node;
}

int				car_queue_sizeof( CarQueue *head ){
	int s = 0;
	CarQueue *node = head;
	while(node != NULL){
		s++;
		node = node->next;
	}
	return s;
}

void			car_queue_print( CarQueue *head ){
	CarQueue *node = head;
	cout << "{ ";
	while(node != NULL){
		cout << "[P: " << node->car.plate << "|A: " << node->car.attempts << "]";
		if (node->next != NULL){
			cout " ";
		} 
		node = node->next;
	}
	cout << "}" << endl;
}

void			ui_head(){
	system("cls");
	cout << "Redmond Parking Co" << endl
			 << "Version: 1.0" << endl
			 << endl;
}
bool			ui_menu( CarQueue **parking, CarQueue **street ){
	char k = NULL;
	while(k != 's' && k != 'S'){
		cout << "Por favor, selecione uma opcao: " << endl
				 << "N - Novo carro;" << endl
				 << "R - Remover carro;" << endl
				 << "S - Sair" << endl;
		cin >> k;

		switch(k){
			case 'n':
			case 'N':
				return ui_add_car( parking, street );
				break;
			case 'r':
			case 'R':
				return ui_remove_car( parking, street );
				break;
		}
	}
	return 0;
}
bool			ui_start( CarQueue **parking, CarQueue **street ){
	bool = k;

	ui_head();
	return ui_menu( parking, street );
}
bool			ui_add_car( CarQueue **parking, CarQueue **street ){
	string 	plate;
	int			queue_size = car_queue_sizeof((*parking));

	ui_head();

	if (queue_size == SLOTS){
		cout << "Desculpe, mas o estacionamento esta lotado." << endl;
	} else {
		cout << "Informe a placa do veiculo (sem espacos): ";
		cin >> plate;

		*parking = car_queue_pop( *parking, plate );

		car_queue_print( *parking ); 
	}

	system("pause");
	return 1;
}

bool			ui_remove_car( CarQueue **parking, CarQueue **street ){
	string 	 plate;
	CarQueue *node;
	int 		 position = 0;
	bool 		 searching = true;

	ui_head();

	cout << "Informe a placa do carro que deseja retirar (sem espacos): ";
	cin >> plate;

	cout << "Procurando carro...";
	node = *parking;
	while(searching){
		if (node->car.plate == plate){
			cout << " encontrado";
			searching =  false;
		} else {
			position++;
			node = node->next;
			if (node == NULL){
				searching = false;
				cout << "não encontrado";
			}
		}
	}
	cout << endl;

	for (int x=0; x<=position; x++){
		node = car_queue_pop( *parking );
		// Check empty
		if (node == *paring){
			*parking = NULL;
		}
		// if it is the car...
		if (x < position){
			// Increase car move
			node->car.attempts++;
			// Put car on street
			*street = car_queue_push(*street, node);
		}
	}

	cout << "Carro [" << node->car->plate << "] foi removido. Houveram " << node->car->attempts << " manobras enquanto estava estacionado." << endl;

	// Devolvendo carros para o estacionamento
	while (*street != NULL){
		node = car_queue_pop( *street );
		// Check empty
		if (node == *street){
			*street = NULL;
		}
		// Put car back on parking
		*parking = car_queue_push(*parking, node);
	}

	car_queue_print( *parking ); 

	system("pause");
	return 1;
}