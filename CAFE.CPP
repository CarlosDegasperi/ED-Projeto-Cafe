// Programa TURMA DO CAFE 2.SEMESTRE (Estrutura de Dados)
// Prof Me Orlando
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estrutura para armazenar informa��es de participantes
struct Participante {
    int id;
    string nome;
    int semestre;
    int anoIngresso;
    string curso;
    Participante* proximo;
};

// Estrutura para armazenar informa��es de contribui��es
struct Contribuicao {
    int idParticipante;
    int mes;
    int ano;
    double valor;
    Contribuicao* proximo;
};

// N� da lista encadeada de participantes
struct Node {
    Participante participante;
    Node* next;
};

// N� da lista encadeada de contribui��es
struct NodeContribuicao {
    Contribuicao contribuicao;
    NodeContribuicao* next;
};

Node* headParticipantes = NULL;
NodeContribuicao* headContribuicoes = NULL;

// Fun��o para inserir participante na lista encadeada
void inserirParticipante(int id, string nome, int semestre, int anoIngresso, string curso) {
    Participante novoParticipante;
    novoParticipante.id = id;
    novoParticipante.nome = nome;
    novoParticipante.semestre = semestre;
    novoParticipante.anoIngresso = anoIngresso;
    novoParticipante.curso = curso;

    Node* novoNode = new Node();
    novoNode->participante = novoParticipante;
    novoNode->next = NULL;

    if (headParticipantes == NULL) {
        headParticipantes = novoNode;
    } else {
        Node* temp = headParticipantes;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNode;
    }

    cout << "Participante inserido com sucesso!!!" << endl;
}

