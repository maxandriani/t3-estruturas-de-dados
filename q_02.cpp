#include <cstdlib>
#include <cstring>
#include <iostream>

#define SLOTS 10

using namespace std;

struct CarQueue {
	string plate;
	int attempts;
	struct CarQueue *next;
	struct CarQueue *prev;
};

CarQueue  *car_queue_build( string plate );
CarQueue 	*car_queue_push( CarQueue *head, CarQueue *slot );
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
	while(t == true){
		t = ui_start( &parking, &street );
	}

	return 0;
}

CarQueue  *car_queue_build( string plate ) {
	CarQueue *q = (CarQueue*) malloc(sizeof(CarQueue));
	q->next = NULL;
	q->prev = NULL;
	q->attempts = 0;
	q->plate = plate;
	return q;
}

CarQueue 	*car_queue_push( CarQueue *head, CarQueue *slot ) {
	CarQueue *node = head;
	if (node != NULL){
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
		cout << "[" << node->plate << "|" << node->attempts << "]";
		if (node->next != NULL){
			cout << " ";
		} 
		node = node->next;
	}
	cout << " }" << endl;
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
	bool k;

	ui_head();
	k = ui_menu( parking, street );

	cout << "Estacionamento: ";
	car_queue_print( *parking );
	cout << endl << "Rua: ";
	car_queue_print( *street );
	cout << endl;
	
	return k;
}
bool			ui_add_car( CarQueue **parking, CarQueue **street ){
	CarQueue *node = NULL;
	int			 queue_size = car_queue_sizeof((*parking));
	string   plate;

	ui_head();

	if (queue_size == SLOTS){
		cout << "Desculpe, mas o estacionamento esta lotado." << endl;
	} else {
		
		cout << "Informe a placa do veiculo (sem espacos): ";
		cin.clear();
    cin.ignore();
		getline(cin, plate);

		node = car_queue_build( plate );
		*parking = car_queue_push( *parking, node );

		cout << "Estacionamento: ";
		car_queue_print( *parking );
		cout << endl; 
	}

	cout << endl;

	system("pause");
	return true;
}

bool			ui_remove_car( CarQueue **parking, CarQueue **street ){
	string 	 plate;
	CarQueue *node;
	int 		 position = -1;
	int			 size = car_queue_sizeof(*parking);
	bool 		 searching = true;

	ui_head();

	cout << "Informe a placa do carro que deseja retirar (sem espacos): ";
	cin.clear();
  cin.ignore();
	getline(cin, plate);
	//cin >> plate;

	cout << "Procurando carro...";
	node = *parking;
	while(searching){
		cout << plate << endl;
		cout << node->plate <<  endl;
		if (plate == node->plate){
			cout << " encontrado na posicao " << position;
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

	if (position > -1){
		// Carro encontrado
		searching = true;
		while (searching){
			node = car_queue_pop( *parking );
			car_queue_print( *parking );
			// Check empty
			if (node == *parking){
				*parking = NULL;
			}
			// if it is not the car..
			if (node->plate == plate){
				searching = false;
			} else {
				// Increase car move
				node->attempts++;
				// Put car on street
				*street = car_queue_push(*street, node);
				car_queue_print( *street );
			}
		}
	}

	cout << "Carro [" << node->plate << "] foi removido. Houveram " << node->attempts << " manobras enquanto estava estacionado." << endl;

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

	cout << "Carros estacionados novamente." << endl
			 << "Estacionamento: ";

	car_queue_print( *parking );

	cout << endl;

	system("pause");
	return true;
}