#include <iostream>

int main(){

	char
	op = 'a';

	while( op != 's' )
	{
		std::cout << "### MENU DE TESTE DO X_BOGA ###"   << std::endl;
		std::cout << "\n\n(s) - Sai dessa porra!"	 << std::endl;
		std::cout << "(p) - Vai te chamar de fdp!"   << std::endl;
		std::cout << "(v) - Vai te chamar de viado!" << std::endl;
		std::cout << "(b) - Vai te chamar de bixa!"  << std::endl;
		std::cin >> op;

		if( op == 'p' )
		{
			std::cout << "\n\nSEU FILHO DA PUTA!!" << std::endl;
		}
		else if( op == 'v' )
		{
			std::cout << "\n\nSEU VIADO DO CARALHO!!" << std::endl;
		}
		else if( op == 'b' )
		{
			std::cout << "\n\nSEU BIXA ARROMBADO!!" << std::endl;
		}
		else if( op == 's' )
		{
			std::cout << "\n\nTO VAZANDO!!" << std::endl;
		}
		else
		{
			std::cout << "\n\nDIGITA UMA OPCAO VALIDA SEU IDIOTA!!" << std::endl;
		}
	}
	return 0;
}
