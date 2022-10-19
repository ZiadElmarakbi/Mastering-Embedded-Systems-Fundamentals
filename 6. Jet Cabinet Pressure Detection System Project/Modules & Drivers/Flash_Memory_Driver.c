
#include "Flash_Memory_Driver.h"

fifo_flash flash; // Creating an Object From a FIFO Structure
fifo_flash* flashptr = &flash; // Creating a Pointer to a FIFO Structure
uint32_t flashArr[flashSpace]; // Creating a Flash Memory Storage

// Enumerating Flash Memory States
enum {
	Storing,
	Waiting
}Flash_Memory_state;

// Pointer to function to alternate between states
void (*Flash_Memory_ptr2Fun)(uint32_t);

// Initializing Flash Memory
void Flash_Memory_init(fifo_flash* flashptr, uint32_t* flashArr, uint32_t Length){

	flashptr->Base = flashArr;
	flashptr->Head = flashArr;
	flashptr->Tail = flashArr;
	flashptr->Count = 0;
	flashptr->Length = Length;

	//DPRINTF("Initializing Flash Memory...\n");
	//DPRINTF("...Flash Memory Initialized Successfully !!\n\n");
	Flash_Memory_ptr2Fun = Waiting_State;
}

// Defining the Storing State
void Storing_State(uint32_t pval){

	Flash_Memory_state = Storing;
	Flash_Memory_Enqueue(flashptr, &pval);
	Flash_Memory_state = Waiting;
}

// Defining the Waiting State
void Waiting_State(uint32_t pval){

	Flash_Memory_state = Waiting;

	if(flashptr->Count != flashptr->Length){

		Flash_Memory_ptr2Fun = Storing_State;
		Flash_Memory_ptr2Fun(pval);
	}

	else {Flash_Memory_ptr2Fun = Waiting_State;}
}

// Defining a function to Enqueue Values into the Flash Memory Queue Array
Flash_Memory_Status Flash_Memory_Enqueue(fifo_flash* flashptr, uint32_t* pval){

	if(flashptr->Count == flashptr->Length){

		//  DPRINTF("Warning!! Flash Memory is Full.\n\n");
		return Flash_Memory_Full;
	}

	else{

		*(flashptr->Head) = *(pval);
		flashptr->Count++;

		if(flashptr->Head == flashptr->Base + (flashptr->Length * sizeof(flashSpace))){
			flashptr->Base = flashptr->Head;
			// DPRINTF("Warning!!, Stored Data will be overwritten.\n");
		}

		else
			flashptr->Head++;

		// DPRINTF("...Storing Pressure Value: [%u bars]\n\n",*pval);
		return Flash_No_error;
	}
}

