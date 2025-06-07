#pragma once
#include <iostream>
#include "Profesor.h"
using namespace std;

class Sistema {
private:
	//ADMIN
	bool admin = false;
	void menuAdminDebug();
	/// USER
	void menuDebug();

	///
	//void menuPrincipal();
public:
	void iniciarPrograma();
};

