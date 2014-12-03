#include "Mapa.h"
#include "tests.h"
#include "Driver.h"

void test_agregar() {
	Mapa* mapatest = new Mapa();
	mapatest->Agregar("Belgrano");//
	mapatest->Agregar("Palermo");//
	mapatest->Agregar("Recoleta");//
	mapatest->Agregar("Almagro");
	mapatest->Agregar("Microcentro");
	mapatest->Agregar("Retiro");//
	mapatest->Agregar("Constitucion");//

	ArbolSintactico* expr = ArbolSintactico::LeerDeString("negros & !autocheto & (bondi | taxi | subte | auto)");
	mapatest->Conectar("Retiro", "Constitucion", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Retiro", "Constitucion"));
	ASSERT(mapatest->Conectadas("Constitucion", "Retiro"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("!negros & !bondi & (autocheto | auto)");
	mapatest->Conectar("Recoleta", "Palermo", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Recoleta", "Palermo"));
	ASSERT(mapatest->Conectadas("Palermo", "Recoleta"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("bondi | auto | autocheto | taxi");
	mapatest->Conectar("Palermo", "Belgrano", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Belgrano", "Palermo"));
	ASSERT(mapatest->Conectadas("Palermo", "Belgrano"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("auto | !auto");
	mapatest->Conectar("Microcentro", "Almagro", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Microcentro", "Almagro"));
	ASSERT(mapatest->Conectadas("Almagro", "Microcentro"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("auto | !auto");
	mapatest->Conectar("Palermo", "Almagro", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Palermo", "Almagro"));
	ASSERT(mapatest->Conectadas("Almagro", "Palermo"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("bondi | subte");
	mapatest->Conectar("Microcentro", "Retiro", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Retiro", "Microcentro"));
	ASSERT(mapatest->Conectadas("Microcentro", "Retiro"));
	delete expr;

	expr = ArbolSintactico::LeerDeString("bondi | subte");
	mapatest->Conectar("Microcentro", "Constitucion", Driver::ArboltoRestr(expr));
	ASSERT(mapatest->Conectadas("Constitucion", "Microcentro"));
	ASSERT(mapatest->Conectadas("Microcentro", "Constitucion"));
	delete expr;

	delete mapatest;
}

void test_mapa() {

}