// Fun��o para verificar se um participante existe
bool participanteExiste(int id) {
    Node* temp = headParticipantes;
    while (temp != NULL) {
        if (temp->participante.id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Fun��o para ler participantes do arquivo e inserir na lista encadeada
void lerParticipantesDoArquivo() {
    ifstream arquivo("participantes.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo participantes.txt!!!" << endl;
        return;
    }

    int id, semestre, anoIngresso;
    string nome, curso;

    while (arquivo >> id >> nome >> semestre >> anoIngresso >> curso) {
        inserirParticipante(id, nome, semestre, anoIngresso, curso);
    }

    arquivo.close();
}

// Fun��o para editar participante na lista encadeada
void editarParticipante(int id) {
    Node* temp = headParticipantes;
    while (temp != NULL) {
        if (temp->participante.id == id) {
            string nome, curso;
            int semestre, anoIngresso;

            cout << "Digite o novo nome: ";
            cin >> nome;
            cout << "Digite o novo semestre: ";
            cin >> semestre;
            cout << "Digite o novo ano de ingresso: ";
            cin >> anoIngresso;
            cout << "Digite o novo curso (DSM, SI, GE): ";
            cin >> curso;

            temp->participante.nome = nome;
            temp->participante.semestre = semestre;
            temp->participante.anoIngresso = anoIngresso;
            temp->participante.curso = curso;

            cout << "Participante atualizado com sucesso!!!" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Participante com ID " << id << " n�o encontrado!!!" << endl;
}

// Fun��o para mostrar todos os participantes cadastrados
void mostrarParticipantes() {
    if (headParticipantes == NULL) {
        cout << "Nenhum participante cadastrado!!!" << endl;
    } else {
        Node* temp = headParticipantes;
        while (temp != NULL) {
            cout << "ID: " << temp->participante.id 
                 << ", Nome: " << temp->participante.nome 
                 << ", Semestre: " << temp->participante.semestre 
                 << ", Ano de Ingresso: " << temp->participante.anoIngresso 
                 << ", Curso: " << temp->participante.curso << endl;
            temp = temp->next;
        }
    }
}

// Fun��o para gravar participantes no arquivo
void gravarParticipantesNoArquivo() {
    ofstream arquivo("participantes.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo participantes.txt para escrita!!!" << endl;
        return;
    }

    Node* temp = headParticipantes;
    while (temp != NULL) {
        arquivo << temp->participante.id << " "
                << temp->participante.nome << " "
                << temp->participante.semestre << " "
                << temp->participante.anoIngresso << " "
                << temp->participante.curso << endl;
        temp = temp->next;
    }

    arquivo.close();
    cout << "Dados dos participantes gravados com sucesso em participantes.txt!!!" << endl;
}

// Fun��o para cadastrar contribui��o de um participante
void cadastrarContribuicao(int idParticipante, int mes, int ano, double valor) {
    if (!participanteExiste(idParticipante)) {
        cout << "Participante com ID " << idParticipante << " n�o encontrado. Nenhuma contribuicao cadastrad!!!" << endl;
        return;
    }

    Contribuicao novaContribuicao;
    novaContribuicao.idParticipante = idParticipante;
    novaContribuicao.mes = mes;
    novaContribuicao.ano = ano;
    novaContribuicao.valor = valor;
    
    NodeContribuicao* novoNode = new NodeContribuicao();
    novoNode->contribuicao = novaContribuicao;
    novoNode->next = NULL;

    if (headContribuicoes == NULL) {
        headContribuicoes = novoNode;
    } else {
        NodeContribuicao* temp = headContribuicoes;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novoNode;
    }

    cout << "Contribui��o cadastrada com sucesso!!!" << endl;
}

// Fun��o para liberar a mem�ria alocada para participantes
void liberarMemoriaParticipantes() {
    Node* temp = headParticipantes;
    while (temp != NULL ){
        Node* proximo = temp->next;
        delete temp;
        temp = proximo;
    }
}

// Fun��o para liberar a mem�ria alocada para contribui��es
void liberarMemoriaContribuicoes() {
    NodeContribuicao* temp = headContribuicoes;
    while (temp != NULL) {
        NodeContribuicao* proximo = temp->next;
        delete temp;
        temp = proximo;
        delete temp;
        temp = proximo;
    }
}

// Fun��o para exibir todas as contribui��es cadastradas
void mostrarContribuicoes() {
    if (headContribuicoes == NULL) {
        cout << "Nenhuma contribui��o cadastrada!!!" << endl;
    } else {
        NodeContribuicao* temp = headContribuicoes;
        while (temp != NULL) {
            cout << "ID Participante: " << temp->contribuicao.idParticipante
                 << ", Mes: " << temp->contribuicao.mes
                 << ", Ano: " << temp->contribuicao.ano
                 << ", Valor: " << temp->contribuicao.valor << endl;
            temp = temp->next;
        }
    }
}

// Fun��o para gravar contribui��es no arquivo
void gravarContribuicoesNoArquivo() {
    ofstream arquivo("contribuicoes.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo contribuicoes.txt para escrita!!!" << endl;
        return;
    }

    NodeContribuicao* temp = headContribuicoes;
    while (temp != NULL) {
        arquivo << temp->contribuicao.idParticipante << " "
                << temp->contribuicao.mes << " "
                << temp->contribuicao.ano << " "
                << temp->contribuicao.valor << endl;
        temp = temp->next;
    }

    arquivo.close();
    cout << "Contribui��es gravadas com sucesso em contribuicoes.txt!!!" << endl;
}

// Fun��o para gravar contribui��es por curso nos arquivos separados
void gravarContribuicoesPorCurso() {
    ofstream arquivoDSM("contribuintes_DSM.txt");
    ofstream arquivoSI( "contribuintes_SI.txt");
    ofstream arquivoGE( "contribuintes_GE.txt");

    NodeContribuicao* temp = headContribuicoes;
    while (temp != NULL) {
        if (temp->contribuicao.idParticipante != -1) {
            if (temp->contribuicao.idParticipante < 10) {
                arquivoDSM << "0" << temp->contribuicao.idParticipante << " "
                           << temp->contribuicao.mes << " "
                           << temp->contribuicao.ano << " "
                           << temp->contribuicao.valor << endl;
            } else if (temp->contribuicao.idParticipante < 20) {
                arquivoSI << "0" << temp->contribuicao.idParticipante - 10 << " "
                          << temp->contribuicao.mes << " "
                          << temp->contribuicao.ano << " "
                          << temp->contribuicao.valor << endl;
            } else if (temp->contribuicao.idParticipante < 30) {
                arquivoGE << "0" << temp->contribuicao.idParticipante - 20 << " "
                          << temp->contribuicao.mes << " "
                          << temp->contribuicao.ano << " "
                          << temp->contribuicao.valor << endl;
            }
        }
        temp = temp->next;
    }

    arquivoDSM.close();
    arquivoSI.close();
    arquivoGE.close();

    cout << "Contribui��es gravadas com sucesso:" << endl;
    cout << " - contribuintes_DSM.txt" << endl;
    cout << " - contribuintes_SI.txt" << endl;
    cout << " - contribuintes_GE.txt" << endl;
}

// Fun��o para liberar toda a mem�ria alocada
void liberarMemoria() {
    liberarMemoriaParticipantes();
    liberarMemoriaContribuicoes();
}

// Fun��o principal
int main() {
	setlocale(LC_ALL, "Portuguese");
	int opcao;

    do {
        cout << "\nTURMA DO CAFE - FATEC(ARARAS)\n";
        cout <<   "-----------------------------\n";
        cout << "1. Inserir Participante\n";
        cout << "2. Mostrar Participante\n";
        cout << "3. Editar  Participante\n";
        cout << "4. LER     Participantes do TXT\n";
        cout << "5. GRAVAR  TXT Participantes\n";
        cout << "6. Inserir Contribui��o\n";
        cout << "7. Mostrar Contribui��es\n";
        cout << "8. GRAVAR  TXT Contribui��es\n";
        cout << "9. GRAVAR  TXT Contribui��es por curso\n";
        cout << "0. Sair\n";
        cout << "ESCOLHA A OP��O DESEJADA: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                int id, semestre, anoIngresso;
                string nome, curso;

                cout << "Digite o ID: ";
                cin >> id;
                cout << "Digite o nome: ";
                cin >> nome;
                cout << "Digite o semestre: ";
                cin >> semestre;
                cout << "Digite o ano de ingresso: ";
                cin >> anoIngresso;
                cout << "Digite o curso (DSM, SI, GE): ";
                cin >> curso;
                
                inserirParticipante(id, nome, semestre, anoIngresso, curso);
                break;
            }
            case 2:
                mostrarParticipantes();
                break;
            case 3: {
                int id;
                cout << "Digite o ID do participante a ser editado: ";
                cin >> id;
                editarParticipante(id);
                break;
            }
            case 4:
                lerParticipantesDoArquivo();
                break;
            case 5:
                gravarParticipantesNoArquivo();
                break;
            case 6: {
                int idParticipante, mes, ano;
                double valor;

                cout << "Digite o ID do participante: ";
                cin >> idParticipante;
                cout << "Digite o mes da contribuicao (1 a 12): ";
                cin >> mes;
                cout << "Digite o ano da contribuicao (>= 2024): ";
                cin >> ano;
                if (ano < 2024) {
					cout << "ATEN��O: Ano Inv�lido!!!";
					break;
				}
                            	
				cout << "Digite o valor da contribuicao: ";
                cin >> valor;

                cadastrarContribuicao(idParticipante, mes, ano, valor);
                break;
            }
            case 7:
                mostrarContribuicoes();
                break;
            case 8:
                gravarContribuicoesNoArquivo();
                break;
            case 9:
                gravarContribuicoesPorCurso();
                break;
            case 0:
                cout << "- SAINDO..." << endl;
                break;
            default:
                cout << "- OP��O INV�LIDA!!!" << endl;
        }
    } while (opcao != 0);

    liberarMemoria();

    return 0;
}

